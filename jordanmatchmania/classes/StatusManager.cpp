//
//  StatusManager.cpp
//  VivaStampede
//
//  Created by Mikhail Berrya on 11/26/13.
//
//

#include "StatusManager.h"
#include "ValuesManager.h"


StatusManager* StatusManager::sharedStatusManager(){
    StatusManager* temp = NULL;
    if (temp == NULL) {
        temp = new StatusManager();
    }
    
    return temp;
}
 
void StatusManager::clearGameStats(){
    currentLevel = 1;
    currentScore = 0;
    currentLevelScore = 0;
    pointsToCompleteLevel = 0;
    player1Score = 0;
    player2Score = 0;
}

bool StatusManager::didSeePopUpForSpecialType(int thisType){
    bool didSee = false;
    userDefaults = CCUserDefault::sharedUserDefault();
    switch (thisType) {
        case 0:
            didSee = userDefaults->getBoolForKey("didSeeSpecialType0");  
            if (!didSee) userDefaults->setBoolForKey("didSeeSpecialType0", true);
            break;
        case 1:
            didSee = userDefaults->getBoolForKey("didSeeSpecialType1");
            if (!didSee) userDefaults->setBoolForKey("didSeeSpecialType1", true); 
            break;
        case 2:
            didSee = userDefaults->getBoolForKey("didSeeSpecialType2"); 
            if (!didSee) userDefaults->setBoolForKey("didSeeSpecialType2", true); 
            break;
        case 3:
            didSee = userDefaults->getBoolForKey("didSeeSpecialType3"); 
            if (!didSee) userDefaults->setBoolForKey("didSeeSpecialType3", true); 
            break;
        default:
            break;
    }
    return didSee;
}

void StatusManager:: setHighScore() {
   
    userDefaults = CCUserDefault::sharedUserDefault();
    switch (selectedGameMode) {
        case 0:
            if (currentScore > userDefaults->getIntegerForKey("highScorePrimary")) userDefaults->setIntegerForKey("highScorePrimary", currentScore);
            break;
        case 1:
            if (currentScore > userDefaults->getIntegerForKey("highScoreAction")) userDefaults->setIntegerForKey("highScoreAction", currentScore);
            break;
        case 2:
            if (currentScore > userDefaults->getIntegerForKey("highScoreInfinity")) userDefaults->setIntegerForKey("highScoreInfinity", currentScore);
            break;
    }
}

int StatusManager:: getHighScore(){
    userDefaults = CCUserDefault::sharedUserDefault();
    switch (selectedGameMode) {
        case 0:
            return userDefaults->getIntegerForKey("highScorePrimary");//[userDefaults integerForKey:@"highScorePrimary"];
            break;
        case 1:
            return userDefaults->getIntegerForKey("highScoreAction");//[userDefaults integerForKey:@"highScoreAction"];
            break;
        case 2:
            return userDefaults->getIntegerForKey("highScoreInfinity");//[userDefaults integerForKey:@"highScoreInfinity"];
            break;
        default:
            return 0;
            break;
    }
}

void StatusManager:: setTopTenScoresForGameMode(int thisGameMode) {
//    CCArray *topTenScores = new CCArray();
//    switch (thisGameMode) {
//        case 0:
//            topTenScores = userDefaults-> //[userDefaults arrayForKey:@"topTenScoresPrimary"];
//            break;
//        case 1:
//            topTenScores = [userDefaults arrayForKey:@"topTenScoresAction"];
//            break;
//        case 2:
//            topTenScores = [userDefaults arrayForKey:@"topTenScoresInfinity"]; 
//            break;
//        default:
//            break;
//    }
//    int topScores[10];
//    for (int i = 0; i < 10; i++) {
//        topScores[i] = [[topTenScores objectAtIndex:i] intValue];
//    }
//    if (topScores[9] < currentScore) {
//        topScores[9] = currentScore;
//        for (int i = 0; i < 9; i++) {
//            for (int j = i+1; j < 10; j++) {
//                if (topScores[i] < topScores[j]) {
//                    int k = topScores[i];
//                    topScores[i] = topScores[j];
//                    topScores[j] = k;
//                }
//            }
//        }
//    }
//    
//    NSMutableArray *array = [[NSMutableArray alloc] init];
//    for (int i = 0; i < 10; i++) {
//        [array addObject:[NSNumber numberWithInt:topScores[i]]];
//    }
//    switch (thisGameMode) {
//        case 0:
//            [userDefaults setObject:array forKey:@"topTenScoresPrimary"];
//            break;
//        case 1:
//            [userDefaults setObject:array forKey:@"topTenScoresAction"];
//            break;
//        case 2:
//            [userDefaults setObject:array forKey:@"topTenScoresInfinity"];
//            break;
//        default:
//            break;
//    }
}

CCArray* StatusManager:: getTopTenScoresForGameMode(int thisGameMode) {
    CCArray *topTenScores = new CCArray();
//    switch (thisGameMode) {
//        case 0:
//            topTenScores = [userDefaults arrayForKey:@"topTenScoresPrimary"];
//            break;
//        case 1:
//            topTenScores = [userDefaults arrayForKey:@"topTenScoresAction"];
//            break;
//        case 2:
//            topTenScores = [userDefaults arrayForKey:@"topTenScoresInfinity"];
//            break;
//        default:
//            break;
//    }
    return topTenScores;
}

int StatusManager::rowsNeededForLevel(int thisLevel){
    
    int rows = 0;
    
    if (thisLevel >= 1 && thisLevel <= 5) {
        rows = 6;
    }else if (thisLevel >= 6 && thisLevel <= 15){
        rows = 7;
    }else if (thisLevel >= 16 && thisLevel <= 20){
        rows = 8;
    }
    
    return rows;
}

int StatusManager:: pointsNeededForLevel(int thisLevel /*,GameMode thisGameMode*/) {
    int points = 0;
//    switch (thisGameMode) {
//        case kTagPrimary:
//            if (thisLevel < 6) points = 4000; //kPointsRequiredToCompleteLevels1_5_Primary;
//                else if (thisLevel < 11) points = kPointsRequiredToCompleteLevels6_10_Primary;
//                    else if (thisLevel < 16) points = kPointsRequiredToCompleteLevels11_15_Primary;
//                        else points = kPointsRequiredToCompleteLevels16_ON_Primary;
//                            break;
//        case kTagTime:
//            if (thisLevel < 6) points = 3000; //kPointsRequiredToCompleteLevels1_5_Action;
//                else if (thisLevel < 11) points = kPointsRequiredToCompleteLevels6_10_Action;
//                    else if (thisLevel < 16) points = kPointsRequiredToCompleteLevels11_15_Action;
//                        else points = kPointsRequiredToCompleteLevels16_ON_Action;
//                            break;
//        case kTagEndress:
//            if (thisLevel < 6) points = 6000; //kPointsRequiredToCompleteLevels1_5_Infinity;
//                else if (thisLevel < 11) points = kPointsRequiredToCompleteLevels6_10_Infinity;
//                    else if (thisLevel < 16) points = kPointsRequiredToCompleteLevels11_15_Infinity;
//                        else points = kPointsRequiredToCompleteLevels16_ON_Infinity;
//                            break;
//    }

    if (thisLevel >= 1 && thisLevel <= 5) {
        points = 300 + (thisLevel - 1) * 50;
    }else if (thisLevel >=6 && thisLevel <=20){
        points = thisLevel * 100;
    }
    
    return points;
}

int StatusManager:: wildcardProbabilityForLevel(int thisLevel){
    int probability;
    
    if (thisLevel < 6) probability = kProbabilityOfWildcardSymbolInLevels1_5;
        else if (thisLevel < 11) probability = kProbabilityOfWildcardSymbolInLevels6_10;
            else if (thisLevel < 16) probability = kProbabilityOfWildcardSymbolInLevels11_15;
                else probability = kProbabilityOfWildcardSymbolInLevels16_ON;
                    
                    return probability;
}

int StatusManager::shifterProbabilityForLevel(int thisLevel){
    int probability;
    
    if (thisLevel < 6) probability = kProbabilityOfShifterSymbolInLevels1_5;
        else if (thisLevel < 11) probability = kProbabilityOfShifterSymbolInLevels6_10;
            else if (thisLevel < 16) probability = kProbabilityOfShifterSymbolInLevels11_15;
                else probability = kProbabilityOfShifterSymbolInLevels16_ON;
                    
                    return probability;
}

int StatusManager::corruptedProbabilityForLevel(int thisLevel){
    int probability;
    
    if (thisLevel < 6) probability = kProbabilityOfCorruptedSymbolInLevels1_5;
        else if (thisLevel < 11) probability = kProbabilityOfCorruptedSymbolInLevels6_10;
            else if (thisLevel < 16) probability = kProbabilityOfCorruptedSymbolInLevels11_15;
                else probability = kProbabilityOfCorruptedSymbolInLevels16_ON;
                    
                    return probability;
}

int StatusManager::hiddenProbabilityForLevel(int thisLevel) {
    int probability;
    
    if (thisLevel < 6) probability = kProbabilityOfHiddenSymbolInLevels1_5;
        else if (thisLevel < 11) probability = kProbabilityOfHiddenSymbolInLevels6_10;
            else if (thisLevel < 16) probability = kProbabilityOfHiddenSymbolInLevels11_15;
                else probability = kProbabilityOfHiddenSymbolInLevels16_ON;
                    
                    return probability;    
}
