#if defined(AUDEALIZE_MODULE) && !JUCE_AMALGAMATED_INCLUDE
/* When you add this cpp file to your project, you mustn't include it in a file where you've
   already included any other headers - just put it inside a file on its own, possibly with your config
   flags preceding it, but don't include anything else. That also includes avoiding any automatic prefix
   header files that the compiler may be using.
*/
#error "Incorrect use of JUCE cpp file"
#endif

// Your project must contain an AppConfig.h file with your project-specific settings in it,
// and your header search path must make it accessible to the module's files.
#include "AppConfig.h"
#include "audealize_module.h"

#include "LookAndFeel/LookAndFeel.cpp"

#include "resources/AudealizeImages.cpp"
#include "resources/Fonts.cpp"

#include "ui_components/AboutComponent.cpp"
#include "ui_components/AudealizeMultiUI.cpp"
#include "ui_components/AudealizeUI.cpp"
#include "ui_components/GraphicEQComponent.cpp"
#include "ui_components/ReverbComponent.cpp"
#include "ui_components/TypeaheadPopupMenu.cpp"
#include "ui_components/WordMap.cpp"

#include "audio_processors/AudealizeEQAudioProcessor.cpp"
#include "audio_processors/AudealizeReverbAudioProcessor.cpp"

#include "utils/Biquad.cpp"
#include "utils/properties.cpp"