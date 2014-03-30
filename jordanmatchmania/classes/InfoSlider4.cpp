//
//  InfoSlider4.cpp
//  VivaStampede
//
//  Created by Mikhail Berrya on 11/25/13.
//
//

#include "InfoSlider4.h"
InfoSlide4* InfoSlide4::body(){
    
    InfoSlide4* layer= InfoSlide4::create();
    return layer;
}

bool InfoSlide4:: init(){
    
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
    
    m_lTitleLabel = CCLabelTTF::createWithFontDefinition("Special Symbols", strokeTextDef);
    m_lTitleLabel->setPosition(ccp(size.width / 2, size.height - 220*dScaleY));
    m_lTitleLabel->setScaleX(m_lTitleLabel->getScaleX()*0.9f);
    m_lTitleLabel->setScaleY(m_lTitleLabel->getScaleY()*1.2f);
    addChild(m_lTitleLabel);

    
    m_lDescriptionLabel1 = CCLabelTTF::createWithFontDefinition("Tap the symbol then tap any sneaker to \nchange the raffle ticket into that sneaker.", strokeTextDef);
    m_lDescriptionLabel1->setPosition(ccp(size.width *3/4-115*dScaleX, size.height  / 2 + 200*dScaleY));
    m_lDescriptionLabel1->setScaleX(m_lDescriptionLabel1->getScaleX()*0.5f);
    m_lDescriptionLabel1->setScaleY(m_lDescriptionLabel1->getScaleY()*0.7f);
    m_lDescriptionLabel1->setHorizontalAlignment(kCCTextAlignmentLeft);
    addChild(m_lDescriptionLabel1);

    m_lDescriptionLabel2 = CCLabelTTF::createWithFontDefinition("Hypebeast John is crazy! The only way \nto get rid of him is with the Magic shoe \nbox or with the beast Traps!", strokeTextDef);
    m_lDescriptionLabel2->setPosition(ccp(size.width *3/4-100*dScaleX, size.height  / 2+ 50*dScaleY));
    m_lDescriptionLabel2->setScaleX(m_lDescriptionLabel2->getScaleX()*0.5f);
    m_lDescriptionLabel2->setScaleY(m_lDescriptionLabel2->getScaleY()*0.7f);
    m_lDescriptionLabel2->setHorizontalAlignment(kCCTextAlignmentLeft);
    addChild(m_lDescriptionLabel2);


    m_lDescriptionLabel3 = CCLabelTTF::createWithFontDefinition("This sneaky symbol changes to a new \nsneaker every time you make a move.", strokeTextDef);
    m_lDescriptionLabel3->setPosition(ccp(size.width *3/4-125*dScaleX, size.height  / 2-100*dScaleY));
    m_lDescriptionLabel3->setScaleX(m_lDescriptionLabel3->getScaleX()*0.5f);
    m_lDescriptionLabel3->setScaleY(m_lDescriptionLabel3->getScaleY()*0.7f);
    m_lDescriptionLabel3->setHorizontalAlignment(kCCTextAlignmentLeft);
    addChild(m_lDescriptionLabel3);
    
 
    
   
    m_lDescriptionLabel4 = CCLabelTTF::createWithFontDefinition("Tap the shoe store to see what sneaker \nis hiding behind it. But watch out for \nthat crazy Hypebeast!", strokeTextDef);
    m_lDescriptionLabel4->setPosition(ccp(size.width *3/4-100*dScaleX, size.height  / 2 - 250*dScaleY));
    m_lDescriptionLabel4->setScaleX(m_lDescriptionLabel4->getScaleX()*0.5f);
    m_lDescriptionLabel4->setScaleY(m_lDescriptionLabel4->getScaleY()*0.7f);
    m_lDescriptionLabel4->setHorizontalAlignment(kCCTextAlignmentLeft);
    addChild(m_lDescriptionLabel4);

 
    CCSprite* symbol1 = CCSprite::create("symbol7@2x.png");
    symbol1->setPosition(ccp(100*dScaleX, size.height  / 2 + 200*dScaleY));
    symbol1->setScaleX(symbol1->getScaleX()*dScaleX);
    symbol1->setScaleY(symbol1->getScaleY()*dScaleY);
    addChild(symbol1);
    
    CCSprite* symbol2 = CCSprite::create("symbol9@2x.png");
    symbol2->setPosition(ccp(100*dScaleX, size.height  / 2 + 50*dScaleY));
    symbol2->setScaleX(symbol2->getScaleX()*dScaleX);
    symbol2->setScaleY(symbol2->getScaleY()*dScaleY);
    addChild(symbol2);
    
    s1 = CCAnimation::create();
    char file[0x50] = {0};
    sprintf(file, "symbol9@2x.png");
    s1->addSpriteFrameWithFileName(file);
    sprintf(file, "symbol9b@2x.png");
    s1->addSpriteFrameWithFileName(file);
    s1->setDelayPerUnit(0.1f);
    s1->setLoops(-1);
    
    CCAnimate* s1Ani = CCAnimate::create(s1);
    symbol2->runAction(s1Ani);
    
    CCSprite* symbol3 = CCSprite::create("symbol0-shift@2x.png");
    symbol3->setPosition(ccp(100*dScaleX, size.height  / 2-100*dScaleY ));
    symbol3->setScaleX(symbol3->getScaleX()*dScaleX);
    symbol3->setScaleY(symbol3->getScaleY()*dScaleY);
    addChild(symbol3);
    
    s2 = CCAnimation::create();
    for (int i = 0; i<7; i++) {
        char file[0x50] = {0};
        sprintf(file, "symbol%d-shift@2x.png",i);
        s2->addSpriteFrameWithFileName(file);
    }
    s2->setLoops(-1);
    s2->setDelayPerUnit(1.0f);
    CCAnimate* s2Ani = CCAnimate::create(s2);
    symbol3->runAction(s2Ani);
    
    CCSprite* symbol4 = CCSprite::create("symbol10-1@2x.png");
    symbol4->setPosition(ccp(100*dScaleX, size.height  / 2 - 250*dScaleY));
    symbol4->setScaleX(symbol4->getScaleX()*dScaleX);
    symbol4->setScaleY(symbol4->getScaleY()*dScaleY);
    addChild(symbol4);
    
    s3 = CCAnimation::create();
    for (int i = 1; i<5; i++) {
        char file[0x50] = {0};
        sprintf(file, "symbol10-%d@2x.png",i);
        s3->addSpriteFrameWithFileName(file);
    }
    
    s3->setDelayPerUnit(0.2f);
    s3->setLoops(-1);
    
    CCAnimate* s3Ani = CCAnimate::create(s3);
    symbol4->runAction(s3Ani);
    
    
    return  true;
    
}