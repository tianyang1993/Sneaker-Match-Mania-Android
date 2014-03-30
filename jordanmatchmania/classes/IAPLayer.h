//
//  IAPLayer.h
//  VivaStampede
//
//  Created by Mikhail Berrya on 12/3/13.
//
//

#ifndef __VivaStampede__IAPLayer__
#define __VivaStampede__IAPLayer__

#include <iostream>
#include "cocos2d.h"
USING_NS_CC;

class IAPLayer:public CCLayerColor{
public:
    static IAPLayer* layer();
    
    CREATE_FUNC(IAPLayer);
};

#endif /* defined(__VivaStampede__IAPLayer__) */
