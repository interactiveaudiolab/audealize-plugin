#ifndef PLUGINEDITOR_H_INCLUDED
#define PLUGINEDITOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "ui_components/GraphicEQComponent.h"


//==============================================================================
/**
*/
class AudealizeeqAudioProcessorEditor  : public AudioProcessorEditor, AudioProcessorValueTreeState::Listener
{
public:
    AudealizeeqAudioProcessorEditor (AudealizeeqAudioProcessor&);
    ~AudealizeeqAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    
    void parameterChanged(const String &parameterID, float newValue) override;
    
private:
    AudealizeeqAudioProcessor& processor;
    
<<<<<<< HEAD
=======
    ScopedPointer<GraphicEQComponent> mEqualizerComponent;
    
>>>>>>> master
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudealizeeqAudioProcessorEditor)
    
    ScopedPointer<Slider> mGainSliders[NUMBANDS];
    
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> mGainSliderAttachment[NUMBANDS];
    ScopedPointer<AudioProcessorValueTreeState::Listener> mGainListener[NUMBANDS];
};


#endif  // PLUGINEDITOR_H_INCLUDED
