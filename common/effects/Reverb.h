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

using dsp::simple_delay;
using std::vector;

namespace Audealize{

class Reverb : AudioEffect{
public:
    Reverb() : mComb(6), mAllpass(2)
    {
        //Initialize samples to 0
        mSample[0] = mSample[1] = 0;
    }
    
    float processSample(float sample, int channelIdx){
        float sampL, sampR;
        
        mSample[channelIdx] = sample;
        
        sample = mSample[0] + mSample[1];
        sample *= 0.5;
        
        sampL = sampR = processCombs(sample);
        
        //@TODO: Implement allpass + lowpass filters
    }
    
    // Setters for reverberator parameters
    void init(float d_val, float g_val, float m_val, float f_val, float E_val){
        d = d_val;
        g = g_val;
        m = m_val;
        f = f_val;
        E = E_val;
        
        calc_rt();
    }
    
    void set_d(float d_val){
        d = d_val;
        calc_rt();
    }
    
    void set_g(float g_val){
        g = g_val;
        calc_rt();
    }
    
    void set_m(float m_val){
        m = m_val;
        calc_rt();
    }
    
    void set_f(float f_val){
        f = f_val;
        calc_rt();
    }
    
    void set_E(float E_val){
        E = E_val;
        calc_rt();
    }
    
private:
    /*
     d = delay fator of first comb filter
     g = gain factor of first comb filter
     m = delay difference between allpass filters
     f = cutoff frequency of lowpass filters
     E = wet/dry gain
     */
    float d, g, m, f, E;
    
    float rt;
    
    // Most recent sample from each channel
    float mSample[2];
    
    vector<simple_delay<1024, float>> mComb, mAllpass;
    
    void calc_rt(){
        rt = d * log(.001) / log(g);
    }
    
    float processCombs(float sample){
        float outSample = 0;
        for (int i = 0; i < mComb.size(); i++){
            float delay = d * (15 - i) / 15.0f;
            float gain = pow(.001, delay / rt);
            
            delay = prevPrime((int)(delay * mSampleRate)) / mSampleRate;
            
            outSample += mComb[i].process_comb(sample, d * (15-i) / 15.0f, gain);
        }
        
        return outSample;
    }
    

    
};//class Reverb

} //namespace Audealize

#endif  // REVERB_H_INCLUDED
