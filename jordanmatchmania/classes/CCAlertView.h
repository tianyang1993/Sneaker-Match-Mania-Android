#include "cocos2d.h"

#ifndef __CC_ALERT_VIEW_CLASS__
#define __CC_ALERT_VIEW_CLASS__

using namespace cocos2d;

class CCAlertView : public CCLayer {
public:
    static CCAlertView *create(const char *_title, const char *_message, const char *_cancel, const char *_ok, CCObject *_object, SEL_CallFuncO _selector1, SEL_CallFuncO _selector2);
    bool init(const char *_title, const char *_message, const char *_cancel, const char *_ok, CCObject *_object, SEL_CallFuncO _selector1, SEL_CallFuncO _selector2);
    double dScaleX,dScaleY;

private:
    CCObject *object;
    SEL_CallFuncO selector1;
    SEL_CallFuncO selector2;
    void cleanUpCallback();
	void button1Callback(CCObject *pSender);
	void button2Callback(CCObject *pSender);
};

#endif
