//
//  AudealizeTabbedComponent.h
//
//  Defines a JUCE::TabbedComponent class with custom TabbedButtonBar position
//

#ifndef AUDEALIZETABBEDCOMPONENT_H_INCLUDED
#define AUDEALIZETABBEDCOMPONENT_H_INCLUDED

namespace Audealize{
    
    class AudealizeTabbedComponent : public TabbedComponent{
    public:
        enum ColourIds{
            backgroundColourId = 0x2000600
        };
        
        AudealizeTabbedComponent(const TabbedButtonBar::Orientation orientation) : TabbedComponent(orientation) {
        
        }
        ~AudealizeTabbedComponent(){};
        
        void resized() override {
            TabbedComponent::resized();

            tabs->setBounds(30, 0, getWidth() - 55, getTabBarDepth());
        }
        
        void lookAndFeelChanged() override
        {
            TabbedComponent::lookAndFeelChanged();
            for (int i = 0; i < getNumTabs(); i++){
                setTabBackgroundColour(i, findColour(AudealizeTabbedComponent::backgroundColourId));
            }
        }
        
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR ( AudealizeTabbedComponent );
    };
}




#endif  // AUDEALIZETABBEDCOMPONENT_H_INCLUDED
