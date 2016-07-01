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
        void actionListenerCallback(const String &message) override;
        
    protected:
        trie<string> mTrie;
        ScopedPointer<PopupMenu> mPopup;
    };
}



#endif  // SEARCHBAR_H_INCLUDED
