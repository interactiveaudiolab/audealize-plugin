//
//  AudealizeInterfaces.h
//
//  Interface class for Audealize plugin AudioProcessors to facilitate communication of state/param data with UI components
//
 
#ifndef AudealizeAudioProcessor_h
#define AudealizeAudioProcessor_h

using std::vector;
using namespace juce;

namespace Audealize{

    class AudealizeAudioProcessor : public juce::AudioProcessor, public AudioProcessorValueTreeState::Listener {
    public:
        int lastUIWidth, lastUIHeight;
        
        
        String paramAmount = "paramAmount";
        
        AudealizeAudioProcessor() : mParamSettings(0){            
            mUndoManager = new UndoManager();
            mState = new AudioProcessorValueTreeState(*this, mUndoManager);
            
            mState->createAndAddParameter(paramAmount, "Amount", "Amount", NormalisableRange<float>(0.0f, 1.0f), 0.5f, nullptr, nullptr);
            mState->addParameterListener(paramAmount, this);

            mAmount = 0.5f;
            
            lastUIWidth = 840;
            lastUIHeight = 560;
            
            mBypass = false;
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
        
        /**
         *  Set the states of all parameters with a vector<float>. To be called by a WordMap
         *
         *  @param settings a vector of floats
         */
        virtual void settingsFromMap(vector<float> settings) {};
        
        /**
         *  Returns the AudioProcessorValueTreeState
         *
         *  @return an AudioProcessorValueTreeState
         */
        AudioProcessorValueTreeState& getValueTreeState(){
            return *mState;
        }
        
        /**
         *  Normalizes a vector of floats
         *
         *  @param vals
         */
        void normalize(vector<float>* vals){
            float max = *std::max_element(vals->begin(), vals->end());
            float min = *std::min_element(vals->begin(), vals->end());
            for (int i = 0; i < vals->size(); i++){
                (*vals)[i] = ((*vals)[i] - min) / (max - min);
            }
        }
        
        /**
         *  Returns a string with the parameter ID of one of the parameters
         *
         *  @param index
         */
        inline virtual String getParamID(int index) {};
        
        void setBypass(bool bypass){
            mBypass = bypass;
        }
        
        bool isBypassed(){
            return mBypass;
        }
        
        
        AudioProcessorValueTreeState* getState(){
            return mState;
        }
        
    protected:
        ScopedPointer<AudioProcessorValueTreeState> mState; // and AudioProcessorValueTreeState containing the parameter state information
        ScopedPointer<UndoManager> mUndoManager;
        
        vector<float> mParamSettings;
        
        bool mBypass;
        
        float mAmount; // value in range [0,1]. dictates the amount of the effect to be applied.
        
    };
}// namespace audealize
#endif /* AudealizeInterfaces_h */
