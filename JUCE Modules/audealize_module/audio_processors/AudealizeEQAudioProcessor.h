#ifndef AUDEALIZEEQAUDIOPROCESSOR_H_INCLUDED
#define AUDEALIZEEQAUDIOPROCESSOR_H_INCLUDED

#define NUMBANDS 40 // the number of eq bands

using namespace Audealize;

class AudealizeeqAudioProcessor  : public AudealizeAudioProcessor
{
public:
    AudealizeeqAudioProcessor();
    ~AudealizeeqAudioProcessor();

    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool setPreferredBusArrangement (bool isInput, int bus, const AudioChannelSet& preferredSet) override;
   #endif

    void processBlock (AudioSampleBuffer&, MidiBuffer&) override;

    AudealizeUI* createEditor(bool isPluginMultiEffect);
    
    // this is here so that IDE doesnt complain about allocating an object of an abstract class
    AudioProcessorEditor* createEditor(){return nullptr;}
    
    bool hasEditor() const override;

    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    double getTailLengthSeconds() const override;

    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;
    
    void parameterChanged(const juce::String &parameterID, float newValue) override;
    void settingsFromMap(vector<float> settings) override;
    
    inline String getParamID(int index) override;
        
    bool isParameterAutomatable(int index){
        return true;
    }
    
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudealizeeqAudioProcessor)
    
#ifdef JUCE_MAC
    const String PATH_TO_POINTS = "/Library/Application Support/Audealize/eqdescriptors.json"; //@TODO
#elif JUCE_WINDOWS
    const String PATH_TO_POINTS = "C:\Program Files\Audealize\eqdescriptors.json";
#elif JUCE_LINUX
    const String PATH_TO_POINTS = "/usr/share/Audealize/eqdescriptors.json";
#endif
    
    NormalisableRange<float> mGainRange; // Range of the graphic eq gain sliders
        
    LinearSmoothedValue<float> mSmoothedVals[NUMBANDS];
    
    std::vector<float> mFreqs = {20, 50, 83, 120, 161, 208, 259, 318, 383, 455, 537, 628, 729, 843, 971, 1114, 1273, 1452, 1652, 1875, 2126, 2406, 2719, 3070, 3462, 3901, 4392, 4941, 5556, 6244, 7014, 7875, 8839, 9917, 11124, 12474, 13984, 15675, 17566, 19682};
    
    Equalizer mEqualizer;
};


#endif  // AUDEALIZEEQAUDIOPROCESSOR_H_INCLUDED
