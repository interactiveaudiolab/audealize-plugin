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