//
//  SymbolManager.cpp
//  VivaStampede
//
//  Created by Mikhail Berrya on 11/25/13.
//
//

#include "SymbolManager.h"
#include "SyntaxSymbol.h"
#include "StatusManager.h"
#include "GameSetting.h"
#include "GameEngineLayer.h"
#include "ValuesManager.h"

SymbolManager* SymbolManager::sharedSymbolManager(){
    
    static SymbolManager* temp = NULL;
    if (temp == NULL) {
        temp = new SymbolManager();
    }
    
    return temp;
}
SyntaxSymbol* SymbolManager::randomSymbolWithMaxType(int maxTypes) {
    
    SyntaxSymbol *newSymbol = SyntaxSymbol::body();
    size = CCDirector::sharedDirector()->getWinSize();
    dScaleX = size.width / 640,dScaleY = size.height / 1024;
   
    newSymbol->setScaleX(newSymbol->getScaleX()*dScaleX);
    newSymbol->setScaleY(newSymbol->getScaleY()*dScaleY);
    
    int k = arc4random() % 4;
    int i = 0;
    int l = 0;
    
//    switch (k) {
//        case 0:
//            
//            if (wildcardProbability != 0) {
//                l = arc4random() % wildcardProbability;
//            }else{
//                l = arc4random();
//            }
//            
//            if (l == 0) i = 7;
//            else i = arc4random() % maxTypes;
//            break;
//        case 1:
//            
//            if (shifterProbability != 0) {
//                l = arc4random() % shifterProbability;
//            }else{
//                l = arc4random();
//            }
//            
//            if (l == 0) i = 8;
//            else i = arc4random() % maxTypes;
//            break;
//        case 2:
//            
//            if (corruptedProbability != 0) {
//                l = arc4random() % corruptedProbability;
//            }else{
//                l = arc4random();
//            }
//            
//            if (l == 0) i = 9;
//            else i = arc4random() % maxTypes;
//            break;
//        case 3:
//            
//            if (hiddenProbability != 0) {
//                l = arc4random() % hiddenProbability;
//            }else{
//                l = arc4random();
//            }
//            
//            if (l == 0) i = 10;
//            else i = arc4random() % maxTypes;
//            break;
//        default:
//            break;
//    }
//    
//    if (i == 7) newSymbol->isKeepable = true;
//    CCLOG("type = %d", i);
//    if (i < 8) {
//        char file[0x50] = {0};
////        sprintf(file, "symbol%d@2x.png" , i);
//        
//        
//        
//        sprintf(file, "symbol%d-idle0@2x.png" , i);
//
//        newSymbol->initWithFile(file);
//        
//    }

    char file[0x50] = {0};
    
    i = arc4random() % maxTypes;
    sprintf(file, "symbol%d-idle0@2x.png" , i);
    newSymbol->initWithFile(file);

//    if (i == 8) {
//        newSymbol->isShifter = true;
//        i = arc4random() % 7;
//        char file[0x50] = {0};
//        sprintf(file, "symbol%d-shift@2x.png" , i);
//        newSymbol->initWithFile(file);
//    }
//    
//    if (i == 9) {
//        newSymbol->isKeepable = true;
//        newSymbol->initWithFile("symbol9@2x.png");
//        CCAnimation* temp = CCAnimation::create();
//        temp->addSpriteFrameWithFileName("symbol9@2x.png");
//        temp->addSpriteFrameWithFileName("symbol9b@2x.png");
//        temp->setLoops(-1);
//        temp->setDelayPerUnit(0.25f);
//        CCAnimate* ani = CCAnimate::create(temp);
//        newSymbol->runAction(ani);
//        animSuperSymbol(newSymbol);
//       
//        temp = NULL;
//        ani = NULL;
//    }
//    if (i == 10) {
//        newSymbol->isKeepable = true;
//        hiddenSymbolAnimationFrames = CCAnimation::create();
//        for (int i =1 ; i< 5; i++) {
//            char file[0x50] = {0};
//            sprintf(file, "symbol10-%d@2x.png" , i);
//            hiddenSymbolAnimationFrames->addSpriteFrameWithFileName(file);
//            hiddenSymbolAnimationFrames->setDelayPerUnit(0.1f);
//            hiddenSymbolAnimationFrames->setLoops(-1);
//            
//        }
//        CCAnimate* ani = CCAnimate::create(hiddenSymbolAnimationFrames);
//        newSymbol->runAction(ani);
//        ani = NULL;
//        
//    }
//    
    newSymbol->isOfType = i;
    return newSymbol;
//    SyntaxSymbol *newSymbol = SyntaxSymbol::body();
//    size = CCDirector::sharedDirector()->getWinSize();
//    dScaleX = size.width / 640,dScaleY = size.height / 1024;
//    
//    newSymbol->setScaleX(newSymbol->getScaleX()*dScaleX);
//    newSymbol->setScaleY(newSymbol->getScaleY()*dScaleY);
//    
//    int k = arc4random() % maxTypes;
//    CCLOG("randomSymbolWithMaxType maxTypes = %d, type = %d", maxTypes, k);
//    char file[0x50] = {0};
//    sprintf(file, "ball_0%d@2x.png" , k);
//    newSymbol->initWithFile(file);
//    newSymbol->isOfType = k;
//    return newSymbol;
}

SyntaxSymbol* SymbolManager::symbolWithType(int thisType) {
    CCLOG("symbolWithType type ==%d" , thisType);
    SyntaxSymbol *newSymbol = SyntaxSymbol::body();
    char file[0x50] ={0};
//    sprintf(file, "symbol%d@2x.png" , thisType);
    sprintf(file, "symbol%d-idle0@2x.png" , thisType);

     newSymbol->initWithFile(file);
     newSymbol->isOfType = thisType;
    return newSymbol;
}

SyntaxSymbol* SymbolManager::symbolWithIsOfType(int isOfType) {
    CCLOG("symbolWithIsOfType type ==%d" , isOfType);
    SyntaxSymbol *newSymbol = SyntaxSymbol::body();
    size = CCDirector::sharedDirector()->getWinSize();
    dScaleX = size.width / 640,dScaleY = size.height / 1024;
    newSymbol->setScaleX(newSymbol->getScaleX()*dScaleX);
    newSymbol->setScaleY(newSymbol->getScaleY()*dScaleY);

    int i = isOfType;
    
    if (i == 7) newSymbol->isKeepable = true;
    
    if (i < 8) {
        char file[0x50] = {0};
//        sprintf(file, "symbol%d@2x.png" , i);
        sprintf(file, "symbol%d-idle0@2x.png" , i);

        newSymbol->initWithFile(file);
    }
//    if (i == 8) {
//        newSymbol->isShifter = true;
//        i = arc4random() % 7;
//        newSymbol = SyntaxSymbol::body();
//        char file[0x50] = {0};
//        sprintf(file, "symbol%d-shift@2x.png" , i);
//        newSymbol->initWithFile(file);
//        newSymbol->runAction(CCBlink::create(1.0f, 5));
//
//        animShifterSymbol(newSymbol);
//    }
//    if (i == 9) {
//        newSymbol->isKeepable = true;
//        newSymbol->initWithFile("symbol9@2x.png");
//       
//        CCAnimation* temp = CCAnimation::create();
//        temp->addSpriteFrameWithFileName("symbol9@2x.png");
//        temp->addSpriteFrameWithFileName("symbol9b@2x.png");
//        temp->setLoops(-1);
//        temp->setDelayPerUnit(0.25f);
//       
//        CCAnimate* ani = CCAnimate::create(temp);
//        newSymbol->runAction(ani);
//       
//        animSuperSymbol(newSymbol);
//        
//        
//    }
//    if (i == 10) {
//        newSymbol->isKeepable = true;
//        hiddenSymbolAnimationFrames = CCAnimation::create();
//        for (int i =1 ; i< 5; i++) {
//            char file[0x50] = {0};
//            sprintf(file, "symbol10-%d@2x.png" , i);
//            hiddenSymbolAnimationFrames->addSpriteFrameWithFileName(file);
//            hiddenSymbolAnimationFrames->setDelayPerUnit(0.1f);
//            hiddenSymbolAnimationFrames->setLoops(-1);
//            
//        }
//
//        CCAnimate* ani = CCAnimate::create(hiddenSymbolAnimationFrames);
//        newSymbol->runAction(ani);
//        ani = NULL;
//    }
    
    
    newSymbol->isOfType = i;
    return newSymbol;
}

 
 
void SymbolManager:: turnToExplosiveSymbol(SyntaxSymbol* thisSymbol) {
    CCLOG("turnToExplosiveSymbol type ==%d" , thisSymbol->isOfType);
    
    if (thisSymbol->isShifter) {
        thisSymbol->isShifter = false;
        char file[0x50] = {0};
//        sprintf(file, "symbol%d@2x.png",thisSymbol->isOfType);
        sprintf(file, "symbol%d-idle0@2x.png" , thisSymbol->isOfType);

        thisSymbol->initWithFile(file);
        turnToExplosiveSymbol(thisSymbol);
    }
    else {
        if (!thisSymbol->isExplosive) {
            thisSymbol->isKeepable = true;
            thisSymbol->isExplosive = true;
//            char file[0x50] = {0};
//            sprintf(file, "symbol%d-glow@2x.png",thisSymbol->isOfType);
//            thisSymbol->initWithFile(file);
//            animGlowSymbol(thisSymbol);
            animSparkSymbol(thisSymbol);
        }
    }
}

void SymbolManager::turnToSuperSymbol(SyntaxSymbol* thisSymbol) {
    
    CCLOG("turnToSuperSymbol type ==%d" , thisSymbol->isOfType);

    if (thisSymbol->isShifter) {
        thisSymbol->isShifter = false;
        char file[0x50] = {0};
//        sprintf(file, "symbol%d@2x.png",thisSymbol->isOfType);
        sprintf(file, "symbol%d-idle0@2x.png" , thisSymbol->isOfType);
        turnToSuperSymbol(thisSymbol);
    }
    else {
        if (thisSymbol->isExplosive) {
            thisSymbol->isExplosive = false;
            thisSymbol->removeFromParentAndCleanup(true);// removeFromSuperview];
            thisSymbol = NULL;
            turnToSuperSymbol(thisSymbol);
        }
        else {
            thisSymbol->isKeepable = true;
            thisSymbol->isOfType = 11;
            animShiftToSuperSymbol(thisSymbol);
        }
    }
}

void SymbolManager::turnToWildcardSymbol(SyntaxSymbol* thisSymbol) {
    
    CCLOG("turnToWildcardSymbol type ==%d" , thisSymbol->isOfType);
    thisSymbol->isShifter = false;
    thisSymbol->isExplosive = false;
    thisSymbol->isKeepable = true;
    cleanSymbol(thisSymbol);
    thisSymbol->isOfType = 7;
    char file[0x50] = {0};
    sprintf(file, "symbol7@2x.png");
    thisSymbol->initWithFile(file);
    
}

void SymbolManager::rectifyCorruptedSymbol(SyntaxSymbol* thisSymbol) {
    thisSymbol->stopAllActions();
    thisSymbol->isKeepable = false;
    animRectifySymbol(thisSymbol);
}

void SymbolManager:: shiftSymbol(SyntaxSymbol* thisSymbol ,int thisType) {
    
    CCLOG("shiftSymbol old type == %d, new type = %d" , thisSymbol->isOfType, thisType );

    char file[0x50] = {0};
//    sprintf(file, "symbol%d@2x.png" , thisType);
    sprintf(file, "symbol%d-idle0@2x.png" , thisType);
    //sprintf(file, "ball_0%d@2x.png" , thisType);
    thisSymbol->isOfType = thisType;
     if (!thisSymbol->isShifter) {
        thisSymbol->initWithFile(file);
//        if (thisType == 9) {
//            thisSymbol->isKeepable = true;
//            thisSymbol->initWithFile("symbol9b@2x.png");
//            thisSymbol->runAction(CCFadeTo::create(0.6f, 255.0f));
//            animSuperSymbol(thisSymbol);
// 
//        }
//        if (thisType == 10) {
//            thisSymbol->isKeepable = true;
//            hiddenSymbolAnimationFrames = CCAnimation::create();
//            for (int i =1 ; i< 5; i++) {
//                char file[0x50] = {0};
//                sprintf(file, "symbol10-%d@2x.png" , i);
//                hiddenSymbolAnimationFrames->addSpriteFrameWithFileName(file);
//                hiddenSymbolAnimationFrames->setDelayPerUnit(0.1f);
//                hiddenSymbolAnimationFrames->setLoops(1);
//                
//            }
//
//            CCAnimate* ani = CCAnimate::create(hiddenSymbolAnimationFrames);
//            thisSymbol->runAction(ani);
//            hiddenSymbolAnimationFrames = NULL;
//            ani = NULL;
//         }
//        if (thisType == 11) {
//            thisSymbol->runAction(CCFadeTo::create(0.6f, 1.0f));
//            thisSymbol->initWithFile("symbol11b@2x.png");
//            animShiftToSuperSymbol(thisSymbol);
//            animGlowSymbol(thisSymbol);
//            
//        }
    }
    else animShifterSymbol(thisSymbol);
}

void SymbolManager ::revealHiddenSymbol(SyntaxSymbol* thisSymbol) {
  
    CCPoint pos = thisSymbol->isIndex;
    cleanSymbol(thisSymbol);
    thisSymbol->removeFromParent();
    thisSymbol = NULL;
    gameEngine->newSymbolMake(pos);
 
}

#pragma animations/////////////////////////////////

void SymbolManager:: animHideSymbol(SyntaxSymbol *thisSymbol,float thisDelay) {
    
//    CCBlink* blink = CCBlink::create(thisDelay, 15);
    
    CCAnimation* temp = CCAnimation::create();
    
    for (int i = 0; i < anim_clear_frames; i++) {
        char file[0x50] = {0};
        sprintf(file, "symbol%d-clear%d@2x.png" , thisSymbol->isOfType, i);
        temp->addSpriteFrameWithFileName(file);
    }
    
    temp->setLoops(1);
    temp->setDelayPerUnit(0.05f);
    CCAnimate* ani = CCAnimate::create(temp);
//    thisSymbol->runAction(ani);

    thisSymbol->runAction(CCSequence::create(/*CCDelayTime::create(0.3f),*/ ani , CCCallFuncN::create(this, callfuncN_selector(SymbolManager::removdSymbol)), NULL));

    temp = NULL;
    ani = NULL;
    
//    removdSymbol(thisSymbol);
 
    
}
void SymbolManager::removdSymbol(CCObject* pSender){
    
    SyntaxSymbol* temp = (SyntaxSymbol*)pSender;
    temp->removeFromParent();
    temp = NULL;
    
    if (LShapeHorizontal) {
        LShapeHorizontal = NULL;
         
    }
    
    if (LShapeVertical) {
        LShapeVertical = NULL;
    }
    
}

void SymbolManager ::animSparkSymbol(SyntaxSymbol *thisSymbol){
    
    CCAnimation* temp = CCAnimation::create();
    
    for (int i = 0; i < anim_spark_frames; i++) {
        char file[0x50] = {0};
        sprintf(file, "symbol%d-spark%d@2x.png" , thisSymbol->isOfType, i);
        temp->addSpriteFrameWithFileName(file);
    }
    
    temp->setLoops(-1);
    temp->setDelayPerUnit(0.05f);
    CCAnimate* ani = CCAnimate::create(temp);
    
    thisSymbol->runAction(ani);
    
    temp = NULL;
    ani = NULL;
    
}

void SymbolManager ::animGlowSymbol(SyntaxSymbol* thisSymbol) {
    
//    CCFadeTo* fade  = CCFadeTo::create(0.4f, 180.0f);
//    CCFadeTo* fade_a = CCFadeTo::create(0.4f, 255);
//    CCSequence* seq = CCSequence::create(fade , CCDelayTime::create(0.05f) , fade_a , NULL);
//    thisSymbol->runAction(CCRepeatForever::create(seq));
    
    CCAnimation* temp = CCAnimation::create();
    
    for (int i = 0; i < anim_glow_frames; i++) {
        char file[0x50] = {0};
        sprintf(file, "symbol%d-clear%d@2x.png" , thisSymbol->isOfType, i);
        temp->addSpriteFrameWithFileName(file);
    }
    
    temp->setLoops(1);
    temp->setDelayPerUnit(0.05f);
    CCAnimate* ani = CCAnimate::create(temp);
    //    thisSymbol->runAction(ani);
    
    thisSymbol->runAction(CCSequence::create(/*CCDelayTime::create(0.3f),*/ ani , CCCallFuncN::create(this, callfuncN_selector(SymbolManager::removdSymbol)), NULL));
    
    temp = NULL;
    ani = NULL;

    
}
 
void SymbolManager:: animExplodeSymbol(SyntaxSymbol *thisSymbol , float thisDelay) {
    cleanSymbol(thisSymbol);
    explodingSymbolFrames =CCAnimation::create();
    for (int i =0 ; i< 19; i++) {
        char file[0x50] = {0};
        sprintf(file, "explodingSymbol%02d@2x.png" , i);
        explodingSymbolFrames->addSpriteFrameWithFileName(file);
        explodingSymbolFrames->setDelayPerUnit(0.02f);
         
    }

    CCAnimate* ani = CCAnimate::create(explodingSymbolFrames);
    thisSymbol->runAction(CCSequence::create( CCDelayTime::create(thisDelay) ,ani,CCFadeTo::create(0.00001, 0.0f),NULL));
    explodingSymbolFrames = NULL;

}

void SymbolManager:: setAnimationExplode(cocos2d::CCObject *pSender){
    
    SyntaxSymbol* temp = (SyntaxSymbol*) pSender;
    temp = NULL;
}

void SymbolManager::animShiftToSuperSymbol(SyntaxSymbol *thisSymbol) {
    
    superSymbolMorphFrames = CCAnimation::create();
    for (int i =0 ; i< 24; i++) {
        char file[0x50] = {0};
        sprintf(file, "superSymbolMorph%02d@2x.png" , i);
        
        superSymbolMorphFrames->addSpriteFrameWithFileName(file);
        superSymbolMorphFrames->setDelayPerUnit(0.01f);
        superSymbolMorphFrames->setLoops(1);
    }

    CCAnimate* ani = CCAnimate::create(superSymbolMorphFrames);
    thisSymbol->runAction(CCSequence::create(ani , CCDelayTime::create(0.2f) , CCCallFuncN::create(this, callfuncN_selector(SymbolManager::addSymbol)) , NULL));
    superSymbolMorphFrames = NULL;
    

}
void SymbolManager::addSymbol(cocos2d::CCObject *pSender){
    
    SyntaxSymbol* thisSymbol = (SyntaxSymbol*) pSender;
    thisSymbol->initWithFile("symbol11@2x.png");
    maske = CCAnimation::create();
    char file[0x50] = {0};
    sprintf(file, "symbol11@2x.png");
    maske->addSpriteFrameWithFileName(file);
    sprintf(file, "symbol11b@2x.png");
    maske->addSpriteFrameWithFileName(file);
    
    maske->setDelayPerUnit(0.2f);
     

    aniExplode = CCAnimate::create(maske);
    thisSymbol->runAction(CCRepeatForever::create(aniExplode));
    
    maske = NULL;
    aniExplode = NULL;
    
     
}

void SymbolManager::animSuperSymbol(SyntaxSymbol *thisSymbol) {
  
    if (!thisSymbol->isKeepable) {
        return;
    }
   
    CCAnimation* shiftAnimation = CCAnimation::create();
    char file[0x50] = {0};
    sprintf(file, "symbol9@2x.png");
    shiftAnimation->addSpriteFrameWithFileName(file);
    sprintf(file, "symbol9b@2x.png");
    shiftAnimation->addSpriteFrameWithFileName(file);
    
    shiftAnimation->setDelayPerUnit(0.2f);
    shiftAnimation->setLoops(-1);
    
    CCAnimate* ani = CCAnimate::create(shiftAnimation);
    thisSymbol->runAction(ani);
    
    shiftAnimation = NULL;
    ani = NULL;

}
void SymbolManager:: setAnimationSuper(cocos2d::CCObject *pSender){
    
//    SyntaxSymbol* temp = (SyntaxSymbol*)pSender;
//    if (temp->isVisible) {
//        animSuperSymbol(temp);
//    }
}


void SymbolManager::animSuperEliminateSymbol(SyntaxSymbol *thisSymbol) {
 
    m_nDelaytime = 1.0f;
    superSymbolMorphFrames = NULL;
    superSymbolMorphFrames = CCAnimation::create();
    for (int i =0 ; i< 23; i++) {
        char file[0x50] = {0};
        sprintf(file, "superSymbolMorph%02d@2x.png" , i);
        
        superSymbolMorphFrames->addSpriteFrameWithFileName(file);
        superSymbolMorphFrames->setDelayPerUnit(0.01f);
        superSymbolMorphFrames->setLoops(1);
    }
    
    explodingSymbolFrames =CCAnimation::create();
    for (int i =0 ; i< 19; i++) {
        char file[0x50] = {0};
        if (i == 12) continue;
        
        sprintf(file, "explodingSymbol%02d@2x.png" , i);
        explodingSymbolFrames->addSpriteFrameWithFileName(file);
        explodingSymbolFrames->setDelayPerUnit(0.02f);
        explodingSymbolFrames->setLoops(1);
    }


    CCAnimate* ani_a = CCAnimate::create(superSymbolMorphFrames);
    CCAnimate* ani_b = CCAnimate::create(explodingSymbolFrames);
    CCFadeTo* fade = CCFadeTo::create(0.1f, 0.0f);
    
     
    if (thisSymbol->isOfType == 11) {
          
        thisSymbol->runAction(CCSequence::create(ani_a , CCDelayTime::create(0.05f),fade,CCCallFunc::create(thisSymbol, callfunc_selector(SymbolManager::DieAnimation)), NULL));

    }else{
        thisSymbol->runAction(CCSequence::create(ani_a , CCDelayTime::create(0.05f),ani_b,CCDelayTime::create(0.1f), CCCallFunc::create(this, callfunc_selector(SymbolManager::setAnimationExplode)), NULL));

    }
}

void SymbolManager::DieAnimation(CCObject *pSender){
    
    SyntaxSymbol* temp = (SyntaxSymbol*) pSender;
    temp = NULL;
}

void SymbolManager::animRectifySymbol(SyntaxSymbol *thisSymbol) {
    
    CCLOG("animRectifySymbol type = %d", thisSymbol->isOfType);
    rectifySymbolMorphFrames = CCAnimation::create();
    for (int i =0 ; i< 31; i++) {
        char file[0x50] = {0};
        sprintf(file, "rectifySymbolMorph%02d@2x.png" , i);
        rectifySymbolMorphFrames->addSpriteFrameWithFileName(file);
        rectifySymbolMorphFrames->setDelayPerUnit(0.01f);
        rectifySymbolMorphFrames->setLoops(1);
    }
    char file[0x50]= {0};
    int type = arc4random() % 6;
//    sprintf(file,"symbol%d@2x.png" ,type);
    sprintf(file, "symbol%d-idle0@2x.png" , type);
    
    rectifySymbolMorphFrames->addSpriteFrameWithFileName(file);
    CCAnimate* ani = CCAnimate::create(rectifySymbolMorphFrames);
    thisSymbol->isOfType = type;
    thisSymbol->runAction(ani);
    
    rectifySymbolMorphFrames = NULL;
    ani = NULL;
 
}

void SymbolManager::animShifterSymbol(SyntaxSymbol *thisSymbol) {
 
     
     
}

void SymbolManager::animGlitchSymbol(SyntaxSymbol *thisSymbol,float thisDelay) {
  
    CCFadeTo* fade = CCFadeTo::create(0.2f, 255);
    CCBlink* blink = CCBlink::create(0.1f,5);
    thisSymbol->runAction(CCSequence::create(CCDelayTime::create(thisDelay), fade, blink , NULL));
    blink = NULL;
}

void SymbolManager:: animFlashSymbol(SyntaxSymbol *thisSymbol) {
    
    thisSymbol->initWithFile("selectionBox@2x.png");
    thisSymbol->runAction(CCBlink::create(1.0f, 7));
}

void  SymbolManager::animLShapeOnSymbol(SyntaxSymbol *thisSymbol, CCLayer* thisView) {
   
    LShapeFramesV = CCAnimation::create();
    LShapeFramesH = CCAnimation::create();
    for (int i =0 ; i< 16; i++) {
        char file[0x50] = {0};
        if (dScaleX < 0.7f) {
             sprintf(file, "beam%02d.png" , i);
        }else {
            sprintf(file, "beam%02d@2x.png" , i);
        }
         
        LShapeFramesV->addSpriteFrameWithFileName(file);
        LShapeFramesV->setDelayPerUnit(0.05f);
        LShapeFramesV->setLoops(1);
        
        LShapeFramesH->addSpriteFrameWithFileName(file);
        LShapeFramesH->setDelayPerUnit(0.05f);
        LShapeFramesH->setLoops(1);

        
    }

    
    LShapeHorizontal = CCSprite::create("beam00@2x.png");
    LShapeVertical = CCSprite::create("beam00@2x.png");
    
    
    LShapeHorizontal->setPosition(thisSymbol->getPosition()); 
    LShapeVertical->setPosition(thisSymbol->getPosition()); 

    
    LShapeHorizontal->setScaleX(LShapeHorizontal->getScaleX());
    LShapeHorizontal->setScaleY(LShapeHorizontal->getScaleY());
    LShapeHorizontal->setRotation(90.0f);
    
    LShapeVertical->setScaleX(LShapeVertical->getScaleX());
    LShapeVertical->setScaleY(LShapeVertical->getScaleY());
    
    thisView->addChild(LShapeHorizontal);
    thisView->addChild(LShapeVertical);
    CCAnimate* ani_V = CCAnimate::create(LShapeFramesV);
    CCAnimate* ani_H = CCAnimate::create(LShapeFramesH);
    
    LShapeVertical->runAction(ani_V);
    LShapeHorizontal->runAction(ani_H);
    
    LShapeVertical->runAction(CCSequence::create(CCDelayTime::create(0.8f) , CCCallFuncN::create(this, callfuncN_selector(SymbolManager::removeLShapeOnSymbol)),NULL));
    LShapeHorizontal->runAction(CCSequence::create(CCDelayTime::create(0.8f) , CCCallFuncN::create(this, callfuncN_selector(SymbolManager::removeLShapeOnSymbol)),NULL));
   
    this->animHideSymbol(thisSymbol, 0);
    
    LShapeFramesH = NULL;
    LShapeFramesV = NULL;
 
}
void SymbolManager::removeLShapeOnSymbol(cocos2d::CCObject *pSender){
    
    CCSprite* temp = (CCSprite*) pSender;
    char file[0x50] = {0};
    sprintf(file, "beam%02d@2x.png" , 15);
    temp->initWithFile(file);
    temp->removeFromParentAndCleanup(true);
}

void SymbolManager::refreshGrid(CCArray *thisGrid){
       for (int i = 0; i < 8; i++) {
           CCArray*temp = (CCArray*)thisGrid->objectAtIndex(i);
             for (int j = 0; j < 8; j++) {
                SyntaxSymbol *thisSymbol =(SyntaxSymbol*)temp->objectAtIndex(j);
                if (thisSymbol->isKeepable) {
                    if (thisSymbol->isExplosive) //animGlowSymbol(thisSymbol);
                        animSparkSymbol(thisSymbol);
                    else {
                        animSuperSymbol(thisSymbol);
                    }
                }
            }
        }
}

void SymbolManager:: cleanSymbol(SyntaxSymbol *thisSymbol) {
   
    if (thisSymbol!= NULL) {
        thisSymbol->stopAllActions();
        thisSymbol = NULL;
    }

}

void SymbolManager:: updateProbabilities() {
    StatusManager* st = StatusManager::sharedStatusManager();
    GameSettings* settings = GameSettings::sharedGameSettings();
    wildcardProbability = st->wildcardProbabilityForLevel(settings->getCurrentLevel());
    shifterProbability = st->shifterProbabilityForLevel(settings->getCurrentLevel());
    corruptedProbability = st->corruptedProbabilityForLevel(settings->getCurrentLevel());
    hiddenProbability = st->hiddenProbabilityForLevel(settings->getCurrentLevel());
}

void SymbolManager ::zeroProbabilities() {
    wildcardProbability = 0;
    shifterProbability = 0;
    corruptedProbability = 0;
    hiddenProbability = 0;
}
