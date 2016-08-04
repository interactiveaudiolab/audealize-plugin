//
//  AudealizeColors.h
//
//  Defines a color palette for Audealize plugins
//

#ifndef AudealizeColors_h
#define AudealizeColors_h

class AudealizeColors{
public:
    const Colour outline = Colours::grey;
    const Colour mapBackground = Colours::white;
    const Colour background = Colours::white;
    const Colour titleText = Colours::black;
    const Colour knobFill = Colours::lightblue;
    const Colour accent = Colour(0xffd9edf7);
    const Colour textEditorFill = Colours::white;
    const Colour textEditorFocusedOutline = Colours::violet;
    const Colour buttonFill = Colours::grey;
    
    
private:
    AudealizeColors();
    
    JUCE_DECLARE_NON_COPYABLE(AudealizeColors);
};
}

#endif /* AudealizeColors_h */
