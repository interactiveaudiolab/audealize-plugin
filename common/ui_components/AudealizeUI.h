#ifndef AudealizeUI_h
#define AudealizeUI_h

#include "../JuceLibraryCode/JuceHeader.h"
#include "../../common/common.h"
#include <fstream>

using namespace nlohmann;
using std::vector;

class AudealizeUI  : public Component
{
public:
    AudealizeUI (AudealizeAudioProcessor& p, String pathToPoints);
    ~AudealizeUI();

    void paint (Graphics& g) override;
    void resized() override;
    void mouseMove (const MouseEvent& e) override;
    void mouseEnter (const MouseEvent& e) override;
    void mouseDown (const MouseEvent& e) override;
    void mouseDrag (const MouseEvent& e) override;

private:
    AudealizeAudioProcessor& processor;
    
    ScopedPointer<Component> mMap;
    ScopedPointer<TextEditor> textEditor;
    
    json mPoints;

    String mPathToPoints, mSelected, mHovered;

    Point<float> hover_position;
    
    bool hovering;
    
    const int pad = 2;
    const float unhighlighted_alpha_value = 0.7f;
    const float hover_alpha_value = 0.15f;
    const int hover_center = -1;
    
    const String font_name = "Helvetica";
    
    bool check_for_collision(Point<float> point, vector<Point<float>> plotted, float dist);
    
    bool inRadius(Point<float> pt , Point<float> centerpt, float r);
    
    void plot_word(String word, Colour color, int font_size, Point<float> point, Graphics& g);
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudealizeUI)
};

#endif 
