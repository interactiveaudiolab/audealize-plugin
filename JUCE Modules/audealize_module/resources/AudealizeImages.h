//
// AudealizeImages.h
//
// Defines image resources for Audealize plugins
//

#ifndef AudealizeImages_h
#define AudealizeImages_h

namespace Audealize{
    class AudealizeImages{
    public:
        static const char* darkModeButton_svg;
        static const int darkModeButton_svgSize;
        
        static const char* iallogo_svg;
        static const int iallogo_svgSize;
        
        static const char* powerButton_svg;
        static const int powerButton_svgSize;

    private:
        AudealizeImages();
        
        JUCE_DECLARE_NON_COPYABLE(AudealizeImages);
    };
}

#endif