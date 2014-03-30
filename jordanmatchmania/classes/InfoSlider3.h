//
//  InfoSlider3.h
//  VivaStampede
//
//  Created by Mikhail Berrya on 11/25/13.
//
//

#ifndef __INFOSLIDER3_LAYER_H__
#define __INFOSLIDER3_LAYER_H__

#include <iostream>
#include "cocos2d.h"
USING_NS_CC;

class SymbolManager;
class SyntaxSymbol;
class InfoSlide3:public CCLayer{
public:
    virtual bool init();
    static InfoSlide3* body();
    
    CCSize  size;
    int count;
    
    double dScaleX , dScaleY;
    CCLabelTTF* m_lTitleLabel;
    CCLabelTTF* m_lDescriptionLabel;
    
    SymbolManager* symbolManager;
    SyntaxSymbol *symbolToMakeSuper;
    SyntaxSymbol *symbolA;
    SyntaxSymbol *symbolB;
    
    SyntaxSymbol* symbolTemp;
    
    CCArray* allSymbols;
    CCArray* allSymbolsTem;
    CCSprite* selectbox;
    CCAnimation* maske;
    
    void initWithSymbol();
    void nextWithSymbol();
    void step1(float dt);
    void step2(float dt);
    
    CREATE_FUNC(InfoSlide3);
    CCAnimation*   createArray (char* name , int framCount);
};

#endif /* defined(__VivaStampede__InfoSlider3__) */
