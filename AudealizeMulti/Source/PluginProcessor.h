/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#ifndef PLUGINPROCESSOR_H_INCLUDED
#define PLUGINPROCESSOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

using std::vector;
using namespace Audealize;

//==============================================================================
/**
*/
class AudealizeMultiAudioProcessor : public AudealizeAudioProcessor
{
public:
    //==============================================================================
    AudealizeMultiAudioProcessor ();
    ~AudealizeMultiAudioProcessor ();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources () override;

#ifndef JucePlugin_PreferredChannelConfigurations
    bool setPreferredBusArrangement (bool isInput, int bus, const AudioChannelSet& preferredSet) override;
#endif

    void processBlock (AudioSampleBuffer&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor () override;
    bool hasEditor () const override;

    //==============================================================================
    const String getName () const override;

    bool acceptsMidi () const override;
    bool producesMidi () const override;
    double getTailLengthSeconds () const override;

    //==============================================================================
    int getNumPrograms () override;
    int getCurrentProgram () override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    void parameterChanged (const juce::String& parameterID, float newValue) override {}
    void settingsFromMap (vector<float> settings) override {}
    inline String getParamID (int index) override { return ""; }
    bool isParameterAutomatable (int index) { return true; }
private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudealizeMultiAudioProcessor)

    ScopedPointer<AudealizeeqAudioProcessor> mEQAudioProcessor;
    ScopedPointer<AudealizereverbAudioProcessor> mReverbAudioProcessor;
};

#endif  // PLUGINPROCESSOR_H_INCLUDED
