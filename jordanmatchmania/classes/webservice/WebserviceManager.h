//
//  WebserviceManager.h
//  jordanmatchmania
//
//  Created by Lion on 4/8/14.
//
//

#ifndef jordanmatchmania_WebserviceManager_h
#define jordanmatchmania_WebserviceManager_h

#include "cocos2d.h"

USING_NS_CC;

class WebserviceManager : public CCObject{
    
public:
    static WebserviceManager* sharedInstance();

    void postUser(int fbid, char* user_name, char *pass, int gender, int locationid, float lat, float lon, char* email, int deviceid, cocos2d::CCObject *pTarget, SEL_CallFuncND pSelector);
    void getUser(char* user_name, char *pass, CCObject *pTarget, SEL_CallFuncND pSelector);
    void getGameId(char* gamekey, CCObject *pTarget, SEL_CallFuncND pSelector);
    void postGamePlay(int userid, int score, int gameid, CCObject *pTarget, SEL_CallFuncND pSelector);
    void getAds(int userid, int gameid, CCObject *pTarget, SEL_CallFuncND pSelector);
    void postAdView(int userid, int adid, int gameid, CCObject *pTarget, SEL_CallFuncND pSelector);
    void getGpgid(char* gpgcode, CCObject *pTarget, SEL_CallFuncND pSelector);
    void postGpg(int userid, int gpgid, CCObject *pTarget, SEL_CallFuncND pSelector);
    void getCoupons(int userid, int gameid, CCObject *pTarget, SEL_CallFuncND pSelector);
    void postCoupons(int userid, int couponid, int gameid, CCObject *pTarget, SEL_CallFuncND pSelector);
    void postBrandlike(int userid, int gameid, CCObject *pTarget, SEL_CallFuncND pSelector);
    void postFriendInvite(int userid, int friendid, int gameid, CCObject *pTarget, SEL_CallFuncND pSelector);
    void postCouponShare(int userid, int friendid, int couponid, int gameid, CCObject *pTarget, SEL_CallFuncND pSelector);

};

#endif
