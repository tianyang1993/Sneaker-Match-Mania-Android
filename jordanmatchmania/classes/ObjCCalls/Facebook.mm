//
//  TweetSender.m
//  GetSocial
//
//  Created by Mikel Eizagirre on 24/03/13.
//
//

#import "Facebook.h"
#import "../cocos2dx/platform/ios/EAGLView.h"
#import "MoreLayer.h" 


@implementation Facebook

/**
 * Try to send a tweet using iOS 5 automatically
 */
+(void) tryToPostOnFacebook:(const char *)score
{
    NSLog(@"Try to post on facebook");
    SLComposeViewController  *mySocialComposer;
    UIViewController *myViewController;

    myViewController = [UIViewController alloc];
    EAGLView *view = [EAGLView sharedEGLView];
    [view addSubview:(myViewController.view)];
    
    mySocialComposer = [SLComposeViewController composeViewControllerForServiceType:SLServiceTypeFacebook];
    
    NSString *customMessage = [NSString stringWithFormat:@"This is a sample posting in iOS. My Score is %s!", score];
    
    [mySocialComposer setInitialText:customMessage];
    
    [myViewController presentViewController:mySocialComposer animated:YES completion:nil];
    
    mySocialComposer.completionHandler = ^(SLComposeViewControllerResult result)
    {
        const char *message = "";
        
        switch (result)
        {
            case SLComposeViewControllerResultCancelled:
                message = "Post Canceled";
                break;
            case SLComposeViewControllerResultDone:
                message = "Posted on Facebook";
                
            default:
                break;
        }
        UIAlertView *myalertView = [[UIAlertView alloc]initWithTitle:@"Facebook"
                                                             message:[NSString stringWithCString:message encoding:NSASCIIStringEncoding] delegate:nil cancelButtonTitle:@"Ok" otherButtonTitles:nil, nil];
        [myalertView show];
        
        MoreScene::get_instance()->updateMessageLabel(message);
        
        // Dismiss the controller
        [myViewController dismissViewControllerAnimated:true completion:^{}];
    };
}

@end
