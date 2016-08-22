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
        
        AudealizeAudioProcessor(AudealizeAudioProcessor* owner = nullptr) : mParamSettings(0){
            if (owner == nullptr){
                mOwner = this;
                mUndoManager = new UndoManager();
                mState = new AudioProcessorValueTreeState(*this, mUndoManager);
            }
            else{
                mOwner = owner;
                mUndoManager = mOwner->getUndoManager();
                mState = mOwner->getState();
            }
            
            paramAmountId = "paramAmount";
            
            mAmount = 0.5f;
            
            lastUIWidth = 840;
            lastUIHeight = 560;
            
            mBypass = false;
        };
        
        ~AudealizeAudioProcessor(){
            if (mOwner == this){
                delete mState;
                delete mUndoManager;
            }
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
         *  @param newValue    The new value for that parameter
         */
        virtual void parameterChanged(const juce::String &parameterID, float newValue) {};
        
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
        inline virtual String getParamID(int index) { return ""; };
        
        inline String getParamAmountID() {
            return paramAmountId;
        }
        
        void setBypass(bool bypass){
            mBypass = bypass;
        }
        
        bool isBypassed(){
            return mBypass;
        }
        
        AudioProcessorValueTreeState* getState(){
            return mState;
        }
        
        UndoManager* getUndoManager(){
            return mUndoManager;
        }
        
        AudioProcessorParameter* getParameterPtr(int idx){
            return mState->getParameter(getParamID(idx));
        }
        
        AudioProcessorParameter* getParameterPtrFromID(String paramID){
            return mState->getParameter(paramID);
        }
        
        bool isMetaParameter(int parameterIndex) const override {
            return true;
        }
        
    protected:
        AudioProcessorValueTreeState* mState; // and AudioProcessorValueTreeState containing the parameter state information
        UndoManager* mUndoManager;
        
        vector<float> mParamSettings;
        
        AudealizeAudioProcessor* mOwner;
        
        bool mBypass;
        
        String paramAmountId;
        
        float mAmount; // value in range [0,1]. dictates the amount of the effect to be applied.
        
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR ( AudealizeAudioProcessor );
    };
}// namespace audealize
#endif /* AudealizeInterfaces_h */
