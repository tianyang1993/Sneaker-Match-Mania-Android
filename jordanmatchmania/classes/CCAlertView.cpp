#include "CCAlertView.h"

CCAlertView *CCAlertView::create(const char *_title, const char *_message, const char *_cancel, const char *_ok, CCObject *_object, SEL_CallFuncO _selector1, SEL_CallFuncO _selector2) {
    CCAlertView *pRet = new CCAlertView();
    if(pRet && pRet->init(_title, _message, _cancel, _ok, _object, _selector1, _selector2)) {
		pRet->autorelease();
		return pRet;
	}
	CC_SAFE_DELETE(pRet);

	return NULL;
}

bool CCAlertView::init(const char *_title, const char *_message, const char *_cancel, const char *_ok, CCObject *_object, SEL_CallFuncO _selector1, SEL_CallFuncO _selector2) {
    object    = _object;
    selector1 = _selector1;
    selector2 = _selector2;

    CCSize size = CCDirector::sharedDirector()->getWinSize();
    dScaleX = size.width / 768 , dScaleY = size.height / 1024;
    double dScaleX1 = dScaleX, dScaleY1 = dScaleY;
    if (dScaleX1 < 0.8f) {
        dScaleX1 = 0.9f , dScaleY1 = 0.9f;
    }else if(dScaleX == 1){
        dScaleX1 = 0.9f , dScaleY1 = 0.9f;
    }
    
    this->setTouchEnabled(true);
    this->setPosition(ccp(size.width / 2.0f, size.height / 2.0f));
    

    CCSprite *bgSprite = CCSprite::create("blank.png");
    bgSprite->setTextureRect(CCRect(0, 0, size.width, size.height));
    bgSprite->setColor(ccc3(0, 0, 0));
	bgSprite->setOpacity(0);
    this->addChild(bgSprite, 1000);

    CCSprite *alertViewSprite = CCSprite::create("alert_body.png");
    this->addChild(alertViewSprite, 1001);


    CCMenuItemImage *button1 = CCMenuItemImage::create("alert_button1.png", "alert_button1_down.png", this, menu_selector(CCAlertView::button1Callback));
    CCMenuItemImage *button2 = CCMenuItemImage::create("alert_button2.png", "alert_button2_down.png", this, menu_selector(CCAlertView::button2Callback));
	button1->setOpacity(180);
    button1->setScaleX(button1->getScaleX()*dScaleX1);
    button1->setScaleY(button1->getScaleY()*dScaleY1);
	button2->setOpacity(180);
    button2->setScaleX(button2->getScaleX()*dScaleX1);
    button2->setScaleY(button2->getScaleY()*dScaleY1);

    CCMenu *alertMenu = CCMenu::create(button1, button2, NULL);
    alertMenu->alignItemsHorizontallyWithPadding(15);
    alertMenu->setPosition(ccp(alertViewSprite->getContentSize().width / 2.0f, alertViewSprite->getPosition().y+80*dScaleY1));
    alertViewSprite->addChild(alertMenu);

    CCLabelTTF *titleLabel = CCLabelTTF::create(_title, "HelveticaNeue-Bold", 36*dScaleY1);
    titleLabel->setPosition(ccp(alertViewSprite->getContentSize().width / 2.0f, alertViewSprite->getPosition().y +320.0f*dScaleY1));
    alertViewSprite->addChild(titleLabel);

    CCLabelTTF *messageLabel = CCLabelTTF::create(_message, "HelveticaNeue", 32*dScaleY1, CCSizeMake(alertViewSprite->getContentSize().width - 40.0f*dScaleY, 0), kCCTextAlignmentCenter);
    messageLabel->setPosition(ccp(alertViewSprite->getContentSize().width / 2.0f, alertViewSprite->getPosition().y +200.0f*dScaleY1));
    alertViewSprite->addChild(messageLabel);

    CCLabelTTF *cancelLabel = CCLabelTTF::create(_cancel, "HelveticaNeue-Bold", 36*dScaleY1);
    cancelLabel->setPosition(ccp(button2->getContentSize().width / 2.0f, button2->getContentSize().height / 2.0f));
    button1->addChild(cancelLabel);

    CCLabelTTF *OKlabel = CCLabelTTF::create(_ok, "HelveticaNeue-Bold", 36*dScaleY1);
    OKlabel->setPosition(ccp(button1->getContentSize().width / 2.0f, button1->getContentSize().height / 2.0f));
    button2->addChild(OKlabel);

    bgSprite->runAction(CCFadeTo::create(0.1f, 150));

    CCFiniteTimeAction *scale1 = CCScaleTo::create(0.15f, 1.1f);
    CCFiniteTimeAction *scale2 = CCScaleTo::create(0.1f, 0.9f);
    CCFiniteTimeAction *scale3 = CCScaleTo::create(0.05f, 1.0f*dScaleY);
    alertViewSprite->runAction(CCSequence::create(scale1, scale2, scale3, NULL));

	return true;
}

void CCAlertView::cleanUpCallback() {
    this->removeFromParentAndCleanup(true);
}

void CCAlertView::button1Callback(CCObject *pSender) {
    CCCallFuncO *first  = CCCallFuncO::create(object, selector1, object);
    CCCallFunc *second = CCCallFunc::create(this, callfunc_selector(CCAlertView::cleanUpCallback));
    this->runAction(CCSequence::create(first, second, NULL));
}

void CCAlertView::button2Callback(CCObject *pSender) {
    CCCallFuncO *first  = CCCallFuncO::create(object, selector2, object);
    CCCallFunc *second = CCCallFunc::create(this, callfunc_selector(CCAlertView::cleanUpCallback));
    this->runAction(CCSequence::create(first, second, NULL));
}
