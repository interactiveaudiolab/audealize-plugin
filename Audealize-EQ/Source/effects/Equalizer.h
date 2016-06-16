//
//  Equalizer.h
//  Created by Michael Donovan on 6/13/16.
//
//  An N-band graphic equalizer 
//

#ifndef Equalizer_h
#define Equalizer_h

#include <vector>
#include "NChannelFilter.h"

using std::vector;

class Equalizer{
public:
    Equalizer(vector<float> freqs, float sampleRate) : mFilters(freqs.size()), mFreqs(freqs.size(), 0.0f), mGains(freqs.size(), 0.0f)
    {
        mQ = 4.31f;
        mChannels = 2;
        mNumBands = freqs.size();
        mSampleRate = sampleRate;
        setFreqs(freqs);
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
        float in = sample;
        for (int i = 0; i < mFilters.size(); i++){
            in = mFilters[i].processSample(in, channelIdx);
        }
        
        return in;
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
            samples[i] = processSample(samples[i], channelIdx);
        }
    }
    
    /**
     *  Sets the frequencies and gains of the eq bands
     *
     *  @param freqs    Vector of floats containing band frequencies
     *  @param gains    Vector of floats containing band gains
     */
    void setEqualizer(vector<float> freqs, vector<float> gains){
        setFreqs(freqs);
        setGains(gains);
    }
    
    /**
     *  Sets the frequencies of the EQ bands
     *
     *  @param freqs    Vector of floats containing the new eq band frequencies
     */
    void setFreqs(vector<float> freqs){
        if (mFilters.size() != freqs.size()){
            mNumBands = freqs.size();
            mFilters.resize(mNumBands);
            mFreqs.resize(mNumBands);
        }
        
        for (int i = 0; i < mNumBands; i++){
            mFreqs[i] = freqs[i];
            
            mFilters[i].setNumChannels(mChannels);
            mFilters[i].setFilter(bq_type_peak, freqs[i], mQ, mGains[i], mSampleRate);
        }
    }
    
    /**
     *  Sets the gains of the EQ bands
     *
     *  @param gains Vector of floats containing band gains in dB
     */
    void setGains(vector<float> gains){
        mGains = gains;
        for (int i = 0; i < mNumBands; i++){
            setBandGain(i, gains[i]);
        }
    }
    
    /**
     *  Sets the gain of an individual EQ band
     *
     *  @param bandIdx Band index
     *  @param gainDB  Band gain in dB
     */
    void setBandGain(int bandIdx, float gainDB){
        mFilters[bandIdx].setGain(gainDB);
    }
    
    /**
     *  Sets the Q values of the filters
     *
     *  @param Q Q
     */
    void setQ(float Q){
        mQ = Q;
        setEqualizer(mFreqs, mGains);
    }
    
    /**
     *  Sets the sample rate of the filters
     *
     *  @param sampleRate Sample Rate
     */
    void setSampleRate(float sampleRate){
        mSampleRate = sampleRate;
        setFreqs(mFreqs);
        setGains(mGains);
    }
    
    float getBandFreq(int bandIdx){
        return mFreqs[bandIdx];
    }
    
    float getSampleRate(){
        return mSampleRate;
    }
    
    float getNumChannels(){
        return mChannels;
    }
    
private:
    vector<NChannelFilter> mFilters;
    vector<float> mFreqs, mGains;
    float mSampleRate;
    int mChannels, mNumBands;
    float mQ;
};

#endif /* Equalizer_h */
