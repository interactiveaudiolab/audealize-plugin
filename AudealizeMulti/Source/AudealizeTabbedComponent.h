//
//  AudealizeTabbedComponent.h
//
//  Defines a JUCE::TabbedComponent class with custom TabbedButtonBar position
//

#ifndef AUDEALIZETABBEDCOMPONENT_H_INCLUDED
#define AUDEALIZETABBEDCOMPONENT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

namespace Audealize{
    
    class AudealizeTabbedComponent : public TabbedComponent{
    public:
        AudealizeTabbedComponent(const TabbedButtonBar::Orientation orientation) : TabbedComponent(orientation) {
        
        }
        ~AudealizeTabbedComponent(){};
        
        void resized(){
            TabbedComponent::resized();

            tabs->setBounds(30, 0, getWidth() - 55, getTabBarDepth());
        }
        
    };
}




#endif  // AUDEALIZETABBEDCOMPONENT_H_INCLUDED
