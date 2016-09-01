//
//  BypassButton.h
//
//  A toggleable juce::DrawableButton with an on/off glyph graphic
//  Intended for use as bypass buttons in a TabbedButtonBar component in an AudealizeMultiUI
//

#ifndef BypassButton_h
#define BypassButton_h

namespace Audealize
{
class BypassButton : public DrawableButton
{
public:
    enum ColourIds
    {
        offColourId = 0x2000900,
        onColourId = 0x2000901,
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
