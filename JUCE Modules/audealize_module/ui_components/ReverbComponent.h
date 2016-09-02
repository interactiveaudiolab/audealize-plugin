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

#ifndef REVERBCOMPONENT_H
#define REVERBCOMPONENT_H

#include "RotarySliderCentered.h"

namespace Audealize
{
/// A TraditionalUI component for controlling the Audealize reverberator
class ReverbComponent : public TraditionalUI
{
public:
    ReverbComponent (AudealizeAudioProcessor& p);
    ~ReverbComponent ();

    void paint (Graphics& g) override;
    void resized () override;

private:
    ScopedPointer<AudealizeSlider> mSliderD, mSliderG, mSliderM, mSliderF, mSliderE;

    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> mSliderAttachmentD, mSliderAttachmentG,
        mSliderAttachmentM, mSliderAttachmentF, mSliderAttachmentE;

    ScopedPointer<Label> mLabelD, mLabelG, mLabelM, mLabelF, mLabelE;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ReverbComponent)
};
}

#endif