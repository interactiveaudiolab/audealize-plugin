//
//  GraphicEQComponent.h
//
//  A component for creating a graphic EQ interface for Audealize-EQ plugin
//

#ifndef GraphicEQComponent_h
#define GraphicEQComponent_h

#include "../JuceLibraryCode/JuceHeader.h"
#include "../common.h"

using std::vector;

class GraphicEQComponent  : public Component
{
public:
    GraphicEQComponent (AudealizeAudioProcessor& p, int numBands);
    ~GraphicEQComponent();

    void paint (Graphics& g) override;
    void resized() override;

private:
    AudealizeAudioProcessor& processor; // the plugin audio processor
    
    vector< ScopedPointer<Slider> > mGainSliders; // a vector contianing the gain sliders
    
    vector<ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> >mGainSliderAttachment; //
    
    //vector<ScopedPointer<AudioProcessorValueTreeState::Listener>> mGainListener;
    
    int mNumBands; // number of EQ bands
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GraphicEQComponent)
};

#endif
