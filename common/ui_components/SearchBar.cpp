/*
  ==============================================================================

    SearchBar.cpp
    Created: 1 Jul 2016 12:49:25pm
    Author:  Michael

  ==============================================================================
*/

#include "SearchBar.h"

using std::vector;
using std::string;

namespace Audealize{
    SearchBar::SearchBar(String name){
        setMultiLine (false);
        setReturnKeyStartsNewLine (false);
        setReadOnly (false);
        setScrollbarsShown (false);
        setCaretVisible (true);
        setSelectAllWhenFocused(true);
        setTextToShowWhenEmpty("Search for a word to apply", Colour (0xff888888));
        setPopupMenuEnabled(false);
        setWantsKeyboardFocus(true);
        
        addListener(this);
        
        mPopup = new PopupMenu();
    }
    
    SearchBar::~SearchBar() {
        mPopup = nullptr;
    };
    
    void SearchBar::addWord(string word){
        mTrie.insert(word);
    }
    
    void SearchBar::setWords(vector<String> words){
        for (int i = 0; i < words.size(); i++){
            mTrie.insert(words[i].toStdString());
        }
    }
    
    void SearchBar::textEditorTextChanged (TextEditor &editor){
        if (getText().length() > 0){
            // if the user deleted a characted, don't show the completion menu
            // otherwise the popupmenu will grab keyboard focus
            if (getText().substring(0, getText().length()-2).equalsIgnoreCase(mPrevText)){
                mPrevText = getText();
                return;
            }
            else {
                mPrevText = getText();
            }
            
            
            vector<const std::basic_string<char> *> completions = mTrie.complete(getText().toStdString());
            
            // don't show the menu if there's only one item and that item is the word in the textbox
            if (completions.size() == 1 && getText().equalsIgnoreCase(completions[0]->c_str())){
                return ;
            }
            
            PopupMenu::dismissAllActiveMenus();
            
            mPopup->clear();
            
            // show no more than 5 completions
            int wordsToShow = std::min((int)completions.size(), 5);
            for (int i = 0; i < wordsToShow; i++){
                mPopup->addItem(i+1, String(*completions[i]));
            }
            
            int result = mPopup->showAt(this);
            grabKeyboardFocus();
            
            if (result > 0){
                setText(completions[result-1]->c_str());
                returnPressed();
                PopupMenu::dismissAllActiveMenus();
            }
        }
    }
    
    void SearchBar::textEditorReturnKeyPressed (TextEditor &editor){

    }
    
    void SearchBar::textEditorEscapeKeyPressed (TextEditor &editor){
        
    }
    
    void SearchBar::textEditorFocusLost (TextEditor &editor){
    }
    
    void SearchBar::actionListenerCallback(const juce::String &message){
        setText(message);
    }
}