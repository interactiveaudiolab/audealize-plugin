//
//  TraditionalUIComponent.h
//
//  An interface class for traditional user interfaces
//

#ifndef TraditionalUIComponent_h
#define TraditionalUIComponent_h


namespace Audealize {
    
    class TraditionalUI : public Component
    {
    public:
        TraditionalUI(AudealizeAudioProcessor& p) : processor(p) {};
        
    protected:
        AudealizeAudioProcessor& processor;
    };

}

#endif /* TraditionalUIComponent_h */
