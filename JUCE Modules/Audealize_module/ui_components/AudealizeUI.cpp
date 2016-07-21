
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
        
        // word map
        addAndMakeVisible (mWordMap = new Audealize::WordMap (p, descriptors));
        mWordMap->setName ("Descriptor Map");
        mWordMap->setBroughtToFrontOnMouseClick(true);
        mWordMap->addActionListener(this);
        
        // amount slider
        addAndMakeVisible (mAmountSlider = new Slider ("Amount"));
        mAmountSlider->setRange (0, 10, 0);
        mAmountSlider->setSliderStyle (Slider::LinearHorizontal);
        mAmountSlider->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
        mAmountSlider->setRange(0.0f, 1.0f);
        
        mAmountSliderAttachment = new AudioProcessorValueTreeState::SliderAttachment (p.getValueTreeState(), p.paramAmount, *mAmountSlider);
        
        // amount slider label "Less"
        addAndMakeVisible (mLabelLess = new Label ("Less",
                                              TRANS("Less\n")));
        mLabelLess->setFont (Font (16.00f, Font::plain));
        mLabelLess->setJustificationType (Justification::centredLeft);
        mLabelLess->setEditable (false, false, false);
        mLabelLess->setColour (TextEditor::textColourId, Colours::black);
        mLabelLess->setColour (TextEditor::backgroundColourId, Colour (0x00000000));
        mLabelLess->setJustificationType (Justification::centredRight);
        
        // amount slider label "More"
        addAndMakeVisible (mLabelMore = new Label ("More",
                                               TRANS("More\n")));
        mLabelMore->setFont (Font (16.00f, Font::plain));
        mLabelMore->setJustificationType (Justification::centredLeft);
        mLabelMore->setEditable (false, false, false);
        mLabelMore->setColour (TextEditor::textColourId, Colours::black);
        mLabelMore->setColour (TextEditor::backgroundColourId, Colour (0x00000000));
        
        // english language button
        addAndMakeVisible (mEnglishButton = new ToggleButton ("English"));
        mEnglishButton->addListener (this);
        mEnglishButton->setToggleState (true, dontSendNotification);
        
        // espanol language button
        addAndMakeVisible (mEspanolButton = new ToggleButton (CharPointer_UTF8 ("Espa\xc3\xb1ol")));
        mEspanolButton->addListener (this);
        mEspanolButton->setToggleState (true, dontSendNotification);
        
        // if this AudealizeUI is a child component of an AudealizeMultiUI, we wont show the Audealize title text here. 
        if (getTopLevelComponent() == NULL){
            // Audealize title text
            addAndMakeVisible (mAudealizeLabel = new Label ("Audealize",
                                                            TRANS("Audealize\n")));
            mAudealizeLabel->setFont (Font ("Helvetica", 28, Font::plain));
            mAudealizeLabel->setJustificationType (Justification::topLeft);
            mAudealizeLabel->setEditable (false, false, false);
            mAudealizeLabel->setColour (TextEditor::textColourId, Colours::black);
            mAudealizeLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));
            
            // Audealize effect type title text
            addAndMakeVisible (mEffectTypeLabel = new Label ("Effect Type",
                                                             TRANS("Type\n")));
            mEffectTypeLabel->setFont (Font ("Helvetica", 28, Font::plain));
            mEffectTypeLabel->setJustificationType (Justification::topLeft);
            mEffectTypeLabel->setEditable (false, false, false);
            mEffectTypeLabel->setColour (Label::textColourId, Colours::black);
            mEffectTypeLabel->setColour (TextEditor::textColourId, Colours::black);
            mEffectTypeLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));
            mEffectTypeLabel->setText(effectType, NotificationType::dontSendNotification);
        }
        
        // search bar
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
        mWordMap->addActionListener(mSearchBar);

        // traditional UI
        addAndMakeVisible(mTradUI);
        mTradUI->setVisible(false); // hidden by default
        isTradUIVisible = false;
        
        // show/hide traditional UI button
        addAndMakeVisible (mTradUIButton = new TextButton ("new button"));
        mTradUIButton->setButtonText (TRANS("+ Show traditional interface"));
        mTradUIButton->addListener (this);
        mTradUIButton->setButtonText (TRANS("+ Show " + String(mTradUI->getName())));
        
        
        // resize limits + ResizableCornerComponent
        // if this AudealizeUI is a child component of an AudealizeMultiUI, resizing will be handled there
        if (getTopLevelComponent() == NULL){ 
            mResizeLimits = new ComponentBoundsConstrainer();
            mResizeLimits->setSizeLimits (600, 400, 1180, 800);
            addAndMakeVisible (mResizer = new ResizableCornerComponent (this, mResizeLimits));
        }
        
        // set initial size of plugin window
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
        mLabelLess = nullptr;
        mLabelMore = nullptr;
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
        // resizable corner
        if (getTopLevelComponent() == NULL){
            mResizer->setBounds (getWidth() - 18, getHeight() - 18, 16, 16);
        }
        
        // reduce word map font size if width of window is less than fontSizeThresh
        int fontSizeThresh = 750;
        if (getWidth() <= fontSizeThresh && processor.lastUIWidth > fontSizeThresh) {
            mWordMap->setMinFontSize(10);
            mWordMap->setInfoTextSize(10);
        }
        else if (getWidth() > fontSizeThresh && processor.lastUIWidth <= fontSizeThresh) {
            mWordMap->setMinFontSize(12);
            mWordMap->setInfoTextSize(12);
        }
        
        // if this AudealizeUI is a child component of an AudealizeMultiUI, we wont show the Audealize title text here. 
        // bounds of wordmap, searchbar, language select buttons must be adjusted to accommodate
        int titleTextOffset;
        if (getTopLevelComponent() == NULL){
            titleTextOffset = 0;
        }
        else{
            titleTextOffset = -40;
        }
        
        // calculate the width of the amount slider
        int sliderWidth = getWidth() * 0.28f;
        
        // word map size and amount slider position are dependent upon whether or not traditional UI is visible
        if (isTradUIVisible)
        {
            int tradUIOffset = 130; // amount by which amount slider/tradui button will be offset from the bottom of the window when the traditional ui is visible
            
            mWordMap->setBounds (32, 105 + titleTextOffset, getWidth() - 63, getHeight() - 163 - tradUIOffset - titleTextOffset);
            mTradUIButton->setBounds (40, getHeight() - 45 - tradUIOffset, 190, 24);
            
            // amount slider
            mAmountSlider->setBounds (getWidth() - sliderWidth - 72, getHeight() - 45 - tradUIOffset, sliderWidth, 24);
            
            // amount slider labels
            mLabelLess->setBounds (getWidth() - sliderWidth - 185, getHeight() - 45 - tradUIOffset, 114, 24);
            mLabelMore->setBounds (getWidth() - 72, getHeight() - 45 - tradUIOffset - titleTextOffset, 56, 24);
        }
        else
        {
            mWordMap->setBounds (32, 105 + titleTextOffset, getWidth() - 63, getHeight() - 163 - titleTextOffset);
            mTradUIButton->setBounds (40, getHeight() - 45, 190, 24);
            
            // amount slider
            mAmountSlider->setBounds (getWidth() - sliderWidth - 72, getHeight() - 45, sliderWidth, 24);
            
            // amount slider labels
            mLabelLess->setBounds (getWidth() - sliderWidth - 185, getHeight() - 45, 114, 24);
            mLabelMore->setBounds (getWidth() - 72, getHeight() - 45, 56, 24);
        }
        
        // Audealize title labels
        if (getTopLevelComponent() == NULL){
            mAudealizeLabel->setBounds (27, 22, 176, 32);
            mEffectTypeLabel->setBounds (150, 22, 118, 32);
        }

        // language select buttons
        mEnglishButton->setBounds (getWidth() - 184, 65 + titleTextOffset, 72, 24);
        mEspanolButton->setBounds (getWidth() - 110, 65 + titleTextOffset, 80, 24);
        
        // search bar
        mSearchBar->setBounds (32, 60 + titleTextOffset, 240, 32);
        
        // traditional UI
        mTradUI->setBounds(38, getHeight() - 140, getWidth()-63, 120);
        
        // update UI width stored in processor
        processor.lastUIWidth = getWidth();
        processor.lastUIHeight = getHeight();
    }
    
    
    void AudealizeUI::buttonClicked (Button* buttonThatWasClicked)
    {
        // if neither language selected, display alert box and re-enable the last language to be disabled.
        if (!mEspanolButton->getToggleState() && !mEnglishButton->getToggleState()){
            languageAlert();
            buttonThatWasClicked->setToggleState(true, NotificationType::sendNotification);
        }
        
        
        // english button
        if (buttonThatWasClicked == mEnglishButton)
        {
            mWordMap->toggleLanguage("English", mEnglishButton->getToggleState());
        }
        
        // espanol button
        else if (buttonThatWasClicked == mEspanolButton)
        {
            mWordMap->toggleLanguage("Español", mEspanolButton->getToggleState());
        }
        
        // traditional UI button
        else if (buttonThatWasClicked == mTradUIButton)
        {
            if(mTradUI->isVisible()){
                isTradUIVisible = false;
                
                setSize(getWidth(), getHeight()-mTradUI->getHeight()-10); // resize the window
                
                mTradUI->setVisible(false);
                
                mTradUIButton->setButtonText (TRANS("+ Show " + String(mTradUI->getName()))); // update the text on traditional UI button "Hide" -> "Show"
                
                if (getTopLevelComponent() == NULL)
                    mResizeLimits->setSizeLimits (600, 400, 1180, 800); // window size limits depend on whether or not the traditional UI is visible
            }
            else{
                isTradUIVisible = true;
                
                setSize(getWidth(), getHeight()+mTradUI->getHeight()+10); // resize the window to accommodate the traditional UI
                
                mTradUI->setVisible(true); // make the traditional UI visible
                
                mTradUIButton->setButtonText (TRANS("- Hide " + String(mTradUI->getName()))); // update the text on traditional UI button "Show" -> "Hide"
                
                if (getTopLevelComponent() == NULL)
                    mResizeLimits->setSizeLimits (600, 400 + mTradUI->getHeight() + 10, 1180, 800 + mTradUI->getHeight() + 10); // window size limits depend on whether or not the traditional UI is visible
            }
        }// end if buttonThatWasClicked
    }
    
    void AudealizeUI::lookAndFeelChanged()
    {
    }
    
    void AudealizeUI::childrenChanged()
    {
    }
    
    
    void AudealizeUI::textEditorReturnKeyPressed(TextEditor &editor){
        String text = editor.getText();
        
        // if word not in map, display "Word not found!" and select all text
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
            mSearchBar->setOptions(mWordMap->getWords()); // update the set of words that will be searched by the search bar to include only the selected languages
        }
        else{
            mLabelLess->setText("Less \"" + message + "\"", NotificationType::sendNotification); // change the text of the amount slider label to include the descriptor
        
        }
    }
    
}
