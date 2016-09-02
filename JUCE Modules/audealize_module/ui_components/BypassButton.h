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

#ifndef BypassButton_h
#define BypassButton_h

namespace Audealize
{
/// A toggleable juce::DrawableButton with an on/off glyph graphic
class BypassButton : public DrawableButton
{
public:
    enum ColourIds
    {
        offColourId = 0x2000800,
        onColourId = 0x2000801,
    };

    BypassButton () : DrawableButton ("", ButtonStyle::ImageOnButtonBackground)
    {
        mOffGraphic =
            Drawable::createFromImageData (AudealizeImages::powerButton_svg, AudealizeImages::powerButton_svgSize);
        mOffGraphic->replaceColour (Colour (0xff000000), findColour (offColourId));

        mOnGraphic =
            Drawable::createFromImageData (AudealizeImages::powerButton_svg, AudealizeImages::powerButton_svgSize);
        mOnGraphic->replaceColour (Colour (0xff000000), findColour (onColourId));

        setImages (mOffGraphic, nullptr, nullptr, nullptr, mOnGraphic, nullptr, nullptr, nullptr);

        setEdgeIndent (10);

        setClickingTogglesState (true);

        setSize (30, 30);
    }

    ~BypassButton ()
    {
        mOffGraphic = nullptr;
        mOnGraphic = nullptr;
    }

    void lookAndFeelChanged () override
    {
        mOffGraphic =
            Drawable::createFromImageData (AudealizeImages::powerButton_svg, AudealizeImages::powerButton_svgSize);
        mOffGraphic->replaceColour (Colour (0xff000000), findColour (offColourId));

        mOnGraphic =
            Drawable::createFromImageData (AudealizeImages::powerButton_svg, AudealizeImages::powerButton_svgSize);
        mOnGraphic->replaceColour (Colour (0xff000000), findColour (onColourId));

        setImages (mOffGraphic, nullptr, nullptr, nullptr, mOnGraphic, nullptr, nullptr, nullptr);
    }

    void paintButton (Graphics& g, const bool isMouseOverButton, const bool isButtonDown) override
    {
    }

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BypassButton);

    ScopedPointer<Drawable> mOffGraphic, mOnGraphic;
};
}

#endif /* BypassButton_h */
