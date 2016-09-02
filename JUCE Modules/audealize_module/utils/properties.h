//
//  properties.h
//
//  Functions for saving/loading properties data for Audealize plugins
//

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
