
#include "AudealizeUI.h"


using namespace std;
using json = nlohmann::json;

namespace Audealize{
    
    AudealizeUI::AudealizeUI (AudealizeAudioProcessor& p, ScopedPointer<TraditionalUI> t, String pathToPoints, String effectType, bool isPluginMultiEffect)
    : AudioProcessorEditor(&p), processor(p), mPathToPoints(pathToPoints), mTradUI(t)
    {
        LookAndFeel::setDefaultLookAndFeel(&mLookAndFeel);
        
        isMultiEffect = isPluginMultiEffect;
        
        mEffectType = effectType;
        
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
        mLabelLess->setColour (TextEditor::textColourId, AudealizeColors::titleText);
        mLabelLess->setColour (TextEditor::backgroundColourId, Colour (0x00000000));
        mLabelLess->setJustificationType (Justification::centredRight);
        
        // amount slider label "More"
        addAndMakeVisible (mLabelMore = new Label ("More",
                                               TRANS("More\n")));
        mLabelMore->setFont (Font (16.00f, Font::plain));
        mLabelMore->setJustificationType (Justification::centredLeft);
        mLabelMore->setEditable (false, false, false);
        mLabelMore->setColour (TextEditor::textColourId, AudealizeColors::titleText);
        mLabelMore->setColour (TextEditor::backgroundColourId, Colour (0x00000000));
        mLabelMore->setAlwaysOnTop(true);
        
        // english language button
        addAndMakeVisible (mEnglishButton = new ToggleButton ("English"));
        mEnglishButton->addListener (this);
        mEnglishButton->setToggleState (true, dontSendNotification);
        
        // espanol language button
        addAndMakeVisible (mEspanolButton = new ToggleButton (CharPointer_UTF8 ("Espa\xc3\xb1ol")));
        mEspanolButton->addListener (this);
        mEspanolButton->setToggleState (true, dontSendNotification);
        
        
        // if this AudealizeUI is a child component of an AudealizeMultiUI, we wont show the Audealize title text here. 
        if (!isMultiEffect){
            // Audealize title text
            addAndMakeVisible (mAudealizeLabel = new Label ("Audealize: ",
                                                            TRANS("Audealize: ")));
            mAudealizeLabel->setFont (Font ("Roboto Medium", 32, Font::plain));
            mAudealizeLabel->setJustificationType (Justification::topLeft);
            mAudealizeLabel->setEditable (false, false, false);
            mAudealizeLabel->setColour (TextEditor::textColourId, AudealizeColors::titleText);
            mAudealizeLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));
            
            // Audealize effect type title text
            addAndMakeVisible (mEffectTypeLabel = new Label ("Effect Type",
                                                             TRANS("Type\n")));
            mEffectTypeLabel->setFont (Font ("Roboto Medium", 32, Font::plain));
            mEffectTypeLabel->setJustificationType (Justification::topLeft);
            mEffectTypeLabel->setEditable (false, false, false);
            mEffectTypeLabel->setColour (Label::textColourId, AudealizeColors::titleText);
            mEffectTypeLabel->setColour (TextEditor::textColourId, AudealizeColors::titleText);
            mEffectTypeLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));
            mEffectTypeLabel->setText(effectType, NotificationType::dontSendNotification);
            
            // info button
            addAndMakeVisible(mInfoButton = new TextButton("About"));
            mInfoButton->addListener (this);
            mInfoButton->setAlpha(0.8);
            
            // about dialog window
            mAboutComponent = new AboutComponent();
            mDialogOpts.content.setOwned(mAboutComponent);
            mDialogOpts.escapeKeyTriggersCloseButton = true;
            mDialogOpts.useNativeTitleBar = false;
            mDialogOpts.resizable = false;
            mAboutWindow = mDialogOpts.create();
            mAboutWindow->setVisible(false);
        }
        
        // search bar
        addAndMakeVisible (mSearchBar = new TypeaheadEditor());
        mSearchBar->setName ("Search Bar");
        mSearchBar->getEditor()->addListener(this);
        mSearchBar->setColour (TextEditor::outlineColourId, Colours::grey);
        mSearchBar->setColour(TextEditor::ColourIds::focusedOutlineColourId, Colours::lightblue);
        mSearchBar->setColour (TextEditor::shadowColourId, Colour (0x00a1a1a1));
        mSearchBar->getEditor()->setFont(Font(Font::getDefaultSansSerifFontName(), 18, Font::plain));
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
        
        // effect bypass button
        addAndMakeVisible(mBypassButton = new TextButton ("Turn " + effectType + " Off"));
        mBypassButton->setClickingTogglesState(true);
        mBypassButton->addListener(this);
        

        
        // resize limits + ResizableCornerComponent
        // if this AudealizeUI is a child component of an AudealizeMultiUI, resizing will be handled there
        if (!isMultiEffect){
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
        mBypassButton = nullptr;
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
        mAboutComponent = nullptr;
        mInfoButton = nullptr;
        mAboutWindow = nullptr;
    }
    
    //==============================================================================
    void AudealizeUI::paint (Graphics& g)
    {
        g.fillAll (AudealizeColors::background);
    }
    
    void AudealizeUI::resized()
    {
        // resizable corner
        if (!isMultiEffect){
            mResizer->setBounds (getWidth() - 18, getHeight() - 18, 16, 16);
            mInfoButton->setBounds(getWidth() - 80, 22, 48, 20);
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
        if (!isMultiEffect){
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
            mLabelMore->setBounds (getWidth() - 72, getHeight() - 45 - tradUIOffset, 56, 24);
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
        if (!isMultiEffect){
            mAudealizeLabel->setBounds (27, 17, 176, 32);
            mEffectTypeLabel->setBounds (183, 17, 118, 32);
        }

        
        // bypass button
        int width = mBypassButton->getBestWidthForHeight(32);
        width = std::min(140, width); // limit the width to 140 so that it doesn't interfere with language select buttons
        mBypassButton->setBounds(getWidth() - width - 32, 60 + titleTextOffset, width, 32);
        
        // search bar
        mSearchBar->setBounds (32, 60 + titleTextOffset, 240, 32);
        
        // language select buttons
        mEnglishButton->setBounds (mSearchBar->getX() + mSearchBar->getWidth() + 10, 65 + titleTextOffset, 72, 24);
        mEspanolButton->setBounds (mSearchBar->getX() + mSearchBar->getWidth() + 78, 65 + titleTextOffset, 80, 24);
        
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
                sendActionMessage("TradUI_FALSE");
                isTradUIVisible = false;
                
                setSize(getWidth(), getHeight()-mTradUI->getHeight()-10); // resize the window
                
                mTradUI->setVisible(false);
                
                mTradUIButton->setButtonText (TRANS("+ Show " + String(mTradUI->getName()))); // update the text on traditional UI button "Hide" -> "Show"
                
                if (!isMultiEffect)
                    mResizeLimits->setSizeLimits (600, 400, 1180, 800); // window size limits depend on whether or not the traditional UI is visible
            }
            else{
                sendActionMessage("TradUI_TRUE");
                isTradUIVisible = true;
                
                setSize(getWidth(), getHeight()+mTradUI->getHeight()+10); // resize the window to accommodate the traditional UI
                
                mTradUI->setVisible(true); // make the traditional UI visible
                
                mTradUIButton->setButtonText (TRANS("- Hide " + String(mTradUI->getName()))); // update the text on traditional UI button "Show" -> "Hide"
                
                if (!isMultiEffect)
                    mResizeLimits->setSizeLimits (600, 400 + mTradUI->getHeight() + 10, 1180, 800 + mTradUI->getHeight() + 10); // window size limits depend on whether or not the traditional UI is visible
            }
        }// end if buttonThatWasClicked
        
        else if (buttonThatWasClicked == mBypassButton){
            if (processor.isBypassed()){
                mBypassButton->setButtonText("Turn " + mEffectType + " Off");
                processor.setBypass(false);
            }
            else{
                mBypassButton->setButtonText("Turn " + mEffectType + " On");
                processor.setBypass(true);
            }
        }
        
        else if (buttonThatWasClicked == mInfoButton){
            mAboutWindow->setVisible(true);
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
        
        // if word not in map, display "Word not found!" and select all text
        if (!mWordMap->searchMapAndSelect(text)){
            AttributedString attStr;
            attStr.append("Word not found!", Font (18.0f));
            static_cast<TypeaheadEditor*>(editor.getParentComponent())->showBubbleMessage(attStr, Colours::red, Colour(0xFFFFB4AF), 1000);
            editor.selectAll();
        }
        mWordMap->repaint();
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
