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

#ifndef RotarySliderCentered_h
#define RotarySliderCentered_h

#include "AudealizeSlider.h"

namespace Audealize
{
/// A rotary slider that draws its track fill starting from center
class RotarySliderCentered : public AudealizeSlider
{
public:
    RotarySliderCentered ()
    {
        setSliderStyle (RotaryVerticalDrag);
    }

    ~RotarySliderCentered ()
    {
    }

    void paint (Graphics& g) override
    {
        const float sliderPos = (float) valueToProportionOfLength (getValue ());

        RotaryParameters rotaryParams = getRotaryParameters ();

        Rectangle<int> sRect = getLookAndFeel ()
                                   .getSliderLayout (*this)
                                   .sliderBounds;  // bounds of slider (excluding text box) within component bounds

        static_cast<AudealizeLookAndFeel&> (getLookAndFeel ())
            .drawRotarySliderCentered (g, sRect.getX (), sRect.getY (), sRect.getWidth (), sRect.getHeight (),
                                       sliderPos, rotaryParams.startAngleRadians, rotaryParams.endAngleRadians, *this);
    }

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (RotarySliderCentered);
};
}

#endif /* RotarySliderCentered_h */
