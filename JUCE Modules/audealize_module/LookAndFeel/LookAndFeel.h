//
//  LookAndFeel.h
//  Audealize
//
//  Created by Michael on 8/4/16.
//
//

#ifndef LookAndFeel_h
#define LookAndFeel_h

using namespace juce;

namespace Audealize {
    class AudealizeLookAndFeel : public LookAndFeel_V3{
    public:
        AudealizeLookAndFeel() {};
        ~AudealizeLookAndFeel() {};
        
        void drawTabAreaBehindFrontButton (TabbedButtonBar& bar, Graphics& g, const int w, const int h)
        {
            g.setColour (AudealizeColors::outline);
            g.fillRect (line);
        }
    };
}

#endif /* LookAndFeel_h */
