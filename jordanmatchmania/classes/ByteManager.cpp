//
//  ByteManager.cpp
//  VivaStampede
//
//  Created by Mikhail Berrya on 12/3/13.
//
//

#include "ByteManager.h"
#include "IAPLayer.h"
#include "ValuesManager.h"
#include "CCAlertView.h"
#include "SymbolItem.h"
#include "SymbolManager.h"
#include "AppDelegate.h"


ByteManager* ByteManager::sharedByteManager(){
    
    static ByteManager* temp = NULL;
    if (temp == NULL) {
        temp = new ByteManager();
    }
    
    return  temp;
    
}
void ByteManager:: initWithGame(){
    
    if (this != NULL) {
        userDefaults = CCUserDefault::sharedUserDefault();
        bytes = userDefaults->getIntegerForKey("bytes");
        wildcards = userDefaults->getIntegerForKey("wildcards");
        rectifiers = userDefaults->getIntegerForKey("rectifiers");
        prompts = userDefaults->getIntegerForKey("prompts");
        selectedIAP = -1;
        
        int first =  CCUserDefault::sharedUserDefault()->getIntegerForKey("first");
      
        if (first == 1) {
            if (bytes == 0) bytes = 0;
            if (wildcards == 0) wildcards = 2;
            if (rectifiers == 0) rectifiers = 2;
            if (prompts== 0) prompts = 2;

        }
        
        
        
    }
    return;
}
void ByteManager::addBytes(int noOfBytes) {
   
    bytes += noOfBytes;
    CCUserDefault::sharedUserDefault()->setIntegerForKey("bytes", bytes);
    
}

void ByteManager::spendBytes(int noOfBytes){
    bytes -= noOfBytes;
    CCUserDefault::sharedUserDefault()->setIntegerForKey("bytes", bytes);
}

bool ByteManager::getPack(int thisPack) {
    bool canGet = true;
    int packCosts[6] = {250 , 500 , 500 , 1000 ,1000,1500};
    
    if (packCosts[thisPack] <= bytes) {
        spendBytes(packCosts[thisPack]); 
        switch (thisPack) {
            case 0:
                prompts += 5;
                CCUserDefault::sharedUserDefault()->setIntegerForKey("prompts", prompts); 
                break;
            case 1:
                prompts += 10;
                CCUserDefault::sharedUserDefault()->setIntegerForKey("prompts", prompts);  
                break;
            case 2:
                wildcards += 5;
                CCUserDefault::sharedUserDefault()->setIntegerForKey("wildcards", wildcards);  
                break;
            case 3:
                wildcards += 10;
                CCUserDefault::sharedUserDefault()->setIntegerForKey("wildcards", wildcards); 
                break;
            case 4:
                rectifiers += 5;
                CCUserDefault::sharedUserDefault()->setIntegerForKey("rectifiers", rectifiers); 
                break;
            case 5:
                rectifiers += 10;
               CCUserDefault::sharedUserDefault()->setIntegerForKey("rectifiers", rectifiers); 
                break;
            default:
                break;
        }
    }
    else {
        canGet = false;
    }
     
    return canGet;
}

bool ByteManager::getReshuffle(int cost) {
    bool canGet = true;
    if (cost <= bytes)
        spendBytes(cost);
    else canGet = false;
        
        return canGet;
}

// This is one of the naming conventions
void ByteManager::usePackItem(int thisItem , CCLabelTTF*thisLabel){
   /* wildCards     ==1,
      rectifiers    == 2,
      prompts       ==3
    */
    char file[0x90] = {0};
    if (thisItem ==1){
        wildcards--;
        userDefaults->setIntegerForKey("wildcards", wildcards);
        sprintf(file, "x%d" , wildcards);
         
    }
    else if (thisItem == 2) {
        rectifiers--;
        userDefaults->setIntegerForKey("rectifiers", rectifiers);
        sprintf(file, "x%d" , rectifiers);
         
        
    }
    else if (thisItem == 3) {
        prompts--;
        userDefaults->setIntegerForKey("prompts", prompts);
        sprintf(file, "x%d" , prompts);
        
    }
    
    thisLabel->setString(file);
}

void ByteManager:: buyIAP(int thisIAP,IAPLayer* thisView) {
//    AppDelegate *appDelegate =(AppDelegate*)CCApplication::sharedApplication(); //= (AppDelegate *)[[UIApplication sharedApplication] delegate];
//    switch (thisIAP) {
//        case 0:
//            appDelegate purchase(IAP_500_BYTES_PACK);
//            break;
//        case 1:
//            [appDelegate purchase:IAP_1000_BYTES_PACK];
//            break;
//        case 2:
//            [appDelegate purchase:IAP_3000_BYTES_PACK];
//            break;
//        case 3:
//            [appDelegate purchase:IAP_7500_BYTES_PACK];
//            break;
//        case 4:
//            [appDelegate purchase:IAP_20000_BYTES_PACK];
//            break;
//        case 5:
//            [appDelegate purchase:IAP_50000_BYTES_PACK];
//            break;
//        default:
//            break;
//    }
}

//void ByteManager:: provideContent(CCString productIdentifier){
//    if ([productIdentifier isEqualToString:IAP_1000_BYTES_PACK]) {
//        [self addBytes:1000];
//    }
//    else if ([productIdentifier isEqualToString:IAP_3000_BYTES_PACK]) {
//        [self addBytes:3000];
//    }
//    else if ([productIdentifier isEqualToString:IAP_7500_BYTES_PACK]) {
//        [self addBytes:7500];
//    }
//    else if ([productIdentifier isEqualToString:IAP_20000_BYTES_PACK]) {
//        [self addBytes:20000];
//    }
//    else if ([productIdentifier isEqualToString:IAP_50000_BYTES_PACK]) {
//        [self addBytes:50000];
//    }
//    [IAPView.viewController.soundController playSound:@"IAP"];
//    [IAPView backToMotherView];
//    self.IAPView = nil;
//}
//

#pragma SKProduct

//void ByteManager::requestProductDataFromIAPView(IAPLayer* thisView) {
//    self.IAPView = thisView;
//    NSSet *allIAPIdentifiers = [NSSet setWithObjects:
//                                IAP_500_BYTES_PACK,
//                                IAP_1000_BYTES_PACK,
//                                IAP_3000_BYTES_PACK
//                                IAP_7500_BYTES_PACK
//                                IAP_20000_BYTES_PACK
//                                IAP_50000_BYTES_PACK,
//                                nil];
//    self.request = [[SKProductsRequest alloc] initWithProductIdentifiers:allIAPIdentifiers];
//    request.delegate = ((AppDelegate *)[[UIApplication sharedApplication] delegate]).observer;
//    [request start];
//    NSLog(@"requesting products...");
//}

//void productsRequest(SKProductsRequest *)request didReceiveResponse:(SKProductsResponse *)response {
//    NSLog(@"product response received...");
//    self.allIAP = response.products;
//    self.request = nil;
//    [IAPView showIAP];
//}
//
//- (void)request:(SKRequest *)request didFailWithError:(NSError *)error {
//    selectedIAP = -1;
//    [IAPView disconnect];
//    self.IAPView = nil;
//}
//
#pragma SKPayment

//- (void)buyProductIdentifier:(NSString *)productIdentifier {
//    SKPayment *payment = [SKPayment paymentWithProductIdentifier:productIdentifier];
//    [[SKPaymentQueue defaultQueue] addPayment:payment];
//}
//
//- (void)paymentQueue:(SKPaymentQueue *)queue updatedTransactions:(NSArray *)transactions {
//    for (SKPaymentTransaction *transaction in transactions) {
//        switch (transaction.transactionState) {
//            case SKPaymentTransactionStatePurchased:
//                [self completeTransaction:transaction];
//                break;
//            case SKPaymentTransactionStateFailed:
//                [self failedTransaction:transaction];
//                break;
//            default:
//                [loadingView dismissWithClickedButtonIndex:0 animated:NO];
//                break;
//        }
//    }
//}
//
//- (void)completeTransaction:(SKPaymentTransaction *)transaction {
//	[loadingView dismissWithClickedButtonIndex:0 animated:NO];
//    NSLog(@"transaction complete...");
//    [self provideContent:transaction.payment.productIdentifier];
//    [[SKPaymentQueue defaultQueue] finishTransaction:transaction];
//}
//
//- (void)failedTransaction:(SKPaymentTransaction *)transaction {
//	[loadingView dismissWithClickedButtonIndex:0 animated:NO];
//    NSLog(@"transaction failed...");
//    // show error;
//    [[SKPaymentQueue defaultQueue] finishTransaction:transaction];
//}

