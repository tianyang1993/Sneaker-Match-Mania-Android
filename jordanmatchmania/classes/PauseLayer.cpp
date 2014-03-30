//
//  PauseLayer.cpp
//  VivaStampede
//
//  Created by Mikhail Berrya on 11/25/13.
//
//

#include "PauseLayer.h"
#include "GameSetting.h"
#include "GameScene.h"
#include "MainView.h"
#include "SimpleAudioEngine.h"
PauseLayer* PauseLayer::pause(){
    
    PauseLayer* layer = PauseLayer::create();
    return layer;
}

void PauseLayer::initWithGame(GameScene *nScene){
    
    if (this == NULL) {
        return ;
    }
    
    m_nScene = nScene;
    m_nGameSettings = GameSettings::sharedGameSettings();
   
    size = CCDirector::sharedDirector()->getWinSize();
    dScaleX = size.width / 768 , dScaleY = size.height / 1024;
    
    setBackGroundView(m_nGameSettings->getBackground());    
    ccColor3B strokeColor       =  { 255, 255, 255 };
    ccFontDefinition strokeTextDef;
    strokeTextDef.m_fontSize = 40*dScaleX;
    strokeTextDef.m_fontName = std::string("Dimbo Regular");
    strokeTextDef.m_stroke.m_strokeColor   = strokeColor;
    strokeTextDef.m_stroke.m_strokeEnabled = true;
    strokeTextDef.m_stroke.m_strokeSize    = 3.0f;
    
    
    
    CCMenuItemFont::setFontSize(60*dScaleX);
    CCMenuItemFont::setFontName("Dimbo Regular");
    
    resume = CCMenuItemFont::create("Resume", this, menu_selector(PauseLayer::onResume));
    resume->setPosition(ccp(size.width / 2, size.height / 2 + 300*dScaleY));
    resume->setFontName("Dimbo Regular");
    
    
    restart = CCMenuItemFont::create("Restart", this, menu_selector(PauseLayer::onRestart));
    restart->setPosition(ccp(size.width / 2, size.height / 2 + 200*dScaleY));
    restart->setFontName("Dimbo Regular");
    
    mainmenu = CCMenuItemFont::create("MainMenu", this, menu_selector(PauseLayer::onMainMenu));
    mainmenu->setPosition(ccp(size.width / 2, size.height / 2 + 100*dScaleY));
    
    getfreeapp = CCMenuItemFont::create("GetFree App", this, menu_selector(PauseLayer::onGetFreeApp));
    getfreeapp->setPosition(ccp(size.width / 2, size.height / 2 ));
    
    sfxoff = CCMenuItemFont::create("SFX Off", this, menu_selector(PauseLayer::onSfxOn));
    sfxoff->setPosition(ccp(size.width / 2, size.height / 2 -100*dScaleY));
    
    
    sfxon = CCMenuItemFont::create("SFX ON", this, menu_selector(PauseLayer::onSfxOn));
    sfxon->setPosition(ccp(size.width / 2, size.height / 2 -100*dScaleY));
    
    bool visibleE = CCUserDefault::sharedUserDefault()->getBoolForKey("effectSound");
    if (visibleE) {
        sfxoff->setVisible(false);
    }else if(!visibleE){
        sfxon->setVisible(false);
    }
    
    
    musicoff = CCMenuItemFont::create("Music Off", this, menu_selector(PauseLayer::onMusicOn));
    musicoff->setPosition(ccp(size.width / 2, size.height / 2 -200*dScaleY));
    
    
    musicon = CCMenuItemFont::create("Music On", this, menu_selector(PauseLayer::onMusicOn));
    musicon->setPosition(ccp(size.width / 2, size.height / 2 -200*dScaleY));
     
    
    bool visibleB = CCUserDefault::sharedUserDefault()->getBoolForKey("backgroundSound");
    if (visibleB) {
        musicoff->setVisible(false);
    }else if(!visibleB){
        musicon->setVisible(false);
    }

    
    CCActionInterval* color_action = CCTintBy::create(0.5f, 0, -255, -255);
    CCActionInterval* color_back = color_action->reverse();
    CCSequence* seq = CCSequence::create(color_action, color_back, NULL);
    getfreeapp->runAction(CCRepeatForever::create(seq));
    
    
    CCMenu* menu = CCMenu::create(resume , restart, mainmenu , getfreeapp , sfxoff , sfxon , musicoff , musicon , NULL);
    menu->setPosition(CCPointZero);
    
    addChild(menu);
    
}
void PauseLayer:: setBackGroundView(int nType){
    
    char file[0x90] = {0};
    switch (nType) {
        case 0:
            sprintf(file, "background@2x.png");
            break;
        case 1:
            sprintf(file, "iapbackground1@2x.png");
            break;
        case 2:
            sprintf(file, "iapbackground2@2x.png");
            break;
        case 3:
            sprintf(file, "iapbackground3@2x.png");
            break;
        case 4:
            sprintf(file, "iapbackground4@2x.png");
            break;
            
        default:
            break;
    }
    
    CCSprite* backgroundView = CCSprite::create(file);
    backgroundView->setScaleX(size.width / backgroundView->getContentSize().width);
    backgroundView->setScaleY(size.height / backgroundView->getContentSize().height);
    backgroundView->setPosition(ccp(size.width / 2, size.height / 2));
    addChild(backgroundView);
    
    
}

void PauseLayer:: onResume(cocos2d::CCObject *pSender){
    
    m_nGameSettings->playSound((char*)"SFX-GeneralMenuButton.wav");
    this->removeFromParent();
}

void PauseLayer:: onRestart( CCObject *pSender){
    
   m_nGameSettings->playSound((char*)"SFX-GeneralMenuButton.wav");
    GameMode mode = m_nGameSettings->getGameMode();
    if (mode == kTagPrimary) {
        AnalyticX::flurryLogEvent("Primary Mode Level Restart");
    }else if(mode == kTagTime){
        AnalyticX::flurryLogEvent("Action Mode Level Restart");
    }else if(mode==kTagEndress){
        AnalyticX::flurryLogEvent("Primary Mode Level Restart");
    }
    m_nScene->restartLevel();

    this->removeFromParent();
}

void PauseLayer:: onMainMenu(cocos2d::CCObject *pSender){
    
    m_nGameSettings->playSound((char*)"SFX-GeneralMenuButton.wav");
    m_nGameSettings->setCurrentStatus(kTagPause);
    CCDirector::sharedDirector()->replaceScene(CCTransitionCrossFade::create(0.3f,MainView::scene()));
}

void PauseLayer:: onGetFreeApp(cocos2d::CCObject *pSender){
    
    m_nGameSettings->playSound((char*)"SFX-GeneralMenuButton.wav");
    AnalyticX::flurryLogEvent("Get Free App");
   
}
void PauseLayer:: onSfxOn(cocos2d::CCObject *pSender){
    
    if (sfxon->isVisible() == true) {
        sfxoff->setVisible(true);
        CCUserDefault::sharedUserDefault()->setBoolForKey("effectSound", false);
        m_nGameSettings->stopSound();
        sfxon->setVisible(false);
         
    }else if(sfxon->isVisible() == false){
        sfxon->setVisible(true);
        sfxoff->setVisible(false);
        CCUserDefault::sharedUserDefault()->setBoolForKey("effectSound", true);
       
    }
    
}

void PauseLayer:: onMusicOn(cocos2d::CCObject *pSender){
    
    if (musicon->isVisible() == true) {
        musicoff->setVisible(true);
        musicon->setVisible(false);
        CCUserDefault::sharedUserDefault()->setBoolForKey("backgroundSound", false);
        m_nGameSettings->stopBackground();
    }else if(musicon->isVisible() == false){
        musicon->setVisible(true);
        musicoff->setVisible(false);
        CCUserDefault::sharedUserDefault()->setBoolForKey("backgroundSound", true);
        m_nGameSettings->playBackGround(m_nGameSettings->getBackgroundMusic());
    }
    
}