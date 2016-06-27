#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
AudealizeeqAudioProcessorEditor::AudealizeeqAudioProcessorEditor (AudealizeeqAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    mEqualizerComponent = new GraphicEQComponent(processor, NUMBANDS);
    //addAndMakeVisible(mEqualizerComponent);
    
    mWordMap = new WordMap(p, PATH_TO_POINTS);
    addAndMakeVisible(mWordMap);
    
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (800, 400);
}

AudealizeeqAudioProcessorEditor::~AudealizeeqAudioProcessorEditor()
{
    mEqualizerComponent = nullptr;
    mWordMap = nullptr;
}

//==============================================================================
void AudealizeeqAudioProcessorEditor::paint (Graphics& g)
{
    g.fillAll (Colours::white);
    
    g.setColour (Colours::white);
}

void AudealizeeqAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    Rectangle<int> box (getLocalBounds());
    //mEqualizerComponent->setBounds(box);
    mWordMap->setBounds(box);
}

