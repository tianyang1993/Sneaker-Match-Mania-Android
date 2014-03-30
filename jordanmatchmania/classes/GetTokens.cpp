//
//  GetTokens.cpp
//  VivaStampede
//
//  Created by Mikhail Berrya on 12/7/13.
//
//

#include "GetTokens.h"
#include "GameSetting.h"
#include "TokenBuy.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "ObjCCalls/ObjCCalls.h"
#endif
 
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "JNICalls/InterfaceJNI.h"
#endif

CCScene* GetTokens::scene(){
    
    CCScene* scene = CCScene::create();
    GetTokens* layer = GetTokens::create();
    scene->addChild(layer);
    
    return scene;
}

 
bool GetTokens::init(){
    
    if (!CCLayer::init()) {
        return false;
    }
    
    this->setTouchEnabled(true);
    
    
    size = CCDirector::sharedDirector()->getWinSize();
    dScaleX = size.width / 768 , dScaleY = size.height / 1024;
    gameSettings = GameSettings::sharedGameSettings();
    
   
    // background
    CCSprite* background = CCSprite::create("iphone_gettokens@2x.png");
    background->setPosition(ccp(size.width / 2, size.height / 2));
    background->setScaleX(size.width/ background->getContentSize().width);
    background->setScaleY(size.height/background->getContentSize().height);
    addChild(background,3);
    
    //Token Buy Menu
    token_5 = CCMenuItemImage::create("makepurchase@2x.png", "makepurchase_pressed@2x.png", this, menu_selector(GetTokens::onToken_5));
    token_5->setScaleX(3.0f*dScaleX);
    token_5->setScaleY(token_5->getScaleY()*dScaleY*0.5);
    token_5->setPosition(ccp(size.width / 2, 850*dScaleY));
   
   
    token_10 = CCMenuItemImage::create("makepurchase@2x.png", "makepurchase_pressed@2x.png", this, menu_selector(GetTokens::onToken_10));
    token_10->setScaleX(3.0f*dScaleX);
    token_10->setScaleY(token_10->getScaleY()*dScaleY*0.5);
    token_10->setPosition(ccp(size.width / 2, 735*dScaleY));
   

    token_30 = CCMenuItemImage::create("makepurchase@2x.png", "makepurchase_pressed@2x.png", this, menu_selector(GetTokens::onToken_30));
    token_30->setScaleX(3.0f*dScaleX);
    token_30->setScaleY(token_30->getScaleY()*dScaleY*0.5);
    token_30->setPosition(ccp(size.width / 2, 620*dScaleY));
 

    token_75 = CCMenuItemImage::create("makepurchase@2x.png", "makepurchase_pressed@2x.png", this, menu_selector(GetTokens::onToken_75));
    token_75->setScaleX(3.0f*dScaleX);
    token_75->setScaleY(token_75->getScaleY()*dScaleY*0.5);
    token_75->setPosition(ccp(size.width / 2, 505*dScaleY));

    token_200 = CCMenuItemImage::create("makepurchase@2x.png", "makepurchase_pressed@2x.png", this, menu_selector(GetTokens::onToken_200));
    token_200->setScaleX(3.0f*dScaleX);
    token_200->setScaleY(token_200->getScaleY()*dScaleY*0.5);
    token_200->setPosition(ccp(size.width / 2, 390*dScaleY));
    

    token_500 = CCMenuItemImage::create("makepurchase@2x.png", "makepurchase_pressed@2x.png", this, menu_selector(GetTokens::onToken_500));
    token_500->setScaleX(3.0f*dScaleX);
    token_500->setScaleY(token_500->getScaleY()*dScaleY*0.5);
    token_500->setPosition(ccp(size.width / 2, 270*dScaleY));
   

    
    
    back = CCMenuItemImage::create("backbutton@2x.png", "backbutton@2x.png", this, menu_selector(GetTokens::onBack));
    back->setPosition(ccp(size.width / 2 - 260*dScaleX , 100*dScaleY));
    back->setScaleX(5.0f * back->getScaleX()*dScaleX);
    back->setScaleY(5.0f * back->getScaleY()*dScaleY);
   
    
    CCMenu* menu = CCMenu::create(token_5,token_10,token_30,token_75,token_200,token_500 ,back, NULL);
    menu->setPosition(CCPointZero);
    addChild(menu , 2);
    
         
    
    return true;
}


void GetTokens::ccTouchesBegan(cocos2d::CCSet *touches, cocos2d::CCEvent *event){
    
    CCTouch *touch =(CCTouch*)(touches->anyObject());
	CCPoint touchpos = touch->getLocationInView();
	touchpos = CCDirector::sharedDirector()->convertToGL(touchpos);
    
    if (touchpos.y > size.height / 2 + 280*dScaleY || touchpos.y < 150*dScaleY) {
        return;
    }
    
    if (touchpos.y > size.height / 2 - 180) {
        
    }
    
}

#define	TOKEN_5_ID		0
#define	TOKEN_10_ID		1
#define TOKEN_30_ID		2
#define TOKEN_75_ID		3
#define TOKEN_200_ID	4
#define TOKEN_500_ID	5

void GetTokens::onToken_5(CCObject* pSender){
    this->requestPurchaseToken(TOKEN_5_ID);
}
void GetTokens::onToken_10(CCObject* pSender){
    this->requestPurchaseToken(TOKEN_10_ID);
}

void GetTokens::onToken_30(CCObject* pSender){
    this->requestPurchaseToken(TOKEN_30_ID);
}

void GetTokens::onToken_75(CCObject* pSender){
    this->requestPurchaseToken(TOKEN_75_ID);
}

void GetTokens::onToken_200(CCObject* pSender){
    this->requestPurchaseToken(TOKEN_200_ID);
}
void GetTokens::onToken_500(CCObject* pSender){
    this->requestPurchaseToken(TOKEN_500_ID);
}

void GetTokens::requestPurchaseToken(int tokenID)
{
	CCLOG("GetTokens::requestPurchaseToken = %d", tokenID);
	
    if (this->tryIsInternetConnection())
    {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		InterfaceJNI::purchaseToken(tokenID);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
//         ObjCCalls::purchaseToken(tokenID);
#endif
    }
    else
    {
        this->updateMessageLabel("No internet connection to send an email");
    }	
}

bool GetTokens::tryIsInternetConnection()
{
	CCLog("tryIsInternetConnection");
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	return InterfaceJNI::isInternetConnected();
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    return ObjCCalls::tryIsInternetConnection();
#endif
}

void GetTokens::updateMessageLabel(const char *text)
{
    return;
}


void GetTokens:: onBack(CCObject *pSender){
    
    CCDirector::sharedDirector()->replaceScene(CCTransitionCrossFade::create(0.2f, TokenBuy::scene()));
        
}
