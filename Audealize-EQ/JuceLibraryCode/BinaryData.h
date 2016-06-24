/* =========================================================================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

#ifndef BINARYDATA_H_127880878_INCLUDED
#define BINARYDATA_H_127880878_INCLUDED

namespace BinaryData
{
    extern const char*   CircleDark_png;
    const int            CircleDark_pngSize = 879;

    extern const char*   CircleDark2x_png;
    const int            CircleDark2x_pngSize = 1981;

    extern const char*   CircleLight_png;
    const int            CircleLight_pngSize = 819;

    extern const char*   CircleLight2x_png;
    const int            CircleLight2x_pngSize = 1954;

    extern const char*   eqpoints_json;
    const int            eqpoints_jsonSize = 364420;

    extern const char*   COPYING;
    const int            COPYINGSize = 26428;

    // Points to the start of a list of resource names.
    extern const char* namedResourceList[];

    // Number of elements in the namedResourceList array.
    const int namedResourceListSize = 6;

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding data and its size (or a null pointer if the name isn't found).
    const char* getNamedResource (const char* resourceNameUTF8, int& dataSizeInBytes) throw();
}

#endif
