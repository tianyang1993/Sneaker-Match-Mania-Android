//
//  TokenBuy.cpp
//  VivaStampede
//
//  Created by Mikhail Berrya on 11/25/13.
//
//

#include "TokenBuy.h"
#include "MainView.h"
#include "GameSetting.h"
#include "GetTokens.h"
#include "GameScene.h"
CCScene* TokenBuy::scene(){
    
    CCScene* scene = CCScene::create();
    TokenBuy* layer = TokenBuy::create();
    scene->addChild(layer);
    
    return scene;
}

TokenBuy* TokenBuy::body(){
    
    static TokenBuy* temp = TokenBuy::create();
    return temp;
}

bool TokenBuy::init(){
    
    if (!CCLayer::init()) {
        return false;
    }
    
    this->setTouchEnabled(true);
   
    
    size = CCDirector::sharedDirector()->getWinSize();
    dScaleX = size.width / 768 , dScaleY = size.height / 1024;
    gameSettings = GameSettings::sharedGameSettings();
    
    selectItem = CCSprite::create("itemselect@2x.png");
    selectItem->setScaleX(selectItem->getScaleX()*dScaleX);
    selectItem->setScaleY(selectItem->getScaleY()*dScaleY);
    addChild(selectItem,5);
    
    
    selectItem0 = CCMenuItemImage::create("stuckpopup@2x.png", "stuckpopup@2x.png", this, menu_selector(TokenBuy::onSelect0));
    selectItem0->setScaleX(3*dScaleX);
    selectItem0->setScaleY(selectItem0->getScaleY()*dScaleY*0.5);
    
    selectItem1 = CCMenuItemImage::create("stuckpopup@2x.png", "stuckpopup@2x.png", this, menu_selector(TokenBuy::onSelect1));
    selectItem1->setScaleX(3*dScaleX);
    selectItem1->setScaleY(selectItem1->getScaleY()*dScaleY*0.5);
   
    selectItem2 = CCMenuItemImage::create("stuckpopup@2x.png", "stuckpopup@2x.png", this, menu_selector(TokenBuy::onSelect2));
    selectItem2->setScaleX(3*dScaleX);
    selectItem2->setScaleY(selectItem2->getScaleY()*dScaleY*0.5);
   
    selectItem3 = CCMenuItemImage::create("stuckpopup@2x.png", "stuckpopup@2x.png", this, menu_selector(TokenBuy::onSelect3));
    selectItem3->setScaleX(3*dScaleX);
    selectItem3->setScaleY(selectItem3->getScaleY()*dScaleY*0.5);
    
    selectItem4 = CCMenuItemImage::create("stuckpopup@2x.png", "stuckpopup@2x.png", this, menu_selector(TokenBuy::onSelect4));
    selectItem4->setScaleX(3*dScaleX);
    selectItem4->setScaleY(selectItem4->getScaleY()*dScaleY*0.5);
    
    selectItem5 = CCMenuItemImage::create("stuckpopup@2x.png", "stuckpopup@2x.png", this, menu_selector(TokenBuy::onSelect5));
    selectItem5->setScaleX(3*dScaleX);
    selectItem5->setScaleY(selectItem5->getScaleY()*dScaleY*0.5);
 
    selectItem0->setPosition(ccp(size.width*3/4 - 15*dScaleX, 805*dScaleY));
    selectItem1->setPosition(ccp(size.width*3/4 - 15*dScaleX, 730*dScaleY));
    selectItem2->setPosition(ccp(size.width*3/4 - 15*dScaleX, 650*dScaleY));
    selectItem3->setPosition(ccp(size.width*3/4 - 15*dScaleX, 578*dScaleY));
    selectItem4->setPosition(ccp(size.width*3/4 - 15*dScaleX, 492*dScaleY));
    selectItem5->setPosition(ccp(size.width*3/4 - 15*dScaleX, 408*dScaleY));
  


  
// background
    CCSprite* background = CCSprite::create("iphone_newstore@2x.png");
    background->setPosition(ccp(size.width / 2, size.height / 2));
    background->setScaleX(size.width/ background->getContentSize().width);
    background->setScaleY(size.height/background->getContentSize().height);
    addChild(background,3);

    
    smalTokon = CCSprite::create("makepurchase@2x.png");
    smalTokon->setPosition(ccp(size.width / 4, size.height /2 + 240*dScaleY));
    smalTokon->setScaleX(smalTokon->getScaleX()*dScaleX);
    smalTokon->setScaleY(smalTokon->getScaleY()*dScaleY);
    
    
    
    mediumToken = CCSprite::create("makepurchase@2x.png");
    mediumToken->setPosition(ccp(size.width / 4, size.height / 2+ 80*dScaleY));
    mediumToken->setScaleX(mediumToken->getScaleX()*dScaleX);
    mediumToken->setScaleY(mediumToken->getScaleY()*dScaleY);
    
    
    largToken = CCSprite::create("makepurchase@2x.png");
    largToken->setPosition(ccp(size.width / 4, size.height / 2 -80*dScaleY));
    largToken->setScaleX(largToken->getScaleX()*dScaleX);
    largToken->setScaleY(largToken->getScaleY()*dScaleY);
    
    
    removeAdsButton = CCSprite::create("makepurchase@2x.png");
    removeAdsButton->setPosition(ccp(size.width / 4, size.height / 2 -240*dScaleY));
    removeAdsButton->setScaleX(removeAdsButton->getScaleX()*dScaleX);
    removeAdsButton->setScaleY(removeAdsButton->getScaleY()*dScaleY);
    
    
    
    redeem = CCMenuItemImage::create("makepurchase@2x.png", "makepurchase_pressed@2x.png", this, menu_selector(TokenBuy::onRedeem));
    redeem->setPosition(ccp(size.width / 2, 120*dScaleY));
    redeem->setScaleX(redeem->getScaleX()*dScaleX);
    redeem->setScaleY(redeem->getScaleY()*dScaleY);
    redeem->setVisible(false);
    
       
    
    back = CCMenuItemImage::create("backbutton@2x.png", "backbutton@2x.png", this, menu_selector(TokenBuy::onBack));
    back->setPosition(ccp(size.width / 2 - 260*dScaleX , 100*dScaleY));
    back->setScaleX(2.0f * back->getScaleX()*dScaleX);
    back->setScaleY(2.0f * back->getScaleY()*dScaleY);
    back->setVisible(true);
    
    CCMenu* menu = CCMenu::create(redeem,back, NULL);
    menu->setPosition(CCPointZero);
    addChild(menu , 4);
    
    CCMenu* menu2 = CCMenu::create(selectItem0 , selectItem1,selectItem2,selectItem3,selectItem4,selectItem5,NULL);
    menu2->setPosition(CCPointZero);
    addChild(menu2 , 2);

    byteCount = gameSettings->getByteCount();
    char file[0x80] = {0};
    sprintf(file, "%d" , byteCount);
    ccColor3B strokeColor       =  { 255, 255, 255  };
    ccFontDefinition strokeTextDef;
    strokeTextDef.m_fontSize = 60*dScaleX;
    strokeTextDef.m_fontName = std::string("Dimbo Regular");
    strokeTextDef.m_stroke.m_strokeColor   = strokeColor;
    strokeTextDef.m_stroke.m_strokeEnabled = true;
    strokeTextDef.m_stroke.m_strokeSize    = 3.0f;
    
    
    
    ByteLabel = CCLabelTTF::createWithFontDefinition(file, strokeTextDef);
    ByteLabel->setPosition(ccp(size.width-80*dScaleX, 110*dScaleY));
    ByteLabel->setScaleY(1.0f*dScaleY);
    ByteLabel->setScaleX(1.0f*dScaleX);
    addChild(ByteLabel , 10);

    return true;
}

void TokenBuy::ccTouchesBegan(cocos2d::CCSet *touches, cocos2d::CCEvent *event){
    
    CCTouch *touch =(CCTouch*)(touches->anyObject());
	CCPoint touchpos = touch->getLocationInView();
	touchpos = CCDirector::sharedDirector()->convertToGL(touchpos);
    if ((size.width / 2 -100*dScaleX < touchpos.x < size.width / 2 + 100*dScaleX) &&(55*dScaleY < touchpos.y && touchpos.y < 150*dScaleY)&&(redeem->isVisible()==false)) {
//        this->removeAllChildren();
        
        gotoTokenBuy();
    
    }
    
}

void TokenBuy:: gotoTokenBuy(){
    CCLog("TokenBuy::gotoTokenBuy() is called");
    CCDirector::sharedDirector()->replaceScene(GetTokens::scene());
}

void TokenBuy::onRedeem(CCObject* pSender){
	CCLog("TokenBuy::onRedeem() is called");

	redeem->setVisible(false);
   
    CCAlertView *alert = CCAlertView::create( "Not enough Tokens","You`re gonna need more Tokens for\nthis. Get some now!","Cancel", "Get!", this, callfuncO_selector(TokenBuy::popupCancel), callfuncO_selector(TokenBuy::popupBuy));
    this->addChild(alert, 100);

    
    CCLOG("RedeeHandler");
}
void TokenBuy:: popupBuy(cocos2d::CCObject *pSender){
    CCLog("TokenBuy::popupBuy() is called");
    CCDirector::sharedDirector()->replaceScene(GetTokens::scene());
}

void TokenBuy::popupCancel(cocos2d::CCObject *pSender){
    
    CCAlertView* alert = (CCAlertView*) pSender;
    this->removeChild(alert, true);
    
}

void TokenBuy:: onBack(CCObject *pSender){
   
    if (gameSettings->getSuperType() == 1) {
        
        CCDirector::sharedDirector()->replaceScene(CCTransitionCrossFade::create(0.2f, GameScene::scene()));
    }else if(gameSettings->getSuperType() == 2){
        gameSettings->setPlayed(true);
        CCDirector::sharedDirector()->replaceScene(CCTransitionCrossFade::create(0.2f, MainView::scene()));
    }
   
}

void TokenBuy:: onSelect0(cocos2d::CCObject *pSender){
    redeem->setVisible(true);
    selectItem->setPosition(ccp(size.width*3/4 - 15*dScaleX, 800*dScaleY));
    
}

void TokenBuy:: onSelect1(cocos2d::CCObject *pSender){
    
    redeem->setVisible(true);
    selectItem->setPosition(ccp(size.width*3/4 - 15*dScaleX, 750*dScaleY));

}
void TokenBuy:: onSelect2(cocos2d::CCObject *pSender){
    redeem->setVisible(true);
    selectItem->setPosition(ccp(size.width*3/4 - 15*dScaleX, 640*dScaleY));
    
}
void TokenBuy:: onSelect3(cocos2d::CCObject *pSender){
    redeem->setVisible(true);
    selectItem->setPosition(ccp(size.width*3/4 - 15*dScaleX, 590*dScaleY));
    
}
void TokenBuy:: onSelect4(cocos2d::CCObject *pSender){
    redeem->setVisible(true);
    selectItem->setPosition(ccp(size.width*3/4 - 15*dScaleX, 470*dScaleY));
    
}void TokenBuy:: onSelect5(cocos2d::CCObject *pSender){
    
    redeem->setVisible(true);
    selectItem->setPosition(ccp(size.width*3/4 - 15*dScaleX, 420*dScaleY));
}