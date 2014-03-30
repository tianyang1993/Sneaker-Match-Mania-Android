//
//  MailSender.m
//  GetSocial
//
//  Created by Mikel Eizagirre on 24/03/13.
//
//

#import "MailSender.h"
#import "../cocos2dx/platform/ios/EAGLView.h"
#import "MoreLayer.h"

@implementation MailSender

-(void) sendMailUsingExternalApp:(const char *)score
{
    NSString *message = [NSString stringWithFormat:@"Local : en\ndevice Model : Android Simulator\nApp Version : 1.0\nMy Score is %s",score];
    [self sendEmailTo:@"support@bravebilly.com"
               withCC:@""
              withBCC:@""
          withSubject:@"Jordan Match Mania"
             withBody:message]; 
}


- (void)sendEmailTo:(NSString*)to withCC:(NSString*)cc withBCC:(NSString*)bcc withSubject:(NSString*)subject withBody:(NSString*)body {
	NSString * url = [NSString stringWithFormat:@"mailto:?to=%@&cc=%@&bcc=%@&subject=%@&body=%@",
					  [to stringByAddingPercentEscapesUsingEncoding:NSASCIIStringEncoding],
					  [cc stringByAddingPercentEscapesUsingEncoding:NSASCIIStringEncoding],
					  [bcc stringByAddingPercentEscapesUsingEncoding:NSASCIIStringEncoding],
					  [subject stringByAddingPercentEscapesUsingEncoding:NSASCIIStringEncoding],
					  [body stringByAddingPercentEscapesUsingEncoding:NSASCIIStringEncoding]];
    
	[[UIApplication sharedApplication] openURL:[NSURL URLWithString:url]];
}

- (void)sendMailUsingInAppMailer:(const char *)score
{
    if ([MFMailComposeViewController canSendMail])
    {
        MFMailComposeViewController *mailer = [[MFMailComposeViewController alloc] init];
                
        mailer.mailComposeDelegate = self;
        
        [mailer setSubject:@"Jordan Match Mania"];
        
        NSString *emailBody = [NSString stringWithFormat:@"Local : en \ndevice Model : Android Simulator\nApp Version : 1.0\nMy Score is %s",score];

        [mailer setMessageBody:emailBody isHTML:YES];
        
        // only for iPad
        // mailer.modalPresentationStyle = UIModalPresentationPageSheet;
        
        UIWindow *window = [[UIApplication sharedApplication] keyWindow];
        currentModalViewController = [UIViewController alloc];
        [window addSubview:currentModalViewController.view];
        [currentModalViewController presentViewController:mailer animated:true completion:^{}];
    }
    else
    {
        UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"Failure"
                                                        message:@"Your device doesn't support the composer sheet"
                                                       delegate:nil
                                              cancelButtonTitle:@"OK"
                                              otherButtonTitles: nil];
        [alert show];
        [alert release];
    }
    
}

- (void)mailComposeController:(MFMailComposeViewController*)controller didFinishWithResult:(MFMailComposeResult)result error:(NSError*)error
{
    const char *message;
	switch (result)
	{
		case MFMailComposeResultCancelled:
			message = "Mail cancelled";
			break;
		case MFMailComposeResultSaved:
			message = "Mail saved";
			break;
		case MFMailComposeResultSent:
			message = "Mail send";
			break;
		case MFMailComposeResultFailed:
			message = "Mail failed";
			break;
		default:
            message = "Mail cancelled";
			break;
	}
    UIAlertView *myalertView = [[UIAlertView alloc]initWithTitle:@"Mail"
                                                         message:[NSString stringWithCString:message encoding:NSASCIIStringEncoding] delegate:nil cancelButtonTitle:@"Ok" otherButtonTitles:nil, nil];
    [myalertView show];
    
    MoreScene::get_instance()->updateMessageLabel(message);

    NSLog(@"%s",message);
    
	[currentModalViewController dismissViewControllerAnimated:true completion:^{}];
    [currentModalViewController.view.superview removeFromSuperview];
    [currentModalViewController release];
}

@end
