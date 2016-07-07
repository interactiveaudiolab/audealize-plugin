//
//  TraditionalUIComponent.h
//
//  An interface class for traditional user interfaces
//

#ifndef TraditionalUIComponent_h
#define TraditionalUIComponent_h

#include "../JuceLibraryCode/JuceHeader.h"
#include "AudealizeAudioProcessor.h"

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
        String name;
    };
}

#endif /* TraditionalUIComponent_h */
