#include "ReverbComponent.h"

String ReverbComponent::paramD ("CombDelay");
String ReverbComponent::paramG ("CombGain");
String ReverbComponent::paramM ("ChannelDelay");
String ReverbComponent::paramF ("f");
String ReverbComponent::paramE ("E");
String ReverbComponent::paramWetDry ("Wet/Dry");


//==============================================================================
ReverbComponent::ReverbComponent (AudealizeAudioProcessor& p) : processor(p)
{
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
    mSliderAttachmentD = new AudioProcessorValueTreeState::SliderAttachment(p.getValueTreeState(), paramD, *mSliderD);
    mSliderAttachmentG = new AudioProcessorValueTreeState::SliderAttachment(p.getValueTreeState(), paramG, *mSliderG);
    mSliderAttachmentM = new AudioProcessorValueTreeState::SliderAttachment(p.getValueTreeState(), paramM, *mSliderM);
    mSliderAttachmentF = new AudioProcessorValueTreeState::SliderAttachment(p.getValueTreeState(), paramF, *mSliderF);
    mSliderAttachmentE = new AudioProcessorValueTreeState::SliderAttachment(p.getValueTreeState(), paramE, *mSliderE);
    mSliderAttachmentMix = new AudioProcessorValueTreeState::SliderAttachment(p.getValueTreeState(), paramWetDry, *mSliderMix);
    
    p.getValueTreeState().addParameterListener(paramD, this);
    p.getValueTreeState().addParameterListener(paramG, this);
    p.getValueTreeState().addParameterListener(paramM, this);
    p.getValueTreeState().addParameterListener(paramF, this);
    p.getValueTreeState().addParameterListener(paramE, this);
    p.getValueTreeState().addParameterListener(paramWetDry, this);

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
    box.setX(box.getRight());
    mSliderG->setBounds (box);
    box.setX(box.getRight());
    mSliderM->setBounds (box);
    box.setX(box.getRight());
    mSliderF->setBounds (box);
    box.setX(box.getRight());
    mSliderE->setBounds (box);
    box.setX(box.getRight());
    mSliderMix->setBounds (box);
    box.setX(box.getRight());
}

void ReverbComponent::parameterChanged(const juce::String &parameterID, float newValue){
    processor.parameterChanged(parameterID);    
}
