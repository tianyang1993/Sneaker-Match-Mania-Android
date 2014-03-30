//
//  IntroLayer.h
//  VivaStampede
//
//  Created by Mikhail Berrya on 11/25/13.
//
//

#ifndef __INTROLAYER_SCENE_H__
#define __INTROLAYER_SCENE_H__

#include "cocos2d.h"

class IntroLayer : public cocos2d::CCLayer
{
public:
    
    virtual bool init();
    static cocos2d::CCScene* scene();
    void Next(CCObject* pSender);
    
    CREATE_FUNC(IntroLayer);
};

#endif // __INTROLAYER_SCENE_H__
