//
//  TweetSender.h
//  GetSocial
//
//  Created by Mikel Eizagirre on 24/03/13.
//
//

#import <Social/Social.h>
#import <Accounts/Accounts.h>

@interface TweetSender : NSObject

+ (void) trySendATweet:(const char *)score;

@end
