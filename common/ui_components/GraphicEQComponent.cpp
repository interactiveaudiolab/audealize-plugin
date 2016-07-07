
#include "GraphicEQComponent.h"

using std::vector;
using std::to_string;

namespace Audealize {
    
    GraphicEQComponent::GraphicEQComponent (AudealizeAudioProcessor& p, int numBands, NormalisableRange<float> gainRange) : TraditionalUI(p), mGainSliders(numBands), mGainSliderAttachment(numBands) //, mGainListener(numBands)
    {
        mNumBands = numBands;
        
        name = "graphic EQ";
        
        for (int i = 0; i < mNumBands; i++){
            String paramID = "paramGain" + to_string(i);
            
            mGainSliders[i] = new Slider (Slider::LinearVertical, Slider::NoTextBox);
            mGainSliders[i]->setRange(gainRange.getRange().getStart(), gainRange.getRange().getEnd());
            addAndMakeVisible(mGainSliders[i]);
            
            mGainSliderAttachment[i] = new AudioProcessorValueTreeState::SliderAttachment (p.getValueTreeState(), paramID, *mGainSliders[i]);
        }
        
        setSize (400, 200);
    }
    
    GraphicEQComponent::~GraphicEQComponent()
    {
        for (int i = 0; i < mNumBands; i++){
            mGainSliders[i] = nullptr;
            mGainSliderAttachment[i] = nullptr;
            //mGainListener[i] = nullptr;
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
    
}