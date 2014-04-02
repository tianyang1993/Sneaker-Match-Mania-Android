//
//  GameSetting.h
//  VivaStampede
//
//  Created by Mikhail Berrya on 11/25/13.
//
//

#ifndef __VivaStampede__GameSetting__
#define __VivaStampede__GameSetting__

#include <iostream>
#include "cocos2d.h"

USING_NS_CC;

typedef enum {
    kTagNon,
    kTagGame,
    kTagMain,
}SuperType;

typedef enum {
    kTagPrimary,
    kTagTime,
    kTagEndress,
}GameMode;

typedef enum {
    kTagBackground,
    kTagPause,
    kTagStore,
    kTagMore,
    kTagNonStatus,
}SceneStatus;


class GameSettings : public CCLayer{
    
public:
    static GameSettings* sharedGameSettings();
    
    int         m_nRows;
    int         m_nGameScore;
    int         m_nCurrentLevel;
     
    
    
    char        backgroundName[0x60];
    SuperType   m_nSuperType;
    GameMode    m_nMode;
    SceneStatus m_nStatus;
    
    void        setBackGround(int nType);
    int         getBackground();
    
    void        setBackGroundMusic(int nType);
    int         getBackgroundMusic();

    void        setSuperType(int nType);
    SuperType   getSuperType();
    
    void        setGameMode(GameMode nMode);
    GameMode    getGameMode();

    void        setGameScore(int nScore);
    int         getGameScore();

    void        setGameRows(int nRows);
    int         getGameRows();

    void        setGameLives(int nLives);
    int         getGameLives();

    void        setGameHighScore(int nHighScore);
    int         getGameHighScore();
    
    void        setTotalGameScore(int nScore);
    int         getTotalGameScore();
    
   
    
    void        setByteCount(int nCount);
    int         getByteCount();
    
    void        setCurrentLevel(int nLevel);
    int         getCurrentLevel();
    
    void        setProgressBarScale(float nScale);
    float       getProgressBarScale();
    
    void        setTimeBarScale(float nScale);
    float       getTimeBarScale();
    
    void        setEffectMute(bool nMute);
    bool        getEffectMute();
    
    
    void        playSound(char* file);
    void        playBackGround(int nType);
    void        playBackGround(char* file);
    
    void        stopSound();
    void        stopBackground();
    
    void        setMoreToHowToPlayerScene(int select);
    int         getMoreToHowToPlayerScene();
    
    void        setCurrentStatus(SceneStatus nStatus);
    SceneStatus getCurrentStatus();
    
    void        setPlayed(bool nPlay);
    bool        isPlayed();
    
    
};
#endif /* defined(__VivaStampede__GameSetting__) */
