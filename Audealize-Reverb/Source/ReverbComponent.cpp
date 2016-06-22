#include "ReverbComponent.h"

//==============================================================================
ReverbComponent::ReverbComponent (AudealizereverbAudioProcessor& p) : processor(p)
{
    //=========================================================================
    // Labels
    
    addAndMakeVisible (mLabelD = new Label ("new label",
                                          TRANS("Comb Delay")));
    mLabelD->setFont (Font (15.00f, Font::plain));
    mLabelD->setJustificationType (Justification::centredTop);
    mLabelD->setEditable (false, false, false);
    mLabelD->setColour (TextEditor::textColourId, Colours::black);
    mLabelD->setColour (TextEditor::backgroundColourId, Colour (0x00000000));
    
    addAndMakeVisible (mLabelG = new Label ("new label",
                                           TRANS("Comb Gain\n")));
    mLabelG->setFont (Font (15.00f, Font::plain));
    mLabelG->setJustificationType (Justification::centredTop);
    mLabelG->setEditable (false, false, false);
    mLabelG->setColour (TextEditor::textColourId, Colours::black);
    mLabelG->setColour (TextEditor::backgroundColourId, Colour (0x00000000));
    
    addAndMakeVisible (mLabelM = new Label ("new label",
                                           TRANS("Channel Delay\n")));
    mLabelM->setFont (Font (15.00f, Font::plain));
    mLabelM->setJustificationType (Justification::centredTop);
    mLabelM->setEditable (false, false, false);
    mLabelM->setColour (TextEditor::textColourId, Colours::black);
    mLabelM->setColour (TextEditor::backgroundColourId, Colour (0x00000000));
    
    addAndMakeVisible (mLabelF = new Label ("new label",
                                           TRANS("Cutoff\n"
                                                 "\n")));
    mLabelF->setFont (Font (15.00f, Font::plain));
    mLabelF->setJustificationType (Justification::centredTop);
    mLabelF->setEditable (false, false, false);
    mLabelF->setColour (TextEditor::textColourId, Colours::black);
    mLabelF->setColour (TextEditor::backgroundColourId, Colour (0x00000000));
    
    addAndMakeVisible (mLabelE = new Label ("new label",
                                           TRANS("Effect Gain\n"
                                                 "\n"
                                                 "\n")));
    mLabelE->setFont (Font (15.00f, Font::plain));
    mLabelE->setJustificationType (Justification::centredTop);
    mLabelE->setEditable (false, false, false);
    mLabelE->setColour (TextEditor::textColourId, Colours::black);
    mLabelE->setColour (TextEditor::backgroundColourId, Colour (0x00000000));
    
    addAndMakeVisible (mLabelMix = new Label ("new label",
                                           TRANS("Mix\n"
                                                 "\n"
                                                 "\n"
                                                 "\n")));
    mLabelMix->setFont (Font (15.00f, Font::plain));
    mLabelMix->setJustificationType (Justification::centredTop);
    mLabelMix->setEditable (false, false, false);
    mLabelMix->setColour (TextEditor::textColourId, Colours::black);
    mLabelMix->setColour (TextEditor::backgroundColourId, Colour (0x00000000));
    
    
    //=========================================================================
    // Sliders
    
    addAndMakeVisible (mSliderD = new Slider ("mSliderD"));
    mSliderD->setTooltip (TRANS("Delay of comb filters"));
    mSliderD->setRange (0, 10, 0);
    mSliderD->setSliderStyle (Slider::RotaryVerticalDrag);
    mSliderD->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    
    addAndMakeVisible (mSliderG = new Slider ("mSliderG"));
    mSliderG->setTooltip (TRANS("Gain of comb filters"));
    mSliderG->setRange (0, 10, 0);
    mSliderG->setSliderStyle (Slider::RotaryVerticalDrag);
    mSliderG->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    
    addAndMakeVisible (mSliderM = new Slider ("mSliderM"));
    mSliderM->setTooltip (TRANS("Delay between channels"));
    mSliderM->setRange (0, 10, 0);
    mSliderM->setSliderStyle (Slider::RotaryVerticalDrag);
    mSliderM->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    
    addAndMakeVisible (mSliderF = new Slider ("mSliderF"));
    mSliderF->setTooltip (TRANS("Cutoff frequency"));
    mSliderF->setRange (0, 10, 0);
    mSliderF->setSliderStyle (Slider::RotaryVerticalDrag);
    mSliderF->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    
    addAndMakeVisible (mSliderE = new Slider ("mSliderE"));
    mSliderE->setTooltip (TRANS("Effect Gain"));
    mSliderE->setRange (0, 10, 0);
    mSliderE->setSliderStyle (Slider::RotaryVerticalDrag);
    mSliderE->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    
    addAndMakeVisible (mSliderMix = new Slider ("mSliderMix"));
    mSliderMix->setTooltip (TRANS("Mix\n"));
    mSliderMix->setRange (0, 10, 0);
    mSliderMix->setSliderStyle (Slider::RotaryVerticalDrag);
    mSliderMix->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    
    //=========================================================================
    // SliderAttachments
    mSliderAttachmentD = new AudioProcessorValueTreeState::SliderAttachment(p.getValueTreeState(), p.paramD, *mSliderD);
    mSliderAttachmentG = new AudioProcessorValueTreeState::SliderAttachment(p.getValueTreeState(), p.paramG, *mSliderG);
    mSliderAttachmentM = new AudioProcessorValueTreeState::SliderAttachment(p.getValueTreeState(), p.paramM, *mSliderM);
    mSliderAttachmentF = new AudioProcessorValueTreeState::SliderAttachment(p.getValueTreeState(), p.paramF, *mSliderF);
    mSliderAttachmentE = new AudioProcessorValueTreeState::SliderAttachment(p.getValueTreeState(), p.paramE, *mSliderE);
    mSliderAttachmentMix = new AudioProcessorValueTreeState::SliderAttachment(p.getValueTreeState(), p.paramMix, *mSliderMix);
    
    setSize (600, 400);
}

ReverbComponent::~ReverbComponent()
{
    mSliderD = nullptr;
    mSliderG = nullptr;
    mSliderM = nullptr;
    mSliderF = nullptr;
    mSliderE = nullptr;
    mSliderMix = nullptr;
    
    mSliderAttachmentD = nullptr;
    mSliderAttachmentG = nullptr;
    mSliderAttachmentM = nullptr;
    mSliderAttachmentF = nullptr;
    mSliderAttachmentE = nullptr;
    mSliderAttachmentMix = nullptr;
}

//==============================================================================
void ReverbComponent::paint (Graphics& g)
{
    g.fillAll (Colours::white);
}

void ReverbComponent::resized()
{
    Rectangle<int> box (getLocalBounds());
    box.setWidth(box.getWidth() / 6.);
    mSliderD->setBounds (box);
    mLabelD->setBounds (box);
    box.setX(box.getRight());
    mSliderG->setBounds (box);
    mLabelG->setBounds (box);
    box.setX(box.getRight());
    mSliderM->setBounds (box);
    mLabelM->setBounds (box);
    box.setX(box.getRight());
    mSliderF->setBounds (box);
    mLabelF->setBounds (box);
    box.setX(box.getRight());
    mSliderE->setBounds (box);
    mLabelE->setBounds (box);
    box.setX(box.getRight());
    mSliderMix->setBounds (box);
    mLabelMix->setBounds (box);
    box.setX(box.getRight());
}
