//
//  PluginProcessor.h
//
//  JUCE AudioProcessor for Audealize reverb plguin
//  Handles the main audio processing for the plugin
//

#ifndef PLUGINPROCESSOR_H_INCLUDED
#define PLUGINPROCESSOR_H_INCLUDED


#include "../JuceLibraryCode/JuceHeader.h"


//==============================================================================
/**
 */
class ReverbPluginProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    ReverbPluginProcessor();
    ~ReverbPluginProcessor();
    
    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;
    
#ifndef JucePlugin_PreferredChannelConfigurations
    bool setPreferredBusArrangement (bool isInput, int bus, const AudioChannelSet& preferredSet) override;
#endif
    
    void processBlock (AudioSampleBuffer&, MidiBuffer&) override;
    
    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;
    
    //==============================================================================
    const String getName() const override;
    
    bool acceptsMidi() const override;
    bool producesMidi() const override;
    double getTailLengthSeconds() const override;
    
    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;
    
    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ReverbPluginProcessor)
    
    ScopedPointer<AudealizereverbAudioProcessor> mAudealizeAudioProcessor;
};


#endif  // PLUGINPROCESSOR_H_INCLUDED

