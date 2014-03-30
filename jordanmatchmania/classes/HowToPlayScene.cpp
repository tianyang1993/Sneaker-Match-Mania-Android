//
//  HowToPlayScene.cpp
//  VivaStampede
//
//  Created by Mikhail Berrya on 11/25/13.
//
//

#include "HowToPlayScene.h"
#include "InfoSlider1.h"
#include "InfoSlider2.h"
#include "InfoSlider3.h"
#include "InfoSlider4.h"
#include "InfoSlider5.h"
#include "InfoSlider6.h"
#include "GameScene.h"
#include "MoreLayer.h"

 
 
CCScene* HowToPlayScene::scene(){
    
    CCScene* scene = CCScene::create();
    HowToPlayScene* layer = HowToPlayScene::create();
    scene->addChild(layer);
    
    return scene;
}

bool HowToPlayScene:: init(){
    
    if (!CCLayer ::init()) {
        return false;
    }
    
    size = CCDirector::sharedDirector()->getWinSize();
    dScaleX = size.width / 768 , dScaleY = size.height / 1024;
    gameSettings = GameSettings::sharedGameSettings();
    
    if (gameSettings->getMoreToHowToPlayerScene()== 10) {
        superType = false;
    }else if(gameSettings->getMoreToHowToPlayerScene() == 5){
        superType  = true;
    }
    setBackGroundView(gameSettings->getBackground());
    initMenu();
    return true;
}
void HowToPlayScene:: setBackGroundView(int nType){
    
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

void HowToPlayScene:: initMenu(){
    
    currentSlide = 1;
    
    
    infoBackground = CCSprite::create("infoBackground@2x.png");
    infoBackground->setScaleX(size.width / infoBackground->getContentSize().width);
    infoBackground->setScaleY(infoBackground->getScaleY()*dScaleY);
    infoBackground->setPosition(ccp(size.width / 2 , size.height / 2));
    addChild(infoBackground);
    
    header = CCSprite::create("howtoplaysign@2x.png");
    header->setPosition(ccp(size.width / 2, size.height - 100*dScaleY));
    header->setScaleX(header->getScaleX()*dScaleX);
    header->setScaleY(header->getScaleY()*dScaleY);
    header->setVisible(!superType);
    addChild(header);
    
    
    ccColor3B strokeColor       =  { 255, 255, 255  };
    ccFontDefinition strokeTextDef;
    strokeTextDef.m_fontSize = 50*dScaleX;
    strokeTextDef.m_fontName = std::string("Dimbo Regular");
    strokeTextDef.m_stroke.m_strokeColor   = strokeColor;
    strokeTextDef.m_stroke.m_strokeEnabled = true;
    strokeTextDef.m_stroke.m_strokeSize    = 1.8;
    
    
    CCLabelTTF* prev = CCLabelTTF::createWithFontDefinition("<<<", strokeTextDef);
    prev->setScaleX(prev->getScaleX()*0.8f);
    prev->setScaleY(prev->getScaleY()*1.0f);
 
 
    CCLabelTTF* next = CCLabelTTF::createWithFontDefinition(">>>", strokeTextDef);
    next->setScaleX(next->getScaleX()*0.8f);
    next->setScaleY(next->getScaleY()*1.0f);
    


    previousSlideButton = CCMenuItemLabel::create(prev, this, menu_selector(HowToPlayScene::onPrev));    
    previousSlideButton->setPosition(ccp(size.width / 2 - 300*dScaleX, size.height / 2 -330*dScaleY));
    previousSlideButton->setVisible(false);
    
    nextSlideButton = CCMenuItemLabel::create(next, this, menu_selector(HowToPlayScene::onNext));
    nextSlideButton->setPosition(ccp(size.width / 2 + 300*dScaleX, size.height / 2 - 330*dScaleY));
    
    playButton = CCMenuItemImage::create("howtoplaybutton@2x.png", "howtoplaybutton@2x.png", this, menu_selector(HowToPlayScene::onPlay));
    playButton->setPosition(ccp(size.width / 2, size.height / 2 -400*dScaleY));
    playButton->setScaleX(playButton->getScaleX()*dScaleX);
    playButton->setScaleY(playButton->getScaleY()*dScaleY);
    playButton->setVisible(false);
    
    
      
    CCLabelTTF* b = CCLabelTTF::createWithFontDefinition("<<BACK", strokeTextDef);
    b->setScaleX(b->getScaleX()*1.0f);
    b->setScaleY(b->getScaleY()*1.2f);
    b->setColor(ccGRAY);
    
    CCLabelTTF* i = CCLabelTTF::createWithFontDefinition("INFO", strokeTextDef);
    i->setScaleX(i->getScaleX()*1.0f);
    i->setScaleY(i->getScaleY()*1.2f);
    i->setColor(ccGRAY);
    
    moreBack = CCMenuItemLabel::create(b, this, menu_selector(HowToPlayScene::onMore));
    moreBack->setPosition(ccp(size.width / 2 + 200*dScaleX, size.height- 100*dScaleY));
    moreBack->setVisible(superType);
    
    moreInfo = CCMenuItemLabel::create(i, this, menu_selector(HowToPlayScene::onInfo));
    moreInfo->setPosition(ccp(size.width / 2 - 200*dScaleX, size.height-100*dScaleY));
    moreInfo->setVisible(superType);
    
    CCMenu* menu = CCMenu::create(previousSlideButton  , nextSlideButton , playButton , moreBack , moreInfo, NULL);
    menu->setPosition(CCPointZero);
    addChild(menu);


    
    
    showSlideNumber(currentSlide);
    
}
void HowToPlayScene:: showSlideNumber(int thisSlideNumber){
    switch (thisSlideNumber) {
        case 1:
            infoSlide1 = InfoSlide1::body();
            addChild(infoSlide1,1);
            break;
        case 2:
            
            infoSlide2 = InfoSlide2::body();
            addChild(infoSlide2,2);
            break;
        case 3:
            infoSlide3 = InfoSlide3::body();
            addChild(infoSlide3,3);
            break;
        case 4:
            infoSlide4 = InfoSlide4::body();
            addChild(infoSlide4,4);
            break;
        case 5:
            infoSlide5 = InfoSlide5::body();
            addChild(infoSlide5,5);
            break;
        case 6:
            infoSlide6 = InfoSlide6::body();
            addChild(infoSlide6,6);
            break;
            
        default:
            break;
    }
    
}
void HowToPlayScene:: removeSlideNumber(int thisSlideNumber){
    switch (thisSlideNumber) {
        case 1:
            removeChild(infoSlide1);
            break;
        case 2:
            
            removeChild(infoSlide2);
            break;
        case 3:
            removeChild(infoSlide3);
            break;
        case 4:
            removeChild(infoSlide4);
            break;
        case 5:
            removeChild(infoSlide5);
            break;
        case 6:
            removeChild(infoSlide6);
            break;
        default:
            break;
    }
    
}
void HowToPlayScene:: onPrev(cocos2d::CCObject *pSender){
    
    gameSettings->playSound((char*)"SFX-GeneralMenuButton.wav");
    
    if (currentSlide < 1)
        return;
    removeSlideNumber(currentSlide);
    currentSlide--;
    if (currentSlide == 1) {
        previousSlideButton->setVisible(false);
    }
    showSlideNumber(currentSlide);
    nextSlideButton->setVisible(true);
    playButton->setVisible(false);
}

void HowToPlayScene:: onNext(cocos2d::CCObject *pSender){
     gameSettings->playSound((char*)"SFX-GeneralMenuButton.wav");
    if (currentSlide > 6) {
        return;
    }
    removeSlideNumber(currentSlide);
    currentSlide++;
    if (currentSlide == 6) {
        nextSlideButton->setVisible(false);
        playButton->setVisible(true);
    }
    showSlideNumber(currentSlide);
    previousSlideButton->setVisible(true);
}

void HowToPlayScene:: onPlay(cocos2d::CCObject *pSender){
    
    CCDirector::sharedDirector()->replaceScene(CCTransitionCrossFade::create(0.3f, GameScene::scene()));
}

void HowToPlayScene:: onMore(cocos2d::CCObject *pSender){
    
    CCDirector::sharedDirector()->replaceScene(CCTransitionCrossFade::create(0.1f, MoreScene::scene()));
}

void HowToPlayScene:: onInfo(cocos2d::CCObject *pSender){
    
    CCLOG("Info");
}