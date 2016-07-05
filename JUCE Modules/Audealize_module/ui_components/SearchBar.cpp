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
        setPopupMenuEnabled(false);
        setWantsKeyboardFocus(true);
        
        addListener(this);
        
        mPopup = new PopupMenu();
        
        changedByMap = false;
    }
    
    SearchBar::~SearchBar() {
        mPopup = nullptr;
    };
    
    void SearchBar::addWord(String word){
        mTrie.insert(word.toStdString());
    }
    
    void SearchBar::setWords(vector<String> words){
        mTrie = trie<string>();
        for (int i = 0; i < words.size(); i++){
            mTrie.insert(words[i].toStdString());
        }
    }
    
    void SearchBar::textEditorTextChanged (TextEditor &editor){
        if (getText().length() > 0 && !changedByMap){
            
            vector<const std::basic_string<char> *> completions = mTrie.complete(getText().toStdString());
            
            // don't show the menu if there's only one item and that item is the word in the textbox
            // or if the word is in the trie
            if ((completions.size() == 1 && getText().equalsIgnoreCase(completions[0]->c_str())) || mTrie.has(getText().toStdString())){
                return ;
            }
            
            // close any open menus
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
    
    void SearchBar::actionListenerCallback(const juce::String &message){
        if(!message.equalsIgnoreCase("_languagechanged")){
            setText(message);
        }
    }
}