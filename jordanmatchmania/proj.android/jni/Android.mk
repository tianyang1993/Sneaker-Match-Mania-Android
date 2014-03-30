LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := game_shared

LOCAL_MODULE_FILENAME := libgame

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/IntroLayer.cpp \
                   ../../Classes/MainView.cpp \
                   ../../Classes/GameScene.cpp \
                   ../../Classes/HowToPlayScene.cpp \
                   ../../Classes/TokenBuy.cpp \
                   ../../Classes/MoreLayer.cpp \
                   ../../Classes/BackgroundChoosenScene.cpp \
                   ../../Classes/GameSetting.cpp \
                   ../../Classes/InfoSlider1.cpp \
                   ../../Classes/InfoSlider2.cpp \
                   ../../Classes/InfoSlider3.cpp \
                   ../../Classes/InfoSlider4.cpp \
                   ../../Classes/InfoSlider5.cpp \
                   ../../Classes/InfoSlider6.cpp \
                   ../../Classes/SyntaxSymbol.cpp \
                   ../../Classes/SymbolManager.cpp \
                   ../../Classes/SymbolItem.cpp \
                   ../../Classes/PauseLayer.cpp \
                   ../../Classes/GameEngineLayer.cpp \
                   ../../Classes/GameItem.cpp \
                   ../../Classes/GameOver.cpp \
                   ../../Classes/CCAlertView.cpp \
                   ../../Classes/LevelCompleted.cpp \
                   ../../Classes/StatusManager.cpp \
                   ../../Classes/ValuesManager.cpp \
                   ../../Classes/ByteManager.cpp \
                   ../../Classes/IAPLayer.cpp \
                   ../../Classes/GetTokens.cpp \
                   ../../Classes/AnalyticX.cpp \
                   ../../Classes/AnalyticXStringUtilAndroid.cpp \
                   ../../Classes/RevMob/RevMob.cpp \
                   ../../Classes/RevMob/RevMobAds_Android.cpp \
                   ../../Classes/JNICalls/InterfaceJNI.cpp \
                   ../../Classes/Chartboost/ChartboostX_android.cpp \
                   ../../Classes/Chartboost/ChartboostXJni.cpp 
                   
LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes                   

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static cocosdenshion_static cocos_extension_static
            
include $(BUILD_SHARED_LIBRARY)

$(call import-module,CocosDenshion/android) \
$(call import-module,cocos2dx) \
$(call import-module,extensions) \
$(call import-module,libwebsockets/android)
