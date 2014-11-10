//
//  HelpGameAppPopup.cpp
//  DgDiary
//
//  Created by 사원3 on 2014. 9. 13..
//
//

#include "HelpGameAppPopup.h"
#include "TouchSuctionLayer.h"
#include "DataStorageHub.h"
#include "MyLocalization.h"
#include "KSLabelTTF.h"
#include "StyledLabelTTF.h"
#include "StarGoldData.h"
#include "CommonButton.h"
#include "CommonAnimation.h"
#include "DiaryOptionPopup.h"

HelpGameAppPopup* HelpGameAppPopup::create(int t_touch_priority, function<void()> t_end_func)
{
	HelpGameAppPopup* t_mup = new HelpGameAppPopup();
	t_mup->myInit(t_touch_priority, t_end_func);
	t_mup->autorelease();
	return t_mup;
}

void HelpGameAppPopup::myInit(int t_touch_priority, function<void()> t_end_func)
{
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
	
	suction = TouchSuctionLayer::create(touch_priority+1);
	addChild(suction);
	
	suction->setTouchEnabled(true);
	
	m_container = CCNode::create();
	m_container->setPosition(ccp(240,160));
	addChild(m_container);
	
	back_case = CCSprite::create("popup_small_back.png");
	back_case->setPosition(ccp(0,0));
	m_container->addChild(back_case);
	
	CCScale9Sprite* back_in = CCScale9Sprite::create("common_grayblue.png", CCRectMake(0, 0, 26, 26), CCRectMake(12, 12, 2, 2));
	back_in->setContentSize(CCSizeMake(251,65));
	back_in->setPosition(ccpFromSize(back_case->getContentSize()/2.f) + ccp(0,10));
	back_case->addChild(back_in);
	
	string title_str, content_str;
	title_str = myLoc->getLocalForKey(kMyLocalKey_helpPopupTitle);
	content_str = myLoc->getLocalForKey(kMyLocalKey_helpPopupContent);
	
	KSLabelTTF* title_label = KSLabelTTF::create(title_str.c_str(), mySGD->getFont().c_str(), 12);
	title_label->disableOuterStroke();
	title_label->setAnchorPoint(ccp(0.5f,0.5f));
	title_label->setPosition(ccpFromSize(back_case->getContentSize()/2.f) + ccp(-85, back_case->getContentSize().height/2.f-35));
	back_case->addChild(title_label);
	
	CommonButton* close_button = CommonButton::createCloseButton(touch_priority);
	close_button->setPosition(ccp(back_case->getContentSize().width-25,back_case->getContentSize().height-22));
	close_button->setFunction([=](CCObject* sender)
							  {
								  if(!is_menu_enable)
									  return;
								  
								  is_menu_enable = false;
								  
								  AudioEngine::sharedInstance()->playEffect("se_button1.mp3", false);
								  
								  CommonAnimation::closePopup(this, m_container, gray, [=](){
									  
								  }, [=](){
									  DiaryOptionPopup* t_popup = DiaryOptionPopup::create(touch_priority, end_func);
									  getParent()->addChild(t_popup, getZOrder());
									  removeFromParent();
									  
								  });
							  });
	back_case->addChild(close_button);
	
	StyledLabelTTF* content_label = StyledLabelTTF::create(content_str.c_str(), mySGD->getFont().c_str(), 12, 999, StyledAlignment::kCenterAlignment);
	content_label->setAnchorPoint(ccp(0.5f,0.5f));
	content_label->setPosition(ccpFromSize(back_in->getContentSize() / 2.f));
	back_in->addChild(content_label);
	
	
	CCLabelTTF* r_label = CCLabelTTF::create();
	KSLabelTTF* rightnow_label = KSLabelTTF::create(myLoc->getLocalForKey(kMyLocalKey_helpPopupButton), mySGD->getFont().c_str(), 12);
	rightnow_label->disableOuterStroke();
	r_label->addChild(rightnow_label);
	
	CCScale9Sprite* rightnow_back = CCScale9Sprite::create("achievement_button_success.png");
	
	CCControlButton* rightnow_button = CCControlButton::create(r_label, rightnow_back);
	rightnow_button->addTargetWithActionForControlEvents(this, cccontrol_selector(HelpGameAppPopup::buttonAction), CCControlEventTouchUpInside);
	rightnow_button->setPreferredSize(CCSizeMake(131,44));
	rightnow_button->setPosition(ccp(0,-50));
	m_container->addChild(rightnow_button);
	
	rightnow_button->setTouchPriority(touch_priority);
	
	
	CommonAnimation::openPopup(this, m_container, gray, [=](){
	}, [=](){
		is_menu_enable = true;
	});
}

void HelpGameAppPopup::buttonAction(CCObject* sender, CCControlEvent t_event)
{
	if(!is_menu_enable)
		return;
	
	AudioEngine::sharedInstance()->playEffect("se_button1.mp3", false);
	
	graphdog->openOriginalApp();
	
//	if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		CCDirector::sharedDirector()->end();
}