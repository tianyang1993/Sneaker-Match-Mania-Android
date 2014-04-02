//
//  GameItem.cpp
//  VivaStampede
//
//  Created by Mikhail Berrya on 11/26/13.
//
//

#include "GameItem.h"
#import "SymbolManager.h"
#import "SymbolItem.h"
#include "StatusManager.h"

GameItem* GameItem::sharedGameItem(){
 
    static GameItem* temp =  NULL;
    if (temp == NULL) {
        temp = new GameItem();
    }
    
    return temp;
}
 
void GameItem:: init() {
	 
    gameGrid = new CCArray();
    for (int i = 0; i < 8; i++){
        CCArray* temp = new CCArray();
        gameGrid->addObject(temp);
    }
    stats = StatusManager::sharedStatusManager();
    isPaused = false;
    isActive = false;
    timer = 0.0f;
     
}

 
void GameItem::initWithDictionary(CCDictionary*gameDictionary) {
    
//        if (gameDictionary) {
//            
//            CCDictionary *statsDictionary =(CCDictionary*)gameDictionary->objectForKey("stats");//[gameDictionary objectForKey:@"stats"];
//           
//            if (statsDictionary != NULL) {
//                selectedGameMode = (int)statsDictionary->objectForKey("selectedGameMode");
//                currentLevel              = (int)statsDictionary->objectForKey("currentLevel");
//                currentScore              = (int)statsDictionary->objectForKey("currentScore");
//                currentLevelScore         = (int)statsDictionary->objectForKey("currentLevelScore");
//                pointsToCompleteLevel     = (int)statsDictionary->objectForKey("pointsToCompleteLevel");
//                player1Score              = (int)statsDictionary->objectForKey("player1Score");
//                player2Score              = (int)statsDictionary->objectForKey("player2Score");
//            }
//            
//            CCArray *gameGridArray = (CCArray*)gameDictionary->objectForKey("gameGrid");
//            if (gameGridArray && gameGridArray->count() == 8) {
//                for (int i = 0; i < 8; i++) {
//                    
//                    CCArray *row = (CCArray*)gameGridArray->objectAtIndex(i);
//                    
//                    if (row->count() == 8) {
//                        
//                        for (int j = 0; j < 8; j++) {
//                            
//                            SymbolItem *symbolItem = SymbolItem ::sharedItem();
//                            symbolItem->symbolManager = symbolManager;
//                            symbolItem->initWithDictionary(row->objectAtIndex(j));
//                            [[gameGrid objectAtIndex:i] addObject:symbolItem];
//                            
//                        }
//                        
//                    }
//                    
//                }
//            }
//            
//            isPaused    = (bool) gameDictionary->objectForKey("isPaused");//[[gameDictionary objectForKey:@"isPaused"] boolValue];
//            isActive    = (bool) gameDictionary->objectForKey("isActive");//[[gameDictionary objectForKey:@"isActive"] boolValue];
//            timer       =  1.0f;//(float) gameDictionary->objectForKey("timer");//[[gameDictionary objectForKey:@"timer"] floatValue];
//        }
    
   
}

CCDictionary* GameItem::getDataInDictionary(){
    CCDictionary * tempReturnDictionary = new CCDictionary();//[[NSMutableDictionary alloc] init];
    
//    CCDictionary *statsDic = [NSDictionary dictionaryWithObjectsAndKeys:
//                              [NSNumber numberWithInt:stats.selectedGameMode], @"selectedGameMode",
//                              [NSNumber numberWithInt:stats.currentLevel], @"currentLevel",
//                              [NSNumber numberWithInt:stats.currentScore], @"currentScore",
//                              [NSNumber numberWithInt:stats.currentLevelScore], @"currentLevelScore",
//                              [NSNumber numberWithInt:stats.pointsToCompleteLevel], @"pointsToCompleteLevel",
//                              [NSNumber numberWithInt:stats.player1Score], @"player1Score",
//                              [NSNumber numberWithInt:stats.player2Score], @"player2Score",
//                              nil];
    
//    CCArray *gameGridArray = new CCArray();
//    
//    for (CCArray *row in gameGrid) {
//        
//        CCArray *symbolItems = new CCArray();
//        
//        for(SymbolItem *symbolItem in row){
//            [symbolItems addObject:[symbolItem getDataInDictionary]];
//        }
//        
//        [gameGridArray addObject:symbolItems];
//        
//    }
//    
//    [tempReturnDictionary setObject:statsDic forKey:@"stats"];
//    [tempReturnDictionary setObject:gameGridArray forKey:@"gameGrid"];
//    [tempReturnDictionary setObject:[NSNumber numberWithBool:self.isPaused] forKey:@"isPaused"];
//    [tempReturnDictionary setObject:[NSNumber numberWithBool:self.isActive] forKey:@"isActive"];
//    [tempReturnDictionary setObject:[NSNumber numberWithFloat:self.timer] forKey:@"timer"];
//    
    return tempReturnDictionary;
}