//
//  A JUCE AudioProcessorEditor for Audealize plugins
//

#ifndef __JUCE_HEADER_EB0317DAAAA56B94__
#define __JUCE_HEADER_EB0317DAAAA56B94__

#include <fstream>
#include "WordMap.h"
#include "TypeaheadPopupMenu.h"

using namespace juce;

namespace Audealize{
    class AudealizeUI  : public AudioProcessorEditor,
    public TextEditorListener,
    public ActionListener,
    public SliderListener,
    public ButtonListener
    {
    public:
        //==============================================================================
        AudealizeUI (AudealizeAudioProcessor& p, ScopedPointer<TraditionalUI> t, String pathToPoints, String effectType);
        ~AudealizeUI();
        //==============================================================================
        
        void textEditorReturnKeyPressed(TextEditor &editor) override;
        
        void languageAlert();
        
        void actionListenerCallback(const String &message) override;
        
        
        void paint (Graphics& g) override;
        void resized() override;
        void sliderValueChanged (Slider* sliderThatWasMoved) override;
        void buttonClicked (Button* buttonThatWasClicked) override;
        void lookAndFeelChanged() override;
        void childrenChanged() override;
        
        
        
    private:
        AudealizeAudioProcessor& processor;
        String mPathToPoints;
        
        ScopedPointer<NativeMessageBox> mAlertBox;
        ScopedPointer<Audealize::TraditionalUI> mTradUI;
        const String TYPEFACE = "Helvetica";
        
        ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> mAmountSliderAttachment;
        
        ScopedPointer<ResizableCornerComponent> mResizer;
        ScopedPointer<ComponentBoundsConstrainer> mResizeLimits;
        
        bool isTradUIVisible;
        
        //==============================================================================
        ScopedPointer<Audealize::WordMap> mWordMap;
        ScopedPointer<Slider> mAmountSlider;
        ScopedPointer<Label> label;
        ScopedPointer<Label> label2;
        ScopedPointer<ToggleButton> mEnglishButton;
        ScopedPointer<ToggleButton> mEspanolButton;
        ScopedPointer<Label> mAudealizeLabel;
        ScopedPointer<Label> mEffectTypeLabel;
        ScopedPointer<TextButton> mTradUIButton;
        ScopedPointer<TypeaheadEditor> mSearchBar;
        
        //==============================================================================
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudealizeUI)
    };
    
}

#endif   // __JUCE_HEADER_EB0317DAAAA56B94__
