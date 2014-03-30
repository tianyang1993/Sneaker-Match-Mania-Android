//
//  SyntaxSymbol.h
//  VivaStampede
//
//  Created by Mikhail Berrya on 11/25/13.
//
//

#ifndef __VivaStampede__SyntaxSymbol__
#define __VivaStampede__SyntaxSymbol__

#include <iostream>
#include "cocos2d.h"
USING_NS_CC;

class SyntaxSymbol:public CCSprite{
public:
    static SyntaxSymbol* body();
    
    int isOfType;
    bool isVisible;
    bool isSelected;
    bool isExplosive;
    bool isShifter;
    bool isKeepable;
    bool isToExplode;
    bool isLShapeCorner;
    bool isSuperEliminated;
    bool isRemoved;
    
    CCPoint isIndex;
    int  dropSize;
    
    
    CREATE_FUNC(SyntaxSymbol);
};

#endif /* defined(__VivaStampede__SyntaxSymbol__) */
