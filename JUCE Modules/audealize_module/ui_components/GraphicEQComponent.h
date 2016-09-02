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

#ifndef GraphicEQComponent_h
#define GraphicEQComponent_h

#include <sstream>

using std::vector;
using namespace juce;

namespace Audealize
{
/// A TraditionalUI with an N slider graphic EQ interface for Audealize-EQ plugin
class GraphicEQComponent : public TraditionalUI, public SliderListener
{
public:
    enum ColourIds
    {
        tickMarkColourId = 0x2000500
    };

    GraphicEQComponent (AudealizeAudioProcessor& p, int numBands, NormalisableRange<float> gainRange);
    ~GraphicEQComponent ();

    void paint (Graphics& g) override;
    void resized () override;

    void sliderValueChanged (Slider* slider) override;
    void sliderDragStarted (Slider* slider) override
    {
    }

    void sliderDragEnded (Slider* slider) override
    {
    }

private:
    vector<ScopedPointer<Slider> > mGainSliders;  // a vector contianing the gain sliders

    vector<ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> > mGainSliderAttachment;

    int mNumBands;  // number of EQ bands

    std::vector<int> mFreqs = {20,   50,   83,   120,  161,  208,  259,   318,   383,   455,   537,   628,  729,  843,
                               971,  1114, 1273, 1452, 1652, 1875, 2126,  2406,  2719,  3070,  3462,  3901, 4392, 4941,
                               5556, 6244, 7014, 7875, 8839, 9917, 11124, 12474, 13984, 15675, 17566, 19682};

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GraphicEQComponent)
};
}
#endif
