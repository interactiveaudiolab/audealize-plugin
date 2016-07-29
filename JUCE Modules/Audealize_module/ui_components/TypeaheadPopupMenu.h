//
//  TypeaheadPopupMenu.h
//
//  Original code written by user bazrush from the JUCE community forums.
//  https://forum.juce.com/t/type-ahead-dropdown-box/5600/8
//

#ifndef TypeaheadPopupMenu_h
#define TypeaheadPopupMenu_h

using nlohmann::json;

class TypeaheadPopupMenu : public ListBoxModel,
                           public Component
{
public:
    TypeaheadPopupMenu() : shadow(DropShadow())
    {
        setAlwaysOnTop(true);
        setOpaque(true);
        list.setModel(this);
        list.setColour(ListBox::ColourIds::backgroundColourId, Colours::white);
        list.setRowHeight(30);
        addAndMakeVisible(list);
        
        shadow.setOwner(this);
    }
    
    void setItems(const std::vector<String> & options_)
    {
        options = options_;
        list.updateContent();
        setSize(getWidth(), jmin(int(options.size()), 5) * list.getRowHeight());
    }
    
    void resized() override
    {
        list.setBounds(getLocalBounds());
    }
    
    void paint(Graphics & g) override
    {
    }
    
    int getNumRows() override
    {
        return options.size();
    }
    
    
    void setActionOnItemSelected(std::function<void(String)> function)
    {
        onItemSelected = function;
    }
    
    void listBoxItemClicked(int row, const MouseEvent&) override
    {
        if (onItemSelected)
            onItemSelected(options[row]);  // note action may delete this object
    }
    
    void returnKeyPressed(int lastRowSelected) override
    {
        if (onItemSelected)
            onItemSelected(options[lastRowSelected]);  // note action may delete this object
    }
    
    void paintListBoxItem(int rowNumber, Graphics& g, int width, int height, bool rowIsSelected) override
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
    
    void setFirstItemFocused()
    {
        toFront(true);
        list.selectRow(0);
    }
    
private:
    std::function<void(String)> onItemSelected;
    ListBox list;
    std::vector<String> options;
    DropShadower shadow;
};


/**
 A text editor component that shows a pop-up menu/combo box below it.
 */
class TypeaheadEditor : public Component,
                        public TextEditor::Listener,
                        public KeyListener,
                        public Timer,
                        public ActionListener
{
public:
    TypeaheadEditor()
    {
        addAndMakeVisible(editor);
        
        editor.addListener(this);
        editor.addKeyListener(this);
        editor.setColour(TextEditor::outlineColourId, Colours::grey);
        editor.setWantsKeyboardFocus(true);
        
        setFromMap = false;
        setWithoutPressingReturn = false;
    }
    
    void mouseDown(const MouseEvent& event) override
    {
        if (!isParentOf(event.eventComponent))
            dismissMenu();
    }
    
    ~TypeaheadEditor()
    {
        Desktop::getInstance().removeGlobalMouseListener(this);
    }
    
    void setOptions(std::vector<String> opts){
        options.clear();
        for (int i = 0; i < opts.size(); i++){
            options.add(opts[i]);
        }
        options.sort(true);
        options.minimiseStorageOverheads();
    }
    
    void showMenu()
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
    
    void textEditorTextChanged(TextEditor&) override
    {
        dismissMenu();
        
        std::vector<String> stringsToShow;
        
        auto text = editor.getText();
        auto itemId = 0;
       
        if (options.contains(text) && !setFromMap){
            dismissMenu();

            bubbleMessage = new BubbleMessageComponent(1000);
            bubbleMessage->setColour(BubbleMessageComponent::ColourIds::backgroundColourId, Colours::white);
            bubbleMessage->setColour(BubbleMessageComponent::ColourIds::outlineColourId, Colours::green);
            getParentComponent()->addChildComponent(bubbleMessage);
            
            AttributedString attString;
            attString.append ("Found \"" + text + "\"", Font (18.0f));
            
            bubbleMessage->showAt(&editor, attString, 1000, true, false);
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
                stringsToShow.push_back(o);
            
            itemId++;
        }
        
        if (stringsToShow.size() == 0){
            vector<string> syn = synonyms(text);
            if (syn.size() > 0){
                int i = 0;
                while (stringsToShow.size() <= 5 && i < syn.size()){
                    if (binarySearch(&options, String(syn[i]))){ // because JUCE::StringArray::contains is a bit slow
                        stringsToShow.push_back(syn[i]);
                    }
                    i++;
                }
            }
            //if (stringsToShow == 0)
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
    
    void dismissMenu()
    {
        menu = nullptr;
        stopTimer();
        Desktop::getInstance().removeGlobalMouseListener(this);
    }
    
    void timerCallback() override
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
    
    bool keyPressed(const KeyPress& key, Component * component) override
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
    
    void focusLost(FocusChangeType cause) override
    {
        if(!menu->hasKeyboardFocus(true)){
            dismissMenu();   
        }
        if (menu && !menu->hasKeyboardFocus(true))
            menu = nullptr;
    }
    
    void resized() override
    {
        editor.setBounds(getLocalBounds()); 
    }
    
    void actionListenerCallback(const juce::String &message) override{
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
    
    TextEditor* getEditor(){
        return &editor;
    }
    
    vector<string> synonyms(String word){
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
    
    bool binarySearch(StringArray* arr, String str){
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
    
private:
    ScopedPointer<TypeaheadPopupMenu> menu;
    StringArray options;
    TextEditor editor;
    ScopedPointer<BubbleMessageComponent> bubbleMessage;
    bool setFromMap;
    bool setWithoutPressingReturn;
    json synonymCache;
};


#endif /* TypeaheadPopupMenu_h */
