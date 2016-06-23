#ifndef PLUGINEDITOR_H_INCLUDED
#define PLUGINEDITOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "../../common/common.h"
#include "../../common/ui_components/GraphicEQComponent.h"

//==============================================================================
/**
*/
class AudealizeeqAudioProcessorEditor  : public AudioProcessorEditor
{
public:
    AudealizeeqAudioProcessorEditor (AudealizeeqAudioProcessor&);
    ~AudealizeeqAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
        
private:
    const String PATH_TO_POINTS = "/Users/michael/JUCE/projects/audealize-plugin/common/data/eqpoints.json"; //@TODO
    
    AudealizeeqAudioProcessor& processor;
    
    ScopedPointer<GraphicEQComponent> mEqualizerComponent;
    ScopedPointer<AudealizeUI> mAudealizeUI;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudealizeeqAudioProcessorEditor)
    
    ScopedPointer<Slider> mGainSliders[NUMBANDS];
    
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> mGainSliderAttachment[NUMBANDS];
    ScopedPointer<AudioProcessorValueTreeState::Listener> mGainListener[NUMBANDS];
};


#endif  // PLUGINEDITOR_H_INCLUDED
