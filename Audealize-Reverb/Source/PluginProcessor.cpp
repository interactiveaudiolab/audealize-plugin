#include "PluginProcessor.h"
#include "PluginEditor.h"

using namespace Audealize;


AudealizereverbAudioProcessor::AudealizereverbAudioProcessor() : mReverb(), mDSmoother(), mGSmoother(), mMSmoother(), mFSmoother(), mESmoother(), mMixSmoother()
{
    // initialize parameter ranges
    mParamRanges[paramD]   = NormalisableRange<float>(0.01f, 0.1f, 0.0000001f);
    mParamRanges[paramG]   = NormalisableRange<float>(0.01f, 0.7f, 0.0001f);
    mParamRanges[paramM]   = NormalisableRange<float>(0.01f, 0.012f, 0.000001f);
    mParamRanges[paramF]   = NormalisableRange<float>(20.0f, 20000.0f, 0.1f);
    mParamRanges[paramE]   = NormalisableRange<float>(0.0f, 1.0f, 0.0001f);
    mParamRanges[paramMix] = NormalisableRange<float>(0.0f, 1.0f, 0.0001f);


    // Initialize parameters
    addParameter(mParams[paramD] = new AudioParameterFloat("d", "Delay of comb filters", mParamRanges[paramD], DEFAULT_D));
    addParameter(mParams[paramG] = new AudioParameterFloat("g", "Gain of comb filters", mParamRanges[paramG], DEFAULT_G));
    addParameter(mParams[paramM] = new AudioParameterFloat("g", "Gain of comb filters", mParamRanges[paramG], DEFAULT_G));
    addParameter(mParams[paramF] = new AudioParameterFloat("f", "LP Cutoff", mParamRanges[paramF], DEFAULT_F));
    addParameter(mParams[paramE] = new AudioParameterFloat("E", "Effect gain", mParamRanges[paramE], DEFAULT_E));
    addParameter(mParams[paramMix] = new AudioParameterFloat("mix", "Mix", mParamRanges[paramMix], DEFAULT_MIX));
}

AudealizereverbAudioProcessor::~AudealizereverbAudioProcessor()
{

}

const String AudealizereverbAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

int AudealizereverbAudioProcessor::getNumParameters(){
    return numParams;
}

NormalisableRange<float>* getParamRange(int index){
    return *mParamRanges[index];
}

void AudealizereverbAudioProcessor::setParameter (int index, float newValue){
    if (index == paramD){
        mReverb.set_d(*mParams[paramD]);
    }
    else if (index == paramG){
        mReverb.set_g(*mParams[paramG]);
    }
    else if (index == paramM){
        mReverb.set_m(*mParams[paramM]);
    }
    else if (index == paramF){
        mReverb.set_f(*mParams[paramF]);
    }
    else if (index == paramE){
        mReverb.set_E(*mParams[paramE]);
    }
    else if (index == paramMix){
        mReverb.set_wetdry(*mParams[paramMix]);
    }
    debugParams();
}

bool AudealizereverbAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool AudealizereverbAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

double AudealizereverbAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int AudealizereverbAudioProcessor::getNumPrograms()
{
    return 1;
}

int AudealizereverbAudioProcessor::getCurrentProgram()
{
    return 0;
}

void AudealizereverbAudioProcessor::setCurrentProgram (int index)
{
}

const String AudealizereverbAudioProcessor::getProgramName (int index)
{
    return String();
}

void AudealizereverbAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void AudealizereverbAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Initialize reverberator
    mReverb.init(DEFAULT_D, DEFAULT_G, DEFAULT_M, DEFAULT_F, DEFAULT_E, DEFAULT_MIX, sampleRate);
    debugParams();
    
    // Initialize parameter smoothers
    mDSmoother.init(5.0f, sampleRate);
    mGSmoother.init(5.0f, sampleRate);
    mMSmoother.init(5.0f, sampleRate);
    mFSmoother.init(5.0f, sampleRate);
    mESmoother.init(5.0f, sampleRate);
    mMixSmoother.init(5.0f, sampleRate);
}

void AudealizereverbAudioProcessor::releaseResources()
{
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool AudealizereverbAudioProcessor::setPreferredBusArrangement (bool isInput, int bus, const AudioChannelSet& preferredSet)
{
    // Reject any bus arrangements that are not compatible with your plugin

    const int numChannels = preferredSet.size();

   #if JucePlugin_IsMidiEffect
    if (numChannels != 0)
        return false;
   #elif JucePlugin_IsSynth
    if (isInput || (numChannels != 1 && numChannels != 2))
        return false;
   #else
    if (numChannels != 1 && numChannels != 2)
        return false;

    if (! AudioProcessor::setPreferredBusArrangement (! isInput, bus, preferredSet))
        return false;
   #endif

    return AudioProcessor::setPreferredBusArrangement (isInput, bus, preferredSet);
}
#endif

void AudealizereverbAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    const int totalNumInputChannels  = getTotalNumInputChannels();
    const int totalNumOutputChannels = getTotalNumOutputChannels();
    const int numSamples = buffer.getNumSamples();
    
    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (int i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    
    // Process reverb
    if (totalNumInputChannels == 1){
        float* channelData = buffer.getWritePointer(0);
        mReverb.processMonoBlock(channelData, numSamples);
    }
    else{
        float* channelData1 = buffer.getWritePointer(0);
        float* channelData2 = buffer.getWritePointer(1);
        
        mReverb.processStereoBlock(channelData1, channelData2, buffer.getNumSamples());
    }
}

bool AudealizereverbAudioProcessor::hasEditor() const
{
    return true; 
}

AudioProcessorEditor* AudealizereverbAudioProcessor::createEditor()
{
    return new AudealizereverbAudioProcessorEditor (*this);
}

AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new AudealizereverbAudioProcessor();
}

void AudealizereverbAudioProcessor::debugParams(){
    DBG("d: " << mReverb.get_d() << " g: " << mReverb.get_g() << " m: " << mReverb.get_m() << " f: " << mReverb.get_f() << " E: " << mReverb.get_E());
}
