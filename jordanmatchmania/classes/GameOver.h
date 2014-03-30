//
//  GameOver.h
//  VivaStampede
//
//  Created by Mikhail Berrya on 12/2/13.
//
//

#ifndef __VivaStampede__GameOver__
#define __VivaStampede__GameOver__

#include <iostream>
#include "cocos2d.h"
#include "GameSetting.h"
USING_NS_CC;

class GameScene;

class GameOver:public CCLayer {
public:
    static GameOver* layer();
    CCSize size;
    double dScaleX, dScaleY;
    GameMode        m_nGameMode;
    
    
    CCLabelTTF*     m_lLabelHighScore;
    CCLabelTTF*     m_lHighScore;
    
    GameSettings*   gameSettings;
    GameScene*      gameScene;
    
    
    void initWithGame(GameScene* nScene);
    void onPlayAgain(CCObject* pSender);
    void onFreeApp(CCObject* pSender);
    void onMainMenu(CCObject* pSender);


    CREATE_FUNC(GameOver);


};

#endif /* defined(__VivaStampede__GameOver__) */
