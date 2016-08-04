#ifndef __JUCE_HEADER_2C6B94272375A9F2__
#define __JUCE_HEADER_2C6B94272375A9F2__

#include "../JuceLibraryCode/JuceHeader.h"
#include "AudealizeTabbedComponent.h"

using std::vector;
using namespace Audealize;



class AudealizeMultiUI  : public AudioProcessorEditor,
                          public ActionListener
{
public:
    //==============================================================================
    AudealizeMultiUI (AudioProcessor& p, vector<AudealizeUI*> AudealizeUIs);
    ~AudealizeMultiUI();

    //==============================================================================
    void actionListenerCallback(const juce::String &message);
    void currentTabChanged (int newCurrentTabIndex, const String &newCurrentTabName);

    void paint (Graphics& g) override;
    void resized() override;
    void childrenChanged() override;



private:
    vector<AudealizeUI*> mAudealizeUIs;

    ScopedPointer<ResizableCornerComponent> mResizer; // handles resizing of the plugin window
    ScopedPointer<ComponentBoundsConstrainer> mResizeLimits; // sets size limits for the plugin window

    int prevChildHeight;

    //==============================================================================
    ScopedPointer<AudealizeTabbedComponent> mTabbedComponent;
    ScopedPointer<Label> label;

    AudealizeLookAndFeel mLookAndFeel;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudealizeMultiUI)
};

#endif   // __JUCE_HEADER_2C6B94272375A9F2__
