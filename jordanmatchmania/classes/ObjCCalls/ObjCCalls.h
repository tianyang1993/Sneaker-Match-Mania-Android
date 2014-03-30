//PrintMessage.h
#ifndef __PRINTMESSAGE_H__
#define __PRINTMESSAGE_H__

#include <stddef.h>

class ObjCCalls
{
public:
     
    static void trySendAnEMail(const char *score, bool usingInternalApp);
    static bool tryIsInternetConnection();
};

#endif//__PRINTMESSAGE_H__