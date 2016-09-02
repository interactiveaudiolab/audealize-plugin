/*
 Audealize
 
 http://music.cs.northwestern.edu
 http://github.com/interactiveaudiolab/audealize-plugin
 
 Licensed under the GNU GPLv2 <https://opensource.org/licenses/GPL-2.0>
 
 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 2
 of the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#ifndef NChannelFilter_h
#define NChannelFilter_h

using std::vector;

namespace Audealize
{
/// A Biquad filter class for processing N channels of audio
class NChannelFilter : public AudioEffect
{
public:
    enum type
    {
        bq_type_lowpass = 0,
        bq_type_highpass,
        bq_type_bandpass,
        bq_type_notch,
        bq_type_peak,
        bq_type_lowshelf,
        bq_type_highshelf
    };

    NChannelFilter () : filters (1)
    {
        setFilter (bq_type_peak, 1000.0f, 0.707f, 0.0f, 441000.0f);
    }

    NChannelFilter (int type, int numChannels, float Fc, float Q, float gainDB, float sampleRate)
        : filters (numChannels)
    {
        mChannels = numChannels;
        setFilter (type, Fc, Q, gainDB, sampleRate);
    }

    /**
     *  Process a single sample of audio
     *
     *  @param sample     A float audio sample
     *  @param channelIdx Channel index
     *
     *  @return the filtered Sample
     */
    float processSample (float sample, int channelIdx)
    {
        float out = filters[channelIdx].process (sample);
        JUCE_UNDENORMALISE (out);
        return out;
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
    void setFilter (int type, float Fc, float Q, float gainDB, float sampleRate)
    {
        mType = type;
        mFc = Fc;
        mQ = Q;
        mGain = gainDB;
        mSampleRate = sampleRate;

        calc ();
    }

    /**
     *  Sets the center frequency of the filters
     *
     *  @param Fc Center frequency in Hz
     */
    void setFreq (float Fc)
    {
        mFc = Fc;

        calc ();
    }

    /**
     *  Sets the type of the filters
     *  @see NChannelFilter::type
     *
     *  @param type Filter type
     */
    void setType (int type)
    {
        mType = type;

        calc ();
    }

    /**
     *  Sets the filter gain in dB
     *
     *  @param gainDB Filter gain in dB
     */
    void setGain (float gainDB)
    {
        mGain = gainDB;

        calc ();
    }

    /**
     *  Sets the number of audio channels for the filter to process (1=mono, 2=stereo, etc.)
     *
     *  @param numChannels New number of channels
     */
    void setNumChannels (int numChannels)
    {
        mChannels = numChannels;
        filters.resize (numChannels);

        calc ();
    }

    /**
     *  Sets the sample rate of the filter
     *
     *  @param sampleRate Sample rate
     */
    void setSampleRate (float sampleRate)
    {
        mSampleRate = sampleRate;

        calc ();
    }

    int getNumChannels ()
    {
        return mChannels;
    }

    /**
     *  Returns the type of filter as an int
     *  @see NChannelFilter::type
     *
     *  @return filter type
     */
    int getType ()
    {
        return mType;
    }

    /**
     *  Returns the frequency of the filter
     */
    float getFreq ()
    {
        return mFc;
    }

    /**
     *  Returns the gain of the filter in dB
     */
    float getGain ()
    {
        return mGain;
    }

private:
    vector<Biquad> filters;  // vector of the filters
    int mChannels;           // number of audio channels to be processed
    int mType;               // filter type. @see Biquad::bq_types
    float mFc;               // filter cutoff frequency
    float mQ;                // filter Q value
    float mGain;             // filter gain in dB

    /**
     *  Recalculates the filters
     */
    void calc ()
    {
        for (int i = 0; i < filters.size (); i++)
        {
            filters[i].setBiquad (mType, mFc / mSampleRate, mQ, mGain);
        }
    }
};

}  // namespace Audealize

#endif /* NChannelFilter_h */
