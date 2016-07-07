//
//  SearchBar.h
//
//  A JUCE TextEditor component that uses a trie to provide autocompletion/suggestions
//

#ifndef SEARCHBAR_H_INCLUDED
#define SEARCHBAR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "../libs/trie/trie.hpp"

using std::vector;
using std::string;

namespace Audealize{
    class SearchBar : public TextEditor, public TextEditorListener, public ActionListener {
    public:
        SearchBar(String name = "");
        
        ~SearchBar();
        
        /**
         *  Set the list of words to be searched
         *
         *  @param words A vector<String> of words
         */
        void setWords (vector<String> words);
        
        /**
         *  Add an individual word to the list of words to be searched
         *
         *  @param word
         */
        void addWord (String word);
        
        /**
         *  Performs a search and displays suggestions when the text of the bar is changed. (inherited from TextEditorListener
         *
         *  @param editor this
         */
        void textEditorTextChanged (TextEditor &editor) override;
        
        /**
         *  To be called by WordMap::wordselected()
         *
         *  @param message
         */
        void actionListenerCallback (const String &message) override;
        
    protected:
        trie<string> mTrie;
        ScopedPointer<PopupMenu> mPopup;
        ScopedPointer<ListBox> mListBox;
        bool changedByMap; //@TODO
    };
    
    class ListItemComponent : public Component{
    public:
        ListItemComponent(){
            isSelected = false;
            addAndMakeVisible(mLabel = new Label());
        }
        
        ~ListItemComponent(){
            mLabel = nullptr;
        }
        
        void setText(String text){
            mLabel->setText(text, NotificationType::sendNotification);
        }
        
        void setSelected(bool selected){
            isSelected = selected;
        }
        
        void paint( Graphics& g) override{
            if (isSelected){
                g.setColour(Colours::blue);
                g.fillAll();
                mLabel->setColour(Label::ColourIds::textColourId, Colours::white);
                mLabel->repaint();
            }
            else{
                g.setColour(Colours::white);
                g.fillAll();
                mLabel->setColour(Label::ColourIds::textColourId, Colours::black);
                mLabel->repaint();
            }
        }
        
        void resized() override{
            mLabel->setBounds(getLocalBounds());
        }
        
    protected:
        ScopedPointer<Label> mLabel;
        bool isSelected;
    };
    
    class SuggestBox : public Component, public ListBoxModel, public KeyListener {
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
         *  Inherited from ListBoxModel
         *
         *  @param rowNumber     index of the row to be painted
         *  @param g             Juce::Graphics context
         *  @param width         row width
         *  @param height        row height
         *  @param rowIsSelected true if row is currently selected
         */
        void paintListBoxItem(int rowNumber, Graphics &g, int width, int height, bool rowIsSelected) override{
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
        void resized(){
            mListBox->setBounds(getLocalBounds());
        }
        
        int getNumRows() {
            return mWords.size();
        }
        
        
    protected:
        ScopedPointer<ListBox> mListBox;
        vector<String> mWords;
    };

}



#endif  // SEARCHBAR_H_INCLUDED
