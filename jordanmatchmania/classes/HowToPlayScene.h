//
//  HowToPlayScene.h
//  VivaStampede
//
//  Created by Mikhail Berrya on 11/25/13.
//
//

#ifndef __HOWTOPLAY_SCENE_H__
#define __HOWTOPLAY_SCENE_H__


#include <iostream>
#include "cocos2d.h"
#include "GameSetting.h"

USING_NS_CC;
class InfoSlide1;
class InfoSlide2;
class InfoSlide3;
class InfoSlide4;
class InfoSlide5;
class InfoSlide6;


class HowToPlayScene : public CCLayer{
public:
    virtual bool        init();
    static CCScene*     scene();
    CCSize              size;
    double  dScaleX ,   dScaleY;
    
    CCSprite *infoBackground;
    CCSprite *moreBackground;
    CCSprite *header;
    GameSettings* gameSettings;
    
    
    CCMenuItemImage *playButton;
    
    
    CCLabelTTF *moreTable;
    CCLabelTTF *backButton;
    CCMenuItemLabel *previousSlideButton;
    CCMenuItemLabel *nextSlideButton;
    
    CCMenuItemLabel *moreBack;
    CCMenuItemLabel *moreInfo;
    
    
    InfoSlide1 *infoSlide1;
    InfoSlide2 *infoSlide2;
    InfoSlide3 *infoSlide3;
    InfoSlide4 *infoSlide4;
    InfoSlide5 *infoSlide5;
    InfoSlide6 *infoSlide6;
    int currentSlide;
    bool superType;
    void initMenu();
    void setBackGroundView(int nType);
    void showSlideNumber(int thisSlideNumber);
    void removeSlideNumber(int thisSlideNumber);
    void showMore();
    
    void onPrev(CCObject* pSender);
    void onNext(CCObject* pSender);
    void onPlay(CCObject* pSender);
    void onMore(CCObject* pSender);
    void onInfo(CCObject* pSender);
    
    CREATE_FUNC(HowToPlayScene);
    
};

#endif /*  __HOWTOPLAY_SCENE_H__*/
