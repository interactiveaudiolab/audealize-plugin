#ifndef __JUCE_HEADER_2C6B94272375A9F2__
#define __JUCE_HEADER_2C6B94272375A9F2__

#include "AudealizeTabbedComponent.h"
#include "AboutComponent.h"

using std::vector;

namespace Audealize
{
    
    class AudealizeMultiUI  : public AudioProcessorEditor,
    public ActionListener,
    public ButtonListener
    {
    public:
        enum ColourIds{
            backgroundColourId = 0x2000200,
            textColourId = 0x2000201,
            outlineColourId = 0x2000202,
            accentColourId = 0x2000203
        };
        
        AudealizeMultiUI (AudioProcessor& p, vector<AudealizeUI*> AudealizeUIs);
        ~AudealizeMultiUI();
        
        void actionListenerCallback(const juce::String &message) override;
        
        void paint (Graphics& g) override;
        void resized() override;
        void childrenChanged() override;
        
        void lookAndFeelChanged() override;
        
        void buttonClicked (Button* buttonThatWasClicked) override;
        
    private:
        var properties;
        
        vector<AudealizeUI*> mAudealizeUIs;
        
        ScopedPointer<ResizableCornerComponent> mResizer; // handles resizing of the plugin window
        ScopedPointer<ComponentBoundsConstrainer> mResizeLimits; // sets size limits for the plugin window
        
        int prevChildHeight;
        
        TooltipWindow mToolTip;
        
        ScopedPointer<AudealizeTabbedComponent> mTabbedComponent;
        ScopedPointer<Label> label;
        
        AudealizeLookAndFeel mLookAndFeel;
        AudealizeLookAndFeelDark mLookAndFeelDark;
        
        ScopedPointer<AboutComponent> mAboutComponent;
        DialogWindow::LaunchOptions mDialogOpts;
        ScopedPointer<DialogWindow> mAboutWindow;
        ScopedPointer<TextButton> mInfoButton;
        
        ScopedPointer<Drawable> mDarkModeGraphic;
        ScopedPointer<DrawableButton> mDarkModeButton;
        
        ScopedPointer<Drawable> mPowerButtonGraphic;
        vector<DrawableButton*> mTabBypassButtons;
        
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudealizeMultiUI)
    };
}
#endif   // __JUCE_HEADER_2C6B94272375A9F2__
