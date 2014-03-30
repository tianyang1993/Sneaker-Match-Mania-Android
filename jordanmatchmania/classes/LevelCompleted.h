//
//  GameOverLayer.h
//  VivaStampede
//
//  Created by Mikhail Berrya on 12/2/13.
//
//

#ifndef __VivaStampede__GameOverLayer__
#define __VivaStampede__GameOverLayer__

#include <iostream>
#include "cocos2d.h"
USING_NS_CC;

class GameScene;
class LevelCompleted:public CCLayer{
public:
    virtual bool init();
    static LevelCompleted* layer();
    CCSize size;
    double dScaleX , dScaleY;
    CCSprite* popUp;
    void initWithGame(GameScene* nScene);
    void restart(CCObject* pSender);
    
    void onClickEnd();
    void onClickNext();
    
    GameScene* m_nGameScene;
   
    void ccTouchesBegan(CCSet* touches,CCEvent* event);
    CREATE_FUNC(LevelCompleted);
    
};

#endif /* defined(__VivaStampede__GameOverLayer__) */
