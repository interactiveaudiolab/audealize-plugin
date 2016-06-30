/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 4.2.1

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright (c) 2015 - ROLI Ltd.

  ==============================================================================
*/

#ifndef __JUCE_HEADER_EB0317DAAAA56B94__
#define __JUCE_HEADER_EB0317DAAAA56B94__

//[Headers]     -- You can add your own extra header files here --
#include "../JuceLibraryCode/JuceHeader.h"
#include <fstream>
#include "WordMap.h"

namespace Audealize{
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    A container component that creates the full Audealize plugin UI
                                                                    //[/Comments]
*/
class AudealizeUI  : public AudioProcessorEditor,
                     public TextEditorListener,
                     public SliderListener,
                     public ButtonListener
{
public:
    //==============================================================================
    AudealizeUI (AudealizeAudioProcessor& p, ScopedPointer<TraditionalUI> t, String pathToPoints, String effectType);
    ~AudealizeUI();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    void textEditorReturnKeyPressed(TextEditor &editor) override;

    void languageAlert();
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;
    void sliderValueChanged (Slider* sliderThatWasMoved) override;
    void buttonClicked (Button* buttonThatWasClicked) override;
    void lookAndFeelChanged() override;
    void childrenChanged() override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    AudealizeAudioProcessor& processor;
    String mPathToPoints;

    ScopedPointer<NativeMessageBox> mAlertBox;
    ScopedPointer<Audealize::TraditionalUI> mTradUI;
    const String TYPEFACE = "Helvetica";

    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> mAmountSliderAttachment;
    
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<Component> component;
    ScopedPointer<Audealize::WordMap> mWordMap;
    ScopedPointer<Slider> mAmountSlider;
    ScopedPointer<Label> label;
    ScopedPointer<Label> label2;
    ScopedPointer<ToggleButton> mEnglishButton;
    ScopedPointer<ToggleButton> mEspanolButton;
    ScopedPointer<TextEditor> mSearchBar;
    ScopedPointer<Label> mAudealizeLabel;
    ScopedPointer<Label> mEffectTypeLabel;
    ScopedPointer<TextButton> mTradUIButton;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudealizeUI)
};

//[EndFile] You can add extra defines here...
}
//[/EndFile]

#endif   // __JUCE_HEADER_EB0317DAAAA56B94__
