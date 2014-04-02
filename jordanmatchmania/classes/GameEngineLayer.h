//
//  GameEngineLayer.h
//  VivaStampede
//
//  Created by Mikhail Berrya on 11/26/13.
//
//

#ifndef __VivaStampede__GameEngineLayer__
#define __VivaStampede__GameEngineLayer__

#include <iostream>
#include "cocos2d.h"
#include "GameSetting.h"
#include "GameScene.h"

USING_NS_CC;

class SymbolManager;
class SyntaxSymbol;
class GameEngine : public CCLayer{
public:
    virtual bool init();
    static GameEngine* body();
    ~GameEngine();
   
    bool isVisible;
    bool canTouch;
    bool startTouch;
    bool popTouch;
    
    CCSize  size;
    double dScaleFactorX , dSclaeFactorY;
    float  delayMoveTime;
   
    
    GameScene *gameScene;
    GameSettings* gameSettings;
    SymbolManager *symbolManager;
    
    CCArray* popBack;
    CCArray* popTitle;
    CCArray* popDescription;
   
    CCArray     *gameGrid;
    
    CCArray     *hintGrid;
    CCArray     *symbolsToRemove;
    CCArray     *symbolsToMove;
    CCArray     *symbolsToSkip;
    CCArray     *allPopUps;
   
    bool isShockwave;
    bool isCascading;
    bool isDoubleMatch;
    bool isMoveValid;
    bool didSuperEliminate;
    bool actionStop;
    bool levelCompleted;
    
    CCPoint shockwaveCentre;
    CCPoint firstTouchPos;
    
    SyntaxSymbol *firstTouchedSymbol;
    
    int noOfNormalMatches;
    int noOfDoubleMatches;
    int noOfShifterMatches;
    int noOfMatchesOf4;
    int noOfMatchesOf4Explosion;
    int noOfMatchesOf5;
    int noOfSuperEliminated;
    int noOfLShapedMatches;
    int noOfCorruptedCleared;
    int noOfCascadingMatches;
    int pointsToAdd;
    
   
    
    CCSprite* stuckLabel;
    CCSprite* stuckPoint1;
    CCSprite* stuckPoint2;
    CCSprite* stuckPoint3;
   
    bool stuckMessage;
    bool canShowStuck;
    bool visibleStatus;
    int stuckMessageCounter;
    
    
    CCSprite* background;
    CCLabelTTF* m_lTitle;
    CCLabelTTF* m_lDescription;

//Local Functions
   
    void initGame();
    void resetLocalStore();
    void populateGameField();
    void populateGameFieldForNextLevel();
    
    void checkIfSymbolNotMakingPattern(SyntaxSymbol *thisSymbol);
    void selectSymbol(SyntaxSymbol* thisSymbol);
    bool symbol(CCPoint firstIndex ,CCPoint secondIndex);
    void swapSymbol(SyntaxSymbol * firstSymbol,SyntaxSymbol* secondSymbol);
    void swapBackSymbol(SyntaxSymbol* firstSymbol , SyntaxSymbol *secondSymbol);
    void eliminateNeightboursOfSymbolAtIndex(CCPoint thisIndex);
    void eliminateAllSymbolsOfType(int thisType);
    void eliminateAllSymbolsInLineWithSymbolAtIndex(CCPoint thisIndex);
    void eraseSymbols();
    void refillGameField();
    void repositionAllSymbols();
    void checkIfAllSymbolsRepositioned();
 
    void shiftShifters();
    void rectify();
    void buyWildcard();
    void reshuffle();
    
    
    void rectifySearch();//customize
    void searchPatterns();
    void searchPatternTShapeForSymbol(SyntaxSymbol *thisSymbol);
    void searchPatternLShapeForSymbol(SyntaxSymbol *thisSymbol);
    void searchPatternHorizontalForSymbol(SyntaxSymbol *thisSymbol);
    void searchPatternVerticalForSymbol(SyntaxSymbol *thisSymbol);
    
    bool didFindHint();
    CCPoint getHint();
    void HintAction(SyntaxSymbol* hintSymbol);
    void stopHitAction(CCObject* pSender);
    void moveSymbol(SyntaxSymbol *thisSymbol, CCPoint thisDirection);
    bool possiblePatternFoundForSymbol(SyntaxSymbol *thisSymbol);
    void newSymbolMake(CCPoint nPos);
    
    
    CCPoint CCPointFromIndex(CCPoint thisIndex);
    void glitch();
    void shockWaveFromCenter(CCPoint thisCenter);
    void clearPoints();
    void checkScore();
    void resetGame();
    void clearGame();
    void removStuckMessage(CCObject* pSender);
    
    //Schduler
    bool timerUntilStuck;
    bool timerToRemoveStuck;
   
    void showStuckMessage(CCObject* pSender);
    void hideStuckMessage();
    
    void move(CCObject* pSender);

    
   
    void refreshStuckTimer();
    void refreshTimerToRemoveStuck();
   
     
    void stopAllTimers();
     
    bool getHintExceptThis(CCPoint lastPoint);
    ///\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/
    void makeBox(SyntaxSymbol* thisSymbol);
    void removeBox(SyntaxSymbol* thisSymbol);
     
    void setSymbloPosition(CCObject* pSender);
    CCSprite* box;
    ///\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/
    // touchEvent
    void ccTouchesBegan(CCSet* touches,CCEvent* event);
    void ccTouchesMoved(CCSet* touches,CCEvent* event);
    void checkForInfoPopUps();
    void clearInfoPopUps();
    void makePopUp(CCPoint nPos, int nType);

    
    void registerWithTouchDispatcher();

 

    CREATE_FUNC(GameEngine);
    
};
#endif /* defined(__VivaStampede__GameEngineLayer__) */
