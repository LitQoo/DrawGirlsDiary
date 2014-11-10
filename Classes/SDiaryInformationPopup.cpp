//
//  SDiaryInformationPopup.cpp
//  DgDiary
//
//  Created by 사원3 on 2014. 10. 7..
//
//

#include "SDiaryInformationPopup.h"
#include "TouchSuctionLayer.h"
#include "KSUtil.h"
#include "KSLabelTTF.h"
#include "DataStorageHub.h"
#include "MyLocalization.h"
#include "AudioEngine.h"
#include "FormSetter.h"
#include "StarGoldData.h"
#include "StyledLabelTTF.h"
#include "CommonAnimation.h"
#include "StageImgLoader.h"

SDiaryInformationPopup* SDiaryInformationPopup::create(int t_touch_priority, function<void()> t_end_func)
{
	SDiaryInformationPopup* t_mup = new SDiaryInformationPopup();
	t_mup->myInit(t_touch_priority, t_end_func);
	t_mup->autorelease();
	return t_mup;
}

void SDiaryInformationPopup::myInit(int t_touch_priority, function<void()> t_end_func)
{
	startFormSetter(this);
	
	mySGD->is_new_puzzle_card = false;
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
	
	back_case = CCSprite::create("popup_large_back.png");
	back_case->setPosition(ccp(0,0));
	m_container->addChild(back_case);
	setFormSetter(back_case);
	
	CCScale9Sprite* back_in = CCScale9Sprite::create("common_grayblue.png", CCRectMake(0, 0, 26, 26), CCRectMake(12, 12, 2, 2));
	back_in->setContentSize(CCSizeMake(251,160));
	back_in->setPosition(ccpFromSize(back_case->getContentSize()/2.f) + ccp(0,-22.5f));
	back_case->addChild(back_in);
	setFormSetter(back_in);
	
	KSLabelTTF* title_label = KSLabelTTF::create(myLoc->getLocalForKey(kMyLocalKey_sdiaryInformationTitle), mySGD->getFont().c_str(), 12);
	title_label->disableOuterStroke();
	title_label->setAnchorPoint(ccp(0.5f,0.5f));
	title_label->setPosition(ccpFromSize(back_case->getContentSize()/2.f) + ccp(-85, back_case->getContentSize().height/2.f-35));
	back_case->addChild(title_label);
	
	KSLabelTTF* sub_title_label = KSLabelTTF::create(myLoc->getLocalForKey(kMyLocalKey_sdiaryInformationSubTitle), mySGD->getFont().c_str(), 11);
	sub_title_label->enableOuterStroke(ccBLACK, 0.3f, 60, true);
	sub_title_label->setAnchorPoint(ccp(0.5f,0.5f));
	sub_title_label->setPosition(ccpFromSize(back_case->getContentSize()/2.f) + ccp(0, back_case->getContentSize().height/2.f-62));
	back_case->addChild(sub_title_label);
	
	CommonButton* close_button = CommonButton::createCloseButton(touch_priority);
	close_button->setPosition(ccp(back_case->getContentSize().width-25,back_case->getContentSize().height-22));
	close_button->setFunction([=](CCObject* sender)
							  {
								  if(!is_menu_enable)
									  return;
								  
								  is_menu_enable = false;
								  
								  AudioEngine::sharedInstance()->playEffect("se_buy.mp3", false);
								  
								  CommonAnimation::closePopup(this, m_container, gray, [=](){
									  
								  }, [=](){
									  end_func();
									  removeFromParent();
									  
								  });
							  });
	back_case->addChild(close_button);
	
		
	StyledLabelTTF* content_label = StyledLabelTTF::create(myLoc->getLocalForKey(kMyLocalKey_sdiaryInformationContent), mySGD->getFont().c_str(), 12, 999, StyledAlignment::kCenterAlignment);
	content_label->setAnchorPoint(ccp(0.5f,0.5f));
	content_label->setPosition(ccpFromSize(back_in->getContentSize() / 2.f) + ccp(0,10));
	back_in->addChild(content_label);
//	
//	CCSprite* title_img = CCSprite::create("temp_title_name.png");
//	title_img->setScale(0.25f);
//	title_img->setPosition(ccp(back_case->getContentSize().width-50, 40));
//	back_case->addChild(title_img);
	
	CommonAnimation::openPopup(this, m_container, gray, [=](){
	}, [=](){
		is_menu_enable = true;
	});
}