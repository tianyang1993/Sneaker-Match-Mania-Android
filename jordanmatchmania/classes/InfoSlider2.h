//
//  InfoSlider2.h
//  VivaStampede
//
//  Created by Mikhail Berrya on 11/25/13.
//
//

#ifndef __INFOSLIDER2_LAYER_H__
#define __INFOSLIDER2_LAYER_H__

#include <iostream>
#include <iostream>
#include "cocos2d.h"

USING_NS_CC;

class SymbolManager;
class SyntaxSymbol;
class InfoSlide2:public CCLayer{
public:
    virtual bool init();
    static InfoSlide2* body();
    CCSize  size;
    
    
    int count;
    double dScaleX , dScaleY;
    CCLabelTTF* m_lTitleLabel;
    CCLabelTTF* m_lDescriptionLabel;
    
    SymbolManager* symbolManager;
    SyntaxSymbol *symbolToMakeExplosive;
    SyntaxSymbol *symbolA;
    SyntaxSymbol *symbolB;
    CCArray* allSymbols;
    CCSprite* selectbox;
    
    void initWithSymbol();
    void nextWithSymbol();
    void step1(float dt);
    void step2(float dt);
    void ExplodeAnimation();
    
    
    CCAnimation*   createArray (char* name , int framCount);
    
    
    CREATE_FUNC(InfoSlide2);
};


#endif /* defined(__VivaStampede__InfoSlider2__) */
