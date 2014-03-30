//
//  IntroLayer.cpp
//  VivaStampede
//
//  Created by Mikhail Berrya on 11/25/13.
//
//

#include "IntroLayer.h"
#include "SimpleAudioEngine.h"
#include "MainView.h"
#include "Define.h"
#include "ValuesManager.h"
#include "GameSetting.h" 

using namespace cocos2d;
using namespace CocosDenshion;

CCScene* IntroLayer::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    IntroLayer *layer = IntroLayer::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool IntroLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSize size = CCDirector::sharedDirector()->getWinSize();
//    double dScalX = size.width / 768 , dScalY= size.height / 1024;
    CCSprite* back = CCSprite::create("bkg_default@2x.png");
    back->setPosition(ccp(size.width / 2 , size.height / 2));
    
    float scale_x = size.width / back->getContentSize().width;
    float scale_y = size.height / back->getContentSize().height;

    back->setScaleX(scale_x);
    back->setScaleY(scale_y);
    addChild(back);

    CCSprite* spLogo = CCSprite::create("loading_logo@2x.png");
    spLogo->setPosition(ccp(size.width / 2 , getY(size.height, 304, 71) * scale_y));
    spLogo->setScaleX(scale_x);
    spLogo->setScaleY(scale_y);
    addChild(spLogo);

    CCSprite* spTextLogo = CCSprite::create("Text_Loading@2x.png");
    spTextLogo->setPosition(ccp(size.width / 2 , getY(size.height, 71, 666) * scale_y));
    spTextLogo->setScaleX(scale_x);
    spTextLogo->setScaleY(scale_y);
    addChild(spTextLogo);

    CCSprite* spAdBanner = CCSprite::create("ad@2x.png");
    spAdBanner->setPosition(ccp(size.width / 2 , getY(size.height, 50, 910) * scale_y));
    spAdBanner->setScaleX(scale_x);
    spAdBanner->setScaleY(scale_y);
    addChild(spAdBanner);

    CCSprite* spLoadingBar = CCSprite::create("loadingbar01@2x.png");
    spLoadingBar->setPosition(ccp(size.width / 2 , getY(size.height, 102, 746) * scale_y));
    spLoadingBar->setScaleX(scale_x);
    spLoadingBar->setScaleY(scale_y);
    addChild(spLoadingBar);

    CCAnimation* animLoadingBar = CCAnimation::create();
    char str[100] = {0};
    
    for (int i = 1; i <= 20; i++) {
        sprintf(str, "loadingbar0%d@2x.png", i);
        animLoadingBar->addSpriteFrameWithFileName(str);
    }

    animLoadingBar->setLoops(1);
    animLoadingBar->setDelayPerUnit(0.1);
    CCAnimate* ani = CCAnimate::create(animLoadingBar);
    spLoadingBar->runAction(ani);

//    animLoadingBar->runAction( CCSequence::create(ani,CCCallFuncN::create( this, callfuncN_selector(IntroLayer::Next)), NULL) );
    
    GameSettings::sharedGameSettings()->playBackGround((char*)kIntroMusic);
    
    this->schedule(schedule_selector(IntroLayer::Next), 2.0f);
    return true;
}

void IntroLayer::Next(CCObject *pSender){
    
    GameSettings::sharedGameSettings()->stopBackground();
    CCDirector::sharedDirector()->replaceScene(CCTransitionCrossFade::create(0.5f, MainView::scene()));
}

