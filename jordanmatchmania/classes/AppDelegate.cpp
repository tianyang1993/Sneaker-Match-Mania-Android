//
//  JordanMatchMainaAppDelegate.cpp
//  JordanMatchMaina
//
//  Created by Mikhail Berrya on 12/19/13.
//  Copyright __MyCompanyName__ 2013. All rights reserved.
//

#include "AppDelegate.h"
#include "IntroLayer.h"
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "GameSetting.h" 
#include <vector>
#include <string>
#include "RevMob/RevMob.h"
#include "ChartboostX.h"
 
#include "AnalyticX.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <jni.h>
#include "platform/android/jni/JniHelper.h"
#include "AnalyticXStringUtilAndroid.h"
#include <android/log.h>
#endif


USING_NS_CC;
using namespace CocosDenshion;
using namespace std;

AppDelegate::AppDelegate()
{

}

AppDelegate::~AppDelegate()
{
}

bool AppDelegate::applicationDidFinishLaunching()
{
    
    CCDirector *pDirector = CCDirector::sharedDirector();
    pDirector->setOpenGLView(CCEGLView::sharedOpenGLView());
    pDirector->setDisplayStats(false);
    pDirector->setAnimationInterval(1.0 / 60);
   
    vector<string> searchPath;
    searchPath.push_back("Symbols");
    searchPath.push_back("Menu");
    searchPath.push_back("Animations");
    searchPath.push_back("Sounds/Music");
    searchPath.push_back("Sounds/SFX");
    searchPath.push_back("RevMob");
//    searchPath.push_back("Flurry");
    searchPath.push_back("ChartBosst/jansson");
    searchPath.push_back("ChartBosst/NDKHelper");
    
    CCFileUtils::sharedFileUtils()->setSearchPaths(searchPath);

#pragma mark - RevMob StartSession
//\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/
   
    revmob::RevMob *revmob = revmob::RevMob::SharedInstance();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    revmob->StartSession("5106be9d0639b41100000052");
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    revmob->StartSession("52b13db903a7a08f2b000035");
#endif
    

    ChartboostX::sharedChartboostX()->startSession();
    ChartboostX::sharedChartboostX()->setAppId("51c313f316ba47bc7500000d");
    ChartboostX::sharedChartboostX()->setAppSignature("9e179398ab9e9867b77ea97dda5ec8ea2fca2571");
    
    AnalyticX::flurrySetAppVersion("v_1_97");
    cocos2d::CCLog("--->>>get flurry version = %s", AnalyticX::flurryGetFlurryAgentVersion());
    AnalyticX::flurrySetDebugLogEnabled(false);
    AnalyticX::flurrySetSessionContinueSeconds(143);
    AnalyticX::flurrySetSecureTransportEnabled(false);
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    AnalyticX::flurryStartSession("5D2WXK3DPKFKYMG25P4Z");
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    AnalyticX::flurryStartSession("5D2WXK3DPKFKYMG25P4Z");
#endif
    
    AnalyticX::flurrySetUserID("fake_user_id");
    AnalyticX::flurrySetAge(34);
    AnalyticX::flurrySetGender("f");
    AnalyticX::flurrySetReportLocation(false);


    gameSettings = GameSettings::sharedGameSettings();
    gameSettings->setPlayed(false);
   
    CCScene *pScene = IntroLayer::scene();

    // run
    pDirector->runWithScene(pScene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    
   
    CCDirector::sharedDirector()->stopAnimation();
    SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
    SimpleAudioEngine::sharedEngine()->pauseAllEffects();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->startAnimation();
    SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
    SimpleAudioEngine::sharedEngine()->resumeAllEffects();
}
