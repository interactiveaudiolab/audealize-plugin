#include "ReverbComponent.h"

namespace Audealize
{
ReverbComponent::ReverbComponent (AudealizeAudioProcessor& p) : TraditionalUI (p)
{
    //=========================================================================
    // Labels

    addAndMakeVisible (mLabelD = new Label ("new label", TRANS ("Comb Filter Delay")));
    mLabelD->setFont (Font (15.00f, Font::plain));
    mLabelD->setJustificationType (Justification::centredTop);
    mLabelD->setEditable (false, false, false);
    mLabelD->setColour (TextEditor::textColourId, Colours::black);
    mLabelD->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (mLabelG = new Label ("new label", TRANS ("Comb Filter Gain\n")));
    mLabelG->setFont (Font (15.00f, Font::plain));
    mLabelG->setJustificationType (Justification::centredTop);
    mLabelG->setEditable (false, false, false);
    mLabelG->setColour (TextEditor::textColourId, Colours::black);
    mLabelG->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (mLabelM = new Label ("new label", TRANS ("Channel Delay\n")));
    mLabelM->setFont (Font (15.00f, Font::plain));
    mLabelM->setJustificationType (Justification::centredTop);
    mLabelM->setEditable (false, false, false);
    mLabelM->setColour (TextEditor::textColourId, Colours::black);
    mLabelM->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (mLabelF = new Label ("new label", TRANS ("High Cut\n"
                                                                "\n")));
    mLabelF->setFont (Font (15.00f, Font::plain));
    mLabelF->setJustificationType (Justification::centredTop);
    mLabelF->setEditable (false, false, false);
    mLabelF->setColour (TextEditor::textColourId, Colours::black);
    mLabelF->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (mLabelE = new Label ("new label", TRANS ("Effect Gain\n"
                                                                "\n"
                                                                "\n")));
    mLabelE->setFont (Font (15.00f, Font::plain));
    mLabelE->setJustificationType (Justification::centredTop);
    mLabelE->setEditable (false, false, false);
    mLabelE->setColour (TextEditor::textColourId, Colours::black);
    mLabelE->setColour (TextEditor::backgroundColourId, Colour (0x00000000));


    //=========================================================================
    // Sliders
    std::function<String (float)> valToText;
    std::function<float(String)> textToVal;


    // d slider
    addAndMakeVisible (mSliderD = new AudealizeSlider ());
    mSliderD->setSliderStyle (Slider::RotaryVerticalDrag);
    mSliderD->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    mSliderD->setColour (Slider::ColourIds::rotarySliderFillColourId, Colours::lightblue);
    mSliderD->setRange (0.01f, 0.1f);
    mSliderD->setTextValueSuffix (" ms");

    valToText = [](float f) { return String (f * 1000, 1); };

    textToVal = [](String s) { return s.initialSectionContainingOnly ("1234567890.,-").getDoubleValue () * .001; };

    mSliderD->setValueToTextFunction (valToText);
    mSliderD->setTextToValueFunction (textToVal);


    // g slider
    addAndMakeVisible (mSliderG = new AudealizeSlider ());
    mSliderG->setSliderStyle (Slider::RotaryVerticalDrag);
    mSliderG->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    mSliderG->setColour (Slider::ColourIds::rotarySliderFillColourId, Colours::lightblue);
    mSliderG->setRange (0.01f, 0.96f);
    mSliderG->setTextValueSuffix (" %");

    valToText = [](float f) {
        NormalisableRange<float> gRange (0.01f, 0.96f, 0.0001f);
        return String (roundToInt (gRange.convertTo0to1 (f) * 100));
    };

    textToVal = [](String s) {
        NormalisableRange<float> gRange (0.01f, 0.96f, 0.0001f);
        float val = s.initialSectionContainingOnly ("1234567890.,-").getDoubleValue () * .01;
        return gRange.convertFrom0to1 (val);
    };
    mSliderG->setValueToTextFunction (valToText);
    mSliderG->setTextToValueFunction (textToVal);


    // m slider
    addAndMakeVisible (mSliderM = new RotarySliderCentered ());
    mSliderM->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    mSliderM->setColour (Slider::ColourIds::rotarySliderFillColourId, Colours::lightblue);
    mSliderM->setRange (-0.012f, 0.012f);
    mSliderM->setTextValueSuffix (" ms");

    valToText = [](float f) {
        String s = String (f * 1000, 1);
        if (s.equalsIgnoreCase ("-0.0")) return String ("0");  // otherwise it'll display -0.0 at startup
        return s;
    };

    textToVal = [](String s) { return s.initialSectionContainingOnly ("1234567890.,-").getDoubleValue () * .001; };

    mSliderM->setValueToTextFunction (valToText);
    mSliderM->setTextToValueFunction (textToVal);


    // F slider
    addAndMakeVisible (mSliderF = new AudealizeSlider ());
    mSliderF->setSliderStyle (Slider::RotaryVerticalDrag);
    mSliderF->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    mSliderF->setColour (Slider::ColourIds::rotarySliderFillColourId, Colours::lightblue);
    mSliderF->setRange (20, 20000);
    mSliderF->setSkewFactor (.22);
    mSliderF->setValueToTextFunction (freqToText);


    // E slider
    addAndMakeVisible (mSliderE = new AudealizeSlider ());
    mSliderE->setSliderStyle (Slider::RotaryVerticalDrag);
    mSliderE->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    mSliderE->setColour (Slider::ColourIds::rotarySliderFillColourId, Colours::lightblue);
    mSliderE->setRange (0.0f, 1.0f);
    mSliderE->setTextValueSuffix (" %");

    valToText = [](float f) { return String (roundToInt (f * 100)); };

    textToVal = [](String s) { return s.initialSectionContainingOnly ("1234567890.,-").getDoubleValue () * .01; };

    mSliderE->setValueToTextFunction (valToText);
    mSliderE->setTextToValueFunction (textToVal);


    //=========================================================================
    // SliderAttachments

    mSliderAttachmentD =
        new AudioProcessorValueTreeState::SliderAttachment (p.getValueTreeState (), p.getParamID (0), *mSliderD);
    mSliderAttachmentG =
        new AudioProcessorValueTreeState::SliderAttachment (p.getValueTreeState (), p.getParamID (1), *mSliderG);
    mSliderAttachmentM =
        new AudioProcessorValueTreeState::SliderAttachment (p.getValueTreeState (), p.getParamID (2), *mSliderM);
    mSliderAttachmentF =
        new AudioProcessorValueTreeState::SliderAttachment (p.getValueTreeState (), p.getParamID (3), *mSliderF);
    mSliderAttachmentE =
        new AudioProcessorValueTreeState::SliderAttachment (p.getValueTreeState (), p.getParamID (4), *mSliderE);

    setSize (600, 400);
}

ReverbComponent::~ReverbComponent ()
{
    mSliderD = nullptr;
    mSliderG = nullptr;
    mSliderM = nullptr;
    mSliderF = nullptr;
    mSliderE = nullptr;

    mSliderAttachmentD = nullptr;
    mSliderAttachmentG = nullptr;
    mSliderAttachmentM = nullptr;
    mSliderAttachmentF = nullptr;
    mSliderAttachmentE = nullptr;
}

void ReverbComponent::paint (Graphics& g)
{
}

void ReverbComponent::resized ()
{
    Rectangle<int> box (getLocalBounds ());
    box.setWidth (box.getWidth () / 5.);

    mLabelD->setBounds (box);
    box.setY (20);
    box.setHeight (box.getHeight () - 20);
    mSliderD->setBounds (box);
    box.setY (0);
    box.setHeight (box.getHeight () + 20);
    box.setX (box.getRight ());

    mLabelG->setBounds (box);
    box.setY (20);
    box.setHeight (box.getHeight () - 20);
    mSliderG->setBounds (box);
    box.setY (0);
    box.setHeight (box.getHeight () + 20);
    box.setX (box.getRight ());

    mLabelM->setBounds (box);
    box.setY (20);
    box.setHeight (box.getHeight () - 20);
    mSliderM->setBounds (box);
    box.setY (0);
    box.setHeight (box.getHeight () + 20);
    box.setX (box.getRight ());

    mLabelF->setBounds (box);
    box.setY (20);
    box.setHeight (box.getHeight () - 20);
    mSliderF->setBounds (box);
    box.setY (0);
    box.setHeight (box.getHeight () + 20);
    box.setX (box.getRight ());

    mLabelE->setBounds (box);
    box.setY (20);
    box.setHeight (box.getHeight () - 20);
    mSliderE->setBounds (box);
}
}