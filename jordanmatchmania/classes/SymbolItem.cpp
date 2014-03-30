//
//  SymbolItem.cpp
//  VivaStampede
//
//  Created by Mikhail Berrya on 11/26/13.
//
//

#include "SymbolItem.h"
#include "SymbolManager.h"
#include "SyntaxSymbol.h"

SymbolItem* SymbolItem::sharedItem(){
    
    static SymbolItem* temp = NULL;
    if (temp == NULL) {
        temp = new SymbolItem();
    }
    
    return temp;
}

void SymbolItem::initWithDictionary(CCDictionary* symbolDictionary) {
    if(this != NULL)
    {
        isOfType = (int)symbolDictionary->objectForKey("isOfType");//[[symbolDictionary objectForKey:@"isOfType"] intValue];
        isVisible =(bool)symbolDictionary->objectForKey("isVisible"); //[[symbolDictionary objectForKey:@"isVisible"] boolValue];
        isSelected =(bool)symbolDictionary->objectForKey("isSelected");   //[[symbolDictionary objectForKey:@"isSelected"] boolValue];
        isExplosive = (bool)symbolDictionary->objectForKey("isExplosive");//[[symbolDictionary objectForKey:@"isExplosive"] boolValue];
        isShifter = (bool)symbolDictionary->objectForKey("isShifter");//[[symbolDictionary objectForKey:@"isShifter"] boolValue];
        isKeepable = (bool)symbolDictionary->objectForKey("isKeepable");//[[symbolDictionary objectForKey:@"isKeepable"] boolValue];
        isToExplode = (bool)symbolDictionary->objectForKey("isToExplode");//[[symbolDictionary objectForKey:@"isToExplode"] boolValue];
        isLShapeCorner = (bool)symbolDictionary->objectForKey("isLShapeCorner");//[[symbolDictionary objectForKey:@"isLShapeCorner"] boolValue];
        isSuperEliminated = (bool)symbolDictionary->objectForKey("isSuperEliminated");//[[symbolDictionary objectForKey:@"isSuperEliminated"] boolValue];
        dropSize = (int)symbolDictionary->objectForKey("dropSize");//[[symbolDictionary objectForKey:@"dropSize"] intValue];
        
        symbolManager = SymbolManager::sharedSymbolManager();
        if (symbolManager != NULL) {
            symbol = symbolManager->symbolWithIsOfType(isOfType);
        }
               
    }
    
}

void SymbolItem::initWithSymbol(SyntaxSymbol *symbolObj) {
    
     symbol = symbolObj;
}

CCDictionary* SymbolItem :: getDataInDictionary(){
    CCDictionary * tempReturnDictionary = new CCDictionary();
    
    if (symbol != NULL) {
        isOfType = symbol->isOfType;
        isVisible = symbol->isVisible;
        isSelected = symbol->isSelected;
        isExplosive = symbol->isExplosive;
        isShifter = symbol->isShifter;
        isKeepable = symbol->isKeepable;
        isToExplode = symbol->isToExplode;
        isLShapeCorner = symbol->isLShapeCorner;
        isSuperEliminated = symbol->isSuperEliminated;
        dropSize = symbol->dropSize;
         
        tempReturnDictionary->setObject((CCObject*)isOfType, "isOfType");
        tempReturnDictionary->setObject((CCObject*)isVisible, "isVisible");
        tempReturnDictionary->setObject((CCObject*)isSelected, "isSelected");
        tempReturnDictionary->setObject((CCObject*)isExplosive, "isExplosive");
        tempReturnDictionary->setObject((CCObject*)isShifter, "isShifter");
        tempReturnDictionary->setObject((CCObject*)isKeepable, "isKeepable");
        tempReturnDictionary->setObject((CCObject*)isToExplode, "isToExplode");
        tempReturnDictionary->setObject((CCObject*)isOfType, "isLShapeCorner");
        tempReturnDictionary->setObject((CCObject*)isSuperEliminated, "isSuperEliminated");
        tempReturnDictionary->setObject((CCObject*)dropSize, "dropSize");
        
    }
    
    return tempReturnDictionary;
    
}
