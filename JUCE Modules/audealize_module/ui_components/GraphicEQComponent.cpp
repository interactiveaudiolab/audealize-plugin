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

#include "GraphicEQComponent.h"

using std::vector;
using std::to_string;

namespace Audealize
{
GraphicEQComponent::GraphicEQComponent (AudealizeAudioProcessor& p, int numBands, NormalisableRange<float> gainRange)
    : TraditionalUI (p), mGainSliders (numBands), mGainSliderAttachment (numBands)
{
    mNumBands = numBands;

    name = "graphic EQ";

    for (int i = 0; i < mNumBands; i++)
    {
        String paramID = "paramGain" + to_string (i);

        mGainSliders[i] = new Slider (Slider::LinearVertical, Slider::NoTextBox);
        mGainSliders[i]->addListener (this);
        mGainSliders[i]->setRange (gainRange.getRange ().getStart (), gainRange.getRange ().getEnd ());
        String tooltip = freqToText (mFreqs[i]);
        mGainSliders[i]->setTooltip (tooltip);
        addAndMakeVisible (mGainSliders[i]);

        mGainSliderAttachment[i] =
            new AudioProcessorValueTreeState::SliderAttachment (p.getValueTreeState (), paramID, *mGainSliders[i]);
    }

    setSize (400, 200);
}

GraphicEQComponent::~GraphicEQComponent ()
{
    for (int i = 0; i < mNumBands; i++)
    {
        mGainSliders[i] = nullptr;
        mGainSliderAttachment[i] = nullptr;
        // mGainListener[i] = nullptr;
    }
}

void GraphicEQComponent::paint (Graphics& g)
{
    int midpoint = mGainSliders[0]->getY () + mGainSliders[0]->getHeight () / 2;

    for (int i = 0; i < NUMBANDS - 1; i++)
    {
        int x1 = mGainSliders[i]->getRight ();
        int x2 = mGainSliders[i + 1]->getX ();
        g.setColour (findColour (GraphicEQComponent::tickMarkColourId));
        g.drawLine (x1 - 1, midpoint, x2 + 1, midpoint, 2);
    }
}

void GraphicEQComponent::resized ()
{
    Rectangle<int> box (getLocalBounds ());
    box.setWidth (box.getWidth () / 40.);

    for (int i = 0; i < mNumBands; i++)
    {
        mGainSliders[i]->setBounds (box);
        box.setX (box.getRight ());
    }
}

void GraphicEQComponent::sliderValueChanged (Slider* slider)
{
    for (int i = 0; i < mNumBands; ++i)
    {
        if (mGainSliders[i] == slider)
        {
            mGainSliders[i]->setTooltip (freqToText (mFreqs[i]) + ": " + String (slider->getValue (), 2) + " dB");
            return;
        }
    }
}
}