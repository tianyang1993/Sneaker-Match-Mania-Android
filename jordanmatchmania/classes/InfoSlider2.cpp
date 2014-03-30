//
//  InfoSlider2.cpp
//  VivaStampede
//
//  Created by Mikhail Berrya on 11/25/13.
//
//

#include "InfoSlider2.h"
#include "SymbolManager.h"
#include "SyntaxSymbol.h"

InfoSlide2* InfoSlide2::body(){
    
    InfoSlide2* layer = InfoSlide2::create();
    return layer;
}


bool InfoSlide2::init(){
    
    if (!CCLayer::init()) {
        return false;
    }
    
    size = CCDirector::sharedDirector()->getWinSize();
    dScaleX = size.width / 768 , dScaleY = size.height / 1024;
    count = 0;
    
    ccColor3B strokeColor       =  { 255, 255, 255  };
    ccFontDefinition strokeTextDef;
    strokeTextDef.m_fontSize = 60*dScaleX;
    strokeTextDef.m_fontName = std::string("Dimbo Regular");
    strokeTextDef.m_stroke.m_strokeColor   = strokeColor;
    strokeTextDef.m_stroke.m_strokeEnabled = true;
    strokeTextDef.m_stroke.m_strokeSize    = 1.8;

    m_lTitleLabel = CCLabelTTF::createWithFontDefinition("4 symbol match", strokeTextDef);
    m_lTitleLabel->setPosition(ccp(size.width / 2, size.height - 280*dScaleY));
    m_lTitleLabel->setScaleX(m_lTitleLabel->getScaleX()*0.9f);
    m_lTitleLabel->setScaleY(m_lTitleLabel->getScaleY()*1.2f);
    addChild(m_lTitleLabel);
    
 
    m_lDescriptionLabel = CCLabelTTF::createWithFontDefinition("Matching 4 sneakers will get them hype power. \nThey will take all adjacent sneaker back to the \ncloset with them!", strokeTextDef);
    m_lDescriptionLabel->setPosition(ccp(size.width / 2, size.height  / 2+ 50*dScaleY));
    m_lDescriptionLabel->setScaleX(m_lDescriptionLabel->getScaleX()*0.6f);
    m_lDescriptionLabel->setScaleY(m_lDescriptionLabel->getScaleY()*0.8f);
    addChild(m_lDescriptionLabel);

    
    initWithSymbol();
    
    return true;
}

void InfoSlide2:: initWithSymbol(){
    allSymbols = new CCArray();
    
    SyntaxSymbol* symbol = SyntaxSymbol::body();
//Row 1. Symbols/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\
    
    symbolToMakeExplosive = symbolManager->symbolWithType(3);
    symbolToMakeExplosive->setPosition(ccp(size.width / 2 - 200*dScaleX, size.height / 2 - 150*dScaleY));
    symbolToMakeExplosive->setScaleX(symbolToMakeExplosive->getScaleX()*dScaleX);
    symbolToMakeExplosive->setScaleY(symbolToMakeExplosive->getScaleY()*dScaleY);
    addChild(symbolToMakeExplosive);
    
    
    
    symbol = symbolManager->symbolWithType(3);
    symbol->setPosition(ccp(size.width / 2 - 100*dScaleX, size.height / 2 - 150*dScaleY));
    symbol->setScaleX(symbol->getScaleX()*dScaleX);
    symbol->setScaleY(symbol->getScaleY()*dScaleY);
    addChild(symbol);
    allSymbols->addObject(symbol);
    
    symbolB = symbolManager->symbolWithType(4);
    symbolB->setPosition(ccp(size.width / 2, size.height / 2- 150*dScaleY));
    symbolB->setScaleX(symbolB->getScaleX()*dScaleX);
    symbolB->setScaleY(symbolB->getScaleY()*dScaleY);
    addChild(symbolB);
    allSymbols->addObject(symbolB);
    
    symbol = symbolManager->symbolWithType(3);
    symbol->setPosition(ccp(size.width / 2+100*dScaleX, size.height / 2- 150*dScaleY));
    symbol->setScaleX(symbol->getScaleX()*dScaleX);
    symbol->setScaleY(symbol->getScaleY()*dScaleY);
    addChild(symbol);
    allSymbols->addObject(symbol);
    
    
//Row 2. Symbols/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\
   
    
    symbol = symbolManager->symbolWithType(2);
    symbol->setPosition(ccp(size.width / 2-200*dScaleX, size.height / 2- 220*dScaleY));
    symbol->setScaleX(symbol->getScaleX()*dScaleX);
    symbol->setScaleY(symbol->getScaleY()*dScaleY);
    addChild(symbol);
    allSymbols->addObject(symbol);
    
    symbol = symbolManager->symbolWithType(5);
    symbol->setPosition(ccp(size.width / 2-100*dScaleX, size.height / 2- 220*dScaleY));
    symbol->setScaleX(symbol->getScaleX()*dScaleX);
    symbol->setScaleY(symbol->getScaleY()*dScaleY);
    
    addChild(symbol);
    allSymbols->addObject(symbol);
    
    symbolA = symbolManager->symbolWithType(3);
    symbolA->setPosition(ccp(size.width / 2, size.height / 2- 220*dScaleY));
    symbolA->setScaleX(symbolA->getScaleX()*dScaleX);
    symbolA->setScaleY(symbolA->getScaleY()*dScaleY);
    addChild(symbolA);
    allSymbols->addObject(symbolA);
    
    symbol = symbolManager->symbolWithType(1);
    symbol->setPosition(ccp(size.width / 2+100*dScaleX, size.height / 2- 220*dScaleY));
    symbol->setScaleX(symbol->getScaleX()*dScaleX);
    symbol->setScaleY(symbol->getScaleY()*dScaleY);
    addChild(symbol);
    allSymbols->addObject(symbol);
    
    
    selectbox = CCSprite::create("selectionBox@2x.png");
    selectbox->setPosition(symbolA->getPosition());
    selectbox->setScaleX(selectbox->getScaleX()*dScaleX);
    selectbox->setScaleY(selectbox->getScaleY()*dScaleY);
    selectbox->setVisible(false);
    addChild(selectbox);
    
    this->schedule(schedule_selector(InfoSlide2::step1), 0.5);
    
}

void InfoSlide2:: step1(float dt){
    count++;
    char file[0x50] = {0};
    CCFadeTo* fade  = CCFadeTo::create(0.4f, 180.0f);
    CCFadeTo* fade_a = CCFadeTo::create(0.4f, 255);
    CCSequence* seq = CCSequence::create(fade , CCDelayTime::create(0.05f) , fade_a , NULL);
    sprintf(file, "symbol%d-glow@2x.png",symbolToMakeExplosive->isOfType);
   
    CCLOG("Schdule Schdule");
    
    switch (count) {
        case 1:
            selectbox->setVisible(true);
            break;
        case 2:
            selectbox->setVisible(false);
            break;
        case 3:
            symbolA->runAction(CCMoveTo::create(0.2f, symbolB->getPosition()));
            symbolB->runAction(CCMoveTo::create(0.2f, symbolA->getPosition()));
            break;
        case 4:
            
            for (int i= 0 ; i< allSymbols->count(); i++) {
                SyntaxSymbol* temp = (SyntaxSymbol*)allSymbols->objectAtIndex(i);
                if (temp->isOfType == 3) {
                    temp->runAction(CCSequence::create(CCBlink::create(0.2f, 8) , CCDelayTime::create(0.2f), CCFadeTo::create(0.3f, 0) , NULL));
                }
            }
            symbolToMakeExplosive->initWithFile(file);
            symbolToMakeExplosive->runAction(CCRepeatForever::create(seq));
            break;
       
        case 6:
            for (int j= 0 ; j< allSymbols->count(); j++) {
                SyntaxSymbol* temp = (SyntaxSymbol*)allSymbols->objectAtIndex(j);
                if (temp->isOfType !=3) {
                    temp->runAction(CCFadeTo::create(0.5f, 0));
                }
                
            }
            break;
        case 8:
            for (int j= 0 ; j< allSymbols->count(); j++) {
                SyntaxSymbol* temp = (SyntaxSymbol*)allSymbols->objectAtIndex(j);
                removeChild(temp);
            }
            allSymbols->removeAllObjects();
            count = 0;
            unschedule(schedule_selector(InfoSlide2::step1));
            this->nextWithSymbol();

       default:
            break;
    }
    
    
}

void InfoSlide2:: nextWithSymbol(){
    
    allSymbols->removeAllObjects();
    SyntaxSymbol* symbol = SyntaxSymbol::body();
    

    symbolToMakeExplosive->setPosition(ccp(size.width / 2 - 200*dScaleX, size.height / 2 - 150*dScaleY));
    // block 1 Bottom
    symbol = symbolManager->symbolWithType(0);
    symbol->setPosition(ccp(size.width / 2-200*dScaleX, size.height / 2- 220*dScaleY));
    symbol->setScaleX(symbol->getScaleX()*dScaleX);
    symbol->setScaleY(symbol->getScaleY()*dScaleY);
    
    addChild(symbol);
    allSymbols->addObject(symbol);
    
    symbol = symbolManager->symbolWithType(1);
    symbol->setPosition(ccp(size.width / 2-100*dScaleX, size.height / 2- 220*dScaleY));
    symbol->setScaleX(symbol->getScaleX()*dScaleX);
    symbol->setScaleY(symbol->getScaleY()*dScaleY);
    
    addChild(symbol);
    allSymbols->addObject(symbol);
    
    symbol = symbolManager->symbolWithType(2);
    symbol->setPosition(ccp(size.width / 2, size.height / 2- 220*dScaleY));
    symbol->setScaleX(symbol->getScaleX()*dScaleX);
    symbol->setScaleY(symbol->getScaleY()*dScaleY);
    
    addChild(symbol);
    allSymbols->addObject(symbol);
    
    symbol = symbolManager->symbolWithType(5);
    symbol->setPosition(ccp(size.width / 2+100*dScaleX, size.height / 2- 220*dScaleY));
    symbol->setScaleX(symbol->getScaleX()*dScaleX);
    symbol->setScaleY(symbol->getScaleY()*dScaleY);
    
    addChild(symbol);
    allSymbols->addObject(symbol);
    
    symbol = symbolManager->symbolWithType(6);
    symbol->setPosition(ccp(size.width / 2+200*dScaleX, size.height / 2- 220*dScaleY));
    symbol->setScaleX(symbol->getScaleX()*dScaleX);
    symbol->setScaleY(symbol->getScaleY()*dScaleY);
    
    addChild(symbol);
    allSymbols->addObject(symbol);
    
    
    // block 2 center
    
    allSymbols->addObject(symbolToMakeExplosive);
    
    symbolB = symbolManager->symbolWithType(5);
    symbolB->setPosition(ccp(size.width / 2 - 100*dScaleX, size.height / 2 - 150*dScaleY));
    symbolB->setScaleX(symbolB->getScaleX()*dScaleX);
    symbolB->setScaleY(symbolB->getScaleY()*dScaleY);
    
    addChild(symbolB);
    allSymbols->addObject(symbolB);
    
    symbol = symbolManager->symbolWithType(3);
    symbol->setPosition(ccp(size.width / 2 , size.height / 2- 150*dScaleY));
    symbol->setScaleX(symbol->getScaleX()*dScaleX);
    symbol->setScaleY(symbol->getScaleY()*dScaleY);
    
    addChild(symbol);
    allSymbols->addObject(symbol);
    
    symbol = symbolManager->symbolWithType(3);
    symbol->setPosition(ccp(size.width / 2+100*dScaleX, size.height / 2- 150*dScaleY));
    symbol->setScaleX(symbol->getScaleX()*dScaleX);
    symbol->setScaleY(symbol->getScaleY()*dScaleY);
    
    addChild(symbol);
    allSymbols->addObject(symbol);
    
    symbol = symbolManager->symbolWithType(2);
    symbol->setPosition(ccp(size.width / 2+200*dScaleX, size.height / 2- 150*dScaleY));
    symbol->setScaleX(symbol->getScaleX()*dScaleX);
    symbol->setScaleY(symbol->getScaleY()*dScaleY);
    
    addChild(symbol);
    allSymbols->addObject(symbol);
    
    //block3 Top
    
    symbol = symbolManager->symbolWithType(1);
    symbol->setPosition(ccp(size.width / 2-200*dScaleX, size.height / 2- 80*dScaleY));
    symbol->setScaleX(symbol->getScaleX()*dScaleX);
    symbol->setScaleY(symbol->getScaleY()*dScaleY);
    
    addChild(symbol);
    allSymbols->addObject(symbol);
    symbol = symbolManager->symbolWithType(1);
    symbol->setPosition(ccp(size.width / 2-100*dScaleX, size.height / 2- 80*dScaleY));
    symbol->setScaleX(symbol->getScaleX()*dScaleX);
    symbol->setScaleY(symbol->getScaleY()*dScaleY);
    
    addChild(symbol);
    allSymbols->addObject(symbol);
    symbol = symbolManager->symbolWithType(6);
    symbol->setPosition(ccp(size.width / 2, size.height / 2- 80*dScaleY));
    symbol->setScaleX(symbol->getScaleX()*dScaleX);
    symbol->setScaleY(symbol->getScaleY()*dScaleY);
    
    addChild(symbol);
    allSymbols->addObject(symbol);
    symbol = symbolManager->symbolWithType(1);
    symbol->setPosition(ccp(size.width / 2+100*dScaleX, size.height / 2- 80*dScaleY));
    symbol->setScaleX(symbol->getScaleX()*dScaleX);
    symbol->setScaleY(symbol->getScaleY()*dScaleY);
    
    addChild(symbol);
    allSymbols->addObject(symbol);
    symbol = symbolManager->symbolWithType(4);
    symbol->setPosition(ccp(size.width/2+200*dScaleX, size.height / 2- 80*dScaleY));
    symbol->setScaleX(symbol->getScaleX()*dScaleX);
    symbol->setScaleY(symbol->getScaleY()*dScaleY);
    
    addChild(symbol);
    allSymbols->addObject(symbol);
    
    selectbox->setPosition(symbolToMakeExplosive->getPosition());
    
    this->schedule(schedule_selector(InfoSlide2::step2), 0.5);
    
}

void InfoSlide2:: step2(float dt){
    count++;
   
    
  
    switch (count) {
        case 1:
            selectbox->setVisible(true);
            break;
        case 2:
            selectbox->setVisible(false);
            break;
        case 3:
            symbolToMakeExplosive->runAction(CCMoveTo::create(0.2f, symbolB->getPosition()));
            
            symbolB->runAction(CCMoveTo::create(0.2f, symbolToMakeExplosive->getPosition()));
            break;
        case 4:
            symbolToMakeExplosive->stopAllActions();
            this->ExplodeAnimation();
            break;
        case 6:
            for (int j= 0 ; j< allSymbols->count(); j++) {
                SyntaxSymbol* temp = (SyntaxSymbol*)allSymbols->objectAtIndex(j);
                removeChild(temp, true);
            }
            allSymbols->removeAllObjects();
            removeChild(symbolToMakeExplosive, true);
            count = 0;
            this->unschedule(schedule_selector(InfoSlide2::step2));
            initWithSymbol();
        default:
            break;
    }
    
    
}
void InfoSlide2:: ExplodeAnimation(){
    
     
    CCAnimation* explode = createArray((char*)"explodingSymbol", 18);
   
    for (int i= 0 ; i< allSymbols->count(); i++) {
        float delay = (float) ((arc4random() % 5) / 10.0);
        CCAnimate* ani = CCAnimate::create(explode);
        SyntaxSymbol* temp = (SyntaxSymbol*)allSymbols->objectAtIndex(i);
        temp->runAction(CCSequence::create(CCDelayTime::create(delay) ,ani,CCFadeTo::create(0.00001, 0.0f),NULL));
    }
    
    CCAnimate* ani = CCAnimate::create(explode);
    symbolToMakeExplosive->runAction(CCSequence::create(ani,CCFadeTo::create(0.0000001, 0.0f),NULL));

    
}
CCAnimation* InfoSlide2::createArray(char *name, int framCount){
    CCAnimation* animation = CCAnimation::create();
    for (int i = 0; i<framCount; i++) {
        char file[100] = {0};
        sprintf(file, "%s%02d@2x.png" , name , i);
        animation->addSpriteFrameWithFileName(file);
    }
    
    animation->setDelayPerUnit(0.02f);
    animation->setLoops(1);
    
    return animation;
    
    
}
