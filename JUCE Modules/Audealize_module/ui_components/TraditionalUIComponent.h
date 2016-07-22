//
//  TraditionalUIComponent.h
//
//  An interface class for traditional user interfaces
//

#ifndef TraditionalUIComponent_h
#define TraditionalUIComponent_h

#include "../audio_processors/AudealizeAudioProcessor.h"

namespace Audealize {
    class TraditionalUI : public Component
    {
    public:
        TraditionalUI(AudealizeAudioProcessor& p) : processor(p) {
            name = "traditional interface";
        };
        
        String getName(){
            return name;
        }
        
    protected:
        AudealizeAudioProcessor& processor;
        String name; // this will determine what the title text (mEffectTypeLabel) in AudealizeUI will display
    };
}

#endif /* TraditionalUIComponent_h */
