//
//  GameOverLayer.cpp
//  VivaStampede
//
//  Created by Mikhail Berrya on 12/2/13.
//
//

#include "LevelCompleted.h"
#include "GameScene.h"
#include "Define.h"

LevelCompleted* LevelCompleted::layer(){
   
    LevelCompleted* layer = LevelCompleted::create();
    return layer;
}

bool LevelCompleted::init(){
    
    if (!CCLayer::init()) {
        return false;
    }

    this->setTouchEnabled(true);
    size = CCDirector::sharedDirector()->getWinSize();
    dScaleX = size.width / 768 , dScaleY = size.height / 1024;
    return true;
}

void LevelCompleted::initWithGame(GameScene *nScene){
    
    m_nGameScene = nScene;
    CCSprite *bgSprite = CCSprite::create("bkg_default@2x.png");
    //bgSprite->setTextureRect(CCRect(0, 0, size.width, size.height));
    bgSprite->setPosition(ccp(size.width / 2, size.height / 2));
    //bgSprite->setColor(ccc3(0, 0, 0));
    //bgSprite->setOpacity(0);
    this->addChild(bgSprite, 10);
    //bgSprite->runAction(CCFadeTo::create(0.5f, 150));
    
    float scale_x = size.width / bgSprite->getContentSize().width;
    float scale_y = size.height / bgSprite->getContentSize().height;

    popUp = CCSprite::create("Text_Congrats@2x.png");
    popUp->setPosition(ccp(size.width / 2, size.height / 2 + 100));
 
    addChild(popUp , 11);

    CCFiniteTimeAction *scale1 = CCScaleTo::create(0.15f, 1.1f*dScaleX);
    CCFiniteTimeAction *scale2 = CCScaleTo::create(0.05f, 0.9f*dScaleX);
    CCFiniteTimeAction *scale3 = CCScaleTo::create(0.05f, 1.0f*dScaleX);
    popUp->runAction(CCSequence::create(scale1, scale2, scale3, NULL));

    CCSprite* spAdBanner = CCSprite::create("ad@2x.png");
    spAdBanner->setPosition(ccp(size.width / 2 , getY(size.height, 100, 860) * scale_y));
    spAdBanner->setScaleX(scale_x);
    spAdBanner->setScaleY(scale_y);
    addChild(spAdBanner,12);

    CCMenuItemImage *endButton = CCMenuItemImage::create("Button_END_1@2x.png", "Button_END_hit@2x.png", "button_END_2@2x.png", this, menu_selector(LevelCompleted::onClickEnd));
    endButton->setPosition(ccp(getX(84, 162) * scale_x, getY(size.height,102, 738) * scale_y));
    endButton->setScaleX(scale_x);
    endButton->setScaleY(scale_y);
    
    CCMenuItemImage *nextButton = CCMenuItemImage::create("Button_NEXT_1@2x.png", "Button_NEXT_hit@2x.png", "button_NEXT_2@2x.png", this, menu_selector(LevelCompleted::onClickNext));
    nextButton->setPosition(ccp(getX(394, 162) * scale_x, getY(size.height,102, 738) * scale_y));
    nextButton->setScaleX(scale_x);
    nextButton->setScaleY(scale_y);
    
    CCMenu* menu = CCMenu::create(endButton,nextButton,NULL);
    menu->setPosition(CCPointZero);
    addChild(menu, 12);

}

void LevelCompleted::onClickEnd(){
    
}

void LevelCompleted::onClickNext(){
    
}

void LevelCompleted::ccTouchesBegan(CCSet* touches,CCEvent* event){
    CCTouch *touch =(CCTouch*)(touches->anyObject());
    CCPoint touchPos = touch->getLocationInView();
    touchPos = CCDirector::sharedDirector()->convertToGL(touchPos);
    if (m_nGameScene != NULL) {
        this->setTouchEnabled(false);
        CCFiniteTimeAction *scale1 = CCScaleTo::create(0.15f, 1.1f*dScaleX);
        CCFiniteTimeAction *scale2 = CCScaleTo::create(0.05f, 0.9f*dScaleX);
        CCFiniteTimeAction *scale3 = CCScaleTo::create(0.01f, 0.0f*dScaleX);
        popUp->runAction(CCSequence::create(scale1, scale2, scale3, NULL));
        this->schedule(schedule_selector(LevelCompleted::restart), 0.8f);
        
    }
}
void LevelCompleted::restart(cocos2d::CCObject *pSender){
    this->unschedule(schedule_selector(LevelCompleted::restart));
    this->removeFromParent();
    m_nGameScene->showNextLevel();
}
 