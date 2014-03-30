//
//  SymbolItem.h
//  VivaStampede
//
//  Created by Mikhail Berrya on 11/26/13.
//
//

#ifndef __VivaStampede__SymbolItem__
#define __VivaStampede__SymbolItem__

#include <iostream>
#include "cocos2d.h"
USING_NS_CC;

class SymbolManager;
class SyntaxSymbol;
class SymbolItem : public CCObject{
public:
     
    static SymbolItem* sharedItem();
    
    SyntaxSymbol *symbol;
    SymbolManager *symbolManager;
    int isOfType;
    bool isVisible;
    bool isSelected;
    bool isExplosive;
    bool isShifter;
    bool isKeepable;
    bool isToExplode;
    bool isLShapeCorner;
    bool isSuperEliminated;
    CCPoint isIndex;
    int dropSize;
    
    
    void initWithDictionary(CCDictionary* symbolDictionary);
    void initWithSymbol(SyntaxSymbol* symbolObj);
    CCDictionary*  getDataInDictionary();

};

#endif /* defined(__VivaStampede__SymbolItem__) */
