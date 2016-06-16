
#include "GraphicEQComponent.h"

using std::vector;
using std::to_string;
GraphicEQComponent::GraphicEQComponent (AudealizeAudioProcessor& p, int numBands) : processor(p), mGainSliders(numBands), mGainSliderAttachment(numBands), mGainListener(numBands)
{
    mNumBands = numBands;
    
    for (int i = 0; i < mNumBands; i++){
        String paramID = "paramGain" + to_string(i);
        
        mGainSliders[i] = new Slider (Slider::LinearVertical, Slider::TextBoxBelow);
        addAndMakeVisible(mGainSliders[i]);
        
        mGainSliderAttachment[i] = new AudioProcessorValueTreeState::SliderAttachment (p.getValueTreeState(), paramID, *mGainSliders[i]);
        
        p.getValueTreeState().addParameterListener(paramID, this);
    }
    
    setSize (400, 200);
}

GraphicEQComponent::~GraphicEQComponent()
{
    for (int i = 0; i < mNumBands; i++){
        mGainSliders[i] = nullptr;
        mGainSliderAttachment[i] = nullptr;
        mGainListener[i] = nullptr;
    }
}

void GraphicEQComponent::paint (Graphics& g)
{
    g.fillAll (Colours::white);
}

void GraphicEQComponent::resized()
{
    Rectangle<int> box (getLocalBounds());
    box.setWidth(box.getWidth() / 40.);
    for (int i = 0; i < mNumBands; i++){
        mGainSliders[i]->setBounds(box);
        box.setX(box.getRight());
    }
}

void GraphicEQComponent::parameterChanged(const juce::String &parameterID, float newValue){
    processor.parameterChanged(parameterID);
}
