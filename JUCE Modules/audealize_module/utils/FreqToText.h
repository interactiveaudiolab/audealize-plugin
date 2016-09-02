/*
 Audealize
 
 http://music.cs.northwestern.edu
 http://github.com/interactiveaudiolab/audealize-plugin
 
 Licensed under the GNU GPLv2 <https://opensource.org/licenses/GPL-2.0>
 
 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 2
 of the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

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
