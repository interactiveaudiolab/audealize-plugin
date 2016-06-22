#include "PluginProcessor.h"
#include "PluginEditor.h"

using namespace Audealize;

String AudealizereverbAudioProcessor::paramD ("paramD");
String AudealizereverbAudioProcessor::paramG ("paramG");
String AudealizereverbAudioProcessor::paramM ("paramM");
String AudealizereverbAudioProcessor::paramF ("paramF");
String AudealizereverbAudioProcessor::paramE ("paramE");
String AudealizereverbAudioProcessor::paramWetDry ("paramWetDry");

AudealizereverbAudioProcessor::AudealizereverbAudioProcessor() : mReverb(), mDSmoother(), mGSmoother(), mMSmoother(), mFSmoother(), mESmoother(), mMixSmoother()
{
    // initialize parameter ranges
    mDRange   = NormalisableRange<float>(0.01f, 0.1f, 0.0001f);
    mGRange   = NormalisableRange<float>(0.01f, 0.7f, 0.0001f);
    mMRange   = NormalisableRange<float>(0.00f, 0.012f, 0.0001f);
    mFRange   = NormalisableRange<float>(20.0f, 20000.0f, 0.1f, 0.25);
    mERange   = NormalisableRange<float>(0.0f, 1.0f, 0.0001f);
    mMixRange = NormalisableRange<float>(0.0f, 1.0f, 0.0001f);
    
    // Initialize parameters
    mState->createAndAddParameter(paramD, "Delay of comb filters", TRANS ("Delay of comb filters"), mDRange, DEFAULT_D, nullptr, nullptr);
    mState->createAndAddParameter(paramG, "Gain of comb filters", TRANS ("Gain of comb filters"), mGRange, DEFAULT_G, nullptr, nullptr);
    mState->createAndAddParameter(paramM, "Delay between channels", TRANS ("Delay between channels"), mMRange, DEFAULT_M, nullptr, nullptr);
    mState->createAndAddParameter(paramF, "LP Cutoff", TRANS ("LP Cutoff"), mFRange, DEFAULT_F, nullptr, nullptr);
    mState->createAndAddParameter(paramE, "Effect Gain", TRANS ("Effect Gain"), mERange, DEFAULT_E, nullptr, nullptr);
    mState->createAndAddParameter(paramWetDry, "Wet/Dry Mix", TRANS ("Wet/Dry Mix"), mMixRange, DEFAULT_MIX, nullptr, nullptr);
    
    // Add Listeners
    mState->addParameterListener(paramD, this);
    mState->addParameterListener(paramG, this);
    mState->addParameterListener(paramM, this);
    mState->addParameterListener(paramF, this);
    mState->addParameterListener(paramE, this);
    mState->addParameterListener(paramWetDry, this);
    
    mState->state = ValueTree ("Audealize-Reverb");
}

AudealizereverbAudioProcessor::~AudealizereverbAudioProcessor()
{
}

const String AudealizereverbAudioProcessor::getName() const
{
    return JucePlugin_Name;
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

void AudealizereverbAudioProcessor::parameterChanged(const juce::String &parameterID, float newValue){    
    if (parameterID == paramD){
        mReverb.set_d(newValue);
    }
    else if (parameterID == paramG){
        mReverb.set_g(newValue);
    }
    else if (parameterID == paramM){
        mReverb.set_m(newValue);
    }
    else if (parameterID == paramF){
        mReverb.set_f(newValue);
    }
    else if (parameterID == paramE){
        mReverb.set_E(newValue);
    }
    else if (parameterID == paramWetDry){
        mReverb.set_wetdry(newValue);
    }
    debugParams();
}

void AudealizereverbAudioProcessor::debugParams(){
    DBG("d: " << mReverb.get_d() << " g: " << mReverb.get_g() << " m: " << mReverb.get_m() << " f: " << mReverb.get_f() << " E: " << mReverb.get_E());
}
