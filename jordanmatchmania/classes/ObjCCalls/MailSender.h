//
//  MailSender.h
//  GetSocial
//
//  Created by Mikel Eizagirre on 24/03/13.
//
//

#import <UIKit/UIKit.h>
#import <MessageUI/MessageUI.h>

@interface MailSender : UIViewController <MFMailComposeViewControllerDelegate>
{
    UIViewController *currentModalViewController;
}
- (void) sendMailUsingInAppMailer:(const char *)score;
- (void) sendMailUsingExternalApp:(const char *)score;

@end
