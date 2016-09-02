//
//  FreqToText.h
//
//  A function for nicely formatting frequency values for display
//

#ifndef FreqToText_h
#define FreqToText_h

using namespace std;

/**
 *  Returns a formatted string representation of a frequency value (in Hz)
 *  ex: freqToText(7531)  => "7.53 kHz"
 *      freqToText(13463) => "13.4 kHz"
 *
 *  @param freq - a frequency value in Hz
 *
 *  @return a formatted juce::String representation of freq
 */
static String freqToText (const float freq)
{
    String val (freq);

    if (freq >= 1000 && freq < 10000)
    {
        return val.substring (0, 1) + "." + val.substring (1, 2) + " kHz";
    }
    else if (freq >= 10000)
    {
        return val.substring (0, 2) + "." + val.substring (2, 3) + " kHz";
    }

    return val + " Hz";
}

#endif /* FreqToText_h */
