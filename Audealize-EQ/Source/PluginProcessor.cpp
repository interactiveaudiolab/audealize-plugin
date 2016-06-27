#include "PluginProcessor.h"
#include "PluginEditor.h"


AudealizeeqAudioProcessor::AudealizeeqAudioProcessor() : mEqualizer(mFreqs, 0.0f)
{
    //DBG(std::to_string(getSampleRate()));
        
    //Create params for each EQ band gain
    for (int i = 0; i < NUMBANDS; i++){
        std::string paramID = "paramGain" + std::to_string(i);
        std::string paramName =  "Gain: " + std::to_string(mFreqs[i]) + " Hz";
        mState->createAndAddParameter(paramID, paramName, TRANS(paramName), mGainRange, mGainRange.snapToLegalValue(0.0f), nullptr, nullptr);
        mState->addParameterListener(TRANS(paramID), this);
    }
    
    mState->state = ValueTree ("Audealize-EQ");
}


AudealizeeqAudioProcessor::~AudealizeeqAudioProcessor()
{

}

const String AudealizeeqAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool AudealizeeqAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool AudealizeeqAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

double AudealizeeqAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int AudealizeeqAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int AudealizeeqAudioProcessor::getCurrentProgram()
{
    return 0;
}

void AudealizeeqAudioProcessor::setCurrentProgram (int index)
{
}

const String AudealizeeqAudioProcessor::getProgramName (int index)
{
    return String();
}

void AudealizeeqAudioProcessor::changeProgramName (int index, const String& newName)
{
}

void AudealizeeqAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    mEqualizer.setSampleRate(sampleRate);
    
    for (int i = 0; i < NUMBANDS; i++){
        mSmoothers[i] = CParamSmooth(0.5f, sampleRate);
    }
}

void AudealizeeqAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool AudealizeeqAudioProcessor::setPreferredBusArrangement (bool isInput, int bus, const AudioChannelSet& preferredSet)
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

void AudealizeeqAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    const int totalNumInputChannels  = getTotalNumInputChannels();
    const int totalNumOutputChannels = getTotalNumOutputChannels();

    const int numSamples = buffer.getNumSamples();
    
    // Parameter smoothing
    for (int i = 0; i < NUMBANDS; i++){
        if(mSmoothers[i].isDirty()){
            String paramID = String("paramGain" + std::to_string(i));
            float gain = mGainRange.snapToLegalValue(mSmoothers[i].process(mGainRange.convertFrom0to1(mState->getParameter(paramID)->getValue())));
            mEqualizer.setBandGain(i, gain);
        }
    }
    
    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        float* channelData = buffer.getWritePointer (channel);
        
        mEqualizer.processBlock(channelData, numSamples, channel);
    }
    
    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    for (int i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear(i, 0, buffer.getNumSamples());
}

bool AudealizeeqAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* AudealizeeqAudioProcessor::createEditor()
{
    return new AudealizeeqAudioProcessorEditor (*this);
}

void AudealizeeqAudioProcessor::parameterChanged(const juce::String &parameterID, float newValue){
    //EQ gain slider changed
    if (parameterID.substring(0, 9).equalsIgnoreCase("paramGain")){
        
        int idx = parameterID.substring(9).getIntValue();
        
        float gain = mGainRange.snapToLegalValue(mSmoothers[idx].process(newValue));
        //DBG("Called parameterChanged(): " << newValue);
        mEqualizer.setBandGain(idx, gain);
    }
    
}

void AudealizeeqAudioProcessor::settingsFromMap(vector<float> settings){
    for (int i = 0; i < NUMBANDS; i++){
        //DBG("Settings[i] " << settings[i]);
        String paramID = String("paramGain" + std::to_string(i));
        mState->getParameter(paramID)->setValueNotifyingHost(mGainRange.convertTo0to1(settings[i]));
    }
    //DBG(mEqualizer.getBandGain(10));
}

AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new AudealizeeqAudioProcessor();
}
