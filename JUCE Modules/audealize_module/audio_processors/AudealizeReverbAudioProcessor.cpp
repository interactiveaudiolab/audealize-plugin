#include "AudealizeReverbAudioProcessor.h"

using namespace Audealize;

String AudealizereverbAudioProcessor::paramD ("paramD");
String AudealizereverbAudioProcessor::paramG ("paramG");
String AudealizereverbAudioProcessor::paramM ("paramM");
String AudealizereverbAudioProcessor::paramF ("paramF");
String AudealizereverbAudioProcessor::paramE ("paramE");

AudealizereverbAudioProcessor::AudealizereverbAudioProcessor() : mReverb()
{    
    // initialize parameter ranges
    mParamRange[kParamD]  = NormalisableRange<float>(0.01f, 0.1f, 0.0001f);
    mParamRange[kParamG]  = NormalisableRange<float>(0.01f, 0.96f, 0.0001f);
    mParamRange[kParamM]  = NormalisableRange<float>(-0.012f, 0.012f, 0.00001f);
    mParamRange[kParamF]  = NormalisableRange<float>(20.0f, 20000.0f, 0.1f);
    mParamRange[kParamE]  = NormalisableRange<float>(0.0f, 1.0f, 0.0001f);
    
    // Initialize parameters
    mState->createAndAddParameter(paramD, "Delay of comb filters", TRANS ("Delay of comb filters"), mParamRange[kParamD], DEFAULT_D, nullptr, nullptr);
    mState->createAndAddParameter(paramG, "Gain of comb filters", TRANS ("Gain of comb filters"), mParamRange[kParamG], DEFAULT_G, nullptr, nullptr);
    mState->createAndAddParameter(paramM, "Delay between channels", TRANS ("Delay between channels"), mParamRange[kParamM], DEFAULT_M, nullptr, nullptr);
    mState->createAndAddParameter(paramF, "LP Cutoff", TRANS ("LP Cutoff"), mParamRange[kParamF], DEFAULT_F, nullptr, nullptr);
    mState->createAndAddParameter(paramE, "Effect Gain", TRANS ("Effect Gain"), mParamRange[kParamE], DEFAULT_E, nullptr, nullptr);

    // Add Listeners
    mState->addParameterListener(paramD, this);
    mState->addParameterListener(paramG, this);
    mState->addParameterListener(paramM, this);
    mState->addParameterListener(paramF, this);
    mState->addParameterListener(paramE, this);
    mState->addParameterListener(paramAmount, this);
    
    mState->state = ValueTree ("Audealize_Reverb");
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

void AudealizereverbAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Initialize reverberator
    mReverb.init(mParamRange[kParamD].snapToLegalValue(DEFAULT_D),
                 mParamRange[kParamG].snapToLegalValue(DEFAULT_G),
                 mParamRange[kParamM].snapToLegalValue(DEFAULT_M),
                 mParamRange[kParamF].snapToLegalValue(DEFAULT_F),
                 mParamRange[kParamE].snapToLegalValue(DEFAULT_E),
                 mParamRange[kParamAmount].snapToLegalValue(DEFAULT_MIX),
                 sampleRate);
    //debugParams();
    
    // Initialize parameter smoothers
    for (int i = 0; i < kNumParams; i++){
        if (i == kParamM)
            // Channel delay requires a slower smoothing time to avoid artifacts
            mSmoother[i].init(3.0f, sampleRate);
        else
            mSmoother[i].init(0.001f, sampleRate);
    }
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
    
    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (int i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // Parameter smoothing
    float paramValue;
    if (mSmoother[kParamG].isDirty()){
        paramValue = mState->getParameter(paramG)->getValue();
        mReverb.set_g(mSmoother[kParamG].process(mParamRange[kParamG].convertFrom0to1(paramValue)));
       
    }
    if (mSmoother[kParamM].isDirty()){
        paramValue = mState->getParameter(paramM)->getValue();
        mReverb.set_m(mSmoother[kParamM].process(mParamRange[kParamM].convertFrom0to1(paramValue)));
    }
    if (mSmoother[kParamF].isDirty()){
        paramValue = mState->getParameter(paramF)->getValue();
        mReverb.set_f(mParamRange[kParamF].snapToLegalValue(mParamRange[kParamF].convertFrom0to1(mSmoother[kParamF].process(paramValue))));
    }
    if (mSmoother[kParamE].isDirty()){
        paramValue = mState->getParameter(paramE)->getValue();
        mReverb.set_E(mParamRange[kParamE].snapToLegalValue(mSmoother[kParamE].process(paramValue)));
    }
    if (mSmoother[kParamAmount].isDirty()){
        paramValue = mState->getParameter(paramAmount)->getValue();
        mReverb.set_wetdry(mParamRange[kParamAmount].snapToLegalValue(mSmoother[kParamAmount].process(paramValue)));
    }
        
    // Process reverb
    if (!mBypass){
        if (totalNumInputChannels == 1){
            float* channelData = buffer.getWritePointer(0);
            mReverb.processMonoBlock(channelData, buffer.getNumSamples());
        }
        else{
            float* channelData1 = buffer.getWritePointer(0);
            float* channelData2 = buffer.getWritePointer(1);
            
            mReverb.processStereoBlock(channelData1, channelData2, buffer.getNumSamples());
        }
    }
}

bool AudealizereverbAudioProcessor::hasEditor() const
{
    return true; 
}

AudealizeUI* AudealizereverbAudioProcessor::createEditor(bool isPluginMultiEffect)
{
    ScopedPointer<TraditionalUI> mReverbComponent = new ReverbComponent(*this);
    
    return new AudealizeUI (*this, mReverbComponent, PATH_TO_POINTS, "Reverb", isPluginMultiEffect);
}


void AudealizereverbAudioProcessor::parameterChanged(const juce::String &parameterID, float newValue){    
    if (parameterID == paramD){
        //mReverb.set_d(mParamRange[kParamD].snapToLegalValue(mSmoother[kParamD].process(newValue)));
        
        // Changing d will create artifacts no matter what, smoothing the value just exacerbates the issue
        mReverb.set_d(mParamRange[kParamD].snapToLegalValue(newValue));
    }
    else if (parameterID == paramG){
        mReverb.set_g(mSmoother[kParamG].process(mParamRange[kParamG].convertFrom0to1(newValue)));
    }
    else if (parameterID == paramM){
        mReverb.set_m(mSmoother[kParamM].process(mParamRange[kParamM].convertFrom0to1(newValue)));
    }
    else if (parameterID == paramF){
        mReverb.set_f(mParamRange[kParamF].snapToLegalValue(mParamRange[kParamF].convertFrom0to1(mSmoother[kParamF].process(newValue))));
    }
    else if (parameterID == paramE){
        mReverb.set_E(mSmoother[kParamE].process(newValue)); // E is already in range [0,1]
    }
    else if (parameterID == paramAmount){
        mReverb.set_wetdry(mParamRange[kParamAmount].snapToLegalValue(mSmoother[kParamAmount].process(newValue)));
    }
    //debugParams();
}

void AudealizereverbAudioProcessor::debugParams(){
    DBG("\nREVERB: d: " << mReverb.get_d() << " g: " << mReverb.get_g() << " m: " << mReverb.get_m() << " f: " << mReverb.get_f() << " E: " << mReverb.get_E());
    DBG("PARAMS: d: " << mState->getParameter(paramD)->getValue() << " g: " << mState->getParameter(paramG)->getValue() << " m: " << mState->getParameter(paramM)->getValue() << " f: " << mState->getParameter(paramF)->getValue() << " E: " << mState->getParameter(paramE)->getValue());
    
}

/**
 *  Transaltes a parameter index to its corresponding ID string
 */
String AudealizereverbAudioProcessor::getParamID(int index){
    switch (index) {
        case kParamD:
            return paramD;
        
        case kParamG:
            return paramG;
            
        case kParamM:
            return paramM;
            
        case kParamF:
            return paramF;
            
        case kParamE:
            return paramE;
            
        case kParamAmount:
            return paramAmount;
            
        default:
            break;
    }
}

void AudealizereverbAudioProcessor::settingsFromMap(vector<float> settings){
    mParamSettings = settings;
    
    //DBG("Raw: " << settings[0] << " " << settings[1] << " "<< settings[2] << " "<< settings[3] << " "<< settings[4]);
    
    for (int i = 0; i < kNumParams - 1; i++){
        // for some reason the F and M param ranges are [0,1] in the plugin
        mState->getParameter(getParamID(i))->setValueNotifyingHost(mParamRange[i].convertTo0to1((settings[i])));
    }
}
