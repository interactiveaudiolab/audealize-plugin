//
//  ReverbComponent.h
//
//  An Audealize::TraditionalUI component for controlling the Audealize reverberator
//

#ifndef REVERBCOMPONENT_H
#define REVERBCOMPONENT_H

#include "RotarySliderCentered.h"

namespace Audealize
{
class ReverbComponent : public TraditionalUI
{
public:
    ReverbComponent (AudealizeAudioProcessor& p);
    ~ReverbComponent ();

    void paint (Graphics& g) override;
    void resized () override;

private:
    ScopedPointer<AudealizeSlider> mSliderD, mSliderG, mSliderM, mSliderF, mSliderE;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> mSliderAttachmentD, mSliderAttachmentG,
        mSliderAttachmentM, mSliderAttachmentF, mSliderAttachmentE;

    ScopedPointer<Label> mLabelD, mLabelG, mLabelM, mLabelF, mLabelE;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ReverbComponent)
};
}

#endif