//
//  JoinLayer.h
//  jordanmatchmania
//
//  Created by Lion on 3/24/14.
//
//

#ifndef jordanmatchmania_JoinLayer_h
#define jordanmatchmania_JoinLayer_h

#include "cocos2d.h"

class JoinLayer : public cocos2d::CCLayer
{
public:
    
    virtual bool init();
    static cocos2d::CCScene* scene();

    void onClickPlay();
    
    CREATE_FUNC(JoinLayer);
};

#endif
