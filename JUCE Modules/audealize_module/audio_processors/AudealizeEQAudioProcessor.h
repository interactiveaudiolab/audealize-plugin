#ifndef AUDEALIZEEQAUDIOPROCESSOR_H_INCLUDED
#define AUDEALIZEEQAUDIOPROCESSOR_H_INCLUDED

#define NUMBANDS 40  // the number of eq bands

namespace Audealize
{
/// AudealizeAudioProcessor for EQ effect
class AudealizeeqAudioProcessor : public AudealizeAudioProcessor
{
public:
    AudealizeeqAudioProcessor (AudealizeAudioProcessor* owner = nullptr);
    ~AudealizeeqAudioProcessor ();

    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources () override;

#ifndef JucePlugin_PreferredChannelConfigurations
    bool setPreferredBusArrangement (bool isInput, int bus, const AudioChannelSet& preferredSet) override;
#endif

    void processBlock (AudioSampleBuffer&, MidiBuffer&) override;

    AudealizeUI* createEditorForMultiEffect ();

    AudioProcessorEditor* createEditor () override;

    bool hasEditor () const override;

    const String getName () const override;

    bool acceptsMidi () const override;
    bool producesMidi () const override;
    double getTailLengthSeconds () const override;

    int getNumPrograms () override;
    int getCurrentProgram () override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    void parameterChanged (const juce::String& parameterID, float newValue) override;
    void settingsFromMap (vector<float> settings) override;

    inline String getParamID (int index) override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudealizeeqAudioProcessor)

    NormalisableRange<float> mGainRange;  // Range of the graphic eq gain sliders

    LinearSmoothedValue<float> mSmoothedVals[NUMBANDS];

    std::vector<float> mFreqs = {20,   50,   83,   120,  161,   208,   259,   318,   383,   455,
                                 537,  628,  729,  843,  971,   1114,  1273,  1452,  1652,  1875,
                                 2126, 2406, 2719, 3070, 3462,  3901,  4392,  4941,  5556,  6244,
                                 7014, 7875, 8839, 9917, 11124, 12474, 13984, 15675, 17566, 19682};

    Equalizer mEqualizer;
};
}
#endif  // AUDEALIZEEQAUDIOPROCESSOR_H_INCLUDED
