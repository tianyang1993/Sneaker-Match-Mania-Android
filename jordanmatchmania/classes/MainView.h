//
//  MainView.h
//  VivaStampede
//
//  Created by Mikhail Berrya on 11/25/13.
//
//

#ifndef __VivaStampede__MainView__
#define __VivaStampede__MainView__

#include <iostream>
#include "cocos2d.h"
#include "ChartboostX.h"

USING_NS_CC;
class GameSettings;
class TokenBuy;
class MainView : public CCLayer,public ChartboostXDelegate {
public:
    virtual bool init();
    static CCScene* scene();
    
    CCSize size;
    double dScaleFactorX , dScaleFactorY;
    
    GameSettings* gameSettings;
    
    CCSprite *zookeeperImage;
    CCSprite *matchLogo;
    
    CCMenuItemImage *primaryButton;
    CCMenuItemImage *actionButton;
    CCMenuItemImage *infinityButton;
    CCMenuItemImage *engageButton;
    CCMenuItemImage *StoreButton;
    CCMenuItemImage *getFreeAppButton;
    CCMenuItemImage *moreButton;
    CCMenuItemImage *howToButton;
    
    void showMainView();
   
    void onClickFacebookButton();
    void onClickGuestButton();
    
    void maintoLevels(CCObject* pSender);
    void maintoTime(CCObject* pSender);
    void maintoEndless(CCObject* pSender);
    void maintoMultiplayer(CCObject* pSender);
    void onStore(CCObject* pSender);
    void getFreeApp(CCObject* pSender);
    void maintomoreBackgrounds(CCObject* pSender);
    void maintoMore(CCObject* pSender);
    void howToPlay(CCObject* pSender);
    void setBackGroundView(int nType);
////\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\\/\/\/\/\/\/\/\/\/\/\/\/\/\\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\\/\/\//\\/\/\/\/\/\/\/\/\/\/\/\/\/\/\\/\/
    //ChartBoost SDk Integration
     void ShowChartBoost();
    // ChartboostXDelegate method
    bool shouldDisplayInterstitial(const char* location);
    void didCacheInterstitial(const char* location);
    void didFailToLoadInterstitial(const char* location);
    
    void didCloseInterstitial(const char* location);
    void didClickInterstitial(const char* location);
//\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\\/\/\/\/\/\/\/\/\/\/\/\/\/\\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\\/\/\//\\/\/\/\/\/\/\/\/\/\/\/\/\/\/\\/\/
   
    void onHttpRequestCompleted(CCObject *pSender, void *data);

//\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\\/\/\/\/\/\/\/\/\/\/\/\/\/\\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\\/\/\//\\/\/\/\/\/\/\/\/\/\/\/\/\/\/\\/\/

    
    bool    FirstGame;
    CREATE_FUNC(MainView);
    
private:
    bool m_interstitialShowed;
    bool m_gameLogicContinued;

};


#endif /* defined(__VivaStampede__MainView__) */
