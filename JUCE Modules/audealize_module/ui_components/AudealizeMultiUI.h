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

#ifndef __JUCE_HEADER_2C6B94272375A9F2__
#define __JUCE_HEADER_2C6B94272375A9F2__

#include "AboutComponent.h"
#include "AudealizeTabbedComponent.h"

#define MIN_WIDTH 600
#define MAX_WIDTH 1180
#define MIN_HEIGHT 500
#define MAX_HEIGHT 800

using std::vector;

namespace Audealize
{
/// An AudioProcessorEditor for Audealize multi effect plugins containing multiple AudealizeUI
class AudealizeMultiUI : public AudioProcessorEditor, public ActionListener, public ButtonListener
{
public:
    enum ColourIds
    {
        backgroundColourId = 0x2000200,
        textColourId = 0x2000201,
        outlineColourId = 0x2000202,
        accentColourId = 0x2000203
    };

    AudealizeMultiUI (AudioProcessor& p, vector<AudealizeUI*> AudealizeUIs);
    ~AudealizeMultiUI ();

    void actionListenerCallback (const juce::String& message) override;

    void paint (Graphics& g) override;
    void resized () override;
    void childrenChanged () override;

    void lookAndFeelChanged () override;

    void buttonClicked (Button* buttonThatWasClicked) override;

    void mouseDown (const MouseEvent& event) override;

private:
    var properties;

    vector<AudealizeUI*> mAudealizeUIs;

    ScopedPointer<ResizableCornerComponent> mResizer;         // handles resizing of the plugin window
    ScopedPointer<ComponentBoundsConstrainer> mResizeLimits;  // sets size limits for the plugin window

    int prevChildHeight;

    TooltipWindow mToolTip;

    ScopedPointer<AudealizeTabbedComponent> mTabbedComponent;
    ScopedPointer<Label> label;

    AudealizeLookAndFeel mLookAndFeel;
    AudealizeLookAndFeelDark mLookAndFeelDark;

    ScopedPointer<AboutComponent> mAboutComponent;
    ScopedPointer<TextButton> mInfoButton;
    DropShadower mShadow;

    ScopedPointer<Drawable> mDarkModeGraphic;
    ScopedPointer<DrawableButton> mDarkModeButton;

    ScopedPointer<Drawable> mPowerButtonGraphic;
    vector<DrawableButton*> mTabBypassButtons;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudealizeMultiUI)
};
}
#endif  // __JUCE_HEADER_2C6B94272375A9F2__
