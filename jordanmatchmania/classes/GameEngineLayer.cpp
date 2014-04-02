//
//  GameEngineLayer.cpp
//  VivaStampede
//
//  Created by Mikhail Berrya on 11/26/13.
//
//

#include "GameEngineLayer.h"
#include "SymbolManager.h"
#include "SyntaxSymbol.h"
#include "SymbolItem.h"
#include "GameItem.h"
#include "ValuesManager.h"
 


GameEngine* GameEngine::body(){
    
    GameEngine* layer = GameEngine::create();
    return layer;
}
GameEngine::~GameEngine(){

    if (firstTouchedSymbol != NULL) firstTouchedSymbol->release();

    if (symbolsToRemove) {
        symbolsToRemove->removeAllObjects();
        symbolsToRemove->release();
    }
   
    if (symbolsToMove) {
        symbolsToMove->removeAllObjects();
        symbolsToMove->release();
    }
    if (symbolsToSkip) {
        symbolsToSkip->removeAllObjects();
        symbolsToSkip->release();
    }
    
    if (gameGrid) {
        gameGrid->removeAllObjects();
        gameGrid->release();
    }
    
    if (allPopUps) {
        allPopUps->removeAllObjects();
        allPopUps->release();
    }

    
    stuckMessage = false;
    symbolManager = NULL;
    popTouch = false;
    unscheduleAllSelectors();
    this->stopAllActions();
    this->removeAllChildren();
    
        
    
}
bool GameEngine::init(){
    
    if (!CCLayer ::init()) {
        return false;
    }
    
    size  = CCDirector::sharedDirector()->getWinSize();
    dScaleFactorX = size.width / 640, dSclaeFactorY = size.height / 960;
    setTouchEnabled(true);
    
    
    initGame();
      
    return true;
}
void GameEngine::initGame(){
   
    
    gameSettings = GameSettings::sharedGameSettings();
    isVisible           = false;
    isShockwave         = false;
    isCascading         = false;
    isDoubleMatch       = false;
    startTouch          = false;
    timerUntilStuck     = false;
    timerToRemoveStuck  = false;
    levelCompleted      = false;
    canShowStuck        = true;
    firstTouchedSymbol  = NULL;
    firstTouchPos       = CCPointZero;
    delayMoveTime       = 0.0f;
    stuckMessageCounter = 0;
    stuckMessage = false;
    
    
    popBack             = new CCArray();
    popTitle            = new CCArray();
    popDescription      = new CCArray();
    symbolsToRemove     = new CCArray();
    symbolsToMove       = new CCArray();
    symbolsToSkip       = new CCArray();
    allPopUps           = new CCArray();
    
    
    symbolManager = SymbolManager::sharedSymbolManager();
    symbolManager->gameEngine = this;
    noOfCascadingMatches = 0;
    clearPoints();
    
     
    gameGrid = new CCArray();
        
    for (int i = 0; i < gameSettings->getGameRows(); i++) {
        CCArray* temp = new CCArray();
        gameGrid->addObject(temp);
    }
    
    box = CCSprite::create("selectionBox@2x.png");
    box->setScaleX(box->getScaleX()*dScaleFactorX);
    box->setScaleY(box->getScaleY()*dSclaeFactorY);
    box->setVisible(false);
    this->addChild(box);
    
    CCLOG("x = %f, y = %f", this->getPositionX(), this->getPositionY());
    
    for (int j = 0; j < gameSettings->getGameRows(); j++) {
        for (int k = 0; k < gameSettings->getGameRows(); k++) {

            CCSprite *gridSprite = CCSprite::create("grid.png");
            
            gridSprite->setPosition(CCPointFromIndex(CCPointMake(j, k)));

            this->addChild(gridSprite);
        }
    }
    
    this->populateGameField();
    this->refreshStuckTimer();
    

    
}
void GameEngine::refreshStuckTimer(){

    if (timerUntilStuck ) {
        unschedule(schedule_selector(GameEngine::showStuckMessage));
        timerUntilStuck = false;
    }
    hideStuckMessage();
    if (!canShowStuck) {
        stopAllTimers();
        return;
     }
    //this->schedule(schedule_selector(GameEngine::showStuckMessage), 13);
    timerUntilStuck = true;
 
}
void GameEngine::stopAllTimers(){
    
    if(timerUntilStuck) {
         unschedule(schedule_selector(GameEngine::showStuckMessage));
    }
    if(timerToRemoveStuck){
        unschedule(schedule_selector(GameEngine::hideStuckMessage));
    }
        
}
void GameEngine::refreshTimerToRemoveStuck(){
   
    
    if(!canShowStuck) {
        stopAllTimers();
        return;
    }
    if(timerToRemoveStuck) {
        unschedule(schedule_selector(GameEngine::hideStuckMessage));
        timerToRemoveStuck = false;
    }
        
    this->schedule(schedule_selector(GameEngine::hideStuckMessage) , 5);
    
}

void GameEngine::showStuckMessage(cocos2d::CCObject *pSender) {
    
    CCLOG("Schedule");
    timerUntilStuck = true;
    
    if(!canShowStuck) {
        stopAllTimers();
        return;
    }

    stuckMessageCounter++;
    if(stuckMessageCounter == 3) canShowStuck = false;
 
    if(!stuckMessage ) {
 
        stuckLabel = CCSprite::create("stuckpopup@2x.png");
        stuckPoint1 = CCSprite::create("stuckarrow@2x.png");
        stuckPoint2 = CCSprite::create("stuckarrow@2x.png");
        stuckPoint3 = CCSprite::create("stuckarrow@2x.png");
        
        stuckLabel->setPosition(ccp(size.width / 2, 350*dSclaeFactorY));
        stuckPoint1->setPosition(ccp(size.width / 2 - 130*dScaleFactorX, 250*dSclaeFactorY));
        stuckPoint2->setPosition(ccp(size.width / 2 + 30*dScaleFactorX , 250*dSclaeFactorY));
        stuckPoint3->setPosition(ccp(size.width* 3/4 - 20*dScaleFactorX, 250*dSclaeFactorY));
        
        stuckLabel->setScale(stuckLabel->getScale()*dScaleFactorX);//(ccp(size.width / 2, 350*dSclaeFactorY));
        stuckPoint1->setScale(stuckPoint1->getScale()*dScaleFactorX);
        stuckPoint2->setScale(stuckPoint2->getScale()*dScaleFactorX);
        stuckPoint3->setScale(stuckPoint3->getScale()*dScaleFactorX);

        gameScene->addChild(stuckLabel,7);
        gameScene->addChild(stuckPoint1,7);
        gameScene->addChild(stuckPoint2,7);
        gameScene->addChild(stuckPoint3,7);
        
        
        stuckPoint1->runAction(CCRepeatForever::create(CCSequence::create(CCMoveBy::create(0.8f, ccp(0 , -50*dSclaeFactorY)) , CCMoveBy::create(0.8f, ccp(0 ,50*dSclaeFactorY)), NULL)));
        stuckPoint2->runAction(CCRepeatForever::create(CCSequence::create(CCMoveBy::create(0.8f, ccp(0 , -50*dSclaeFactorY)) , CCMoveBy::create(0.8f, ccp(0 ,50*dSclaeFactorY)), NULL)));
        stuckPoint3->runAction(CCRepeatForever::create(CCSequence::create(CCMoveBy::create(0.8f, ccp(0 , -50*dSclaeFactorY)) , CCMoveBy::create(0.8f, ccp(0 ,50*dSclaeFactorY)), NULL)));
        
        stuckMessage = true;
        
    }else{
        stuckLabel->stopAllActions();
        stuckPoint1->stopAllActions();
        stuckPoint2->stopAllActions();
        stuckPoint3->stopAllActions();
        gameScene->removeChild(stuckLabel);
        gameScene->removeChild(stuckPoint1);
        gameScene->removeChild(stuckPoint2);
        gameScene->removeChild(stuckPoint3);

    }
       
    
    this->refreshTimerToRemoveStuck();
}
void GameEngine::removStuckMessage(cocos2d::CCObject *pSender){
    
    CCSprite* temp = (CCSprite*)pSender;
    temp->removeFromParent();
    temp = NULL;
   
    stuckMessage = false;
}
void GameEngine::hideStuckMessage(){
   
    CCLOG("Schedule");
   if (timerToRemoveStuck) {
       unschedule(schedule_selector(GameEngine::hideStuckMessage));
       timerToRemoveStuck = false;
   }
    
    if (stuckMessage) {
        stuckLabel->stopAllActions(); 
        stuckPoint1->stopAllActions();
        stuckPoint2->stopAllActions();
        stuckPoint3->stopAllActions();
        gameScene->removeChild(stuckLabel);
        gameScene->removeChild(stuckPoint1);
        gameScene->removeChild(stuckPoint2);
        gameScene->removeChild(stuckPoint3);
        stuckMessage = false;

    }

}

#pragma mark - GRID MANAGEMENT
//\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\

void GameEngine::reshuffle() {
 
    
    gameSettings->playSound((char*)"SFX-HiddenSymbolMorph.wav");
   
    for (int i = 0; i < gameSettings->getGameRows(); i++) {
        CCArray* temp;
        temp = (CCArray*)gameGrid->objectAtIndex(i);
        for (int j = 0; j < gameSettings->getGameRows(); j++) {
            
            SyntaxSymbol *symbol = (SyntaxSymbol*)temp->objectAtIndex(j);
            
            if (!symbol->isKeepable) {
                symbolManager->animHideSymbol(symbol , 0.5f);
                SyntaxSymbol *symbolToReplace = symbolManager->randomSymbolWithMaxType(6);
                symbolToReplace->isIndex = CCPointMake(i, j);
                symbolToReplace->setPosition(CCPointFromIndex(symbolToReplace->isIndex));
                temp->replaceObjectAtIndex(j, symbolToReplace);
                CCLOG("reshuffle type = %d", symbolToReplace->isOfType);
                gameGrid->replaceObjectAtIndex(i, temp);
                this->checkIfSymbolNotMakingPattern(symbolToReplace);
                symbolToReplace->setOpacity(1.0f);
                addChild(symbolToReplace);
            }
        }
        temp->removeAllObjects();
        temp->release();
    }
    this->glitch();
}

void GameEngine::resetLocalStore(){

//    for(NSMutableArray *row in viewController.localStore.levelMode.gameGrid){
//        [row removeAllObjects];
//    }
    
//    for (int i = 0; i < 8; i++) {
//        
//        NSMutableArray *row = [viewController.localStore.levelMode.gameGrid objectAtIndex:i];
//        
//        for (int j = 0; j < 8; j++) {
//            
//            SyntaxSymbol *symbol = [[gameGrid objectAtIndex:i] objectAtIndex:j];
//            if (symbol) {
//                [row addObject:[[SymbolItem alloc] initWithSymbol:symbol]];
//            }
//            
//        }
//    }
//    
//    viewController.localStore.levelMode.stats = [viewController.statsManager copy];
//    
//    [viewController.localStore synchronize];
}

void GameEngine::populateGameField(){
    
    CCLOG("populateGameField");
    
    for (int i = 0; i < gameSettings->getGameRows(); i++) {
        CCArray* temp = new CCArray();
        for (int j = 0; j < gameSettings->getGameRows(); j++) {
            bool isSymbolLoaded = true;
            SyntaxSymbol *symbol = NULL;
            if (!symbol)
                symbol = symbolManager->randomSymbolWithMaxType(6);
            
            symbolManager->animIdleSysmbol(symbol);
            symbol->isIndex = CCPointMake(i, j);
            symbol->setPosition(CCPointFromIndex(symbol->isIndex)); 
            temp->addObject(symbol);
            
            gameGrid->replaceObjectAtIndex(i, temp);
            this->checkIfSymbolNotMakingPattern(symbol);
            symbol->setOpacity(0.0f);
            this->addChild(symbol);
            if (isSymbolLoaded) {
                if (symbol->isShifter) {
                    symbolManager->animShifterSymbol(symbol);
                }
                
                if (symbol->isExplosive) {
                    symbol->isExplosive = false;
                    symbolManager->turnToExplosiveSymbol(symbol);
                }
                
                if (symbol->isSelected) {
                    symbol->isSelected = false;
                    firstTouchedSymbol = symbol;
                    firstTouchPos = firstTouchedSymbol->getPosition();
                    makeBox(symbol);
                    
                }
            }
            
        }
        
      }
    canTouch = true;
    this->setTouchEnabled(true);
    this->glitch();
    this->resetLocalStore();
    
}

void GameEngine::populateGameFieldForNextLevel(){
    
    CCLOG("populateGameFieldForNextLevel");
    symbolsToRemove->removeAllObjects();
    symbolsToSkip->removeAllObjects();
    symbolsToMove->removeAllObjects();
    
    for (int i = 0; i < gameSettings->getGameRows(); i++) {
        
        CCArray* temp;
        
        for (int j = 0; j < gameSettings->getGameRows(); j++) {
           temp = (CCArray*)gameGrid->objectAtIndex(i);
            SyntaxSymbol *symbol =(SyntaxSymbol*)temp->objectAtIndex(j);
            if (symbol->isKeepable) {
                symbol->setOpacity(255);//alpha = 1;
                this->addChild(symbol);
                if (symbol->isKeepable) {
                    if (symbol->isExplosive)
                        //symbolManager->animGlowSymbol(symbol);
                        symbolManager->animSparkSymbol(symbol);
                    else
                        symbolManager->animSuperSymbol(symbol);
                }
            }
            else {
                SyntaxSymbol *symbolToReplace = symbolManager->randomSymbolWithMaxType(6);
                symbolToReplace->isIndex = CCPointMake(i, j);
                symbolToReplace->setPosition(CCPointFromIndex(symbolToReplace->isIndex));
                CCLOG("populateGameFieldForNextLevel type = %d", symbolToReplace->isOfType);

                temp->replaceObjectAtIndex(j, symbolToReplace);
                gameGrid->replaceObjectAtIndex(i, temp);
                this->checkIfSymbolNotMakingPattern(symbolToReplace);
                symbolToReplace->setOpacity(10.0f);
                addChild(symbolToReplace);
            }
        }
        
        temp->removeAllObjects();
        temp->release();
         
    }
    this->glitch();
     
    //    [symbolManager performSelector:@selector(refreshGrid:) withObject:gameGrid afterDelay:1];
    canTouch = true;
    this->setTouchEnabled(true);
    
    this->resetLocalStore();
}

void GameEngine::checkIfSymbolNotMakingPattern(SyntaxSymbol *thisSymbol) {
    
    int x = thisSymbol->isIndex.x;
    int y = thisSymbol->isIndex.y;
    int typeToSkip = thisSymbol->isOfType;
    
    bool hasToChange = false;
    
    SyntaxSymbol *symbolToCheck;
   
    if (x > 1) {
        CCArray* temp;
        temp =(CCArray*)gameGrid->objectAtIndex(x-1);
        symbolToCheck = (SyntaxSymbol*)temp->objectAtIndex(y); 
        
        if (symbolToCheck->isOfType == typeToSkip) {
            temp =(CCArray*)gameGrid->objectAtIndex(x-2);
            symbolToCheck =(SyntaxSymbol*)temp->objectAtIndex(y);  
            
            if (symbolToCheck->isOfType == typeToSkip) hasToChange = true;
            
        }
    }
    if (y > 1) {
        CCArray* temp;
        temp =(CCArray*)gameGrid->objectAtIndex(x);
        symbolToCheck =(SyntaxSymbol*)temp->objectAtIndex(y-1);  
        if (symbolToCheck->isOfType == typeToSkip) {
            
            symbolToCheck =(SyntaxSymbol*)temp->objectAtIndex(y-2); 
           
            if (symbolToCheck->isOfType == typeToSkip) hasToChange = true;
            
        }
    }
   
    if (hasToChange) {
        int newType = (arc4random() % 6);
        while (newType == typeToSkip) {
            newType = (arc4random() % 6);
        }
      symbolManager->shiftSymbol(thisSymbol,newType);
        CCLOG("%d to %d", typeToSkip, newType);
    }
}

void GameEngine::selectSymbol(SyntaxSymbol *thisSymbol){
   
    gameSettings = GameSettings::sharedGameSettings();
     
    if (firstTouchedSymbol == NULL) {
        
        gameSettings->playSound((char*)"SFX-SymbolSelect_A.wav");
          
        if (thisSymbol->isOfType == 10) {
            gameSettings->playSound((char*)"SFX-HiddenSymbolMorph.wav");
            symbolManager->revealHiddenSymbol(thisSymbol);
            this->searchPatterns();
        }
        else {
            firstTouchedSymbol = thisSymbol;
            makeBox(firstTouchedSymbol);
            
        }
    }
    else {
        removeBox(firstTouchedSymbol);
        gameSettings->playSound((char*)"SFX-SymbolSelect_B.wav");
        
        if (firstTouchedSymbol->isOfType == 7) {
            firstTouchedSymbol->isKeepable = false;
            symbolManager->shiftSymbol(firstTouchedSymbol,thisSymbol->isOfType);
            this->searchPatterns();
        }
        else if (this->symbol(thisSymbol->isIndex ,firstTouchedSymbol->isIndex)) {
            if (!(firstTouchedSymbol->isOfType == 11)){
                this->swapSymbol(thisSymbol ,firstTouchedSymbol);
            }
            else {
                firstTouchedSymbol->isSuperEliminated = true;
                symbolsToRemove->addObject(firstTouchedSymbol);
                this->eliminateAllSymbolsOfType(thisSymbol->isOfType);
            }
        }
 
        firstTouchedSymbol = NULL;
        removeChild(firstTouchedSymbol);
    }
    
    this->resetLocalStore();
}
#pragma mark My Customize
///\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\My TEST/\/\/\/\/\\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\\//\/\/\/\/\/\/\/\/\/
void GameEngine:: makeBox(SyntaxSymbol *thisSymbol){
    
    if (thisSymbol->isSelected == false) {
        box->setPosition(CCPointFromIndex(thisSymbol->isIndex));
        box->setVisible(true);
        thisSymbol->isSelected = true;
    }

}
void GameEngine:: removeBox(SyntaxSymbol* thisSymbol){
   
    if (thisSymbol->isSelected) {
        thisSymbol->isSelected = false;
        box->setVisible(false);
       
    }
}

void GameEngine::setSymbloPosition(CCObject *pSender){
    
    SyntaxSymbol* temp = (SyntaxSymbol*)pSender;
    temp->setPosition(CCPointFromIndex(temp->isIndex));
    
    
 
}
 
///\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\MY TEST/\/\/\\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\\//\/\/\/\/\/\/\/\/\/
bool GameEngine::symbol(CCPoint firstIndex,CCPoint secondIndex) {
    bool isNeighbour = false;
    if ((abs((firstIndex.x - secondIndex.x)) == 1) && (firstIndex.y == secondIndex.y)) isNeighbour = true;
        else if ((abs((firstIndex.y - secondIndex.y)) == 1) & (firstIndex.x == secondIndex.x)) isNeighbour = true;
    
    return isNeighbour;
}

# pragma mark SWAP SYMBOL START
///\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\SWAP SYMBOL ACTION START/\/\/\\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\\//\/\/\/\/\/\/\/\/\/

void GameEngine::swapSymbol(SyntaxSymbol*firstSymbol ,SyntaxSymbol*secondSymbol){
    
    canTouch = false;
    this->setTouchEnabled(false);
    
    CCArray *firstSymbolRow;
    firstSymbolRow =(CCArray*)gameGrid->objectAtIndex(firstSymbol->isIndex.x);
    CCArray *secondSymbolRow ;
    secondSymbolRow =(CCArray*)gameGrid->objectAtIndex(secondSymbol->isIndex.x);
    
    firstSymbolRow->replaceObjectAtIndex(firstSymbol->isIndex.y, secondSymbol);
    secondSymbolRow->replaceObjectAtIndex(secondSymbol->isIndex.y, firstSymbol);     
    CCPoint temp = firstSymbol->isIndex;
    
    firstSymbol->isIndex = secondSymbol->isIndex;
    secondSymbol->isIndex = temp;
    
    firstTouchedSymbol = NULL;
    removeChild(firstTouchedSymbol);
  
    firstSymbol->runAction(CCSequence::create(CCMoveTo::create(0.2f, CCPointFromIndex(firstSymbol->isIndex)) , CCCallFunc::create(this, callfunc_selector(GameEngine::move)),NULL));
    secondSymbol->runAction(CCSequence::create(CCMoveTo::create(0.2f, CCPointFromIndex(secondSymbol->isIndex)) , CCCallFunc::create(this, callfunc_selector(GameEngine::move)),NULL));
     
    isMoveValid = false;
    isDoubleMatch = true;
    this->searchPatterns();
    
    if (gameSettings->getGameMode() == kTagEndress) {
        return;
    }
   
    if (!isMoveValid){
        this->swapBackSymbol(firstSymbol,secondSymbol);
    }else{
         this->shiftShifters();
    }
    
  
   
}

void GameEngine::swapBackSymbol(SyntaxSymbol *firstSymbol,SyntaxSymbol*secondSymbol){
    
    canTouch = false;
    this->setTouchEnabled(false);
    gameSettings = GameSettings::sharedGameSettings();
    gameSettings->playSound((char*)kBadMoveSound);
    
    CCArray *firstSymbolRow = (CCArray*)gameGrid->objectAtIndex(firstSymbol->isIndex.x);
    CCArray *secondSymbolRow = (CCArray*)gameGrid->objectAtIndex(secondSymbol->isIndex.x);
    firstSymbolRow->replaceObjectAtIndex(firstSymbol->isIndex.y ,secondSymbol);
    secondSymbolRow->replaceObjectAtIndex(secondSymbol->isIndex.y,firstSymbol);
    
    CCPoint temp = firstSymbol->isIndex;
    firstSymbol->isIndex = secondSymbol->isIndex;
    secondSymbol->isIndex = temp;
   
    firstTouchedSymbol = NULL;
    removeChild(firstTouchedSymbol);
    
    CCSequence* action_a = CCSequence::create(CCDelayTime::create(0.2f), CCMoveTo::create(0.2f, CCPointFromIndex(firstSymbol->isIndex)),CCCallFunc::create(this, callfunc_selector(GameEngine::move)),NULL);
    CCSequence* action_b = CCSequence::create(CCDelayTime::create(0.2f), CCMoveTo::create(0.2f, CCPointFromIndex(secondSymbol->isIndex)),CCCallFunc::create(this, callfunc_selector(GameEngine::move)),NULL);
    firstSymbol->runAction(action_a);
    secondSymbol->runAction(action_b);
    
    
 }
void GameEngine:: move(cocos2d::CCObject *pSender){
    
    if (box->isVisible() == true) {
        box->setVisible(false);
        firstTouchedSymbol = NULL;
    }
    this->setTouchEnabled(true);
    canTouch = true;
    
}
///\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\SWAP SYMBOL ACTION END/\/\/\\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\\//\/\/\/\/\/\/\/\/\/
void GameEngine::eliminateNeightboursOfSymbolAtIndex(CCPoint thisIndex) {
    int m;
    int n;
    for (int i = -1; i < 2; i++) {
        for (int j = -1; j < 2; j++) {
            m = thisIndex.x + i;
            n = thisIndex.y + j;
            if ((m > -1) && (m < gameSettings->getGameRows() - 2) && (n > -1) && (n < gameSettings->getGameRows() - 2)) {
                CCArray* temp;
                temp = (CCArray*)gameGrid->objectAtIndex(m);
                SyntaxSymbol *symbolToAdd =(SyntaxSymbol*)temp->objectAtIndex(n); 
                if (symbolToAdd->isOfType > 6) symbolsToSkip->addObject(symbolToAdd);
                if (!(symbolsToRemove->containsObject(symbolToAdd)) && (!(symbolsToSkip->containsObject(symbolToAdd)))) {
                    symbolsToRemove->addObject(symbolToAdd);
                    symbolToAdd->isToExplode = true;
                }
            }
        }
    }
}

void GameEngine::eliminateAllSymbolsOfType(int thisType) {
    for (int i = 0; i < gameSettings->getGameRows(); i++) {
        for (int j = 0; j < gameSettings->getGameRows(); j++) {
            CCArray* temp;
            temp = (CCArray*)gameGrid->objectAtIndex(i);
            SyntaxSymbol *symbolToCheck = (SyntaxSymbol*)temp->objectAtIndex(j);//[[gameGrid objectAtIndex:i] objectAtIndex:j];
            if (symbolToCheck->isOfType == thisType) {
                symbolToCheck->isSuperEliminated = true;
                symbolsToRemove->addObject(symbolToCheck);
                noOfSuperEliminated++;
            }
        }
    }
    this->eraseSymbols();
}

void GameEngine::eliminateAllSymbolsInLineWithSymbolAtIndex(CCPoint thisIndex) {
  
    for (int i = 0; i < gameSettings->getGameRows(); i++) {
        CCArray* temp;
        temp = (CCArray*)gameGrid->objectAtIndex(i);
        SyntaxSymbol *symbolToAdd = (SyntaxSymbol*)temp->objectAtIndex(thisIndex.y);//[[gameGrid objectAtIndex:i] objectAtIndex:thisIndex.y];
        if (!(symbolsToRemove->containsObject(symbolToAdd))) symbolsToRemove->addObject(symbolToAdd);
    }
    for (int j = 0; j < gameSettings->getGameRows(); j++) {
        CCArray* temp;
        temp = (CCArray*)gameGrid->objectAtIndex(thisIndex.x);
        SyntaxSymbol *symbolToAdd =(SyntaxSymbol*)temp->objectAtIndex(j); //[[gameGrid objectAtIndex:thisIndex.x] objectAtIndex:j];
        if (!(symbolsToRemove->containsObject(symbolToAdd))) symbolsToRemove->addObject(symbolToAdd);
    }
}

void GameEngine::eraseSymbols() {
    canTouch = false;
    this->setTouchEnabled(false);
    
    if (isShockwave) {
        this->shockWaveFromCenter(shockwaveCentre);
        shockwaveCentre = CCPointMake(-1, -1);
    }
    
    didSuperEliminate = false;
    
    for (int i = 0; i < symbolsToRemove->count() ; i++) {
        SyntaxSymbol *thisSymbol = (SyntaxSymbol*)symbolsToRemove->objectAtIndex(i);
        CCArray* temp;
        if (!(symbolsToSkip->containsObject(thisSymbol))) {
            
            temp = (CCArray*)gameGrid->objectAtIndex(thisSymbol->isIndex.x);
            temp->removeObject(thisSymbol);
            CCLOG("eraseSymbols type = %d", thisSymbol->isOfType);

            gameGrid->replaceObjectAtIndex(thisSymbol->isIndex.x, temp);
            
            if (thisSymbol->isShifter) noOfShifterMatches++;
            if (thisSymbol->isOfType == 9) noOfCorruptedCleared++;
            if (thisSymbol->isToExplode) symbolManager->animExplodeSymbol(thisSymbol , (float)((arc4random() % 5) / 10.0));
            else if (thisSymbol->isLShapeCorner )symbolManager->animLShapeOnSymbol(thisSymbol , this);
            else if (thisSymbol->isSuperEliminated) {
                symbolManager->animSuperEliminateSymbol(thisSymbol);
                didSuperEliminate = true;
            }
            else{
                
                symbolManager->animHideSymbol(thisSymbol,0.3f);
            }
        }
        
         
    }
    symbolsToRemove->removeAllObjects();
    symbolsToSkip->removeAllObjects();
 
    if (isCascading) noOfCascadingMatches++;
    
    if (noOfNormalMatches > 0) gameSettings->playSound((char*)kStandardMatchSound);
    if (noOfMatchesOf4 > 0) gameSettings->playSound((char*)k4MatchSound);
    if (noOfMatchesOf4Explosion > 0) gameSettings->playSound((char*)kSparklingBombSound);
    if (noOfMatchesOf5 > 0) gameSettings->playSound((char*)k5MatchSound);
    if (noOfLShapedMatches > 0) gameSettings->playSound((char*)kSparklingBombSound);
    if (noOfSuperEliminated > 0) gameSettings->playSound((char*)kGlitterBombSound);
    
    pointsToAdd = noOfNormalMatches * kPointsStandardMatch + noOfMatchesOf4 * kPoints4Match + noOfMatchesOf4Explosion * kPoints4MatchExplosion +
    noOfMatchesOf5 * kPoints5Match + noOfLShapedMatches * kPointsLMatch + noOfSuperEliminated * kPointsSuperEliminatedSymbol +
    noOfShifterMatches * kPointsShifterMatch + noOfCorruptedCleared * kPointsCorruptedEliminated + noOfCascadingMatches * kPointsCascadingMatch +
    noOfDoubleMatches * kPointsDoubleMatch;
    
    gameScene->setGameScore(pointsToAdd);
    this->clearPoints();
    isCascading = true;
    this->refillGameField();
}

void GameEngine::refillGameField(){
  
    for (int i = 0; i < gameSettings->getGameRows(); i++) {
        CCArray* temp;
        temp = (CCArray*)gameGrid->objectAtIndex(i);

        int m = temp->count();
        if (m < gameSettings->getGameRows()) {
            for (int j = 0; j < gameSettings->getGameRows() - m; j++) {
                SyntaxSymbol *newSymbol = symbolManager->randomSymbolWithMaxType(6);
                symbolManager->animIdleSysmbol(newSymbol);
                newSymbol->setPosition(CCPointFromIndex(CCPointMake(i, gameSettings->getGameRows()+j)));
                newSymbol->isIndex = CCPointMake(i, gameSettings->getGameRows()+j);
                this->addChild(newSymbol);
                temp->addObject(newSymbol);
                CCLOG("refillGameField type = %d", newSymbol->isOfType);

                gameGrid->replaceObjectAtIndex(i, temp);
            }
        }
    }
    this->repositionAllSymbols();
    this->resetLocalStore();
}

void GameEngine::repositionAllSymbols(){
 
    for (int i = 0; i < gameSettings->getGameRows(); i++) {
        CCArray* temp;
        temp = (CCArray*)gameGrid->objectAtIndex(i);
        for (int j = 0; j < gameSettings->getGameRows(); j++) {
            SyntaxSymbol *thisSymbol = (SyntaxSymbol*)temp->objectAtIndex(j);
            if (!(thisSymbol->isIndex.y == j)) {
                thisSymbol->dropSize = thisSymbol->isIndex.y - j;
                thisSymbol->isIndex = CCPointMake(i, j);
                symbolsToMove->addObject(thisSymbol);
            }
        }
     
    }
  
    float a;
    if (didSuperEliminate) a = 1.15;
    else a = 0.15;
    int k = 0;
    int l = 0;
    float delay;
    float time;
    bool didFindSpot;
    
 
    for (int i = 0; i < gameSettings->getGameRows(); i++) {
        k = 0;
        didFindSpot = false;
        CCArray* temp ;
        temp = (CCArray*)gameGrid->objectAtIndex(i);
        
        for (int j = 0; j < gameSettings->getGameRows(); j++) {
            SyntaxSymbol *thisSymbol = (SyntaxSymbol*)temp->objectAtIndex(j);
            if (symbolsToMove->containsObject(thisSymbol)) {
                if (!didFindSpot) l++;
                didFindSpot = true;
                time = sqrtf(0.05 * thisSymbol->dropSize);
                delay = k * 0.1 + l * 0.05 + a - symbolManager->m_nDelaytime;
                delayMoveTime = delay + 0.1f + time; // Modified by Dream org:0.4f
                thisSymbol->runAction(CCSequence::create(CCDelayTime::create(delay/*+0.3f*/), CCMoveTo::create(time, CCPointFromIndex(thisSymbol->isIndex)),CCCallFuncN::create(this, callfuncN_selector(GameEngine::setSymbloPosition)), NULL));
                symbolsToRemove->removeObject(thisSymbol);
                
                k++;
            }
        }
    }
    
    if (symbolManager->m_nDelaytime == 1.0f) {
        symbolManager->m_nDelaytime = 0.0f;
    }
    symbolsToMove->removeAllObjects();
    CCLOG("DelayMove Time ==%f" , delayMoveTime);
    
    schedule(schedule_selector(GameEngine::checkIfAllSymbolsRepositioned), delayMoveTime);
    
}

void GameEngine:: newSymbolMake(CCPoint nPos){
    
    CCArray* temp ;
    int k = arc4random() % 6;
    SyntaxSymbol* newSymbol = symbolManager->symbolWithIsOfType(k);
    newSymbol->setPosition(CCPointFromIndex(nPos));
    newSymbol->isOfType = k;
    newSymbol->isIndex = nPos;
    this->addChild(newSymbol);
    
    temp = (CCArray*)gameGrid->objectAtIndex(nPos.x);
    temp->replaceObjectAtIndex(nPos.y, newSymbol);
    
    CCLOG("newSymbolMake type = %d", newSymbol->isOfType);
    gameGrid->replaceObjectAtIndex(nPos.x, temp);
    
    if (k < 6){
        symbolManager->shiftSymbol(newSymbol ,arc4random() % 6);
    }
    else
    {
        newSymbol->isKeepable = true;
        symbolManager->shiftSymbol(newSymbol,9);
        
    }
    
}
void GameEngine::checkIfAllSymbolsRepositioned(){
    unschedule(schedule_selector(GameEngine::checkIfAllSymbolsRepositioned));
    if (symbolsToMove->count() == 0){
        this->searchPatterns();
    }
}

void GameEngine::shiftShifters(){
    int k;
    for (int i = 0; i < gameSettings->getGameRows(); i++) {
        CCArray* temp;
        temp = (CCArray*)gameGrid->objectAtIndex(i);
        for (int j = 0; j < gameSettings->getGameRows(); j++) {
            SyntaxSymbol *thisSymbol = (SyntaxSymbol*)temp->objectAtIndex(j);
            if (thisSymbol->isShifter) {
                k = arc4random() % 2;
                if (k == 0) symbolManager->shiftSymbol(thisSymbol , arc4random() % 6);
            }
        }
    }
}

void GameEngine::rectify() {
    symbolManager->rectifyCorruptedSymbol(firstTouchedSymbol);
    this->selectSymbol(firstTouchedSymbol);
    searchPatterns();
   this->schedule(schedule_selector(GameEngine::rectifySearch), 1.6f);  
}
void GameEngine:: rectifySearch(){
    CCLOG("Schedule");
    unschedule(schedule_selector(GameEngine::rectifySearch));
    this->searchPatterns();
}
void GameEngine::buyWildcard(){
    symbolManager->turnToWildcardSymbol(firstTouchedSymbol);
    this->selectSymbol(firstTouchedSymbol);
}

 
#pragma mark - PATTERN SEARCHING
//\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\

void GameEngine::searchPatterns() {
    
    ///L-shaped pattern
    for (int i = 0; i < gameSettings->getGameRows(); i++) {
        CCArray* temp;
        temp = (CCArray*)gameGrid->objectAtIndex(i);
        for (int j = 0; j < gameSettings->getGameRows(); j++) {
            SyntaxSymbol *searchedSymbol = (SyntaxSymbol*) temp->objectAtIndex(j);
            if (searchedSymbol->isOfType < 7) if (!(symbolsToRemove->containsObject(searchedSymbol))) this->searchPatternLShapeForSymbol(searchedSymbol);
        }
    }
    
    ///horizontal patterns
    for (int i = 0; i < gameSettings->getGameRows() - 2; i++) {
        CCArray* temp;
        temp = (CCArray*)gameGrid->objectAtIndex(i);
        for (int j = 0; j < gameSettings->getGameRows(); j++) {
            SyntaxSymbol *searchedSymbol = (SyntaxSymbol*) temp->objectAtIndex(j);
            if (searchedSymbol->isOfType < 7) if (!(symbolsToRemove->containsObject(searchedSymbol))) this->searchPatternHorizontalForSymbol(searchedSymbol);
        }
    }
    
    ///vertical patterns
    for (int i = 0; i < gameSettings->getGameRows(); i++) {
        CCArray* temp;
        temp = (CCArray*)gameGrid->objectAtIndex(i);
        for (int j = 0; j < gameSettings->getGameRows() - 2; j++) {
            SyntaxSymbol *searchedSymbol = (SyntaxSymbol*) temp->objectAtIndex(j);
            if (searchedSymbol->isOfType < 7) if (!(symbolsToRemove->containsObject(searchedSymbol))) this->searchPatternVerticalForSymbol(searchedSymbol);
        }
    }
    
    if (symbolsToRemove->count() > 0) {
        isMoveValid = true;
        if ((isDoubleMatch) && (symbolsToRemove->count() > 5)) noOfDoubleMatches++;
        this->eraseSymbols();
    }
    else {
        isCascading = false;
        noOfCascadingMatches = 0;
        this->checkScore();
        checkForInfoPopUps();
        canTouch = true;
        this->setTouchEnabled(true);
        
 
        
    }
    isDoubleMatch = false;
}

void GameEngine::searchPatternTShapeForSymbol(SyntaxSymbol *thisSymbol){
    
}

void GameEngine::searchPatternLShapeForSymbol(SyntaxSymbol *thisSymbol){
    int x = thisSymbol->isIndex.x;
    int y = thisSymbol->isIndex.y;
    bool hasHorizontal = false;
    bool hasVertical = false;
    
    if (x > 1) {
        CCArray* temp;
        temp = (CCArray*)gameGrid->objectAtIndex(x-1);
        SyntaxSymbol *nextSymbol = (SyntaxSymbol*) temp->objectAtIndex(y); 
        if (thisSymbol->isOfType == nextSymbol->isOfType) {
            temp = (CCArray*)gameGrid->objectAtIndex(x-2);
            nextSymbol = (SyntaxSymbol*)temp->objectAtIndex(y);
            if (thisSymbol->isOfType == nextSymbol->isOfType) hasHorizontal = true;
                }
    }
    if (x < gameSettings->getGameRows() - 2) {
        CCArray* temp;
        temp = (CCArray*)gameGrid->objectAtIndex(x+1);
        SyntaxSymbol *nextSymbol = (SyntaxSymbol*) temp->objectAtIndex(y);
        if (thisSymbol->isOfType == nextSymbol->isOfType) {
            temp = (CCArray*)gameGrid->objectAtIndex(x+2);
            nextSymbol = (SyntaxSymbol*)temp->objectAtIndex(y);
             
            if (thisSymbol->isOfType == nextSymbol->isOfType) hasHorizontal = true;
                }
    }
    if (y > 1) {
        CCArray* temp;
        temp = (CCArray*)gameGrid->objectAtIndex(x);
        SyntaxSymbol *nextSymbol = (SyntaxSymbol*) temp->objectAtIndex(y-1);
        if (thisSymbol->isOfType == nextSymbol->isOfType) {
            temp = (CCArray*)gameGrid->objectAtIndex(x);
            nextSymbol = (SyntaxSymbol*)temp->objectAtIndex(y-2);
            if (thisSymbol->isOfType == nextSymbol->isOfType) hasVertical = true;
                }
    }
    if (y < gameSettings->getGameRows() - 2) {
        CCArray* temp;
        temp = (CCArray*)gameGrid->objectAtIndex(x);
        SyntaxSymbol *nextSymbol = (SyntaxSymbol*) temp->objectAtIndex(y+1);
        
        if (thisSymbol->isOfType == nextSymbol->isOfType) {
            temp = (CCArray*)gameGrid->objectAtIndex(x);
            nextSymbol = (SyntaxSymbol*)temp->objectAtIndex(y+2);
            if (thisSymbol->isOfType == nextSymbol->isOfType) hasVertical = true;
            
        }
        
       
    }
    
    if (hasHorizontal && hasVertical) {
        thisSymbol->isLShapeCorner = true;
        noOfLShapedMatches++;
        this->eliminateAllSymbolsInLineWithSymbolAtIndex(thisSymbol->isIndex);
    }
}

void GameEngine::searchPatternHorizontalForSymbol(SyntaxSymbol* thisSymbol){
    
    int x = thisSymbol->isIndex.x + 1;
    int y = thisSymbol->isIndex.y;
    int matched = 1;
    bool canBreak = false;
    bool canEliminateNeighbours = false;
    
    if (thisSymbol->isExplosive) canEliminateNeighbours = true;
        
        while (x < gameSettings->getGameRows()) {
            CCArray* temp;
            temp = (CCArray*)gameGrid->objectAtIndex(x);
            SyntaxSymbol *nextSymbol = (SyntaxSymbol*) temp->objectAtIndex(y);
             
            if (thisSymbol->isOfType == nextSymbol->isOfType) {
                matched++;
                if (nextSymbol->isExplosive) canEliminateNeighbours = true;
                    }
            else canBreak = true;
                x++;
            if (canBreak) break;
        }
    
    x = thisSymbol->isIndex.x;
    switch (matched) {
        case 5:
            noOfMatchesOf5++;
            for (int i = 0; i < matched; i++) {
                CCArray* temp;
                temp = (CCArray*)gameGrid->objectAtIndex(thisSymbol->isIndex.x + i);
                SyntaxSymbol *symbolToAdd = (SyntaxSymbol*) temp->objectAtIndex(thisSymbol->isIndex.y);
                if (i == 0) {
                    symbolsToSkip->addObject(symbolToAdd);
                    symbolManager->turnToSuperSymbol(symbolToAdd);
                }
                else {
                    if (!(symbolsToRemove->containsObject(symbolToAdd))) symbolsToRemove->addObject(symbolToAdd);
                }
            }
            break;
        case 4:
            noOfMatchesOf4++;
            for (int i = 0; i < matched; i++) {
                CCArray* temp;
                temp = (CCArray*)gameGrid->objectAtIndex(thisSymbol->isIndex.x + i);
                SyntaxSymbol *symbolToAdd = (SyntaxSymbol*) temp->objectAtIndex(thisSymbol->isIndex.y);
                if (i == 0) {
                    symbolsToSkip->addObject(symbolToAdd);
                    symbolManager->turnToExplosiveSymbol(symbolToAdd);
                }
                else {
                    if (!(symbolsToRemove->containsObject(symbolToAdd))) symbolsToRemove->addObject(symbolToAdd);
                }
            }
            break;
        case 3:
            noOfNormalMatches++;
            for (int i = 0; i < matched; i++) {
                CCArray* temp;
                temp = (CCArray*)gameGrid->objectAtIndex(thisSymbol->isIndex.x + i);
                SyntaxSymbol *symbolToAdd = (SyntaxSymbol*) temp->objectAtIndex(thisSymbol->isIndex.y);
                 
                if (!(symbolsToRemove->containsObject(symbolToAdd))) symbolsToRemove->addObject(symbolToAdd);
            }
            break;
        default:
            break;
    }
    if (canEliminateNeighbours && (matched > 2)) {
        noOfMatchesOf4Explosion++;
        for (int i = 0; i < matched; i++) {
            CCArray* temp;
            temp = (CCArray*)gameGrid->objectAtIndex(thisSymbol->isIndex.x + i);
            SyntaxSymbol *symbolToCheck = (SyntaxSymbol*) temp->objectAtIndex(thisSymbol->isIndex.y);
            symbolToCheck->isToExplode = true;
           this->eliminateNeightboursOfSymbolAtIndex(symbolToCheck->isIndex);
        }
        isShockwave = true;
        shockwaveCentre = CCPointMake(x, y);
    }
}

void GameEngine::searchPatternVerticalForSymbol(SyntaxSymbol *thisSymbol){
    int x = thisSymbol->isIndex.x;
    int y = thisSymbol->isIndex.y + 1;
    int matched = 1;
    bool canBreak = false;
    bool canEliminateNeighbours = false;
    
    if (thisSymbol->isExplosive) canEliminateNeighbours = true;
        
        while (y < gameSettings->getGameRows()) {
            CCArray* temp;
            temp = (CCArray*)gameGrid->objectAtIndex(thisSymbol->isIndex.x);
            SyntaxSymbol *nextSymbol = (SyntaxSymbol*) temp->objectAtIndex(y);
            if (thisSymbol->isOfType == nextSymbol->isOfType) {
                matched++;
                if (nextSymbol->isExplosive) canEliminateNeighbours = true;
                    }
            else canBreak = true;
                y++;
            if (canBreak) break;
        }
    
    y = thisSymbol->isIndex.y;
    switch (matched) {
        case 5:
            noOfMatchesOf5++;
            for (int j = 0; j < matched; j++) {
                CCArray* temp;
                temp = (CCArray*)gameGrid->objectAtIndex(thisSymbol->isIndex.x);
                SyntaxSymbol *symbolToAdd = (SyntaxSymbol*) temp->objectAtIndex(thisSymbol->isIndex.y + j);
                if (j == 0) {
                    symbolsToSkip->addObject(symbolToAdd);
                    symbolManager->turnToSuperSymbol(symbolToAdd);
                }
                else {
                    if (!(symbolsToRemove->containsObject(symbolToAdd))) symbolsToRemove->addObject(symbolToAdd);
                }
            }
            break;
        case 4:
            noOfMatchesOf4++;
            for (int j = 0; j < matched; j++) {
                CCArray* temp;
                temp = (CCArray*)gameGrid->objectAtIndex(thisSymbol->isIndex.x);
                SyntaxSymbol *symbolToAdd = (SyntaxSymbol*) temp->objectAtIndex(thisSymbol->isIndex.y + j);
                
                if (j == 0) {
                    symbolsToSkip->addObject(symbolToAdd);
                    symbolManager->turnToExplosiveSymbol(symbolToAdd);

                    
                }
                else {
                    if (!(symbolsToRemove->containsObject(symbolToAdd))) symbolsToRemove->addObject(symbolToAdd);
                }
            }
            break;
        case 3:
            noOfNormalMatches++;
            for (int j = 0; j < matched; j++) {
                CCArray* temp;
                temp = (CCArray*)gameGrid->objectAtIndex(thisSymbol->isIndex.x);
                SyntaxSymbol *symbolToAdd = (SyntaxSymbol*) temp->objectAtIndex(thisSymbol->isIndex.y + j);
                
                if (!(symbolsToRemove->containsObject(symbolToAdd))) symbolsToRemove->addObject(symbolToAdd);
            }
            break;
        default:
            break;
    }
    if (canEliminateNeighbours && (matched > 2)) {
        noOfMatchesOf4Explosion++;
        for (int j = 0; j < matched; j++) {
            CCArray* temp;
            temp = (CCArray*)gameGrid->objectAtIndex(thisSymbol->isIndex.x);
            SyntaxSymbol *symbolToCheck = (SyntaxSymbol*) temp->objectAtIndex(thisSymbol->isIndex.y + j);
            symbolToCheck->isToExplode = true;
            this->eliminateNeightboursOfSymbolAtIndex(symbolToCheck->isIndex);
        }
        isShockwave = true;
        shockwaveCentre =CCPointMake(x, y);
    }
}

 
#pragma mark - HINT SYSTEM 
//\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\

bool GameEngine::didFindHint() {
    CCPoint hintPos = this->getHint();
    if (hintPos.x > -1) {
        CCArray* temp ;
        temp = (CCArray*)gameGrid->objectAtIndex(hintPos.x);
        SyntaxSymbol *hintSymbol = (SyntaxSymbol*) temp->objectAtIndex(hintPos.y);
        HintAction(hintSymbol);
        return  true;
    }
    else return false;
}

void GameEngine::HintAction(SyntaxSymbol *hintSymbol){
  
    if (box) {
        box->setPosition(hintSymbol->getPosition());
        box->runAction(CCSequence::create(CCBlink::create(0.5f, 3) , CCDelayTime::create(0.0f) ,CCCallFunc::create(this, callfunc_selector(GameEngine::stopHitAction)) , NULL));
    }
    
}
void GameEngine:: stopHitAction(cocos2d::CCObject *pSender){
    if (box->isVisible()) {
        box->setVisible(false);
    }
}
bool GameEngine:: getHintExceptThis(CCPoint lastPoint) { // to recognize last move TODO - absorb with next method
    bool possiblePatternFount = false;
    bool foundSpecialSymbol = false;
    CCPoint hint = CCPointMake(-1, -1);
    CCPoint specialPos = CCPointMake(-1, -1);
    hintGrid = gameGrid;
    for (int i = 0; i < gameSettings->getGameRows(); i++) {
        CCArray* temp;
        temp = (CCArray*)hintGrid->objectAtIndex(i);
        for (int j = 0; j < gameSettings->getGameRows(); j++) {
            if (!possiblePatternFount && ! ((lastPoint.x == i)&&(lastPoint.y == j)) /*CCPointEqualToPoint(lastPoint, CCPointMake(i, j))*/) {
                SyntaxSymbol *symbolToTest = (SyntaxSymbol*) temp->objectAtIndex(j);
//                SyntaxSymbol *symbolToTest = [[[hintGrid objectAtIndex:i] objectAtIndex:j] retain];
                if ((symbolToTest->isOfType == 7) | (symbolToTest->isOfType == 11) | (symbolToTest->isOfType == 10)) {
                    foundSpecialSymbol = true;
                    specialPos = CCPointMake(i, j);
                }
                else {
                    if (i > 0) {
                        this->moveSymbol(symbolToTest ,CCPointMake(-1, 0));
                        possiblePatternFount = this->possiblePatternFoundForSymbol(symbolToTest);
                        this->moveSymbol(symbolToTest,CCPointMake(1, 0));
                        if (possiblePatternFount) hint = CCPointMake(i, j);
                            }
                    if (i < 7) {
                        this->moveSymbol(symbolToTest,CCPointMake(1, 0));
                        possiblePatternFount = this->possiblePatternFoundForSymbol(symbolToTest);
                        this->moveSymbol(symbolToTest ,CCPointMake(-1, 0));
                        if (possiblePatternFount) hint = CCPointMake(i, j);
                            }
                    if (j > 0) {
                        this->moveSymbol(symbolToTest,CCPointMake(0, -1));
                        possiblePatternFount = this->possiblePatternFoundForSymbol(symbolToTest);
                        this->moveSymbol(symbolToTest ,CCPointMake(0, 1));
                        if (possiblePatternFount) hint = CCPointMake(i, j);
                            }
                    if (j < 7) {
                        this->moveSymbol(symbolToTest,CCPointMake(0, 1));
                        possiblePatternFount = this->possiblePatternFoundForSymbol(symbolToTest);
                        this->moveSymbol(symbolToTest ,CCPointMake(0, -1));
                        if (possiblePatternFount) hint = CCPointMake(i, j);
                            }
                }
                symbolToTest->release();
            }
        }
    }
    hintGrid->release();
    if (possiblePatternFount || !((hint.x == -1)&&(hint.y == -1))/*CGPointEqualToPoint(hint, CGPointMake(-1, -1))*/) return true;
    else if (foundSpecialSymbol) return true;
    else return false;
}

CCPoint GameEngine:: getHint() {
    bool possiblePatternFount = false;
    bool foundSpecialSymbol = false;
    CCPoint hint = CCPointMake(-1, -1);
    CCPoint specialPos = CCPointMake(-1, -1);
    hintGrid = gameGrid;
    for (int i = 0; i < gameSettings->getGameRows(); i++) {
        CCArray* temp;
        temp = (CCArray*)hintGrid->objectAtIndex(i);

        for (int j = 0; j < gameSettings->getGameRows(); j++) {
            if (!possiblePatternFount) {
                SyntaxSymbol *symbolToTest = (SyntaxSymbol*) temp->objectAtIndex(j);
//                SyntaxSymbol *symbolToTest = [[[hintGrid objectAtIndex:i] objectAtIndex:j] retain];
                if ((symbolToTest->isOfType == 7) || (symbolToTest->isOfType == 11) || (symbolToTest->isOfType == 10)) {
                    foundSpecialSymbol = true;
                    specialPos = CCPointMake(i, j);
                }
                else {
                    if (i > 0) {
                        this->moveSymbol(symbolToTest ,CCPointMake(-1, 0));
                        possiblePatternFount = this->possiblePatternFoundForSymbol(symbolToTest);
                        this->moveSymbol(symbolToTest ,CCPointMake(1, 0));
                        if (possiblePatternFount) hint = CCPointMake(i, j);
                            }
                    if (i < 7) {
                        this->moveSymbol(symbolToTest ,CCPointMake(1, 0));
                        possiblePatternFount = this->possiblePatternFoundForSymbol(symbolToTest);
                        this->moveSymbol(symbolToTest ,CCPointMake(-1, 0));

                        if (possiblePatternFount) hint = CCPointMake(i, j);
                            }
                    if (j > 0) {
                        this->moveSymbol(symbolToTest ,CCPointMake(0, -1));
                        possiblePatternFount = this->possiblePatternFoundForSymbol(symbolToTest);
                        this->moveSymbol(symbolToTest ,CCPointMake(0, 1));

                        if (possiblePatternFount) hint = CCPointMake(i, j);
                            }
                    if (j < 7) {
                        this->moveSymbol(symbolToTest ,CCPointMake(0, 1));
                        possiblePatternFount = this->possiblePatternFoundForSymbol(symbolToTest);
                        this->moveSymbol(symbolToTest ,CCPointMake(0, -1));
                        if (possiblePatternFount) hint = CCPointMake(i, j);
                            }
                }
//                symbolToTest->release();
            }
        }
    }
//    hintGrid->release();
    
    if (possiblePatternFount) return hint;
    else if (foundSpecialSymbol) return specialPos;
    else return hint;
}


void GameEngine::moveSymbol(SyntaxSymbol *thisSymbol,CCPoint thisDirection) {
  
    CCPoint thisIndex = thisSymbol->isIndex;
    SyntaxSymbol *firstSymbol = thisSymbol;
    CCArray* temp_a;
    temp_a = (CCArray*) hintGrid->objectAtIndex(thisIndex.x+thisDirection.x);
    SyntaxSymbol *secondSymbol = (SyntaxSymbol*) temp_a->objectAtIndex(thisIndex.y + thisDirection.y); //[[hintGrid objectAtIndex:thisIndex.x + thisDirection.x] objectAtIndex:thisIndex.y + thisDirection.y];
    
    CCArray *firstSymbolRow = (CCArray*)hintGrid->objectAtIndex(firstSymbol->isIndex.x);
    CCArray *secondSymbolRow = (CCArray*)hintGrid->objectAtIndex(secondSymbol->isIndex.x);
    
    firstSymbolRow->replaceObjectAtIndex(firstSymbol->isIndex.y ,secondSymbol);
    secondSymbolRow->replaceObjectAtIndex(secondSymbol->isIndex.y ,firstSymbol);
    
    CCPoint temp = firstSymbol->isIndex;
    firstSymbol->isIndex = secondSymbol->isIndex;
    secondSymbol->isIndex = temp;
}

bool GameEngine:: possiblePatternFoundForSymbol(SyntaxSymbol *thisSymbol) {
  
    if (thisSymbol->isOfType == 9) return false;
    CCPoint thisIndex = thisSymbol->isIndex;
    bool canBreak = false;
    int x = thisIndex.x;
    int y = thisIndex.y;
    int matchL = 0;
    int matchR = 0;
    int matchD = 0;
    int matchU = 0;
    
    int matchH;
    int matchV;
    
    while (x > 0) {
        CCArray* temp;
        temp = (CCArray*) hintGrid->objectAtIndex(x-1);
        SyntaxSymbol *nextSymbol = (SyntaxSymbol*)temp->objectAtIndex(y); //[[hintGrid objectAtIndex:x - 1] objectAtIndex:y];
        if (thisSymbol->isOfType == nextSymbol->isOfType) {
            matchL++;
        }
        else canBreak = true;
            x--;
        if (canBreak) break;
    }
    canBreak = false;
    x = thisIndex.x;
    
    while (x < 7) {
        CCArray* temp;
        temp = (CCArray*) hintGrid->objectAtIndex(x+1);
        SyntaxSymbol *nextSymbol = (SyntaxSymbol*)temp->objectAtIndex(y);
//        SyntaxSymbol *nextSymbol = [[hintGrid objectAtIndex:x + 1] objectAtIndex:y];
        if (thisSymbol->isOfType == nextSymbol->isOfType) {
            matchR++;
        }
        else canBreak = true;
            x++;
        if (canBreak) break;
    }
    canBreak = false;
    x = thisIndex.x;
    
    while (y > 0) {
        CCArray* temp;
        temp = (CCArray*) hintGrid->objectAtIndex(x);
        SyntaxSymbol *nextSymbol = (SyntaxSymbol*)temp->objectAtIndex(y-1);
 
        if (thisSymbol->isOfType == nextSymbol->isOfType) {
            matchD++;
        }
        else canBreak = true;
            y--;
        if (canBreak) break;
    }
    canBreak = false;
    y = thisIndex.y;
    
    while (y < 7) {
        CCArray* temp;
        temp = (CCArray*) hintGrid->objectAtIndex(x);
        SyntaxSymbol *nextSymbol = (SyntaxSymbol*)temp->objectAtIndex(y+1);
 
        if (thisSymbol->isOfType == nextSymbol->isOfType) {
            matchU++;
        }
        else canBreak = true;
            y++;
        if (canBreak) break;
    }
    
    matchH = matchL + matchR + 1;
    matchV = matchD + matchU + 1;
    
    if ((matchH > 2) || (matchV > 2)) return true;
    else return false;
}

 
 
#pragma mark - ANIMATIONS AND OTHERS 
//\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\

CCPoint GameEngine::CCPointFromIndex(CCPoint thisIndex) {
    
    float xOffset = (size.width - gameSettings->getGameRows() * 70 + symbol_w)/2 ;
    float yOffset = (size.height - gameSettings->getGameRows() * 70 + symbol_h)/2;
    return CCPointMake((xOffset + thisIndex.x * 70)*dScaleFactorX, (yOffset + thisIndex.y * 70)*dSclaeFactorY);
}

void GameEngine::glitch() {
   
    SyntaxSymbol *symbolToGlitch;
    float delay;
    for (int i = 0; i < gameSettings->getGameRows(); i++) {
        CCArray* temp;
        temp = (CCArray*) gameGrid->objectAtIndex(i);
        
        for (int j = 0; j < gameSettings->getGameRows(); j++) {
            symbolToGlitch = (SyntaxSymbol*)temp->objectAtIndex(j);
            delay = sqrtf(i*i + j*j) / 15;
            symbolManager->animGlitchSymbol(symbolToGlitch,delay);
        }
    }
}

void GameEngine::shockWaveFromCenter(CCPoint thisCenter) {
    
    isShockwave = false;
    SyntaxSymbol *symbolToGlitch;
    float delay;
    float m = thisCenter.x;
    float n = thisCenter.y;
    
    for (int i = 0; i < gameSettings->getGameRows(); i++) {
        CCArray* temp;
        temp = (CCArray*) gameGrid->objectAtIndex(i);
        for (int j = 0; j < gameSettings->getGameRows(); j++) {
            symbolToGlitch = (SyntaxSymbol*)temp->objectAtIndex(j);
            if (!(symbolsToRemove->containsObject(symbolToGlitch))) {
                delay = sqrtf((i - m)*(i - m) + (j - n)*(j - n)) / 15;
                symbolManager->animGlitchSymbol(symbolToGlitch,delay);
            }
        }
    }
}

void GameEngine:: clearPoints(){
    noOfNormalMatches = 0;
    noOfDoubleMatches = 0;
    noOfShifterMatches = 0;
    noOfMatchesOf4 = 0;
    noOfMatchesOf4Explosion = 0;
    noOfMatchesOf5 = 0;
    noOfSuperEliminated = 0;
    noOfLShapedMatches = 0;
    noOfCorruptedCleared = 0;
}

void GameEngine::checkScore(){
    
    if(gameScene->m_nGameScore >= gameScene->m_nPointsNeedForLevel){
        this->stopAllActions();
        this->unscheduleAllSelectors();
        levelCompleted = true;
        gameScene->showLevelCompleted();
        return;
    }
    else {
//        CCPoint hint = this->getHint();
//        if(! getHintExceptThis(hint))
////            [[NSNotificationCenter defaultCenter] postNotificationName:@"lastMove" object:nil];
//        if ((hint.x < 0) /*&& (viewController.byteManager.wildcards == 0)*/) {
//            gameScene->showGameOver();
//            canShowStuck = false;
//        }
    }
}

void GameEngine::resetGame(){

    for (int i = 0; i < gameSettings->getGameRows(); i++) {
        CCArray* temp;
        temp = (CCArray*) gameGrid->objectAtIndex(i);

        for (int j = 0; j < gameSettings->getGameRows(); j++) {
            SyntaxSymbol *symbol = (SyntaxSymbol*)temp->objectAtIndex(j);
            symbolManager->animHideSymbol(symbol ,0);
        }
        temp->removeAllObjects();
    }
    if (firstTouchedSymbol != NULL) firstTouchedSymbol->release();
    
    this->setTouchEnabled(false);
         
    if (symbolsToRemove) {
        symbolsToRemove->removeAllObjects();
        symbolsToRemove->release();
    }
    
    if (symbolsToMove) {
        symbolsToMove->removeAllObjects();
        symbolsToMove->release();
    }
    if (symbolsToSkip) {
        symbolsToSkip->removeAllObjects();
        symbolsToSkip->release();
    }
    
    if (gameGrid) {
        gameGrid->removeAllObjects();
        gameGrid->release();
    }
    
    if (popBack) {
        popBack->removeAllObjects();
        popBack->release();
    }
    if (popTitle) {
        popTitle->removeAllObjects();
        popTitle->release();
    }

    if (popDescription) {
        popDescription->removeAllObjects();
        popDescription->release();
    }

     if (allPopUps) {
        allPopUps->removeAllObjects();
        allPopUps->release();
    }
    
    if (symbolManager) {
        symbolManager = NULL;
//        symbolManager->release();
    }

    this->unscheduleAllSelectors();
    this->removeAllChildren();
    this->stopAllActions();
    this->initGame();

}

void GameEngine::clearGame(){
    for (int i = 0; i < gameSettings->getGameRows(); i++) {
        CCArray* temp ;
        temp = (CCArray*) gameGrid->objectAtIndex(i);
        for (int j = 0; j < gameSettings->getGameRows(); j++) {
            SyntaxSymbol *symbol = (SyntaxSymbol*)temp->objectAtIndex(j);
            symbolManager->animHideSymbol(symbol,(float)((arc4random() % 100) / 100.0));
        }
    }
    symbolsToRemove->removeAllObjects();
    symbolsToSkip->removeAllObjects();
    symbolsToMove->removeAllObjects();
}

////////////////
//////////////////////////////////////////////////---> Input & App Specific <---///////////////////////////////////////////////////
///////////////

void GameEngine::ccTouchesBegan(CCSet* touches,CCEvent* event) {
    
    CCTouch *touch =(CCTouch*)(touches->anyObject());
	CCPoint touchPos = touch->getLocationInView();
	touchPos = CCDirector::sharedDirector()->convertToGL(touchPos);
    refreshStuckTimer();
   
 
    if (popBack->count() > 0) {
        for (int i = 0; i < popBack->count(); i++) {
            CCSprite* back = (CCSprite*) popBack->objectAtIndex(i);
            CCRect rect = CCRectMake(back->getPosition().x - back->getContentSize().width*dScaleFactorX / 2 ,
                                     back->getPosition().y - back->getContentSize().height*dSclaeFactorY / 2,
                                     back->getContentSize().width*dScaleFactorX,
                                     back->getContentSize().height*dSclaeFactorY);
            if (rect.containsPoint(touchPos)) {
                CCLabelTTF* t = (CCLabelTTF*) popTitle->objectAtIndex(i);
                CCLabelTTF* d = (CCLabelTTF*) popDescription->objectAtIndex(i);
                
                back->removeFromParentAndCleanup(true);
                t->removeFromParentAndCleanup(true);
                d->removeFromParentAndCleanup(true);
                popBack->removeObjectAtIndex(i);
                popTitle->removeObjectAtIndex(i);
                popDescription->removeObjectAtIndex(i);
               
            }
        }
       
        return;
    }
    
    if (levelCompleted) {
        return;
    }
    
    for (int i = 0; i < gameSettings->getGameRows(); i++) {
        CCArray* temp;
        temp = (CCArray*) gameGrid->objectAtIndex(i);
        for (int j = 0; j < gameSettings->getGameRows(); j++) {
            SyntaxSymbol *symbol = (SyntaxSymbol*)temp->objectAtIndex(j);
            CCRect rect = CCRectMake(symbol->getPosition().x - symbol->getContentSize().width*dScaleFactorX / 2 ,
                                     symbol->getPosition().y - symbol->getContentSize().height*dSclaeFactorY / 2,
                                     symbol->getContentSize().width*dScaleFactorX,
                                     symbol->getContentSize().height*dSclaeFactorY);
            if (rect.containsPoint(touchPos)) {
   
                this->selectSymbol(symbol);
            }
             
        }
    }

    
   

}

void GameEngine::ccTouchesMoved(CCSet* touches,CCEvent* event) {
    
    if (firstTouchedSymbol == NULL)
         return;

    
    CCTouch *touch =(CCTouch*)(touches->anyObject());
	CCPoint touchPos = touch->getLocationInView();
	touchPos = CCDirector::sharedDirector()->convertToGL(touchPos);
    for (int i = 0; i < gameSettings->getGameRows(); i++) {
        CCArray* temp  ;
        CCArray* temp_1  ;
        temp = (CCArray*) gameGrid->objectAtIndex(i);
        for (int j = 0; j < gameSettings->getGameRows(); j++) {
            SyntaxSymbol *thisSymbol = (SyntaxSymbol*)temp->objectAtIndex(j);
            if (thisSymbol == firstTouchedSymbol) {
                
                float dx = thisSymbol->getPosition().x - touchPos.x;
                float dy = thisSymbol->getPosition().y - touchPos.y;
                
                if ((abs(dx) > 50*dScaleFactorX) || (abs(dy) > 50*dSclaeFactorY)) {
                
                    CCPoint direction;
                    if (abs(dx) > abs(dy)) {
                        if (dx > 0) direction = CCPointMake(-1, 0);
                        else direction = CCPointMake(1, 0);
                        }
                    else {
                        if (dy > 0) direction = CCPointMake(0, -1);
                        else direction = CCPointMake(0, 1);
                    }
                  
                    CCPoint posibleIndex = CCPointMake(thisSymbol->isIndex.x + direction.x, thisSymbol->isIndex.y + direction.y);
                    if ((posibleIndex.x > -1) && (posibleIndex.x < gameSettings->getGameRows()) && (posibleIndex.y > -1) && (posibleIndex.y < gameSettings->getGameRows())) {
                        temp_1 = (CCArray*)gameGrid->objectAtIndex(posibleIndex.x);
                        SyntaxSymbol *otherSymbol =(SyntaxSymbol*)temp_1->objectAtIndex(posibleIndex.y);
                        if (this->symbol(thisSymbol->isIndex,otherSymbol->isIndex)) {
                            this->swapSymbol(thisSymbol,otherSymbol);
                            removeBox(thisSymbol);
                        }
                    }
                }
        
            }
        }
    }
    
}
void GameEngine::registerWithTouchDispatcher()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addStandardDelegate(this,0);
}
void GameEngine::checkForInfoPopUps(){
    
     for (int i = 0; i < gameSettings->getGameRows(); i++) {
        CCArray* temp = (CCArray*) gameGrid->objectAtIndex(i);
        for (int j = 0; j < gameSettings->getGameRows(); j++) {
            SyntaxSymbol *thisSymbol =(SyntaxSymbol*)temp->objectAtIndex(j);
            if ((thisSymbol->isOfType > 6) || (thisSymbol->isShifter)) {
            int k = -1;
            if (thisSymbol->isOfType == 3) k = 0;
            else if (thisSymbol->isShifter) k = 1;
            else if (thisSymbol->isOfType == 9) k = 2;
            else if (thisSymbol->isOfType == 10) k = 3;
            
                if ((k > -1) && (!gameScene->statusManager->didSeePopUpForSpecialType(k))) {
                    makePopUp(thisSymbol->getPosition(), k);
                
                }
            }
        }
    }
}

void GameEngine:: clearInfoPopUps(){
    
    if (popBack->count() > 0) {
        for (int i = 0; i < popBack->count(); i++) {
            CCSprite* b = (CCSprite*) popBack->objectAtIndex(i);
            CCLabelTTF* t = (CCLabelTTF*) popTitle->objectAtIndex(i);
            CCLabelTTF* d = (CCLabelTTF*) popDescription->objectAtIndex(i);
            b->removeFromParent();
            t->removeFromParent();
            d->removeFromParent();
            
        }
        popBack->removeAllObjects();
        popTitle->removeAllObjects();
        popDescription->removeAllObjects();
    }
    
}

void GameEngine:: makePopUp(cocos2d::CCPoint nPos, int nType){
    
    int margin;
    char file_title[0x80]={0};
    char file_description[0x90] = {0};
    switch (nType) {
        case 0:
            sprintf(file_title, "Raffle ticket:");
            sprintf(file_description, "Tap the symbol then tap any \nsneaker to change the \nraffle ticket into that sneaker.");
            break;
        case 1:
            sprintf(file_title, "OG kicks :");
            sprintf(file_description, "This sneaky symbol changes \nto a new sneaker \nevery time you make a move.");
            break;
        case 2:
            sprintf(file_title, "Hypebeast:");
            sprintf(file_description, "hypebeast john is wild! Get \nrid of him with \nthe Magic shoe box or beast Traps!");
            break;
        case 3:
            sprintf(file_title, "Shoe Store:");
            sprintf(file_description, "Tap to see what sneaker is \nhiding. But watch out \nfor Hypebeast John!");
            
        default:
            break;
    }
    
    background = CCSprite::create("infoPopUp@2x.png");
    background->setScaleX(background->getScaleX()*dScaleFactorX);
    background->setScaleY(background->getScaleY()*dSclaeFactorY);
    
    gameScene->addChild(background , 10);
    
    if (nPos.x < size.width / 2) {
        background->setPosition(ccp(nPos.x + 150*dScaleFactorX , nPos.y));
        margin = 10*dScaleFactorX;
    }
    else {
        
        background->setPosition(ccp(nPos.x - 150*dScaleFactorX , nPos.y));
        background->setRotation(180);
        margin = -10*dScaleFactorX;
        
    }
    
    
    ccColor3B strokeColor                   =  { 255, 255, 255 };
    ccFontDefinition strokeTextDef;
    strokeTextDef.m_fontSize                = 40*dScaleFactorX;
    strokeTextDef.m_fontName                = std::string("Dimbo Regular");
    strokeTextDef.m_stroke.m_strokeColor    = strokeColor;
    strokeTextDef.m_stroke.m_strokeEnabled  = true;
    strokeTextDef.m_stroke.m_strokeSize     = 2.0f;
    
    
    m_lTitle = CCLabelTTF::createWithFontDefinition(file_title, strokeTextDef);
    m_lTitle->setPosition(ccp(background->getPosition().x , background->getPosition().y + 40*dSclaeFactorY));
    m_lTitle->setScaleY(1.0f*dSclaeFactorY);
    m_lTitle->setScaleX(0.8f*dScaleFactorX);
    gameScene->addChild(m_lTitle , 10);
    
    
    ccFontDefinition strokeTextDef1;
    strokeTextDef1.m_fontSize                = 40*dSclaeFactorY;
    strokeTextDef1.m_fontName                = std::string("Dimbo Regular");
    strokeTextDef1.m_stroke.m_strokeColor    = strokeColor;
    strokeTextDef1.m_stroke.m_strokeEnabled  = true;
    strokeTextDef1.m_stroke.m_strokeSize     = 1.0f;
    
    
    m_lDescription = CCLabelTTF::createWithFontDefinition(file_description, strokeTextDef);
    m_lDescription->setPosition(ccp(background->getPosition().x+margin*dSclaeFactorY ,background->getPosition().y-20*dSclaeFactorY));
    m_lDescription->setScaleY(0.55f*dSclaeFactorY);
    m_lDescription->setScaleX(0.55f*dScaleFactorX);
    gameScene->addChild(m_lDescription , 10);
    
    popBack->addObject(background);
    popTitle->addObject(m_lTitle);
    popDescription->addObject(m_lDescription);

}



