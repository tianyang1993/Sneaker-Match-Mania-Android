//
//  ValuesManager.h
//  VivaStampede
//
//  Created by Mikhail Berrya on 11/30/13.
//
//

#ifndef __VivaStampede__ValuesManager__
#define __VivaStampede__ValuesManager__

#include <iostream>
#include "cocos2d.h"
USING_NS_CC;
//IAP macros
#define IAP_FULL_VERSION "com.bravebilly.zookeeperstampede.remove_banner_ads"
#define IAP_ADD_BACKGROUNDS "com.bravebilly.zookeeperstampede.add_backgrounds"
#define IAP_500_BYTES_PACK  "com.bravebilly.zookeeperstampede.500bytespack"
#define IAP_1000_BYTES_PACK "com.bravebilly.zookeeperstampede.1000bytespack"
#define IAP_3000_BYTES_PACK "com.bravebilly.zookeeperstampede.3000bytespack"
#define IAP_7500_BYTES_PACK "com.bravebilly.zookeeperstampede.7500bytespack"
#define IAP_20000_BYTES_PACK "com.bravebilly.zookeeperstampede.20000bytespack"
#define IAP_50000_BYTES_PACK "com.bravebilly.zookeeperstampede.50000bytespack"

#define supportEmail @"support@bravebilly.com"

#define rateLink @"http://itunes.apple.com/WebObjects/MZStore.woa/wa/viewContentsUserReviews?id=600112655&onlyLatestVersion=false&type=Purple+Software"

#define kMoreBackgroundIAPCancelled @"BackgroundIAPCancelled"
#define kMoreBackgroundIAPBought @"BackgroundIAPBought"
#define kPlayHavenID @"2cdc6888bd5e4661a7031e3c961f6cd8"
#define kPlayHeavenSecret @"3d3a3f6d36344ad89d29255d6646e3d0"

#define kStandardMatchSound     "Match3.mp3"
#define k4MatchSound            "Match4.mp3"
#define k5MatchSound            "Match5.mp3"
#define kBadMoveSound           "BadMove.mp3"
#define kMLogoBombSound         "MLogoBomb.mp3"
#define kGlitterBombSound       "GlitterBomb.mp3"
#define kSparklingBombSound     "SparklingBomb.mp3"
#define kLevelFailSound         "LevelFail.mp3"
#define kLevelPassedSound       "LevelPassed.mp3"
#define kLast10seconds          "Last10seconds.mp3"
#define kIntroMusic             "IntroMusic.mp3"
#define kPlayMusic1             "PlayMusic1.mp3"
#define kPlayMusic2             "PlayMusic2.mp3"

#define anim_idle_frames        10
#define anim_movement_frames    10
#define anim_glow_frames        10
#define anim_spark_frames       8
#define anim_clear_frames       10

#define max_lives                   3
#define level_clock                 30

#define symbol_w                70
#define symbol_h                70

//#define USE_TESTFLIGHT //comment it on release

//#ifdef USE_TESTFLIGHT
//#import "TestFlight.h"
//#define NSLog TFLog


extern int kPointsStandardMatch;
extern int kPointsDoubleMatch;
extern int kPointsShifterMatch;
extern int kPoints4Match;
extern int kPoints4MatchExplosion;
extern int kPoints5Match;
extern int kPointsSuperEliminatedSymbol;
extern int kPointsLMatch;
extern int kPointsCorruptedEliminated;
extern int kPointsCascadingMatch;
extern int kPointsDeducedWhenUsingPrompt;
extern int kPointsDeducedWhenNonMatchMove;
extern int kPointsRequiredToCompleteLevels1_5_Primary;
extern int kPointsRequiredToCompleteLevels6_10_Primary;
extern int kPointsRequiredToCompleteLevels11_15_Primary;
extern int kPointsRequiredToCompleteLevels16_ON_Primary;
extern int kPointsRequiredToCompleteLevels1_5_Action;
extern int kPointsRequiredToCompleteLevels6_10_Action;
extern int kPointsRequiredToCompleteLevels11_15_Action;
extern int kPointsRequiredToCompleteLevels16_ON_Action;
extern int kPointsRequiredToCompleteLevels1_5_Infinity;
extern int kPointsRequiredToCompleteLevels6_10_Infinity;
extern int kPointsRequiredToCompleteLevels11_15_Infinity;
extern int kPointsRequiredToCompleteLevels16_ON_Infinity;
extern int kProbabilityOfCorruptedSymbolInLevels1_5;
extern int kProbabilityOfShifterSymbolInLevels1_5;
extern int kProbabilityOfHiddenSymbolInLevels1_5;
extern int kProbabilityOfWildcardSymbolInLevels1_5;
extern int kProbabilityOfCorruptedSymbolInLevels6_10;
extern int kProbabilityOfShifterSymbolInLevels6_10;
extern int kProbabilityOfHiddenSymbolInLevels6_10;
extern int kProbabilityOfWildcardSymbolInLevels6_10;
extern int kProbabilityOfCorruptedSymbolInLevels11_15;
extern int kProbabilityOfShifterSymbolInLevels11_15;
extern int kProbabilityOfHiddenSymbolInLevels11_15;
extern int kProbabilityOfWildcardSymbolInLevels11_15;
extern int kProbabilityOfCorruptedSymbolInLevels16_ON;
extern int kProbabilityOfShifterSymbolInLevels16_ON;
extern int kProbabilityOfHiddenSymbolInLevels16_ON;
extern int kProbabilityOfWildcardSymbolInLevels16_ON;
extern int kPointsForByte;


#endif /* defined(__VivaStampede__ValuesManager__) */
