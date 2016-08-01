#include "TypeaheadPopupMenu.h"

//================================================================================================
// TypeaheadPopupMenu
//================================================================================================

TypeaheadPopupMenu::TypeaheadPopupMenu() : shadow(DropShadow())
{
    setAlwaysOnTop(true);
    setOpaque(true);
    list.setModel(this);
    list.setColour(ListBox::ColourIds::backgroundColourId, Colours::white);
    list.setRowHeight(30);
    addAndMakeVisible(list);
    
    shadow.setOwner(this);
}

void TypeaheadPopupMenu::setItems(const StringArray & options_)
{
    for (auto s : options_){
        options.push_back(s);
    }
    list.updateContent();
    setSize(getWidth(), jmin(int(options.size()), 5) * list.getRowHeight());
}

void TypeaheadPopupMenu::resized()
{
    list.setBounds(getLocalBounds());
}

void TypeaheadPopupMenu::paint(Graphics & g) 
{
}

int TypeaheadPopupMenu::getNumRows() 
{
    return options.size();
}


void TypeaheadPopupMenu::setActionOnItemSelected(std::function<void(String)> function)
{
    onItemSelected = function;
}

void TypeaheadPopupMenu::listBoxItemClicked(int row, const MouseEvent&) 
{
    if (onItemSelected)
        onItemSelected(options[row]);  // note action may delete this object
}

void TypeaheadPopupMenu::returnKeyPressed(int lastRowSelected) 
{
    if (onItemSelected)
        onItemSelected(options[lastRowSelected]);  // note action may delete this object
}

void TypeaheadPopupMenu::paintListBoxItem(int rowNumber, Graphics& g, int width, int height, bool rowIsSelected) 
{
    if (rowNumber >= options.size())
        return;
    
    auto fg = Colours::black;
    auto bg = Colours::white;
    
    if (rowIsSelected){
        fg = Colours::white;
        bg = Colours::mediumpurple;
    }
    g.fillAll(bg);
    g.setColour(fg);
    g.setFont(height*0.65f);
    g.drawText(options[rowNumber], 10, 0, width, height * 0.8f, Justification::left, true);
}

void TypeaheadPopupMenu::setFirstItemFocused()
{
    toFront(true);
    list.selectRow(0);
}


//================================================================================================
// TypeaheadEditor
//================================================================================================

TypeaheadEditor::TypeaheadEditor() : synonymCache(0)
{
    addAndMakeVisible(editor);
    
    editor.addListener(this);
    editor.addKeyListener(this);
    editor.setColour(TextEditor::outlineColourId, Colours::grey);
    editor.setWantsKeyboardFocus(true);
    
    setFromMap = false;
    setWithoutPressingReturn = false;
    
}

TypeaheadEditor::~TypeaheadEditor()
{
    Desktop::getInstance().removeGlobalMouseListener(this);
}

void TypeaheadEditor::mouseDown(const MouseEvent& event) 
{
    if (!isParentOf(event.eventComponent))
        dismissMenu();
}

void TypeaheadEditor::setOptions(std::vector<String> opts){
    options.clear();
    for (int i = 0; i < opts.size(); i++){
        options.add(opts[i]);
    }
    options.sort(true);
    options.minimiseStorageOverheads();
}

void TypeaheadEditor::showMenu()
{
    menu = new TypeaheadPopupMenu();
    menu->addToDesktop(ComponentPeer::StyleFlags::windowIsTemporary);
    menu->setVisible(true);
    menu->setBounds(getScreenBounds().translated(0, getHeight()).withHeight(100));
    
    editor.toFront(true);
    editor.setHighlightedRegion(Range<int>(editor.getText().length(), editor.getText().length()));
    menu->setActionOnItemSelected([this](String item)
                                  {
                                      editor.setText(item, dontSendNotification);
                                      editor.keyPressed(KeyPress(KeyPress::returnKey));
                                      menu = nullptr;
                                  });
    
    menu->addKeyListener(this);
    
    Desktop::getInstance().addGlobalMouseListener(this);
    
    startTimer(200);
}

void TypeaheadEditor::textEditorTextChanged(TextEditor&) 
{
    dismissMenu();
    
    StringArray stringsToShow;
    
    auto text = editor.getText();
    auto itemId = 0;
    
    if (options.contains(text) && !setFromMap){
        dismissMenu();
        
        AttributedString attString;
        attString.append ("Found \"" + text + "\"", Font (18.0f));

        showBubbleMessage(attString, Colours::green);
        
        setWithoutPressingReturn = true;
        editor.keyPressed(KeyPress(KeyPress::returnKey));
        editor.setHighlightedRegion(Range<int>(text.length(), text.length()));
        
        return;
    }
    if (setFromMap){
        setFromMap = false;
    }
    
    for (auto o : options)
    {
        if (o.containsIgnoreCase(text))
            stringsToShow.add(o);
        
        itemId++;
    }
    
    if (stringsToShow.size() == 0){ // if descriptor not found in this map
        for (int i = 0; i < otherMaps.size(); i++){  // search other maps
            if (otherMaps[i].contains(text, true)){
                AttributedString attString;
                attString.append ("Try checking the " + otherMapEffectNames[i] + "map", Font (18.0f));
                showBubbleMessage(attString, Colours::blue, Colours::lightblue);
            }
        }
        if (cacheKeys.contains(text, true)){ // check if synonyms are cached
            int index = cacheKeys.indexOf(text, true);
            stringsToShow = synonymCache[index];
        }
        else{  // if not, get synonyms from server and add to cache
            vector<string> syn = synonyms(text);
            if (syn.size() > 0){
                int i = 0;
                while (stringsToShow.size() <= 10 && i < syn.size()){
                    if (binarySearch(&options, String(syn[i]))){ // because JUCE::StringArray::contains is a bit slow
                        stringsToShow.addIfNotAlreadyThere(syn[i]);
                    }
                    i++;
                }
            }
            synonymCache.push_back(stringsToShow);
            cacheKeys.add(text);
        }
    }
    
    if (stringsToShow.size() == 0)
    {
        dismissMenu();
    }
    else if (editor.getText().length() == 0)
    {
        dismissMenu();
    }
    else if (stringsToShow.size() == 1 && stringsToShow[0].equalsIgnoreCase(editor.getText()))
    {
        dismissMenu();
    }
    else
    {
        if (!menu)
            showMenu();
        
        menu->setItems(stringsToShow);
    }
}

void TypeaheadEditor::dismissMenu()
{
    menu = nullptr;
    stopTimer();
    Desktop::getInstance().removeGlobalMouseListener(this);
}

void TypeaheadEditor::timerCallback() 
{
    if (!Process::isForegroundProcess())
        //dismissMenu();
        
        if (menu)
        {
            if (!hasKeyboardFocus(true) && !menu->hasKeyboardFocus(true))
                dismissMenu();
        }
        else
        {
            if (!hasKeyboardFocus(true))
                dismissMenu();
        }
}

bool TypeaheadEditor::keyPressed(const KeyPress& key, Component * component) 
{
    if (component == &editor)
    {
        if (key == KeyPress::downKey || key == KeyPress::tabKey)
        {
            if (menu)
                menu->setFirstItemFocused();
            
            return true;
        }
    }
    else if (component == menu)
    {
        // if the user tries to type into the menu lets move the focus back there and inject the keypress
        editor.toFront(true);
        return editor.keyPressed(key);
    }
    
    return false;
}

void TypeaheadEditor::focusLost(FocusChangeType cause) 
{
    if(!menu->hasKeyboardFocus(true)){
        dismissMenu();
    }
    if (menu && !menu->hasKeyboardFocus(true))
        menu = nullptr;
}

void TypeaheadEditor::resized() 
{
    editor.setBounds(getLocalBounds());
}

void TypeaheadEditor::actionListenerCallback(const juce::String &message) {
    if(!message.equalsIgnoreCase("_languagechanged")){
        editor.setText(message);
        if (!setWithoutPressingReturn){
            editor.selectAll();
        }
        setWithoutPressingReturn = false;
        
        dismissMenu();
        setFromMap = true;
    }
}

TextEditor* TypeaheadEditor::getEditor(){
    return &editor;
}

void TypeaheadEditor::setMultiEffect(vector<String> effectNames, vector<StringArray> descriptors){
    isMultiEffect = true;
    otherMaps = descriptors;
    otherMapEffectNames = effectNames;
}

vector<string> TypeaheadEditor::synonyms(String word){
    if (word.contains(" ")){  // don't want spaces in the url
        return vector<string>(0);
    }
    
    //Thesaurus service provided by words.bighugelabs.com
    URL url = URL("https://words.bighugelabs.com/api/2/4cdc8dfc9297f52969df235e3b339e63/" + word + "/json");
    
    string urlText = url.readEntireTextStream(true).toStdString();
    
    if (urlText.length() == 0){
        return vector<string>(0);
    }
    
    json dict = json::parse(urlText);
    
    vector<string> likewords(0);
    
    if (!dict.empty()){
        // iterate through parts of speech
        for (auto it = dict.begin(); it != dict.end(); ++it){
            if (!it.value().empty()){
                // iterate through relation (synonym, antonym, etc...)
                for (auto it2 = it.value().begin(); it2 != it.value().end(); ++it2){
                    // don't include antonyms
                    if (!it2.value().empty() && String(it2.key().c_str()) != "ant") {
                        vector<string> words = it2.value().get<vector<string>>();
                        likewords.insert(std::end(likewords), std::begin(words), std::end(words)); // add to likewords
                    }
                }
            }
        }
    }
    
    return likewords;
}

bool TypeaheadEditor::binarySearch(StringArray* arr, String str){
    int left = 0;
    int right = arr->size();
    
    while (left <= right){
        int mid = (left + right) / 2;
        
        if ((*arr)[mid].equalsIgnoreCase(str)){
            return true;
        }
        else if ((*arr)[mid] > str){
            right = mid - 1;
        }
        else {
            left = mid + 1;
        }
    }
    return false;
}

void TypeaheadEditor::showBubbleMessage(AttributedString str, Colour outlineColor, Colour fillColor){
    bubbleMessage = new BubbleMessageComponent(1000);
    bubbleMessage->setColour(BubbleMessageComponent::ColourIds::backgroundColourId, fillColor);
    bubbleMessage->setColour(BubbleMessageComponent::ColourIds::outlineColourId, outlineColor);
    getParentComponent()->addChildComponent(bubbleMessage);
    
    
    bubbleMessage->showAt(&editor, str, 1000, true, false);
}

