//
//  TraditionalUIComponent.h
//
//  An interface class for Audealize traditional user interfaces (interfaces with knobs sliders)
//  Intended for use as child component of an AudealizeUI
//

#ifndef TraditionalUIComponent_h
#define TraditionalUIComponent_h

#include "../audio_processors/AudealizeAudioProcessor.h"

namespace Audealize
{
class TraditionalUI : public Component
{
public:
    TraditionalUI (AudealizeAudioProcessor& p) : processor (p)
    {
        name = "traditional interface";
    };

    /**
     *  Returns the name of the effect being controlled by the TraditionalUI
     */
    String getName ()
    {
        return name;
    }

protected:
    AudealizeAudioProcessor& processor;
    String name;  // this will determine what the title text (mEffectTypeLabel) in AudealizeUI will display

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TraditionalUI);
};
}

#endif /* TraditionalUIComponent_h */
