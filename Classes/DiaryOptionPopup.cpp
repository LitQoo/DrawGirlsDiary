//
//  DiaryOptionPopup.cpp
//  DgDiary
//
//  Created by 사원3 on 2014. 9. 13..
//
//

#include "DiaryOptionPopup.h"
#include "TouchSuctionLayer.h"
#include "DataStorageHub.h"
#include "MyLocalization.h"
#include "KSLabelTTF.h"
#include "StyledLabelTTF.h"
#include "StarGoldData.h"
#include "CommonButton.h"
#include "CommonAnimation.h"
#include "CCMenuLambda.h"
#include "FlagSelector.h"
#include "HelpGameAppPopup.h"
#include "PasswordPopup.h"

DiaryOptionPopup* DiaryOptionPopup::create(int t_touch_priority, function<void()> t_end_func)
{
	DiaryOptionPopup* t_mup = new DiaryOptionPopup();
	t_mup->myInit(t_touch_priority, t_end_func);
	t_mup->autorelease();
	return t_mup;
}

void DiaryOptionPopup::myInit(int t_touch_priority, function<void()> t_end_func)
{
	TRACE();
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("flags.plist");
	
	is_menu_enable = false;
	
	touch_priority = t_touch_priority;
	end_func = t_end_func;
	
	CCSize screen_size = CCEGLView::sharedOpenGLView()->getFrameSize();
	float screen_scale_x = screen_size.width/screen_size.height/1.5f;
	if(screen_scale_x < 1.f)
		screen_scale_x = 1.f;
	
	gray = CCSprite::create("back_gray.png");
	gray->setOpacity(0);
	gray->setPosition(ccp(240,160));
	gray->setScaleX(screen_scale_x);
	gray->setScaleY(myDSH->ui_top/320.f/myDSH->screen_convert_rate);
	addChild(gray);
	
	TRACE();
	
	suction = TouchSuctionLayer::create(touch_priority+1);
	addChild(suction);
	
	suction->setTouchEnabled(true);
	
	m_container = CCNode::create();
	m_container->setPosition(ccp(240,160));
	addChild(m_container);
	
	back_case = CCSprite::create("popup_large_back.png");
	back_case->setPosition(ccp(0,0));
	m_container->addChild(back_case);
	
	TRACE();
	
	back_in = CCScale9Sprite::create("common_grayblue.png", CCRectMake(0, 0, 26, 26), CCRectMake(12, 12, 2, 2));
	back_in->setContentSize(CCSizeMake(251,175));
	back_in->setPosition(ccpFromSize(back_case->getContentSize()/2.f) + ccp(0,-8));
	back_case->addChild(back_in);
	
	TRACE();
	
	string title_str;
	title_str = myLoc->getLocalForKey(kMyLocalKey_diaryOptionTitle);
	
	KSLabelTTF* title_label = KSLabelTTF::create(title_str.c_str(), mySGD->getFont().c_str(), 12);
	TRACE();
	title_label->disableOuterStroke();
	title_label->setAnchorPoint(ccp(0.5f,0.5f));
	title_label->setPosition(ccpFromSize(back_case->getContentSize()/2.f) + ccp(-85, back_case->getContentSize().height/2.f-35));
	back_case->addChild(title_label);
	TRACE();
	
	//	CommonButton* close_button = CommonButton::createCloseButton(touch_priority);
	//	close_button->setPosition(ccp(back_case->getContentSize().width-25,back_case->getContentSize().height-22));
	//	close_button->setFunction([=](CCObject* sender)
	//							  {
	//								  if(!is_menu_enable)
	//									  return;
	//
	//								  is_menu_enable = false;
	//
	//								  AudioEngine::sharedInstance()->playEffect("se_button1.mp3", false);
	//
	//								  CommonAnimation::closePopup(this, m_container, gray, [=](){
	//
	//								  }, [=](){
	//									  end_func();
	//									  removeFromParent();
	//
	//								  });
	//							  });
	//	back_case->addChild(close_button);
	
	KSLabelTTF* country_title = KSLabelTTF::create(myLoc->getLocalForKey(kMyLocalKey_diaryOptionContentCountry), mySGD->getFont().c_str(), 13);
	country_title->setAnchorPoint(ccp(0,0.5f));
	country_title->setPosition(ccp(20, back_in->getContentSize().height/2.f) + ccp(0, 67));
	back_in->addChild(country_title);
	
	string flag = GraphDog::get()->t_flag;
	CCSprite* selectedFlagSpr = CCSprite::createWithSpriteFrameName(FlagSelector::getFlagString(flag).c_str());
	selectedFlagSpr->setScale(0.8f);
	selectedFlagSpr->setPosition(ccp(20, back_in->getContentSize().height/2.f) + ccp(73, 67));
	back_in->addChild(selectedFlagSpr);
	
	CCSprite* line1 = CCSprite::create("common_line.png");
	line1->setScaleX(230.f/line1->getContentSize().width);
	line1->setPosition(ccpFromSize(back_in->getContentSize()/2.f) + ccp(0,51));
	back_in->addChild(line1);
	
	KSLabelTTF* nick_title = KSLabelTTF::create(myLoc->getLocalForKey(kMyLocalKey_diaryOptionContentNickname), mySGD->getFont().c_str(), 13);
	nick_title->setAnchorPoint(ccp(0,0.5f));
	nick_title->setPosition(ccp(20, back_in->getContentSize().height/2.f) + ccp(0, 35));
	back_in->addChild(nick_title);
	
	KSLabelTTF* nick_content = KSLabelTTF::create(GraphDog::get()->t_nick.c_str(), mySGD->getFont().c_str(), 13);
	nick_content->setColor(ccORANGE);
	nick_content->setAnchorPoint(ccp(0,0.5f));
	nick_content->setPosition(ccp(20, back_in->getContentSize().height/2.f) + ccp(60, 35));
	back_in->addChild(nick_content);
	
	CCSprite* line2 = CCSprite::create("common_line.png");
	line2->setScaleX(230.f/line1->getContentSize().width);
	line2->setPosition(ccpFromSize(back_in->getContentSize()/2.f) + ccp(0,19));
	back_in->addChild(line2);
	
	KSLabelTTF* memberID_title = KSLabelTTF::create(myLoc->getLocalForKey(kMyLocalKey_diaryOptionContentMemberID), mySGD->getFont().c_str(), 13);
	memberID_title->setAnchorPoint(ccp(0,0.5f));
	memberID_title->setPosition(ccp(20, back_in->getContentSize().height/2.f) + ccp(0, 3));
	back_in->addChild(memberID_title);
	
	KSLabelTTF* memberID_content = KSLabelTTF::create(myDSH->getStringForKey(kDSH_Key_diaryMemberID).c_str(), mySGD->getFont().c_str(), 13);
	memberID_content->setColor(ccORANGE);
	memberID_content->setAnchorPoint(ccp(0,0.5f));
	memberID_content->setPosition(ccp(20, back_in->getContentSize().height/2.f) + ccp(60, 3));
	back_in->addChild(memberID_content);
	
	CCSprite* line3 = CCSprite::create("common_line.png");
	line3->setScaleX(230.f/line1->getContentSize().width);
	line3->setPosition(ccpFromSize(back_in->getContentSize()/2.f) + ccp(0,-13));
	back_in->addChild(line3);
	
	KSLabelTTF* appVersion_title = KSLabelTTF::create(myLoc->getLocalForKey(kMyLocalKey_diaryOptionContentAppVersion), mySGD->getFont().c_str(), 13);
	appVersion_title->setAnchorPoint(ccp(0,0.5f));
	appVersion_title->setPosition(ccp(20, back_in->getContentSize().height/2.f) + ccp(0, -29));
	back_in->addChild(appVersion_title);
	
	KSLabelTTF* appVersion_content = KSLabelTTF::create("1.0.3", mySGD->getFont().c_str(), 13);
	appVersion_content->setColor(ccORANGE);
	appVersion_content->setAnchorPoint(ccp(0,0.5f));
	appVersion_content->setPosition(ccp(20, back_in->getContentSize().height/2.f) + ccp(60, -29));
	back_in->addChild(appVersion_content);
	
	CCSprite* line4 = CCSprite::create("common_line.png");
	line4->setScaleX(230.f/line1->getContentSize().width);
	line4->setPosition(ccpFromSize(back_in->getContentSize()/2.f) + ccp(0,-45));
	back_in->addChild(line4);
	
	CCMenuLambda* help_menu = CCMenuLambda::create();
	help_menu->setPosition(ccp(0, 0));
	back_case->addChild(help_menu);
	help_menu->setTouchPriority(touch_priority);
	
	KSLabelTTF* passwordLock_title = KSLabelTTF::create(myLoc->getLocalForKey(kMyLocalKey_passwordLock), mySGD->getFont().c_str(), 13);
	passwordLock_title->setAnchorPoint(ccp(0,0.5f));
	passwordLock_title->setPosition(ccp(20, back_in->getContentSize().height/2.f) + ccp(0, -64));
	back_in->addChild(passwordLock_title);
	
	
	CCSprite* passwordLock_scroll = CCSprite::create("option_scroll.png");
	passwordLock_scroll->setPosition(ccp(20, back_in->getContentSize().height/2.f) + ccp(120, -64));
	back_in->addChild(passwordLock_scroll);
	
	CCSprite* n_passwordLock = CCSprite::create("whitePaper.png", CCRectMake(0, 0, 115, 30));
	n_passwordLock->setOpacity(0);
	CCSprite* s_passwordLock = CCSprite::create("whitePaper.png", CCRectMake(0, 0, 115, 30));
	s_passwordLock->setOpacity(0);
	
	CCMenuItemLambda* passwordLock_item = CCMenuItemSpriteLambda::create(n_passwordLock, s_passwordLock, [=](CCObject* sender)
																		 {
																			 if(!is_menu_enable)
																				 return;
																			 
																			 is_menu_enable = false;
																			 
																			 AudioEngine::sharedInstance()->playEffect("se_button1.mp3", false);
																			 
																			 if(!myDSH->getBoolForKey(kDSH_Key_isDiaryLocked))
																			 {
																				 CommonAnimation::closePopup(this, m_container, gray, [=](){
																					 
																				 }, [=](){
																					 
																					 PasswordPopup* t_popup = PasswordPopup::create(touch_priority-100, end_func);
																					 getParent()->addChild(t_popup, getZOrder());
																					 removeFromParent();
																				 });
																			 }
																			 else
																			 {
																				 myDSH->setBoolForKey(kDSH_Key_isDiaryLocked, !myDSH->getBoolForKey(kDSH_Key_isDiaryLocked));
																				 resetLockButton();
																				 is_menu_enable = true;
																			 }
																		 });
	passwordLock_item->setPosition(back_in->getPosition() - ccpFromSize(back_in->getContentSize()/2.f) + ccp(20, back_in->getContentSize().height/2.f) + ccp(120, -64));
	
	help_menu->addChild(passwordLock_item);
	
	lock_button_img = NULL;
	resetLockButton();
	
	
	CommonButton* t_close_button = CommonButton::createCloseButton(touch_priority);
	t_close_button->setPosition(ccp(back_case->getContentSize().width-25,back_case->getContentSize().height-22));
	t_close_button->setFunction([=](CCObject* sender)
							  {
								  if(!is_menu_enable)
									  return;
								  
								  is_menu_enable = false;
								  
								  AudioEngine::sharedInstance()->playEffect("se_button1.mp3", false);
								  
								  CommonAnimation::closePopup(this, m_container, gray, [=](){
									  
								  }, [=](){
									  end_func();
									  removeFromParent();
									  
								  });
							  });
	back_case->addChild(t_close_button);
	
	
//	CCSprite* n_help_img = CCSprite::create("subbutton_pink.png");
//	KSLabelTTF* n_help_label = KSLabelTTF::create(myLoc->getLocalForKey(kMyLocalKey_diaryOptionContentHelp), mySGD->getFont().c_str(), 12.5f);
////	n_help_label->enableOuterStroke(ccBLACK, 0.5f, 150, true);
//	n_help_label->setPosition(ccpFromSize(n_help_img->getContentSize()/2.f) + ccp(0,-1));
//	n_help_img->addChild(n_help_label);
//	
//	CCSprite* s_help_img = CCSprite::create("subbutton_pink.png");
//	s_help_img->setColor(ccGRAY);
//	KSLabelTTF* s_help_label = KSLabelTTF::create(myLoc->getLocalForKey(kMyLocalKey_diaryOptionContentHelp), mySGD->getFont().c_str(), 12.5f);
//	s_help_label->setColor(ccGRAY);
//	s_help_label->disableOuterStroke();
//	s_help_label->setPosition(ccpFromSize(s_help_img->getContentSize()/2.f) + ccp(0,-1));
//	s_help_img->addChild(s_help_label);
//	
//	CCMenuItemLambda* help_item = CCMenuItemSpriteLambda::create(n_help_img, s_help_img, [=](CCObject* sender)
//																 {
//																	 if(!is_menu_enable)
//																		 return;
//																	 
//																	 is_menu_enable = false;
//																	 
//																	 AudioEngine::sharedInstance()->playEffect("se_button1.mp3", false);
//																	 
//																	 CommonAnimation::closePopup(this, m_container, gray, [=](){
//																		 
//																	 }, [=](){
//																		 
//																		 HelpGameAppPopup* t_popup = HelpGameAppPopup::create(touch_priority, end_func);
//																		 getParent()->addChild(t_popup, getZOrder());
//																		 removeFromParent();
//																		 
//																	 });
//																 });
//	help_item->setPosition(ccp(225, 25));
//	
//	help_menu->addChild(help_item);
	
//	CCLabelTTF* r_label = CCLabelTTF::create();
//	KSLabelTTF* rightnow_label = KSLabelTTF::create(myLoc->getLocalForKey(kMyLocalKey_interlockButton), mySGD->getFont().c_str(), 13);
//	rightnow_label->disableOuterStroke();
//	r_label->addChild(rightnow_label);
//	TRACE();
//	
//	CCScale9Sprite* rightnow_back = CCScale9Sprite::create("achievement_button_success.png");
//	TRACE();
//	
//	CCControlButton* rightnow_button = CCControlButton::create(r_label, rightnow_back);
//	rightnow_button->addTargetWithActionForControlEvents(this, cccontrol_selector(DiaryOptionPopup::buttonAction), CCControlEventTouchUpInside);
//	rightnow_button->setPreferredSize(CCSizeMake(155,44));
//	rightnow_button->setPosition(ccp(0,-50));
//	m_container->addChild(rightnow_button);
//	
//	rightnow_button->setTouchPriority(touch_priority);
	
	TRACE();
	
	
	CommonAnimation::openPopup(this, m_container, gray, [=](){
	}, [=](){
		is_menu_enable = true;
	});
}

void DiaryOptionPopup::resetLockButton()
{
	if(lock_button_img)
	{
		lock_button_img->removeFromParent();
		lock_button_img = NULL;
	}
	
	lock_button_img = CCSprite::create("subbutton_purple2.png");
	back_in->addChild(lock_button_img);
	
	string inner_text;
	CCPoint img_position;
	if(!myDSH->getBoolForKey(kDSH_Key_isDiaryLocked))
	{
		inner_text = myLoc->getLocalForKey(kMyLocalKey_lightOff);
		img_position = ccp(-28,0);
	}
	else
	{
		inner_text = myLoc->getLocalForKey(kMyLocalKey_lightOn);
		img_position = ccp(28,0);
	}
	
	KSLabelTTF* inner_label = KSLabelTTF::create(inner_text.c_str(), mySGD->getFont().c_str(), 12);
	inner_label->enableOuterStroke(ccBLACK, 0.5f, 150, true);
	inner_label->setPosition(ccp(lock_button_img->getContentSize().width/2.f, lock_button_img->getContentSize().height/2.f));
	lock_button_img->addChild(inner_label);
	
	lock_button_img->setPosition(ccpAdd(ccp(20, back_in->getContentSize().height/2.f) + ccp(120, -64), img_position));
}

void DiaryOptionPopup::buttonAction(CCObject* sender, CCControlEvent t_event)
{
	if(!is_menu_enable)
		return;
	
	AudioEngine::sharedInstance()->playEffect("se_button1.mp3", false);
	
	graphdog->openOriginalApp();
	
//	if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		CCDirector::sharedDirector()->end();
}