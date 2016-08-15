//
//  AudioEffect.h
//
//  Interface class for Audio effects that perform processing on samples either individually or in blocks
//

#ifndef AudioEffect_h
#define AudioEffect_h

namespace Audealize{

    class AudioEffect{
    public:
        AudioEffect(float sampleRate = 44100){
            mSampleRate = sampleRate;
        }
        
        virtual ~AudioEffect() {}
        
        /**
         *  Process an individual sample of audio. Should be overriden by child class
         *
         *  @param sample     Sample of audio to process
         *  @param channelIdx Channel index (0 = mono)
         *
         *  @return A sample of processed audio
         */
        virtual float processSample(float sample, int channelIdx) { return sample; }
        
        /**
         *  Process a block of audio
         *
         *  @param samples    Pointer to an array of audio samples
         *  @param numSamples Number of samples
         *  @param channelIdx Channel index
         */
        virtual void processBlock(float* const samples, int numSamples, int channelIdx){
            for (int i = 0; i < numSamples; i++){
                samples[i] = processSample(samples[i], channelIdx);
            }
        }
        
        /**
         *  Set the sample rate of the AudioEffect
         *
         *  @param sampleRate
         */
        virtual void setSampleRate(float sampleRate){
            mSampleRate = sampleRate;
        }
        
        float getSampleRate(){
            return mSampleRate;
        }
        
    protected:
        float mSampleRate;
    };
    
} //namespace Audealize


#endif /* AudioEffect_h */
