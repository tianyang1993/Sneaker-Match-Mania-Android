//
//  MoreLayer.h
//  VivaStampede
//
//  Created by Mikhail Berrya on 11/25/13.
//
//

#ifndef __MORELAYER_SCENE_H__
#define __MORELAYER_SCENE_H__

#include <iostream>
#include "cocos2d.h"
#include "ChartboostX.h"
#include "AnalyticX.h"
USING_NS_CC;


class GameSettings;
class MoreScene: public CCLayer,public ChartboostXDelegate{
    
public:
    virtual bool init();
    static CCScene* scene();
    static MoreScene *instance;
    static MoreScene *get_instance();
   
    CCSize              size;
    CCLabelTTF*                 sLabel;
    
    CCMenuItemLabel          *backToMenuButton;
    CCMenuItemLabel          *getFreeAppLabel;
    CCMenuItemImage         *getFreeAppButton;
    CCMenuItemLabel          *rateLabel;
    CCMenuItemImage         *rateLabelButton;
    CCMenuItemLabel          *topScoresLabel;
    CCMenuItemImage         *topScoresLabelButton;
    CCMenuItemLabel          *infoLabel;
    CCMenuItemImage         *infoLabelButton;
    CCMenuItemLabel          *shareLabel;
    CCMenuItemImage         *shareLabelButton;
    CCMenuItemLabel          *emailSupportLabel;
    CCMenuItemImage         *emailSupportLabelButton;
    CCMenuItemLabel          *moreAppsLabel;
    CCMenuItemImage         *moreAppsLabelButton;
    CCMenuItemLabel          *buyAdFreeVersion;
    CCMenuItemImage         *buyAdFreeVersionButton;
    
    
    GameSettings* gameSettings;
    
    void            onFreeApp(CCObject* pSender);
    void            onRateLabel(CCObject* pSender);
    void            onTopScore(CCObject* pSender);
    void            onInfo(CCObject* pSender);
    void            onShare(CCObject* pSender);
    void            onEmail(CCObject* pSender);
    void            onMoreApp(CCObject* pSender);
    void            onByAdFree(CCObject* pSender);
    void            onBack(CCObject* pSender);
    void            onHowToPlay(CCObject*pSender);
    void            setBackGroundView(int nType);
    
    
    bool tryIsInternetConnection();
    void trySendAnEmail(CCObject* pSender);
    void trySendAnEmailInApp(CCObject* pSender);
    void updateMessageLabel(const char *status);
    
    
    bool shouldDisplayInterstitial(const char* location);
    void didCacheInterstitial(const char* location);
    void didFailToLoadInterstitial(const char* location);
    
    void didCloseInterstitial(const char* location);
    void didClickInterstitial(const char* location);


    CREATE_FUNC(MoreScene);
private:
    bool m_interstitialShowed;
    bool m_gameLogicContinued;
};

#endif /* defined(__VivaStampede__MoreLayer__) */
