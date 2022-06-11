#include "OSMutex.h"

OSMutex::OSMutex(std::string name)
{
    // Create or acquire named mutex
    _osMutex = ::CreateMutex(NULL, FALSE, name.c_str());

    ::WaitForSingleObject(_osMutex, INFINITE);
}


OSMutex::~OSMutex(void)
{
    ::ReleaseMutex(_osMutex);
}
