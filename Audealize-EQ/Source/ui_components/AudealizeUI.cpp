#include "AudealizeUI.h"

using namespace std;

AudealizeUI::AudealizeUI (AudealizeAudioProcessor& p, String pathToPoints) : processor(p), mPathToPoints(pathToPoints)
{
    //Load file with points, parse into nlohman::json object
    ifstream infile;
    infile.open(mPathToPoints.toUTF8());
    mPoints = json::parse(infile);
    
    
    addAndMakeVisible (mMap = new Component());
    mMap->setName ("Descriptor Map");

    addAndMakeVisible (textEditor = new TextEditor ("new text editor"));
    textEditor->setMultiLine (false);
    textEditor->setReturnKeyStartsNewLine (false);
    textEditor->setReadOnly (false);
    textEditor->setScrollbarsShown (true);
    textEditor->setCaretVisible (true);
    textEditor->setPopupMenuEnabled (true);
    textEditor->setColour (TextEditor::outlineColourId, Colours::green);
    textEditor->setColour (TextEditor::shadowColourId, Colour (0x00a1a1a1));
    textEditor->setText (String());


    setSize (600, 400);
}

AudealizeUI::~AudealizeUI()
{
    mMap = nullptr;
    textEditor = nullptr;
}

//==============================================================================
void AudealizeUI::paint (Graphics& g)
{
    g.fillAll (Colours::white);
}

void AudealizeUI::resized()
{
    mMap->setBounds (0, 0, 616, 400);
    textEditor->setBounds (8, 8, 150, 24);
}

void AudealizeUI::mouseMove (const MouseEvent& e)
{
}

void AudealizeUI::mouseEnter (const MouseEvent& e)
{
}

void AudealizeUI::mouseDown (const MouseEvent& e)
{
}

void AudealizeUI::mouseDrag (const MouseEvent& e)
{
}


