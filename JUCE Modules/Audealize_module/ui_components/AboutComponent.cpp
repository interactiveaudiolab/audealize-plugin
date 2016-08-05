/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 4.2.3

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright (c) 2015 - ROLI Ltd.

  ==============================================================================
*/

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "AboutComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
AboutComponent::AboutComponent ()
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

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

    drawable1 = Drawable::createFromImageData (iallogo_svg, iallogo_svgSize);

    //[UserPreSize]
    //[/UserPreSize]

    setSize (496, 320);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

AboutComponent::~AboutComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    NSF = nullptr;
    label2 = nullptr;
    audealizeLink = nullptr;
    label3 = nullptr;
    label4 = nullptr;
    labLink = nullptr;
    drawable1 = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void AboutComponent::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::white);

    g.setColour (Colours::black);
    g.fillRect (28, 42, proportionOfWidth (0.3726f), 1);

    g.setColour (Colours::black.withAlpha (0.181f));
    jassert (drawable1 != 0);
    if (drawable1 != 0)
        drawable1->drawWithin (g, Rectangle<float> (276, 28, 184, 160),
                               RectanglePlacement::stretchToFit, 0.181f);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void AboutComponent::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    NSF->setBounds (proportionOfWidth (0.0484f), 294, proportionOfWidth (0.8972f), 56);
    label2->setBounds (proportionOfWidth (0.0484f), 275, proportionOfWidth (0.8992f), 22);
    audealizeLink->setBounds (276, 198, 184, 24);
    label3->setBounds (24, 46, proportionOfWidth (0.4516f), 210);
    label4->setBounds (24, 16, 150, 24);
    labLink->setBounds (249, 222, 240, 24);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void AboutComponent::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == audealizeLink)
    {
        //[UserButtonCode_audealizeLink] -- add your button handler code here..
        //[/UserButtonCode_audealizeLink]
    }
    else if (buttonThatWasClicked == labLink)
    {
        //[UserButtonCode_labLink] -- add your button handler code here..
        //[/UserButtonCode_labLink]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="AboutComponent" componentName=""
                 parentClasses="public Component" constructorParams="" variableInitialisers=""
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="496" initialHeight="320">
  <BACKGROUND backgroundColour="ffffffff">
    <RECT pos="28 42 37.255% 1" fill="solid: ff000000" hasStroke="0"/>
    <IMAGE pos="276 28 184 160" resource="iallogo_svg" opacity="0.18099999999999999423"
           mode="0"/>
  </BACKGROUND>
  <LABEL name="new label" id="5802bd6abc639fa3" memberName="NSF" virtualName=""
         explicitFocusOrder="0" pos="4.839% 294 89.718% 56" edTextCol="ff000000"
         edBkgCol="0" labelText="This work was funded in part by National Science Foundation Grant number IIS-1116384&#10;&#10;"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default sans-serif font" fontsize="11" bold="0" italic="0"
         justification="12"/>
  <LABEL name="new label" id="aebb72c536f9af0e" memberName="label2" virtualName=""
         explicitFocusOrder="0" pos="4.839% 275 89.919% 22" edTextCol="ff000000"
         edBkgCol="0" labelText="&#169; 2016 Interactive Audio Lab, Northwestern University&#10;&#10;"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default sans-serif font" fontsize="11" bold="0" italic="0"
         justification="12"/>
  <HYPERLINKBUTTON name="new hyperlink" id="6c9818dd33edd5cd" memberName="audealizeLink"
                   virtualName="" explicitFocusOrder="0" pos="276 198 184 24" tooltip="https://audealize.appspot.com"
                   buttonText="audealize.appspot.com" connectedEdges="0" needsCallback="1"
                   radioGroupId="0" url="https://audealize.appspot.com"/>
  <LABEL name="new label" id="74df2044109f2871" memberName="label3" virtualName=""
         explicitFocusOrder="0" pos="24 46 45.161% 210" edTextCol="ff000000"
         edBkgCol="0" labelText="Audealize is a new way of looking at audio production tools. Instead of the traditional complex interfaces consisting of knobs with hard-to-understand labels, Audealize provides a semantic interface. Simply describe the type of sound you're looking for in the search boxes, or click and drag around the maps to find new effects.&#10;&#10;This work is developed by the Interactive Audio Lab at Northwestern University."
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default sans-serif font" fontsize="14" bold="0" italic="0"
         justification="9"/>
  <LABEL name="new label" id="1cb7203ac37e2964" memberName="label4" virtualName=""
         explicitFocusOrder="0" pos="24 16 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="What is Audealize?" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default sans-serif font"
         fontsize="18" bold="1" italic="0" justification="33"/>
  <HYPERLINKBUTTON name="new hyperlink" id="ea44cfb854b0fd25" memberName="labLink"
                   virtualName="" explicitFocusOrder="0" pos="249 222 240 24" tooltip="http://music.cs.northwestern.edu"
                   buttonText="music.cs.northwestern.edu" connectedEdges="0" needsCallback="1"
                   radioGroupId="0" url="http://music.cs.northwestern.edu"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif

//==============================================================================
// Binary resources - be careful not to edit any of these sections!

// JUCER_RESOURCE: iallogo_svg, 2987, "../../JUCE Modules/audealize_module/resources/IALlogo.svg"
static const unsigned char resource_AboutComponent_iallogo_svg[] = { 60,63,120,109,108,32,118,101,114,115,105,111,110,61,34,49,46,48,34,32,101,110,99,111,100,105,110,103,61,34,85,84,70,45,56,34,32,115,
116,97,110,100,97,108,111,110,101,61,34,110,111,34,63,62,10,60,115,118,103,32,119,105,100,116,104,61,34,54,56,112,120,34,32,104,101,105,103,104,116,61,34,53,57,112,120,34,32,118,105,101,119,66,111,120,
61,34,48,32,48,32,54,56,32,53,57,34,32,118,101,114,115,105,111,110,61,34,49,46,49,34,32,120,109,108,110,115,61,34,104,116,116,112,58,47,47,119,119,119,46,119,51,46,111,114,103,47,50,48,48,48,47,115,118,
103,34,32,120,109,108,110,115,58,120,108,105,110,107,61,34,104,116,116,112,58,47,47,119,119,119,46,119,51,46,111,114,103,47,49,57,57,57,47,120,108,105,110,107,34,62,10,32,32,32,32,60,33,45,45,32,71,101,
110,101,114,97,116,111,114,58,32,83,107,101,116,99,104,32,51,46,54,46,49,32,40,50,54,51,49,51,41,32,45,32,104,116,116,112,58,47,47,119,119,119,46,98,111,104,101,109,105,97,110,99,111,100,105,110,103,46,
99,111,109,47,115,107,101,116,99,104,32,45,45,62,10,32,32,32,32,60,116,105,116,108,101,62,71,114,111,117,112,60,47,116,105,116,108,101,62,10,32,32,32,32,60,100,101,115,99,62,67,114,101,97,116,101,100,
32,119,105,116,104,32,83,107,101,116,99,104,46,60,47,100,101,115,99,62,10,32,32,32,32,60,100,101,102,115,62,60,47,100,101,102,115,62,10,32,32,32,32,60,103,32,105,100,61,34,80,97,103,101,45,49,34,32,115,
116,114,111,107,101,61,34,110,111,110,101,34,32,115,116,114,111,107,101,45,119,105,100,116,104,61,34,49,34,32,102,105,108,108,61,34,110,111,110,101,34,32,102,105,108,108,45,114,117,108,101,61,34,101,118,
101,110,111,100,100,34,62,10,32,32,32,32,32,32,32,32,60,103,32,105,100,61,34,65,114,116,98,111,97,114,100,45,49,34,32,102,105,108,108,61,34,35,48,48,48,48,48,48,34,62,10,32,32,32,32,32,32,32,32,32,32,
32,32,60,103,32,105,100,61,34,71,114,111,117,112,34,62,10,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,60,112,97,116,104,32,100,61,34,77,54,50,46,55,48,51,53,50,51,50,44,51,50,46,48,54,50,52,51,53,
53,32,76,54,50,46,55,48,51,53,50,51,50,44,50,53,46,50,56,56,56,54,53,53,32,67,54,50,46,55,48,51,53,50,51,50,44,49,49,46,52,56,53,55,55,51,49,32,53,49,46,53,49,48,49,53,51,56,44,48,46,50,56,56,50,51,53,
51,51,49,32,51,55,46,55,48,50,52,51,50,56,44,48,46,50,56,56,50,51,53,51,51,49,32,76,51,48,46,49,51,49,56,49,50,55,44,48,46,50,56,56,50,51,53,51,51,49,32,67,49,54,46,51,49,54,54,57,48,57,44,48,46,50,56,
56,50,51,53,51,51,49,32,53,46,49,51,48,55,50,50,51,53,44,49,49,46,52,56,49,51,57,56,55,32,53,46,49,51,48,55,50,50,51,53,44,50,53,46,50,56,56,56,54,53,53,32,76,53,46,49,51,48,55,50,50,51,53,44,51,50,46,
48,54,50,52,51,53,53,32,76,56,46,53,57,48,48,49,48,50,56,44,51,50,46,48,54,50,52,51,53,53,32,76,56,46,53,57,48,48,49,48,50,56,44,50,52,46,57,49,50,49,54,54,55,32,67,56,46,53,57,48,48,49,48,50,56,44,49,
51,46,51,49,57,53,49,51,56,32,49,55,46,57,57,56,57,54,56,56,44,51,46,57,50,49,56,49,49,55,52,32,50,57,46,53,57,53,50,56,49,51,44,51,46,57,50,49,56,49,49,55,52,32,76,51,56,46,50,51,56,57,54,52,51,44,51,
46,57,50,49,56,49,49,55,52,32,67,52,57,46,56,51,57,56,53,53,49,44,51,46,57,50,49,56,49,49,55,52,32,53,57,46,50,52,52,50,51,53,51,44,49,51,46,51,50,54,56,51,55,50,32,53,57,46,50,52,52,50,51,53,51,44,50,
52,46,57,49,50,49,54,54,55,32,76,53,57,46,50,52,52,50,51,53,51,44,51,50,46,48,54,50,52,51,53,53,32,76,54,50,46,55,48,51,53,50,51,50,44,51,50,46,48,54,50,52,51,53,53,32,90,34,32,105,100,61,34,82,101,99,
116,97,110,103,108,101,45,49,34,62,60,47,112,97,116,104,62,10,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,60,112,97,116,104,32,100,61,34,77,51,52,46,48,48,52,50,52,53,54,44,53,56,46,55,49,49,55,54,
52,55,32,67,52,56,46,49,53,54,49,56,54,49,44,53,56,46,55,49,49,55,54,52,55,32,53,57,46,54,50,56,54,48,48,54,44,52,55,46,50,51,57,51,53,48,50,32,53,57,46,54,50,56,54,48,48,54,44,51,51,46,48,56,55,52,48,
57,55,32,67,53,57,46,54,50,56,54,48,48,54,44,49,56,46,57,51,53,52,54,57,50,32,52,56,46,49,53,54,49,56,54,49,44,55,46,52,54,51,48,53,52,55,50,32,51,52,46,48,48,52,50,52,53,54,44,55,46,52,54,51,48,53,52,
55,50,32,67,49,57,46,56,53,50,51,48,53,49,44,55,46,52,54,51,48,53,52,55,50,32,56,46,51,55,57,56,57,48,54,52,44,49,56,46,57,51,53,52,54,57,50,32,56,46,51,55,57,56,57,48,54,52,44,51,51,46,48,56,55,52,48,
57,55,32,67,56,46,51,55,57,56,57,48,54,52,44,52,55,46,50,51,57,51,53,48,50,32,49,57,46,56,53,50,51,48,53,49,44,53,56,46,55,49,49,55,54,52,55,32,51,52,46,48,48,52,50,52,53,54,44,53,56,46,55,49,49,55,54,
52,55,32,90,32,77,51,52,46,48,48,52,50,52,53,54,44,53,52,46,54,49,49,56,54,55,57,32,67,52,53,46,56,57,49,56,55,53,54,44,53,52,46,54,49,49,56,54,55,57,32,53,53,46,53,50,56,55,48,51,56,44,52,52,46,57,55,
53,48,51,57,55,32,53,53,46,53,50,56,55,48,51,56,44,51,51,46,48,56,55,52,48,57,55,32,67,53,53,46,53,50,56,55,48,51,56,44,50,49,46,49,57,57,55,55,57,55,32,52,53,46,56,57,49,56,55,53,54,44,49,49,46,53,54,
50,57,53,49,53,32,51,52,46,48,48,52,50,52,53,54,44,49,49,46,53,54,50,57,53,49,53,32,67,50,50,46,49,49,54,54,49,53,54,44,49,49,46,53,54,50,57,53,49,53,32,49,50,46,52,55,57,55,56,55,52,44,50,49,46,49,57,
57,55,55,57,55,32,49,50,46,52,55,57,55,56,55,52,44,51,51,46,48,56,55,52,48,57,55,32,67,49,50,46,52,55,57,55,56,55,52,44,52,52,46,57,55,53,48,51,57,55,32,50,50,46,49,49,54,54,49,53,54,44,53,52,46,54,49,
49,56,54,55,57,32,51,52,46,48,48,52,50,52,53,54,44,53,52,46,54,49,49,56,54,55,57,32,90,34,32,105,100,61,34,67,111,109,98,105,110,101,100,45,83,104,97,112,101,34,62,60,47,112,97,116,104,62,10,32,32,32,
32,32,32,32,32,32,32,32,32,32,32,32,32,60,112,97,116,104,32,100,61,34,77,49,49,46,48,50,56,49,55,54,50,44,52,50,46,49,55,48,50,51,52,50,32,67,49,48,46,53,48,49,50,52,52,53,44,52,50,46,50,54,51,55,54,53,
52,32,57,46,57,53,56,56,52,57,57,51,44,52,50,46,51,49,50,53,54,51,55,32,57,46,52,48,53,48,53,55,57,53,44,52,50,46,51,49,50,53,54,51,55,32,67,52,46,51,49,48,50,53,50,55,51,44,52,50,46,51,49,50,53,54,51,
55,32,48,46,49,56,48,48,57,55,48,53,49,44,51,56,46,49,56,50,52,48,56,32,48,46,49,56,48,48,57,55,48,53,49,44,51,51,46,48,56,55,54,48,50,56,32,67,48,46,49,56,48,48,57,55,48,53,49,44,50,55,46,57,57,50,55,
57,55,54,32,52,46,51,49,48,50,53,50,55,51,44,50,51,46,56,54,50,54,52,49,57,32,57,46,52,48,53,48,53,55,57,53,44,50,51,46,56,54,50,54,52,49,57,32,67,57,46,57,53,56,56,52,57,57,51,44,50,51,46,56,54,50,54,
52,49,57,32,49,48,46,53,48,49,50,52,52,53,44,50,51,46,57,49,49,52,52,48,50,32,49,49,46,48,50,56,49,55,54,50,44,50,52,46,48,48,52,57,55,49,52,32,67,57,46,57,55,57,50,52,56,49,55,44,50,54,46,56,50,56,48,
49,52,50,32,57,46,52,48,53,48,53,55,57,53,44,50,57,46,56,56,57,51,56,53,52,32,57,46,52,48,53,48,53,55,57,53,44,51,51,46,48,56,55,54,48,50,56,32,67,57,46,52,48,53,48,53,55,57,53,44,51,54,46,50,56,53,56,
50,48,50,32,57,46,57,55,57,50,52,56,49,55,44,51,57,46,51,52,55,49,57,49,52,32,49,49,46,48,50,56,49,55,54,50,44,52,50,46,49,55,48,50,51,52,50,32,90,34,32,105,100,61,34,79,118,97,108,45,51,34,62,60,47,112,
97,116,104,62,10,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,60,112,97,116,104,32,100,61,34,77,53,55,46,53,55,56,54,53,50,50,44,52,50,46,50,56,56,49,53,49,52,32,67,53,55,46,56,48,49,57,55,49,56,44,
52,50,46,51,48,52,51,51,50,52,32,53,56,46,48,50,55,52,57,53,54,44,52,50,46,51,49,50,53,54,51,55,32,53,56,46,50,53,52,57,52,49,57,44,52,50,46,51,49,50,53,54,51,55,32,67,54,51,46,51,52,57,55,52,55,49,44,
52,50,46,51,49,50,53,54,51,55,32,54,55,46,52,55,57,57,48,50,56,44,51,56,46,49,56,50,52,48,56,32,54,55,46,52,55,57,57,48,50,56,44,51,51,46,48,56,55,54,48,50,56,32,67,54,55,46,52,55,57,57,48,50,56,44,50,
55,46,57,57,50,55,57,55,54,32,54,51,46,51,52,57,55,52,55,49,44,50,51,46,56,54,50,54,52,49,57,32,53,56,46,50,53,52,57,52,49,57,44,50,51,46,56,54,50,54,52,49,57,32,67,53,56,46,48,50,55,52,57,53,54,44,50,
51,46,56,54,50,54,52,49,57,32,53,55,46,56,48,49,57,55,49,56,44,50,51,46,56,55,48,56,55,51,50,32,53,55,46,53,55,56,54,53,50,50,44,50,51,46,56,56,55,48,53,52,50,32,67,53,56,46,54,55,55,53,56,48,54,44,50,
54,46,55,52,50,54,57,50,50,32,53,57,46,50,55,57,57,51,55,54,44,50,57,46,56,52,52,56,48,51,53,32,53,57,46,50,55,57,57,51,55,54,44,51,51,46,48,56,55,54,48,50,56,32,67,53,57,46,50,55,57,57,51,55,54,44,51,
54,46,51,51,48,52,48,50,49,32,53,56,46,54,55,55,53,56,48,54,44,51,57,46,52,51,50,53,49,51,52,32,53,55,46,53,55,56,54,53,50,50,44,52,50,46,50,56,56,49,53,49,52,32,90,34,32,105,100,61,34,79,118,97,108,45,
51,45,67,111,112,121,34,62,60,47,112,97,116,104,62,10,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,60,112,97,116,104,32,100,61,34,77,51,52,44,50,53,46,48,51,55,48,51,55,32,67,51,54,46,50,48,57,49,51,
57,44,50,53,46,48,51,55,48,51,55,32,51,56,44,50,51,46,50,51,55,56,56,53,32,51,56,44,50,49,46,48,49,56,53,49,56,53,32,67,51,56,44,49,56,46,55,57,57,49,53,50,32,51,54,46,50,48,57,49,51,57,44,49,55,32,51,
52,44,49,55,32,67,51,49,46,55,57,48,56,54,49,44,49,55,32,51,48,44,49,56,46,55,57,57,49,53,50,32,51,48,44,50,49,46,48,49,56,53,49,56,53,32,67,51,48,44,50,51,46,50,51,55,56,56,53,32,51,49,46,55,57,48,56,
54,49,44,50,53,46,48,51,55,48,51,55,32,51,52,44,50,53,46,48,51,55,48,51,55,32,90,32,77,51,48,44,50,55,46,51,51,51,51,51,51,51,32,76,51,56,44,50,55,46,51,51,51,51,51,51,51,32,76,51,56,44,52,54,32,76,51,
48,44,52,54,32,76,51,48,44,50,55,46,51,51,51,51,51,51,51,32,90,34,32,105,100,61,34,67,111,109,98,105,110,101,100,45,83,104,97,112,101,34,62,60,47,112,97,116,104,62,10,32,32,32,32,32,32,32,32,32,32,32,
32,60,47,103,62,10,32,32,32,32,32,32,32,32,60,47,103,62,10,32,32,32,32,60,47,103,62,10,60,47,115,118,103,62,0,0};

const char* AboutComponent::iallogo_svg = (const char*) resource_AboutComponent_iallogo_svg;
const int AboutComponent::iallogo_svgSize = 2987;


//[EndFile] You can add extra defines here...
//[/EndFile]
