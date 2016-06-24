
#include "GraphicEQComponent.h"

using std::vector;
using std::to_string;
GraphicEQComponent::GraphicEQComponent (AudealizeAudioProcessor& p, int numBands) : TraditionalUIComponent(p, numBands)
{
    mRange = NormalisableRange<float>(-40.0f, 40.0f, .0001);
    mNumBands = numBands;
    
    for (int i = 0; i < mNumBands; i++){
        String paramID = "paramGain" + to_string(i);
        
        mSliders[i] = new Slider (Slider::LinearVertical, Slider::TextBoxBelow);
        addAndMakeVisible(mSliders[i]);
        
        mSliderAttachments[i] = new AudioProcessorValueTreeState::SliderAttachment (p.getValueTreeState(), paramID, *mSliders[i]);
    }
    
    Component::setSize (400, 200);
}

GraphicEQComponent::~GraphicEQComponent()
{
    for (int i = 0; i < mNumBands; i++){
        mSliders[i] = nullptr;
        mSliderAttachments[i] = nullptr;
        mListeners[i] = nullptr;
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
        mSliders[i]->setBounds(box);
        box.setX(box.getRight());
    }
}

void GraphicEQComponent::settingsFromMap(vector<float> settings){
    for (int i = 0; i < mNumParams; i++){
        setSlider(i, settings[i] * 5);
    }
    repaint();
}