#ifndef PLUGINEDITOR_H_INCLUDED
#define PLUGINEDITOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

class AudealizereverbAudioProcessorEditor  : public AudioProcessorEditor
{
public:
    AudealizereverbAudioProcessorEditor (AudealizereverbAudioProcessor&);
    ~AudealizereverbAudioProcessorEditor();

    void paint (Graphics&) override;
    void resized() override;

private:
    AudealizereverbAudioProcessor& processor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudealizereverbAudioProcessorEditor)
};


#endif  // PLUGINEDITOR_H_INCLUDED
