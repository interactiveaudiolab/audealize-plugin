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
    ScopedPointer<Slider> mSliderD;
    ScopedPointer<Slider> mSliderG;
    ScopedPointer<Slider> mSliderM;
    ScopedPointer<Slider> mSliderF;
    ScopedPointer<Slider> mSliderE;
    ScopedPointer<Slider> mSliderMix;

    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> mSliderAttachmentD;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> mSliderAttachmentG;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> mSliderAttachmentM;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> mSliderAttachmentF;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> mSliderAttachmentE;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> mSliderAttachmentMix;
    
    //ScopedPointer<AudioProcessorValueTreeState::Listener> mListenerD;
    //ScopedPointer<AudioProcessorValueTreeState::Listener> mListenerG;
    //ScopedPointer<AudioProcessorValueTreeState::Listener> mListenerM;
    //ScopedPointer<AudioProcessorValueTreeState::Listener> mListenerF;
    //ScopedPointer<AudioProcessorValueTreeState::Listener> mListenerE;
    //ScopedPointer<AudioProcessorValueTreeState::Listener> mListenerMix;
    
    static String paramD;
    static String paramG;
    static String paramM;
    static String paramF;
    static String paramE;
    static String paramWetDry;
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ReverbComponent)
};

#endif