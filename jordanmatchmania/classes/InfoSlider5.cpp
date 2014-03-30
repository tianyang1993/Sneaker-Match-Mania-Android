//
//  InfoSlider5.cpp
//  VivaStampede
//
//  Created by Mikhail Berrya on 11/25/13.
//
//

#include "InfoSlider5.h"
InfoSlide5* InfoSlide5::body(){
    
    InfoSlide5* layer = InfoSlide5::create();
    return layer;
}


bool InfoSlide5::init(){
    
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
    
    m_lTitleLabel = CCLabelTTF::createWithFontDefinition("Token", strokeTextDef);
    m_lTitleLabel->setPosition(ccp(size.width / 2, size.height - 220*dScaleY));
    m_lTitleLabel->setScaleX(m_lTitleLabel->getScaleX()*0.9f);
    m_lTitleLabel->setScaleY(m_lTitleLabel->getScaleY()*1.2f);
    addChild(m_lTitleLabel);

    
       
    CCSprite* token = CCSprite::create("byteSymbol@2x.png");
    token->setPosition(ccp(size.width / 2, size.height - 300*dScaleY));
    token->setScaleX(token->getScaleX()*dScaleX);
    token->setScaleY(token->getScaleY()*dScaleY);
    addChild(token);
    
    
    m_lDescriptionLabel = CCLabelTTF::createWithFontDefinition("Collect Tokens and redeem them for Power\n Up`s! Then more points you score, the more\n Tokens you collect.", strokeTextDef);
    m_lDescriptionLabel->setPosition(ccp(size.width / 2, size.height  / 2+50*dScaleY));
    m_lDescriptionLabel->setScaleX(m_lDescriptionLabel->getScaleX()*0.6f);
    m_lDescriptionLabel->setScaleY(m_lDescriptionLabel->getScaleY()*0.8f);
    addChild(m_lDescriptionLabel);

         
    
    return true;
}