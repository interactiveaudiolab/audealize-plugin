//
//  GraphicEQComponent.h
//
//  A JUCE gui component for creating a graphic EQ interface for Audealize-EQ plugin
//

#ifndef GraphicEQComponent_h
#define GraphicEQComponent_h

using std::vector;
using namespace juce;

namespace Audealize{
    
    class GraphicEQComponent  : public TraditionalUI
    {
    public:
        GraphicEQComponent (AudealizeAudioProcessor& p, int numBands, NormalisableRange<float> gainRange);
        ~GraphicEQComponent();
        
        void paint (Graphics& g) override;
        void resized() override;
        
    private:        
        vector< ScopedPointer<Slider> > mGainSliders; // a vector contianing the gain sliders
        
        vector<ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> >mGainSliderAttachment; //
        
        int mNumBands; // number of EQ bands
        
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GraphicEQComponent)
    };
    
}
#endif
