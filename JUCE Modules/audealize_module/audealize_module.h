/*   BEGIN_JUCE_MODULE_DECLARATION
 
      ID:               audealize_module
      vendor:           Northwestern University Interactive Audio Lab
      version:          4.2.1
      name:             JUCE audio and MIDI I/O device classes
      description:      
      website:          http://music.eecs.northwestern.edu
      license:          

      dependencies:     juce_core, juce_audio_processors, juce_audio_basics, juce_audio_formats, juce_audio_utils, juce_graphics, juce_gui_basics, juce_gui_extra

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

#include "effects/AudioEffect.h"
#include "effects/NChannelFilter.h"
#include "effects/Equalizer.h"
#include "effects/Reverb.h"

#include "audio_processors/AudealizeEQAudioProcessor.h"
#include "audio_processors/AudealizeReverbAudioProcessor.h"
#include "audio_processors/AudealizeAudioProcessor.h"

#endif   // AUDEALIZE_MODULE
