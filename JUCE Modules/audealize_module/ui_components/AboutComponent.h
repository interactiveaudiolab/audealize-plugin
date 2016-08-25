//
//  AboutComponent.h
//
//  A JUCE component to display "about" info for Audealize plugins
//  Intended for use as the content component of a DialogWindow
//

#ifndef __JUCE_HEADER_6F5BC92BB0597534__
#define __JUCE_HEADER_6F5BC92BB0597534__

#include "../JuceLibraryCode/JuceHeader.h"

class AboutComponent  : public Component,
                        public ButtonListener
{
public:
    AboutComponent ();
    ~AboutComponent();
  
    enum ColourIds{
        backgroundColourId = 0x2000700,
        textColourId = 0x2000701
    };

    void paint (Graphics& g) override;
    void resized() override;
    void buttonClicked (Button* buttonThatWasClicked) override;

private:
    ScopedPointer<Label> mGrantInfoLabel;
    ScopedPointer<Label> mCopyrightLabel;
    ScopedPointer<HyperlinkButton> audealizeLink;
    ScopedPointer<Label> mDescriptionLabel;
    ScopedPointer<Label> mAudealizeLabel;
    ScopedPointer<Label> mVersionLabel;
    ScopedPointer<HyperlinkButton> mLabLinkButton;
    ScopedPointer<Drawable> mLogoDrawable;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AboutComponent)
};


#endif   // __JUCE_HEADER_6F5BC92BB0597534__
