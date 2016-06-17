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

#include "../common.h"
#include <math.h>

#define ALLPASSGAIN 0.1f
#define MINDELAY 0.01f
#define PI 3.1415926535897f

using dsp::simple_delay;
using std::vector;

namespace Audealize{
    
    class Reverb : AudioEffect{
    public:
        Reverb() : mComb(6), mAllpass(2), mDelay(2)
        {
            //Initialize samples to 0
            mSample[0] = mSample[1] = 0;
            mLowpass1 = NChannelFilter(bq_type_lowpass, 2, f, 1.0f, 0.0f, mSampleRate);
            mLowpass2 = NChannelFilter(bq_type_lowpass, 2, 22050.0f, 1.0f, 0.0f, mSampleRate);
            
            da = 0.006f + MINDELAY;
        }
        
        /**
         *  Process a block of stereo audio samples
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
                
                //Average left and right channels for comb network
                sampSum = sampDryL + sampDryR;
                sampSum *= 0.5f;
                sampSum *= wet;
                
                //Process sample through comb filter network
                sampRevL = sampRevR = processCombs(sampSum);
                
                //Process allpass filters
                sampRevL = mAllpass[0].process_allpass_comb(sampL, mDelayVal[0], ALLPASSGAIN);
                
                sampRevR = mAllpass[1].process_allpass_comb(sampR, mDelayVal[0], ALLPASSGAIN);
                
                //Process lowpass filters
                sampRevL = mLowpass1.processSample(sampL, 0);
                sampRevR = mLowpass1.processSample(sampR, 1);
                
                sampRevL = mLowpass2.processSample(sampL, 0);
                sampRevR = mLowpass2.processSample(sampR, 1);
                
                sampRevL *= gain;
                sampRevR *= gain;
                
                //Delay unprocessed signal to match phase shift caused by the delayed comb filters
                sampL = wet * mDelay[0].process(sampDryL, MINDELAY * mSampleRate);
                sampR = wet * mDelay[1].process(sampDryR, MINDELAY * mSampleRate);
                
                sampL *= gainclean;
                sampR *= gainclean;
                
                sampL = (sampL + sampRevL) * .5f;
                sampR = (sampR + sampRevR) * .5f;

                sampL *= gainscale;
                sampR *= gainscale;
                
                sampDryL *= dry;
                sampDryR *= dry;
                
                channelData1[i] = 0.45f * (sampDryL + sampR);
                channelData2[i] = 0.45f * (sampDryR + sampR);
            }
        }
        
        /**
         *  Set all parameters at once. 
         *  (Intended to be called from JUCE::AudioProcessor::prepareToPlay)
         */
        void init(float d_val, float g_val, float m_val, float f_val, float E_val, float sampleRate){
            mSampleRate = sampleRate;
            mLowpass1.setSampleRate(sampleRate);
            mLowpass2.setSampleRate(sampleRate);
            set_d(d_val);
            set_g(g_val);
            set_m(m_val);
            set_f(f_val);
            set_E(E_val);
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
            calc_rt();
        }
        
        void set_m(float m_val){
            m = m_val;
            mDelayVal[0] = prevPrime((da + m / 2) * mSampleRate) / mSampleRate;
            mDelayVal[1] = prevPrime((da - m / 2) * mSampleRate) / mSampleRate;
        }
        
        void set_f(float f_val){
            f = f_val;
            mLowpass1.setFreq(f);
            mLowpass2.setFreq(f);
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
         *overload AudioEffect::setSampleRate to update any variables dependent on the sample rate
         */
        void setSampleRate(float sampleRate){
            mSampleRate = sampleRate;
            mLowpass1.setSampleRate(sampleRate);
            mLowpass2.setSampleRate(sampleRate);
            set_m(m);
            set_d(d);
        }
        
        
    private:
        /**
         *  The main reverberator parameters
         *
         *  d      = delay fator of first comb filter
         *  g      = gain factor of first comb filter
         *  m      = delay difference between allpass filters
         *  f      = cutoff frequency of lowpass filters
         *  E      = @TODO: what is this?
         *  wetdry = wet/dry mix
         */
        float d, g, m, f, E, wetdry;
        
        float rt, gainclean, gainscale, gain, wet, dry, da;
        
        float mSample[2], mCombDelay[6], mCombGain[6], mDelayVal[2];
        
        vector<simple_delay<4096, float>> mComb, mAllpass, mDelay;
        
        
        NChannelFilter mLowpass1, mLowpass2;
        

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
                outSample += mComb[i].process_comb(sample, mCombDelay[i], mCombGain[i]);
            }
            return outSample;
        }
        
        inline void calc_rt(){
            rt = d * log(.001) / log(g);
        }
        
        
    };//class Reverb
    
} //namespace Audealize

#endif  // REVERB_H_INCLUDED
