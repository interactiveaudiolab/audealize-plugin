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
        AudealizeLookAndFeel() {
            setColour(TextButton::buttonColourId, AudealizeColors::buttonFill);
            setColour(TextButton::buttonOnColourId, AudealizeColors::buttonFill.darker(.1));
            setColour(Slider::rotarySliderFillColourId, AudealizeColors::knobFill);
            setColour(Slider::trackColourId, AudealizeColors::sliderTrackFill);
            setColour(Slider::thumbColourId, AudealizeColors::sliderThumbFill);
            setColour(TextEditor::backgroundColourId, AudealizeColors::textEditorFill);
            setColour(TabbedButtonBar::tabOutlineColourId, AudealizeColors::outline);
            setColour(TabbedButtonBar::frontOutlineColourId, AudealizeColors::outline);
            setColour(TabbedComponent::outlineColourId, AudealizeColors::outline);
            setColour(ToggleButton::tickColourId, AudealizeColors::titleText);
            LookAndFeel::setDefaultSansSerifTypefaceName("Helvetica Neue");
        };
        ~AudealizeLookAndFeel() {};
        
        void drawTabAreaBehindFrontButton (TabbedButtonBar& bar, Graphics& g, const int w, const int h) override
        {
            Rectangle<int> line;
            
            switch (bar.getOrientation())
            {
                case TabbedButtonBar::TabsAtLeft:
                    line.setBounds (w - 1, 0, 1, h);
                    break;
                    
                case TabbedButtonBar::TabsAtRight:
                    line.setBounds (0, 0, 1, h);
                    break;
                    
                case TabbedButtonBar::TabsAtTop:
                    line.setBounds (0, h - 1, w, 1);
                    break;
                    
                case TabbedButtonBar::TabsAtBottom:
                    line.setBounds (0, 0, w, 1);
                    break;
                    
                default: break;
            }
            
            
            g.setColour (findColour(TabbedButtonBar::tabOutlineColourId));
            g.fillRect (line);
        }
        
        void drawTabButton (TabBarButton& button, Graphics& g, bool isMouseOver, bool isMouseDown) override
        {
            const Rectangle<int> activeArea (button.getActiveArea());
            
            const TabbedButtonBar::Orientation o = button.getTabbedButtonBar().getOrientation();
            
            const Colour bkg (button.getTabBackgroundColour());
            
            if (button.getToggleState())
            {
                g.setColour (bkg);
            }
            else{
                g.setColour (bkg.darker(.1));
            }
            
            g.fillRect (activeArea);
            
            g.setColour (button.findColour (TabbedButtonBar::tabOutlineColourId));
            
            Rectangle<int> r (activeArea);
            
            if (o != TabbedButtonBar::TabsAtBottom)   g.fillRect (r.removeFromTop (1));
            if (o != TabbedButtonBar::TabsAtTop)      g.fillRect (r.removeFromBottom (1));
            if (o != TabbedButtonBar::TabsAtRight)    g.fillRect (r.removeFromLeft (1));
            if (o != TabbedButtonBar::TabsAtLeft)     g.fillRect (r.removeFromRight (1));
            
            const float alpha = button.isEnabled() ? ((isMouseOver || isMouseDown) ? 1.0f : 0.8f) : 0.3f;
            
            Colour col (bkg.contrasting().withMultipliedAlpha (alpha));
            
            if (TabbedButtonBar* bar = button.findParentComponentOfClass<TabbedButtonBar>())
            {
                TabbedButtonBar::ColourIds colID = button.isFrontTab() ? TabbedButtonBar::frontTextColourId
                : TabbedButtonBar::tabTextColourId;
                
                if (bar->isColourSpecified (colID))
                    col = bar->findColour (colID);
                else if (isColourSpecified (colID))
                    col = findColour (colID);
            }
            
            const Rectangle<float> area (button.getTextArea().toFloat());
            
            float length = area.getWidth();
            float depth  = area.getHeight();
            
            if (button.getTabbedButtonBar().isVertical())
                std::swap (length, depth);
            
            TextLayout textLayout;
            createTabTextLayout (button, length, depth, col, textLayout);
            
            AffineTransform t;
            
            switch (o)
            {
                case TabbedButtonBar::TabsAtLeft:   t = t.rotated (float_Pi * -0.5f).translated (area.getX(), area.getBottom()); break;
                case TabbedButtonBar::TabsAtRight:  t = t.rotated (float_Pi *  0.5f).translated (area.getRight(), area.getY()); break;
                case TabbedButtonBar::TabsAtTop:
                case TabbedButtonBar::TabsAtBottom: t = t.translated (area.getX(), area.getY()); break;
                default:                            jassertfalse; break;
            }
            
            g.addTransform (t);
            textLayout.draw (g, Rectangle<float> (length, depth));
        }

        
        void drawButtonShape (Graphics& g, const Path& outline, Colour baseColour, float height)
        {
            const float mainBrightness = baseColour.getBrightness();
            const float mainAlpha = baseColour.getFloatAlpha();
            
            g.setColour(baseColour);
            
            g.fillPath (outline);
            
            g.setColour (AudealizeColors::outline);
            g.strokePath (outline, PathStrokeType (1.0f));
        }
        
        
        void drawButtonBackground (Graphics& g, Button& button, const Colour& backgroundColour,
                                                   bool isMouseOverButton, bool isButtonDown) override
        {
            Colour baseColour (backgroundColour.withMultipliedSaturation (button.hasKeyboardFocus (true) ? 1.3f : 0.9f)
                               .withMultipliedAlpha (button.isEnabled() ? 0.9f : 0.5f));
            
            if (isButtonDown || isMouseOverButton)
                baseColour = baseColour.contrasting (isButtonDown ? 0.2f : 0.1f);
            
            const bool flatOnLeft   = button.isConnectedOnLeft();
            const bool flatOnRight  = button.isConnectedOnRight();
            const bool flatOnTop    = button.isConnectedOnTop();
            const bool flatOnBottom = button.isConnectedOnBottom();
            
            const float width  = button.getWidth() - 1.0f;
            const float height = button.getHeight() - 1.0f;
            
            if (width > 0 && height > 0)
            {
                const float cornerSize = 4.0f;
                
                Path outline;
                outline.addRoundedRectangle (0.5f, 0.5f, width, height, cornerSize, cornerSize,
                                             ! (flatOnLeft  || flatOnTop),
                                             ! (flatOnRight || flatOnTop),
                                             ! (flatOnLeft  || flatOnBottom),
                                             ! (flatOnRight || flatOnBottom));
                
                drawButtonShape (g, outline, baseColour, height);
            }
        }
        
        
        void drawTickBox (Graphics& g, Component& component,
                                          float x, float y, float w, float h,
                                          const bool ticked,
                                          const bool isEnabled,
                                          const bool isMouseOverButton,
                                          const bool isButtonDown) override
        {
            const float boxSize = w * 0.7f;
            
            g.setColour(AudealizeColors::tickBoxFill);
            g.fillRoundedRectangle(x, (y + boxSize) / 2, boxSize, boxSize, boxSize / 4);
            
            g.setColour(AudealizeColors::outline);
            g.drawRoundedRectangle(x, (y + boxSize) / 2, boxSize, boxSize, boxSize / 4, 1);
            
            if (ticked)
            {
                Path tick;
                tick.startNewSubPath (1.5f, 3.0f);
                tick.lineTo (3.0f, 6.0f);
                tick.lineTo (6.0f, 0.0f);
                
                g.setColour (component.findColour (isEnabled ? ToggleButton::tickColourId
                                                   : ToggleButton::tickDisabledColourId));
                
                const AffineTransform trans (AffineTransform::scale (w / 9.0f, h / 9.0f)
                                             .translated (x, y));
                
                g.strokePath (tick, PathStrokeType (2.5f), trans);
            }
        }
        
        void drawLinearSliderThumb (Graphics& g, int x, int y, int width, int height,
                                                    float sliderPos, float minSliderPos, float maxSliderPos,
                                                    const Slider::SliderStyle style, Slider& slider) override
        {
            const float sliderRadius = (float) (getSliderThumbRadius (slider) - 2);
            
            Colour knobColour (LookAndFeelHelpers::createBaseColour (slider.findColour (Slider::thumbColourId),
                                                                     slider.hasKeyboardFocus (false) && slider.isEnabled(),
                                                                     slider.isMouseOverOrDragging() && slider.isEnabled(),
                                                                     slider.isMouseButtonDown() && slider.isEnabled()));
            
            const float outlineThickness = slider.isEnabled() ? 0.8f : 0.3f;
            
            
            if (style == Slider::LinearHorizontal || style == Slider::LinearVertical)
            {
                float kx, ky;
                
                if (style == Slider::LinearVertical)
                {
                    kx = x + width * 0.5f;
                    ky = sliderPos;
                }
                else
                {
                    kx = sliderPos;
                    ky = y + height * 0.5f;
                }
                
                g.setColour(knobColour);
                g.fillEllipse(kx - sliderRadius, ky - sliderRadius, sliderRadius * 2.0f, sliderRadius * 2.0f);
                g.setColour(AudealizeColors::outline);
                g.drawEllipse(kx - sliderRadius, ky - sliderRadius, sliderRadius * 2.0f, sliderRadius * 2.0f, outlineThickness);

            }
            else
            {
                if (style == Slider::ThreeValueVertical)
                {
                    g.setColour(knobColour);
                    g.fillEllipse(x + width * 0.5f - sliderRadius, sliderPos - sliderRadius, sliderRadius * 2.0f, sliderRadius * 2.0f);
                    g.setColour(AudealizeColors::outline);
                    g.drawEllipse(x + width * 0.5f - sliderRadius, sliderPos - sliderRadius, sliderRadius * 2.0f, sliderRadius * 2.0f, outlineThickness);
                }
                else if (style == Slider::ThreeValueHorizontal)
                {
                    g.setColour(knobColour);
                    g.fillEllipse(sliderPos - sliderRadius, y + height * 0.5f - sliderRadius, sliderRadius * 2.0f, sliderRadius * 2.0f);
                    g.setColour(AudealizeColors::outline);
                    g.drawEllipse(sliderPos - sliderRadius, y + height * 0.5f - sliderRadius, sliderRadius * 2.0f, sliderRadius * 2.0f, outlineThickness);
                }
                
                if (style == Slider::TwoValueVertical || style == Slider::ThreeValueVertical)
                {
                    const float sr = jmin (sliderRadius, width * 0.4f);
                    
                    drawGlassPointer (g, jmax (0.0f, x + width * 0.5f - sliderRadius * 2.0f),
                                      minSliderPos - sliderRadius,
                                      sliderRadius * 2.0f, knobColour, outlineThickness, 1);
                    
                    drawGlassPointer (g, jmin (x + width - sliderRadius * 2.0f, x + width * 0.5f), maxSliderPos - sr,
                                      sliderRadius * 2.0f, knobColour, outlineThickness, 3);
                }
                else if (style == Slider::TwoValueHorizontal || style == Slider::ThreeValueHorizontal)
                {
                    const float sr = jmin (sliderRadius, height * 0.4f);
                    
                    drawGlassPointer (g, minSliderPos - sr,
                                      jmax (0.0f, y + height * 0.5f - sliderRadius * 2.0f),
                                      sliderRadius * 2.0f, knobColour, outlineThickness, 2);
                    
                    drawGlassPointer (g, maxSliderPos - sliderRadius,
                                      jmin (y + height - sliderRadius * 2.0f, y + height * 0.5f),
                                      sliderRadius * 2.0f, knobColour, outlineThickness, 4);
                }
            }
        }

        void drawLinearSliderBackground (Graphics& g, int x, int y, int width, int height,
                                                         float /*sliderPos*/,
                                                         float /*minSliderPos*/,
                                                         float /*maxSliderPos*/,
                                                         const Slider::SliderStyle /*style*/, Slider& slider) override
        {
            const float sliderRadius = (float) (getSliderThumbRadius (slider) - 2);
            
            const Colour trackColour (slider.findColour (Slider::trackColourId));

            Path indent;
            
            if (slider.isHorizontal())
            {
                const float iy = y + height * 0.5f - sliderRadius * 0.5f;
                
                g.setColour(AudealizeColors::sliderTrackFill);
                
                indent.addRoundedRectangle (x - sliderRadius * 0.5f, iy, width + sliderRadius, sliderRadius, 5.0f);
            }
            else
            {
                const float ix = x + width * 0.5f - sliderRadius * 0.5f;
                
                g.setColour(AudealizeColors::sliderTrackFill);
                
                indent.addRoundedRectangle (ix, y - sliderRadius * 0.5f, sliderRadius, height + sliderRadius, 5.0f);
            }
            
            g.fillPath (indent);
            
            g.setColour (trackColour.contrasting (0.5f));
            g.strokePath (indent, PathStrokeType (0.5f));
        }
        
        void drawLinearSlider (Graphics& g, int x, int y, int width, int height,
                                               float sliderPos, float minSliderPos, float maxSliderPos,
                                               const Slider::SliderStyle style, Slider& slider) override
        {
            g.fillAll (slider.findColour (Slider::backgroundColourId));
            
            if (style == Slider::LinearBar || style == Slider::LinearBarVertical)
            {
                const float fx = (float) x, fy = (float) y, fw = (float) width, fh = (float) height;
                
                Path p;
                
                if (style == Slider::LinearBarVertical)
                    p.addRectangle (fx, sliderPos, fw, 1.0f + fh - sliderPos);
                else
                    p.addRectangle (fx, fy, sliderPos - fx, fh);
                
                Colour baseColour (slider.findColour (Slider::thumbColourId)
                                   .withMultipliedSaturation (slider.isEnabled() ? 1.0f : 0.5f)
                                   .withMultipliedAlpha (0.8f));
                
                g.setColour(AudealizeColors::sliderTrackFill);
                g.fillPath (p);
                
                g.setColour (baseColour.darker (0.2f));
                
                if (style == Slider::LinearBarVertical)
                    g.fillRect (fx, sliderPos, fw, 1.0f);
                else
                    g.fillRect (sliderPos, fy, 1.0f, fh);
            }
            else
            {
                drawLinearSliderBackground (g, x, y, width, height, sliderPos, minSliderPos, maxSliderPos, style, slider);
                drawLinearSliderThumb (g, x, y, width, height, sliderPos, minSliderPos, maxSliderPos, style, slider);
            }
        }

        void drawRotarySlider (Graphics& g, int x, int y, int width, int height, float sliderPos,
                                               const float rotaryStartAngle, const float rotaryEndAngle, Slider& slider) override
        {
            const float radius = jmin (width / 2, height / 2) - 2.0f;
            const float centreX = x + width * 0.5f;
            const float centreY = y + height * 0.5f;
            const float rx = centreX - radius;
            const float ry = centreY - radius;
            const float rw = radius * 2.0f;
            const float angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
            const bool isMouseOver = slider.isMouseOverOrDragging() && slider.isEnabled();
            
            if (radius > 12.0f)
            {
                if (slider.isEnabled())
                    g.setColour (slider.findColour (Slider::rotarySliderFillColourId).withAlpha (isMouseOver ? 1.0f : 0.7f));
                else
                    g.setColour (Colour (0x80808080));
                
                const float thickness = 0.7f;
                
                Path backgroundArc;
                backgroundArc.addPieSegment (rx, ry, rw, rw, rotaryStartAngle, rotaryEndAngle, thickness);
                backgroundArc.closeSubPath();
                g.setColour(AudealizeColors::sliderTrackFill);
                g.fillPath(backgroundArc);
                
                {
                    Path filledArc;
                    filledArc.addPieSegment (rx, ry, rw, rw, rotaryStartAngle, angle, thickness);
                    g.fillPath (filledArc);
                }
                
                {
                    const float innerRadius = radius * 0.2f;
                    Path p;
                    p.addTriangle (-innerRadius, 0.0f,
                                   0.0f, -radius * thickness * 1.1f,
                                   innerRadius, 0.0f);
                    
                    p.addEllipse (-innerRadius, -innerRadius, innerRadius * 2.0f, innerRadius * 2.0f);
                    
                    g.fillPath (p, AffineTransform::rotation (angle).translated (centreX, centreY));
                }
                
                if (slider.isEnabled())
                    g.setColour (slider.findColour (Slider::rotarySliderOutlineColourId));
                else
                    g.setColour (Colour (0x80808080));
                
             
            }
            else
            {
                if (slider.isEnabled())
                    g.setColour (slider.findColour (Slider::rotarySliderFillColourId).withAlpha (isMouseOver ? 1.0f : 0.7f));
                else
                    g.setColour (Colour (0x80808080));
                
                Path p;
                p.addEllipse (-0.4f * rw, -0.4f * rw, rw * 0.8f, rw * 0.8f);
                PathStrokeType (rw * 0.1f).createStrokedPath (p, p);
                
                p.addLineSegment (Line<float> (0.0f, 0.0f, 0.0f, -radius), rw * 0.2f);
                
                g.fillPath (p, AffineTransform::rotation (angle).translated (centreX, centreY));
            }
        }

    };
}

#endif /* LookAndFeel_h */
