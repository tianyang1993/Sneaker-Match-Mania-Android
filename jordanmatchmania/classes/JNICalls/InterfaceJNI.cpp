#include "InterfaceJNI.h"
#include "platform/android/jni/JniHelper.h"
#include <jni.h>
#include <android/log.h>

using namespace cocos2d;

void InterfaceJNI::helloWorld()
{
	// Java variables
	JavaVM* jvm = JniHelper::getJavaVM();
	int status;
	JNIEnv *env;
	jmethodID mid;
	bool isAttached = false;

	// Return
	bool returnValue = false;

	CCLog("Static helloWorld");

	// Get Status
	status = jvm->GetEnv((void **) &env, JNI_VERSION_1_6);


	if(status < 0)
	{
		//LOGE("callback_handler: failed to get JNI environment, " // "assuming native thread");
		status = jvm->AttachCurrentThread(&env, NULL);
		CCLog("helloWorld Status 2: %d", status);
		if(status < 0)
		{
			// LOGE("callback_handler: failed to attach " // "current thread");
			return;
		}
		isAttached = true;
		//CCLog("helloWorld Status isAttached: %d", isAttached);
	}
	//-----------------------------------------------------------

	CCLog("SneakerMatchMania Status: %d", status);

	// Get the class
	jclass mClass = env->FindClass("com/SneakerMatchMania/InternetConnection");

	// Get a STATIC Method; void helloWorld(void)
	mid = env->GetStaticMethodID(mClass, "SneakerMatchMania", "()V");
	if (mid == 0)
	{
		CCLog("SneakerMatchMania FAIL GET METHOD STATIC");
		return;
	}
	// Call to class
	env->CallStaticVoidMethod(mClass, mid);

	CCLog("helloWorld Done ");

	// Detach
	if(isAttached)
		jvm->DetachCurrentThread();

}

void InterfaceJNI::postMessageEMail()
{
	JavaVM* jvm = JniHelper::getJavaVM();
	int status;
	JNIEnv *env;
	jmethodID mid;

	bool isAttached = false;

	CCLog("Static postMessageEMail");

	// Get Status
	status = jvm->GetEnv((void **) &env, JNI_VERSION_1_6);



	if(status < 0)
	{
		//LOGE("callback_handler: failed to get JNI environment, " // "assuming native thread");
		status = jvm->AttachCurrentThread(&env, NULL);
		CCLog("Status 2: %d", status);
		if(status < 0)
		{
			// LOGE("callback_handler: failed to attach " // "current thread");
			return;
		}
		isAttached = true;
		CCLog("Status isAttached: %d", isAttached);
	}
	//-----------------------------------------------------------

	CCLog("Status: %d", status);

	jclass mClass = env->FindClass("com/SneakerMatchMania/SneakerMatchMania");

	CCLog("jClass Located?");

	mid = env->GetStaticMethodID(mClass, "sendEMail", "()V");

	 

	if (mid!=0)
		env->CallStaticVoidMethod(mClass, mid);
			//-----------------------------------------------------------
	CCLog("Finish");
	if(isAttached)
		jvm->DetachCurrentThread();

	return;
}

void InterfaceJNI::postMessageEMailSupport()
{
	JavaVM* jvm = JniHelper::getJavaVM();
	int status;
	JNIEnv *env;
	jmethodID mid;

	bool isAttached = false;

	CCLog("Static postMessageEMail");

	// Get Status
	status = jvm->GetEnv((void **) &env, JNI_VERSION_1_6);



	if(status < 0)
	{
		//LOGE("callback_handler: failed to get JNI environment, " // "assuming native thread");
		status = jvm->AttachCurrentThread(&env, NULL);
		CCLog("Status 2: %d", status);
		if(status < 0)
		{
			// LOGE("callback_handler: failed to attach " // "current thread");
			return;
		}
		isAttached = true;
		CCLog("Status isAttached: %d", isAttached);
	}
	//-----------------------------------------------------------

	CCLog("Status: %d", status);

	jclass mClass = env->FindClass("com/SneakerMatchMania/SneakerMatchMania");

	CCLog("jClass Located?");

	mid = env->GetStaticMethodID(mClass, "sendEmailSupport", "()V");

	 

	if (mid!=0)
		env->CallStaticVoidMethod(mClass, mid);
			//-----------------------------------------------------------
	CCLog("Finish");
	if(isAttached)
		jvm->DetachCurrentThread();

	return;
}

void InterfaceJNI::showMoreApp()
{
	JavaVM* jvm = JniHelper::getJavaVM();
	int status;
	JNIEnv *env;
	jmethodID mid;

	bool isAttached = false;

	CCLog("Static postMessageEMail");

	// Get Status
	status = jvm->GetEnv((void **) &env, JNI_VERSION_1_6);



	if(status < 0)
	{
		//LOGE("callback_handler: failed to get JNI environment, " // "assuming native thread");
		status = jvm->AttachCurrentThread(&env, NULL);
		CCLog("Status 2: %d", status);
		if(status < 0)
		{
			// LOGE("callback_handler: failed to attach " // "current thread");
			return;
		}
		isAttached = true;
		CCLog("Status isAttached: %d", isAttached);
	}
	//-----------------------------------------------------------

	CCLog("Status: %d", status);

	jclass mClass = env->FindClass("com/SneakerMatchMania/SneakerMatchMania");

	CCLog("jClass Located?");

	mid = env->GetStaticMethodID(mClass, "showMoreApp", "()V");

	 

	if (mid!=0)
		env->CallStaticVoidMethod(mClass, mid);
			//-----------------------------------------------------------
	CCLog("Finish");
	if(isAttached)
		jvm->DetachCurrentThread();

	return;
}


void InterfaceJNI::purchaseToken(int tokenID)
{
	JavaVM* jvm = JniHelper::getJavaVM();
	int status;
	JNIEnv *env;
	jmethodID mid;

	bool isAttached = false;

	CCLog("Static purchaseToken");

	// Get Status
	status = jvm->GetEnv((void **) &env, JNI_VERSION_1_6);

	if(status < 0)
	{
		//LOGE("callback_handler: failed to get JNI environment, " // "assuming native thread");
		status = jvm->AttachCurrentThread(&env, NULL);
		CCLog("Status 2: %d", status);
		if(status < 0)
		{
			// LOGE("callback_handler: failed to attach " // "current thread");
			return;
		}
		isAttached = true;
		CCLog("Status isAttached: %d", isAttached);
	}
	//-----------------------------------------------------------

	CCLog("Status: %d", status);

	jclass mClass = env->FindClass("com/SneakerMatchMania/IAPManager");

	CCLog("jClass Located?");

	mid = env->GetStaticMethodID(mClass, "purchaseToken", "(I)V");

	 

	if (mid!=0)
		env->CallStaticVoidMethod(mClass, mid, tokenID);
			//-----------------------------------------------------------
	CCLog("Finish");
	if(isAttached)
		jvm->DetachCurrentThread();

	return;
}


/**
 * Check if Internet Connection is ONLINE
 */
bool InterfaceJNI::isInternetConnected()
{
	JavaVM* jvm = JniHelper::getJavaVM();
	int status;
	JNIEnv *env;
	jmethodID mid;
	jobject jobj;

	bool isAttached = false;
	bool returnValue = false;

	CCLog("InterfaceJNI isInternetConnected");

	// Get Status
	status = jvm->GetEnv((void **) &env, JNI_VERSION_1_6);

	if(status < 0)
	{
		CCLog("isInternetConnected Status < 0 Failed to get JNI Enviroment!!!");
		status = jvm->AttachCurrentThread(&env, NULL);
		CCLog("isInternetConnected Status 2: %d", status);
		if(status < 0)
		{
			CCLog("isInternetConnected Status < 0 !!!");
			return false;
		}
		isAttached = true;
		CCLog("isInternetConnected Status isAttached: %d", isAttached);
	}

	CCLog("isInternetConnected Status: %d", status);

	CCLog("isInternetConnected Finding Class....");
	
    jclass mClass = env->FindClass("com/SneakerMatchMania/SneakerMatchMania");
    
	// Look for a STATIC METHOD With out send parameters and return BOOLEAN into the class
	CCLog("isInternetConnected Getting method....");
	mid = env->GetStaticMethodID(mClass, "isInternetConnection", "()Z");
	if (mid == 0)
	{
		CCLog("isInternetConnected FAIL GET METHOD STATIC");
		return false;
	}
	CCLog("isInternetConnected Calling method....");
	// Call Static bool isInternetConnection()
	jboolean jReturnValue =	env->CallStaticBooleanMethod(mClass,mid);
	CCLog("Call done ");
	// Convert value from Java to C++
	returnValue = (bool)jReturnValue;
	CCLog("isInternetConnected Done, value is: %d", returnValue);

	if(isAttached)
		jvm->DetachCurrentThread();

	// Change for return value
	return returnValue;
}
