//
//  DdmkLinkPopup.cpp
//  DgDiary
//
//  Created by 사원3 on 2014. 12. 22..
//
//

#include "DdmkLinkPopup.h"
#include "TouchSuctionLayer.h"
#include "DataStorageHub.h"
#include "MyLocalization.h"
#include "KSLabelTTF.h"
#include "StyledLabelTTF.h"
#include "StarGoldData.h"
#include "CommonButton.h"
#include "CommonAnimation.h"
#include "ASPopupView.h"

DdmkLinkPopup* DdmkLinkPopup::create(int t_touch_priority, function<void()> t_end_func, function<void()> t_success_func)
{
	DdmkLinkPopup* t_mup = new DdmkLinkPopup();
	t_mup->myInit(t_touch_priority, t_end_func, t_success_func);
	t_mup->autorelease();
	return t_mup;
}

void DdmkLinkPopup::myInit(int t_touch_priority, function<void()> t_end_func, function<void()> t_success_func)
{
	TRACE();
	is_menu_enable = false;
	
	touch_priority = t_touch_priority;
	end_func = t_end_func;
	success_func = t_success_func;
	
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
	back_in->setContentSize(CCSizeMake(251,68));
	back_in->setPosition(ccpFromSize(back_case->getContentSize()/2.f) + ccp(0,9));
	back_case->addChild(back_in);
	
	
	KSLabelTTF* title_label = KSLabelTTF::create(myLoc->getLocalForKey(kMyLocalKey_link), mySGD->getFont().c_str(), 12);
	TRACE();
	title_label->disableOuterStroke();
	title_label->setAnchorPoint(ccp(0.5f,0.5f));
	title_label->setPosition(ccpFromSize(back_case->getContentSize()/2.f) + ccp(-85, back_case->getContentSize().height/2.f-35));
	back_case->addChild(title_label);
	TRACE();
	
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
									  end_func();
									  removeFromParent();
									  
								  });
							  });
	back_case->addChild(close_button);
	
	StyledLabelTTF* content_label = StyledLabelTTF::create(myLoc->getLocalForKey(kMyLocalKey_ddmkLinkMent), mySGD->getFont().c_str(), 11, 999, StyledAlignment::kCenterAlignment);
	content_label->setAnchorPoint(ccp(0.5f,0.5f));
	content_label->setPosition(ccpFromSize(back_in->getContentSize() / 2.f));
	back_in->addChild(content_label);
	TRACE();
	
	
	CCLabelTTF* r_label = CCLabelTTF::create();
	KSLabelTTF* rightnow_label = KSLabelTTF::create(myLoc->getLocalForKey(kMyLocalKey_goInputLinkCode), mySGD->getFont().c_str(), 11);
	rightnow_label->disableOuterStroke();
	r_label->addChild(rightnow_label);
	TRACE();
	
	CCScale9Sprite* rightnow_back = CCScale9Sprite::create("achievement_button_success.png");
	TRACE();
	
	CCControlButton* rightnow_button = CCControlButton::create(r_label, rightnow_back);
	rightnow_button->addTargetWithActionForControlEvents(this, cccontrol_selector(DdmkLinkPopup::buttonAction), CCControlEventTouchUpInside);
	rightnow_button->setTag(1);
	rightnow_button->setPreferredSize(CCSizeMake(101,44));
	rightnow_button->setPosition(ccp(-60,-50));
	m_container->addChild(rightnow_button);
	
	rightnow_button->setTouchPriority(touch_priority);
	
	CCLabelTTF* r2_label = CCLabelTTF::create();
	KSLabelTTF* rightnow2_label = KSLabelTTF::create(myLoc->getLocalForKey(kMyLocalKey_goGameAppDown), mySGD->getFont().c_str(), 11);
	rightnow2_label->disableOuterStroke();
	r2_label->addChild(rightnow2_label);
	TRACE();
	
	CCScale9Sprite* rightnow2_back = CCScale9Sprite::create("achievement_button_success.png");
	TRACE();
	
	CCControlButton* rightnow2_button = CCControlButton::create(r2_label, rightnow2_back);
	rightnow2_button->addTargetWithActionForControlEvents(this, cccontrol_selector(DdmkLinkPopup::buttonAction), CCControlEventTouchUpInside);
	rightnow2_button->setTag(2);
	rightnow2_button->setPreferredSize(CCSizeMake(101,44));
	rightnow2_button->setPosition(ccp(60,-50));
	m_container->addChild(rightnow2_button);
	
	rightnow2_button->setTouchPriority(touch_priority);
	
	TRACE();
	
	
	CommonAnimation::openPopup(this, m_container, gray, [=](){
	}, [=](){
		is_menu_enable = true;
	});
}

void DdmkLinkPopup::buttonAction(CCObject* sender, CCControlEvent t_event)
{
	if(!is_menu_enable)
		return;
	
	is_menu_enable = false;
	
	AudioEngine::sharedInstance()->playEffect("se_button1.mp3", false);
	
	int t_tag = ((CCNode*)sender)->getTag();
	
	if(t_tag == 1)
	{
		CommonAnimation::closePopup(this, m_container, gray, [=](){
			
		}, [=](){
			success_func();
			removeFromParent();
		});
	}
	else if(t_tag == 2)
	{
		myHSP->openUrl(graphdog->getGameDownUrl());
		
		addChild(KSTimer::create(0.1f, [=]()
								 {
									 CCDirector::sharedDirector()->end();
								 }));
	}
}
