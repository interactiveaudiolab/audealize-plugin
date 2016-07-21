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

#ifndef __JUCE_HEADER_2C6B94272375A9F2__
#define __JUCE_HEADER_2C6B94272375A9F2__

//[Headers]     -- You can add your own extra header files here --
#include "../JuceLibraryCode/JuceHeader.h"

using std::vector;
using namespace Audealize;
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class AudealizeMultiUI  : public AudioProcessorEditor, public ButtonListener
{
public:
    //==============================================================================
    AudealizeMultiUI (AudioProcessor& p, vector<ScopedPointer<AudealizeUI>> AudealizeUIs);
    ~AudealizeMultiUI();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;
    void childrenChanged() override;

    void buttonClicked (Button* buttonThatWasClicked) override;
    
private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    vector<ScopedPointer<AudealizeUI>> mAudealizeUIs;

    ScopedPointer<ResizableCornerComponent> mResizer; // handles resizing of the plugin window
    ScopedPointer<ComponentBoundsConstrainer> mResizeLimits; // sets size limits for the plugin window
    
    bool hasBeenPainted;
    int prevChildHeight;
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<TabbedComponent> mTabbedComponent;
    ScopedPointer<Label> label;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudealizeMultiUI)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_2C6B94272375A9F2__
