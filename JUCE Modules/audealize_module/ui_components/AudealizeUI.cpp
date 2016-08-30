#include "AudealizeUI.h"

using namespace std;
using json = nlohmann::json;

namespace Audealize
{
AudealizeUI::AudealizeUI (AudealizeAudioProcessor& p, ScopedPointer<TraditionalUI> t, String pathToPoints,
                          String effectType, bool isPluginMultiEffect)
    : AudioProcessorEditor (&p), processor (p), mPathToPoints (pathToPoints), mTradUI (t)
{
    setBypassed (true);

    // load properties, set dark mode accordingly
    properties = Properties::loadPropertiesVar ();
    if (!properties.isVoid () && !properties.isUndefined ())
    {
        var darkMode = properties.getDynamicObject ()->getProperty ("darkmode");
        if (darkMode.isBool ())
        {
            if ((bool) darkMode)
            {
                LookAndFeel::setDefaultLookAndFeel (&mLookAndFeelDark);
            }
            else
            {
                LookAndFeel::setDefaultLookAndFeel (&mLookAndFeel);
            }
        }
    }
    else
    {
        DynamicObject* temp = new DynamicObject ();
        temp->setProperty ("darkmode", false);
        properties = var (temp);
        LookAndFeel::setDefaultLookAndFeel (&mLookAndFeelDark);
    }

    isMultiEffect = isPluginMultiEffect;

    mEffectType = effectType;

    mToolTip.setMillisecondsBeforeTipAppears (25);

    // Load file with descriptors, parse into nlohman::json object
    ifstream infile;
    File descriptorsFile (mPathToPoints);

    json descriptors;

    if (!descriptorsFile.existsAsFile ())
    {
        mAlertBox->showMessageBox (AlertWindow::AlertIconType::WarningIcon, "Fatal Error: Descriptor data not found",
                                   "");
        descriptors = NULL;
    }
    else
    {
        descriptors = json::parse (descriptorsFile.loadFileAsString ().toStdString ());
    }

    // word map
    addAndMakeVisible (mWordMap = new Audealize::WordMap (p, descriptors));
    mWordMap->setName ("Descriptor Map");
    mWordMap->setBroughtToFrontOnMouseClick (true);
    mWordMap->addActionListener (this);

    // amount slider
    addAndMakeVisible (mAmountSlider = new Slider ("Amount"));
    mAmountSlider->setRange (0, 10, 0);
    mAmountSlider->setSliderStyle (Slider::LinearHorizontal);
    mAmountSlider->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    mAmountSlider->setRange (0.0f, 1.0f);

    mAmountSliderAttachment = new AudioProcessorValueTreeState::SliderAttachment (
        p.getValueTreeState (), p.getParamAmountID (), *mAmountSlider);

    // amount slider label "Less"
    addAndMakeVisible (mLabelLess = new Label ("Less", TRANS ("Less\n")));
    mLabelLess->setFont (Font (16.00f, Font::plain));
    mLabelLess->setJustificationType (Justification::centredLeft);
    mLabelLess->setEditable (false, false, false);
    mLabelLess->setColour (TextEditor::textColourId, getLookAndFeel ().findColour (AudealizeUI::textColourId));
    mLabelLess->setColour (TextEditor::backgroundColourId, Colour (0x00000000));
    mLabelLess->setJustificationType (Justification::centredRight);

    // amount slider label "More"
    addAndMakeVisible (mLabelMore = new Label ("More", TRANS ("More\n")));
    mLabelMore->setFont (Font (16.00f, Font::plain));
    mLabelMore->setJustificationType (Justification::centredLeft);
    mLabelMore->setEditable (false, false, false);
    mLabelMore->setColour (TextEditor::textColourId, getLookAndFeel ().findColour (AudealizeUI::textColourId));
    mLabelMore->setColour (TextEditor::backgroundColourId, Colour (0x00000000));
    mLabelMore->setAlwaysOnTop (true);

    // english language button
    addAndMakeVisible (mEnglishButton = new ToggleButton ("English"));
    mEnglishButton->addListener (this);
    mEnglishButton->setToggleState (true, dontSendNotification);

    // espanol language button
    addAndMakeVisible (mEspanolButton = new ToggleButton (CharPointer_UTF8 ("Espa\xc3\xb1ol")));
    mEspanolButton->addListener (this);
    mEspanolButton->setToggleState (true, dontSendNotification);

    if (mEffectType == "Reverb")
    {
        mEnglishButton->setVisible (false);
        mEspanolButton->setVisible (false);
    }

    // if this AudealizeUI is a child component of an AudealizeMultiUI, we wont show the Audealize title text here.
    if (!isMultiEffect)
    {
        // Audealize title text
        addAndMakeVisible (mAudealizeLabel =
                               new Label ("Audealize: " + effectType, TRANS ("Audealize: " + effectType)));
        mAudealizeLabel->setFont (Font ("Roboto Medium", 32, Font::plain));
        mAudealizeLabel->setJustificationType (Justification::topLeft);
        mAudealizeLabel->setEditable (false, false, false);


        // dark mode button
        mDarkModeGraphic = Drawable::createFromImageData (AudealizeImages::darkModeButton_svg,
                                                          AudealizeImages::darkModeButton_svgSize);

        addAndMakeVisible (mDarkModeButton =
                               new DrawableButton ("Dark", DrawableButton::ButtonStyle::ImageOnButtonBackground));
        mDarkModeButton->setTooltip ("Dark/Light theme");

        if (static_cast<AudealizeLookAndFeel&> (getLookAndFeel ()).isDarkModeActive ())
        {
            mDarkModeGraphic->replaceColour (Colour (0xff606060), Colour (0xffbbbbbb));
        }

        mDarkModeButton->setImages (mDarkModeGraphic, mDarkModeGraphic, mDarkModeGraphic, mDarkModeGraphic,
                                    mDarkModeGraphic, mDarkModeGraphic, mDarkModeGraphic, mDarkModeGraphic);

        mDarkModeButton->addListener (this);

        // info button
        addAndMakeVisible (mInfoButton = new TextButton ("About"));
        mInfoButton->addListener (this);
        mInfoButton->setAlpha (0.8);

        // about dialog window
        mAboutComponent = new AboutComponent ();
        mDialogOpts.content.setOwned (mAboutComponent);
        mDialogOpts.escapeKeyTriggersCloseButton = true;
        mDialogOpts.useNativeTitleBar = false;
        mDialogOpts.resizable = false;
        mAboutWindow = mDialogOpts.create ();
        mAboutWindow->setVisible (false);

        // effect bypass button
        addAndMakeVisible (mBypassButton = new TextButton ("Turn " + effectType + " Off"));
        mBypassButton->setClickingTogglesState (true);
        mBypassButton->addListener (this);

        // resize limits + ResizableCornerComponent
        // if this AudealizeUI is a child component of an AudealizeMultiUI, resizing will be handled there
        mResizeLimits = new ComponentBoundsConstrainer ();
        mResizeLimits->setSizeLimits (600, 400, 1180, 800);
        addAndMakeVisible (mResizer = new ResizableCornerComponent (this, mResizeLimits));
    }

    // search bar
    addAndMakeVisible (mSearchBar = new TypeaheadEditor ());
    mSearchBar->setName ("Search Bar");
    mSearchBar->getEditor ()->addListener (this);
    mSearchBar->getEditor ()->setFont (Font (Font::getDefaultSansSerifFontName (), 18, Font::plain));
    mSearchBar->getEditor ()->setSelectAllWhenFocused (true);
    mSearchBar->getEditor ()->setTextToShowWhenEmpty ("Search for a word to apply", Colour (0xff888888));
    mSearchBar->setOptions (mWordMap->getWords ());
    mWordMap->addActionListener (mSearchBar);

    // traditional UI
    addAndMakeVisible (mTradUI);
    mTradUI->setVisible (false);  // hidden by default
    isTradUIVisible = false;

    // show/hide traditional UI button
    addAndMakeVisible (mTradUIButton = new TextButton ("new button"));
    mTradUIButton->setButtonText (TRANS ("+ Show traditional interface"));
    mTradUIButton->addListener (this);
    mTradUIButton->setButtonText (TRANS ("+ Show " + String (mTradUI->getName ())));

    // set initial size of plugin window
    setSize (840, 560);
}

AudealizeUI::~AudealizeUI ()
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
    mTradUIButton = nullptr;
    mSearchBar = nullptr;
    mAboutComponent = nullptr;
    mInfoButton = nullptr;
    mAboutWindow = nullptr;
    mDarkModeButton = nullptr;
    mDarkModeGraphic = nullptr;
}

void AudealizeUI::paint (Graphics& g)
{
    g.fillAll (getLookAndFeel ().findColour (AudealizeUI::backgroundColourId));
}

void AudealizeUI::resized ()
{
    // if this AudealizeUI is a child component of an AudealizeMultiUI, we wont show the Audealize title text here.
    // bounds of wordmap, searchbar, language select buttons must be adjusted to accommodate
    int titleTextOffset;

    if (!isMultiEffect)
    {
        titleTextOffset = 0;

        mResizer->setBounds (getWidth () - 18, getHeight () - 18, 16, 16);
        mInfoButton->setBounds (getWidth () - 80, 22, 48, 24);
        mDarkModeButton->setBounds (getWidth () - 110, 22, 24, 24);
        mAudealizeLabel->setBounds (28, 17, 200, 32);
        // bypass button
        int width = mBypassButton->getBestWidthForHeight (32);
        width =
            std::min (140, width);  // limit the width to 140 so that it doesn't interfere with language select buttons
        mBypassButton->setBounds (getWidth () - width - 32, 60 + titleTextOffset, width, 32);
    }
    else
    {
        titleTextOffset = -40;
    }

    // reduce word map font size if width of window is less than fontSizeThresh
    int fontSizeThresh = 750;
    if (getWidth () <= fontSizeThresh && processor.lastUIWidth > fontSizeThresh)
    {
        mWordMap->setMinFontSize (10);
        mWordMap->setInfoTextSize (10);
    }
    else if (getWidth () > fontSizeThresh && processor.lastUIWidth <= fontSizeThresh)
    {
        mWordMap->setMinFontSize (12);
        mWordMap->setInfoTextSize (12);
    }

    // calculate the width of the amount slider
    int sliderWidth = getWidth () * 0.28f;

    // word map size and amount slider position are dependent upon whether or not traditional UI is visible
    if (isTradUIVisible)
    {
        int tradUIOffset = 130;  // amount by which amount slider/tradui button will be offset from the bottom of the
                                 // window when the traditional ui is visible

        mWordMap->setBounds (32, 105 + titleTextOffset, getWidth () - 63,
                             getHeight () - 163 - tradUIOffset - titleTextOffset);
        mTradUIButton->setBounds (40, getHeight () - 45 - tradUIOffset, 190, 24);

        // amount slider
        mAmountSlider->setBounds (getWidth () - sliderWidth - 72, getHeight () - 45 - tradUIOffset, sliderWidth, 24);

        // amount slider labels
        mLabelLess->setBounds (getWidth () - sliderWidth - 185, getHeight () - 45 - tradUIOffset, 114, 24);
        mLabelMore->setBounds (getWidth () - 72, getHeight () - 45 - tradUIOffset, 56, 24);
    }
    else
    {
        mWordMap->setBounds (32, 105 + titleTextOffset, getWidth () - 63, getHeight () - 163 - titleTextOffset);
        mTradUIButton->setBounds (40, getHeight () - 45, 190, 24);

        // amount slider
        mAmountSlider->setBounds (getWidth () - sliderWidth - 72, getHeight () - 45, sliderWidth, 24);

        // amount slider labels
        mLabelLess->setBounds (getWidth () - sliderWidth - 185, getHeight () - 45, 114, 24);
        mLabelMore->setBounds (getWidth () - 72, getHeight () - 45, 56, 24);
    }


    // search bar
    mSearchBar->setBounds (32, 60 + titleTextOffset, 240, 32);

    // language select buttons
    mEnglishButton->setBounds (mSearchBar->getX () + mSearchBar->getWidth () + 10, 65 + titleTextOffset, 72, 24);
    mEspanolButton->setBounds (mSearchBar->getX () + mSearchBar->getWidth () + 78, 65 + titleTextOffset, 80, 24);

    // traditional UI
    mTradUI->setBounds (38, getHeight () - 140, getWidth () - 63, 120);

    // update UI width stored in processor
    processor.lastUIWidth = getWidth ();
    processor.lastUIHeight = getHeight ();
}


void AudealizeUI::buttonClicked (Button* buttonThatWasClicked)
{
    // if neither language selected, display alert box and re-enable the last language to be disabled.
    if (!mEspanolButton->getToggleState () && !mEnglishButton->getToggleState ())
    {
        languageAlert ();
        buttonThatWasClicked->setToggleState (true, NotificationType::sendNotification);
    }


    // english button
    if (buttonThatWasClicked == mEnglishButton)
    {
        mWordMap->toggleLanguage ("English", mEnglishButton->getToggleState ());
    }

    // espanol button
    else if (buttonThatWasClicked == mEspanolButton)
    {
        mWordMap->toggleLanguage ("Español", mEspanolButton->getToggleState ());
    }

    // traditional UI button
    else if (buttonThatWasClicked == mTradUIButton)
    {
        if (mTradUI->isVisible ())
        {
            sendActionMessage ("TradUI_FALSE");
            isTradUIVisible = false;

            setSize (getWidth (), getHeight () - mTradUI->getHeight () - 10);  // resize the window

            mTradUI->setVisible (false);

            mTradUIButton->setButtonText (
                TRANS ("+ Show " +
                       String (mTradUI->getName ())));  // update the text on traditional UI button "Hide" -> "Show"

            if (!isMultiEffect)
                mResizeLimits->setSizeLimits (
                    600, 400, 1180, 800);  // window size limits depend on whether or not the traditional UI is visible
        }
        else
        {
            sendActionMessage ("TradUI_TRUE");
            isTradUIVisible = true;

            setSize (getWidth (),
                     getHeight () + mTradUI->getHeight () + 10);  // resize the window to accommodate the traditional UI

            mTradUI->setVisible (true);  // make the traditional UI visible

            mTradUIButton->setButtonText (
                TRANS ("- Hide " +
                       String (mTradUI->getName ())));  // update the text on traditional UI button "Show" -> "Hide"

            if (!isMultiEffect)
                mResizeLimits->setSizeLimits (
                    600, 400 + mTradUI->getHeight () + 10, 1180,
                    800 + mTradUI->getHeight () +
                        10);  // window size limits depend on whether or not the traditional UI is visible
        }
    }

    // effect bypass button
    else if (buttonThatWasClicked == mBypassButton)
    {
        if (processor.isBypassed ())
        {
            mBypassButton->setButtonText ("Turn " + mEffectType + " Off");
            processor.setBypass (false);
        }
        else
        {
            mBypassButton->setButtonText ("Turn " + mEffectType + " On");
            processor.setBypass (true);
        }
    }

    // infobutton
    else if (buttonThatWasClicked == mInfoButton)
    {
        mAboutWindow->setVisible (true);
    }

    // dark mode
    else if (buttonThatWasClicked == mDarkModeButton)
    {
        bool isDark = static_cast<AudealizeLookAndFeel&> (getLookAndFeel ()).isDarkModeActive ();

        if (isDark)
        {
            setLookAndFeel (&mLookAndFeel);

            mDarkModeGraphic->replaceColour (Colour (0xffbbbbbb), Colour (0xff606060));
            mDarkModeButton->setImages (mDarkModeGraphic, mDarkModeGraphic, mDarkModeGraphic, mDarkModeGraphic,
                                        mDarkModeGraphic, mDarkModeGraphic, mDarkModeGraphic, mDarkModeGraphic);
        }
        else
        {
            setLookAndFeel (&mLookAndFeelDark);

            mDarkModeGraphic->replaceColour (Colour (0xff606060), Colour (0xffbbbbbb));
            mDarkModeButton->setImages (mDarkModeGraphic, mDarkModeGraphic, mDarkModeGraphic, mDarkModeGraphic,
                                        mDarkModeGraphic, mDarkModeGraphic, mDarkModeGraphic, mDarkModeGraphic);
        }  // endif isDark


        if (!isMultiEffect)
        {
            properties.getDynamicObject ()->setProperty ("darkmode", !isDark);
            Properties::writePropertiesToFile (properties);
        }
    }  // endif buttonThatWasClicked
}

void AudealizeUI::lookAndFeelChanged ()
{
    mToolTip.setLookAndFeel (&getLookAndFeel ());
    if (!isMultiEffect) mAboutComponent->setLookAndFeel (&getLookAndFeel ());
}

void AudealizeUI::childrenChanged ()
{
}


void AudealizeUI::textEditorReturnKeyPressed (TextEditor& editor)
{
    String text = editor.getText ();

    // if word not in map, display "Word not found!" and select all text
    if (!mWordMap->searchMapAndSelect (text))
    {
        AttributedString attStr;
        attStr.append ("Word not found!", Font (18.0f));
        static_cast<TypeaheadEditor*> (editor.getParentComponent ())
            ->showBubbleMessage (attStr, Colours::red, Colour (0xFFFFB4AF), 1000);
        editor.selectAll ();
    }
    mWordMap->repaint ();
}

void AudealizeUI::languageAlert ()
{
    mAlertBox->showMessageBox (AlertWindow::AlertIconType::WarningIcon, "At least one language must be selected!", "");
}

void AudealizeUI::actionListenerCallback (const String& message)
{
    if (message.equalsIgnoreCase ("_languagechanged"))
    {
        mSearchBar->setOptions (mWordMap->getWords ());  // update the set of words that will be searched by the search
                                                         // bar to include only the selected languages
    }
    else
    {
        mLabelLess->setText ("Less \"" + message + "\"", NotificationType::sendNotification);  // change the text of the
                                                                                               // amount slider label to
                                                                                               // include the descriptor

        if (isMultiEffect)
        {
            sendActionMessage ("Enabled" + mEffectType);
        }

        setBypassed (false);
    }
}
}
