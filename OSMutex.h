#ifndef OSMUTEX_H
#define OSMUTEX_H

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <string>

// This guy is meant to give us RAII
class OSMutex
{
public:
    OSMutex(std::string name);
    virtual ~OSMutex(void);

private:
    HANDLE _osMutex;

};

#endif // OSMUTEX_H
