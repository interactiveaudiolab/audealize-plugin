#ifndef AudealizeUI_h
#define AudealizeUI_h

#include "../JuceLibraryCode/JuceHeader.h"
#include "../../common/AudealizeInterfaces.h"
#include <fstream>
#include "../../common/libs/json.hpp"

using namespace nlohmann;

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
    json mPoints;
    String mPathToPoints;

    AudealizeAudioProcessor& processor;

    ScopedPointer<Component> mMap;
    ScopedPointer<TextEditor> textEditor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudealizeUI)
};

#endif 
