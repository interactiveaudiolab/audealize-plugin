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

#ifndef TraditionalUIComponent_h
#define TraditionalUIComponent_h

#include "../audio_processors/AudealizeAudioProcessor.h"

namespace Audealize
{
/// An interface class for Audealize traditional user interfaces (interfaces with knobs sliders)
class TraditionalUI : public Component
{
public:
    TraditionalUI (AudealizeAudioProcessor& p) : processor (p)
    {
        name = "traditional interface";
    };

    /**
     *  Returns the name of the effect being controlled by the TraditionalUI
     */
    String getName ()
    {
        return name;
    }

protected:
    AudealizeAudioProcessor& processor;
    String name;  // this will determine what the title text (mEffectTypeLabel) in AudealizeUI will display

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TraditionalUI);
};
}

#endif /* TraditionalUIComponent_h */
