#ifndef PLUGINPROCESSOR_H_INCLUDED
#define PLUGINPROCESSOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "../../common/common.h"


using namespace Audealize;

class AudealizereverbAudioProcessor  : public AudealizeAudioProcessor
{
public:
    AudealizereverbAudioProcessor();
    ~AudealizereverbAudioProcessor();

    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool setPreferredBusArrangement (bool isInput, int bus, const AudioChannelSet& preferredSet) override;
   #endif

    void processBlock (AudioSampleBuffer&, MidiBuffer&) override;

    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    double getTailLengthSeconds() const override;

    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;
    
    void parameterChanged(const juce::String &parameterID);
    
    static String paramD;
    static String paramG;
    static String paramM;
    static String paramF;
    static String paramE;
    static String paramWetDry;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudealizereverbAudioProcessor)
    
    Audealize::Reverb mReverb;
    
    NormalisableRange<float> mDRange, mGRange, mMRange, mFRange, mERange, mMixRange;
    
    CParamSmooth mDSmoother, mGSmoother, mMSmoother, mFSmoother, mESmoother, mMixSmoother;
    
    const float mDefaultD   = 0.05f;
    const float mDefaultG   = 0.5f;
    const float mDefaultM   = 0.003f;
    const float mDefaultF   = 5500.0f;
    const float mDefaultE   = 1.0f;
    const float mDefaultMix = 0.75f;
    
    void debugParams();
};


#endif  // PLUGINPROCESSOR_H_INCLUDED
