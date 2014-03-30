#ifndef __INTERFACE_JNI_H__
#define __INTERFACE_JNI_H__

#include "cocos2d.h"

class InterfaceJNI
{
public:
	static void helloWorld();
    static void postMessageEMail();
    static bool isInternetConnected();
		
	static void postMessageEMailSupport();
	static void showMoreApp();
	static void purchaseToken(int tokenID);
};

#endif // __INTERFACE_JNI_H__
