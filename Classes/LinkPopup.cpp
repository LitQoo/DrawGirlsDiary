//
//  LinkPopup.cpp
//  DgDiary
//
//  Created by 사원3 on 2014. 11. 14..
//
//

#include "LinkPopup.h"
#include "TouchSuctionLayer.h"
#include "DataStorageHub.h"
#include "MyLocalization.h"
#include "KSLabelTTF.h"
#include "StyledLabelTTF.h"
#include "StarGoldData.h"
#include "CommonButton.h"
#include "CommonAnimation.h"
#include "ASPopupView.h"
#include "LoadingLayer.h"

LinkPopup* LinkPopup::create(int t_touch_priority, function<void()> t_end_func, function<void()> t_success_func)
{
	LinkPopup* t_mup = new LinkPopup();
	t_mup->myInit(t_touch_priority, t_end_func, t_success_func);
	t_mup->autorelease();
	return t_mup;
}

void LinkPopup::myInit(int t_touch_priority, function<void()> t_end_func, function<void()> t_success_func)
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
								  
								  input_text1->removeFromParent();
								  
								  CommonAnimation::closePopup(this, m_container, gray, [=](){

								  }, [=](){
									  end_func();
									  removeFromParent();

								  });
							  });
	back_case->addChild(close_button);
	
	StyledLabelTTF* content_label = StyledLabelTTF::create(myLoc->getLocalForKey(kMyLocalKey_notLinkedDoYouWannaLink), mySGD->getFont().c_str(), 12, 999, StyledAlignment::kCenterAlignment);
	content_label->setAnchorPoint(ccp(0.5f,0.5f));
	content_label->setPosition(ccpFromSize(back_in->getContentSize() / 2.f));
	back_in->addChild(content_label);
	TRACE();
	
	CCScale9Sprite* t_back1 = CCScale9Sprite::create("common_grayblue.png", CCRectMake(0, 0, 26, 26), CCRectMake(12, 12, 2, 2));
	input_text1 = CCEditBox::create(CCSizeMake(100, 30), t_back1);
	input_text1->setPosition(ccp(130.0 + 70.f,109.f));
	CCDirector::sharedDirector()->getRunningScene()->getChildByTag(1)->addChild(input_text1, 99999);
	
	input_text1->setAnchorPoint(ccp(0.5f, 0.5f));
	input_text1->setPlaceHolder(myLoc->getLocalForKey(kMyLocalKey_passwordInput));
	input_text1->setReturnType(kKeyboardReturnTypeDone);
	input_text1->setFont(mySGD->getFont().c_str(), 12);
	input_text1->setInputMode(kEditBoxInputModeSingleLine);
	input_text1->setInputFlag(cocos2d::extension::EditBoxInputFlag::kEditBoxInputFlagSensitive);
	input_text1->setDelegate(this);
	input_text1->setTouchPriority(touch_priority);
//	input_text1->setMaxLength(4);
	input_text1->setEnabled(false);
	input_text1->setVisible(false);
	
	CCLabelTTF* r_label = CCLabelTTF::create();
	KSLabelTTF* rightnow_label = KSLabelTTF::create(myLoc->getLocalForKey(kMyLocalKey_ok), mySGD->getFont().c_str(), 13);
	rightnow_label->disableOuterStroke();
	r_label->addChild(rightnow_label);
	TRACE();
	
	CCScale9Sprite* rightnow_back = CCScale9Sprite::create("achievement_button_success.png");
	TRACE();
	
	CCControlButton* rightnow_button = CCControlButton::create(r_label, rightnow_back);
	rightnow_button->addTargetWithActionForControlEvents(this, cccontrol_selector(LinkPopup::buttonAction), CCControlEventTouchUpInside);
	rightnow_button->setPreferredSize(CCSizeMake(101,44));
	rightnow_button->setPosition(ccp(73,-50));
	m_container->addChild(rightnow_button);
	
	rightnow_button->setTouchPriority(touch_priority);
	
	TRACE();
	
	
	CommonAnimation::openPopup(this, m_container, gray, [=](){
	}, [=](){
		is_menu_enable = true;
		input_text1->setVisible(true);
		input_text1->setEnabled(true);
	});
}

void LinkPopup::editBoxEditingDidBegin(CCEditBox* editBox)
{
	CCLOG("edit begin");
}
void LinkPopup::editBoxEditingDidEnd(CCEditBox* editBox)
{
	CCLOG("edit end");
}
void LinkPopup::editBoxTextChanged(CCEditBox* editBox, const std::string& text)
{
	CCLOG("edit changed : %s", text.c_str());
//	if(text.size() == 4)
//	{
//		if(editBox == input_text1)
//		{
//			input_text2->touchDownAction(nullptr, CCControlEvent());
//		}
//		else if(editBox == input_text2)
//		{
//			input_text3->touchDownAction(nullptr, CCControlEvent());
//		}
//	}
}
void LinkPopup::editBoxReturn(CCEditBox* editBox)
{
	CCLOG("edit return");
}

void LinkPopup::buttonAction(CCObject* sender, CCControlEvent t_event)
{
	if(!is_menu_enable)
		return;
	
	is_menu_enable = false;
	
	AudioEngine::sharedInstance()->playEffect("se_button1.mp3", false);
	
	input_text1->setEnabled(false);
	input_text1->setVisible(false);
	
	if(string(input_text1->getText()).length() == 0)
	{
		addChild(ASPopupView::getCommonNoti(touch_priority-100, myLoc->getLocalForKey(kMyLocalKey_noti), myLoc->getLocalForKey(kMyLocalKey_pleaseInputLinkCode), [=]()
								   {
									   input_text1->setEnabled(true);
									   input_text1->setVisible(true);
									   is_menu_enable = true;
								   }), 999);
		
		return;
	}
	
	t_loading = LoadingLayer::create(touch_priority-100);
	addChild(t_loading, 999);
	t_loading->startLoading();
	
	Json::Value param;
	param["diaryCode"] = input_text1->getText();
	
	graphdog->command("checkdiarycode", param, json_selector(this, LinkPopup::resultLink));
}

void LinkPopup::resultLink(Json::Value result_data)
{
	CCLog("resultLink : %s", GraphDogLib::JsonObjectToString(result_data).c_str());
	
	if(result_data["result"]["code"].asInt() == GDSUCCESS)
	{
		mySGD->network_check_cnt = 0;
		
		input_text1->removeFromParent();
		t_loading->removeFromParent();
		
		myDSH->setStringForKey(kDSH_Key_diaryMemberID, result_data["memberID"].asString().c_str());
		myDSH->setStringForKey(kDSH_Key_diaryCode, result_data["diaryCode"].asString().c_str());
	
		graphdog->setMemberID(atoll(myDSH->getStringForKey(kDSH_Key_diaryMemberID).c_str()));
		graphdog->setSocialID(myDSH->getStringForKey(kDSH_Key_diaryMemberID).c_str());
		
		CommonAnimation::closePopup(this, m_container, gray, [=](){
			
		}, [=](){
			success_func();
			removeFromParent();
		});
	}
	else if(result_data["result"]["code"].asInt() == GDEXPIRE)
	{
		mySGD->network_check_cnt = 0;
		
		t_loading->removeFromParent();
		
		addChild(ASPopupView::getCommonNoti(touch_priority-100, myLoc->getLocalForKey(kMyLocalKey_noti), myLoc->getLocalForKey(kMyLocalKey_invalidLinkCode), [=]()
								   {
									   input_text1->setEnabled(true);
									   input_text1->setVisible(true);
									   is_menu_enable = true;
								   }), 999);
	}
	else
	{
		mySGD->network_check_cnt++;
		
		if(mySGD->network_check_cnt >= mySGD->max_network_check_cnt)
		{
			mySGD->network_check_cnt = 0;
			
			ASPopupView *alert = ASPopupView::getCommonNotiTag(-99999,myLoc->getLocalForKey(kMyLocalKey_reConnect), myLoc->getLocalForKey(kMyLocalKey_reConnectAlert4),[=](){
				Json::Value param;
				param["diaryCode"] = input_text1->getText();
				
				graphdog->command("checkdiarycode", param, json_selector(this, LinkPopup::resultLink));
			}, 1);
			if(alert)
				((CCNode*)CCDirector::sharedDirector()->getRunningScene()->getChildren()->objectAtIndex(0))->addChild(alert,999999);
		}
		else
		{
			addChild(KSTimer::create(0.5f, [=]()
									 {
										 Json::Value param;
										 param["diaryCode"] = input_text1->getText();
										 
										 graphdog->command("checkdiarycode", param, json_selector(this, LinkPopup::resultLink));
									 }));
		}
	}
}