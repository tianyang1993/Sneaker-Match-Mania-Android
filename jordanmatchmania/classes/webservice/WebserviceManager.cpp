//
//  WebserviceManager.cpp
//  jordanmatchmania
//
//  Created by Lion on 4/8/14.
//
//

#include <iostream>
#include "WebserviceManager.h"
#include "CCHttpRequest.h"

#define root_url "http://brandoutgames.com"
#define post_user "http://brandoutgames.com/post_user.php?fbid=%d&login=%s&pass=%s&gender=%d&dob=1976-02-11&locationid=%d&lat=%f&lon=%f&email=%s&deviceid=%d"
#define get_user "http://brandoutgames.com/get_userid.php?login=%s&pass=%s"
#define get_gameid "http://brandoutgames.com/get_gameid.php?gamekey=%s"
#define post_gameplay "http://brandoutgames.com/post_gameplay.php?userid=%d&score=%d&gameid=%d"
#define get_ads "http://brandoutgames.com/get_ads.php?userid=%d&gameid=%d"
#define post_adview "http://brandoutgames.com/post_adview.php?userid=%d&adid=%d&gameid=%d"
#define get_gpgid "http://brandoutgames.com/get_gpgid.php?gpgcode=%s"
#define post_gpg "http://brandoutgames.com/post_gpgredeem.php?userid=%d&gpgid=%d"
#define get_coupons "http://brandoutgames.com/get_coupons.php?userid=%d&gameid=%d"
#define post_coupons "http://brandoutgames.com/post_couponrequest.php?userid=%d&couponid=%d&gameid=%d"
#define post_brand_like "http://brandoutgames.com/post_brandlike.php?userid=%d&gameid=%d"
#define post_friend_invite "http://brandoutgames.com/post_friendinvite.php?userid=%d&friendid=%d&gameid=%d"
#define post_coupon_share "http://brandoutgames.com/post_couponshare.php?userid=%d&friendid=%d&couponid=%d&gameid=%d"

using namespace cocos2d::extension;

WebserviceManager* WebserviceManager::sharedInstance(){
    
    WebserviceManager* manager = new WebserviceManager();
    return manager;

}

void WebserviceManager::postUser(int fbid, char* user_name, char *pass, int gender, int locationid, float lat, float lon, char* email, int deviceid, cocos2d::CCObject *pTarget, SEL_CallFuncND pSelector){
    
    CCHttpRequest *requestor = CCHttpRequest::sharedHttpRequest();
    
    char request[0x100] = {0};
    sprintf(request, post_user, fbid, user_name, pass, gender, locationid, lat, lon, email, deviceid);

    std::string url = request;
    
    requestor->addGetTask(url, pTarget, pSelector);
}

void WebserviceManager::getUser(char* user_name, char *pass, CCObject *pTarget, SEL_CallFuncND pSelector){

    CCHttpRequest *requestor = CCHttpRequest::sharedHttpRequest();
    
    char request[0x100] = {0};
    sprintf(request, get_user, user_name, pass);
    
    std::string url = request;
    
    requestor->addGetTask(url, pTarget, pSelector);

}

void WebserviceManager::getGameId(char* gamekey, CCObject *pTarget, SEL_CallFuncND pSelector){
    CCHttpRequest *requestor = CCHttpRequest::sharedHttpRequest();
    
    char request[0x100] = {0};
    sprintf(request, get_gameid, "FRUIT_CHARMS");
    
    std::string url = request;
    
    requestor->addGetTask(url, pTarget, pSelector);
}

void WebserviceManager::postGamePlay(int userid, int score, int gameid, CCObject *pTarget, SEL_CallFuncND pSelector){
    CCHttpRequest *requestor = CCHttpRequest::sharedHttpRequest();
    
    char request[0x100] = {0};
    sprintf(request, post_gameplay, userid, score, gameid);
    
    std::string url = request;
    
    requestor->addGetTask(url, pTarget, pSelector);
}

void WebserviceManager::getAds(int userid, int gameid, CCObject *pTarget, SEL_CallFuncND pSelector){
    CCHttpRequest *requestor = CCHttpRequest::sharedHttpRequest();
    
    char request[0x100] = {0};
    sprintf(request, get_ads, userid, gameid);
    
    std::string url = request;
    
    requestor->addGetTask(url, pTarget, pSelector);
    
}

void WebserviceManager::postAdView(int userid, int adid, int gameid, CCObject *pTarget, SEL_CallFuncND pSelector){
    CCHttpRequest *requestor = CCHttpRequest::sharedHttpRequest();
    
    char request[0x100] = {0};
    sprintf(request, post_adview, userid, adid, gameid);
    
    std::string url = request;
    
    requestor->addGetTask(url, pTarget, pSelector);
}

void WebserviceManager::getGpgid(char* gpgcode, CCObject *pTarget, SEL_CallFuncND pSelector){
    CCHttpRequest *requestor = CCHttpRequest::sharedHttpRequest();
    
    char request[0x100] = {0};
    sprintf(request, get_gpgid, "BERRYNOW");
    
    std::string url = request;
    
    requestor->addGetTask(url, pTarget, pSelector);
}

void WebserviceManager::postGpg(int userid, int gpgid, CCObject *pTarget, SEL_CallFuncND pSelector){
    CCHttpRequest *requestor = CCHttpRequest::sharedHttpRequest();
    
    char request[0x100] = {0};
    sprintf(request, post_gpg, userid, gpgid);
    
    std::string url = request;
    
    requestor->addGetTask(url, pTarget, pSelector);
    
}

void WebserviceManager::getCoupons(int userid, int gameid, CCObject *pTarget, SEL_CallFuncND pSelector){
    CCHttpRequest *requestor = CCHttpRequest::sharedHttpRequest();
    
    char request[0x100] = {0};
    sprintf(request, get_coupons, userid, gameid);
    
    std::string url = request;
    
    requestor->addGetTask(url, pTarget, pSelector);
}

void WebserviceManager::postCoupons(int userid, int couponid, int gameid, CCObject *pTarget, SEL_CallFuncND pSelector){
    CCHttpRequest *requestor = CCHttpRequest::sharedHttpRequest();
    
    char request[0x100] = {0};
    sprintf(request, post_coupons, userid, couponid, gameid);
    
    std::string url = request;
    
    requestor->addGetTask(url, pTarget, pSelector);
    
}

void WebserviceManager::postBrandlike(int userid, int gameid, CCObject *pTarget, SEL_CallFuncND pSelector){
    CCHttpRequest *requestor = CCHttpRequest::sharedHttpRequest();
    
    char request[0x100] = {0};
    sprintf(request, post_brand_like, userid, gameid);
    
    std::string url = request;
    
    requestor->addGetTask(url, pTarget, pSelector);
}

void WebserviceManager::postFriendInvite(int userid, int friendid, int gameid, CCObject *pTarget, SEL_CallFuncND pSelector){
 
    CCHttpRequest *requestor = CCHttpRequest::sharedHttpRequest();
    
    char request[0x100] = {0};
    sprintf(request, post_friend_invite, userid, friendid, gameid);
    
    std::string url = request;
    
    requestor->addGetTask(url, pTarget, pSelector);
}

void WebserviceManager::postCouponShare(int userid, int friendid, int couponid, int gameid, CCObject *pTarget, SEL_CallFuncND pSelector){
    CCHttpRequest *requestor = CCHttpRequest::sharedHttpRequest();
    
    char request[0x100] = {0};
    sprintf(request, post_coupon_share, userid, friendid, couponid, gameid);
    
    std::string url = request;
    
    requestor->addGetTask(url, pTarget, pSelector);
}

