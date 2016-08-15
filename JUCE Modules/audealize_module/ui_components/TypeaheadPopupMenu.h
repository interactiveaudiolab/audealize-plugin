//
//  TypeaheadPopupMenu.h
//
//  Defines classes for creating the search bar for Audealize Plugins
//
//  Based on code written by user bazrush from the JUCE community forums.
//  https://forum.juce.com/t/type-ahead-dropdown-box/5600/8
//

#ifndef TypeaheadPopupMenu_h
#define TypeaheadPopupMenu_h

using nlohmann::json;
using std::vector;

class TypeaheadPopupMenu : public ListBoxModel,
                           public Component
{
public:
    enum ColourIds{
        backgroundColourId = 0x2000400,
        textColourId = 0x2000401,
        highlightColourId = 0x2000402,
        textSelectedColourId = 0x2000403
    };
    
    
    TypeaheadPopupMenu();
    ~TypeaheadPopupMenu() {};
    
    void setItems(const StringArray & options_);
    
    void resized() override;
    
    void paint(Graphics & g) override;
    
    int getNumRows() override;
    
    /**
     *  Sets the function to be executed when an item is selected
     *
     *  @param std::function<void(String)> function
     */
    void setActionOnItemSelected(std::function<void(String)> function);
    
    /**
     *  Called when an item in the popup menu is clicked
     *
     *  @param row         row index
     *  @param MouseEvent&
     */
    void listBoxItemClicked(int row, const MouseEvent&) override;
    
    /**
     *  Called when return key pressed in TypeaheadEditor
     *
     *  @param lastRowSelected
     */
    void returnKeyPressed(int lastRowSelected) override;
    
    /**
     *  Paint an individual row of the popup menu
     *
     *  @param rowNumber
     *  @param g             Graphics drawing context
     *  @param width
     *  @param height
     *  @param rowIsSelected
     */
    void paintListBoxItem(int rowNumber, Graphics& g, int width, int height, bool rowIsSelected) override;
    
    void setFirstItemFocused();
    
private:
    std::function<void(String)> onItemSelected;
    ListBox list;
    std::vector<String> options;
    DropShadower shadow;
};


/**
 *  A TextEditor component that displays a TypeaheadPopupMenu below it with suggestions of words
 *
 */
class TypeaheadEditor : public Component,
                        public TextEditor::Listener,
                        public KeyListener,
                        public Timer,
                        public ActionListener
{
public:
    TypeaheadEditor();
    ~TypeaheadEditor();

    void mouseDown(const MouseEvent& event) override;
    
    /**
     *  Set the list of words to be searched by the texteditor
     *
     *  @param opts a vector<String>
     */
    void setOptions(std::vector<String> opts);
    
    /**
     *  Show the TypeaheadPopupMenu
     */
    void showMenu();
    
    /**
     *  Called when the text of the texteditor is changed
     *  Searches for matching words in options, searches for synonyms if none present
     *
     *  @param TextEditor&
     */
    void textEditorTextChanged(TextEditor&) override;
    
    /**
     *  Remove the popup menu from the screen
     */
    void dismissMenu();
    
    /**
     *  Inherited from timer
     */
    void timerCallback() override;
    
    /**
     *  Called when a key is pressed. Inherited from KeyListener
     *
     *  @param key       KeyPress&
     *  @param component The component that has focus
     *
     *  @return bool
     */
    bool keyPressed(const KeyPress& key, Component * component) override;
    
    void focusLost(FocusChangeType cause) override;

    void resized() override;
        
    /**
     *  Used to set text of editor when word is selected in a WordMap
     *
     *  @param message  A string containing the word
     */
    void actionListenerCallback(const juce::String &message) override;
    
    /**
     *  Tells the TypeaheadPopupMenu that it is part of a multi effect plugin and should therefore search the descriptor sets for the ther effects
     *
     *  @param effectNames vector<String> list of names of other effects in the plugin (EQ, reverb, etc..)
     *  @param descriptors vector<StringArray> containing the sets of descriptors for each other effect/wordmap. Must be in same order as effectNames
     */
    void setMultiEffect(vector<String> effectNames, vector<StringArray> descriptors);
    
    TextEditor* getEditor();
    
    /**
     *  Finds synonyms of a given word using WordNet
     *
     *  @param word
     *
     *  @return StringArray of synonyms
     */
    StringArray synonyms(String word);
    
    /**
     *  Use binary search to find a String in a StringArray
     *
     *  @param arr StringArray
     *  @param str String
     *
     *  @return true if found
     */
    bool binarySearch(StringArray* arr, String str);
    
    /**
     *  Show a BubbleMessageComponent pointed at this TypeaheadEditor
     *
     *  @param str          The message to be displayed
     *  @param outlineColor Color of the outline of the BubbleMessageComponent
     *  @param fillColor      Color of the outline of the BubbleMessageComponent
     *  @param timeInMS     Time (in ms) for BubbleMessageComponent to stay visible
     */
    void showBubbleMessage(AttributedString str, Colour outlineColor, Colour fillColor = Colours::white, int timeInMS = 1000);
    
    /**
     *  Returns a StringArray containing the set of descriptors being searched by this TypeaheadEditor
     *
     *  @return StringArray
     */
    StringArray getDescriptors(){
        return options;
    }
    
private:
    ScopedPointer<TypeaheadPopupMenu> menu;  // the popup menu containing suggestions
    StringArray options;  // the set of words to be searched
    TextEditor editor;  // the text box
    ScopedPointer<BubbleMessageComponent> bubbleMessage;  // a bubble message for displaying messages/warnings
    bool setFromMap;  // true if the text of the TextEditor was last set as a result of choosing a word on a WordMap (not by typing into the editor)
    bool setWithoutPressingReturn;  // true if the word was selected automatically (word was found in map and selected, but user did not press return key)
    vector<StringArray> otherMaps;  // vector of StringArrays containing the descriptor sets for other effects (if plugin is a multi effect
    vector<String> otherMapEffectNames;  // vector containing the names of the other effects (if plugin is a multi effect)
    bool isMultiEffect;  // true if parent plugin is a multi effect
};


#endif /* TypeaheadPopupMenu_h */
