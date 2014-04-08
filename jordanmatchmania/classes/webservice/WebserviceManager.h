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

    void postUser(int fbid, char* user_name, char *pass, int gender, int locationid, float lat, float lon, char* email, int deviceid);
    void getUser(char* user_name, char *pass);
    void getGameId(char* gamekey);
    void postGamePlay(int userid, int score, int gameid);
    void getAds(int userid, int gameid);
    void postAdView(int userid, int adid, int gameid);
    void getGpgid(char* gpgcode);
    void postGpg(int userid, int gpgid);
    void getCoupons(int userid, int gameid);
    void postCoupons(int userid, int couponid, int gameid);
    void postBrandlike(int userid, int gameid);
    void postFriendInvite(int userid, int friendid, int gameid);
    void postCouponShare(int userid, int friendid, int couponid, int gameid);
    
    void onHttpRequestCompleted(CCObject *pSender, void *data);
    
};

#endif
