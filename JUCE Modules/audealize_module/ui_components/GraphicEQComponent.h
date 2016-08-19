//
//  GraphicEQComponent.h
//
//  A JUCE gui component for creating a graphic EQ interface for Audealize-EQ plugin
//

#ifndef GraphicEQComponent_h
#define GraphicEQComponent_h

#include <sstream>

using std::vector;
using namespace juce;

namespace Audealize{
    
    class GraphicEQComponent  : public TraditionalUI, public SliderListener
    {
    public:
        enum ColourIds{
            tickMarkColourId = 0x2000500
        };
        
        GraphicEQComponent (AudealizeAudioProcessor& p, int numBands, NormalisableRange<float> gainRange);
        ~GraphicEQComponent();
        
        void paint (Graphics& g) override;
        void resized() override;
                
        void sliderValueChanged	(Slider* slider) override;
        void sliderDragStarted	(Slider* slider) override {}
        void sliderDragEnded	(Slider* slider) override {}

    private:
        vector< ScopedPointer<Slider> > mGainSliders; // a vector contianing the gain sliders
        
        vector< ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> >mGainSliderAttachment;
        
        
        int mNumBands; // number of EQ bands
        
        std::vector<int> mFreqs = {20, 50, 83, 120, 161, 208, 259, 318, 383, 455, 537, 628, 729, 843, 971, 1114, 1273, 1452, 1652, 1875, 2126, 2406, 2719, 3070, 3462, 3901, 4392, 4941, 5556, 6244, 7014, 7875, 8839, 9917, 11124, 12474, 13984, 15675, 17566, 19682};
        
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GraphicEQComponent)
    };
    
}
#endif
