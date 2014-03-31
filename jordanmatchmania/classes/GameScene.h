//
//  GameScene.h
//  VivaStampede
//
//  Created by Mikhail Berrya on 11/25/13.
//
//

#ifndef __VivaStampede__GameScene__
#define __VivaStampede__GameScene__

#include <iostream>
#include "cocos2d.h"
#include "GameSetting.h"
#include "StatusManager.h"
#include "AnalyticX.h"
USING_NS_CC;

class GameEngine;
class LevelCompleted;
class GameOver;
class SymbolManager;
class ByteManager;
class CCAlertView;
class PauseLayer;
class GameScene : public CCLayer{
    
public:
    virtual bool init();
    static CCScene* scene();
    ~GameScene();
    CCSize  size;
    double dScaleX , dScaleY;
    
    CCLabelTTF      *scoreLabel;
//    CCLabelTTF      *levelLabel;
//    CCLabelTTF      *bytesCounter;
    
//    CCSprite        *byteImage;
//    CCSprite        *progressBarBackground;
//    CCSprite        *progressBar;
//    CCSprite        *timeBar;
//    CCSprite        *powButton;
//    CCSprite        *gameFailerBackground;
//
//    CCLabelTTF          *promptButton;
//    CCLabelTTF          *levelingLabel;
//    CCLabelTTF          *backButton;
//    CCLabelTTF          *rectifyButton;
//    CCLabelTTF          *wildcardButton;
//    CCLabelTTF          *levelsMode;
    
    
//    CCMenuItemImage     *clueButton;
//    CCMenuItemImage     *menuButton;
//    CCMenuItemImage     *powerButton;
//    CCMenuItemImage     *platyTrap;
//    CCMenuItemImage     *chameleons;
//    CCMenuItemImage     *powerUp;
//    CCMenuItemImage     *reshuffleButton;
//    CCMenuItemImage     *gameOverButton;
//    CCMenuItemImage     *endGame;
//    CCMenuItemImage     *reshuffle;
    
    
   
    
    int         m_nGameScore;
    int         m_nGameTotalScore;
    int         m_nByteCount;
    int         m_nLevel;
    int         m_nPointsNeedForLevel;
    
    int         m_nRowsNeedForLevel;
    
    int         currentAlert;
    float       m_fFirstScale;
    float       m_fProgressBarScale;
    float       m_fTimeBarScale;
    GameMode    m_nGameMode;

    
    void    initmenu();
    void    initGame();
    void    initGameInfo();
    void    onClueBtn(CCObject* pSender);
    void    onMenuBtn(CCObject* pSender);
    void    onPowerBtn(CCObject* pSender);
    void    onPlatyTrapBtn(CCObject* pSender);
    void    onChameLeonsBtn(CCObject* pSender);
    void    onPowerUpBtn(CCObject* pSender);
    void    onReshuffleBtn(CCObject* pSender);
    void    onGameOverBtn(CCObject* pSender);
    void    onEndGame(CCObject* pSender);
    void    onReshuffle(CCObject* pSender);
    void    popupRemoveParticleNO(CCObject* pSender);
    void    popupRemoveParticleYES(CCObject* pSender);
    
    void    setBackGroundView(int nType);
   
    void    onClickExit();
    void    onClickHint();
    
    // Objetc Pointer
    GameEngine*         m_nEngine;
    GameSettings*       gameSettings;
    StatusManager*      statusManager;
    LevelCompleted*     levelCompleted;
    GameOver*           gameOver;
    SymbolManager*      symbolManager;
    ByteManager*        byteManager;
    PauseLayer*         pauseLayer;
    CCAlertView *       alert;
    
    void    setGameScore(int nScore);
    void    showLevelCompleted();
    void    showNextLevel();
    void    showGameOver();
    void    increaseProgressBar(int nScore);
    void    decreaseProgressBar(float dt);
    void    decreaseTimeBar(float dt);
    void    restartLevel();
    void    showPurchaseAlert(int num);
    void    checkForInfoPopUps();
    void    clearInfoPopUps();
    //Game Over
    void    proposeReshuffle();
    void    GameFaild();
    void    showBaner();

    void    playBgMusic();
     
    
       
    
    
    CREATE_FUNC(GameScene);
};

#endif /* defined(__VivaStampede__GameScene__) */
