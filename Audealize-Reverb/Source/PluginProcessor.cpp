#include "PluginProcessor.h"
#include "PluginEditor.h"

using namespace Audealize;

String AudealizereverbAudioProcessor::paramD ("CombDelay");
String AudealizereverbAudioProcessor::paramG ("CombGain");
String AudealizereverbAudioProcessor::paramM ("ChannelDelay");
String AudealizereverbAudioProcessor::paramF ("f");
String AudealizereverbAudioProcessor::paramE ("E");
String AudealizereverbAudioProcessor::paramWetDry ("Wet/Dry");

AudealizereverbAudioProcessor::AudealizereverbAudioProcessor() : mReverb()
{
    // Initialize parameters
    mState->createAndAddParameter(paramD, "Delay of comb filters", TRANS ("Delay of comb filters"), NormalisableRange<float>(0.0f, 0.1f, 0.0000001f), 0.0f, nullptr, nullptr);
    mState->createAndAddParameter(paramG, "Gain of comb filters", TRANS ("Gain of comb filters"), NormalisableRange<float>(0.0f, 1.0f, 0.0001f), 0.0f, nullptr, nullptr);
    mState->createAndAddParameter(paramM, "Delay between channels", TRANS ("Delay between channels"), NormalisableRange<float>(0.0f, 0.012f, 0.000001f), 0.0f, nullptr, nullptr);
    mState->createAndAddParameter(paramF, "LP Cutoff", TRANS ("LP Cutoff"), NormalisableRange<float>(0.0f, 22050.0f, 0.1f), 0.0f, nullptr, nullptr);
    mState->createAndAddParameter(paramE, "Effect Gain", TRANS ("Effect Gain"), NormalisableRange<float>(0.0f, 1.0f, 0.0001f), 0.0f, nullptr, nullptr);
    mState->createAndAddParameter(paramWetDry, "Wet/Dry Mix", TRANS ("Wet/Dry Mix"), NormalisableRange<float>(0.0f, 1.0f, 0.0001f), 0.0f, nullptr, nullptr);
    
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
    mReverb.init(mState->getParameter(paramD)->getValue(), mState->getParameter(paramG)->getValue(), mState->getParameter(paramM)->getValue(), mState->getParameter(paramF)->getValue(), mState->getParameter(paramE)->getValue(), sampleRate);
}

void AudealizereverbAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
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

    float* channelData1 = buffer.getWritePointer(0);
    float* channelData2 = buffer.getWritePointer(1);
    
    
    // Process reverb
    mReverb.processStereoBlock(channelData1, channelData2, buffer.getNumSamples());
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
