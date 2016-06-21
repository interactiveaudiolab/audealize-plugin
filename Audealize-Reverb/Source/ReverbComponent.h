#ifndef __JUCE_HEADER_F31C8E96463616E__
#define __JUCE_HEADER_F31C8E96463616E__

#include "JuceHeader.h"
#include "PluginProcessor.h"
#include "../../common/AudealizeInterfaces.h"

class ReverbComponent  : public Component,
                         public AudioProcessorValueTreeState::Listener
{
public:
    ReverbComponent (AudealizeAudioProcessor& p);
    ~ReverbComponent();

    void paint (Graphics& g) override;
    void resized() override;

    void parameterChanged(const String &parameterID, float newValue) override;

private:
    AudealizeAudioProcessor& processor;

    //==============================================================================
    ScopedPointer<Slider> mSliderD, mSliderG, mSliderM, mSliderF, mSliderE, mSliderMix;

    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> mSliderAttachmentD, mSliderAttachmentG, mSliderAttachmentM, mSliderAttachmentF, mSliderAttachmentE, mSliderAttachmentMix;
    
    //ScopedPointer<AudioProcessorValueTreeState::Listener> mListenerD;
    //ScopedPointer<AudioProcessorValueTreeState::Listener> mListenerG;
    //ScopedPointer<AudioProcessorValueTreeState::Listener> mListenerM;
    //ScopedPointer<AudioProcessorValueTreeState::Listener> mListenerF;
    //ScopedPointer<AudioProcessorValueTreeState::Listener> mListenerE;
    //ScopedPointer<AudioProcessorValueTreeState::Listener> mListenerMix;
    
    ScopedPointer<Label> mLabelD, mLabelG, mLabelM, mLabelF, mLabelE, mLabelMix;
    
    static String paramD, paramG, paramM, paramF, paramE, paramWetDry;
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ReverbComponent)
};

#endif