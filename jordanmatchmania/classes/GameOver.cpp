//
//  GameOver.cpp
//  VivaStampede
//
//  Created by Mikhail Berrya on 12/2/13.
//
//

#include "GameOver.h"
#include "GameScene.h"
#include "MoreLayer.h"
#include "MainView.h"
#include "Define.h"

GameOver* GameOver::layer(){
    
    static GameOver* layer = GameOver::create();
    return layer;
}

void GameOver::initWithGame(GameScene* nScene){
  
    if (this != NULL)
    {
        size  = CCDirector::sharedDirector()->getWinSize();
        dScaleX = size.width / 768 , dScaleY = size.height / 1024;
        gameSettings = GameSettings::sharedGameSettings();
        gameScene = nScene;
    
        CCSprite* back = CCSprite::create("bkg_default@2x.png");
        back->setPosition(ccp(size.width / 2, size.height / 2));
        back->setScaleX(size.width / back->getContentSize().width);
        back->setScaleY(size.height / back->getContentSize().height);
        addChild(back , 2);
        
        float scale_x = size.width / back->getContentSize().width;
        float scale_y = size.height / back->getContentSize().height;
        
        CCSprite* popUp = CCSprite::create("Text_TryAgain@2x.png");
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
        
        CCMenuItemImage *noButton = CCMenuItemImage::create("Button_NO_1@2x.png", "Button_NO_hit@2x.png", "button_NO_2@2x.png", this, menu_selector(GameOver::onMainMenu));
        noButton->setPosition(ccp(getX(84, 162) * scale_x, getY(size.height,102, 738) * scale_y));
        noButton->setScaleX(scale_x);
        noButton->setScaleY(scale_y);
        
        CCMenuItemImage *yesButton = CCMenuItemImage::create("Button_YES_1@2x.png", "Button_YES_hit@2x.png", "button_YES_2@2x.png", this, menu_selector(GameOver:: onPlayAgain));
        yesButton->setPosition(ccp(getX(394, 162) * scale_x, getY(size.height,102, 738) * scale_y));
        yesButton->setScaleX(scale_x);
        yesButton->setScaleY(scale_y);
        
        CCMenu* menu = CCMenu::create(noButton,yesButton,NULL);
        menu->setPosition(CCPointZero);
        addChild(menu, 12);
     
    }
    return;
}

void GameOver:: onPlayAgain(cocos2d::CCObject *pSender){
    
    gameScene->restartLevel();
    this->removeAllChildren();
    this->removeFromParent();
    
     
}

void GameOver:: onFreeApp(cocos2d::CCObject *pSender){
    
    CCDirector::sharedDirector()->replaceScene(CCTransitionCrossFade::create(0.5f, MoreScene::scene()));
}

void GameOver::onMainMenu(cocos2d::CCObject *pSender){
    
    CCDirector::sharedDirector()->replaceScene(CCTransitionCrossFade::create(0.5f, MainView::scene()));
    
}