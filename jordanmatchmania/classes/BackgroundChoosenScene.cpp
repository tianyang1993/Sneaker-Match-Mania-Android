//
//  BackgroundChoosenScene.cpp
//  VivaStampede
//
//  Created by Mikhail Berrya on 11/25/13.
//
//

#include "BackgroundChoosenScene.h"
#include "MainView.h"
#include "CCAlertView.h"

CCScene* BackgroundChoosenScene::scene(){
    CCScene* scene = CCScene::create();
    BackgroundChoosenScene* temp = BackgroundChoosenScene::create();
    scene->addChild(temp);
    return scene;
    
}

bool BackgroundChoosenScene::init(){
    
    if (!CCLayer::init()) {
        return false;
    }
    
    size = CCDirector::sharedDirector()->getWinSize();
    double dScalX = size.width / 768,dScalY = size.height / 1024;
    gameSettings = GameSettings::sharedGameSettings();
   
    
    CCSprite* back = CCSprite ::create("choosebackgroundblank@2x.png");
    back->setScaleX(size.width / back->getContentSize().width);
    back->setScaleY (size.height / back->getContentSize().height);
    back->setPosition(ccp(size.width / 2, size.height / 2));
    addChild(back);
    
    //back
    backButton = CCMenuItemImage::create("backbutton@2xold.png", "backbutton@2xold.png", this, menu_selector(BackgroundChoosenScene::onBack));
    backButton->setPosition(ccp( 80* dScalX, 950*dScalY));
    backButton->setScaleX(backButton->getScaleX()* dScalX*2);
    backButton->setScaleY(backButton->getScaleY()* dScalY*2);
    
    restorePurchase = CCMenuItemImage::create("restore@2x.png", "restore@2x.png",this,menu_selector(BackgroundChoosenScene::onRestore));
    restorePurchase->setPosition(ccp(size.width - 80* dScalX, 950*dScalY));
    restorePurchase->setScaleX(restorePurchase->getScaleX()* dScalX);
    restorePurchase->setScaleY(restorePurchase->getScaleY()* dScalY);
    // Arabian Nights Button
    backgroundImage1 = CCMenuItemImage::create("iapbgbutton1@2x.png", "iapbgbutton1@2x.png", this, menu_selector(BackgroundChoosenScene::onBack1));
    backgroundImage1->setPosition(ccp(size.width / 2 -200* dScalX, 180*dScalY));
    backgroundImage1->setScaleX(backgroundImage1->getScaleX()* dScalX);
    backgroundImage1->setScaleY(backgroundImage1->getScaleY()* dScalY*0.9);
    
    
    
    // The Outback
    backgroundImage2 = CCMenuItemImage::create("iapbgbutton2@2x.png","iapbgbutton2@2x.png", this, menu_selector(BackgroundChoosenScene::onBack2));
    backgroundImage2->setPosition(ccp(size.width /2+200* dScalX, 180*dScalY));
    backgroundImage2->setScaleX(backgroundImage2->getScaleX()* dScalX);
    backgroundImage2->setScaleY(backgroundImage2->getScaleY()* dScalY*0.9);
    
    
    
    // Grassy Knoll
    backgroundImage3 = CCMenuItemImage::create("iapbgbutton3@2x.png", "iapbgbutton3@2x.png", this, menu_selector(BackgroundChoosenScene::onBack3));
    backgroundImage3->setPosition(ccp(size.width / 2, 380*dScalY));
    backgroundImage3->setScaleX(backgroundImage3->getScaleX()* dScalX);
    backgroundImage3->setScaleY(backgroundImage3->getScaleY()* dScalY*0.9);
    
    
    
    // Loose in the City
    backgroundImage4 = CCMenuItemImage::create("iapbgbutton4@2x.png", "iapbgbutton4@2x.png", this, menu_selector(BackgroundChoosenScene::onBack4));
    backgroundImage4->setPosition(ccp(size.width / 2 -200* dScalX, 600*dScalY));
    backgroundImage4->setScaleX(backgroundImage4->getScaleX()* dScalX);
    backgroundImage4->setScaleY(backgroundImage4->getScaleY()* dScalY*0.9);
    
    
    
    // Outer Space
    backgroundImage5 = CCMenuItemImage::create("iapbgbutton5@2x.png", "iapbgbutton5@2x.png", this, menu_selector(BackgroundChoosenScene::onBack5));
    backgroundImage5->setPosition(ccp(size.width /2+200* dScalX, 600*dScalY));
    backgroundImage5->setScaleX(backgroundImage5->getScaleX()* dScalX);
    backgroundImage5->setScaleY(backgroundImage5->getScaleY()* dScalY*0.9);
    
    CCMenu* menu = CCMenu::create(backButton,restorePurchase, backgroundImage1,backgroundImage2,backgroundImage3,backgroundImage4,backgroundImage5,NULL);
    menu->setPosition(CCPointZero);
    addChild(menu);
    
    
    
    return true;
}

void BackgroundChoosenScene::onBack(cocos2d::CCObject *pSender){
    
    gameSettings->setPlayed(true);
    CCDirector::sharedDirector()->replaceScene(MainView::scene());
    
    CCAlertView *alert = CCAlertView::create( "Confirm Your In-App\n Purchase","Do you want to buy one More Cool\nbackgrounds for 33.p?\n[Environment : Sandbox]","Cancel", "Buy", this, callfuncO_selector(BackgroundChoosenScene::popupCancel), callfuncO_selector(BackgroundChoosenScene::popupBuy));
    this->addChild(alert, 100);
    
    
}
void BackgroundChoosenScene::onBack1(CCObject *pSender){
    
    //gameSettings->setBackGround(1);
    CCAlertView *alert = CCAlertView::create( "Confirm Your In-App\n Purchase","Do you want to buy one More Cool\nbackgrounds for 33.p?\n[Environment : Sandbox]","Cancel", "Buy", this, callfuncO_selector(BackgroundChoosenScene::popupCancel), callfuncO_selector(BackgroundChoosenScene::popupBuy));
    this->addChild(alert, 100);

}

void BackgroundChoosenScene::onBack2(CCObject *pSender){
    
    //gameSettings->setBackGround(2);
    CCAlertView *alert = CCAlertView::create( "Confirm Your In-App\n Purchase","Do you want to buy one More Cool\nbackgrounds for 33.p?\n[Environment : Sandbox]","Cancel", "Buy", this, callfuncO_selector(BackgroundChoosenScene::popupCancel), callfuncO_selector(BackgroundChoosenScene::popupBuy));
    this->addChild(alert, 100);

}
void BackgroundChoosenScene::onBack3(CCObject *pSender){
    
    //gameSettings->setBackGround(3);
    CCAlertView *alert = CCAlertView::create( "Confirm Your In-App\n Purchase","Do you want to buy one More Cool\nbackgrounds for 33.p?\n[Environment : Sandbox]","Cancel", "Buy", this, callfuncO_selector(BackgroundChoosenScene::popupCancel), callfuncO_selector(BackgroundChoosenScene::popupBuy));
    this->addChild(alert, 100);

    
}
void BackgroundChoosenScene::onBack4(CCObject *pSender){
    
    //gameSettings->setBackGround(4);
    CCAlertView *alert = CCAlertView::create( "Confirm Your In-App\n Purchase","Do you want to buy one More Cool\nbackgrounds for 33.p?\n[Environment : Sandbox]","Cancel", "Buy", this, callfuncO_selector(BackgroundChoosenScene::popupCancel), callfuncO_selector(BackgroundChoosenScene::popupBuy));
    this->addChild(alert, 100);

}
void BackgroundChoosenScene::onBack5(CCObject *pSender){
    
  
    CCAlertView *alert = CCAlertView::create( "Confirm Your In-App\n Purchase","Do you want to buy one More Cool\nbackgrounds for 33.p?\n[Environment : Sandbox]","Cancel", "Buy", this, callfuncO_selector(BackgroundChoosenScene::popupCancel), callfuncO_selector(BackgroundChoosenScene::popupBuy));
    this->addChild(alert, 100);
    //gameSettings->setBackGround(0);

     
}
void BackgroundChoosenScene::onRestore(CCObject *pSender){
    
    CCLOG("Restore");
}

void BackgroundChoosenScene:: popupBuy(cocos2d::CCObject *pSender){
    
}

void BackgroundChoosenScene::popupCancel(cocos2d::CCObject *pSender){
    
    CCAlertView* alert = (CCAlertView*) pSender;
    this->removeChild(alert, true);

}


