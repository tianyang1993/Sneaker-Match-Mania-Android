//
//  InfoSlider1.h
//  VivaStampede
//
//  Created by Mikhail Berrya on 11/25/13.
//
//

#ifndef __INFOSLIDER1_LAYER_H__
#define __INFOSLIDER1_LAYER_H__


#include <iostream>
#include "cocos2d.h"

USING_NS_CC;
class SyntaxSymbol;
class SymbolManager;
class InfoSlide1:public CCLayer{
public:
    virtual bool init();
    static InfoSlide1* body();
    
    void initSymbol();
    void step(float dt);
    
    CCSize  size;
    double dScaleX , dScaleY;
    
    CCLabelTTF* m_lTitleLabel;
    CCLabelTTF* m_lDescriptionLabel;
    
    SyntaxSymbol* symbolA;
    SyntaxSymbol* symbolB;
    CCSprite* selectbox;
    
    SymbolManager* symbolManager;
    CCArray* allSymbols;
    
    int count;
    
    CREATE_FUNC(InfoSlide1);
};
#endif /* __INFOSLIDER1_LAYER_H__*/