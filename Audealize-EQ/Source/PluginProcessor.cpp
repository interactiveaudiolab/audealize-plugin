#include "PluginProcessor.h"
#include "../../common/common.h"

AudealizeeqAudioProcessor::AudealizeeqAudioProcessor() : mEqualizer(mFreqs, 0.0f)
{
    //DBG(std::to_string(getSampleRate()));
    mParamSettings.resize(NUMBANDS, 0);
    
    
    mGainRange = NormalisableRange<float>(-4.30f, 4.30f, 0.001f);
        
    // Create amount parameter
    
    // Create params for each EQ band gain
    for (int i = 0; i < NUMBANDS; i++){
        String paramID = getParamID(i);
        std::string paramName = std::to_string(mFreqs[i]) + " Hz";
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
        mSmoothedVals[i].reset(sampleRate, 0.00019);
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
        float diff = fabs( mEqualizer.getBandGain(i) - mSmoothedVals[i].getTargetValue() );
        if(diff > 0.01f * mSmoothedVals[i].getTargetValue() ){
            String paramID = getParamID(i);
            
            float gain = mSmoothedVals[i].getNextValue();
            mEqualizer.setBandGain(i, gain * mAmount);
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
    ScopedPointer<TraditionalUI> mGraphicEQ = new GraphicEQComponent(*this, NUMBANDS, mGainRange);
    return new AudealizeUI (*this, mGraphicEQ, PATH_TO_POINTS, ""); //@TODO
}

void AudealizeeqAudioProcessor::parameterChanged(const juce::String &parameterID, float newValue){
    //EQ gain slider changed
    
    //DBG("Paramter changed: " << parameterID);
    
    if (parameterID.substring(0, 9).equalsIgnoreCase("paramGain")){
        int idx = parameterID.substring(9).getIntValue();

        mSmoothedVals[idx].setValue(newValue);
    }
    else if (parameterID.equalsIgnoreCase(paramAmount)){
        mAmount = newValue;
        DBG("Amount: " << mAmount);
        float gain;
        for (int i = 0; i < NUMBANDS; i++){
            gain = mParamSettings[i];
            gain = mGainRange.convertFrom0to1(gain);
            gain *= mAmount;
            gain = mGainRange.convertTo0to1(gain);
            
            mState->getParameter(getParamID(i))->setValueNotifyingHost(gain);
        }
    }
}

void AudealizeeqAudioProcessor::settingsFromMap(vector<float> settings){
    mParamSettings = settings;
    normalize(&mParamSettings);
    
    float gain;
    for (int i = 0; i < NUMBANDS; i++){
        //DBG("Settings[i] " << settings[i]);
        gain = mParamSettings[i];
        gain = mGainRange.convertFrom0to1(gain);
        gain *= mAmount;
        gain = mGainRange.convertTo0to1(gain);
        mState->getParameter(getParamID(i))->setValueNotifyingHost(gain);
    }
    //DBG(mEqualizer.getBandGain(10));
}

AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new AudealizeeqAudioProcessor();
}

void AudealizeeqAudioProcessor::normalize(vector<float>* vals){
    float max = *std::max_element(vals->begin(), vals->end());
    float min = *std::min_element(vals->begin(), vals->end());
    for (int i = 0; i < vals->size(); i++){
        (*vals)[i] = ((*vals)[i] - min) / (max - min);
    }
}

inline String AudealizeeqAudioProcessor::getParamID(int index){
    return String("paramGain" + std::to_string(index));
}
