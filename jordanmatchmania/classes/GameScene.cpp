//
//  GameScene.cpp
//  VivaStampede
//
//  Created by Mikhail Berrya on 11/25/13.
//
//

#include "GameScene.h"
#include "PauseLayer.h"
#include "TokenBuy.h"
#include "MoreLayer.h"
#include "GameEngineLayer.h"
#include "ValuesManager.h"
#include "LevelCompleted.h"
#include "GameOver.h"
#include "SymbolManager.h"
#include "ByteManager.h" 
#include "SyntaxSymbol.h"
#include "CCAlertView.h"
#include "RevMob/RevMob.h"
#include "SyntaxSymbol.h"
#include "SimpleAudioEngine.h"
#include "TokenBuy.h"
#include "Define.h"

using namespace CocosDenshion;


typedef enum {
    kPurchNil = 0,
    kPurchPlat,
    kPurchChamel,
    kPurchClue
} kPurchases;

CCScene* GameScene::scene(){
    
    CCScene* scene = CCScene::create();
    GameScene* layer = GameScene::create();
    scene->addChild(layer);
    return scene;
}

GameScene::~GameScene(){
    
    revmob::RevMob *revmob = revmob::RevMob::SharedInstance();
    revmob->HideBanner();
    revmob = NULL;

    gameSettings->setTimeBarScale(m_fTimeBarScale);
    gameSettings->setProgressBarScale(m_fProgressBarScale);
    gameSettings->setCurrentLevel(m_nLevel);
    gameSettings->setGameScore(m_nGameScore);
    gameSettings->setTotalGameScore(m_nGameTotalScore);
 
    
    this->stopAllActions();
    this->removeAllChildren();
    
}

bool GameScene::init(){
    
    if (!CCLayer ::init()) {
        return false;
    }
    
    this->setTouchEnabled(false);
    
    size = CCDirector::sharedDirector()->getWinSize();
    dScaleX = size.width / 768 , dScaleY = size.height / 1024;
      
    initGame();
    return true;
}

void GameScene::initGame(){
    
    this->initGameInfo();
    
    m_nEngine = GameEngine::body();
    m_nEngine->gameScene = this;
    
    addChild(m_nEngine , 2);

    this->schedule(schedule_selector(GameScene::initmenu), 1.0f);
     
}

void GameScene:: setBackGroundView(int nType){
    
    char file[0x90] = {0};
    char file_h[0x90] = {0};
    char file_f[0x90] = {0};
    switch (nType) {
        case 0:
            sprintf(file, "background@2x.png");
            sprintf(file_h, "b1_h.png");
            sprintf(file_f, "b1_f.png");
            break;
        case 1:
            sprintf(file, "iapbackground1@2x.png");
            sprintf(file_h, "b2_h.png");
            sprintf(file_f, "b2_f.png");
            break;
        case 2:
            sprintf(file, "iapbackground2@2x.png");
            sprintf(file_h, "b3_h.png");
            sprintf(file_f, "b3_f.png");
            break;
        case 3:
            sprintf(file, "iapbackground3@2x.png");
            sprintf(file_h, "b4_h.png");
            sprintf(file_f, "b4_f.png");
            break;
        case 4:
            sprintf(file, "iapbackground4@2x.png");
            sprintf(file_h, "b5_h.png");
            sprintf(file_f, "b5_f.png");
            break;
            
        default:
            break;
    }
    
    CCSprite* backgroundView = CCSprite::create(file);
    backgroundView->setScaleX(size.width / backgroundView->getContentSize().width);
    backgroundView->setScaleY(size.height / backgroundView->getContentSize().height);
    backgroundView->setPosition(ccp(size.width / 2, size.height / 2));
    addChild(backgroundView);
    
    CCSprite* backgroud_h = CCSprite::create(file_h);
    backgroud_h->setScaleX(size.width / backgroud_h->getContentSize().width);
    backgroud_h->setScaleY(backgroundView->getScaleY());
    backgroud_h->setPosition(ccp(size.width / 2, size.height-backgroud_h->getContentSize().height / 2 * dScaleY + 5));
    addChild(backgroud_h , 3);
    
    CCSprite* backgroud_f = CCSprite::create(file_f);
    backgroud_f->setScaleX(size.width / backgroud_f->getContentSize().width);
    backgroud_f->setScaleY(backgroundView->getScaleY());
    backgroud_f->setPosition(ccp(size.width / 2, backgroud_f->getContentSize().height / 2 *dScaleY - 5));
    addChild(backgroud_f , 3);

    
    
}

#pragma mark GET GAME INFO 
///\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\

void GameScene:: initGameInfo(){
    
    gameSettings        = GameSettings::sharedGameSettings();
    statusManager       = StatusManager::sharedStatusManager();
    
    symbolManager       = SymbolManager::sharedSymbolManager();
    symbolManager->updateProbabilities();
   
    byteManager         = ByteManager::sharedByteManager();
    byteManager->initWithGame();
    
//    allPopUps = new CCArray();
    
   
    m_nRowsNeedForLevel = gameSettings->getGameRows();
    m_nGameScore        = gameSettings->getGameScore();
    m_nGameTotalScore   = gameSettings->getTotalGameScore();
    m_nGameMode         = gameSettings->getGameMode();
    m_fProgressBarScale = gameSettings->getProgressBarScale();
    m_fTimeBarScale     = gameSettings->getTimeBarScale();
    m_nByteCount        = gameSettings->getByteCount();
    m_nLevel            = gameSettings->getCurrentLevel();
    alert = NULL;
    
    if (m_nGameScore == 0) {
        m_nGameScore = 0;
    }
    
    if (m_nGameTotalScore == 0) {
        m_nGameTotalScore = 0;
    }
    
    if (m_nLevel == 0) {
        m_nLevel =1;
    }
    if (m_fProgressBarScale == 0) {
        m_fProgressBarScale = 0.0001*dScaleX;
    }
    if (m_fTimeBarScale == 0) {
        m_fTimeBarScale = 1.12*dScaleX;
    }
    
    m_nPointsNeedForLevel = statusManager->pointsNeededForLevel(m_nLevel, m_nGameMode);
    m_nRowsNeedForLevel = statusManager->rowsNeededForLevel(m_nLevel);
    //setBackGroundView(gameSettings->getBackground());
    
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    //    double dScalX = size.width / 768 , dScalY= size.height / 1024;
    CCSprite* backgroundView = CCSprite::create("bkg_default@2x.png");
    backgroundView->setPosition(ccp(size.width / 2, size.height / 2));
    float scale_x = size.width / backgroundView->getContentSize().width;
    float scale_y = size.height / backgroundView->getContentSize().height;
    backgroundView->setScaleX(scale_x);
    backgroundView->setScaleY(scale_y);
    addChild(backgroundView);
    
    CCSprite* spLogo = CCSprite::create("play_Logo@2x.png");
    spLogo->setPosition(ccp(size.width / 2 , getY(size.height, 141, 9) * scale_y));
    spLogo->setScaleX(scale_x);
    spLogo->setScaleY(scale_y);
    addChild(spLogo);

    CCSprite* spM = CCSprite::create("m@2x.png");
    spM->setPosition(ccp(getX(11, 90) * scale_x , getY(size.height, 90, 10) * scale_y));
    spM->setScaleX(scale_x);
    spM->setScaleY(scale_y);
    addChild(spM);

    CCSprite* spClock = CCSprite::create("clock@2x.png");
    spClock->setPosition(ccp(getX(539, 90) * scale_x , getY(size.height, 90, 10) * scale_y));
    spClock->setScaleX(scale_x);
    spClock->setScaleY(scale_y);
    addChild(spClock);

    CCSprite* spAdBanner = CCSprite::create("ad@2x.png");
    spAdBanner->setPosition(ccp(size.width / 2 , getY(size.height, 50, 910) * scale_y));
    spAdBanner->setScaleX(scale_x);
    spAdBanner->setScaleY(scale_y);
    addChild(spAdBanner);
    
    CCMenuItemImage *exitButton = CCMenuItemImage::create("Button_EXIT_1@2x.png", "Button_EXIT_hit@2x.png", "button_EXIT_2@2x.png", this, menu_selector(GameScene::onClickExit));
    exitButton->setPosition(ccp(getX(14, 162) * scale_x, getY(size.height,102, 798) * scale_y));
    exitButton->setScaleX(scale_x);
    exitButton->setScaleY(scale_y);

    CCMenuItemImage *hintButton = CCMenuItemImage::create("button_HINT_1@2x.png", "button_HINT_hit@2x.png", "button_HINT_2@2x.png", this, menu_selector(GameScene::onClickHint));
    hintButton->setPosition(ccp(getX(464, 162) * scale_x, getY(size.height,102, 798) * scale_y));
    hintButton->setScaleX(scale_x);
    hintButton->setScaleY(scale_y);

    CCMenu* menu = CCMenu::create(exitButton,hintButton,NULL);
    menu->setPosition(CCPointZero);
    addChild(menu);

    if ((m_nLevel >= 1 && m_nLevel <= 5)
        ||(m_nLevel >= 11 && m_nLevel <= 15)) {
        gameSettings->playBackGround((char*)kPlayMusic1);
    }else if ((m_nLevel >= 6 && m_nLevel <= 10)
        ||(m_nLevel >= 16 && m_nLevel <= 20)) {
        gameSettings->playBackGround((char*)kPlayMusic2);
    }
}
///\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\
#pragma mark INIT GAME MENU 
///\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\

void GameScene::initmenu(){
    
    unschedule(schedule_selector(GameScene::initmenu));
    schedule(schedule_selector(GameScene::showBaner), 3.0f);
    
    char barName[0x50] = {0};
    char titleLabel[0x50] = {0};
    m_nEngine->levelCompleted = false;
    if (m_nGameMode == kTagPrimary) {
        sprintf(barName, "progressBarP@2x.png");
        sprintf(titleLabel, "LEVELS MODE");
    }else if(m_nGameMode == kTagTime){
        sprintf(barName, "progressBarT@2x.png");
//        timeBar = CCSprite::create("progressBarBackTimer@2x.png");
//        timeBar->setPosition(ccp(45*dScaleX, size.height - 60*dScaleY));
//        timeBar->setScaleX(m_fTimeBarScale);
//        timeBar->setAnchorPoint(ccp(0.0f, 0.5f));
//        timeBar->setScaleY(timeBar->getScaleY()*dScaleY*1.15);
//        addChild(timeBar , 4);
        sprintf(titleLabel, "TIME MODE");
    }else{
        sprintf(barName, "progressBarP@2x.png");
        sprintf(titleLabel, "ENDLESS MODE");
    }
    
//    
//    
//    progressBarBackground = CCSprite::create("progressBar@2x.png");
//    progressBarBackground->setPosition(ccp(size.width / 2 , size.height - 60* dScaleY));
//    progressBarBackground->setScaleX(progressBarBackground->getScaleX()*dScaleX*1.12);
//    progressBarBackground->setScaleY(progressBarBackground->getScaleY()*dScaleY*1.15);
//    addChild(progressBarBackground,4);
//    
//    progressBar = CCSprite::create(barName);
//    progressBar->setPosition(ccp(45*dScaleX, size.height - 60*dScaleY));
//    m_fFirstScale = progressBar->getScaleX()*dScaleX*1.13;
//    progressBar->setScaleX(m_fProgressBarScale);
//    progressBar->setScaleY(progressBar->getScaleY()*dScaleY*1.15);
//    progressBar->setAnchorPoint(ccp(0.0f , 0.5f));
//    progressBar->setOpacity(150.0f);
//    addChild(progressBar , 4);
//    
    char file[0x90] = {0};
   
    ccColor3B strokeColor       =  { 255, 255, 255  };
    ccFontDefinition strokeTextDef;
    strokeTextDef.m_fontSize = 45*dScaleX;
    strokeTextDef.m_fontName = std::string("LuckiestGuy");
    strokeTextDef.m_stroke.m_strokeColor   = strokeColor;
    strokeTextDef.m_stroke.m_strokeEnabled = true;
    strokeTextDef.m_stroke.m_strokeSize    = 1.8;
    
    sprintf(file, "%d" , m_nGameTotalScore);
    scoreLabel = CCLabelTTF::createWithFontDefinition(file, strokeTextDef);
    scoreLabel->setPosition(ccp(size.width / 2, getY(size.height, 49, 831)));
    scoreLabel->setScaleY(1.2f*dScaleY);
    scoreLabel->setScaleX(0.8f*dScaleX);
    addChild(scoreLabel,4);
    
//    sprintf(file , "LEVEL : %d", m_nLevel);
//    levelLabel = CCLabelTTF::createWithFontDefinition(file, strokeTextDef);
//    levelLabel->setPosition(ccp(size.width / 2 + 270*dScaleX, size.height - 62*dScaleY));
//    levelLabel->setScaleY(1.2f*dScaleY);
//    levelLabel->setScaleX(0.8f*dScaleX);
//    addChild(levelLabel,4);
    
    
//    sprintf(file , "%d", m_nByteCount);
//    bytesCounter = CCLabelTTF::create(file, "Dimbo Regular", 50*dScaleY);
//    bytesCounter->setPosition(ccp(size.width / 2, size.height - 120*dScaleY));
//    bytesCounter->setScaleX(bytesCounter->getScaleX()*dScaleX);
//    bytesCounter->setScaleY(bytesCounter->getScaleY()*dScaleY);
//    addChild(bytesCounter,4);
    
//    levelsMode = CCLabelTTF::createWithFontDefinition(titleLabel, strokeTextDef);
//    levelsMode->setPosition(ccp(size.width / 2+ 270*dScaleY, size.height - 25*dScaleY));
//    levelsMode->setFontSize(25.0f*dScaleX);
//    levelsMode->setColor(ccGRAY);
//    levelsMode->setOpacity(255);
//    levelsMode->setScaleY(1.2f*dScaleY);
//    levelsMode->setScaleX(0.8f*dScaleX);
//    addChild(levelsMode,4);
//    
//    byteImage = CCSprite::create("byteSymbol@2x.png");
//    byteImage->setPosition(ccp(size.width / 2, size.height - 60*dScaleY));
//    byteImage->setScaleX(byteImage->getScaleX()*dScaleX);
//    byteImage->setScaleY(byteImage->getScaleY()*dScaleY);
//    addChild(byteImage,4);
//
//
//    
//    //Pause
//    menuButton = CCMenuItemImage::create("iphone_pause@2x.png", "iphone_pause_press@2x.png", this, menu_selector(GameScene::onMenuBtn));
//    menuButton->setPosition(ccp(size.width / 2 - 250*dScaleX, 150*dScaleY));
//    menuButton->setScaleX(menuButton->getScaleX()* dScaleX);
//    menuButton->setScaleY(menuButton->getScaleY()* dScaleY);
//    // Platypuses
//    platyTrap = CCMenuItemImage::create("iphone_newtraps@2x.png", "iphone_newtraps@2x.png", this, menu_selector(GameScene::onPlatyTrapBtn));
//    platyTrap->setPosition(ccp(size.width / 2 - 130*dScaleX, 150*dScaleY));
//    platyTrap->setScaleX(platyTrap->getScaleX()* dScaleX);
//    platyTrap->setScaleY(platyTrap->getScaleY()* dScaleY);
//    
//    sprintf(file, "x%d" , byteManager->rectifiers);
//    rectifyButton = CCLabelTTF::create(file, "Arial", 40*dScaleY);
//    rectifyButton->setPosition(ccp(size.width / 2 - 60*dScaleX, 150*dScaleY));
//    addChild(rectifyButton,4);
//    
//    // Chameleons
//    chameleons = CCMenuItemImage::create("iphone_newchameleon@2x.png", "iphone_newchameleon@2x.png", this, menu_selector(GameScene::onChameLeonsBtn));
//    chameleons->setPosition(ccp(size.width / 2+20*dScaleX , 150*dScaleY));
//    chameleons->setScaleX(chameleons->getScaleX()* dScaleX);
//    chameleons->setScaleY(chameleons->getScaleY()* dScaleY);
//    
//    sprintf(file, "x%d" , byteManager->wildcards);
//    wildcardButton = CCLabelTTF::create(file, "Arial", 40*dScaleY);
//    wildcardButton->setPosition(ccp(size.width / 2 +80*dScaleX, 150*dScaleY));
//    addChild(wildcardButton,4);
//    
//    // Clues Button
//    clueButton = CCMenuItemImage::create("iphone_newclues@2x.png", "iphone_newclues@2x.png", this, menu_selector(GameScene::onClueBtn));
//    clueButton->setPosition(ccp(size.width* 3/ 4-30*dScaleX , 150*dScaleY));
//    clueButton->setScaleX(clueButton->getScaleX()* dScaleX);
//    clueButton->setScaleY(clueButton->getScaleY()* dScaleY);
//    // Number of clues left
//    
//    sprintf(file, "x%d" , byteManager->prompts);
//    promptButton = CCLabelTTF::create(file, "Arial", 40*dScaleY);
//    promptButton->setPosition(ccp(size.width / 2 +220*dScaleX, 150*dScaleY));
//    addChild(promptButton , 4);
//    
//    // Powerup (shop)
//    powerUp = CCMenuItemImage::create("iphone_newcart@2x.png", "iphone_newcart@2x.png", this, menu_selector(GameScene::onPowerUpBtn));
//    powerUp->setPosition(ccp(size.width / 2 + 300*dScaleX , 150*dScaleY));
//    powerUp->setScaleX(powerUp->getScaleX()* dScaleX);
//    powerUp->setScaleY(powerUp->getScaleY()* dScaleY);
//    
//    
//    CCMenu* menu = CCMenu::create(menuButton , platyTrap , chameleons , clueButton , powerUp , NULL);
//    menu->setPosition(CCPointZero);
//    addChild(menu,4);
// 
//    if (m_nGameMode == kTagTime) {
//        schedule(schedule_selector(GameScene::decreaseTimeBar) , 0.1f);
//    }
//    
//    AnalyticX::flurryLogEvent("Prompt Used");
    
}
void GameScene::showBaner(){
    this->unschedule(schedule_selector(GameScene::showBaner));
    revmob::RevMob *revmob = revmob::RevMob::SharedInstance();
    revmob->ShowBanner();
}

///\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\
#pragma mark - MENU ACTION
///\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\

void GameScene::onClickExit(){
    
    gameSettings->stopBackground();
}

void GameScene::onClickHint(){
    
}

void GameScene:: onClueBtn(cocos2d::CCObject *pSender){

    if (byteManager->prompts > 0) {
        gameSettings->playSound((char*)"SFX-ProptButton.wav");
        if (m_nEngine->didFindHint()) {
            if (byteManager->prompts > 0) {
//                byteManager->usePackItem(3,promptButton);
                if (byteManager->prompts == 0) {
//                    clueButton->stopAllActions();
//                    clueButton->runAction(CCRepeatForever::create(CCSequence::create(CCFadeTo::create(1.0f, 100) , CCDelayTime::create(0.5f), CCFadeTo::create(1.0f, 255) , NULL)));
                    }

                AnalyticX::flurryLogEvent("Penalty Free Prompt Used");
 
            }
            else {
                if (m_nGameScore >= 100) {
                    setGameScore(-100);
                }
                AnalyticX::flurryLogEvent("Prompt Used");
                 
            }
        }
        else {
            //no moves
            gameSettings->playSound((char*)"SFX-NoMatch.wav");
            alert = CCAlertView::create( "Clues","No More Moves!","Ok", NULL, this, callfuncO_selector(GameScene::popupRemoveParticleNO), callfuncO_selector(GameScene::popupRemoveParticleYES));
            this->addChild(alert, 100);

            }
    }
    else {
        //no prompts
        gameSettings->playSound((char*)"SFX-NoMatch.wav");
       
        if(byteManager->prompts <= 0){
//            clueButton->stopAllActions();
//            clueButton->runAction(CCRepeatForever::create(CCSequence::create(CCFadeTo::create(1.0f, 100) , CCDelayTime::create(0.5f), CCFadeTo::create(1.0f, 255) , NULL)));
            if (!alert) {
                showPurchaseAlert(kPurchClue);
                
            }

            //        [self updateScore];

        }
        

    }

}
void GameScene:: onChameLeonsBtn(cocos2d::CCObject *pSender){
   
    SyntaxSymbol* temp = m_nEngine->firstTouchedSymbol;
    if (temp == NULL) {
        return;
    }
   
    if ((temp->isOfType < 7) & (byteManager->wildcards > 0)) {
        gameSettings->playSound((char*)"SFX-WildcardMorph.wav");
        m_nEngine->buyWildcard();
//        byteManager->usePackItem(1,wildcardButton);
        AnalyticX::flurryLogEvent("Turn To Wildcard");
         
        
        CCLog("Count Count ==%d" , byteManager->wildcards);
        if (byteManager->wildcards == 0){
//            chameleons->stopAllActions();
//            chameleons->runAction(CCRepeatForever::create(CCSequence::create(CCFadeTo::create(1.0f, 50) , CCDelayTime::create(0.5f), CCFadeTo::create(1.0f, 255) , NULL)));
        }
        
    }
    else {
        gameSettings->playSound((char*)"SFX-NoMatch.wav");
        if(byteManager->wildcards <= 0){
           showPurchaseAlert(kPurchChamel);
            
        }
        
    }

    
}

void GameScene::onMenuBtn(cocos2d::CCObject *pSender){
    
    this->setTouchEnabled(false);
    pauseLayer = PauseLayer::pause();
    pauseLayer->initWithGame(this);
    this->addChild(pauseLayer , 10);
     
}
void GameScene:: onPowerUpBtn(cocos2d::CCObject *pSender){
    
    
    gameSettings->setSuperType(1);
    CCDirector::sharedDirector()->replaceScene(TokenBuy::scene());
    
    revmob::RevMob *revmob = revmob::RevMob::SharedInstance();
    revmob->HideBanner();
    revmob = NULL;

//    TokenBuy* token = TokenBuy::body();
//    addChild(token,10);
    
    
}

void GameScene:: onGameOverBtn(cocos2d::CCObject *pSender){
    
}

void GameScene:: onPlatyTrapBtn(cocos2d::CCObject *pSender){
    
    SyntaxSymbol* temp = m_nEngine->firstTouchedSymbol;
    if (temp == NULL) {
        return;
    }
    if ((temp->isOfType == 9) && (byteManager->rectifiers > 0)) {
        gameSettings->playSound((char*)"SFX-Rectify.wav");
        m_nEngine->rectify();
//        byteManager->usePackItem(2,rectifyButton);
        if (byteManager->rectifiers == 0) {
//            platyTrap->stopAllActions();
//            platyTrap->runAction(CCRepeatForever::create(CCSequence::create(CCFadeTo::create(1.0f, 100) , CCDelayTime::create(0.5f), CCFadeTo::create(1.0f, 255) , NULL)));

        }
        AnalyticX::flurryLogEvent("Rectifier Used");
         
    }
     else {
        gameSettings->playSound((char*)"SFX-NoMatch.wav");
        if(byteManager->rectifiers <= 0)
             showPurchaseAlert(kPurchPlat);
         
    }
}

void GameScene:: onReshuffleBtn(cocos2d::CCObject *pSender){
    
    
}
void GameScene:: onPowerBtn(cocos2d::CCObject *pSender){
    
    
}

void GameScene::showPurchaseAlert(int num){
    
    currentAlert = num;
    char caption[0x50] = {0};
   
    if(num == kPurchPlat)
         sprintf(caption,"Would you like to buy 1000 tokens for $1.99 and get 5 Platypus Traps?");
    if(num == kPurchChamel)
        sprintf(caption,"Would you like to buy 500 tokens for $.99 and get 5 Chameleons?");
         
    if(num == kPurchClue)
        sprintf(caption,"Would you like to buy 500 tokens for $.99 and get 10 Hints?");
    
    
    CCAlertView *alert = CCAlertView::create( "Get More",caption,"Cancel", "Get!", this, callfuncO_selector(GameScene::popupRemoveParticleNO), callfuncO_selector(GameScene::popupRemoveParticleYES));
    this->addChild(alert, 100);
 
    

}

void GameScene::popupRemoveParticleNO(cocos2d::CCObject *pSender){
    
    CCAlertView* alert = (CCAlertView*) pSender;
    this->removeChild(alert, true);
 
}

void GameScene::popupRemoveParticleYES(cocos2d::CCObject *pSender){
     
    
}
///\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\
#pragma mark - SET GAMESCORE 
///\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\

void GameScene::setGameScore(int nScore){

    char file[0x50] ={0};
    m_nGameScore += nScore;
    sprintf(file, "%d" ,m_nGameScore);
    scoreLabel->setString(file);
    
//    char file[0x50] ={0};
//    m_nGameScore += nScore;
//    m_nGameTotalScore += nScore;
//     
//    sprintf(file, "%d" ,m_nGameTotalScore);
//    scoreLabel->setString(file);
//    
//    int bytesToAdd = m_nGameScore / kPointsForByte;
//    m_nByteCount+= bytesToAdd;
//    sprintf(file, "%d" , m_nByteCount);
//    bytesCounter->setString(file);
//    gameSettings->setByteCount(m_nByteCount);
//    
//    this->increaseProgressBar(nScore);
    
}
///\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\
#pragma mark - LEVEL COMPLETED & OVER
///\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\

void GameScene:: showLevelCompleted(){
    
    this->unscheduleAllSelectors();
    gameSettings->stopBackground();
    gameSettings->playSound((char*)kLevelPassedSound);
    symbolManager->updateProbabilities();
    m_nEngine->clearInfoPopUps();
    m_nEngine->clearGame();
    m_nGameScore = 0;
    schedule(schedule_selector(GameScene::decreaseProgressBar), 0.001f);
    
}

void GameScene:: showNextLevel(){
    
    gameSettings->setCurrentLevel(m_nLevel);
    gameSettings->setProgressBarScale(0.0f);
    gameSettings->setTimeBarScale(1.12*dScaleX);
    gameSettings->setByteCount(m_nByteCount);
    gameSettings->setGameScore(m_nGameScore);

    m_nLevel++;
    char file[0x50] = {0};
    sprintf(file , "LEVEL : %d", m_nLevel);
//    levelLabel->setString((char*)file);
    sprintf(file, "SCORE: %d" , m_nGameTotalScore);
    scoreLabel->setString((char*)file);
    sprintf(file , "%d", m_nByteCount);
//    bytesCounter->setString((char*)file);
    
     
    int nType =(m_nLevel)%4;
    gameSettings->setBackGroundMusic(nType);
    gameSettings->playBackGround(nType);
    
    m_fProgressBarScale = 0.0001*dScaleX;
    m_fTimeBarScale = 1.12*dScaleX;
    if (m_nGameMode == kTagPrimary) {
//        progressBar->setScaleX(m_fProgressBarScale);
    }else if(m_nGameMode == kTagTime){
//        timeBar->setScaleX(m_fTimeBarScale);
    }
    
    
    m_nEngine->resetGame();
    symbolManager->updateProbabilities();


}

void GameScene:: showGameOver(){
    
    gameOver = GameOver::layer();
    gameOver->initWithGame(this);
    addChild(gameOver , 5);
    cleanup();

}

void GameScene:: restartLevel(){
    
      this->unscheduleAllSelectors();
//     
//    removeChild(scoreLabel,true);
//    removeChild(levelLabel,true);
//    removeChild(bytesCounter , true);
//    removeChild(promptButton, true);
//    removeChild(levelsMode,true);
//    removeChild(backButton,true);
//    removeChild(wildcardButton,true);
//    removeChild(rectifyButton,true);
//    
//
    gameSettings->setCurrentLevel(m_nLevel);
    gameSettings->setProgressBarScale(0.0f);
    gameSettings->setTimeBarScale(1.12*dScaleX);
    gameSettings->setByteCount(m_nByteCount);
    gameSettings->setGameScore(m_nGameScore);
    
    
    
    m_fProgressBarScale = 0.0001*dScaleX;
    m_fTimeBarScale = 1.12*dScaleX;
    
    if (m_nGameMode == kTagPrimary) {
//        progressBar->setScaleX(m_fProgressBarScale);
    }else if(m_nGameMode == kTagTime){
//        timeBar->setScaleX(m_fTimeBarScale);
    }
    
    m_nEngine->resetGame();
    symbolManager->updateProbabilities();
    
}
///\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\
#pragma mark - BAR ACTION
///\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\

void GameScene::increaseProgressBar(int nScore){
    
    m_fProgressBarScale += (m_fFirstScale / m_nPointsNeedForLevel)*nScore;
    if (m_fProgressBarScale > m_fFirstScale) return;
    
//    progressBar->setScaleX(m_fProgressBarScale);
    
}

void GameScene::decreaseProgressBar(float dt){
    
    m_fProgressBarScale -= 0.05f;
    
    if (m_fProgressBarScale < 0.0f) {
        m_fProgressBarScale = 0.0f;
//        progressBar->setScaleX(m_fProgressBarScale);
        unschedule(schedule_selector(GameScene::decreaseProgressBar));
        levelCompleted = LevelCompleted::layer();
        levelCompleted->initWithGame(this);
        this->addChild(levelCompleted , 5);
         
        return;
    }
//    progressBar->setScaleX(m_fProgressBarScale);
    
}

void GameScene:: decreaseTimeBar(float dt){
    
    m_fTimeBarScale -= 0.001f;
    if (m_fTimeBarScale < 0.0f) {
        unschedule(schedule_selector(GameScene::decreaseTimeBar));
        /*if (progressBar->getScaleX() < 1.0f)*/ {
            m_nGameScore = 0;
            showGameOver();
           
        }
        return;
    }
//    timeBar->setScaleX(m_fTimeBarScale);
}
///\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\
#pragma mark - GAMEOVER 
///\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\

void GameScene::GameFaild(){
    
    this->proposeReshuffle();
    
}

void GameScene::proposeReshuffle(){
    this->setTouchEnabled(false);
//    gameFailerBackground = CCSprite::create("reshuffle@2x.png");
//    gameFailerBackground->setPosition(ccp(size.width / 2, size.height / 2));
//    gameFailerBackground->setScaleX(size.width / gameFailerBackground->getContentSize().width);
//    gameFailerBackground->setScaleY(size.height / gameFailerBackground->getContentSize().height);
//    
//    this->addChild(gameFailerBackground , 100);
//    
//    endGame = CCMenuItemImage::create("reshuffle_endpress@2x.png", "reshuffle_endpress@2X.png", this, menu_selector(GameScene::onEndGame));
//    reshuffle = CCMenuItemImage::create("reshuffle_press@2x.png", "reshuffle_press@2x.png", this, menu_selector(GameScene::onReshuffle));
//    endGame->setPosition(ccp(190*dScaleX,170*dScaleY));
//    endGame->setScaleX(2.2f*dScaleX);
//    endGame->setScaleY(2.2f*dScaleY);
//    
//    reshuffle->setScaleX(2.2f*dScaleX);
//    reshuffle->setScaleY(2.2f*dScaleY);
//    reshuffle->setPosition(ccp(size.width -50*dScaleX, 80*dScaleY));
//    
//    CCMenu* menu = CCMenu::create(endGame , reshuffle , NULL);
//    menu->setPosition(CCPointZero);
//    this->addChild(menu , 102);
    
}

void GameScene::onEndGame(cocos2d::CCObject *pSender){
    
    CCDirector::sharedDirector()->replaceScene(MainView::scene());
}

void GameScene::onReshuffle(cocos2d::CCObject *pSender){
    
//    CCDirector::sharedDirector()->replaceScene(TokenBuy::scene());
    
}
///\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\
#pragma mark - POPUP CHECK
///\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\

//void GameScene::checkForInfoPopUps(){
//    
//    CCArray* grid = m_nEngine->gameGrid;
//    
//    for (int i = 0; i < 8; i++) {
//        CCArray* temp = (CCArray*) grid->objectAtIndex(i);
//        for (int j = 0; j < 8; j++) {
//            SyntaxSymbol *thisSymbol =(SyntaxSymbol*)temp->objectAtIndex(j);
////            if ((thisSymbol->isOfType > 6) || (thisSymbol->isShifter)) {
//                int k = -1;
//                if (thisSymbol->isOfType == 3) k = 0;
//                else if (thisSymbol->isShifter) k = 1;
//                else if (thisSymbol->isOfType == 9) k = 2;
//                else if (thisSymbol->isOfType == 10) k = 3;
//               
//                if ((k > -1) /*&& (!statusManager->didSeePopUpForSpecialType(k))*/) {
//                    InfoPopUp *temp = InfoPopUp::popUp();
//                    temp->initForSymbolWithIndex(thisSymbol->getPosition(), k);
//                    allPopUps->addObject(temp);
////                    this->addChild(temp);
//                    m_nEngine->setTouchEnabled(false);
//                    
//                }
////            }
//        }
//    }
//
//    
//}
//
//void GameScene:: clearInfoPopUps(){
//    
//    if (allPopUps->count() > 0) {
//        for (int i = 0; i < allPopUps->count(); i++) {
//            InfoPopUp* temp = (InfoPopUp*) allPopUps->objectAtIndex(i);
//            temp->removePopUp();
//        }
//        allPopUps->removeAllObjects();
//    }
//
//}

///\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\
