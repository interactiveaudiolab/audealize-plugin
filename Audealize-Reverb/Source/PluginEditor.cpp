#include "PluginProcessor.h"
#include "PluginEditor.h"


AudealizereverbAudioProcessorEditor::AudealizereverbAudioProcessorEditor (AudealizereverbAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    mReverbComponent = new ReverbComponent(processor);
    addAndMakeVisible(mReverbComponent);
    
    setSize (420, 120);
}

AudealizereverbAudioProcessorEditor::~AudealizereverbAudioProcessorEditor()
{
}

//==============================================================================
void AudealizereverbAudioProcessorEditor::paint (Graphics& g)
{
    g.fillAll (Colours::white);

    g.setColour (Colours::black);
    g.setFont (15.0f);
    g.drawFittedText ("Hello World!", getLocalBounds(), Justification::centred, 1);
}

void AudealizereverbAudioProcessorEditor::resized()
{
    Rectangle<int> box (getLocalBounds());
    mReverbComponent->setBounds(box);
}
