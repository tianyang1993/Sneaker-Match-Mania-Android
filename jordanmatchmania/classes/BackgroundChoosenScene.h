//
//  BackgroundChoosenScene.h
//  VivaStampede
//
//  Created by Mikhail Berrya on 11/25/13.
//
//

#ifndef __VivaStampede__BackgroundChoosenScene__
#define __VivaStampede__BackgroundChoosenScene__

#include <iostream>
#include "cocos2d.h"
#include "GameSetting.h"

USING_NS_CC;

class BackgroundChoosenScene: public CCLayer{
    
public:
    virtual bool init();
    static CCScene* scene();
    CCSize  size;
    
    CCMenuItemImage *backgroundImage1;
    CCMenuItemImage *backgroundImage2;
    CCMenuItemImage *backgroundImage3;
    CCMenuItemImage *backgroundImage4;
    CCMenuItemImage *backgroundImage5;
    CCMenuItemImage *backButton;
    CCMenuItemImage* restorePurchase;
    
    
    GameSettings* gameSettings;
    void onBack1(CCObject* pSender);
    void onBack2(CCObject* pSender);
    void onBack3(CCObject* pSender);
    void onBack4(CCObject* pSender);
    void onBack5(CCObject* pSender);
    void onBack(CCObject* pSender);
    void onRestore(CCObject* pSender);
    
    void    popupCancel(CCObject* pSender);
    void    popupBuy(CCObject* pSender);
    
    CREATE_FUNC(BackgroundChoosenScene);

};

#endif /* defined(__VivaStampede__BackgroundChoosenScene__) */
