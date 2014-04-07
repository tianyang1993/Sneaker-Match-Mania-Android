//
//  MainView.cpp
//  VivaStampede
//
//  Created by Mikhail Berrya on 11/25/13.
//
//

#include "MainView.h"
#include "HowToPlayScene.h"
#include "TokenBuy.h"
#include "MoreLayer.h"
#include "BackgroundChoosenScene.h"
#include "GameSetting.h"
#include "GameScene.h"
#include "RevMob/RevMob.h"
#include "AnalyticX.h"
#include "Define.h"
#include "JoinLayer.h"

CCScene* MainView::scene(){
    
    CCScene* scene = CCScene::create();
    MainView* layer = MainView::create();
    scene->addChild(layer);
    return scene;
    
}
bool MainView::init(){
    
    if (!CCLayer::init()) {
        return false;
    }
    size = CCDirector::sharedDirector()->getWinSize();
//    dScaleFactorX = size.width / 768, dScaleFactorY = size.height / 1024;
//    FirstGame = false;
    
//    gameSettings = GameSettings::sharedGameSettings();
   
    
    // ChartBoost SDK Integration
    
//    ChartboostX::sharedChartboostX()->setDelegate(this);
//    this->ShowChartBoost();
//    
//    
//    int first =  CCUserDefault::sharedUserDefault()->getIntegerForKey("first");
//    if (first == 1) {
//       
//        FirstGame = false;
//        
//    }else{
//        FirstGame = true;
//        CCUserDefault::sharedUserDefault()->setIntegerForKey("first", 1);
//        CCUserDefault::sharedUserDefault()->setBoolForKey("effectSound", true);
//        CCUserDefault::sharedUserDefault()->setBoolForKey("backgroundSound" , true);
//        gameSettings->setBackGround(1);
//        gameSettings->setBackGroundMusic(1);
//        gameSettings->setCurrentStatus(kTagNonStatus);
//        gameSettings->setPlayed(false);
//   
//    }
//    
//    setBackGroundView(gameSettings->getBackground());
//
//    int nType = gameSettings->getBackgroundMusic();
// 
//    if (!gameSettings->isPlayed()) {
//        gameSettings->playBackGround(nType);
//    }
//    
//    showMainView();
    
    CCSprite* backgroundView = CCSprite::create("bkg@2x.png");
    backgroundView->setPosition(ccp(size.width / 2, size.height / 2));
    float scale_x = size.width / backgroundView->getContentSize().width;
    float scale_y = size.height / backgroundView->getContentSize().height;
    backgroundView->setScaleX(scale_x);
    backgroundView->setScaleY(scale_y);
    addChild(backgroundView);

    CCSprite* spCharacter = CCSprite::create("characters@2x.png");
    spCharacter->setPosition(ccp(size.width / 2, size.height / 2));
    spCharacter->setScaleX(scale_x);
    spCharacter->setScaleY(scale_y);
    addChild(spCharacter);

    CCSprite* spLogo = CCSprite::create("loading_logo@2x.png");
    spLogo->setPosition(ccp(size.width / 2 , getY(size.height, 304, 71) * scale_y));
    spLogo->setScaleX(scale_x);
    spLogo->setScaleY(scale_y);
    addChild(spLogo);

    CCSprite* spAdBanner = CCSprite::create("ad@2x.png");
    spAdBanner->setPosition(ccp(size.width / 2 , getY(size.height, 100, 860) * scale_y));
    spAdBanner->setScaleX(scale_x);
    spAdBanner->setScaleY(scale_y);
    addChild(spAdBanner);
    
    CCMenuItemImage *facebookButton = CCMenuItemImage::create("Button_FBLOGIN@2x.png", "Button_FBLOGIN_hit@2x.png", this, menu_selector(MainView::onClickFacebookButton));
    facebookButton->setPosition(ccp(size.width / 2, getY(size.height, 132, 596)));
    facebookButton->setScaleX(scale_x);
    facebookButton->setScaleY(scale_y);

    CCMenuItemImage *guestButton = CCMenuItemImage::create("Button_GUEST@2x.png", "Button_GUEST_hit@2x.png", this, menu_selector(MainView::onClickGuestButton));
    guestButton->setPosition(ccp(size.width / 2, getY(size.height, 132, 730)));
    guestButton->setScaleX(scale_x);
    guestButton->setScaleY(scale_y);
    
    CCMenu* menu = CCMenu::create(facebookButton,guestButton,NULL);
    menu->setPosition(CCPointZero);
    addChild(menu);

    return true;
}

void MainView:: setBackGroundView(int nType){
   
    char file[0x90] = {0};
    switch (nType) {
        case 0:
            sprintf(file, "background@2x.png");
            break;
        case 1:
            sprintf(file, "iapbackground1@2x.png");
            break;
        case 2:
            sprintf(file, "iapbackground2@2x.png");
            break;
        case 3:
            sprintf(file, "iapbackground3@2x.png");
            break;
        case 4:
            sprintf(file, "iapbackground4@2x.png");
            break;

        default:
            break;
    }
    
    CCSprite* backgroundView = CCSprite::create(file);
    backgroundView->setScaleX(size.width / backgroundView->getContentSize().width);
    backgroundView->setScaleY(size.height / backgroundView->getContentSize().height);
    backgroundView->setPosition(ccp(size.width / 2, size.height / 2));
    addChild(backgroundView);

    
}
void MainView::showMainView(){
    
    
    matchLogo = CCSprite::create("zookeeper_logo@2x.png");
    matchLogo->setScaleY(matchLogo->getScaleY()* dScaleFactorY);
    matchLogo->setScaleX(matchLogo->getScaleX()* dScaleFactorX);
    matchLogo->setPosition(ccp(size.width / 2, 850* dScaleFactorY));
    addChild(matchLogo);
    
    //Primary
    primaryButton = CCMenuItemImage::create("mainmenu1@2x.png", "mainmenu1@2x.png", this, menu_selector(MainView::maintoLevels));
    primaryButton->setPosition(ccp(size.width / 2,670* dScaleFactorY));
    primaryButton->setScaleY(primaryButton->getScaleY()* dScaleFactorY);
    primaryButton->setScaleX(primaryButton->getScaleX()* dScaleFactorX);
    
    // Action
    actionButton = CCMenuItemImage::create("mainmenu2@2x.png", "mainmenu2@2x.png", this, menu_selector(MainView::maintoTime));
    actionButton->setPosition(ccp(size.width / 2-20*dScaleFactorX, 570*dScaleFactorY));
    actionButton->setScaleY(actionButton->getScaleY()* dScaleFactorY);
    actionButton->setScaleX(actionButton->getScaleX()* dScaleFactorX);
    // Endless
    infinityButton = CCMenuItemImage::create("mainmenu3@2x.png", "mainmenu3@2x.png", this, menu_selector(MainView::maintoEndless));
    infinityButton->setPosition(ccp(size.width / 2, 470*dScaleFactorY));
    infinityButton->setScaleY(infinityButton->getScaleY()* dScaleFactorY);
    infinityButton->setScaleX(infinityButton->getScaleX()* dScaleFactorX);
   
    // Store
    StoreButton = CCMenuItemImage::create("mainmenu4@2x.png", "mainmenu4@2x.png", this, menu_selector(MainView::onStore));
    StoreButton->setPosition(ccp(size.width / 2-60*dScaleFactorX, 370*dScaleFactorY));
    StoreButton->setScaleX(StoreButton->getScaleX()* dScaleFactorX);
    StoreButton->setScaleY(StoreButton->getScaleY()* dScaleFactorY);
    
    // Get a Free App
    getFreeAppButton = CCMenuItemImage::create("mainmenu5@2x.png", "mainmenu5@2x.png", this, menu_selector(MainView::getFreeApp));
    getFreeAppButton->setPosition(ccp(size.width / 2, 270*dScaleFactorY));
    getFreeAppButton->setScaleY(getFreeAppButton->getScaleY()* dScaleFactorY);
    getFreeAppButton->setScaleX(getFreeAppButton->getScaleX()* dScaleFactorX);
    // More
    moreButton = CCMenuItemImage::create("mainmenu6@2x.png", "mainmenu6@2x.png", this, menu_selector(MainView::maintoMore));
    moreButton->setPosition(ccp(size.width / 2 + 250*dScaleFactorX, 170*dScaleFactorY));
    moreButton->setScaleY(moreButton->getScaleY()* dScaleFactorY);
    moreButton->setScaleX(moreButton->getScaleX()* dScaleFactorX);
    //How to play
    howToButton = CCMenuItemImage::create("newhowtoplay@2x.png", "newhowtoplay@2x.png", this, menu_selector(MainView::howToPlay));
    howToButton->setPosition(ccp(size.width / 2 - 200*dScaleFactorX, 170*dScaleFactorY));
    howToButton->setScaleX(howToButton->getScaleX()*dScaleFactorX);
    howToButton->setScaleY(howToButton->getScaleY()*dScaleFactorY);
    // Choose Backgroun Button
    engageButton = CCMenuItemImage::create("choose_background@2x.png", "choose_background@2x.png", this, menu_selector(MainView::maintomoreBackgrounds));
    engageButton->setPosition(ccp(size.width / 2+ 280*dScaleFactorX, 570*dScaleFactorY));
    engageButton->setScaleX(engageButton->getScaleX()*dScaleFactorX);
    engageButton->setScaleY(engageButton->getScaleY()*dScaleFactorY*0.9);
    
    
    //    PHNotificationView *notifView=[[[PHNotificationView alloc] initWithApp:kPlayHavenID
    //                                                                    secret:kPlayHeavenSecret
    //                                                                 placement:@"more_games"] autorelease];
    //    [moreButton addSubview:notifView];
    //    notifView.center=CGPointMake(16, 16);
    //    notifView.tag=playhavenNotificationViewTag;
    //    [notifView refresh];
    
    
    
    
    // Zookeeper Image
    zookeeperImage = CCSprite::create("zookeep@2x.png");
    zookeeperImage->setScaleX(zookeeperImage->getScaleX()*dScaleFactorX);
    zookeeperImage->setScaleY(zookeeperImage->getScaleY()*dScaleFactorY);
    zookeeperImage->setPosition(ccp(90 * dScaleFactorX, 370* dScaleFactorY));
    addChild(zookeeperImage);
    
    
    
    
    CCMenu* menu = CCMenu::create(primaryButton,actionButton,howToButton,StoreButton,engageButton,infinityButton,getFreeAppButton,moreButton,NULL);
    menu->setPosition(CCPointZero);
    addChild(menu);
    
}

void MainView::maintoLevels(CCObject *pSender){
    
    gameSettings->setGameMode(kTagPrimary);
    AnalyticX::flurryLogEvent("Primary Mode Play");
    if (FirstGame == true) {
        CCDirector::sharedDirector()->replaceScene(HowToPlayScene::scene());
    }else{
   
        CCDirector::sharedDirector()->replaceScene(GameScene::scene());
    }
    
    
}
void MainView::maintoTime(CCObject *pSender){
    
    gameSettings->setGameMode(kTagTime);
    AnalyticX::flurryLogEvent("Action Mode Play");
    if (FirstGame == true) {
        CCDirector::sharedDirector()->replaceScene(HowToPlayScene::scene());
    }else{
        
        CCDirector::sharedDirector()->replaceScene(GameScene::scene());
    }

     
    
}
void MainView::maintoEndless(CCObject *pSender){
    
    gameSettings->setGameMode(kTagEndress);
    AnalyticX::flurryLogEvent("Infinity Mode Play");
    if (FirstGame == true) {
        CCDirector::sharedDirector()->replaceScene(HowToPlayScene::scene());
    }else{
        
        CCDirector::sharedDirector()->replaceScene(GameScene::scene());
    }

     
}

void MainView::onStore(CCObject *pSender) {
    
    gameSettings->setSuperType(2);
    AnalyticX::flurryLogEvent("Store View Visit");
    CCDirector::sharedDirector()->replaceScene(TokenBuy::scene());
   
}
void MainView::getFreeApp(CCObject *pSender){
    
    CCLOG("GetFreeGame");
    revmob::RevMob *revmob = revmob::RevMob::SharedInstance();
    revmob->ShowPopup();

    
}
void MainView::maintomoreBackgrounds(CCObject *pSender){
    
    CCDirector::sharedDirector()->replaceScene(BackgroundChoosenScene::scene());
}
void MainView::maintoMore(CCObject *pSender){
    
    AnalyticX::flurryLogEvent("More View Visit");
    CCDirector::sharedDirector()->replaceScene(MoreScene::scene());
    
    
}
void MainView::howToPlay(CCObject *pSender){
    
    gameSettings->setMoreToHowToPlayerScene(10);
   CCDirector::sharedDirector()->replaceScene(HowToPlayScene::scene());
}

void MainView::onClickFacebookButton(){
    
}

void MainView::onClickGuestButton(){
    
    CCDirector::sharedDirector()->replaceScene(CCTransitionCrossFade::create(0.5f, JoinLayer::scene()));

}

# pragma mark - ChartBoost SDK Integration
//\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\\/\/\/\/\/\/\/\/\/\/\/\/\/\\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\\/\/\//\\/\/\/\/\/\/\/\/\/\/\/\/\/\/\\/\/

void MainView::ShowChartBoost()
{
    ChartboostX::sharedChartboostX()->hasCachedInterstitial();
//    ChartboostX::sharedChartboostX()->showInterstitial();
    
    ChartboostX::sharedChartboostX()->cacheMoreApps();
}

bool MainView::shouldDisplayInterstitial(const char* location)
{
    CCLog("about to display interstitial at location %s", location);
    
    return !m_interstitialShowed;
}

void MainView::didCacheInterstitial(const char* location)
{
    CCLog("did cache interstitial at location %s", location);
}

void MainView::didFailToLoadInterstitial(const char* location)
{
    CCLog("did fail to load interstitial at location %s", location);
    
    
}

void MainView::didCloseInterstitial(const char* location)
{
    CCLog("did close interstitial at location %s", location);
    m_interstitialShowed = true;
    
}

void MainView::didClickInterstitial(const char* location)
{
    CCLog("did click interstitial at location %s", location);
    m_interstitialShowed = true;
     
}

//\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\\/\/\/\/\/\/\/\/\/\/\/\/\/\\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\\/\/\//\\/\/\/\/\/\/\/\/\/\/\/\/\/\/\\/\/


