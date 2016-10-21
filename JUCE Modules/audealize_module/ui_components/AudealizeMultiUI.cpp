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

#include "AudealizeMultiUI.h"

AudealizeMultiUI::AudealizeMultiUI (AudioProcessor& p, vector<AudealizeUI*> AudealizeUIs)
    : AudioProcessorEditor (&p),
      mAudealizeUIs (AudealizeUIs),
      mShadow (DropShadow (Colours::black.withAlpha (0.6f), 10, Point<int> (0, 3)))
{
    // load properties, set dark mode accordingly
    properties = Properties::loadPropertiesVar ();

    var darkMode = Properties::getProperty ("darkmode");

    if (darkMode.isBool ())
    {
        if ((bool) darkMode)
        {
            LookAndFeel::setDefaultLookAndFeel (&mLookAndFeelDark);
        }
        else
        {
            LookAndFeel::setDefaultLookAndFeel (&mLookAndFeel);
        }
    }
    else
    {
        LookAndFeel::setDefaultLookAndFeel (&mLookAndFeelDark);
    }

    mToolTip.setMillisecondsBeforeTipAppears (.25);

    // TabbedComponent
    addAndMakeVisible (mTabbedComponent = new AudealizeTabbedComponent (TabbedButtonBar::TabsAtTop));
    mTabbedComponent->setTabBarDepth (28);
    mTabbedComponent->addTab (TRANS ("EQ"), getLookAndFeel ().findColour (AudealizeTabbedComponent::backgroundColourId),
                              mAudealizeUIs[0], true);
    mTabbedComponent->addTab (TRANS ("Reverb"),
                              getLookAndFeel ().findColour (AudealizeTabbedComponent::backgroundColourId),
                              mAudealizeUIs[1], true);
    mTabbedComponent->setCurrentTabIndex (0);
    mTabbedComponent->setOutline (0);

    // tab bypass buttons
    for (int i = 0; i < mAudealizeUIs.size (); ++i)
    {
        mTabBypassButtons.push_back (new BypassButton ());
        mTabbedComponent->getTabbedButtonBar ().getTabButton (i)->setExtraComponent (
            mTabBypassButtons[i], TabBarButton::ExtraComponentPlacement::beforeText);
        mTabBypassButtons[i]->addListener (this);
        mTabBypassButtons[i]->setToggleState (false, sendNotification);

        mAudealizeUIs[i]->getBypassButton ()->addListener (this);
    }

    // Audealize Label
    addAndMakeVisible (label = new Label ("new label", TRANS ("Audealize\n")));
    label->setFont (Font ("Roboto", 34, Font::plain));
    label->setJustificationType (Justification::centredLeft);
    label->setEditable (false, false, false);
    label->setColour (TextEditor::textColourId, getLookAndFeel ().findColour (AudealizeMultiUI::textColourId));
    label->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    // dark mode button
    mDarkModeGraphic =
        Drawable::createFromImageData (AudealizeImages::darkModeButton_svg, AudealizeImages::darkModeButton_svgSize);

    addAndMakeVisible (mDarkModeButton =
                           new DrawableButton ("Dark", DrawableButton::ButtonStyle::ImageOnButtonBackground));
    mDarkModeButton->setTooltip ("Dark/Light theme");

    // set dark mode button graphic based on state
    if (static_cast<AudealizeLookAndFeel&> (getLookAndFeel ()).isDarkModeActive ())
    {
        mDarkModeGraphic->replaceColour (Colour (0xff606060), Colour (0xffbbbbbb));
    }
    mDarkModeButton->setImages (mDarkModeGraphic, mDarkModeGraphic, mDarkModeGraphic, mDarkModeGraphic,
                                mDarkModeGraphic, mDarkModeGraphic, mDarkModeGraphic, mDarkModeGraphic);

    mDarkModeButton->addListener (this);

    // info button
    addAndMakeVisible (mInfoButton = new TextButton ("About"));
    mInfoButton->addListener (this);
    mInfoButton->setAlpha (.9);

    // about dialog window
    addChildComponent (mAboutComponent = new AboutComponent ());
    mShadow.setOwner (mAboutComponent);

    // reziser corner
    mResizeLimits = new ComponentBoundsConstrainer ();
    mResizeLimits->setSizeLimits (MIN_WIDTH, MIN_HEIGHT, MAX_WIDTH, MAX_HEIGHT);
    addAndMakeVisible (mResizer = new ResizableCornerComponent (this, mResizeLimits));
    mResizer->setAlwaysOnTop (true);

    var windowHeight = Properties::getProperty (Properties::propertyIds::windowHeight);
    var windowWidth = Properties::getProperty (Properties::propertyIds::windowWidth);
    setSize (windowWidth, windowHeight);

    // post-resize

    prevChildHeight = mAudealizeUIs[0]->getHeight ();

    for (int i = 0; i < mAudealizeUIs.size (); i++)
    {
        mAudealizeUIs[i]->addActionListener (this);
    }

    // make each map searchable by other maps
    for (int i = 0; i < mAudealizeUIs.size (); i++)
    {
        vector<String> effectNames;  // a vector of the names of the other effects
        vector<StringArray>
            otherMapDescriptors;  // a vector of StringArrays containing the descriptors from the other maps

        for (int j = 0; j < mAudealizeUIs.size (); j++)
        {
            if (j != i)
            {
                effectNames.push_back (mAudealizeUIs[j]->getEffectName ());
                otherMapDescriptors.push_back (mAudealizeUIs[j]->getSearchBar ()->getDescriptors ());
            }
        }

        if (effectNames.size () > 0 && otherMapDescriptors.size () > 0)
        {
            mAudealizeUIs[i]->getSearchBar ()->setMultiEffect (effectNames, otherMapDescriptors);
        }
    }
}

AudealizeMultiUI::~AudealizeMultiUI ()
{
    Properties::setProperty (Properties::propertyIds::windowHeight, std::min (getHeight (), MIN_HEIGHT));
    Properties::setProperty (Properties::propertyIds::windowWidth, std::min (getWidth (), MIN_WIDTH));

    for (auto au : mAudealizeUIs)
    {
        au = nullptr;
    }

    mTabbedComponent = nullptr;
    label = nullptr;
    mInfoButton = nullptr;
    mAboutComponent = nullptr;
    mDarkModeButton = nullptr;
    mDarkModeGraphic = nullptr;
}

void AudealizeMultiUI::paint (Graphics& g)
{
    g.fillAll (getLookAndFeel ().findColour (AudealizeMultiUI::backgroundColourId));

    g.setColour (getLookAndFeel ().findColour (AudealizeMultiUI::accentColourId));
    g.fillRect (24, 48, getWidth () - 48, 34);

    g.setColour (getLookAndFeel ().findColour (AudealizeMultiUI::outlineColourId));
    g.drawRect (24, 48, getWidth () - 48, 34, 1);
}

void AudealizeMultiUI::resized ()
{
    mResizer->setBounds (getWidth () - 18, getHeight () - 18, 16, 16);

    mDarkModeButton->setBounds (getWidth () - 102, 12, 24, 24);

    mInfoButton->setBounds (getWidth () - 72, 12, 48, 24);

    mTabbedComponent->setBounds (0, 54, getWidth () - 0, getHeight () - 54);
    label->setBounds (22, 10, 179, 32);

    mAboutComponent->setCentrePosition (getWidth () * .5f, getHeight () * .5f);

    prevChildHeight = mAudealizeUIs[0]->getHeight ();
}

void AudealizeMultiUI::childrenChanged ()
{
}

void AudealizeMultiUI::actionListenerCallback (const juce::String& message)
{
    int childIndex = mTabbedComponent->getCurrentTabIndex ();

    if (message == "TradUI_TRUE")
    {  // Traditional UI set to visible
        mResizeLimits->setSizeLimits (
            600, 500 + 120 + 10, 1180,
            800 + 120 + 10);  // window size limits depend on whether or not the traditional UI is visible

        // show all traditional UIs (prevents window size issues)
        for (int i = 0; i < mAudealizeUIs.size (); i++)
        {
            if (i != childIndex && !mAudealizeUIs[i]->isTraditionalUIVisible ())
            {
                mAudealizeUIs[i]->getTraditionalUIButton ()->triggerClick ();
            }
        }
    }
    else if (message == "TradUI_FALSE")
    {
        mResizeLimits->setSizeLimits (
            600, 500, 1180, 800);  // window size limits depend on whether or not the traditional UI is visible

        // hide all traditional UIs (prevents window size issues)
        for (int i = 0; i < mAudealizeUIs.size (); i++)
        {
            if (i != childIndex && mAudealizeUIs[i]->isTraditionalUIVisible ())
            {
                mAudealizeUIs[i]->getTraditionalUIButton ()->triggerClick ();
            }
        }
    }
    else if (message.startsWith ("Enabled"))
    {
        for (int i = 0; i < mAudealizeUIs.size (); i++)
        {
            if (message.contains (mAudealizeUIs[i]->getEffectName ()))
            {
                mTabBypassButtons[i]->setToggleState (true, sendNotification);
            }
        }
    }
    setBounds (getX (), getY (), getWidth (), getHeight () + mAudealizeUIs[childIndex]->getHeight () - prevChildHeight);
    prevChildHeight = mAudealizeUIs[childIndex]->getHeight ();
}

void AudealizeMultiUI::buttonClicked (juce::Button* buttonThatWasClicked)
{
    if (buttonThatWasClicked == mInfoButton)
    {
        mAboutComponent->setVisible (true);
    }
    else if (buttonThatWasClicked == mDarkModeButton)
    {
        bool isDark = static_cast<AudealizeLookAndFeel&> (getLookAndFeel ()).isDarkModeActive ();
        if (isDark)
        {
            setLookAndFeel (&mLookAndFeel);
            mDarkModeGraphic->replaceColour (Colour (0xffbbbbbb), Colour (0xff606060));

            mDarkModeButton->setImages (mDarkModeGraphic, mDarkModeGraphic, mDarkModeGraphic, mDarkModeGraphic,
                                        mDarkModeGraphic, mDarkModeGraphic, mDarkModeGraphic, mDarkModeGraphic);
        }
        else
        {
            setLookAndFeel (&mLookAndFeelDark);
            mDarkModeGraphic->replaceColour (Colour (0xff606060), Colour (0xffbbbbbb));

            mDarkModeButton->setImages (mDarkModeGraphic, mDarkModeGraphic, mDarkModeGraphic, mDarkModeGraphic,
                                        mDarkModeGraphic, mDarkModeGraphic, mDarkModeGraphic, mDarkModeGraphic);
        }

        Properties::setProperty (Properties::propertyIds::darkMode, !isDark);
    }

    for (int i = 0; i < mTabBypassButtons.size (); ++i)
    {
        if (mAudealizeUIs[i]->getBypassButton ()->getToggleState () !=
            mTabBypassButtons[i]->getToggleState ())  // do nothing if toggle states match, prevent infinite loop
        {
            if (buttonThatWasClicked == mTabBypassButtons[i])
            {
                mAudealizeUIs[i]->setEnabled (mTabBypassButtons[i]->getToggleState ());
            }
            else if (buttonThatWasClicked == mAudealizeUIs[i]->getBypassButton ())
            {
                mTabBypassButtons[i]->setToggleState (mAudealizeUIs[i]->getBypassButton ()->getToggleState (),
                                                      sendNotification);
            }
        }
    }
}

void AudealizeMultiUI::lookAndFeelChanged ()
{
    mAboutComponent->setLookAndFeel (&getLookAndFeel ());
    mToolTip.setLookAndFeel (&getLookAndFeel ());
    for (auto b : mTabBypassButtons)
    {
        b->setLookAndFeel (&getLookAndFeel ());
    }
}

void AudealizeMultiUI::mouseDown (const MouseEvent& event)
{
    if (mAboutComponent->isVisible () && !mAboutComponent->getBounds ().contains (event.getPosition ()))
    {
        mAboutComponent->setVisible (false);
    }
}
