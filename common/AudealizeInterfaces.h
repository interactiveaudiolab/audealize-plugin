//
//  AudealizeInterfaces.h
//
//  Created by Michael Donovan on 6/15/16.
//
//

#ifndef AudealizeInterfaces_h
#define AudealizeInterfaces_h

#include "../JuceLibraryCode/JuceHeader.h"

using std::vector;

/// Interface class for Audealize plugin AudioProcessors to facilitate communication of state/param data with UI components
class AudealizeAudioProcessor : public AudioProcessor {
public:
    AudealizeAudioProcessor(){
        mUndoManager = new UndoManager();
        mState = new AudioProcessorValueTreeState(*this, mUndoManager);
    };
    
    ~AudealizeAudioProcessor(){
        mState = nullptr;
        mUndoManager = nullptr;
    }
    
    /**
     *  Stores parameter data in a given memory block.
     *
     *  @param destData Memory block in which to store parameter data
     */
    void getStateInformation (MemoryBlock& destData)
    {
        MemoryOutputStream stream(destData, false);
        mState->state.writeToStream (stream);
    }

    /**
     *  Restores parameters from state data saved in a memory block
     *
     *  @param data        Pointer to the memory block
     *  @param sizeInBytes Size of the memory block in bytes
     */
    void setStateInformation (const void* data, int sizeInBytes)
    {
        ValueTree tree = ValueTree::readFromData (data, sizeInBytes);
        if (tree.isValid()) {
            mState->state = tree;
        }
    }
    
    /**
     *  Called by an AudioProcessorEditor to notify AudioProcessor of parameter value changes
     *
     *  @param parameterID The ID of the parameter that was changed
     */
    virtual void parameterChanged(const juce::String &parameterID) {};
    
    virtual void settingsFromMap(vector<float> settings) {};
    
    /**
     *  Returns the AudioProcessorValueTreeState
     *
     *  @return an AudioProcessorValueTreeState
     */
    AudioProcessorValueTreeState& getValueTreeState(){
        return *mState;
    }
    
protected:
    ScopedPointer<AudioProcessorValueTreeState> mState;
    ScopedPointer<UndoManager>                  mUndoManager;
};


class TraditionalUIComponent : public Component{
public:
    TraditionalUIComponent(AudealizeAudioProcessor& p, int numParams) : processor(p), mSliders(numParams), mSliderAttachments(numParams), mListeners(numParams) {};
    
    void setSlider(int index, float newValue){
        mSliders[index]->setValue(newValue);
        //repaint();
    }
    
    virtual void settingsFromMap(vector<float> settings) {};
    
protected:
    AudealizeAudioProcessor& processor;
    
    vector<ScopedPointer<Slider>> mSliders;
    
    vector<ScopedPointer<AudioProcessorValueTreeState::SliderAttachment>> mSliderAttachments;
    
    vector<ScopedPointer<AudioProcessorValueTreeState::Listener>> mListeners;
        
    int mNumParams;
};

#endif /* AudealizeInterfaces_h */
