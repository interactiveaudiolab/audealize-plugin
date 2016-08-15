//
//  Equalizer.h
//
//  Implements an N-band graphic equalizer. Construct with a vector of center frequencies and a sample rate.
//  Set individual band gains with Equalizer::setBandGain(), set all band gains with a vector of gain values in dB using Equalizer::setGains()
//
//  Requires AudioEffect.h, NChannelFilter.h
//

#ifndef Equalizer_h
#define Equalizer_h

using std::vector;

namespace Audealize{

class Equalizer : public AudioEffect{
public:    
    Equalizer(vector<float> freqs, float sampleRate) : AudioEffect(sampleRate), mFilters(freqs.size()), mFreqs(freqs.size(), 0.0f), mGains(freqs.size(), 0.0f)
    {
        mQ = 4.31f;
        mChannels = 2;
        mNumBands = freqs.size();
        setFreqs(freqs);
    }
    
    /**
     *  Process a single sample of audio
     *
     *  @param sample     A float audio sample
     *  @param channelIdx Channel index [0, num channels)
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
     *  @param bandIdx Index of band to be set
     *  @param gainDB  Band gain in dB
     */
    void setBandGain(int bandIdx, float gainDB){
        mGains[bandIdx] = gainDB;
        mFilters[bandIdx].setGain(gainDB);
    }
    
    /**
     *  Sets the Q values of the filters
     *
     *  @param Q value
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
    
    /**
     *  returns the center frequency of one of the filters in the bank given its index
     *
     *  @param bandIdx index of the filter
     *
     *  @return the center frequency of the filter
     */
    float getBandFreq(int bandIdx){
        return mFilters[bandIdx].getFreq();
    }
    
    /**
     *  returns the gain of one of the filters in the bank given its index
     *
     *  @param bandIdx - index of the filter
     *
     *  @return the gain of the filter
     */
    float getBandGain(int bandIdx){
        return mFilters[bandIdx].getGain();
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
    int mChannels, mNumBands;
    float mQ;
};

} //namespace Audealize

#endif /* Equalizer_h */
