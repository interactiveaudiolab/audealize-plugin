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

#ifndef AudioEffect_h
#define AudioEffect_h

namespace Audealize
{
/// Interface class for audio effects that perform processing on samples either individually or in blocks
class AudioEffect
{
public:
    AudioEffect (float sampleRate = 44100)
    {
        mSampleRate = sampleRate;
    }

    virtual ~AudioEffect ()
    {
    }

    /**
     *  Process an individual sample of audio. Should be overriden by child class
     *
     *  @param sample     Sample of audio to process
     *  @param channelIdx Channel index (0 = mono)
     *
     *  @return A sample of processed audio
     */
    virtual float processSample (float sample, int channelIdx)
    {
        return sample;
    }

    /**
     *  Process a block of audio
     *
     *  @param samples    Pointer to an array of audio samples
     *  @param numSamples Number of samples
     *  @param channelIdx Channel index
     */
    virtual void processBlock (float* const samples, int numSamples, int channelIdx)
    {
        for (int i = 0; i < numSamples; i++)
        {
            samples[i] = processSample (samples[i], channelIdx);
        }
    }

    /**
     *  Set the sample rate of the AudioEffect
     *
     *  @param sampleRate
     */
    virtual void setSampleRate (float sampleRate)
    {
        mSampleRate = sampleRate;
    }

    /**
     *  Returns the sample rate of the AudioEffect
     *
     *  @return samplRate
     */
    float getSampleRate ()
    {
        return mSampleRate;
    }

protected:
    float mSampleRate;
};
}

#endif /* AudioEffect_h */
