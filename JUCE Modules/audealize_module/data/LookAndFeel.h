#ifndef Header_h
#define Header_h

using namespace juce;

namespace Audealize {
    class LookAndFeel : public LookAndFeel_V3{
    public:
        LookAndFeel();
        
        ~LookAndFeel();
        
        
        virtual void drawRotarySlider	(	Graphics & 	g,
                                         int 	x,
                                         int 	y,
                                         int 	width,
                                         int 	height,
                                         float 	sliderPosProportional,
                                         float 	rotaryStartAngle,
                                         float 	rotaryEndAngle,
                                         Slider & 	slider );
        
        virtual void drawLinearSlider (Graphics& g,
                                       int x, int y,
                                       int width, int height,
                                       float sliderPos,
                                       float minSliderPos,
                                       float maxSliderPos,
                                       const Slider::SliderStyle style,
                                       Slider& slider);
        
        virtual void drawTickBox (Graphics& g,
                                  Component& component,
                                  float x, float y, float w, float h,
                                  bool ticked,
                                  bool isEnabled,
                                  bool isMouseOverButton,
                                  bool isButtonDown);


    };
}

#endif /* Header_h */
