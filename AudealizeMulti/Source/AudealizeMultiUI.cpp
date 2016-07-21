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

#include "AudealizeMultiUI.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
TabbedMenuBar::TabbedMenuBar (AudealizeAudioProcessor& p, vector<ScopedPointer<AudealizeUI>> AudealizeUIs)
    : AudioProcessorEditor(&p), mAudealizeUIs(AudealizeUIs)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    addAndMakeVisible (mTabbedComponent = new TabbedComponent (TabbedButtonBar::TabsAtTop));
    mTabbedComponent->setTabBarDepth (28);
    mTabbedComponent->addTab (TRANS("EQ"), Colours::white, new AudealizeUI (mAudealizeUIs[0]), true);
    mTabbedComponent->addTab (TRANS("Reverb"), Colours::white, new AudealizeUI (mAudealizeUIs[1]), true);
    mTabbedComponent->setCurrentTabIndex (0);

    addAndMakeVisible (label = new Label ("new label",
                                          TRANS("Audealize\n")));
    label->setFont (Font ("Helvetica", 28.00f, Font::plain));
    label->setJustificationType (Justification::centredLeft);
    label->setEditable (false, false, false);
    label->setColour (TextEditor::textColourId, Colours::black);
    label->setColour (TextEditor::backgroundColourId, Colour (0x00000000));


    //[UserPreSize]
    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

TabbedMenuBar::~TabbedMenuBar()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    mTabbedComponent = nullptr;
    label = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void TabbedMenuBar::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::white);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void TabbedMenuBar::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    mTabbedComponent->setBounds (0, 44, getWidth() - 0, getHeight() - 44);
    label->setBounds (8, 8, 152, 32);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="TabbedMenuBar" componentName=""
                 parentClasses="public Component, public AudioProcessorEditor"
                 constructorParams="AudealizeAudioProcessor&amp; p, vector&lt;ScopedPointer&lt;AudealizeUI&gt;&gt; AudealizeUIs"
                 variableInitialisers="AudioProcessorEditor(&amp;p), mAudealizeUIs(AudealizeUIs)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="600" initialHeight="400">
  <BACKGROUND backgroundColour="ffffffff"/>
  <TABBEDCOMPONENT name="Effect Select" id="2c201af9ffdf5533" memberName="mTabbedComponent"
                   virtualName="" explicitFocusOrder="0" pos="0 44 0M 44M" orientation="top"
                   tabBarDepth="28" initialTab="0">
    <TAB name="EQ" colour="ffffffff" useJucerComp="0" contentClassName="AudealizeUI"
         constructorParams="mAudealizeUIs[0]" jucerComponentFile=""/>
    <TAB name="Reverb" colour="ffffffff" useJucerComp="0" contentClassName="AudealizeUI"
         constructorParams="mAudealizeUIs[1]" jucerComponentFile=""/>
  </TABBEDCOMPONENT>
  <LABEL name="new label" id="f1105aba3ed6efbd" memberName="label" virtualName=""
         explicitFocusOrder="0" pos="8 8 152 32" edTextCol="ff000000"
         edBkgCol="0" labelText="Audealize&#10;" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Helvetica"
         fontsize="28" bold="0" italic="0" justification="33"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
