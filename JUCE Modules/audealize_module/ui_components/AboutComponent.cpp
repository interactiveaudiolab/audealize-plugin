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

#include "AboutComponent.h"

AboutComponent::AboutComponent ()
{
    addAndMakeVisible (
        mGrantInfoLabel = new Label (
            "new label", TRANS ("This work was funded in part by National Science Foundation Grant number IIS-1116384\n"
                                "\n")));
    mGrantInfoLabel->setFont (Font (Font::getDefaultSansSerifFontName (), 11.00f, Font::plain));
    mGrantInfoLabel->setJustificationType (Justification::centredTop);
    mGrantInfoLabel->setEditable (false, false, false);
    mGrantInfoLabel->setColour (TextEditor::textColourId, Colours::black);
    mGrantInfoLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));
    mGrantInfoLabel->setInterceptsMouseClicks (false, false);

    addAndMakeVisible (
        mCopyrightLabel =
            new Label ("new label", CharPointer_UTF8 ("\xc2\xa9 2016 Interactive Audio Lab, Northwestern University\n"
                                                      "\n")));
    mCopyrightLabel->setFont (Font (Font::getDefaultSansSerifFontName (), 11.00f, Font::plain));
    mCopyrightLabel->setJustificationType (Justification::centredTop);
    mCopyrightLabel->setEditable (false, false, false);
    mCopyrightLabel->setColour (TextEditor::textColourId, Colours::black);
    mCopyrightLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));
    mCopyrightLabel->setInterceptsMouseClicks (false, false);

    addAndMakeVisible (
        audealizeLink = new HyperlinkButton (TRANS ("audealize.appspot.com"), URL ("https://audealize.appspot.com")));
    audealizeLink->setTooltip (TRANS ("https://audealize.appspot.com"));
    audealizeLink->setButtonText (TRANS ("audealize.appspot.com"));
    audealizeLink->addListener (this);

    addAndMakeVisible (
        mDescriptionLabel =
            new Label ("Description",
                       TRANS ("Audealize is a new way of looking at audio production tools. Instead of the traditional "
                              "complex interfaces consisting of knobs with hard-to-understand labels, Audealize "
                              "provides a semantic interface. Simply describe the type of sound you\'re looking for in "
                              "the search boxes, or click and drag around the maps to find new effects.\n"
                              "\n"
                              "This work is developed by the Interactive Audio Lab at Northwestern University.")));
    mDescriptionLabel->setFont (Font (Font::getDefaultSansSerifFontName (), 14.00f, Font::plain));
    mDescriptionLabel->setJustificationType (Justification::topLeft);
    mDescriptionLabel->setEditable (false, false, false);
    mDescriptionLabel->setColour (TextEditor::textColourId, Colours::black);
    mDescriptionLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));
    mDescriptionLabel->setInterceptsMouseClicks (false, false);

    addAndMakeVisible (mAudealizeLabel = new Label ("new label", "Audealize"));
    mAudealizeLabel->setFont (Font (Font::getDefaultSansSerifFontName (), 26.00f, Font::bold));
    mAudealizeLabel->setJustificationType (Justification::centredLeft);
    mAudealizeLabel->setEditable (false, false, false);
    mAudealizeLabel->setColour (TextEditor::textColourId, Colours::black);
    mAudealizeLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));
    mAudealizeLabel->setInterceptsMouseClicks (false, false);

    addAndMakeVisible (mVersionLabel = new Label ("new label", " v" + String (ProjectInfo::versionString)));
    mVersionLabel->setFont (Font (Font::getDefaultSansSerifFontName (), 10.00f, Font::plain));
    mVersionLabel->setJustificationType (Justification::bottomLeft);
    mVersionLabel->setEditable (false, false, false);
    mVersionLabel->setInterceptsMouseClicks (false, false);

    addAndMakeVisible (mLabLinkButton = new HyperlinkButton (TRANS ("music.cs.northwestern.edu"),
                                                             URL ("http://music.cs.northwestern.edu")));
    mLabLinkButton->setTooltip (TRANS ("http://music.cs.northwestern.edu"));
    mLabLinkButton->setButtonText (TRANS ("music.cs.northwestern.edu"));
    mLabLinkButton->addListener (this);

    mLogoDrawable = Drawable::createFromImageData (AudealizeImages::iallogo_svg, AudealizeImages::iallogo_svgSize);

    setAlwaysOnTop (true);
    setSize (496, 320);
}

AboutComponent::~AboutComponent ()
{
    mGrantInfoLabel = nullptr;
    mCopyrightLabel = nullptr;
    audealizeLink = nullptr;
    mDescriptionLabel = nullptr;
    mAudealizeLabel = nullptr;
    mVersionLabel = nullptr;
    mLabLinkButton = nullptr;
    mLogoDrawable = nullptr;
}

void AboutComponent::paint (Graphics& g)
{
    g.fillAll (findColour (AboutComponent::backgroundColourId));

    g.setColour (findColour (AboutComponent::textColourId));
    g.fillRect (28, 42, proportionOfWidth (0.3726f), 1);

    g.setColour (Colours::black.withAlpha (0.181f));
    jassert (mLogoDrawable != 0);
    if (mLogoDrawable != 0)
        mLogoDrawable->drawWithin (g, Rectangle<float> (276, 28, 184, 160), RectanglePlacement::stretchToFit, 0.181f);
}

void AboutComponent::resized ()
{
    mGrantInfoLabel->setBounds (proportionOfWidth (0.0484f), 294, proportionOfWidth (0.8972f), 56);
    mCopyrightLabel->setBounds (proportionOfWidth (0.0484f), 275, proportionOfWidth (0.8992f), 22);
    audealizeLink->setBounds (276, 198, 184, 24);
    mDescriptionLabel->setBounds (24, 46, proportionOfWidth (0.4516f), 210);
    mAudealizeLabel->setBounds (24, 16, 150, 24);
    mVersionLabel->setBounds (114, 14, 150, 25);
    mLabLinkButton->setBounds (249, 222, 240, 24);
}

void AboutComponent::buttonClicked (Button* buttonThatWasClicked)
{
    if (buttonThatWasClicked == audealizeLink)
    {
    }
    else if (buttonThatWasClicked == mLabLinkButton)
    {
    }
}