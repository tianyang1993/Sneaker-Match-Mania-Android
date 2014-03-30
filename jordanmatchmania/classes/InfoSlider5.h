//
//  InfoSlider5.h
//  VivaStampede
//
//  Created by Mikhail Berrya on 11/25/13.
//
//

#ifndef __INFOSLIDER5_LAYER_H__
#define __INFOSLIDER5_LAYER_H__

#include <iostream>
#include "cocos2d.h"

USING_NS_CC;

class InfoSlide5:public CCLayer{
public:
    virtual bool init();
    static InfoSlide5* body();
    
    CCSize  size;
    
    double dScaleX , dScaleY;
    CCLabelTTF* m_lTitleLabel;
    CCLabelTTF* m_lDescriptionLabel;
    
    CREATE_FUNC(InfoSlide5);
};

#endif /* __INFOSLIDER5_LAYER_H__ */
