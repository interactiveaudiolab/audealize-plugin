//
//  LookAndFeel.h
//  Audealize
//
//  Created by Michael on 8/4/16.
//
//

#ifndef LookAndFeel_h
#define LookAndFeel_h

#include "AudealizeColors.h"

using namespace juce;

namespace LookAndFeelHelpers // from juce_LookAndFeel_V2.cpp
{
    static Colour createBaseColour (Colour buttonColour,
                                    bool hasKeyboardFocus,
                                    bool isMouseOverButton,
                                    bool isButtonDown) noexcept
    {
        const float sat = hasKeyboardFocus ? 1.3f : 0.9f;
        const Colour baseColour (buttonColour.withMultipliedSaturation (sat));
        
        if (isButtonDown)      return baseColour.contrasting (0.2f);
            if (isMouseOverButton) return baseColour.contrasting (0.1f);
                
                return baseColour;
    }
    
    static TextLayout layoutTooltipText (const String& text, Colour colour) noexcept
    {
        const float tooltipFontSize = 13.0f;
        const int maxToolTipWidth = 400;
        
        AttributedString s;
        s.setJustification (Justification::centred);
        s.append (text, Font (tooltipFontSize, Font::bold), colour);
        
        TextLayout tl;
        tl.createLayoutWithBalancedLineLengths (s, (float) maxToolTipWidth);
        return tl;
    }
}

namespace Audealize {
    class AudealizeLookAndFeel : public LookAndFeel_V3{
    public:
        AudealizeLookAndFeel();
        
        ~AudealizeLookAndFeel();
        
        void setOutlines(bool enabled);
        
        void drawTabAreaBehindFrontButton (TabbedButtonBar& bar, Graphics& g, const int w, const int h) override;
        
        void drawTabButton (TabBarButton& button, Graphics& g, bool isMouseOver, bool isMouseDown) override;
        
        void drawButtonShape (Graphics& g, const Path& outline, Colour baseColour, float height);
        
        
        void drawButtonBackground (Graphics& g, Button& button, const Colour& backgroundColour,
                                   bool isMouseOverButton, bool isButtonDown) override;
        
        void drawTickBox (Graphics& g, Component& component,
                                          float x, float y, float w, float h,
                                          const bool ticked,
                                          const bool isEnabled,
                                          const bool isMouseOverButton,
                          const bool isButtonDown) override;
        
        void drawLinearSliderThumb (Graphics& g, int x, int y, int width, int height,
                                                    float sliderPos, float minSliderPos, float maxSliderPos,
                                    const Slider::SliderStyle style, Slider& slider) override;

        void drawLinearSliderBackground (Graphics& g, int x, int y, int width, int height,
                                                         float /*sliderPos*/,
                                                         float /*minSliderPos*/,
                                                         float /*maxSliderPos*/,
                                         const Slider::SliderStyle /*style*/, Slider& slider) override;
        
        void drawLinearSlider (Graphics& g, int x, int y, int width, int height,
                                               float sliderPos, float minSliderPos, float maxSliderPos,
                               const Slider::SliderStyle style, Slider& slider) override;

        void drawRotarySlider (Graphics& g, int x, int y, int width, int height, float sliderPos,
                               const float rotaryStartAngle, const float rotaryEndAngle, Slider& slider) override;
        
        void drawCornerResizer (Graphics& g,
                                int w, int h,
                                bool /*isMouseOver*/,
                                bool /*isMouseDragging*/) override;

        void drawTextEditorOutline (Graphics& g, int width, int height, TextEditor& textEditor) override;
        
    protected:
        bool shouldDrawOutlines;
    };
    
    class AudealizeLookAndFeelDark : public AudealizeLookAndFeel {
    public:
        AudealizeLookAndFeelDark();
        ~AudealizeLookAndFeelDark() {};
    };
}

#endif /* LookAndFeel_h */
