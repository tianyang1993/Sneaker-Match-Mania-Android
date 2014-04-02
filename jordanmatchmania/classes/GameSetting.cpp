//
//  GameSetting.cpp
//  VivaStampede
//
//  Created by Mikhail Berrya on 11/25/13.
//
//

#include "GameSetting.h"
#include "SimpleAudioEngine.h"
#include "ValuesManager.h"
using namespace CocosDenshion;

GameSettings* GameSettings::sharedGameSettings(){
    
    static GameSettings* temp = NULL;
    
    if (temp == NULL) {
        temp = new GameSettings();
    }
    
    return  temp;
}
 void GameSettings::setBackGround(int nType){
    
   CCUserDefault::sharedUserDefault()->setIntegerForKey("backgroundtype", nType);
}

int  GameSettings::getBackground(){
     
    return CCUserDefault::sharedUserDefault()->getIntegerForKey("backgroundtype");
 
}
void GameSettings::setBackGroundMusic(int nType){
    
    CCUserDefault::sharedUserDefault()->setIntegerForKey("backgroundMusic", nType);
}

int  GameSettings::getBackgroundMusic(){
    
    return CCUserDefault::sharedUserDefault()->getIntegerForKey("backgroundMusic");
    
}

///\/\/\/\/\/\/\/\/\/\/\\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/
void GameSettings::setSuperType(int nType){
    
    if (nType == 0) {
        m_nSuperType = kTagNon;
    }else if(nType == 1){
        m_nSuperType = kTagGame;
    }else if(nType ==2){
        m_nSuperType = kTagMain;
    }
    
}
SuperType GameSettings::getSuperType(){
   
    return m_nSuperType;
}

///\/\/\/\/\/\/\/\/\/\/\\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/
void GameSettings::playSound(char *file){
   
    
    bool m_eSound = CCUserDefault::sharedUserDefault()->getBoolForKey("effectSound");
    if (!m_eSound) {
        return;
    }
    SimpleAudioEngine::sharedEngine()->playEffect(file, false);
    
}

void GameSettings:: playBackGround(int nType){
    
    bool m_eSound = CCUserDefault::sharedUserDefault()->getBoolForKey("backgroundSound");
    if (!m_eSound) {
        return;
    }
    char file[0x80] = {0};
    switch (nType) {
        case 0:
            sprintf(file, "MUSIC-MainTitles(Syntax)-Mono.mp3");
            break;
        case 1:
            sprintf(file, "MUSIC-01-InitiationSequence-Mono.mp3");
            break;
        case 2:
            sprintf(file, "MUSIC-02-InTheGame-Mono.mp3");
            break;
        case 3:
            sprintf(file, "MUSIC-03-Assimilation-Mono.mp3");
            break;
        case 4:
            sprintf(file, "MUSIC-MainTitles(Syntax)-Mono.mp3");
            break;
            
        default:
            break;
    }
    
    SimpleAudioEngine::sharedEngine()->playBackgroundMusic(file, true);
}


void GameSettings:: playBackGround(char* file){
    
    SimpleAudioEngine::sharedEngine()->playBackgroundMusic(file, true);
}

void GameSettings:: stopBackground(){
    
    SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
}
void GameSettings:: stopSound(){
    
    SimpleAudioEngine::sharedEngine()->stopAllEffects();
   
}

void GameSettings::setEffectMute(bool nMute){
    
    CCUserDefault::sharedUserDefault()->setBoolForKey("effectSound", nMute);
}

bool GameSettings:: getEffectMute(){
    
    return  CCUserDefault::sharedUserDefault()->getBoolForKey("effectSound");
}
///\/\/\/\/\/\/\/\/\/\/\\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/
void GameSettings:: setGameMode(GameMode nMode){
    m_nMode = nMode;
}
GameMode GameSettings:: getGameMode(){
    return m_nMode;
}
///\/\/\/\/\/\/\/\/\/\/\\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/
void GameSettings:: setGameScore(int nScore){
    CCUserDefault::sharedUserDefault()->setIntegerForKey("gameScore", nScore);
}

int GameSettings:: getGameScore(){
    return CCUserDefault::sharedUserDefault()->getIntegerForKey("gameScore");
}

void GameSettings:: setTotalGameScore(int nScore){
    CCUserDefault::sharedUserDefault()->setIntegerForKey("gameTotalScore", nScore);
}

int GameSettings:: getTotalGameScore(){
    return CCUserDefault::sharedUserDefault()->getIntegerForKey("gameTotalScore");
}

 
///\/\/\/\/\/\/\/\/\/\/\\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/
void GameSettings::setByteCount(int nCount){
    CCUserDefault::sharedUserDefault()->setIntegerForKey("byteCount", nCount);
}
int GameSettings:: getByteCount(){
    return CCUserDefault::sharedUserDefault()->getIntegerForKey("byteCount");
}
///\/\/\/\/\/\/\/\/\/\/\\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/
void GameSettings::setCurrentLevel(int nLevel){
    CCUserDefault::sharedUserDefault()->setIntegerForKey("currentLevel", nLevel);
}
int GameSettings::getCurrentLevel(){
    return CCUserDefault::sharedUserDefault()->getIntegerForKey("currentLevel", 1);
}

///\/\/\/\/\/\/\/\/\/\/\\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/

void GameSettings:: setMoreToHowToPlayerScene(int select){
    CCUserDefault::sharedUserDefault()->setIntegerForKey("moretohowtoplay", select);
}

int GameSettings:: getMoreToHowToPlayerScene(){
    return CCUserDefault::sharedUserDefault()->getIntegerForKey("moretohowtoplay");
}

void GameSettings::setCurrentStatus(SceneStatus nStatus){
    
    m_nStatus = nStatus;
}

SceneStatus GameSettings::getCurrentStatus(){
    
    if (CCUserDefault::sharedUserDefault()->getIntegerForKey("first") !=1) {
        m_nStatus = kTagNonStatus;
    }
    return m_nStatus;
}

void GameSettings:: setPlayed(bool nPlay){
    
    CCUserDefault::sharedUserDefault()->setBoolForKey("played", nPlay);
}
bool GameSettings:: isPlayed(){
    return CCUserDefault::sharedUserDefault()->getBoolForKey("played");
}

void GameSettings::setGameLives(int nLives){
    CCUserDefault::sharedUserDefault()->setIntegerForKey("gamelives", max_lives);
}

int GameSettings::getGameLives(){
    return CCUserDefault::sharedUserDefault()->getIntegerForKey("gamelives");
}

void GameSettings::setGameHighScore(int nHighScore){
    CCUserDefault::sharedUserDefault()->setIntegerForKey("gamehighscore", 0);
}

int GameSettings::getGameHighScore(){
    return CCUserDefault::sharedUserDefault()->getIntegerForKey("gamehighscore");
}











