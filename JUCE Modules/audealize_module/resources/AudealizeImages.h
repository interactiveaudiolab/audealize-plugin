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

#ifndef AudealizeImages_h
#define AudealizeImages_h

namespace Audealize
{
/// Binary data resources for images
class AudealizeImages
{
public:
    /**
     *  Dark/light theme toggle button graphic
     */
    static const char* darkModeButton_svg;
    static const int darkModeButton_svgSize;

    /**
     *  Interactive Audio Lab logo
     */
    static const char* iallogo_svg;
    static const int iallogo_svgSize;

    /**
     *  Power button glyph (for BypassButton)
     */
    static const char* powerButton_svg;
    static const int powerButton_svgSize;

private:
    AudealizeImages ();

    JUCE_DECLARE_NON_COPYABLE (AudealizeImages);
};
}

#endif