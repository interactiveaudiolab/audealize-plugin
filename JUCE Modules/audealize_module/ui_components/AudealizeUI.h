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

#ifndef __JUCE_HEADER_EB0317DAAAA56B94__
#define __JUCE_HEADER_EB0317DAAAA56B94__

#include <fstream>
#include "AboutComponent.h"
#include "TypeaheadPopupMenu.h"
#include "WordMap.h"

using namespace juce;

namespace Audealize
{
/// The main UI of an individual Audealize effect.
class AudealizeUI : public AudioProcessorEditor,
                    public TextEditorListener,
                    public ActionListener,
                    public ActionBroadcaster,
                    public ButtonListener
{
public:
    enum ColourIds
    {
        backgroundColourId = 0x2000100,
        textColourId = 0x2000101
    };

    AudealizeUI (AudealizeAudioProcessor& p, ScopedPointer<TraditionalUI> t, String pathToPoints, String effectType,
                 bool isPluginMultiEffect = false);
    ~AudealizeUI ();

    void paint (Graphics& g) override;
    void lookAndFeelChanged () override;
    void childrenChanged () override;

    /**
     *  Called when return key is pressed in search bar, selects word on map
     */
    void textEditorReturnKeyPressed (TextEditor& editor) override;

    /**
     *  Displays mAlertBox if user tries to select <1 language
     */
    void languageAlert ();

    /**
     *  Listens for changes broadcast by an ActionBroadcaster
     *  Updates the set of descriptors searched by the search bar when language is changed
     *
     *  @param message  A string containing the message received
     */
    void actionListenerCallback (const String& message) override;

    /**
     *  Called when the plugin window is resized.
     *  This is where the layout of the UI is defined
     */
    void resized () override;

    /**
     *  Called when a button is clicked (language selection or traditional UI hide/show)
     *
     *  @param buttonThatWasClicked
     */
    void buttonClicked (Button* buttonThatWasClicked) override;

    /**
     *  Set the bypass state of the audio effect. (true = off)
     *
     *  @param isBypassed True = effect off
     */
    void setBypassed (bool isBypassed)
    {
        processor.setBypass (isBypassed);
    }

    /**
     *  Returns true if the effect is currently bypassed
     */
    bool isBypassed ()
    {
        return processor.isBypassed ();
    }

    /**
     *  Returns true if the TraditionalUI is currently visible
     */
    bool isTraditionalUIVisible ()
    {
        return isTradUIVisible;
    }

    /**
     *  Returns a pointer to the TraditionalUI toggle button
     */
    TextButton* getTraditionalUIButton ()
    {
        return mTradUIButton;
    }

    /**
     *  Returns a pointer to the effect bypass button
     */
    TextButton* getBypassButton ()
    {
        return mBypassButton;
    }

    /**
     *  Returns a pointer to the TraditionalUI
     */
    TraditionalUI* getTraditionalUI ()
    {
        return mTradUI;
    }

    /**
     *  Returns a pointer to the TypeaheadEditor search bar
     */
    TypeaheadEditor* getSearchBar ()
    {
        return mSearchBar;
    }

    /**
     *  Returns a pointer to the WordMap
     */
    WordMap* getWordMap ()
    {
        return mWordMap;
    }

    /**
     *  Returns the String name of the effect
     */
    String getEffectName ()
    {
        return mEffectType;
    }

    /**
     *  Returns the current height in pixels of the WordMap
     */
    int getWordMapHeight ()
    {
        return mWordMap->getHeight ();
    }

    /**
     *  Returns true if this AudealizeUI is a member of a multi effect plugin
     */
    bool isPluginMultiEffect ()
    {
        return isMultiEffect;
    }

private:
    AudealizeAudioProcessor& processor;

    var properties;

    String mPathToPoints;  // path to .json file containing descriptor data

    ScopedPointer<NativeMessageBox> mAlertBox;  // alert window, currently used to warn if no languages are selected

    ScopedPointer<Audealize::TraditionalUI> mTradUI;  // traditional UI for controlling the effect (sliders/knobs/etc)

    ScopedPointer<TextButton> mBypassButton;

    TooltipWindow mToolTip;

    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> mAmountSliderAttachment;

    ScopedPointer<ResizableCornerComponent> mResizer;         // handles resizing of the plugin window
    ScopedPointer<ComponentBoundsConstrainer> mResizeLimits;  // sets size limits for the plugin window

    bool isTradUIVisible;  // true if traditional UI is visible

    bool isMultiEffect;

    String mEffectType;

    ScopedPointer<Audealize::WordMap> mWordMap;
    ScopedPointer<Slider> mAmountSlider;  // controls the intensity of the effect
    ScopedPointer<Label> mLabelLess;      // label for amount slider
    ScopedPointer<Label> mLabelMore;      // label for amount slider
    ScopedPointer<ToggleButton> mEnglishButton;
    ScopedPointer<ToggleButton> mEspanolButton;
    ScopedPointer<Label> mAudealizeLabel;     // "Audealize" text in top left
    ScopedPointer<TextButton> mTradUIButton;  // button to hide/show traditional ui
    ScopedPointer<TypeaheadEditor> mSearchBar;
    ScopedPointer<Button> mInfoButton;
    ScopedPointer<AboutComponent> mAboutComponent;

    AudealizeLookAndFeel mLookAndFeel;
    AudealizeLookAndFeelDark mLookAndFeelDark;

    DialogWindow::LaunchOptions mDialogOpts;
    ScopedPointer<DialogWindow> mAboutWindow;

    ScopedPointer<Drawable> mDarkModeGraphic;
    ScopedPointer<DrawableButton> mDarkModeButton;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudealizeUI)
};
}

#endif  // __JUCE_HEADER_EB0317DAAAA56B94__
