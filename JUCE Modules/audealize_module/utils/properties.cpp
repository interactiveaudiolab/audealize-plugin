#include "properties.h"

using namespace Audealize;

const Identifier Properties::propertyIds::darkMode = "darkmode";
const Identifier Properties::propertyIds::eqDataPath = "eqDataPath";
const Identifier Properties::propertyIds::reverbDataPath = "reverbDataPath";

void Properties::writePropertiesToFile (var properties)
{
    File prop_file = loadPropertiesFile ();

    if (!prop_file.exists ())
    {
        prop_file.create ();
    }

    prop_file.replaceWithText (JSON::toString (properties));
}

File Properties::loadPropertiesFile ()
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

var Properties::loadPropertiesVar ()
{
    var properties;

    if (JSON::parse (loadPropertiesFile ().loadFileAsString (), properties).wasOk ())
    {
        return properties;
    }

    return var ();
}

var Properties::getProperty (Identifier propertyId)
{
    var property = loadPropertiesVar ().getDynamicObject ()->getProperty (propertyId);

    return loadPropertiesVar ().getDynamicObject ()->getProperty (propertyId);
}
