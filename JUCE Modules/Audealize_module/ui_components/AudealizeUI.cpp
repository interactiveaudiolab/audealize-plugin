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

#include "AudealizeUI.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
using namespace std;
using json = nlohmann::json;

namespace Audealize{
//[/MiscUserDefs]

//==============================================================================
AudealizeUI::AudealizeUI (AudealizeAudioProcessor& p, ScopedPointer<TraditionalUI> t, String pathToPoints, String effectType)
    : AudioProcessorEditor(&p), processor(p), mPathToPoints(pathToPoints), mTradUI(t)
{
    //[Constructor_pre] You can add your own custom stuff here..
    // Load file with descriptors, parse into nlohman::json object
    ifstream infile;
    infile.open(mPathToPoints.toUTF8());
    json descriptors = json::parse(infile);
    //[/Constructor_pre]

    addAndMakeVisible (component = new Component());
    component->setName ("new component");

    addAndMakeVisible (mWordMap = new Audealize::WordMap (p, descriptors));
    mWordMap->setName ("Descriptor Map");

    addAndMakeVisible (mAmountSlider = new Slider ("Amount"));
    mAmountSlider->setRange (0, 10, 0);
    mAmountSlider->setSliderStyle (Slider::LinearHorizontal);
    mAmountSlider->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    mAmountSlider->addListener (this);

    addAndMakeVisible (label = new Label ("new label",
                                          TRANS("Less\n")));
    label->setFont (Font (16.00f, Font::plain));
    label->setJustificationType (Justification::centredLeft);
    label->setEditable (false, false, false);
    label->setColour (TextEditor::textColourId, Colours::black);
    label->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label2 = new Label ("new label",
                                           TRANS("More\n")));
    label2->setFont (Font (16.00f, Font::plain));
    label2->setJustificationType (Justification::centredLeft);
    label2->setEditable (false, false, false);
    label2->setColour (TextEditor::textColourId, Colours::black);
    label2->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (mEnglishButton = new ToggleButton ("English"));
    mEnglishButton->addListener (this);
    mEnglishButton->setToggleState (true, dontSendNotification);

    addAndMakeVisible (mEspanolButton = new ToggleButton (CharPointer_UTF8 ("Espa\xc3\xb1ol")));
    mEspanolButton->addListener (this);
    mEspanolButton->setToggleState (true, dontSendNotification);

    addAndMakeVisible (mAudealizeLabel = new Label ("Audealize",
                                                    TRANS("Audealize\n")));
    mAudealizeLabel->setFont (Font ("Helvetica", 28, Font::plain));
    mAudealizeLabel->setJustificationType (Justification::topLeft);
    mAudealizeLabel->setEditable (false, false, false);
    mAudealizeLabel->setColour (TextEditor::textColourId, Colours::black);
    mAudealizeLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (mEffectTypeLabel = new Label ("Effect Type",
                                                     TRANS("Type\n")));
    mEffectTypeLabel->setFont (Font ("Helvetica", 28, Font::plain));
    mEffectTypeLabel->setJustificationType (Justification::topLeft);
    mEffectTypeLabel->setEditable (false, false, false);
    mEffectTypeLabel->setColour (Label::textColourId, Colours::black);
    mEffectTypeLabel->setColour (TextEditor::textColourId, Colours::black);
    mEffectTypeLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (mTradUIButton = new TextButton ("new button"));
    mTradUIButton->setButtonText (TRANS("+ Show traditional interface"));
    mTradUIButton->addListener (this);

    addAndMakeVisible (mSearchBar = new TypeaheadEditor());
    mSearchBar->setName ("Search Bar");


    //[UserPreSize]
    mSearchBar->getEditor()->addListener(this);
    mSearchBar->setColour (TextEditor::outlineColourId, Colours::grey);
    mSearchBar->setColour(TextEditor::ColourIds::focusedOutlineColourId, Colours::lightblue);
    mSearchBar->setColour (TextEditor::shadowColourId, Colour (0x00a1a1a1));
    mSearchBar->getEditor()->setFont(Font(TYPEFACE, 18, Font::plain));
    mSearchBar->getEditor()->setSelectAllWhenFocused(true);
    mSearchBar->getEditor()->setTextToShowWhenEmpty("Search for a word to apply", Colour (0xff888888));
    mSearchBar->setOptions(mWordMap->getWords());

    mEffectTypeLabel->setText(effectType, NotificationType::dontSendNotification);

    mWordMap->setBroughtToFrontOnMouseClick(true);
    mWordMap->addActionListener(mSearchBar);
    mWordMap->addActionListener(this);

    addAndMakeVisible(mTradUI);
    mTradUI->setVisible(false);

    mTradUIButton->setButtonText (TRANS("+ Show " + String(mTradUI->getName())));
    
    mAmountSlider->setRange(0.0f, 1.0f);
    mAmountSliderAttachment = new AudioProcessorValueTreeState::SliderAttachment (p.getValueTreeState(), p.paramAmount, *mAmountSlider);

    mResizeLimits = new ComponentBoundsConstrainer();
    mResizeLimits->setSizeLimits (600, 400, 1180, 800);
    addAndMakeVisible (mResizer = new ResizableCornerComponent (this, mResizeLimits));
    
    isTradUIVisible = false;
    //[/UserPreSize]

    setSize (840, 560);

    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

AudealizeUI::~AudealizeUI()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    mAlertBox = nullptr;
    mAmountSliderAttachment = nullptr;
    mResizer = nullptr;
    mResizeLimits = nullptr;
    //[/Destructor_pre]

    component = nullptr;
    mWordMap = nullptr;
    mAmountSlider = nullptr;
    label = nullptr;
    label2 = nullptr;
    mEnglishButton = nullptr;
    mEspanolButton = nullptr;
    mAudealizeLabel = nullptr;
    mEffectTypeLabel = nullptr;
    mTradUIButton = nullptr;
    mSearchBar = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void AudealizeUI::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::white);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void AudealizeUI::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    mResizer->setBounds (getWidth() - 18, getHeight() - 18, 16, 16);

    //[/UserPreResize]
        
    int fontSizeThresh = 750;
    if (getWidth() <= fontSizeThresh && processor.lastUIWidth > fontSizeThresh) {
        mWordMap->setMinFontSize(10);
    }
    else if (getWidth() > fontSizeThresh && processor.lastUIWidth <= fontSizeThresh) {
        mWordMap->setMinFontSize(12);
    }
    
    component->setBounds (0, 0, 840, 568);
    if (isTradUIVisible){
        mWordMap->setBounds (32, 105, getWidth() - 63, getHeight() - 163 - 130);
        mTradUIButton->setBounds (40, getHeight() - 45 - 130, 208, 24);
            }
    else{
        mWordMap->setBounds (32, 105, getWidth() - 63, getHeight() - 163);
        mTradUIButton->setBounds (40, getHeight() - 45, 208, 24);
    }
    
    int sliderWidth;
    if (getWidth() < 760){
        sliderWidth = getWidth() - 550;
    }
    else {
        sliderWidth = getWidth() * 0.28f;
    }
    mAmountSlider->setBounds (getWidth() - sliderWidth - 72, 65, sliderWidth, 24);
    label->setBounds (getWidth() - sliderWidth - 108, 65, 40, 24);
    label2->setBounds (getWidth() - 72, 65, 56, 24);
    mEnglishButton->setBounds (288, 65, 72, 24);
    mEspanolButton->setBounds (360, 65, 80, 24);
    mAudealizeLabel->setBounds (27, 22, 176, 32);
    mEffectTypeLabel->setBounds (150, 22, 118, 32);
    mSearchBar->setBounds (32, 60, 240, 32);
    //[UserResized] Add your own custom resize handling here..
    mTradUI->setBounds(38, getHeight() - 140, getWidth()-63, 120);
    
    processor.lastUIWidth = getWidth();
    processor.lastUIHeight = getHeight();
    //[/UserResized]
}

void AudealizeUI::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == mAmountSlider)
    {
        //[UserSliderCode_mAmountSlider] -- add your slider handling code here..
        //[/UserSliderCode_mAmountSlider]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}

void AudealizeUI::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    if (!mEspanolButton->getToggleState() && !mEnglishButton->getToggleState()){
        languageAlert();
        buttonThatWasClicked->setToggleState(true, NotificationType::sendNotification);
    }

    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == mEnglishButton)
    {
        //[UserButtonCode_mEnglishButton] -- add your button handler code here..
        mWordMap->toggleLanguage("English", mEnglishButton->getToggleState());
        //[/UserButtonCode_mEnglishButton]
    }
    else if (buttonThatWasClicked == mEspanolButton)
    {
        //[UserButtonCode_mEspanolButton] -- add your button handler code here..
        mWordMap->toggleLanguage("Español", mEspanolButton->getToggleState());
        //[/UserButtonCode_mEspanolButton]
    }
    else if (buttonThatWasClicked == mTradUIButton)
    {
        //[UserButtonCode_mTradUIButton] -- add your button handler code here..
        if(mTradUI->isVisible()){
            isTradUIVisible = false;
            setSize(getWidth(), getHeight()-mTradUI->getHeight()-10);
            mTradUI->setVisible(false);
            mTradUIButton->setButtonText (TRANS("+ Show " + String(mTradUI->getName())));
            mResizeLimits->setSizeLimits (600, 400, 1180, 800);
            
        }
        else{
            isTradUIVisible = true;
            setSize(getWidth(), getHeight()+mTradUI->getHeight()+10);
            mTradUI->setVisible(true);
            mTradUIButton->setButtonText (TRANS("- Hide " + String(mTradUI->getName())));
            mResizeLimits->setSizeLimits (600, 400 + mTradUI->getHeight() + 10, 1180, 800 + mTradUI->getHeight() + 10);
            
        }

        //[/UserButtonCode_mTradUIButton]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}

void AudealizeUI::lookAndFeelChanged()
{
    //[UserCode_lookAndFeelChanged] -- Add your code here...
    //[/UserCode_lookAndFeelChanged]
}

void AudealizeUI::childrenChanged()
{
    //[UserCode_childrenChanged] -- Add your code here...
    //[/UserCode_childrenChanged]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void AudealizeUI::textEditorReturnKeyPressed(TextEditor &editor){
    String text = editor.getText();
    if (!mWordMap->searchMap(text)){
        editor.setText("Word not found!");
        editor.selectAll();
    }
}

void AudealizeUI::languageAlert(){
    mAlertBox->showMessageBox(AlertWindow::AlertIconType::WarningIcon, "At least one language must be selected!", "");
}

void AudealizeUI::actionListenerCallback(const String &message){
    if (message.equalsIgnoreCase("_languagechanged")){
        mSearchBar->setOptions(mWordMap->getWords());
    }
}
    
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="AudealizeUI" componentName=""
                 parentClasses="public AudioProcessorEditor, public TextEditorListener, public ActionListener, public KeyListener"
                 constructorParams="AudealizeAudioProcessor&amp; p, ScopedPointer&lt;TraditionalUI&gt; t, String pathToPoints, String effectType"
                 variableInitialisers="AudioProcessorEditor(&amp;p), processor(p), mPathToPoints(pathToPoints), mTradUI(t)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="840" initialHeight="575">
  <METHODS>
    <METHOD name="lookAndFeelChanged()"/>
    <METHOD name="childrenChanged()"/>
  </METHODS>
  <BACKGROUND backgroundColour="ffffffff"/>
  <GENERICCOMPONENT name="new component" id="9c0130f371d10f60" memberName="component"
                    virtualName="" explicitFocusOrder="0" pos="0 0 840 568" class="Component"
                    params=""/>
  <GENERICCOMPONENT name="Descriptor Map" id="2d4703c07613c1fd" memberName="mWordMap"
                    virtualName="" explicitFocusOrder="0" pos="32 119 63M 400" class="Audealize::WordMap"
                    params="p, descriptors"/>
  <SLIDER name="Amount" id="6e762afa2a0f3d7e" memberName="mAmountSlider"
          virtualName="" explicitFocusOrder="0" pos="528 79 240 24" min="0"
          max="10" int="0" style="LinearHorizontal" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"
          needsCallback="1"/>
  <LABEL name="new label" id="e160c7d1b628f01b" memberName="label" virtualName=""
         explicitFocusOrder="0" pos="488 79 40 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Less&#10;" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="e83fcf2c5fb12a46" memberName="label2" virtualName=""
         explicitFocusOrder="0" pos="768 79 56 24" edTextCol="ff000000"
         edBkgCol="0" labelText="More&#10;" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <TOGGLEBUTTON name="English" id="ea59c9a3fb2b61fe" memberName="mEnglishButton"
                virtualName="" explicitFocusOrder="0" pos="288 79 72 24" buttonText="English"
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="1"/>
  <TOGGLEBUTTON name="Espa&#241;ol" id="3e0d8205ac653424" memberName="mEspanolButton"
                virtualName="" explicitFocusOrder="0" pos="360 79 80 24" buttonText="Espa&#241;ol"
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="1"/>
  <LABEL name="Audealize" id="a779ff2220710b09" memberName="mAudealizeLabel"
         virtualName="" explicitFocusOrder="0" pos="27 24 176 32" edTextCol="ff000000"
         edBkgCol="0" labelText="Audealize&#10;" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Helvetica"
         fontsize="35.399999999999998579" bold="0" italic="0" justification="9"/>
  <LABEL name="Effect Type" id="1c359235d7e6d42b" memberName="mEffectTypeLabel"
         virtualName="" explicitFocusOrder="0" pos="181 24 118 32" textCol="ff000000"
         edTextCol="ff000000" edBkgCol="0" labelText="Type&#10;" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Helvetica"
         fontsize="35" bold="0" italic="0" justification="9"/>
  <TEXTBUTTON name="new button" id="9b1b1e4bf4719d1b" memberName="mTradUIButton"
              virtualName="" explicitFocusOrder="0" pos="40 530 208 24" buttonText="+ Show traditional interface"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <GENERICCOMPONENT name="Search Bar" id="8776fc2b5e88846" memberName="mSearchBar"
                    virtualName="TypeaheadEditor" explicitFocusOrder="0" pos="32 74 240 32"
                    class="TypeaheadEditor" params=""/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
} //end namespace Audealize
//[/EndFile]
