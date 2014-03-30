//
//  PauseLayer.h
//  VivaStampede
//
//  Created by Mikhail Berrya on 11/25/13.
//
//

#ifndef __VivaStampede__PauseLayer__
#define __VivaStampede__PauseLayer__

#include <iostream>
#include "cocos2d.h"
#include "AnalyticX.h"

USING_NS_CC;

class GameScene;
class GameSettings;
class PauseLayer: public CCLayer{
public:
     
    static  PauseLayer* pause();
    void    initWithGame(GameScene* nScene);
    
    CCSize size;
    double dScaleX , dScaleY;
 
    GameScene* m_nScene;
    GameSettings* m_nGameSettings;
    
    
    CCMenuItemFont* resume;
    CCMenuItemFont* restart;
    CCMenuItemFont* mainmenu;
    CCMenuItemFont* getfreeapp;
    CCMenuItemFont* sfxon;
    CCMenuItemFont* sfxoff;
    CCMenuItemFont* musicon;
    CCMenuItemFont* musicoff;
    
    void setBackGroundView(int nType);
    void onResume(CCObject* pSender);
    void onRestart(CCObject* pSender);
    void onMainMenu(CCObject* pSender);
    void onGetFreeApp(CCObject* pSender);
    void onSfxOn(CCObject* pSender);
    void onMusicOn(CCObject* pSender);
    
    CREATE_FUNC(PauseLayer);
    

};

#endif /* defined(__VivaStampede__PauseLayer__) */
