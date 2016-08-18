#include "AudealizeReverbAudioProcessor.h"

using namespace Audealize;

String AudealizereverbAudioProcessor::paramD ("paramD");
String AudealizereverbAudioProcessor::paramG ("paramG");
String AudealizereverbAudioProcessor::paramM ("paramM");
String AudealizereverbAudioProcessor::paramF ("paramF");
String AudealizereverbAudioProcessor::paramE ("paramE");

AudealizereverbAudioProcessor::AudealizereverbAudioProcessor(AudealizeAudioProcessor* owner) : AudealizeAudioProcessor(owner), mReverb()
{
    paramAmountId = "paramAmountReverb";
    
    // initialize parameter ranges
    mParamRange[kParamD]  = NormalisableRange<float>(0.01f, 0.1f, 0.0001f);
    mParamRange[kParamG]  = NormalisableRange<float>(0.01f, 0.96f, 0.0001f);
    mParamRange[kParamM]  = NormalisableRange<float>(-0.012f, 0.012f, 0.00001f);
    mParamRange[kParamF]  = NormalisableRange<float>(20.0f, 20000.0f, 0.1f);
    mParamRange[kParamE]  = NormalisableRange<float>(0.0f, 1.0f, 0.0001f);
    
    // Initialize parameters
    String prefix = (mOwner == this ? "" : "Reverb: ");
    mState->createAndAddParameter(paramD, prefix + "Delay of comb filters", TRANS ("Delay of comb filters"), mParamRange[kParamD], DEFAULT_D, nullptr, nullptr);
    mState->createAndAddParameter(paramG, prefix + "Gain of comb filters", TRANS ("Gain of comb filters"), mParamRange[kParamG], DEFAULT_G, nullptr, nullptr);
    mState->createAndAddParameter(paramM, prefix + "Delay between channels", TRANS ("Delay between channels"), mParamRange[kParamM], DEFAULT_M, nullptr, nullptr);
    mState->createAndAddParameter(paramF, prefix + "LP Cutoff", TRANS ("LP Cutoff"), mParamRange[kParamF], DEFAULT_F, nullptr, nullptr);
    mState->createAndAddParameter(paramE, prefix + "Effect Gain", TRANS ("Effect Gain"), mParamRange[kParamE], DEFAULT_E, nullptr, nullptr);

    mState->createAndAddParameter(paramAmountId, "Reverb: Amount", "Reverb: Amount", NormalisableRange<float>(0.0f, 1.0f), 0.5f, nullptr, nullptr);
    mState->addParameterListener(paramAmountId, this);
    
    // Add Listeners
    for (int i = 0; i < kNumParams - 1; i++){
        mState->addParameterListener(getParamID(i), this);
    }
    
    mState->state = ValueTree ("Audealize_Reverb");
}

AudealizereverbAudioProcessor::~AudealizereverbAudioProcessor()
{
    for (int i = 0; i < kNumParams - 1; i++){
        mState->removeParameterListener(getParamID(i), this);
    }
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
        mSmoothedVals[i].reset(sampleRate, 0.00019);
    }
    
    mSmoothedVals[kParamD].setValue(DEFAULT_D);
    mSmoothedVals[kParamG].setValue(DEFAULT_G);
    mSmoothedVals[kParamM].setValue(DEFAULT_M);
    mSmoothedVals[kParamF].setValue(DEFAULT_F);
    mSmoothedVals[kParamE].setValue(DEFAULT_E);
    mSmoothedVals[kParamAmount].setValue(DEFAULT_MIX);
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
    float diff;
    float paramValue;
    
    diff = fabs (mReverb.get_d() - mSmoothedVals[kParamD].getTargetValue());
    if (diff > 0.01f * mSmoothedVals[kParamD].getTargetValue()){
        mReverb.set_d(mSmoothedVals[kParamD].getNextValue());
    }
    
    diff = fabs (mReverb.get_g() - mSmoothedVals[kParamG].getTargetValue());
    if (diff > 0.01f * mSmoothedVals[kParamG].getTargetValue()){
        mReverb.set_g(mSmoothedVals[kParamG].getNextValue());
    }
    
    diff = fabs (mReverb.get_m() - mSmoothedVals[kParamM].getTargetValue());
    if (diff > 0.01f * mSmoothedVals[kParamM].getTargetValue()){
        mReverb.set_m(mSmoothedVals[kParamM].getNextValue());
    }
    
    diff = fabs (mReverb.get_f() - mSmoothedVals[kParamF].getTargetValue());
    if (diff > 0.01f * mSmoothedVals[kParamF].getTargetValue()){
        mReverb.set_f(mSmoothedVals[kParamF].getNextValue());
    }
    
    diff = fabs (mReverb.get_E() - mSmoothedVals[kParamE].getTargetValue());
    if (diff > 0.01f * mSmoothedVals[kParamE].getTargetValue()){
        mReverb.set_E(mSmoothedVals[kParamE].getNextValue());
    }
    
    diff = fabs (mReverb.get_wetdry() - mSmoothedVals[kParamAmount].getTargetValue());
    if (diff > 0.01f * mSmoothedVals[kParamAmount].getTargetValue()){
        mReverb.set_wetdry(mSmoothedVals[kParamAmount].getNextValue());
    }
    // end parameter smoothing
    
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

AudealizeUI* AudealizereverbAudioProcessor::createEditorForMultiEffect()
{
    ScopedPointer<TraditionalUI> mReverbComponent = new ReverbComponent(*this);
    
    return new AudealizeUI (*this, mReverbComponent, PATH_TO_POINTS, "Reverb", true);
}

AudioProcessorEditor* AudealizereverbAudioProcessor::createEditor()
{
    ScopedPointer<TraditionalUI> mReverbComponent = new ReverbComponent(*this);
    
    return new AudealizeUI (*this, mReverbComponent, PATH_TO_POINTS, "Reverb", false);
}


void AudealizereverbAudioProcessor::parameterChanged(const juce::String &parameterID, float newValue){
    //DBG("param changed :" << parameterID << newValue);
    int idx = getParamIdx(parameterID);
    mSmoothedVals[idx].setValue(newValue);
    //DBG(mSmoothedVals[idx].getTargetValue());
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
            return getParamAmountID();
            
        default:
            break;
    }
}

int AudealizereverbAudioProcessor::getParamIdx(String paramId){
    if (paramId.equalsIgnoreCase(paramD)){
        return kParamD;
    }
    else if (paramId.equalsIgnoreCase(paramG)){
        return kParamG;
    }
    else if (paramId.equalsIgnoreCase(paramM)){
        return kParamM;
    }
    else if (paramId.equalsIgnoreCase(paramF)){
        return kParamF;
    }
    else if (paramId.equalsIgnoreCase(paramE)){
        return kParamE;
    }
    else if (paramId.equalsIgnoreCase(paramAmountId)){
        return kParamAmount;
    }
}

void AudealizereverbAudioProcessor::settingsFromMap(vector<float> settings){
    mParamSettings = settings;
    
    //DBG("Raw: " << settings[0] << " " << settings[1] << " "<< settings[2] << " "<< settings[3] << " "<< settings[4]);
    
    for (int i = 0; i < kNumParams - 1; i++){
        // for some reason the F and M param ranges are [0,1] in the plugin
        mState->getParameter(getParamID(i))->beginChangeGesture();
        mState->getParameter(getParamID(i))->setValueNotifyingHost(mParamRange[i].convertTo0to1((settings[i])));
        mState->getParameter(getParamID(i))->endChangeGesture();
    }
}
