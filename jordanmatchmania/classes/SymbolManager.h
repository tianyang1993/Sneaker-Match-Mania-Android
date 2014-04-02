//
//  SymbolManager.h
//  VivaStampede
//
//  Created by Mikhail Berrya on 11/25/13.
//
//

#ifndef __VivaStampede__SymbolManager__
#define __VivaStampede__SymbolManager__

#include <iostream>
#include "cocos2d.h"
#include "MainView.h"
 

USING_NS_CC;
class SyntaxSymbol;
class StatusManager;
class GameEngine;
class SymbolManager :public CCObject{
public:
    static SymbolManager* sharedSymbolManager();
    
    CCSize  size;
    double dScaleX , dScaleY;
 
    
    MainView* viewController;
    GameEngine* gameEngine;
  
    
    CCRect          normalFrame;
    CCRect          engageFrame;
    CCRect          explosionFrame;
    
    CCAnimation         *hiddenSymbolAnimationFrames;
    CCAnimation         *superSymbolMorphFrames;
    CCAnimation         *rectifySymbolMorphFrames;
    CCAnimation         *explodingSymbolFrames;
    CCAnimation         *LShapeFramesV;
    CCAnimation         *LShapeFramesH;
    CCAnimate           *aniExplode ;
    CCAnimation         *maske;
    
    
    int             wildcardProbability;
    int             shifterProbability;
    int             corruptedProbability;
    int             hiddenProbability;
    float           m_nDelaytime;
    
    CCSprite*       LShapeHorizontal;
    CCSprite*       LShapeVertical;
    
    
public:
 
 
    SyntaxSymbol*   randomSymbolWithMaxType(int maxTypes);
    SyntaxSymbol*   symbolWithType(int thisType);
    SyntaxSymbol*   symbolWithIsOfType(int isOfType);
    
    void            turnToExplosiveSymbol(SyntaxSymbol *thisSymbol);
    void            turnToSuperSymbol(SyntaxSymbol *thisSymbol);
    void            turnToWildcardSymbol(SyntaxSymbol *thisSymbol);
    void            rectifyCorruptedSymbol(SyntaxSymbol *thisSymbol);
    void            shiftSymbol(SyntaxSymbol *thisSymbol , int thisType);
    void            revealHiddenSymbol(SyntaxSymbol *thisSymbol);
    
    void            animHideSymbol(SyntaxSymbol *thisSymbol , float thisDelay);

    void            animHintSysmbol(SyntaxSymbol *thisSymbol, float thisDelay);
    void            animIdleSysmbol(SyntaxSymbol *thisSymbol);
    void            animGlowSymbol(SyntaxSymbol *thisSymbol);
    void            animSparkSymbol(SyntaxSymbol *thisSymbol);
    
    void            animExplodeSymbol(SyntaxSymbol *thisSymbol , float thisDelay);
    void            setAnimationExplode(CCObject* pSender);
    void            DieAnimation(CCObject* pSender);
    
    void            animShiftToSuperSymbol(SyntaxSymbol *thisSymbol);
    void            animSuperSymbol(SyntaxSymbol *thisSymbol);
    void            setAnimationSuper(CCObject* pSender);
    
    
    void            animSuperEliminateSymbol(SyntaxSymbol *thisSymbol);
    void            animRectifySymbol(SyntaxSymbol *thisSymbol);
    void            animShifterSymbol(SyntaxSymbol *thisSymbol);
  
    
    void            animGlitchSymbol(SyntaxSymbol *thisSymbol , float thisDelay);
    void            animFlashSymbol(SyntaxSymbol *thisSymbol);
    void            animLShapeOnSymbol(SyntaxSymbol * thisSymbol , CCLayer* thisView);
    void            removeLShapeOnSymbol(CCObject*pSender);
    
    
    void            refreshGrid(CCArray *thisGrid);
    void            cleanSymbol(SyntaxSymbol *thisSymbol);
    void            updateProbabilities();
    void            zeroProbabilities();
    
    void            removdSymbol(CCObject* pSender);
    void            addSymbol(CCObject* pSender);
    
    
    
    
    
};


#endif /* defined(__VivaStampede__SymbolManager__) */
