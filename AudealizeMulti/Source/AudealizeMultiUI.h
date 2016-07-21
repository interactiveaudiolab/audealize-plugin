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

#ifndef __JUCE_HEADER_6E32A24B25A51A81__
#define __JUCE_HEADER_6E32A24B25A51A81__

//[Headers]     -- You can add your own extra header files here --
#include "../JuceLibraryCode/JuceHeader.h"

using std::vector;
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class TabbedMenuBar  : public Component,
                       public AudioProcessorEditor
{
public:
    //==============================================================================
    TabbedMenuBar (AudealizeAudioProcessor& p, vector<ScopedPointer<AudealizeUI>> AudealizeUIs);
    ~TabbedMenuBar();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    vector<ScopedPointer<AudealizeUI>> mAudealizeUIs
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<TabbedComponent> mTabbedComponent;
    ScopedPointer<Label> label;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TabbedMenuBar)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_6E32A24B25A51A81__
