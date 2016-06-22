#ifndef __JUCE_HEADER_F31C8E96463616E__
#define __JUCE_HEADER_F31C8E96463616E__

#include "JuceHeader.h"
#include "PluginProcessor.h"
#include "../../common/AudealizeInterfaces.h"

class ReverbComponent  : public AudioProcessorEditor,
                         public SliderListener
{
public:
    ReverbComponent (AudealizereverbAudioProcessor& p);
    ~ReverbComponent();

    void paint (Graphics& g) override;
    void resized() override;

    void sliderValueChanged (Slider* sliderThatWasMoved);
    
private:
    AudealizereverbAudioProcessor& processor;

    //==============================================================================
    ScopedPointer<Slider> mSliderD, mSliderG, mSliderM, mSliderF, mSliderE, mSliderMix;

    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> mSliderAttachmentD, mSliderAttachmentG, mSliderAttachmentM, mSliderAttachmentF, mSliderAttachmentE, mSliderAttachmentMix;
    
    ScopedPointer<Label> mLabelD, mLabelG, mLabelM, mLabelF, mLabelE, mLabelMix;
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ReverbComponent)
};

#endif