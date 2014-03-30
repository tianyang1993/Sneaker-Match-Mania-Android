//
//  GetTokens.h
//  VivaStampede
//
//  Created by Mikhail Berrya on 12/7/13.
//
//

#ifndef __VivaStampede__GetTokens__
#define __VivaStampede__GetTokens__

#include <iostream>
#include "cocos2d.h"

USING_NS_CC;

class GameSettings;
class GetTokens: public CCLayer{

public:
    static CCScene* scene();
    virtual bool init();
    
    CCSize size;
    double dScaleX,dScaleY;
    
    CCMenuItemImage *token_5;
    CCMenuItemImage *token_10;
    CCMenuItemImage *token_30;
    CCMenuItemImage *token_75;
    CCMenuItemImage *token_200;
    CCMenuItemImage *token_500;
    CCMenuItemImage *back;
    
    GameSettings* gameSettings;
    
    void onToken_5(CCObject* pSender);
    void onToken_10(CCObject* pSender);
    void onToken_30(CCObject* pSender);
    void onToken_75(CCObject* pSender);
    void onToken_200(CCObject* pSender);
    void onToken_500(CCObject* pSender);
    void onBack(CCObject* pSender);

private:
	void requestPurchaseToken(int tokenID);
	bool tryIsInternetConnection();
	void updateMessageLabel(const char *text);
    
    void ccTouchesBegan(CCSet* touches,CCEvent* event);
    CREATE_FUNC(GetTokens);
};
#endif /* defined(__VivaStampede__GetTokens__) */
