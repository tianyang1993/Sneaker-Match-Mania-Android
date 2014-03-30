//
//  TokenBuy.h
//  VivaStampede
//
//  Created by Mikhail Berrya on 11/25/13.
//
//

#ifndef __VivaStampede__TokenBuy__
#define __VivaStampede__TokenBuy__

#include <iostream>
#include "cocos2d.h"
#include "CCAlertView.h"
USING_NS_CC;


class GameSettings;
class TokenBuy : public CCLayer {
public:
    virtual bool init();
    static CCScene* scene();
    static TokenBuy* body();
    int byteCount;
    
    CCMenuItemImage *redeem;
    CCMenuItemImage *back;
     
    CCLabelTTF* ByteLabel;
 
    CCSprite    *removeAdsButton;
    CCSprite    *smalTokon;
    CCSprite    *mediumToken;
    CCSprite    *largToken;
    CCSprite    *selectItem;
    
    CCMenuItemImage    *selectItem0;
    CCMenuItemImage    *selectItem1;
    CCMenuItemImage    *selectItem2;
    CCMenuItemImage    *selectItem3;
    CCMenuItemImage    *selectItem4;
    CCMenuItemImage    *selectItem5;
    
 
    
    GameSettings* gameSettings;
 
    void onRedeem(CCObject* pSender);
    void onBack(CCObject* pSender);
    void onMoreToken(CCObject* pSender);
    
    
    void onSelect0(CCObject* pSender);
    void onSelect1(CCObject* pSender);
    void onSelect2(CCObject* pSender);
    void onSelect3(CCObject* pSender);
    void onSelect4(CCObject* pSender);
    void onSelect5(CCObject* pSender);
    void    popupCancel(CCObject* pSender);
    void    popupBuy(CCObject* pSender);
    
    void gotoTokenBuy();
    
  
    void ccTouchesBegan(CCSet* touches,CCEvent* event);
    
    CCSize size;
    double dScaleX,dScaleY;

    
    CREATE_FUNC(TokenBuy);
};

#endif /* defined(__VivaStampede__TokenBuy__) */
