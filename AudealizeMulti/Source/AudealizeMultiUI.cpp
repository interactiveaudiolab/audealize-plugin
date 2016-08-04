#include "AudealizeMultiUI.h"

AudealizeMultiUI::AudealizeMultiUI (AudioProcessor& p, vector<AudealizeUI*> AudealizeUIs)
    : AudioProcessorEditor(&p), mAudealizeUIs(AudealizeUIs)
{
    LookAndFeel::setDefaultLookAndFeel (&mLookAndFeel);

    addAndMakeVisible (mTabbedComponent = new AudealizeTabbedComponent (TabbedButtonBar::TabsAtTop));
    mTabbedComponent->setTabBarDepth (28);
    mTabbedComponent->addTab (TRANS("EQ"), AudealizeColors::tabFill, mAudealizeUIs[0], true);
    mTabbedComponent->addTab (TRANS("Reverb"), AudealizeColors::tabFill, mAudealizeUIs[1], true);
    mTabbedComponent->setCurrentTabIndex (0);
    mTabbedComponent->setOutline(0);
    
    addAndMakeVisible (label = new Label ("new label",
                                          TRANS("Audealize\n")));
    label->setFont (Font ("Helvetica Neue", 38.00f, Font::bold));
    label->setJustificationType (Justification::centredLeft);
    label->setEditable (false, false, false);
    label->setColour (TextEditor::textColourId, AudealizeColors::titleText);
    label->setColour (TextEditor::backgroundColourId, Colour (0x00000000));



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
}

//==============================================================================
void AudealizeMultiUI::paint (Graphics& g)
{
  
    g.fillAll (AudealizeColors::background);

    g.setColour (AudealizeColors::accent);
    g.fillRect (24, 48, getWidth() - 48, 34);

    g.setColour (AudealizeColors::outline);
    g.drawRect (24, 48, getWidth() - 48, 34, 1);

}

void AudealizeMultiUI::resized()
{
    mResizer->setBounds (getWidth() - 18, getHeight() - 18, 16, 16);

    mTabbedComponent->setBounds (0, 54, getWidth() - 0, getHeight() - 54);
    label->setBounds (22, 8, 179, 32);
    
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



//==============================================================================
#if 0
#endif

