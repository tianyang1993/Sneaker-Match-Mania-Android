//
//  GameItem.h
//  VivaStampede
//
//  Created by Mikhail Berrya on 11/26/13.
//
//

#ifndef __VivaStampede__GameItem__
#define __VivaStampede__GameItem__

#include <iostream>
#include "cocos2d.h"

USING_NS_CC;

class SymbolManager;
class StatusManager;
class GameSettings;

class GameItem : public CCObject{
public:
    static GameItem* sharedGameItem();
    void init();
    StatusManager *stats;
    CCArray *gameGrid;
    bool isPaused;
    bool isActive;
    float timer;
    
    SymbolManager *symbolManager;
    GameSettings *gameSettings;
    
    void initWithDictionary(CCDictionary* gameDictionary);
    CCDictionary* getDataInDictionary();


    
};

#endif /* defined(__VivaStampede__GameItem__) */
