//
//  InfoSlider3.cpp
//  Zookeeper Stampede
//
//  Created by Mikhail Berrya on 11/19/13.
//
//

#include "InfoSlider3.h"
#include "SyntaxSymbol.h"
#include "SymbolManager.h"
InfoSlide3* InfoSlide3::body(){
    
    InfoSlide3* layer = InfoSlide3::create();
    return layer;
}


bool InfoSlide3::init(){
    
    if (!CCLayer::init()) {
        return false;
    }
    
    size = CCDirector::sharedDirector()->getWinSize();
    dScaleX = size.width / 768 , dScaleY = size.height / 1024;
    count =0;
    
    ccColor3B strokeColor       =  { 255, 255, 255  };
    ccFontDefinition strokeTextDef;
    strokeTextDef.m_fontSize = 60*dScaleX;
    strokeTextDef.m_fontName = std::string("Dimbo Regular");
    strokeTextDef.m_stroke.m_strokeColor   = strokeColor;
    strokeTextDef.m_stroke.m_strokeEnabled = true;
    strokeTextDef.m_stroke.m_strokeSize    = 1.8;
   
    m_lTitleLabel = CCLabelTTF::createWithFontDefinition("5 symbol match", strokeTextDef);
    m_lTitleLabel->setPosition(ccp(size.width / 2, size.height - 280*dScaleY));
    m_lTitleLabel->setScaleX(m_lTitleLabel->getScaleX()*0.9f);
    m_lTitleLabel->setScaleY(m_lTitleLabel->getScaleY()*1.2f);
    addChild(m_lTitleLabel);

    
    
    m_lDescriptionLabel = CCLabelTTF::createWithFontDefinition("Matching 5 sneakers will create a Magic shoe \nbox. A Magic shoe box will send every sneaker of \nthat kind on the screen back to your closet.", strokeTextDef);
    m_lDescriptionLabel->setPosition(ccp(size.width / 2, size.height  / 2+ 50*dScaleY));
    m_lDescriptionLabel->setScaleX(m_lDescriptionLabel->getScaleX()*0.6f);
    m_lDescriptionLabel->setScaleY(m_lDescriptionLabel->getScaleY()*0.8f);
    addChild(m_lDescriptionLabel);

      
    
    allSymbolsTem = new CCArray();
    initWithSymbol();
    return true;
}

void InfoSlide3::initWithSymbol(){
    allSymbols = new CCArray();
    
    SyntaxSymbol* symbol = SyntaxSymbol::body();
    
    // block Top
    symbolToMakeSuper = symbolManager->symbolWithType(3);
    symbolToMakeSuper->setPosition(ccp(size.width / 2 - 200*dScaleX, size.height / 2 - 150*dScaleY));
    symbolToMakeSuper->setScaleX(symbolToMakeSuper->getScaleX()*dScaleX);
    symbolToMakeSuper->setScaleY(symbolToMakeSuper->getScaleY()*dScaleY);
    
    
    addChild(symbolToMakeSuper);
    
    
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
    symbol = symbolManager->symbolWithType(3);
    symbol->setPosition(ccp(size.width / 2+200*dScaleX, size.height / 2- 150*dScaleY));
    symbol->setScaleX(symbol->getScaleX()*dScaleX);
    symbol->setScaleY(symbol->getScaleY()*dScaleY);
    
    addChild(symbol);
    allSymbols->addObject(symbol);
    
    
    // block Bottom
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
    symbol = symbolManager->symbolWithType(2);
    symbol->setPosition(ccp(size.width / 2+200*dScaleX, size.height / 2- 220*dScaleY));
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
    
    this->schedule(schedule_selector(InfoSlide3::step1), 0.5);
    
}

void InfoSlide3:: step1(float dt){
    count++;
    CCLOG("Schdule Schdule");
    CCAnimation* explode = createArray((char*)"superSymbolMorph", 23);
    if (count == 6) {
        maske = CCAnimation::create();
        char file[0x50] = {0};
        sprintf(file, "symbol11@2x.png");
        maske->addSpriteFrameWithFileName(file);
        sprintf(file, "symbol11b@2x.png");
        maske->addSpriteFrameWithFileName(file);
        maske->setDelayPerUnit(0.2f);
        maske->setLoops(-1);
        
    }
    maske = CCAnimation::create();
    char file[0x50] = {0};
    sprintf(file, "symbol11@2x.png");
    maske->addSpriteFrameWithFileName(file);
    sprintf(file, "symbol11b@2x.png");
    maske->addSpriteFrameWithFileName(file);
    
    maske->setDelayPerUnit(0.2f);
    maske->setLoops(-1);
    
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
                    temp->runAction(CCSequence::create(CCBlink::create(0.3f, 5) , CCFadeTo::create(0.3f, 0) , NULL));
                }
            }
            symbolToMakeSuper->runAction(CCSequence::create(CCDelayTime::create(0.2f), CCAnimate::create(explode) , CCFadeTo::create(0.0001f, 0)
                                                     ,NULL));
            break;
        case 6:
            for (int j= 0 ; j< allSymbols->count(); j++) {
                SyntaxSymbol* temp = (SyntaxSymbol*)allSymbols->objectAtIndex(j);
                removeChild(temp, true);
            }
            allSymbols->removeAllObjects();
            count = 0;
            explode = NULL;
            symbolToMakeSuper->removeAllComponents();
            symbolToMakeSuper->stopAllActions();
            symbolToMakeSuper->runAction(CCSequence::create(CCFadeTo::create(0.01f, 255), CCAnimate::create(maske),NULL));
            this->unschedule(schedule_selector(InfoSlide3::step1));
            nextWithSymbol();
            
            
        default:
            break;
    }
    
    
}

void InfoSlide3:: nextWithSymbol(){
    
    allSymbols->removeAllObjects();
    SyntaxSymbol* symbol = SyntaxSymbol::body();
    
    //block3 Top
    
    symbol = symbolManager->symbolWithType(3);
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
    symbol = symbolManager->symbolWithType(1);
    symbol->setPosition(ccp(size.width/2+200*dScaleX, size.height / 2- 80*dScaleY));
    symbol->setScaleX(symbol->getScaleX()*dScaleX);
    symbol->setScaleY(symbol->getScaleY()*dScaleY);
    
    addChild(symbol);
    allSymbols->addObject(symbol);
    
    // block 2 center
    symbolToMakeSuper->setPosition(ccp(size.width / 2 - 200*dScaleX, size.height / 2 - 150*dScaleY));
    
    
    allSymbols->addObject(symbolToMakeSuper);
    
    symbol = symbolManager->symbolWithType(5);
    symbol->setPosition(ccp(size.width / 2 - 100*dScaleX, size.height / 2 - 150*dScaleY));
    symbol->setScaleX(symbol->getScaleX()*dScaleX);
    symbol->setScaleY(symbol->getScaleY()*dScaleY);
    
    addChild(symbol);
    allSymbols->addObject(symbol);
    
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
    
    symbol = symbolManager->symbolWithType(1);
    symbol->setPosition(ccp(size.width / 2+200*dScaleX, size.height / 2- 150*dScaleY));
    symbol->setScaleX(symbol->getScaleX()*dScaleX);
    symbol->setScaleY(symbol->getScaleY()*dScaleY);
    
    addChild(symbol);
    allSymbols->addObject(symbol);
    
    
    // block 1 Bottom
    symbolB = symbolManager->symbolWithType(1);
    symbolB->setPosition(ccp(size.width / 2-200*dScaleX, size.height / 2- 220*dScaleY));
    symbolB->setScaleX(symbolB->getScaleX()*dScaleX);
    symbolB->setScaleY(symbolB->getScaleY()*dScaleY);
    
    addChild(symbolB);
    allSymbols->addObject(symbolB);
    
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
    
    selectbox->setPosition(symbolToMakeSuper->getPosition());
    
    this->schedule(schedule_selector(InfoSlide3::step2), 0.5);
    
}

void InfoSlide3:: step2(float dt){
    count++;
    CCAnimation* explode = createArray((char*)"superSymbolMorph", 23);
    
    switch (count) {
        case 1:
            selectbox->setVisible(true);
            break;
        case 2:
            selectbox->setPosition(ccp(size.width / 2-200*dScaleX, size.height / 2- 220*dScaleY));
            break;
        case 3:
            selectbox->setVisible(false);
            symbolToMakeSuper->runAction(CCMoveTo::create(0.2f, symbolB->getPosition()));
            symbolB->runAction(CCMoveTo::create(0.2f, symbolToMakeSuper->getPosition()));
            break;
        case 4:
            for (int i= 0 ; i< allSymbols->count(); i++) {
                SyntaxSymbol* temp = (SyntaxSymbol*)allSymbols->objectAtIndex(i);
                CCAnimate* ani = CCAnimate::create(explode);
                if (temp->isOfType == 1) {
                    symbolTemp = symbolManager->symbolWithType(1);
                    symbolTemp->setPosition(temp->getPosition());
                    addChild(symbolTemp);
                    symbolTemp->runAction(ani);
                    temp->runAction(CCFadeTo::create(0.8f, 0));
                    allSymbolsTem->addObject(symbolTemp);
                }
                
                symbolToMakeSuper->runAction(CCFadeTo::create(0.8f, 0));
            }
            
            break;
        case 6:
            for (int j= 0 ; j< allSymbols->count(); j++) {
                SyntaxSymbol* temp = (SyntaxSymbol*)allSymbols->objectAtIndex(j);
                removeChild(temp, true);
            }
            
            for (int j= 0 ; j< allSymbolsTem->count(); j++) {
                SyntaxSymbol* temp = (SyntaxSymbol*)allSymbolsTem->objectAtIndex(j);
                removeChild(temp, true);
            }
            allSymbols->removeAllObjects();
            removeChild(symbolToMakeSuper, true);
            count = 0;
            this->unschedule(schedule_selector(InfoSlide3::step2));
            initWithSymbol();
        default:
            break;
    }
    
    
}

CCAnimation* InfoSlide3::createArray(char *name, int framCount){
    CCAnimation* animation = CCAnimation::create();
    for (int i = 0; i<framCount; i++) {
        char file[100] = {0};
        sprintf(file, "%s%02d@2x.png" , name , i);
        animation->addSpriteFrameWithFileName(file);
    }
    
    animation->setDelayPerUnit(0.03f);
    animation->setLoops(1);
    
    return animation;
    
    
}
