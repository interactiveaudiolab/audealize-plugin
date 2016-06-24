//
//  GraphicEQComponent.h
//  Created by Michael Donovan on 6/15/16.
//
//  A component for creating a graphic EQ interface for Audealize-EQ plugin
//

#ifndef GraphicEQComponent_h
#define GraphicEQComponent_h

#include "../JuceLibraryCode/JuceHeader.h"
#include "../common.h"

using std::vector;

class GraphicEQComponent  : public TraditionalUIComponent
{
public:
    GraphicEQComponent (AudealizeAudioProcessor& p, int numBands);
    ~GraphicEQComponent();

    void paint (Graphics& g) override;
    void resized() override;
    
    void settingsFromMap(vector<float> settings) override;
    
private:
    NormalisableRange<float> mRange;
    
    int mNumBands;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GraphicEQComponent)
};

#endif
