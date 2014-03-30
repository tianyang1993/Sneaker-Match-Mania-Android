//
//  ByteManager.h
//  VivaStampede
//
//  Created by Mikhail Berrya on 12/3/13.
//
//

#ifndef __VivaStampede__ByteManager__
#define __VivaStampede__ByteManager__

#include <iostream>
#include "cocos2d.h"
USING_NS_CC;

class IAPLayer;
class CCAlertView;
class ByteManager : public CCObject{
public:
    static ByteManager       *sharedByteManager();
    CCUserDefault           *userDefaults;
    IAPLayer                *IAPView;
    int                     bytes;
    int                     wildcards;
    int                     rectifiers;
    int                     prompts;
    int                     selectedIAP;
    
//    SKProductsRequest *request;
    CCArray                 *allIAP;
	CCAlertView				*loadingView;
    
    void        initWithGame();
    void        addBytes(int noOfBytes);
    void        spendBytes(int noOfBytes);
    void        usePackItem(int thisItem , CCLabelTTF*thisLabel);
    bool        getPack(int thisPack);
    void        buyIAP(int thisIAP , IAPLayer* thisView);
    bool        getReshuffle(int cost);


};

#endif /* defined(__VivaStampede__ByteManager__) */
