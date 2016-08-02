//
//  AudealizeUI.h
//
//  A JUCE AudioProcessorEditor for Audealize plugins. Creates the entire Audealize UI, containting a WordMap, a TypeaheadPopupMenu, and a TraditionalUI
//

#ifndef __JUCE_HEADER_EB0317DAAAA56B94__
#define __JUCE_HEADER_EB0317DAAAA56B94__

#include <fstream>
#include "WordMap.h"
#include "TypeaheadPopupMenu.h"

using namespace juce;

namespace Audealize{
    class AudealizeUI : public AudioProcessorEditor,
    public TextEditorListener,
    public ActionListener,
    public ActionBroadcaster,
    public ButtonListener
    {
    public:
        //==============================================================================
        AudealizeUI (AudealizeAudioProcessor& p, ScopedPointer<TraditionalUI> t, String pathToPoints, String effectType, bool isPluginMultiEffect = false);
        ~AudealizeUI();
        //==============================================================================
        
        /**
         *  Called when return key is pressed in search bar, selects word on map
         */
        void textEditorReturnKeyPressed(TextEditor &editor) override;
        
        /**
         *  Displays mAlertBox if user tries to select <1 language
         */
        void languageAlert();
        
        /**
         *  Listens for changes broadcast by an ActionBroadcaster
         *  Updates the set of descriptors searched by the search bar when language is changed
         *
         *  @param message  A string containing the message received
         */
        void actionListenerCallback(const String &message) override;
        
        
        void paint (Graphics& g) override;
        
        /**
         *  Called when the plugin window is resized.
         *  This is where the layout of the UI is defined
         */
        void resized() override;
        
        /**
         *  Called when a button is clicked (language selection or traditional UI hide/show)
         *
         *  @param buttonThatWasClicked
         */
        void buttonClicked (Button* buttonThatWasClicked) override;
        
        void lookAndFeelChanged() override;
        void childrenChanged() override;
                
        bool isTraditionalUIVisible(){
            return isTradUIVisible;
        }
        
        TextButton* getTraditionalUIButton(){
            return mTradUIButton;
        }
    
        TraditionalUI* getTraditionalUI(){
            return mTradUI;
        }
        
        TypeaheadEditor* getSearchBar(){
            return mSearchBar;
        }
        
        String getEffectName(){
            return mEffectType;
        }
        
        int getWordMapHeight(){
            return mWordMap->getHeight();
        }
        
        bool isPluginMultiEffect(){
            return isMultiEffect;
        }
        
    private:
        AudealizeAudioProcessor& processor;
        
        String mPathToPoints; // path to .json file containing descriptor data
        
        ScopedPointer<NativeMessageBox> mAlertBox; // alert window, currently used to warn if no languages are selected
        
        ScopedPointer<Audealize::TraditionalUI> mTradUI; // traditional UI for controlling the effect (sliders/knobs/etc)
        
        ScopedPointer<TextButton> mBypassButton;
        
        TooltipWindow mToolTip;
        
        const String TYPEFACE = "Helvetica"; // typeface for all text
        
        ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> mAmountSliderAttachment;
        
        ScopedPointer<ResizableCornerComponent> mResizer; // handles resizing of the plugin window
        ScopedPointer<ComponentBoundsConstrainer> mResizeLimits; // sets size limits for the plugin window
        
        bool isTradUIVisible; // true if traditional UI is visible
        
        bool isMultiEffect;
        
        String mEffectType; 
        
        //==============================================================================
        ScopedPointer<Audealize::WordMap> mWordMap;
        ScopedPointer<Slider> mAmountSlider; // controls the intensity of the effect
        ScopedPointer<Label> mLabelLess;  // label for amount slider
        ScopedPointer<Label> mLabelMore;  // label for amount slider
        ScopedPointer<ToggleButton> mEnglishButton;
        ScopedPointer<ToggleButton> mEspanolButton;
        ScopedPointer<Label> mAudealizeLabel;  // "Audealize" text in top left
        ScopedPointer<Label> mEffectTypeLabel; // text to the right of "Audealize" label. changes to reflect the type of effect
        ScopedPointer<TextButton> mTradUIButton; // button to hide/show traditional ui
        ScopedPointer<TypeaheadEditor> mSearchBar;
        
        //==============================================================================
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudealizeUI)
    };
    
}

#endif   // __JUCE_HEADER_EB0317DAAAA56B94__
