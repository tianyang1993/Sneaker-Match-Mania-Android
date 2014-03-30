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
    
        char file[0x50] = {0};
        m_nGameMode = gameSettings->getGameMode();
        if (m_nGameMode == kTagTime) {
            sprintf(file, "iphone_newgameover_notime@2x.png");
        }else {
    
            sprintf(file, "iphone_newgameover_nomatch@2x.png");
        }
    
        CCSprite* back = CCSprite::create(file);
        back->setPosition(ccp(size.width / 2, size.height / 2));
        back->setScaleX(size.width / back->getContentSize().width);
        back->setScaleY(size.height / back->getContentSize().height);
        addChild(back , 2);
    
        CCMenuItemImage* playagain = CCMenuItemImage::create("iphone_mainmenu_press.png", "iphone_playagain_press.png", this, menu_selector(GameOver::onPlayAgain));
        playagain->setPosition(ccp(size.width /5 , size.height / 7));
        playagain->setScaleX(playagain->getScaleX()*dScaleX);
        playagain->setScaleY(playagain->getScaleY()*dScaleY);
    
        CCMenuItemImage* freeapp = CCMenuItemImage::create("iphone_mainmenu_press.png", "iphone_freeapp_press.png", this, menu_selector(GameOver::onFreeApp));
        freeapp->setPosition(ccp(size.width /2 , size.height / 7));
        freeapp->setScaleX(freeapp->getScaleX()*dScaleX);
        freeapp->setScaleY(freeapp->getScaleY()*dScaleY);
    
        CCMenuItemImage* mainmenu = CCMenuItemImage::create("iphone_mainmenu_press.png", "iphone_mainmenu_press.png", this, menu_selector(GameOver::onMainMenu));
        mainmenu->setPosition(ccp(size.width *4/5 , size.height / 7));
        mainmenu->setScaleX(mainmenu->getScaleX()*dScaleX);
        mainmenu->setScaleY(mainmenu->getScaleY()*dScaleY);
    
        CCMenu* menu = CCMenu::create(playagain , freeapp , mainmenu , NULL);
        menu->setPosition(CCPointZero);
        addChild(menu , 1);
    
    
     
        ccFontDefinition strokeTextDef;
        strokeTextDef.m_fontSize = 70*dScaleX;
        strokeTextDef.m_fontName = std::string("Dimbo Regular");
        strokeTextDef.m_stroke.m_strokeColor   = ccYELLOW;
        strokeTextDef.m_stroke.m_strokeEnabled = true;
        strokeTextDef.m_stroke.m_strokeSize    = 3.0f;
        
        sprintf(file, "%d" , gameSettings->getGameScore());
        m_lHighScore = CCLabelTTF::createWithFontDefinition(file, strokeTextDef);
        m_lHighScore->setPosition(ccp(size.width / 2, size.height / 2 +50*dScaleY));
        addChild(m_lHighScore , 3);
    
        sprintf(file, " HighScore  %d" , gameSettings->getGameScore());
        m_lLabelHighScore = CCLabelTTF::createWithFontDefinition(file, strokeTextDef);
        m_lLabelHighScore->setPosition(ccp(size.width / 2, size.height / 2-200*dScaleY));
        addChild(m_lLabelHighScore , 3);

     
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