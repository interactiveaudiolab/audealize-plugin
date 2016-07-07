/* =========================================================================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

#ifndef BINARYDATA_H_106670127_INCLUDED
#define BINARYDATA_H_106670127_INCLUDED

namespace BinaryData
{
    extern const char*   reverbpoints_json;
    const int            reverbpoints_jsonSize = 86608;

    extern const char*   LICENSE_txt;
    const int            LICENSE_txtSize = 862;

    extern const char*   COPYING;
    const int            COPYINGSize = 26428;

    // Points to the start of a list of resource names.
    extern const char* namedResourceList[];

    // Number of elements in the namedResourceList array.
    const int namedResourceListSize = 3;

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding data and its size (or a null pointer if the name isn't found).
    const char* getNamedResource (const char* resourceNameUTF8, int& dataSizeInBytes) throw();
}

#endif
