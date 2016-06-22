#ifndef PLUGINPROCESSOR_H_INCLUDED
#define PLUGINPROCESSOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "../../common/common.h"


using namespace Audealize;

class AudealizereverbAudioProcessor  : public AudioProcessor
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

    //==============================================================================
    const String getName() const override;

    int getNumParameters() override;
    void setParameter (int index, float newValue) override;
    
    bool acceptsMidi() const override;
    bool producesMidi() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;
    
    NormalisableRange<float>* getParamRange(int index);
    
    enum Parameters {
        paramD,
        paramG,
        paramM,
        paramF,
        paramE,
        paramMix,
        numParams
    };
    
    
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudealizereverbAudioProcessor)
    
    Audealize::Reverb mReverb;
    
    NormalisableRange<float> mParamRanges[numParams];
    CParamSmooth mDSmoother, mGSmoother, mMSmoother, mFSmoother, mESmoother, mMixSmoother;
    
    AudioParameterFloat* mParams[numParams];
    
    const float DEFAULT_D   = 0.05f;
    const float DEFAULT_G   = 0.5f;
    const float DEFAULT_M   = 0.003f;
    const float DEFAULT_F   = 5500.0f;
    const float DEFAULT_E   = 1.0f;
    const float DEFAULT_MIX = 0.75f;
    
    void debugParams();
};


#endif  // PLUGINPROCESSOR_H_INCLUDED
