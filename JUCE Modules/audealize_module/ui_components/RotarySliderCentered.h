//
//  RotarySliderCentered.h
//
//  A rotary slider that draws starting from center  
//

#ifndef RotarySliderCentered_h
#define RotarySliderCentered_h

namespace Audealize {
    class RotarySliderCentered : public Slider {
    public:
        RotarySliderCentered(String name) : Slider(name){
            setSliderStyle(RotaryVerticalDrag);
        }
        
        ~RotarySliderCentered() {}
        
        void paint(Graphics& g) override {
            const float sliderPos = (float) valueToProportionOfLength(getValue());
            
            RotaryParameters rotaryParams = getRotaryParameters();
            
            Rectangle<int> sRect = getLookAndFeel().getSliderLayout(*this).sliderBounds; // bounds of slider (excluding text box) within component bounds 
            
            static_cast<AudealizeLookAndFeel&>(getLookAndFeel()).drawRotarySliderCentered(g, sRect.getX(), sRect.getY(), sRect.getWidth(), sRect.getHeight(), sliderPos, rotaryParams.startAngleRadians, rotaryParams.endAngleRadians, *this);
        }
    };
}

#endif /* RotarySliderCentered_h */
