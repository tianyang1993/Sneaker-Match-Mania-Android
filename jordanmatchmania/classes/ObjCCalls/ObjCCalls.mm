#include "ObjCCalls.h" 
#import "../cocos2dx/platform/ios/EAGLView.h" 
#import "MailSender.h"
#import "Reachability.h"

void ObjCCalls::trySendAnEMail(const char *score, bool usingInternalApp)
{
    MailSender *mailSender = [MailSender alloc];
    if (usingInternalApp) {
        [mailSender sendMailUsingInAppMailer:score];
    }
    else{
        [mailSender sendMailUsingExternalApp:score];
    }
}

 
bool ObjCCalls::tryIsInternetConnection()
{
    Reachability *networkReachability = [Reachability reachabilityForInternetConnection];
    NetworkStatus networkStatus = [networkReachability currentReachabilityStatus];
    return !(networkStatus == NotReachable);
}
