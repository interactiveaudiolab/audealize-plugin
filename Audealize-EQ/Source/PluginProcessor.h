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

#ifndef PLUGINPROCESSOR_H_INCLUDED
#define PLUGINPROCESSOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

using namespace Audealize;

//==============================================================================
/**
*/
class EQPluginProcessor : public AudealizeAudioProcessor
{
public:
    //==============================================================================
    EQPluginProcessor ();
    ~EQPluginProcessor ();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources () override;

#ifndef JucePlugin_PreferredChannelConfigurations
    bool setPreferredBusArrangement (bool isInput, int bus, const AudioChannelSet& preferredSet) override;
#endif

    void processBlock (AudioSampleBuffer&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor () override;
    bool hasEditor () const override;

    //==============================================================================
    const String getName () const override;

    bool acceptsMidi () const override;
    bool producesMidi () const override;
    double getTailLengthSeconds () const override;

    //==============================================================================
    int getNumPrograms () override;
    int getCurrentProgram () override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    void parameterChanged (const juce::String& parameterID, float newValue) override
    {
    }
    void settingsFromMap (vector<float> settings) override
    {
    }
    inline String getParamID (int index) override
    {
        return "";
    }
    bool isParameterAutomatable (int index)
    {
        return true;
    }

private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EQPluginProcessor)

    ScopedPointer<AudealizeeqAudioProcessor> mAudealizeAudioProcessor;
};

#endif  // PLUGINPROCESSOR_H_INCLUDED
