//
//  Reverb.h
//  Created by Michael Donovan on 6/16/16.
//
//  Implements a parametric reverberator as described in this paper:
//  http://music.cs.northwestern.edu/publications/Rafii-Pardo%20-%20A%20Digital%20Reverberator%20Controlled%20through%20Measures%20of%20the%20Reverberation%20-%20NU%20EECS%202009.pdf
//
//  Requires delay.h from the Calf DSP Library, licensed under The GNU Lesser General Public License v2.1
//  https://github.com/calf-studio-gear/calf
//

#ifndef REVERB_H_INCLUDED
#define REVERB_H_INCLUDED

#define ALLPASSGAIN 0.1f
#define MINDELAY 0.01f
#define PI 3.1415926535897f

using dsp::simple_delay;
using std::vector;
using std::to_string;

namespace Audealize{
    
    class Reverb : AudioEffect{
    public:
        Reverb() : mComb(6), mAllpass(2), mDelay(2)
        {
            //Initialize samples to 0
            mSample[0] = mSample[1] = 0;
            mLowpass = NChannelFilter(bq_type_lowpass, 2, f, 1.0f, 0.0f, mSampleRate);
            da = 0.006f + MINDELAY;
        }
        
        ~Reverb() {}
        
        /**
         *  Process a block of mono audio
         *
         *  @param channelData Pointer to a block of samples
         *  @param blockSize   Number of samples in the block
         */
        void processMonoBlock(float* channelData, int blockSize){
            float samp, sampRev, sampDry;
            
            for (int i = 0; i < blockSize; i++){
                sampDry = channelData[i];
                
                // Process sample through comb filter network
                sampRev = processCombs(samp * wet);
                
                // Process allpass filter
                sampRev = mAllpass[0].process_allpass_comb(sampRev, mDelayVal[0] * mSampleRate, ALLPASSGAIN);
                
                // Process lowpass filter
                sampRev = mLowpass.processSample(sampRev, 0);
                
                sampRev *= gain;
                
                // Delay unprocessed signal to match phase shift caused by the delayed comb filters
                samp = wet * mDelay[0].process(sampDry, MINDELAY * mSampleRate);
                
                samp *= gainclean;
                
                // Average clean and filtered samples
                samp = (samp + sampRev) * .5f;
                
                samp *= gainscale;
                
                sampDry *= dry;
                
                // Write processed sample back to the buffer
                channelData[i] = 0.45f * (samp + sampDry);
            }
        }
        
        /**
         *  Process a block of stereo audio
         *
         *  @param channelData1 Block of samples corresponding to channel 1
         *  @param channelData2 Block of samples corresponding to channel 2
         *  @param blockSize    Number of samples in each block
         */
        void processStereoBlock(float* channelData1, float* channelData2, int blockSize){
            float sampL, sampR, sampRevL, sampRevR, sampDryL, sampDryR, sampSum;

            for (int i = 0; i < blockSize; i++){
                sampDryL = channelData1[i];
                sampDryR = channelData2[i];
                
                // Average left and right channels for comb network
                sampSum = sampDryL + sampDryR;
                sampSum *= 0.5f;
                sampSum *= wet;
                // Process sample through comb filter network
                sampRevL = sampRevR = processCombs(sampSum);
                
                // Process allpass filters
                sampRevL = mAllpass[0].process_allpass_comb(sampRevL, mDelayVal[0] * mSampleRate, ALLPASSGAIN);
                
                sampRevR = mAllpass[1].process_allpass_comb(sampRevR, mDelayVal[1] * mSampleRate, ALLPASSGAIN);
                
                // Process lowpass filters
                sampRevL = mLowpass.processSample(sampRevL, 0);
                sampRevR = mLowpass.processSample(sampRevR, 1);
                
                sampRevL *= gain;
                sampRevR *= gain;
                
                // Delay unprocessed signal to match phase shift caused by the delayed comb filters
                sampL = wet * mDelay[0].process(sampDryL, MINDELAY * mSampleRate);
                sampR = wet * mDelay[1].process(sampDryR, MINDELAY * mSampleRate);
                
                sampL *= gainclean;
                sampR *= gainclean;
                
                // Average clean and filtered samples
                sampL = (sampL + sampRevL) * .5f;
                sampR = (sampR + sampRevR) * .5f;

                sampL *= gainscale;
                sampR *= gainscale;
                
                sampDryL *= dry;
                sampDryR *= dry;
                
                // Write processed sample back to the buffer
                channelData1[i] = 0.45f * (sampDryL + sampL);
                channelData2[i] = 0.45f * (sampDryR + sampR);
            }
        }
        
        /**
         *  Set all parameters at once. 
         *  (Intended to be called from JUCE::AudioProcessor::prepareToPlay)
         */
        void init(float d_val, float g_val, float m_val, float f_val, float E_val, float wetdry_val, float sampleRate){
            mSampleRate = sampleRate;
            mLowpass.setSampleRate(sampleRate);
            set_d(d_val);
            set_g(g_val);
            set_m(m_val);
            set_f(f_val);
            set_E(E_val);
            set_wetdry(wetdry_val);
            resetBuffs();
        }
        
        /**
         *  Individual setters for reverberator parameters
         */
        void set_d(float d_val){
            d = d_val;
            calc_rt();
            for (int i = 0; i < 6; i++){
                mCombDelay[i] = prevPrime(d * (15-i)/15.0f * mSampleRate) / mSampleRate;
                mCombGain[i] = powf(.001, mCombDelay[i] / rt);
            }
        }
        
        void set_g(float g_val){
            g = g_val;
            set_d(get_d());
        }
        
        void set_m(float m_val){
            m = m_val;
            mDelayVal[0] = prevPrime((da + m / 2) * mSampleRate) / mSampleRate;
            mDelayVal[1] = prevPrime((da - m / 2) * mSampleRate) / mSampleRate;
        }
        
        void set_f(float f_val){
            f = f_val;
            mLowpass.setFreq(f);
        }
        
        void set_E(float E_val){
            float totalGain, g1;
            E = E_val;
            
            totalGain = E + 1;
            g1 = 1 / totalGain;
            gainclean = cos((1 - g1) * .125f * PI);
            gain = cos(g1 * .375 * PI);
            gainscale = .5 * .8 / (gainclean + gain);
        }
        
        void set_wetdry(float wetdry_val){
            wetdry = wetdry_val;
            wet = cos((1 - wetdry) * .5 * PI);
            dry = cos(wetdry * .5 * PI);
        }
        
        /**
         * Overload AudioEffect::setSampleRate to update any variables dependent on the sample rate
         */
        void setSampleRate(float sampleRate){
            mSampleRate = sampleRate;
            mLowpass.setSampleRate(sampleRate);
            set_m(m);
            set_d(d);
            resetBuffs();
        }
        
        /**
         *  Zero out all buffers
         */
        void resetBuffs(){
            mAllpass[0].reset();
            mAllpass[1].reset();
            for (int i = 0; i < 6; i++){
                mComb[i].reset();
            }
        }
    
        
        /**
         *  Getters for main reverberator parameters
         */
        float get_d(){
            return d;
        }
        
        float get_g(){
            return g;
        }
        
        float get_m(){
            return m;
        }
        
        float get_f(){
            return f;
        }
        
        float get_E(){
            return E;
        }
        
        float get_wetdry(){
            return wetdry;
        }
        
    private:
        /**
         *  The main reverberator parameters
         *
         *  d      = delay fator of first comb filter
         *  g      = gain factor of first comb filter
         *  m      = delay difference between allpass filters
         *  f      = cutoff frequency of lowpass filters
         *  E      = effect gain
         *  wetdry = wet/dry mix
         */
        float d, g, m, f, E, wetdry;
        
        float rt, gainclean, gainscale, gain, wet, dry, da;
        
        float mSample[2], mCombDelay[6], mCombGain[6], mDelayVal[2];
        
        vector<simple_delay<9600, float>> mComb, mAllpass, mDelay;
        
        NChannelFilter mLowpass;

        /**
         *  Processes an audio sample through a network of parallel comb filters
         *
         *  @param sample An audio sample to process
         *
         *  @return A processed audio sample
         */
        float processCombs(float sample){
            float outSample = 0;
            for (int i = 0; i < mComb.size(); i++){
                outSample += mComb[i].process_comb(sample, mCombDelay[i] * mSampleRate, mCombGain[i]);
            }
            return outSample;
        }
        
        inline void calc_rt(){
            rt = d * log(.001) / log(g);
        }
        
        
    };//class Reverb
    
} //namespace Audealize

#endif  // REVERB_H_INCLUDED
