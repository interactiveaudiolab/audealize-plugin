//
//  AudealizeInterfaces.h
//
//  Created by Michael Donovan on 6/15/16.
//
//

#ifndef AudealizeInterfaces_h
#define AudealizeInterfaces_h

#include "../JuceLibraryCode/JuceHeader.h"


/// Interface class for Audealize plugin AudioProcessors to facilitate communication of state/param data with UI components
class AudealizeAudioProcessor : public AudioProcessor {
public:
    AudealizeAudioProcessor(){};
    
    void parameterChanged(const juce::String &parameterID);
    
    AudioProcessorValueTreeState& getValueTreeState(){
        return *mState;
    }
    
protected:
    ScopedPointer<AudioProcessorValueTreeState> mState;
    ScopedPointer<UndoManager>                  mUndoManager;
};

#endif /* AudealizeInterfaces_h */
