//
//  InfoSlider6.h
//  VivaStampede
//
//  Created by Mikhail Berrya on 11/25/13.
//
//

#ifndef __INFOSLIDER6_LAYER_H__
#define __INFOSLIDER6_LAYER_H__
#include <iostream>
#include "cocos2d.h"

USING_NS_CC;

class InfoSlide6:public CCLayer{
public:
    virtual bool init();
    static InfoSlide6* body();
    
    CCSize  size;
    
    double dScaleX , dScaleY;
    CCLabelTTF* m_lTitleLabel;
    CCLabelTTF* m_lDescriptionLabel1;
    CCLabelTTF* m_lDescriptionLabel2;
    CCLabelTTF* m_lDescriptionLabel3;
    CCLabelTTF* m_lDescriptionLabel4;
    CREATE_FUNC(InfoSlide6);
};


#endif /* __INFOSLIDER6_LAYER_H__ */
