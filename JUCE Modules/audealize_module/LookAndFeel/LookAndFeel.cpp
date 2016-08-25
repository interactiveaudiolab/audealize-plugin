#include "LookAndFeel.h"

using namespace juce;

namespace Audealize {
    
    AudealizeLookAndFeelDark::AudealizeLookAndFeelDark()
    {
        isDarkMode = true;
        
        const Colour darkGray(0xff1c1c1c);
        const Colour midGray(0xff2f2f2f);
        const Colour textGray(0xffbbbbbb);
        const Colour lightBlue(0xffadd8e6);
        const Colour sliderThumbGray(0xff727272);
        const Colour offWhite(0xff999999);

        outline = darkGray;
        
        setColour(WordMap::backgroundColourId, darkGray);
        setColour(WordMap::outlineColourId, Colours::transparentWhite);
        setColour(WordMap::circleColourId, textGray);

        setColour(AudealizeUI::textColourId, textGray);
        setColour(AudealizeUI::backgroundColourId, midGray);
        
        setColour(AudealizeMultiUI::backgroundColourId, midGray);
        setColour(AudealizeMultiUI::textColourId, textGray);
        setColour(AudealizeMultiUI::outlineColourId, Colours::transparentWhite);
        setColour(AudealizeMultiUI::accentColourId, darkGray);
        
        setColour(TypeaheadPopupMenu::backgroundColourId, midGray);
        setColour(TypeaheadPopupMenu::textColourId, textGray);
        setColour(TypeaheadPopupMenu::highlightColourId, textGray);
        setColour(TypeaheadPopupMenu::textSelectedColourId, midGray);
        setColour(GraphicEQComponent::tickMarkColourId, midGray.brighter(.15));
        
        setColour(AudealizeTabbedComponent::backgroundColourId, midGray);
        
        setColour(AboutComponent::backgroundColourId, midGray);
        setColour(AboutComponent::textColourId, textGray);
        
        setColour(TextButton::buttonColourId, darkGray);
        setColour(TextButton::buttonOnColourId, darkGray.darker(.1));
        setColour(TextButton::textColourOnId, textGray);
        setColour(TextButton::textColourOffId, textGray);
        setColour(Slider::rotarySliderFillColourId, lightBlue);
        setColour(Slider::trackColourId, darkGray);
        setColour(Slider::thumbColourId, sliderThumbGray);
        setColour(TextEditor::backgroundColourId, darkGray);
        setColour(TextEditor::textColourId, textGray);
        setColour(TextEditor::focusedOutlineColourId, textGray.withMultipliedAlpha(0.2f));
        setColour(TextEditor::outlineColourId, textGray.withMultipliedAlpha(0.5f));
        setColour(TextEditor::highlightColourId, offWhite);
        setColour(Slider::textBoxBackgroundColourId, darkGray);
        setColour(Slider::textBoxTextColourId, textGray);
        setColour(Slider::textBoxOutlineColourId, Colours::transparentWhite);
        setColour(Slider::textBoxHighlightColourId, offWhite);
        
        setColour(TabbedButtonBar::tabOutlineColourId, Colours::transparentWhite);
        setColour(TabbedButtonBar::frontOutlineColourId, Colours::transparentWhite);
        setColour(TabbedComponent::outlineColourId, Colours::transparentWhite);
        setColour(ToggleButton::tickColourId, textGray);
        setColour(ToggleButton::textColourId, textGray);
        setColour(Label::textColourId, textGray);
        setColour(ListBox::backgroundColourId , midGray);
        setColour(CaretComponent::caretColourId, textGray);
        setColour(HyperlinkButton::textColourId, textGray.brighter(.3));
        
        setColour(TooltipWindow::textColourId, textGray);
        setColour(TooltipWindow::backgroundColourId, darkGray);
        setColour(TooltipWindow::outlineColourId, darkGray.brighter(.1));
        
        LookAndFeel::setDefaultSansSerifTypefaceName("Roboto");
        
        shouldDrawOutlines = false;
    }
    
    AudealizeLookAndFeel::AudealizeLookAndFeel() : outline(0xff909090)
    {
        isDarkMode = false;
        
        const Colour sliderTrackFill(0xffeeeeee);
        const Colour accentBlue(0xffd9edf7);
        
        setColour(WordMap::backgroundColourId, Colours::white);
        setColour(WordMap::outlineColourId, outline);
        setColour(WordMap::circleColourId, Colour(0xff999999));
        
        setColour(AudealizeUI::textColourId, Colours::black);
        setColour(AudealizeUI::backgroundColourId, Colours::white);
        
        setColour(AudealizeMultiUI::backgroundColourId, Colours::white);
        setColour(AudealizeMultiUI::textColourId, Colours::black);
        setColour(AudealizeMultiUI::outlineColourId, outline);
        setColour(AudealizeMultiUI::accentColourId, accentBlue);
        
        setColour(TypeaheadPopupMenu::backgroundColourId, Colours::white);
        setColour(TypeaheadPopupMenu::textColourId, Colours::black);
        setColour(TypeaheadPopupMenu::highlightColourId, accentBlue);
        setColour(TypeaheadPopupMenu::textSelectedColourId, Colours::black);

        setColour(GraphicEQComponent::tickMarkColourId, outline);
        
        setColour(AudealizeTabbedComponent::backgroundColourId, Colours::white);
        
        setColour(AboutComponent::backgroundColourId, Colours::white);
        setColour(AboutComponent::textColourId, Colours::black);

        setColour(TextButton::buttonColourId, Colours::white);
        setColour(TextButton::buttonOnColourId, Colours::white.darker(.1));
        setColour(TextButton::textColourOnId, Colours::black);
        setColour(TextButton::textColourOffId, Colours::black);
        setColour(Slider::rotarySliderFillColourId, accentBlue);
        setColour(Slider::trackColourId, sliderTrackFill);
        setColour(Slider::thumbColourId, Colours::white);
        setColour(TextEditor::backgroundColourId, Colours::white);
        setColour(TextEditor::textColourId, Colours::black);
        setColour(TextEditor::focusedOutlineColourId, outline);
        setColour(TextEditor::outlineColourId, outline);
        setColour(TextEditor::highlightColourId, accentBlue);

        setColour(Slider::textBoxBackgroundColourId, Colours::white);
        setColour(Slider::textBoxTextColourId, Colours::black);
        setColour(Slider::textBoxOutlineColourId, outline);
        setColour(Slider::textBoxHighlightColourId, accentBlue);
        
        setColour(TabbedButtonBar::tabOutlineColourId, outline);
        setColour(TabbedButtonBar::frontOutlineColourId, outline);
        setColour(TabbedComponent::outlineColourId, outline);
        setColour(ToggleButton::tickColourId, Colours::black);
        setColour(ToggleButton::textColourId, Colours::black);
        setColour(Label::textColourId, Colours::black);
        setColour(ListBox::backgroundColourId , Colours::white);
        setColour(CaretComponent::caretColourId, Colours::black);
        setColour(HyperlinkButton::textColourId, Colours::black.brighter(.3));
        
        setColour(TooltipWindow::textColourId, Colours::black);
        setColour(TooltipWindow::backgroundColourId, Colours::white);
        setColour(TooltipWindow::outlineColourId, outline);

        LookAndFeel::setDefaultSansSerifTypefaceName("Roboto");
        
        shouldDrawOutlines = true;
    };
    AudealizeLookAndFeel::~AudealizeLookAndFeel() {};
    
    void AudealizeLookAndFeel::setOutlines(bool enabled){
        shouldDrawOutlines = enabled;
    }
    
    void AudealizeLookAndFeel::drawTabAreaBehindFrontButton (TabbedButtonBar& bar, Graphics& g, const int w, const int h)
    {
        if (!shouldDrawOutlines) {
            return;
        }
        
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
    
    void AudealizeLookAndFeel::drawTabButton (TabBarButton& button, Graphics& g, bool isMouseOver, bool isMouseDown)
    {
        const Rectangle<int> activeArea (button.getActiveArea());
        
        const TabbedButtonBar::Orientation o = button.getTabbedButtonBar().getOrientation();
        
        const Colour bkg (button.getTabBackgroundColour());
        
        if (button.getToggleState())
        {
            g.setColour (bkg);
        }
        else{
            g.setColour (bkg.darker(.2));
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
    
    
    void AudealizeLookAndFeel::drawButtonShape (Graphics& g, const Path& outline, Colour baseColour, float height)
    {
        g.setColour(baseColour);
        
        g.fillPath (outline);
        
        if (shouldDrawOutlines){
            g.setColour (this->outline);
            g.strokePath (outline, PathStrokeType (1.0f));
        }
    }
    
    
    void AudealizeLookAndFeel::drawButtonBackground (Graphics& g, Button& button, const Colour& backgroundColour,
                                                     bool isMouseOverButton, bool isButtonDown)
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
    
    
    void AudealizeLookAndFeel::drawTickBox (Graphics& g, Component& component,
                                            float x, float y, float w, float h,
                                            const bool ticked,
                                            const bool isEnabled,
                                            const bool isMouseOverButton,
                                            const bool isButtonDown)
    {
        const float boxSize = w * 0.7f;
        
        //g.setColour(0x00000000);
        //g.fillRoundedRectangle(x, (y + boxSize) / 2, boxSize, boxSize, boxSize / 4);

        g.setColour(outline);
        if (shouldDrawOutlines){
            g.drawRoundedRectangle(x, (y + boxSize) / 2, boxSize, boxSize, boxSize / 4, 1);
        }
        else{
            g.fillRoundedRectangle(x, (y + boxSize) / 2, boxSize, boxSize, boxSize / 4);
        }
    
        
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
    
    void AudealizeLookAndFeel::drawLinearSliderThumb (Graphics& g, int x, int y, int width, int height,
                                                      float sliderPos, float minSliderPos, float maxSliderPos,
                                                      const Slider::SliderStyle style, Slider& slider)
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
            if(shouldDrawOutlines){
                g.setColour(this->outline);
                g.drawEllipse(kx - sliderRadius, ky - sliderRadius, sliderRadius * 2.0f, sliderRadius * 2.0f, outlineThickness);
            }
            
        }
        else
        {
            if (style == Slider::ThreeValueVertical)
            {
                g.setColour(knobColour);
                g.fillEllipse(x + width * 0.5f - sliderRadius, sliderPos - sliderRadius, sliderRadius * 2.0f, sliderRadius * 2.0f);
                if(shouldDrawOutlines){
                    g.setColour(this->outline);
                    g.drawEllipse(x + width * 0.5f - sliderRadius, sliderPos - sliderRadius, sliderRadius * 2.0f, sliderRadius * 2.0f, outlineThickness);
                }
            }
            else if (style == Slider::ThreeValueHorizontal)
            {
                g.setColour(knobColour);
                g.fillEllipse(sliderPos - sliderRadius, y + height * 0.5f - sliderRadius, sliderRadius * 2.0f, sliderRadius * 2.0f);
                if(shouldDrawOutlines){
                    g.setColour(this->outline);
                    g.drawEllipse(sliderPos - sliderRadius, y + height * 0.5f - sliderRadius, sliderRadius * 2.0f, sliderRadius * 2.0f, outlineThickness);
                }
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
    
    void AudealizeLookAndFeel::drawLinearSliderBackground (Graphics& g, int x, int y, int width, int height,
                                                           float /*sliderPos*/,
                                                           float /*minSliderPos*/,
                                                           float /*maxSliderPos*/,
                                                           const Slider::SliderStyle /*style*/, Slider& slider)
    {
        const float sliderRadius = (float) (getSliderThumbRadius (slider) - 2);
        
        const Colour trackColour (slider.findColour (Slider::trackColourId));
        
        Path indent;
        
        if (slider.isHorizontal())
        {
            const float iy = y + height * 0.5f - sliderRadius * 0.5f;
            
            g.setColour(trackColour);
            
            indent.addRoundedRectangle (x - sliderRadius * 0.5f, iy, width + sliderRadius, sliderRadius, 5.0f);
        }
        else
        {
            const float ix = x + width * 0.5f - sliderRadius * 0.5f;
            
            g.setColour(trackColour);
            
            indent.addRoundedRectangle (ix, y - sliderRadius * 0.5f, sliderRadius, height + sliderRadius, 5.0f);
        }
        
        g.fillPath (indent);
        
        if(shouldDrawOutlines) {
            g.setColour (trackColour.contrasting (0.5f));
            g.strokePath (indent, PathStrokeType (0.5f));
        }
    }
    
    void AudealizeLookAndFeel::drawLinearSlider (Graphics& g, int x, int y, int width, int height,
                                                 float sliderPos, float minSliderPos, float maxSliderPos,
                                                 const Slider::SliderStyle style, Slider& slider)
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
            
            g.setColour(slider.findColour(Slider::trackColourId));
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
    
    void AudealizeLookAndFeel::drawRotarySlider (Graphics& g, int x, int y, int width, int height, float sliderPos,
                                                 const float rotaryStartAngle, const float rotaryEndAngle, Slider& slider)
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
            const float thickness = 0.78;
            
            int knobRadius = radius * .68;
            
            g.setColour(findColour(Slider::ColourIds::thumbColourId));
            g.fillEllipse(centreX - knobRadius, centreY -knobRadius, knobRadius * 2, knobRadius * 2);
            
            if (shouldDrawOutlines){
                g.setColour(this->outline);
                g.drawEllipse(centreX - knobRadius, centreY -knobRadius, knobRadius * 2, knobRadius * 2, 1);
            }
            
            Path backgroundArc;
            backgroundArc.addPieSegment (rx, ry, rw, rw, rotaryStartAngle, rotaryEndAngle, thickness);
            backgroundArc.closeSubPath();
            g.setColour(findColour(Slider::trackColourId));
            g.fillPath(backgroundArc);
            
            if (shouldDrawOutlines){
                g.setColour(this->outline);
                g.strokePath(backgroundArc, PathStrokeType(1));
            }
            
            if (slider.isEnabled())
                g.setColour (slider.findColour (Slider::rotarySliderFillColourId).withAlpha (isMouseOver ? 1.0f : 0.7f));
            else
                g.setColour (Colour (0x80808080));
            
            
            
            {
                Path filledArc;
                filledArc.addPieSegment (rx, ry, rw, rw, rotaryStartAngle, angle, thickness);
                g.fillPath (filledArc);
                if (shouldDrawOutlines){
                    g.setColour(this->outline);
                    g.strokePath(filledArc, PathStrokeType(1));
                }
            }
            
            {
                Path p;
                float rectHeight = radius * .3f;
                float rectWidth = radius * .15f;
                p.addRoundedRectangle(- rectWidth * .5, - rectHeight * 1.8, rectWidth, rectHeight, rectWidth * .5);
                
                g.setColour(findColour(Slider::trackColourId).darker(.3));
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
    
    void AudealizeLookAndFeel::drawRotarySliderCentered (Graphics& g, int x, int y, int width, int height, float sliderPos,
                                                 const float rotaryStartAngle, const float rotaryEndAngle, Slider& slider)
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
            const float thickness = 0.78;
            
            int knobRadius = radius * .68;
            
            g.setColour(findColour(Slider::ColourIds::thumbColourId));
            g.fillEllipse(centreX - knobRadius, centreY -knobRadius, knobRadius * 2, knobRadius * 2);
            
            if (shouldDrawOutlines){
                g.setColour(this->outline);
                g.drawEllipse(centreX - knobRadius, centreY -knobRadius, knobRadius * 2, knobRadius * 2, 1);
            }
            
            Path backgroundArc;
            backgroundArc.addPieSegment (rx, ry, rw, rw, rotaryStartAngle, rotaryEndAngle, thickness);
            backgroundArc.closeSubPath();
            g.setColour(findColour(Slider::trackColourId));
            g.fillPath(backgroundArc);
            
            if (shouldDrawOutlines){
                g.setColour(this->outline);
                g.strokePath(backgroundArc, PathStrokeType(1));
            }
            
            if (slider.isEnabled())
                g.setColour (slider.findColour (Slider::rotarySliderFillColourId).withAlpha (isMouseOver ? 1.0f : 0.7f));
            else
                g.setColour (Colour (0x80808080));
            
            
            
            {
                Path filledArc;
                filledArc.addPieSegment (rx, ry, rw, rw, (rotaryStartAngle + rotaryEndAngle) * .5f, angle, thickness);
                g.fillPath (filledArc);
                if (shouldDrawOutlines){
                    g.setColour(this->outline);
                    g.strokePath(filledArc, PathStrokeType(1));
                }
            }
            
            {
                Path p;
                float rectHeight = radius * .3f;
                float rectWidth = radius * .15f;
                p.addRoundedRectangle(- rectWidth * .5, - rectHeight * 1.8, rectWidth, rectHeight, rectWidth * .5);
                
                g.setColour(findColour(Slider::trackColourId).darker(.3));
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

    
    void AudealizeLookAndFeel::drawCornerResizer (Graphics& g,
                                                  int w, int h,
                                                  bool /*isMouseOver*/,
                                                  bool /*isMouseDragging*/) 
    {
        const float lineThickness = jmin (w, h) * 0.1f;
        
        for (float i = 0.0f; i < 1.0f; i += 0.3f)
        {
            g.setColour (this->outline);
            
            g.drawLine (w * i,
                        h + 1.0f,
                        w + 1.0f,
                        h * i,
                        lineThickness);
        }
    }
    
    void AudealizeLookAndFeel::drawTextEditorOutline (Graphics& g, int width, int height, TextEditor& textEditor)
    {
        if (textEditor.isEnabled())
        {
            if (textEditor.hasKeyboardFocus (true) && ! textEditor.isReadOnly())
            {
                g.setColour (textEditor.findColour (TextEditor::focusedOutlineColourId));
                g.drawRect (0, 0, width, height, 1.5);
            }
            else if(shouldDrawOutlines)
            {
                g.setColour (textEditor.findColour (TextEditor::outlineColourId));
                g.drawRect (0, 0, width, height);
            }
        }
    }
    
}