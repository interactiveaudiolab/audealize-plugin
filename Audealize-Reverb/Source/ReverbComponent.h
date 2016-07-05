#ifndef REVERBCOMPONENT_H
#define REVERBCOMPONENT_H

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "../../common/AudealizeAudioProcessor.h"
#include "../../common/ui_components/TraditionalUIComponent.h"

namespace Audealize{
    
    class ReverbComponent : public TraditionalUI
    {
    public:
        ReverbComponent (AudealizeAudioProcessor& p);
        ~ReverbComponent();
        
        void paint (Graphics& g) override;
        void resized() override;
        
    private:        
        //==============================================================================
        ScopedPointer<Slider> mSliderD, mSliderG, mSliderM, mSliderF, mSliderE;
        
        ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> mSliderAttachmentD, mSliderAttachmentG, mSliderAttachmentM, mSliderAttachmentF, mSliderAttachmentE;
        
        ScopedPointer<Label> mLabelD, mLabelG, mLabelM, mLabelF, mLabelE;
        
        //==============================================================================
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ReverbComponent)
    };
    
}

#endif