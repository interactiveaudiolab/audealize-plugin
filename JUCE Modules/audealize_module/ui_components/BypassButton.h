//
//  BypassButton.h
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
        
        BypassButton() : DrawableButton("", ButtonStyle::ImageOnButtonBackground)
        {
            mOffGraphic = Drawable::createFromImageData(AudealizeImages::powerButton_svg, AudealizeImages::powerButton_svgSize);
            mOffGraphic->replaceColour(Colour(0xff000000), findColour(offColourId));
            
            mOnGraphic = Drawable::createFromImageData(AudealizeImages::powerButton_svg, AudealizeImages::powerButton_svgSize);
            mOnGraphic->replaceColour(Colour(0xff000000), findColour(onColourId));
            
            
            setImages(mOffGraphic, nullptr, nullptr, nullptr, mOnGraphic, nullptr, nullptr, nullptr);
            
            setEdgeIndent(10);
            
            setClickingTogglesState(true);
            
            setSize(30, 30);
        }
        
        ~BypassButton() {}
        
        void paintButton (Graphics& g, const bool isMouseOverButton, const bool isButtonDown) override {}
        
    private:
        ScopedPointer<Drawable> mOffGraphic, mOnGraphic;
    };
}

#endif /* BypassButton_h */
