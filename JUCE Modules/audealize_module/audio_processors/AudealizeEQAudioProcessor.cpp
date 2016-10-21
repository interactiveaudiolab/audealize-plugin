/*
 Audealize

 http://music.cs.northwestern.edu
 http://github.com/interactiveaudiolab/audealize-plugin

 Licensed under the GNU GPLv2 <https://opensource.org/licenses/GPL-2.0>

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 2
 of the License, or (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#include "AudealizeeqAudioProcessor.h"

AudealizeeqAudioProcessor::AudealizeeqAudioProcessor (AudealizeAudioProcessor* owner)
    : AudealizeAudioProcessor (owner), mEqualizer (mFreqs, 0.0f)
{
    paramAmountId = "paramAmountEQ";
    paramBypassId = "paramBypassEQ";

    // DBG(std::to_string(getSampleRate()));
    mParamSettings.resize (NUMBANDS, 0);

    mGainRange = NormalisableRange<float> (-4.30f, 4.30f, 0.001f);

    // Create amount parameter

    // Create params for each EQ band gain
    for (int i = 0; i < NUMBANDS; i++)
    {
        String paramID = getParamID (i);
        String paramName = String (mOwner == this ? "" : "EQ: ") + "Gain: " + String (mFreqs[i], 0) + " Hz";
        mState->createAndAddParameter (paramID, paramName, TRANS (paramName), mGainRange,
                                       mGainRange.snapToLegalValue (0.0f), nullptr, nullptr);
        mState->addParameterListener (TRANS (paramID), this);
    }

    mState->createAndAddParameter (paramAmountId, "EQ: Amount", "EQ: Amount", NormalisableRange<float> (0.0f, 1.0f),
                                   0.5f, nullptr, nullptr);
    mState->addParameterListener (paramAmountId, this);
    mState->createAndAddParameter (paramBypassId, "EQ: Bypass", "EQ: Bypass", NormalisableRange<float> (0.f, 1.f, 1.f),
                                   1.f, nullptr, nullptr);
}

AudealizeeqAudioProcessor::~AudealizeeqAudioProcessor ()
{
    for (int i = 0; i < NUMBANDS; i++)
    {
        String paramID = getParamID (i);
        mState->removeParameterListener (TRANS (paramID), this);
    }
}

const String AudealizeeqAudioProcessor::getName () const
{
    return JucePlugin_Name;
}

bool AudealizeeqAudioProcessor::acceptsMidi () const
{
#if JucePlugin_WantsMidiInput
    return true;
#else
    return false;
#endif
}

bool AudealizeeqAudioProcessor::producesMidi () const
{
#if JucePlugin_ProducesMidiOutput
    return true;
#else
    return false;
#endif
}

double AudealizeeqAudioProcessor::getTailLengthSeconds () const
{
    return 0.0;
}

int AudealizeeqAudioProcessor::getNumPrograms ()
{
    return 1;  // NB: some hosts don't cope very well if you tell them there are 0 programs,
               // so this should be at least 1, even if you're not really implementing programs.
}

int AudealizeeqAudioProcessor::getCurrentProgram ()
{
    return 0;
}

void AudealizeeqAudioProcessor::setCurrentProgram (int index)
{
}

const String AudealizeeqAudioProcessor::getProgramName (int index)
{
    return String ();
}

void AudealizeeqAudioProcessor::changeProgramName (int index, const String& newName)
{
}

void AudealizeeqAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    mEqualizer.setSampleRate (sampleRate);

    for (int i = 0; i < NUMBANDS; i++)
    {
        mSmoothedVals[i].reset (sampleRate, 0.00019);
    }
}

void AudealizeeqAudioProcessor::releaseResources ()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool AudealizeeqAudioProcessor::setPreferredBusArrangement (bool isInput, int bus, const AudioChannelSet& preferredSet)
{
    // Reject any bus arrangements that are not compatible with your plugin

    const int numChannels = preferredSet.size ();

#if JucePlugin_IsMidiEffect
    if (numChannels != 0) return false;
#elif JucePlugin_IsSynth
    if (isInput || (numChannels != 1 && numChannels != 2)) return false;
#else
    if (numChannels != 1 && numChannels != 2) return false;

    if (!AudioProcessor::setPreferredBusArrangement (!isInput, bus, preferredSet)) return false;
#endif

    return AudioProcessor::setPreferredBusArrangement (isInput, bus, preferredSet);
}
#endif

void AudealizeeqAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    const int totalNumInputChannels = getTotalNumInputChannels ();
    const int totalNumOutputChannels = getTotalNumOutputChannels ();

    const int numSamples = buffer.getNumSamples ();

    // Parameter smoothing
    // look through filters
    for (int i = 0; i < NUMBANDS; i++)
    {
        float diff = fabs (mEqualizer.getBandGain (i) - mSmoothedVals[i].getTargetValue ());

        // if current value is not within acceptable margin of target value, continue smoothing
        if (diff > 0.01f * mSmoothedVals[i].getTargetValue ())
        {
            String paramID = getParamID (i);

            float gain = mSmoothedVals[i].getNextValue ();
            mEqualizer.setBandGain (i, gain * mAmount);
        }
    }

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...

    if (mState->getParameter (paramBypassId)->getValue () == 1)
    {
        for (int channel = 0; channel < totalNumInputChannels; ++channel)
        {
            float* channelData = buffer.getWritePointer (channel);

            mEqualizer.processBlock (channelData, numSamples, channel);
        }
    }

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    for (int i = totalNumInputChannels; i < totalNumOutputChannels; ++i) buffer.clear (i, 0, buffer.getNumSamples ());
}

bool AudealizeeqAudioProcessor::hasEditor () const
{
    return true;  // (change this to false if you choose to not supply an editor)
}

AudealizeUI* AudealizeeqAudioProcessor::createEditorForMultiEffect ()
{
    ScopedPointer<TraditionalUI> mGraphicEQ = new GraphicEQComponent (*this, NUMBANDS, mGainRange);

    String path_to_points = Properties::getProperty (Properties::propertyIds::eqDataPath);

    if (!File (path_to_points).existsAsFile ())
    {
        path_to_points = DEFAULT_EQ_DATA_PATH;
    }

    return new AudealizeUI (*this, mGraphicEQ, path_to_points, "EQ", true);
}

AudioProcessorEditor* AudealizeeqAudioProcessor::createEditor ()
{
    ScopedPointer<TraditionalUI> mGraphicEQ = new GraphicEQComponent (*this, NUMBANDS, mGainRange);

    String path_to_points = Properties::getProperty (Properties::propertyIds::eqDataPath);

    if (!File (path_to_points).existsAsFile ())
    {
        path_to_points = DEFAULT_EQ_DATA_PATH;
    }

    return new AudealizeUI (*this, mGraphicEQ, path_to_points, "EQ", false);
}

void AudealizeeqAudioProcessor::parameterChanged (const juce::String& parameterID, float newValue)
{
    // EQ gain slider changed

    // DBG("Paramter changed: " << parameterID);

    if (parameterID.substring (0, 9).equalsIgnoreCase ("paramGain"))
    {
        int idx = parameterID.substring (9).getIntValue ();

        mSmoothedVals[idx].setValue (newValue);
    }
    else if (parameterID.equalsIgnoreCase (paramAmountId))
    {
        mAmount = newValue;
        float gain;
        for (int i = 0; i < NUMBANDS; i++)
        {
            gain = mParamSettings[i];
            gain = mGainRange.convertFrom0to1 (gain);
            gain *= mAmount;
            gain = mGainRange.convertTo0to1 (gain);

            mState->getParameter (getParamID (i))->setValueNotifyingHost (gain);
        }
    }
    else if (parameterID.equalsIgnoreCase (getParamBypassId ()))
    {
        mState->getParameter (getParamBypassId ())->beginChangeGesture ();
        mState->getParameter (getParamBypassId ())->setValueNotifyingHost (newValue);
        mState->getParameter (getParamBypassId ())->beginChangeGesture ();
    }
}

void AudealizeeqAudioProcessor::settingsFromMap (vector<float> settings)
{
    mParamSettings = settings;
    normalize (&mParamSettings);

    float gain;
    for (int i = 0; i < NUMBANDS; i++)
    {
        // DBG("Settings[i] " << settings[i]);
        gain = mParamSettings[i];
        gain = mGainRange.convertFrom0to1 (gain);
        gain *= mAmount;
        gain = mGainRange.convertTo0to1 (gain);
        mState->getParameter (getParamID (i))->beginChangeGesture ();
        mState->getParameter (getParamID (i))->setValueNotifyingHost (gain);
        mState->getParameter (getParamID (i))->endChangeGesture ();
    }

    // DBG(mEqualizer.getBandGain(10));
}

inline String AudealizeeqAudioProcessor::getParamID (int index)
{
    return String ("paramGain" + std::to_string (index));
}
