#include "AudealizeMultiUI.h"

AudealizeMultiUI::AudealizeMultiUI (AudioProcessor& p, vector<AudealizeUI*> AudealizeUIs)
    : AudioProcessorEditor(&p), mAudealizeUIs(AudealizeUIs)
{
    LookAndFeel::setDefaultLookAndFeel (&mLookAndFeel);

    addAndMakeVisible (mTabbedComponent = new AudealizeTabbedComponent (TabbedButtonBar::TabsAtTop));
    mTabbedComponent->setTabBarDepth (28);
    mTabbedComponent->addTab (TRANS("EQ"), getLookAndFeel().findColour(AudealizeTabbedComponent::backgroundColourId), mAudealizeUIs[0], true);
    mTabbedComponent->addTab (TRANS("Reverb"), getLookAndFeel().findColour(AudealizeTabbedComponent::backgroundColourId), mAudealizeUIs[1], true);
    mTabbedComponent->setCurrentTabIndex (0);
    mTabbedComponent->setOutline(0);
    
    addAndMakeVisible (label = new Label ("new label",
                                          TRANS("Audealize\n")));
    label->setFont (Font ("Roboto", 34, Font::plain));
    label->setJustificationType (Justification::centredLeft);
    label->setEditable (false, false, false);
    label->setColour (TextEditor::textColourId, getLookAndFeel().findColour(AudealizeMultiUI::textColourId));
    label->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    // dark mode button
    mDarkModeGraphic = Drawable::createFromImageData (AudealizeImages::darkModeButton_svg, AudealizeImages::darkModeButton_svgSize);
    mDarkModeGraphicLight = Drawable::createFromImageData (AudealizeImages::darkModeButtonLight_svg, AudealizeImages::darkModeButtonLight_svgSize);

    addAndMakeVisible(mDarkModeButton = new DrawableButton("Dark", DrawableButton::ButtonStyle::ImageOnButtonBackground));
    
    if (static_cast<AudealizeLookAndFeel&>(getLookAndFeel()).isDarkModeActive()){
        mDarkModeButton->setImages(mDarkModeGraphicLight, mDarkModeGraphicLight, mDarkModeGraphicLight, mDarkModeGraphicLight, mDarkModeGraphicLight, mDarkModeGraphicLight, mDarkModeGraphicLight, mDarkModeGraphicLight);
    }
    else{
        mDarkModeButton->setImages(mDarkModeGraphic, mDarkModeGraphic, mDarkModeGraphic, mDarkModeGraphic, mDarkModeGraphic, mDarkModeGraphic, mDarkModeGraphic, mDarkModeGraphic);
    }
    mDarkModeButton->addListener(this);
    
    // info button
    addAndMakeVisible(mInfoButton = new TextButton("About"));
    mInfoButton->addListener (this);
    mInfoButton->setAlpha(.9);

    // about dialog window
    mAboutComponent = new AboutComponent();
    mDialogOpts.content.setOwned(mAboutComponent);
    mDialogOpts.escapeKeyTriggersCloseButton = true;
    mDialogOpts.useNativeTitleBar = false;
    mDialogOpts.resizable = false;
    mAboutWindow = mDialogOpts.create();
    mAboutWindow->setVisible(false);

    mResizeLimits = new ComponentBoundsConstrainer();
    mResizeLimits->setSizeLimits (600, 500, 1180, 800);
    addAndMakeVisible (mResizer = new ResizableCornerComponent (this, mResizeLimits));
    mResizer->setAlwaysOnTop(true);
    
    
    setSize (840, 560);

    
    // post-resize

    prevChildHeight = mAudealizeUIs[0]->getHeight();

    mAudealizeUIs[1]->addActionListener(this);
    for (int i = 0; i < mAudealizeUIs.size(); i++){
        mAudealizeUIs[i]->addActionListener(this);
    }
    
    
    // make each map searchable by other maps
    
    for (int i = 0; i < mAudealizeUIs.size(); i++){
        vector<String> effectNames;  // a vector of the names of the other effects
        vector<StringArray> otherMapDescriptors; // a vector of StringArrays containing the descriptors from the other maps
        
        for (int j = 0; j < mAudealizeUIs.size(); j++){
            if (j != i){
                effectNames.push_back(mAudealizeUIs[j]->getEffectName());
                otherMapDescriptors.push_back(mAudealizeUIs[j]->getSearchBar()->getDescriptors());
            }
        }
        
        if (effectNames.size() > 0 && otherMapDescriptors.size() > 0){
            mAudealizeUIs[i]->getSearchBar()->setMultiEffect(effectNames, otherMapDescriptors);
        }
    }
}

AudealizeMultiUI::~AudealizeMultiUI()
{
    for (int i = 0; i < mAudealizeUIs.size(); i++){
        mAudealizeUIs[i] = nullptr;
    }

    mTabbedComponent = nullptr;
    label = nullptr;
    mInfoButton = nullptr;
    mAboutComponent = nullptr;
    mAboutWindow = nullptr;
    mDarkModeButton = nullptr;
    mDarkModeGraphic = nullptr;
    mDarkModeGraphicLight = nullptr;
}

//==============================================================================
void AudealizeMultiUI::paint (Graphics& g)
{
  
    g.fillAll (getLookAndFeel().findColour(AudealizeMultiUI::backgroundColourId));

    g.setColour (getLookAndFeel().findColour(AudealizeMultiUI::accentColourId));
    g.fillRect (24, 48, getWidth() - 48, 34);

    g.setColour (getLookAndFeel().findColour(AudealizeMultiUI::outlineColourId));
    g.drawRect (24, 48, getWidth() - 48, 34, 1);

}

void AudealizeMultiUI::resized()
{
    mResizer->setBounds (getWidth() - 18, getHeight() - 18, 16, 16);

    mDarkModeButton->setBounds(getWidth() - 102, 12, 24, 24);
    
    mInfoButton->setBounds(getWidth() - 72, 12, 48, 24);
    
    mTabbedComponent->setBounds (0, 54, getWidth() - 0, getHeight() - 54);
    label->setBounds (22, 10, 179, 32);
    
    prevChildHeight = mAudealizeUIs[0]->getHeight();

}

void AudealizeMultiUI::childrenChanged()
{
}


void AudealizeMultiUI::actionListenerCallback(const juce::String &message){
    int childIndex = mTabbedComponent->getCurrentTabIndex();

    if (message == "TradUI_TRUE"){ // Traditional UI set to visible
        mResizeLimits->setSizeLimits (600, 500 + 120 + 10, 1180, 800 + 120 + 10); // window size limits depend on whether or not the traditional UI is visible

        // show all traditional UIs (prevents window size issues)
        for (int i = 0; i < mAudealizeUIs.size(); i++){
            if (i != childIndex && !mAudealizeUIs[i]->isTraditionalUIVisible()){
                mAudealizeUIs[i]->getTraditionalUIButton()->triggerClick();
            }
        }
    }
    else if (message == "TradUI_FALSE"){
        mResizeLimits->setSizeLimits (600, 500, 1180, 800); // window size limits depend on whether or not the traditional UI is visible

        // hide all traditional UIs (prevents window size issues)
        for (int i = 0; i < mAudealizeUIs.size(); i++){
            if (i != childIndex && mAudealizeUIs[i]->isTraditionalUIVisible()){
                mAudealizeUIs[i]->getTraditionalUIButton()->triggerClick();
            }
        }
    }
    setBounds(getX(), getY(), getWidth(), getHeight() + mAudealizeUIs[childIndex]->getHeight() - prevChildHeight);
    prevChildHeight = mAudealizeUIs[childIndex]->getHeight();
}

void AudealizeMultiUI::buttonClicked(juce::Button *buttonThatWasClicked){
    if (buttonThatWasClicked == mInfoButton){
        mAboutWindow->setVisible(true);
    }
    else if (buttonThatWasClicked == mDarkModeButton){
        if (static_cast<AudealizeLookAndFeel&>(getLookAndFeel()).isDarkModeActive()){
            setLookAndFeel(&mLookAndFeel);
            mDarkModeButton->setImages(mDarkModeGraphic, mDarkModeGraphic, mDarkModeGraphic, mDarkModeGraphic, mDarkModeGraphic, mDarkModeGraphic, mDarkModeGraphic, mDarkModeGraphic);
        }
        else{
            setLookAndFeel(&mLookAndFeelDark);
            mDarkModeButton->setImages(mDarkModeGraphicLight, mDarkModeGraphicLight, mDarkModeGraphicLight, mDarkModeGraphicLight, mDarkModeGraphicLight, mDarkModeGraphicLight, mDarkModeGraphicLight, mDarkModeGraphicLight);
        }
    }
}


