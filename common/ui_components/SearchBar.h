//
//  SearchBar.h
//
//  A JUCE TextEditor component that includes autocompletion/suggestions
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
        
        void setWords (vector<String> words);
        
        void addWord (string word);
        
        //void paint (Graphics& g) override;
        
        //bool keyPressed (const KeyPress &key) override;
        
        //void addPopupMenuItems (PopupMenu& m, const MouseEvent*) override;
        
        void textEditorTextChanged (TextEditor &editor) override;
        
        void textEditorReturnKeyPressed (TextEditor &editor) override;
        
        void textEditorEscapeKeyPressed (TextEditor &editor) override;
        
        void textEditorFocusLost (TextEditor &editor) override;
        
        void actionListenerCallback(const String &message) override;
        
    protected:
        trie<string> mTrie;
        ScopedPointer<PopupMenu> mPopup;
        String mPrevText;
    };
}



#endif  // SEARCHBAR_H_INCLUDED
