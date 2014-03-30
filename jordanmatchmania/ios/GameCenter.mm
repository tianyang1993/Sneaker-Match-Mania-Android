//
//  GameCenter.m
//  VivaStampede
//
//  Created by Mikhail Berrya on 12/17/13.
//
//

#import "GameCenter.h"
#include "cocos2d.h"
#import "EAGLView.h"

USING_NS_CC;

@implementation GameCenter

+ (BOOL) startGameCenter
{
    if( [self isGameCenterAPIAvailable] == NO )
    {
        CCLOG("startGameCenter Faile");
        return NO;
    }
    [self authenticateLocalPlayer];
    
    CCLOG("startGameCenter OK");
    return YES;
}

+ (BOOL) isGameCenterAPIAvailable
{
    // Check for presence of GKLocalPlayer class.
    BOOL localPlayerClassAvailable = (NSClassFromString(@"GKLocalPlayer")) != nil;
    
    // The device must be running iOS 4.1 or later.
    NSString *reqSysVer = @"4.1";
    NSString *currSysVer = [[UIDevice currentDevice] systemVersion];
    BOOL osVersionSupported = ([currSysVer compare:reqSysVer options:NSNumericSearch] != NSOrderedAscending);
    
    return (localPlayerClassAvailable && osVersionSupported);
}

+ (void) authenticateLocalPlayer
{
    GKLocalPlayer* localPlayer = [GKLocalPlayer localPlayer];
    [localPlayer authenticateWithCompletionHandler:^(NSError *error) {
        if( localPlayer.isAuthenticated )
        {
            /*
              
             CCLOG("Alias : %s", localPlayer.alias);
             CCLOG("Player ID : %s", localPlayer.playerID);
             */
            NSLog(@"Alias : %@", localPlayer.alias);
            NSLog(@"Player ID : %@", localPlayer.playerID);
        }
    }];
}

+ (void) reportScore:(int64_t)score
{
    GKScore* scoreReporter = [[[GKScore alloc] initWithCategory:LeaderboardID] autorelease];
    scoreReporter.value = score;
    [scoreReporter reportScoreWithCompletionHandler:^(NSError *error) {
        if( error != nil )
        {
            CCMessageBox("reportScore Error", "Game Center");
        }
    }];
}

UIViewController* tempUIView;
+ (void) showLeaderboard
{
    GKLeaderboardViewController* pController = [[[GKLeaderboardViewController alloc] init] autorelease];
    
    if( pController != nil )
    {
        pController.leaderboardDelegate = self;
        
        tempUIView = [[UIViewController alloc] init];
        [[[EAGLView sharedEGLView] window] addSubview:tempUIView.view];
        [tempUIView presentModalViewController:pController animated:YES];
    }
}

+ (void) leaderboardViewControllerDidFinish:(GKLeaderboardViewController *)viewController
{
    [viewController dismissModalViewControllerAnimated:YES];
    [viewController.view.superview removeFromSuperview];
    [tempUIView release];
}

@end
