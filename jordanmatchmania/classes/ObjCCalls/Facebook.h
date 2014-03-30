//
//  TweetSender.h
//  GetSocial
//
//  Created by Mikel Eizagirre on 24/03/13.
//
//

#import <Social/Social.h>
#import <Accounts/Accounts.h>

@interface Facebook : NSObject

+ (void) tryToPostOnFacebook:(const char *)score;

@end
