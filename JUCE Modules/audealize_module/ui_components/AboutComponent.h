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

#ifndef __JUCE_HEADER_6F5BC92BB0597534__
#define __JUCE_HEADER_6F5BC92BB0597534__

#include "../JuceLibraryCode/JuceHeader.h"

namespace Audealize
{
/// A component that displays "about" info for Audealize Plugins
class AboutComponent : public Component, public ButtonListener
{
public:
    AboutComponent ();
    ~AboutComponent ();

    enum ColourIds
    {
        backgroundColourId = 0x2000700,
        textColourId = 0x2000701
    };

    void paint (Graphics& g) override;
    void resized () override;
    void buttonClicked (Button* buttonThatWasClicked) override;

    void focusLost (FocusChangeType cause) override
    {
        setVisible (false);
    }

    void mouseDown (const MouseEvent& event) override
    {
        setVisible (false);
    }

private:
    ScopedPointer<Label> mGrantInfoLabel;           // NSF grant information
    ScopedPointer<Label> mCopyrightLabel;           // copyright information
    ScopedPointer<HyperlinkButton> audealizeLink;   // link to audealze.appspot.com
    ScopedPointer<Label> mDescriptionLabel;         // "about" text
    ScopedPointer<Label> mAudealizeLabel;           // Audealize title text
    ScopedPointer<Label> mVersionLabel;             // plugin version string
    ScopedPointer<HyperlinkButton> mLabLinkButton;  // link to the lab website
    ScopedPointer<Drawable> mLogoDrawable;          // Interactive Audio Lab logo graphic

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AboutComponent)
};
}

#endif  // __JUCE_HEADER_6F5BC92BB0597534__
