//
//  NChannelFilter.h
//  Created by Michael Donovan on 6/13/16.
//
//  A class for managing Biquad filters for use in processing multichannel audio
//

#ifndef NChannelFilter_h
#define NChannelFilter_h

#include <vector>
#include "Biquad.h"

class NChannelFilter
{
public:
    enum type{
        bq_type_lowpass = 0,
        bq_type_highpass,
        bq_type_bandpass,
        bq_type_notch,
        bq_type_peak,
        bq_type_lowshelf,
        bq_type_highshelf
    };
    
    NChannelFilter() : filters(1){
        setFilter(bq_type_peak, 1000.0f, 0.707f, 0.0f, 441000.0f);
    }
    
    NChannelFilter(int type, int numChannels, float Fc, float Q, float gainDB, float sampleRate)
    : filters(numChannels)
    {
        mChannels = numChannels;
        setFilter(type, Fc, Q, gainDB, sampleRate);
    }
    
    /**
     *  Process a single sample of audio
     *
     *  @param sample     A float audio sample
     *  @param channelIdx Channel index
     *
     *  @return the filtered Sample
     */
    float processSample(float sample, int channelIdx){
        return filters[channelIdx].process(sample);
    }
    
    /**
     *  Process a block of audio
     *
     *  @param samples    Pointer to an array of audio samples
     *  @param numSamples Number of samples
     *  @param channelIdx Channel index
     */
    void processBlock(float* const samples, int numSamples, int channelIdx){
        for (int i = 0; i < numSamples; i++){
            float in = samples[i];
            samples[i] = filters[channelIdx].process(in);
        }
    }
    
    /**
     *  Sets the type, center frequency, Q, and gain of the filters
     *
     *  @param type       @see NChannelFilter::type
     *  @param Fc         Center frequency in Hz
     *  @param Q          Q value
     *  @param gainDB     filter gain in dB
     *  @param sampleRate Sample rate
     */
    void setFilter(int type, float Fc, float Q, float gainDB, float sampleRate){
        mType = type;
        mFc = Fc;
        mQ = Q;
        mGain = gainDB;
        mSampleRate = sampleRate;
        
        calc();
    }
    
    /**
     *  Sets the center frequency of the filters
     *
     *  @param Fc Center frequency in Hz
     */
    void setFreq(float Fc){
        mFc = Fc;
        
        calc();
    }
    
    /**
     *  Sets the type of the filters
     *  @see NChannelFilter::type
     *
     *  @param type Filter type
     */
    void setType(int type){
        mType = type;
        
        calc();
    }
    
    /**
     *  Sets the filter gain in dB
     *
     *  @param gainDB Filter gain in dB
     */
    void setGain(float gainDB){
        mGain = gainDB;
         
        calc();
    }
    
    /**
     *  Sets the number of audio channels for the filter to process (1=mono, 2=stereo, etc.)
     *
     *  @param numChannels New number of channels
     */
    void setNumChannels(int numChannels){
        mChannels = numChannels;
        filters.resize(numChannels);
        
        calc();
    }
    
    /**
     *  Sets the sample rate of the filter
     *
     *  @param sampleRate Sample rate
     */
    void setSampleRate(float sampleRate){
        mSampleRate = sampleRate;
        
        calc();
    }
    
    int getNumChannels(){ return mChannels; }
    
    int getType(){ return mType; }
    
    float getFreq(){ return mFc; }
    
    float getGain(){ return mGain; }
    
private:
    std::vector<Biquad> filters;
    int mChannels, mType;
    float mFc, mQ, mGain, mSampleRate;
    
    /**
     *  Recalculates the filters 
     */
    void calc(){
        for (int i = 0; i < filters.size(); i++){
            filters[i].setBiquad(mType, mFc / mSampleRate, mQ, mGain);
        }
    }
};

#endif /* NChannelFilter_h */
