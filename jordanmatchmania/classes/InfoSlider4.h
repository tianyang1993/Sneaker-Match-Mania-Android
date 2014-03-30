//
//  InfoSlider4.h
//  VivaStampede
//
//  Created by Mikhail Berrya on 11/25/13.
//
//

#ifndef __INFOSLIDER4_LAYER_H__
#define __INFOSLIDER4_LAYER_H__

#include <iostream>
#include "cocos2d.h"
USING_NS_CC;

class InfoSlide4 : public CCLayer{
public:
    virtual bool init();
    static InfoSlide4* body();
    
    CCSize size;
    
    double dScaleX , dScaleY;
    CCLabelTTF* m_lTitleLabel;
    CCLabelTTF* m_lDescriptionLabel1;
    CCLabelTTF* m_lDescriptionLabel2;
    CCLabelTTF* m_lDescriptionLabel3;
    CCLabelTTF* m_lDescriptionLabel4;
    
    CCAnimation* s1;
    CCAnimation* s2;
    CCAnimation* s3;
    
    CREATE_FUNC(InfoSlide4);
};

#endif /* __INFOSLIDER4_LAYER_H__ */
