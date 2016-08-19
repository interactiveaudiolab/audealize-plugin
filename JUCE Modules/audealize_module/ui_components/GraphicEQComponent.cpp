
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
            mGainSliders[i]->addListener(this);
            mGainSliders[i]->setRange(gainRange.getRange().getStart(), gainRange.getRange().getEnd());
            String tooltip = freqToText(mFreqs[i]);
            mGainSliders[i]->setTooltip(tooltip);
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
        int midpoint = mGainSliders[0]->getY() + mGainSliders[0]->getHeight() / 2;
        for (int i = 0; i < NUMBANDS - 1; i++){
            int x1 = mGainSliders[i]->getRight();
            int x2 = mGainSliders[i+1]->getX();
            g.setColour(findColour(GraphicEQComponent::tickMarkColourId));
            g.drawLine(x1 - 1, midpoint, x2 + 1, midpoint, 2);
        }
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
        
    void GraphicEQComponent::sliderValueChanged	(Slider* slider) {
        for (int i = 0; i < mNumBands; ++i){
            if (mGainSliders[i] == slider){
                mGainSliders[i]->setTooltip(freqToText(mFreqs[i]) + ": " + String (slider->getValue(), 2) + " dB");
                return;
            }
        }
    }
    
    
    
}