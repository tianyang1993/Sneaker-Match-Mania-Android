//
//  JoinLayer.cpp
//  jordanmatchmania
//
//  Created by Lion on 3/24/14.
//
//

#include "JoinLayer.h"
#include "Define.h"
#include "GameScene.h"

using namespace cocos2d;

CCScene* JoinLayer::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    JoinLayer *layer = JoinLayer::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool JoinLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    //    double dScalX = size.width / 768 , dScalY= size.height / 1024;
    CCSprite* backgroundView = CCSprite::create("bkg@2x.png");
    backgroundView->setPosition(ccp(size.width / 2, size.height / 2));
    float scale_x = size.width / backgroundView->getContentSize().width;
    float scale_y = size.height / backgroundView->getContentSize().height;
    backgroundView->setScaleX(scale_x);
    backgroundView->setScaleY(scale_y);
    addChild(backgroundView);
    
    CCSprite* spCharacter = CCSprite::create("characters@2x.png");
    spCharacter->setPosition(ccp(size.width / 2, size.height / 2));
    spCharacter->setScaleX(scale_x);
    spCharacter->setScaleY(scale_y);
    addChild(spCharacter);
    
    CCSprite* spLogo = CCSprite::create("loading_logo@2x.png");
    spLogo->setPosition(ccp(size.width / 2 , getY(size.height, 304, 71) * scale_y));
    spLogo->setScaleX(scale_x);
    spLogo->setScaleY(scale_y);
    addChild(spLogo);
    
    CCSprite* spAdBanner = CCSprite::create("ad@2x.png");
    spAdBanner->setPosition(ccp(size.width / 2 , getY(size.height, 50, 910) * scale_y));
    spAdBanner->setScaleX(scale_x);
    spAdBanner->setScaleY(scale_y);
    addChild(spAdBanner);
    
    CCMenuItemImage *playButton = CCMenuItemImage::create("Button_PLAY@2x.png", "Button_PLAY_hit@2x.png", this, menu_selector(JoinLayer::onClickPlay));
    playButton->setPosition(ccp(size.width / 2, getY(size.height, 152, 664)));
    playButton->setScaleX(scale_x);
    playButton->setScaleY(scale_y);
    
    CCMenu* menu = CCMenu::create(playButton,NULL);
    menu->setPosition(CCPointZero);
    addChild(menu);
    
    return true;
}


void JoinLayer::onClickPlay(){
    
    CCDirector::sharedDirector()->replaceScene(CCTransitionCrossFade::create(0.5f, GameScene::scene()));
}