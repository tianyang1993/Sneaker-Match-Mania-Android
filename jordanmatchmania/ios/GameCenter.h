//
//  GameCenter.h
//  VivaStampede
//
//  Created by Mikhail Berrya on 12/17/13.
//
//

 

#import <Foundation/Foundation.h>
#import <GameKit/GameKit.h>
 
#define LeaderboardID @"testLBId"//itunes setting ID

@interface GameCenter : NSObject <GKLeaderboardViewControllerDelegate>

+ (BOOL) startGameCenter;
 
+ (BOOL) isGameCenterAPIAvailable;
///< connect identify
+ (void) authenticateLocalPlayer;
///< score request
+ (void) reportScore:(int64_t)score;

+ (void) showLeaderboard;

@end
