//
//  InfoSlider6.cpp
//  VivaStampede
//
//  Created by Mikhail Berrya on 11/25/13.
//
//

#include "InfoSlider6.h"
InfoSlide6* InfoSlide6::body(){
    
    InfoSlide6* layer = InfoSlide6::create();
    return layer;
}


bool InfoSlide6::init(){
    
    if (!CCLayer::init()) {
        return false;
    }
    
    size = CCDirector::sharedDirector()->getWinSize();
    dScaleX = size.width / 768 , dScaleY = size.height / 1024;
    
    ccColor3B strokeColor       =  { 255, 255, 255  };
    ccFontDefinition strokeTextDef;
    strokeTextDef.m_fontSize = 60*dScaleX;
    strokeTextDef.m_fontName = std::string("Dimbo Regular");
    strokeTextDef.m_stroke.m_strokeColor   = strokeColor;
    strokeTextDef.m_stroke.m_strokeEnabled = true;
    strokeTextDef.m_stroke.m_strokeSize    = 1.8;
    
    m_lTitleLabel = CCLabelTTF::createWithFontDefinition("Power Up`s", strokeTextDef);
    m_lTitleLabel->setPosition(ccp(size.width / 2, size.height - 220*dScaleY));
    m_lTitleLabel->setScaleX(m_lTitleLabel->getScaleX()*0.9f);
    m_lTitleLabel->setScaleY(m_lTitleLabel->getScaleY()*1.2f);
    addChild(m_lTitleLabel);

    
    
    m_lDescriptionLabel1 = CCLabelTTF::createWithFontDefinition("Visit the Power Up`s! screen to redeem \nToken for power up`s.", strokeTextDef);
    m_lDescriptionLabel1->setPosition(ccp(size.width *3/4-100*dScaleX, size.height  / 2 + 200*dScaleY));
    m_lDescriptionLabel1->setScaleX(m_lDescriptionLabel1->getScaleX()*0.5f);
    m_lDescriptionLabel1->setScaleY(m_lDescriptionLabel1->getScaleY()*0.7f);
    m_lDescriptionLabel1->setHorizontalAlignment(kCCTextAlignmentLeft);
    addChild(m_lDescriptionLabel1);

    m_lDescriptionLabel2 = CCLabelTTF::createWithFontDefinition("The Penalty-Free Hint(PFH) gives you a\nHint without affecting your score.", strokeTextDef);
    m_lDescriptionLabel2->setPosition(ccp(size.width *3/4-100*dScaleX, size.height  / 2+ 50*dScaleY));
    m_lDescriptionLabel2->setScaleX(m_lDescriptionLabel2->getScaleX()*0.5f);
    m_lDescriptionLabel2->setScaleY(m_lDescriptionLabel2->getScaleY()*0.7f);
    m_lDescriptionLabel2->setHorizontalAlignment(kCCTextAlignmentLeft);
    addChild(m_lDescriptionLabel2);
   
    m_lDescriptionLabel3 = CCLabelTTF::createWithFontDefinition("Need more raffle tickets? Redeem some \nTokens to Power Up and get them.", strokeTextDef);
    m_lDescriptionLabel3->setPosition(ccp(size.width *3/4-100*dScaleX, size.height  / 2- 100 *dScaleY));
    m_lDescriptionLabel3->setScaleX(m_lDescriptionLabel3->getScaleX()*0.5f);
    m_lDescriptionLabel3->setScaleY(m_lDescriptionLabel3->getScaleY()*0.7f);
    m_lDescriptionLabel3->setHorizontalAlignment(kCCTextAlignmentLeft);
    addChild(m_lDescriptionLabel3);

    
    
    m_lDescriptionLabel4 = CCLabelTTF::createWithFontDefinition("No Magic shoe box? Grab some beast \ntraps and get rid of Hypebeast john", strokeTextDef);
    m_lDescriptionLabel4->setPosition(ccp(size.width *3/4-110*dScaleX, size.height  / 2 - 250*dScaleY));
    m_lDescriptionLabel4->setScaleX(m_lDescriptionLabel4->getScaleX()*0.5f);
    m_lDescriptionLabel4->setScaleY(m_lDescriptionLabel4->getScaleY()*0.7f);
    m_lDescriptionLabel4->setHorizontalAlignment(kCCTextAlignmentLeft);
    addChild(m_lDescriptionLabel4);

  
    
    CCSprite* symbol1 = CCSprite::create("byteSymbol@2x.png");
    symbol1->setPosition(ccp(100*dScaleX, size.height  / 2 + 200*dScaleY));
    symbol1->setScaleX(symbol1->getScaleX()*dScaleX);
    symbol1->setScaleY(symbol1->getScaleY()*dScaleY);
    addChild(symbol1);
    
    CCSprite* symbol2 = CCSprite::create("iphone_newclues@2x.png");
    symbol2->setPosition(ccp(100*dScaleX, size.height  / 2 + 50*dScaleY));
    symbol2->setScaleX(symbol2->getScaleX()*dScaleX);
    symbol2->setScaleY(symbol2->getScaleY()*dScaleY);
    addChild(symbol2);
    
    CCSprite* symbol3 = CCSprite::create("symbol7@2x.png");
    symbol3->setPosition(ccp(100*dScaleX, size.height  / 2 - 100*dScaleY));
    symbol3->setScaleX(symbol3->getScaleX()*dScaleX);
    symbol3->setScaleY(symbol3->getScaleY()*dScaleY);
    addChild(symbol3);
    
    CCSprite* symbol4 = CCSprite::create("plattrapsymbol@2x.png");
    symbol4->setPosition(ccp(100*dScaleX, size.height  / 2 -250*dScaleY));
    symbol4->setScaleX(symbol4->getScaleX()*dScaleX);
    symbol4->setScaleY(symbol4->getScaleY()*dScaleY);
    addChild(symbol4);
    
    
    return true;
}