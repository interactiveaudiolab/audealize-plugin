//
//  properties.h
//
//  Functions for saving/loading properties data.
//

#ifndef properties_h
#define properties_h

namespace Audealize
{
class Properties
{
public:
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

        return properties.getDefaultFile ();
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
};
}
#endif /* properties_h */
