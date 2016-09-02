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

#ifndef Fonts_h
#define Fonts_h
namespace Audealize
{
/// Binary data resources for fonts
class AudealizeFonts
{
public:
    static const char* RobotoRegular_ttf;
    static const int RobotoRegular_ttfSize = 145348;

private:
    AudealizeFonts ();

    JUCE_DECLARE_NON_COPYABLE (AudealizeFonts);
};
}

#endif /* Fonts_h */
