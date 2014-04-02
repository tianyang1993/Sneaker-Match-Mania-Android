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
#include "SyntaxSymbol.h"
#include "CCAlertView.h"
#include "SyntaxSymbol.h"
#include "SimpleAudioEngine.h"
#include "TokenBuy.h"
#include "Define.h"

using namespace CocosDenshion;

CCScene* GameScene::scene(){
    
    CCScene* scene = CCScene::create();
    GameScene* layer = GameScene::create();
    scene->addChild(layer);
    return scene;
}

GameScene::~GameScene(){
    
    gameSettings->setGameLives(m_nLives);
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
    m_nEngine->initGame();
    
    addChild(m_nEngine , 2);

    this->schedule(schedule_selector(GameScene::initmenu), 1.0f);
     
}

#pragma mark GET GAME INFO
///\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\

void GameScene:: initGameInfo(){
    
    gameSettings        = GameSettings::sharedGameSettings();
    statusManager       = StatusManager::sharedStatusManager();
    
    symbolManager       = SymbolManager::sharedSymbolManager();
    symbolManager->updateProbabilities();
   
    m_nClock = level_clock;
    m_nLives = gameSettings->getGameLives();
    m_nGameScore        = gameSettings->getGameScore();
    m_nGameTotalScore   = gameSettings->getTotalGameScore();

    m_nLevel            = gameSettings->getCurrentLevel();
    alert = NULL;
    
    if (m_nGameScore == 0) {
        m_nGameScore = 0;
    }
    
    if (m_nGameTotalScore == 0) {
        m_nGameTotalScore = 0;
    }
    
    m_nPointsNeedForLevel = statusManager->pointsNeededForLevel(m_nLevel/*, m_nGameMode*/);
    m_nRowsNeedForLevel = statusManager->rowsNeededForLevel(m_nLevel);
    
    CCSize size = CCDirector::sharedDirector()->getWinSize();
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
    spAdBanner->setPosition(ccp(size.width / 2 , getY(size.height, 100, 860) * scale_y));
    spAdBanner->setScaleX(scale_x);
    spAdBanner->setScaleY(scale_y);
    addChild(spAdBanner);
    
    CCMenuItemImage *exitButton = CCMenuItemImage::create("Button_EXIT_1@2x.png", "Button_EXIT_hit@2x.png", this, menu_selector(GameScene::onClickExit));
    exitButton->setPosition(ccp(getX(17, 162) * scale_x, getY(size.height,102, 775) * scale_y));
    exitButton->setScaleX(scale_x);
    exitButton->setScaleY(scale_y);

    CCMenuItemImage *hintButton = CCMenuItemImage::create("button_HINT_1@2x.png", "button_HINT_hit@2x.png", this, menu_selector(GameScene::onClickHint));
    hintButton->setPosition(ccp(getX(460, 162) * scale_x, getY(size.height,102, 775) * scale_y));
    hintButton->setScaleX(scale_x);
    hintButton->setScaleY(scale_y);

    CCMenu* menu = CCMenu::create(exitButton,hintButton,NULL);
    menu->setPosition(CCPointZero);
    addChild(menu);
    
    playBgMusic();
}
///\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\
#pragma mark INIT GAME MENU 
///\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\

void GameScene::initmenu(){
    
    unschedule(schedule_selector(GameScene::initmenu));

    m_nEngine->levelCompleted = false;

    char file[0x90] = {0};
   
    ccColor3B strokeColor =  { 255, 255, 255  };
    ccFontDefinition strokeTextDef;
    strokeTextDef.m_fontSize = 45*dScaleX;
    strokeTextDef.m_fontName = std::string("LuckiestGuy");
    strokeTextDef.m_stroke.m_strokeColor   = strokeColor;
    strokeTextDef.m_stroke.m_strokeEnabled = true;
    strokeTextDef.m_stroke.m_strokeSize    = 1.8;
    
    sprintf(file, "%d" , m_nGameScore);
    scoreLabel = CCLabelTTF::createWithFontDefinition(file, strokeTextDef);
    scoreLabel->setPosition(ccp(size.width / 2, getY(size.height, 49, 800)));
    scoreLabel->setScaleY(1.2f*dScaleY);
    scoreLabel->setScaleX(0.8f*dScaleX);
    addChild(scoreLabel,4);

    sprintf(file, "%d" , m_nLives);
    livesLabel = CCLabelTTF::createWithFontDefinition(file, strokeTextDef);
    livesLabel->setPosition(ccp(120, getY(size.height, 49, 40)));
    livesLabel->setScaleY(1.2f*dScaleY);
    livesLabel->setScaleX(0.8f*dScaleX);
    addChild(livesLabel,4);

    sprintf(file, "%d" , m_nClock);
    clockLabel = CCLabelTTF::createWithFontDefinition(file, strokeTextDef);
    clockLabel->setPosition(ccp(500, getY(size.height, 49, 40)));
    clockLabel->setScaleY(1.2f*dScaleY);
    clockLabel->setScaleX(0.8f*dScaleX);
    addChild(clockLabel,4);
    
    schedule(schedule_selector(GameScene::decreaseTime) , 1.0f);
}

///\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\
#pragma mark - MENU ACTION
///\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\

void GameScene::onClickExit(){
    
    gameSettings->stopBackground();
}

void GameScene::onClickHint(){
    m_nEngine->didFindHint();
}

///\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\
#pragma mark - SET GAMESCORE 
///\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\

void GameScene::setGameScore(int nScore){

    char file[0x50] ={0};
    m_nGameScore += nScore;
    sprintf(file, "%d" ,m_nGameScore);
    scoreLabel->setString(file);
    
}
///\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\
#pragma mark - LEVEL COMPLETED & OVER
///\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\

void GameScene:: showLevelCompleted(){
    
    this->unscheduleAllSelectors();
    unschedule(schedule_selector(GameScene::decreaseTime));
    
    gameSettings->stopBackground();
    gameSettings->playSound((char*)kLevelPassedSound);
    symbolManager->updateProbabilities();
    m_nEngine->clearInfoPopUps();
    m_nEngine->clearGame();
    m_nGameScore = 0;
    
    levelCompleted = LevelCompleted::layer();
    levelCompleted->initWithGame(this);
    this->addChild(levelCompleted , 5);

}

void GameScene:: showNextLevel(){
    
    gameSettings->setGameLives(m_nLives);
    gameSettings->setCurrentLevel(m_nLevel);
    gameSettings->setGameScore(m_nGameScore);

    m_nLevel++;
    
    char file[0x50] = {0};
    sprintf(file, "%d" , m_nGameScore);
    scoreLabel->setString((char*)file);

    playBgMusic();
    
    m_nEngine->resetGame();
    m_nRowsNeedForLevel = statusManager->rowsNeededForLevel(m_nLevel);
    m_nPointsNeedForLevel = statusManager->pointsNeededForLevel(m_nLevel/*, m_nGameMode*/);
    
    m_nEngine->initGame();
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

    gameSettings->setGameLives(m_nLives);
    gameSettings->setCurrentLevel(m_nLevel);
    gameSettings->setGameScore(m_nGameScore);
    
    m_nRowsNeedForLevel = statusManager->rowsNeededForLevel(m_nLevel);
    
    m_nEngine->resetGame();
    m_nEngine->initGame();
    symbolManager->updateProbabilities();
    
}

void GameScene::playBgMusic(){
    if ((m_nLevel >= 1 && m_nLevel <= 5)
        ||(m_nLevel >= 11 && m_nLevel <= 15)) {
        gameSettings->playBackGround((char*)kPlayMusic1);
    }else if ((m_nLevel >= 6 && m_nLevel <= 10)
              ||(m_nLevel >= 16 && m_nLevel <= 20)) {
        gameSettings->playBackGround((char*)kPlayMusic2);
    }
}

void GameScene::decreaseTime(){
    
    m_nClock--;
    
    if (m_nClock < 0) {
        unschedule(schedule_selector(GameScene::decreaseTime));
        
        if(m_nGameScore < m_nPointsNeedForLevel){
            m_nLives--;
            gameSettings->setGameLives(m_nLives);
            showGameOver();
        }
        
    }else{
        char file[0x50] ={0};
        sprintf(file, "%d" ,m_nClock);
        clockLabel->setString(file);
        
    }
}

///\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\
