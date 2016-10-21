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

#ifndef AudealizeAudioProcessor_h
#define AudealizeAudioProcessor_h

using std::vector;
using namespace juce;

namespace Audealize
{
/// Interface class for Audealize plugin AudioProcessors to facilitate communication of state/param data with UI
class AudealizeAudioProcessor : public juce::AudioProcessor, public AudioProcessorValueTreeState::Listener
{
public:
    int lastUIWidth, lastUIHeight;

    AudealizeAudioProcessor (AudealizeAudioProcessor* owner = nullptr) : mParamSettings (0)
    {
        if (owner == nullptr)
        {
            mOwner = this;
            mUndoManager = new UndoManager ();
            mState = new AudioProcessorValueTreeState (*this, mUndoManager);
        }
        else
        {
            mOwner = owner;
            mUndoManager = mOwner->getUndoManager ();
            mState = mOwner->getState ();
        }

        paramAmountId = "paramAmount";
        paramBypassId = "paramBypass";

        mAmount = 0.5f;

        lastUIWidth = 840;
        lastUIHeight = 560;
    };

    ~AudealizeAudioProcessor ()
    {
        if (mOwner == this)
        {
            delete mState;
            delete mUndoManager;
        }
    }

    /**
     *  Stores parameter data in a given memory block.
     *
     *  @param destData Memory block in which to store parameter data
     */
    void getStateInformation (MemoryBlock& destData) override
    {
        MemoryOutputStream stream (destData, false);
        mState->state.writeToStream (stream);
    }

    /**
     *  Restores parameters from state data saved in a memory block
     *
     *  @param data        Pointer to the memory block
     *  @param sizeInBytes Size of the memory block in bytes
     */
    void setStateInformation (const void* data, int sizeInBytes) override
    {
        ValueTree tree = ValueTree::readFromData (data, sizeInBytes);
        if (tree.isValid ())
        {
            mState->state = tree;
        }
    }

    /**
     *  Called by an AudioProcessorEditor to notify AudioProcessor of parameter value changes
     *
     *  @param parameterID The ID of the parameter that was changed
     *  @param newValue    The new value for that parameter
     */
    virtual void parameterChanged (const juce::String& parameterID, float newValue) override{};

    /**
     *  Set the states of all parameters with a vector<float>. To be called by a WordMap
     *
     *  @param settings a vector of floats
     */
    virtual void settingsFromMap (vector<float> settings){};

    /**
     *  Returns the AudioProcessorValueTreeState
     *
     *  @return an AudioProcessorValueTreeState
     */
    AudioProcessorValueTreeState& getValueTreeState ()
    {
        return *mState;
    }

    /**
     *  Normalizes a vector of floats
     *
     *  @param vals
     */
    void normalize (vector<float>* vals)
    {
        float max = *std::max_element (vals->begin (), vals->end ());
        float min = *std::min_element (vals->begin (), vals->end ());
        for (int i = 0; i < vals->size (); i++)
        {
            (*vals)[i] = ((*vals)[i] - min) / (max - min);
        }
    }

    /**
     *  Returns a string with the parameter ID of one of the parameters
     *
     *  @param index
     */
    inline virtual String getParamID (int index)
    {
        return "";
    };

    /**
     *  Returns the parameter ID String for the "Amount" parameter. (will be different depending on effect type)
     *  Needed for differentiating between different effect amount controls in multi effect plugins
     */
    inline String getParamAmountID ()
    {
        return paramAmountId;
    }

    inline String getParamBypassId ()
    {
        return paramBypassId;
    }

    /**
     *  Returns true if AudioProcessor is bypassed (not applying its effect)
     */
    bool isEnabled ()
    {
        return mState->getParameter (paramBypassId)->getValue () == 1;
    }

    /**
     *  Returns a pointer to the AudioProcessor's ValueTreeState
     */
    AudioProcessorValueTreeState* getState ()
    {
        return mState;
    }

    /**
     *  Returns the AudioProcessor's UndoManager. Not currently used in Audealize plugins
     */
    UndoManager* getUndoManager ()
    {
        return mUndoManager;
    }

    /**
     *  Returns a pointer to an AudioProcessorParameter, referenced by its index
     */
    AudioProcessorParameter* getParameterPtr (int idx)
    {
        return mState->getParameter (getParamID (idx));
    }

    /**
     *  Returns a pointer to an AudioProcessorParameter, referenced by its ID string
     */
    AudioProcessorParameter* getParameterPtrFromID (String paramID)
    {
        return mState->getParameter (paramID);
    }

    /**
     *  Returns true - all parameters should be flagged meta
     */
    bool isMetaParameter (int parameterIndex) const override
    {
        return true;
    }

protected:
    AudioProcessorValueTreeState* mState;  // and AudioProcessorValueTreeState containing the parameter state
                                           // information
    UndoManager* mUndoManager;

    vector<float> mParamSettings;

    AudealizeAudioProcessor* mOwner;  // The main PluginProcessor of the plugin

    String paramAmountId;
    String paramBypassId;

    float mAmount;  // value in range [0,1]. dictates the amount of the effect to be applied.

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudealizeAudioProcessor);
};
}  // namespace audealize
#endif /* AudealizeInterfaces_h */
