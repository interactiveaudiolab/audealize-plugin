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


/*   BEGIN_JUCE_MODULE_DECLARATION

      ID:               audealize_module
      vendor:           Northwestern University Interactive Audio Lab
      version:          4.2.1
      name:             JUCE audio and MIDI I/O device classes
      description:
      website:          http://music.eecs.northwestern.edu
      license:

      dependencies:     juce_core, juce_audio_processors, juce_audio_basics, juce_audio_formats, juce_audio_utils,
   juce_graphics, juce_gui_basics, juce_gui_extra

     END_JUCE_MODULE_DECLARATION
*/
#ifndef AUDEALIZE_MODULE
#define AUDEALIZE_MODULE

#include <vector>
#include <math.h>
#include <fstream>
#include <functional>

#include "wn.h"

#include "../juce_core/juce_core.h"
#include "../juce_audio_basics/juce_audio_basics.h"
#include "../juce_audio_processors/juce_audio_processors.h"
#include "../juce_graphics/juce_graphics.h"
#include "../juce_gui_basics/juce_gui_basics.h"
#include "../juce_gui_extra/juce_gui_extra.h"

#include "LookAndFeel/LookAndFeel.h"

#include "resources/AudealizeImages.h"
#include "resources/Fonts.h"

#include "utils/json.hpp"
#include "utils/calf_dsp_library/delay.h"

#include "utils/PrimeFactors.h"

#include "utils/Biquad.h"
#include "utils/json.hpp"

#include "utils/FreqToText.h"
#include "utils/properties.h"

#include "ui_components/AudealizeUI.h"
#include "ui_components/WordMap.h"
#include "ui_components/GraphicEQComponent.h"
#include "ui_components/TypeaheadPopupMenu.h"
#include "ui_components/TraditionalUIComponent.h"
#include "ui_components/ReverbComponent.h"
#include "ui_components/AudealizeMultiUI.h"
#include "ui_components/AudealizeTabbedComponent.h"
#include "ui_components/AboutComponent.h"
#include "ui_components/AudealizeSlider.h"
#include "ui_components/RotarySliderCentered.h"
#include "ui_components/BypassButton.h"

#include "effects/AudioEffect.h"
#include "effects/NChannelFilter.h"
#include "effects/Equalizer.h"
#include "effects/Reverb.h"

#include "audio_processors/AudealizeAudioProcessor.h"
#include "audio_processors/AudealizeEQAudioProcessor.h"
#include "audio_processors/AudealizeReverbAudioProcessor.h"

#endif  // AUDEALIZE_MODULE
