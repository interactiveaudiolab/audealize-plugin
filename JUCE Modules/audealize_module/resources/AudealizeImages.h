#ifndef AudealizeImages_h
#define AudealizeImages_h


namespace Audealize{
    class AudealizeImages{
    public:
        static const char* darkModeButton_svg;
        static const int darkModeButton_svgSize;
        
        static const char* darkModeButtonLight_svg;
        static const int darkModeButtonLight_svgSize;

        static const char* iallogo_svg;
        static const int iallogo_svgSize;
        

    private:
        AudealizeImages();
        JUCE_DECLARE_NON_COPYABLE(AudealizeImages);
    };
}

#endif