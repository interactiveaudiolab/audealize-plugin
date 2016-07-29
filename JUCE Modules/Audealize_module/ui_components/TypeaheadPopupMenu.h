//
//  TypeaheadPopupMenu.h
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
    TypeaheadPopupMenu();
    ~TypeaheadPopupMenu() {};
    
    /**
     *  <#Description#>
     *
     *  @param options_ <#options_ description#>
     */
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
    
    void listBoxItemClicked(int row, const MouseEvent&) override;
    
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
    
    void dismissMenu();
    
    void timerCallback() override;
    
    bool keyPressed(const KeyPress& key, Component * component) override;
    
    void focusLost(FocusChangeType cause) override;
    
    void resized() override;
    
    void actionListenerCallback(const juce::String &message) override;
    
    TextEditor* getEditor();
    
    vector<string> synonyms(String word);
    
    bool binarySearch(StringArray* arr, String str);
    
private:
    ScopedPointer<TypeaheadPopupMenu> menu;
    StringArray options;
    TextEditor editor;
    ScopedPointer<BubbleMessageComponent> bubbleMessage;
    bool setFromMap;
    bool setWithoutPressingReturn;
    vector<StringArray> synonymCache;
    StringArray cacheKeys;
};


#endif /* TypeaheadPopupMenu_h */
