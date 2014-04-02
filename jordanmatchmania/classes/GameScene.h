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
    CCLabelTTF      *clockLabel;
    CCLabelTTF      *livesLabel;
    
    int         m_nLives;
    int         m_nClock;
    int         m_nGameScore;
    int         m_nGameTotalScore;
    int         m_nLevel;
    int         m_nPointsNeedForLevel;
    
    int         m_nRowsNeedForLevel;
    
    void    initmenu();
    void    initGame();
    void    initGameInfo();

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
    void    restartLevel();

    void    playBgMusic();
    void    decreaseTime();
    
    CREATE_FUNC(GameScene);
};

#endif /* defined(__VivaStampede__GameScene__) */
