//
//  TypeaheadPopupMenu.h
//
//  Original code written by user bazrush from the JUCE community forums
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
        std::vector<String> stringsToShow;
        
        auto text = editor.getText();
        auto itemId = 0;
       

        
        for (auto o : options)
        {
            if (o.containsIgnoreCase(text))
                stringsToShow.push_back(o);
            
            itemId++;
        }
        
        if (stringsToShow.size() == 0){
            vector<string> syn = synonyms(text);
            if (syn.size() > 0){
                for (int i = 0; i < 5; i++){
                    stringsToShow.push_back(syn[i]);
                }
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
            editor.selectAll();
            dismissMenu();
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
        
        string urlText = url.readEntireTextStream().toStdString();
            
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
private:
    ScopedPointer<TypeaheadPopupMenu> menu;
    StringArray options;
    TextEditor editor; 
};


#endif /* TypeaheadPopupMenu_h */
