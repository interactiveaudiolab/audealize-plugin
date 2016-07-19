
#include "AudealizeUI.h"


using namespace std;
using json = nlohmann::json;

namespace Audealize{
    
    AudealizeUI::AudealizeUI (AudealizeAudioProcessor& p, ScopedPointer<TraditionalUI> t, String pathToPoints, String effectType)
    : AudioProcessorEditor(&p), processor(p), mPathToPoints(pathToPoints), mTradUI(t)
    {
        // Load file with descriptors, parse into nlohman::json object
        ifstream infile;
        infile.open(mPathToPoints.toUTF8());
        json descriptors = json::parse(infile);
        
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
        label->setJustificationType (Justification::centredRight);
        
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
        
        setSize (840, 560);
    }
    
    AudealizeUI::~AudealizeUI()
    {
        mAlertBox = nullptr;
        mAmountSliderAttachment = nullptr;
        mResizer = nullptr;
        mResizeLimits = nullptr;
        
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
    }
    
    //==============================================================================
    void AudealizeUI::paint (Graphics& g)
    {
        g.fillAll (Colours::white);
    }
    
    void AudealizeUI::resized()
    {
        mResizer->setBounds (getWidth() - 18, getHeight() - 18, 16, 16);
        
        
        // reduce word map font size if width of window is less than fontSizeThresh
        int fontSizeThresh = 750;
        if (getWidth() <= fontSizeThresh && processor.lastUIWidth > fontSizeThresh) {
            mWordMap->setMinFontSize(10);
            
        }
        else if (getWidth() > fontSizeThresh && processor.lastUIWidth <= fontSizeThresh) {
            mWordMap->setMinFontSize(12);
        }
        
        
        // word map size is dependent upon whether or not traditional UI is visible
        if (isTradUIVisible){
            mWordMap->setBounds (32, 105, getWidth() - 63, getHeight() - 163 - 130);
            mTradUIButton->setBounds (40, getHeight() - 45 - 130, 190, 24);
        }
        else{
            mWordMap->setBounds (32, 105, getWidth() - 63, getHeight() - 163);
            mTradUIButton->setBounds (40, getHeight() - 45, 190, 24);
        }
        
        // Amount slider
        int sliderWidth = getWidth() * 0.28f;
        mAmountSlider->setBounds (getWidth() - sliderWidth - 72, getHeight() - 45, sliderWidth, 24);
        
        // amount slider labels
        label->setBounds (getWidth() - sliderWidth - 188, getHeight() - 45, 120, 24);
        label2->setBounds (getWidth() - 72, getHeight() - 45, 56, 24);
        
        // Audealize title labels
        mAudealizeLabel->setBounds (27, 22, 176, 32);
        mEffectTypeLabel->setBounds (150, 22, 118, 32);
        
        // language select buttons
        mEnglishButton->setBounds (286, 65, 72, 24);
        mEspanolButton->setBounds (358, 65, 80, 24);
        
        // search bar
        mSearchBar->setBounds (32, 60, 240, 32);
        
        mTradUI->setBounds(38, getHeight() - 140, getWidth()-63, 120);
        
        processor.lastUIWidth = getWidth();
        processor.lastUIHeight = getHeight();
    }
    
    void AudealizeUI::sliderValueChanged (Slider* sliderThatWasMoved)
    {
        
        if (sliderThatWasMoved == mAmountSlider)
        {
        }
        
    }
    
    void AudealizeUI::buttonClicked (Button* buttonThatWasClicked)
    {
        if (!mEspanolButton->getToggleState() && !mEnglishButton->getToggleState()){
            languageAlert();
            buttonThatWasClicked->setToggleState(true, NotificationType::sendNotification);
        }
        
        
        if (buttonThatWasClicked == mEnglishButton)
        {
            mWordMap->toggleLanguage("English", mEnglishButton->getToggleState());
        }
        else if (buttonThatWasClicked == mEspanolButton)
        {
            mWordMap->toggleLanguage("Español", mEspanolButton->getToggleState());
        }
        else if (buttonThatWasClicked == mTradUIButton)
        {
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
        }
        
    }
    
    void AudealizeUI::lookAndFeelChanged()
    {
    }
    
    void AudealizeUI::childrenChanged()
    {
    }
    
    
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
        else{
            label->setText("Less " + message, NotificationType::sendNotification);
        }
    }
    
}
