//
// AudealizeImages.h
//
// Defines binary data resources for images used in Audealize plugins
//

#ifndef AudealizeImages_h
#define AudealizeImages_h

namespace Audealize
{
/// Binary data resources for images
class AudealizeImages
{
public:
    /**
     *  Dark/light theme toggle button graphic
     */
    static const char* darkModeButton_svg;
    static const int darkModeButton_svgSize;

    /**
     *  Interactive Audio Lab logo
     */
    static const char* iallogo_svg;
    static const int iallogo_svgSize;

    /**
     *  Power button glyph (for BypassButton)
     */
    static const char* powerButton_svg;
    static const int powerButton_svgSize;

private:
    AudealizeImages ();

    JUCE_DECLARE_NON_COPYABLE (AudealizeImages);
};
}

#endif