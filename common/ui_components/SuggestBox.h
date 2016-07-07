//
//  SuggestBox.h
//
//  A JUCE::ListBox component for displaying descriptor suggestions for an Audealize::SearchBar
//

#ifndef SUGGESTBOX_H_INCLUDED
#define SUGGESTBOX_H_INCLUDED

using std::vector;

class SuggestBox : public Component, public ListBoxModel {
public:
    SuggestBox() {
        addAndMakeVisible(mListBox = new ListBox());
        mListBox->setModel(this);
        mListBox->setColour(ListBox::backgroundColourId, Colours::white);
        mListBox->setColour(ListBox::textColourId, Colours::black);
    }
    
    ~SuggestBox() {
        mListBox = nullptr;
    }
    
    /**
     *  Set the words to be displayed in the box
     *
     *  @param words Vector<Juce::String> of words
     */
    void setWords(vector<String> words){
        mWords = words;
    }
    
    /**
     *  Adds an individual word to the listbox
     *
     *  @param word
     */
    void addWord(String word){
        mWords.push_back(word);
    }
    
    /**
     *  Clears the listbox
     */
    void clear(){
        mWords.resize(0);
    }
    
    /**
     *  Inherited from ListBoxModel
     *
     *  @param rowNumber     index of the row to be painted
     *  @param g             Juce::Graphics context
     *  @param width         row width
     *  @param height        row height
     *  @param rowIsSelected true if row is currently selected
     */
    void paintListBoxItem(int rowNumber, Graphics &g, int width, int height, bool rowIsSelected) override {
        if (rowIsSelected){
            g.setColour(Colours::blue);
            g.fillAll();
            g.setColour(Colours::white);
        }
        else{
            g.setColour(Colours::white);
            g.fillAll();
            g.setColour(Colours::black);
        }
        
        g.setFont(0.8f * height);
        Rectangle<int> textBox = Rectangle<int>(0, 0, width, height);
        g.drawText(mWords[rowNumber], textBox, Justification::centred);
    }
    
    /**
     *  Inherited from component
     */
    void resized() override {
        mListBox->setBounds(getLocalBounds());
    }
    
    /**
     *  Gets the number of rows in the listbox
     *
     *  @return the number of rows
     */
    int getNumRows() override {
        return mWords.size();
    }
    
    
protected:
    ScopedPointer<ListBox> mListBox;
    vector<String> mWords;
};



#endif  // SUGGESTBOX_H_INCLUDED
