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

#ifndef properties_h
#define properties_h

#ifdef JUCE_MAC
#define DEFAULT_EQ_DATA_PATH "/Library/Application Support/Audealize/eqdescriptors.json"
#define DEFAULT_REVERB_DATA_PATH "/Library/Application Support/Audealize/reverbdescriptors.json"

#elif JUCE_WINDOWS
#define DEFAULT_EQ_DATA_PATH "C:\\Program Files\\Audealize\\eqdescriptors.json"
#define DEFAULT_REVERB_DATA_PATH "C:\\Program Files\\Audealize\\reverbdescriptors.json"

#elif JUCE_LINUX
#define DEFAULT_EQ_DATA_PATH "/usr/share/Audealize/eqdescriptors.json"
#define DEFAULT_REVERB_DATA_PATH "/Library/Application Support/Audealize/reverbdescriptors.json"

#endif

#define DEFAULT_DARKMODE TRUE

namespace Audealize
{
/// Functions for saving/loading config data.
class Properties
{
public:
    /// String Ids of each property
    struct propertyIds
    {
        static const Identifier darkMode;
        static const Identifier eqDataPath;
        static const Identifier reverbDataPath;
    };

    /**
     *  Write the contents of a var containing property information to the default properties file
     *
     *  @param properties
     */
    static void writePropertiesToFile (var properties);
    /**
     *  Loads the user's configuration file or creates a new one if none exists
     *
     *  @return File
     */
    static File loadPropertiesFile ();

    /**
     *  Returns a juce::var containing a list of properties
     */
    static var loadPropertiesVar ();

    /**
     *  Returns a juce::var containing an individual property, referenced by its property
     *
     *  @see Properties::propertyIds
     */
    static var getProperty (Identifier propertyId);

private:
    Properties ();
};
}
#endif /* properties_h */
