#include "AboutComponent.h"

AboutComponent::AboutComponent ()
{
    addAndMakeVisible (NSF = new Label ("new label",
                                        TRANS("This work was funded in part by National Science Foundation Grant number IIS-1116384\n"
                                              "\n")));
    NSF->setFont (Font (Font::getDefaultSansSerifFontName(), 11.00f, Font::plain));
    NSF->setJustificationType (Justification::centredTop);
    NSF->setEditable (false, false, false);
    NSF->setColour (TextEditor::textColourId, Colours::black);
    NSF->setColour (TextEditor::backgroundColourId, Colour (0x00000000));
    
    addAndMakeVisible (label2 = new Label ("new label",
                                           CharPointer_UTF8 ("\xc2\xa9 2016 Interactive Audio Lab, Northwestern University\n"
                                                             "\n")));
    label2->setFont (Font (Font::getDefaultSansSerifFontName(), 11.00f, Font::plain));
    label2->setJustificationType (Justification::centredTop);
    label2->setEditable (false, false, false);
    label2->setColour (TextEditor::textColourId, Colours::black);
    label2->setColour (TextEditor::backgroundColourId, Colour (0x00000000));
    
    addAndMakeVisible (audealizeLink = new HyperlinkButton (TRANS("audealize.appspot.com"),
                                                            URL ("https://audealize.appspot.com")));
    audealizeLink->setTooltip (TRANS("https://audealize.appspot.com"));
    audealizeLink->setButtonText (TRANS("audealize.appspot.com"));
    audealizeLink->addListener (this);
    
    addAndMakeVisible (label3 = new Label ("new label",
                                           TRANS("Audealize is a new way of looking at audio production tools. Instead of the traditional complex interfaces consisting of knobs with hard-to-understand labels, Audealize provides a semantic interface. Simply describe the type of sound you\'re looking for in the search boxes, or click and drag around the maps to find new effects.\n"
                                                 "\n"
                                                 "This work is developed by the Interactive Audio Lab at Northwestern University.")));
    label3->setFont (Font (Font::getDefaultSansSerifFontName(), 14.00f, Font::plain));
    label3->setJustificationType (Justification::topLeft);
    label3->setEditable (false, false, false);
    label3->setColour (TextEditor::textColourId, Colours::black);
    label3->setColour (TextEditor::backgroundColourId, Colour (0x00000000));
    
    addAndMakeVisible (label4 = new Label ("new label",
                                           TRANS("What is Audealize?")));
    label4->setFont (Font (Font::getDefaultSansSerifFontName(), 18.00f, Font::bold));
    label4->setJustificationType (Justification::centredLeft);
    label4->setEditable (false, false, false);
    label4->setColour (TextEditor::textColourId, Colours::black);
    label4->setColour (TextEditor::backgroundColourId, Colour (0x00000000));
    
    addAndMakeVisible (labLink = new HyperlinkButton (TRANS("music.cs.northwestern.edu"),
                                                      URL ("http://music.cs.northwestern.edu")));
    labLink->setTooltip (TRANS("http://music.cs.northwestern.edu"));
    labLink->setButtonText (TRANS("music.cs.northwestern.edu"));
    labLink->addListener (this);
    
    drawable1 = Drawable::createFromImageData (AudealizeImages::iallogo_svg, AudealizeImages::iallogo_svgSize);
    
    setSize (496, 320);
}

AboutComponent::~AboutComponent()
{
    NSF = nullptr;
    label2 = nullptr;
    audealizeLink = nullptr;
    label3 = nullptr;
    label4 = nullptr;
    labLink = nullptr;
    drawable1 = nullptr;
}

//==============================================================================
void AboutComponent::paint (Graphics& g)
{
    g.fillAll (findColour(AboutComponent::backgroundColourId));
    
    g.setColour (findColour(AboutComponent::textColourId));
    g.fillRect (28, 42, proportionOfWidth (0.3726f), 1);
    
    g.setColour (Colours::black.withAlpha (0.181f));
    jassert (drawable1 != 0);
    if (drawable1 != 0)
        drawable1->drawWithin (g, Rectangle<float> (276, 28, 184, 160),
                               RectanglePlacement::stretchToFit, 0.181f);
}

void AboutComponent::resized()
{
    NSF->setBounds (proportionOfWidth (0.0484f), 294, proportionOfWidth (0.8972f), 56);
    label2->setBounds (proportionOfWidth (0.0484f), 275, proportionOfWidth (0.8992f), 22);
    audealizeLink->setBounds (276, 198, 184, 24);
    label3->setBounds (24, 46, proportionOfWidth (0.4516f), 210);
    label4->setBounds (24, 16, 150, 24);
    labLink->setBounds (249, 222, 240, 24);
}

void AboutComponent::buttonClicked (Button* buttonThatWasClicked)
{
    if (buttonThatWasClicked == audealizeLink)
    {
    }
    else if (buttonThatWasClicked == labLink)
    {
    }
}