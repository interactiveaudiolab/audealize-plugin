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

#include "PluginProcessor.h"

using std::vector;

//==============================================================================
AudealizeMultiAudioProcessor::AudealizeMultiAudioProcessor ()
{
    mEQAudioProcessor = new AudealizeeqAudioProcessor (this);
    mReverbAudioProcessor = new AudealizereverbAudioProcessor (this);
    mState->state = ValueTree (Identifier ("AudealizeMulti"));
}

AudealizeMultiAudioProcessor::~AudealizeMultiAudioProcessor ()
{
    mEQAudioProcessor = nullptr;
    mReverbAudioProcessor = nullptr;
}

//==============================================================================
const String AudealizeMultiAudioProcessor::getName () const
{
    return JucePlugin_Name;
}

bool AudealizeMultiAudioProcessor::acceptsMidi () const
{
#if JucePlugin_WantsMidiInput
    return true;
#else
    return false;
#endif
}

bool AudealizeMultiAudioProcessor::producesMidi () const
{
#if JucePlugin_ProducesMidiOutput
    return true;
#else
    return false;
#endif
}

double AudealizeMultiAudioProcessor::getTailLengthSeconds () const
{
    return 0.0;
}

int AudealizeMultiAudioProcessor::getNumPrograms ()
{
    return 1;  // NB: some hosts don't cope very well if you tell them there are 0 programs,
               // so this should be at least 1, even if you're not really implementing programs.
}

int AudealizeMultiAudioProcessor::getCurrentProgram ()
{
    return 0;
}

void AudealizeMultiAudioProcessor::setCurrentProgram (int index)
{
}

const String AudealizeMultiAudioProcessor::getProgramName (int index)
{
    return String ();
}

void AudealizeMultiAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void AudealizeMultiAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    mEQAudioProcessor->prepareToPlay (sampleRate, samplesPerBlock);
    mReverbAudioProcessor->prepareToPlay (sampleRate, samplesPerBlock);
}

void AudealizeMultiAudioProcessor::releaseResources ()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
    mEQAudioProcessor->releaseResources ();
    mReverbAudioProcessor->releaseResources ();
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool AudealizeMultiAudioProcessor::setPreferredBusArrangement (bool isInput, int bus,
                                                               const AudioChannelSet& preferredSet)
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

    return AudioProcessor::setPreferredBusArrangement (isInput, bus, preferredSet) &&
           mReverbAudioProcessor->setPreferredBusArrangement (isInput, bus, preferredSet) &&
           mEQAudioProcessor->setPreferredBusArrangement (isInput, bus, preferredSet);
}
#endif

void AudealizeMultiAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    const int totalNumInputChannels = getTotalNumInputChannels ();
    const int totalNumOutputChannels = getTotalNumOutputChannels ();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (int i = totalNumInputChannels; i < totalNumOutputChannels; ++i) buffer.clear (i, 0, buffer.getNumSamples ());

    mEQAudioProcessor->processBlock (buffer, midiMessages);
    mReverbAudioProcessor->processBlock (buffer, midiMessages);
}

//==============================================================================
bool AudealizeMultiAudioProcessor::hasEditor () const
{
    return true;  // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* AudealizeMultiAudioProcessor::createEditor ()
{
    vector<AudealizeUI*> audealizeUIs;

    audealizeUIs.push_back (mEQAudioProcessor->createEditorForMultiEffect ());
    audealizeUIs.push_back (mReverbAudioProcessor->createEditorForMultiEffect ());

    return new AudealizeMultiUI (*this, audealizeUIs);
}

//==============================================================================
void AudealizeMultiAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    DBG ("getStateInformation");
    ScopedPointer<XmlElement> xml (mState->state.createXml ());
    DBG (xml->createDocument (""));
    copyXmlToBinary (*xml, destData);
}

void AudealizeMultiAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    DBG ("setStateInformation");

    ScopedPointer<XmlElement> xmlState (getXmlFromBinary (data, sizeInBytes));
    if (xmlState != nullptr)
        if (xmlState->hasTagName (mState->state.getType ())) mState->state = ValueTree::fromXml (*xmlState);
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter ()
{
    return new AudealizeMultiAudioProcessor ();
}
