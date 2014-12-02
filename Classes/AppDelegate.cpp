#include "AppDelegate.h"
#include "DataStorageHub.h"
#include "StarGoldData.h"
#include "ServerDataSave.h"
//#include "FormSetter.h"
#include "TitleRenewal.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

static cocos2d::CCSize designResolutionSize = cocos2d::CCSizeMake(480, 320);

bool AppDelegate::applicationDidFinishLaunching() {
	
	if(myDSH->getIntegerForKey(kDSH_Key_clientVersion) < mySGD->client_version)
	{
		SaveData::sharedObject()->resetAllData();
		myDSH->removeCache();
		mySDS->removeCache();
		myDSH->setIntegerForKey(kDSH_Key_clientVersion, mySGD->client_version);
	}
	
//	FormSetter::get()->setEnabledRemocon(false);
	
	graphdog = GraphDog::get();
	GraphDog::get()->setup("drawgirls_tstore", "12345678","", "2");
	GraphDog::get()->setServerURL(hspConnector::get()->getServerAddress());;
	
	// initialize director
    CCDirector* pDirector = CCDirector::sharedDirector();
    CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();

    pDirector->setOpenGLView(pEGLView);
	pDirector->setProjection(kCCDirectorProjection2D);
	
	pEGLView->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, kResolutionFixedWidth);
	
	CCSize screen_size = pEGLView->getFrameSize();
	myDSH->ui_top = 480.f*screen_size.height/screen_size.width;
	myDSH->ui_bottom = 0;
	myDSH->ui_center_y = myDSH->ui_top/2.f;
	myDSH->puzzle_ui_top = 320.f;
	
	float screen_rate = screen_size.width/screen_size.height;
	if(screen_rate > 1.5f)
	{
		myDSH->screen_convert_rate = (designResolutionSize.width/designResolutionSize.height)/screen_rate;
		myDSH->ui_zero_point = CCPointZero;
		
		float t_value = screen_size.height/designResolutionSize.height;
		myDSH->mult_point.x = screen_size.width/t_value/designResolutionSize.width;
		myDSH->add_point.x = -(screen_size.width-designResolutionSize.width*t_value)/2.f/t_value;
		
		myDSH->mult_point.y = screen_size.width/designResolutionSize.width/t_value;
		myDSH->add_point.y = 0.f;
	}
	else if(screen_rate < 1.5f)
	{
		myDSH->screen_convert_rate = 1.f;
		myDSH->ui_zero_point = ccp(0,(screen_size.height*(designResolutionSize.width/screen_size.width) - designResolutionSize.height)/2.f);
		myDSH->puzzle_ui_top = myDSH->ui_top;
		
		myDSH->mult_point.x = 1.f;
		myDSH->add_point.x = 0.f;
		
		myDSH->mult_point.y = 1.f;
		myDSH->add_point.y = -(screen_size.height*(designResolutionSize.width/screen_size.width) - designResolutionSize.height)/2.f;
	}
	else
	{
		myDSH->screen_convert_rate = 1.f;
		myDSH->ui_zero_point = CCPointZero;
		
		myDSH->mult_point.x = 1.f;
		myDSH->add_point.x = 0.f;
		
		myDSH->mult_point.y = 1.f;
		myDSH->add_point.y = 0.f;
	}
	
	CCPoint ui_touch_convert = ccp(0,screen_size.height*(designResolutionSize.width/screen_size.width) - designResolutionSize.height);
	myDSH->ui_touch_convert = ui_touch_convert;
	
	CCFileUtils::sharedFileUtils()->addSearchPath("res_img");
	CCFileUtils::sharedFileUtils()->addSearchPath("res_img/resources-iphonehd");
	CCFileUtils::sharedFileUtils()->addSearchPath("res_sound");
	CCFileUtils::sharedFileUtils()->addSearchPath("fonts");
	
	pDirector->setContentScaleFactor(2.0);
	
    // turn on display FPS
    pDirector->setDisplayStats(false);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
    CCScene *pScene = TitleRenewalScene::scene();

    // run
    pDirector->runWithScene(pScene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    CCDirector::sharedDirector()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
	SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
	SimpleAudioEngine::sharedEngine()->pauseAllEffects();
	
	CCDirector::sharedDirector()->end();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    CCDirector::sharedDirector()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
	SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
	SimpleAudioEngine::sharedEngine()->resumeAllEffects();
	
//	CCDirector::sharedDirector()->replaceScene(TitleRenewalScene::scene());
}
