//
//  InfoSlider1.cpp
//  VivaStampede
//
//  Created by Mikhail Berrya on 11/25/13.
//
//

#include "InfoSlider1.h"
#include "SyntaxSymbol.h"
#include "SymbolManager.h"

InfoSlide1* InfoSlide1::body(){
    
    InfoSlide1* layer = InfoSlide1::create();
    return layer;
}


bool InfoSlide1::init(){
    
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

    m_lTitleLabel = CCLabelTTF::createWithFontDefinition("3 symbol match", strokeTextDef);
    m_lTitleLabel->setPosition(ccp(size.width / 2, size.height - 280*dScaleY));
    m_lTitleLabel->setScaleX(m_lTitleLabel->getScaleX()*0.9f);
    m_lTitleLabel->setScaleY(m_lTitleLabel->getScaleY()*1.2f);
    addChild(m_lTitleLabel);
    
    m_lDescriptionLabel = CCLabelTTF::createWithFontDefinition("Make a vertical or horizontal line with 3 \nmatching Sneakers to send them back \nto your closet.", strokeTextDef);
    m_lDescriptionLabel->setPosition(ccp(size.width / 2, size.height  / 2+ 50*dScaleY));
    m_lDescriptionLabel->setScaleX(m_lDescriptionLabel->getScaleX()*0.6f);
    m_lDescriptionLabel->setScaleY(m_lDescriptionLabel->getScaleY()*0.8f);
    addChild(m_lDescriptionLabel);
    
    initSymbol();
    return true;
}

void InfoSlide1::initSymbol(){
    
    allSymbols = new CCArray();
    
    SyntaxSymbol* symbol = SyntaxSymbol::body();
    symbol = symbolManager->symbolWithType(3);
    symbol->setPosition(ccp(size.width / 2, size.height / 2 - 150*dScaleY));
    symbol->setScaleX(symbol->getScaleX()*dScaleX);
    symbol->setScaleY(symbol->getScaleY()*dScaleY);
    addChild(symbol);
    allSymbols->addObject(symbol);
    
    symbol = symbolManager->symbolWithType(3);
    symbol->setPosition(ccp(size.width / 2 - 100*dScaleX, size.height / 2 - 150*dScaleY));
    symbol->setScaleX(symbol->getScaleX()*dScaleX);
    symbol->setScaleY(symbol->getScaleY()*dScaleY);
    addChild(symbol);
    allSymbols->addObject(symbol);
    
    symbolA = symbolManager->symbolWithType(3);
    symbolA->setPosition(ccp(size.width / 2+100*dScaleX, size.height / 2- 220*dScaleY));
    symbolA->setScaleX(symbolA->getScaleX()*dScaleX);
    symbolA->setScaleY(symbolA->getScaleY()*dScaleY);
    addChild(symbolA);
    allSymbols->addObject(symbolA);
    
    symbolB = symbolManager->symbolWithType(4);
    symbolB->setPosition(ccp(size.width / 2+100*dScaleX, size.height / 2- 150*dScaleY));
    symbolB->setScaleX(symbolB->getScaleX()*dScaleX);
    symbolB->setScaleY(symbolB->getScaleY()*dScaleY);
    
    addChild(symbolB);
    allSymbols->addObject(symbolB);
    
    symbol = symbolManager->symbolWithType(2);
    symbol->setPosition(ccp(size.width / 2-100*dScaleX, size.height / 2- 220*dScaleY));
    symbol->setScaleX(symbol->getScaleX()*dScaleX);
    symbol->setScaleY(symbol->getScaleY()*dScaleY);
    addChild(symbol);
    allSymbols->addObject(symbol);
    
    symbol = symbolManager->symbolWithType(5);
    symbol->setPosition(ccp(size.width / 2, size.height / 2- 220*dScaleY));
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
    
    this->schedule(schedule_selector(InfoSlide1::step), 0.5);
    
}

void InfoSlide1:: step(float dt){
    
    count++;
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
                    temp->runAction(CCSequence::create(CCBlink::create(0.3f, 5) , CCFadeTo::create(0.3f, 0) , NULL));
                }
            }
            break;
        case 6:
            for (int j= 0 ; j< allSymbols->count(); j++) {
                SyntaxSymbol* temp = (SyntaxSymbol*)allSymbols->objectAtIndex(j);
                removeChild(temp, true);
            }
            allSymbols->removeAllObjects();
            count = 0;
            unschedule(schedule_selector(InfoSlide1::step));
            initSymbol();
            
        default:
            break;
    }
    
    
}