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

void WebserviceManager::postUser(int fbid, char* user_name, char *pass, int gender, int locationid, float lat, float lon, char* email, int deviceid){
    
    CCHttpRequest *requestor = CCHttpRequest::sharedHttpRequest();
    
    char request[0x100] = {0};
    sprintf(request, post_user, fbid, user_name, pass, gender, locationid, lat, lon, email, deviceid);

    std::string url = request;
    
    requestor->addGetTask(url, this, callfuncND_selector(WebserviceManager::onHttpRequestCompleted));
}

void WebserviceManager::getUser(char* user_name, char *pass){

    CCHttpRequest *requestor = CCHttpRequest::sharedHttpRequest();
    
    char request[0x100] = {0};
    sprintf(request, get_user, user_name, pass);
    
    std::string url = request;
    
    requestor->addGetTask(url, this, callfuncND_selector(WebserviceManager::onHttpRequestCompleted));

}

void WebserviceManager::getGameId(char* gamekey){
    CCHttpRequest *requestor = CCHttpRequest::sharedHttpRequest();
    
    char request[0x100] = {0};
    sprintf(request, get_gameid, "FRUIT_CHARMS");
    
    std::string url = request;
    
    requestor->addGetTask(url, this, callfuncND_selector(WebserviceManager::onHttpRequestCompleted));
}

void WebserviceManager::postGamePlay(int userid, int score, int gameid){
    CCHttpRequest *requestor = CCHttpRequest::sharedHttpRequest();
    
    char request[0x100] = {0};
    sprintf(request, post_gameplay, userid, score, gameid);
    
    std::string url = request;
    
    requestor->addGetTask(url, this, callfuncND_selector(WebserviceManager::onHttpRequestCompleted));
}

void WebserviceManager::getAds(int userid, int gameid){
    CCHttpRequest *requestor = CCHttpRequest::sharedHttpRequest();
    
    char request[0x100] = {0};
    sprintf(request, get_ads, userid, gameid);
    
    std::string url = request;
    
    requestor->addGetTask(url, this, callfuncND_selector(WebserviceManager::onHttpRequestCompleted));
    
}

void WebserviceManager::postAdView(int userid, int adid, int gameid){
    CCHttpRequest *requestor = CCHttpRequest::sharedHttpRequest();
    
    char request[0x100] = {0};
    sprintf(request, post_adview, userid, adid, gameid);
    
    std::string url = request;
    
    requestor->addGetTask(url, this, callfuncND_selector(WebserviceManager::onHttpRequestCompleted));
}

void WebserviceManager::getGpgid(char* gpgcode){
    CCHttpRequest *requestor = CCHttpRequest::sharedHttpRequest();
    
    char request[0x100] = {0};
    sprintf(request, get_gpgid, "BERRYNOW");
    
    std::string url = request;
    
    requestor->addGetTask(url, this, callfuncND_selector(WebserviceManager::onHttpRequestCompleted));
}

void WebserviceManager::postGpg(int userid, int gpgid){
    CCHttpRequest *requestor = CCHttpRequest::sharedHttpRequest();
    
    char request[0x100] = {0};
    sprintf(request, post_gpg, userid, gpgid);
    
    std::string url = request;
    
    requestor->addGetTask(url, this, callfuncND_selector(WebserviceManager::onHttpRequestCompleted));
    
}

void WebserviceManager::getCoupons(int userid, int gameid){
    CCHttpRequest *requestor = CCHttpRequest::sharedHttpRequest();
    
    char request[0x100] = {0};
    sprintf(request, get_coupons, userid, gameid);
    
    std::string url = request;
    
    requestor->addGetTask(url, this, callfuncND_selector(WebserviceManager::onHttpRequestCompleted));
}

void WebserviceManager::postCoupons(int userid, int couponid, int gameid){
    CCHttpRequest *requestor = CCHttpRequest::sharedHttpRequest();
    
    char request[0x100] = {0};
    sprintf(request, post_coupons, userid, couponid, gameid);
    
    std::string url = request;
    
    requestor->addGetTask(url, this, callfuncND_selector(WebserviceManager::onHttpRequestCompleted));
    
}

void WebserviceManager::postBrandlike(int userid, int gameid){
    CCHttpRequest *requestor = CCHttpRequest::sharedHttpRequest();
    
    char request[0x100] = {0};
    sprintf(request, post_brand_like, userid, gameid);
    
    std::string url = request;
    
    requestor->addGetTask(url, this, callfuncND_selector(WebserviceManager::onHttpRequestCompleted));
}

void WebserviceManager::postFriendInvite(int userid, int friendid, int gameid){
 
    CCHttpRequest *requestor = CCHttpRequest::sharedHttpRequest();
    
    char request[0x100] = {0};
    sprintf(request, post_friend_invite, userid, friendid, gameid);
    
    std::string url = request;
    
    requestor->addGetTask(url, this, callfuncND_selector(WebserviceManager::onHttpRequestCompleted));
}

void WebserviceManager::postCouponShare(int userid, int friendid, int couponid, int gameid){
    CCHttpRequest *requestor = CCHttpRequest::sharedHttpRequest();
    
    char request[0x100] = {0};
    sprintf(request, post_coupon_share, userid, friendid, couponid, gameid);
    
    std::string url = request;
    
    requestor->addGetTask(url, this, callfuncND_selector(WebserviceManager::onHttpRequestCompleted));
}

#pragma mark - Http Reqeust
void WebserviceManager::onHttpRequestCompleted(cocos2d::CCObject *pSender, void *data)
{
    HttpResponsePacket *response = (HttpResponsePacket *)data;
    
    if (response->request->reqType == kHttpRequestGet) {
        if (response->succeed) {
            CCLog("Get Request Completed!");
            CCLog("Content: %s", response->responseData.c_str());
        } else {
            CCLog("Get Error: %s", response->responseData.c_str());
        }
    } else if (response->request->reqType == kHttpRequestPost) {
        if (response->succeed) {
            CCLog("Post Request Completed!");
            CCLog("Content: %s", response->responseData.c_str());
        } else {
            CCLog("Post Error: %s", response->responseData.c_str());
        }
    } else if (response->request->reqType == kHttpRequestDownloadFile) {
        if (response->succeed) {
            CCLog("Download Request Completed! Downloaded:");
            
            std::vector<std::string>::iterator iter;
            for (iter = response->request->files.begin(); iter != response->request->files.end(); ++iter) {
                std::string url = *iter;
                CCLog("%s", url.c_str());
            }
        } else {
            CCLog("Download Error: %s", response->responseData.c_str());
        }
    }
}

