//
//  StatusManager.h
//  VivaStampede
//
//  Created by Mikhail Berrya on 11/26/13.
//
//

#ifndef __VivaStampede__StatusManager__
#define __VivaStampede__StatusManager__

#include <iostream>
#include "cocos2d.h"
#include "GameSetting.h"

USING_NS_CC;

class StatusManager : public CCObject{
public:
    
    static StatusManager* sharedStatusManager();
  
    CCUserDefault *userDefaults;
    
    int         selectedGameMode;
    int         currentLevel;
    int         currentScore;
    int         currentLevelScore;
    int         pointsToCompleteLevel;
    int         player1Score;
    int         player2Score;
    
    void        clearGameStats();
    bool        didSeePopUpForSpecialType(int thisType);
    void        setHighScore();
    int         getHighScore();
    void        setTopTenScoresForGameMode(int thisGameMode);
    CCArray*    getTopTenScoresForGameMode(int thisGameMode);
    
    //Values Manager
    int         rowsNeededForLevel(int thisLevel);
    int         pointsNeededForLevel(int thisLevel /*,GameMode thisGameMode*/);
    int         wildcardProbabilityForLevel(int thisLevel);
    int         shifterProbabilityForLevel(int thisLevel);
    int         corruptedProbabilityForLevel(int thisLevel);
    int         hiddenProbabilityForLevel(int thisLevel);


};

#endif /* defined(__VivaStampede__StatusManager__) */
