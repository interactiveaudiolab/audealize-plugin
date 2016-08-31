//
//  properties.h
//
//  Functions for saving/loading properties data.
//

#ifndef properties_h
#define properties_h

#ifdef JUCE_MAC
#define DEFAULT_EQ_DATA_PATH "/Library/Application Support/Audealize/eqdescriptors.json"
#define DEFAULT_REVERB_DATA_PATH "/Library/Application Support/Audealize/reverbdescriptors.json"

#elif JUCE_WINDOWS
#define DEFAULT_EQ_DATA_PATH "C:\\Program Files\\Audealize\\reverbdescriptors.json"
#define DEFAULT_REVERB_DATA_PATH "C:\\Program Files\\Audealize\\reverbdescriptors.json"

#elif JUCE_LINUX
#define DEFAULT_EQ_DATA_PATH "/usr/share/Audealize/eqdescriptors.json"
#define DEFAULT_REVERB_DATA_PATH "/Library/Application Support/Audealize/reverbdescriptors.json"

#endif

#define DEFAULT_DARKMODE TRUE

namespace Audealize
{
class Properties
{
public:
    struct propertyIds
    {
        static const Identifier darkMode;
        static const Identifier eqDataPath;
        static const Identifier reverbDataPath;
    };

    static void writePropertiesToFile (var properties)
    {
        File prop_file = loadPropertiesFile ();

        if (!prop_file.exists ())
        {
            prop_file.create ();
        }

        prop_file.replaceWithText (JSON::toString (properties));
    }

    static File loadPropertiesFile ()
    {
        PropertiesFile::Options properties;
        properties.osxLibrarySubFolder = "Application Support";
#ifdef JUCE_LINUX
        properties.folderName = ".Audealize";
#else
        properties.folderName = "Audealize";
#endif
        properties.applicationName = "Audealize";
        properties.filenameSuffix = "cfg";

        File defaultFile = properties.getDefaultFile ();

        // if no config file exists, create one using the default settings
        if (!defaultFile.existsAsFile ())
        {
            DynamicObject* temp = new DynamicObject ();
            temp->setProperty ("darkmode", DEFAULT_DARKMODE);
            temp->setProperty (propertyIds::eqDataPath, DEFAULT_EQ_DATA_PATH);
            temp->setProperty (propertyIds::reverbDataPath, DEFAULT_REVERB_DATA_PATH);

            defaultFile.create ();

            defaultFile.replaceWithText (JSON::toString (var (temp)));
        }

        return defaultFile;
    }

    static var loadPropertiesVar ()
    {
        var properties;
        if (JSON::parse (loadPropertiesFile ().loadFileAsString (), properties).wasOk ())
        {
            return properties;
        }
        return var ();
    }

    static var getProperty (Identifier propertyName)
    {
        var property = loadPropertiesVar ().getDynamicObject ()->getProperty (propertyName);

        return loadPropertiesVar ().getDynamicObject ()->getProperty (propertyName);
    }
};
}
#endif /* properties_h */
