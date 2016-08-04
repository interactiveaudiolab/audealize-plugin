//
//  AudealizeColors.h
//
//  Defines a color palette for Audealize plugins
//

#ifndef AudealizeColors_h
#define AudealizeColors_h

using namespace juce;

namespace Audealize{
    
    class AudealizeColors{
    public:
        static const Colour outline,
                            mapBackground,
                            background,
                            titleText,
                            knobFill,
                            sliderThumbFill,
                            sliderTrackFill,
                            accent,
                            accentOutline,
                            textEditorFill,
                            textEditorFocusedOutline,
                            tabFill,
                            buttonFill,
                            tickBoxFill;
        
    private:
        AudealizeColors();
        
        JUCE_DECLARE_NON_COPYABLE(AudealizeColors);
    };
    
}

#endif /* AudealizeColors_h */
