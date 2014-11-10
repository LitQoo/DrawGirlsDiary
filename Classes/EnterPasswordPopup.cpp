//
//  EnterPasswordPopup.cpp
//  DgDiary
//
//  Created by 사원3 on 2014. 9. 18..
//
//

#include "EnterPasswordPopup.h"
#include "CCMenuLambda.h"
#include "TouchSuctionLayer.h"
#include "KSUtil.h"
#include "KSLabelTTF.h"
#include "StarGoldData.h"
#include "DataStorageHub.h"
#include "ASPopupView.h"
#include "MyLocalization.h"
#include "CommonButton.h"
#include "CommonAnimation.h"

EnterPasswordPopup* EnterPasswordPopup::create(int t_touch_priority, function<void()> t_end_func)
{
	EnterPasswordPopup* t_mup = new EnterPasswordPopup();
	t_mup->myInit(t_touch_priority, t_end_func);
	t_mup->autorelease();
	return t_mup;
}

void EnterPasswordPopup::myInit(int t_touch_priority, function<void()> t_end_func)
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
	m_container->setPosition(ccp(240,220));
	addChild(m_container);
	
	
	back_case = CCSprite::create("popup_small_back.png");
	back_case->setPosition(ccp(0,0));
	m_container->addChild(back_case);
	
	
//	CommonButton* cancel_button = CommonButton::createCloseButton(touch_priority);
//	cancel_button->setPosition(ccp(back_case->getContentSize().width/2.f-22,back_case->getContentSize().height/2.f-25));
//	cancel_button->setFunction([=](CCObject* sender)
//							   {
//								   if(!is_menu_enable)
//									   return;
//								   
//								   is_menu_enable = false;
//								   input_text1->setEnabled(false);
//								   input_text1->removeFromParent();
//								   
//								   AudioEngine::sharedInstance()->playEffect("se_button1.mp3");
//								   
//								   CommonAnimation::closePopup(this, m_container, gray, [=](){
//									   
//								   }, [=](){
//									   end_func();
//									   removeFromParent();
//								   });
//							   });
//	m_container->addChild(cancel_button);
	
	
	KSLabelTTF* title_label = KSLabelTTF::create(myLoc->getLocalForKey(kMyLocalKey_enterPasswordTitle), mySGD->getFont().c_str(), 12);
	title_label->disableOuterStroke();
	title_label->setAnchorPoint(ccp(0.5f,0.5f));
	title_label->setPosition(ccp(-85,back_case->getContentSize().height/2.f-35));
	m_container->addChild(title_label);
	
	
//	CCScale9Sprite* back_in = CCScale9Sprite::create("common_grayblue.png", CCRectMake(0, 0, 26, 26), CCRectMake(12, 12, 2, 2));
//	back_in->setAnchorPoint(ccp(0.5f, 0.5f));
//	back_in->setContentSize(CCSizeMake(230,35));
//	back_in->setPosition(ccp(0, 0)); 			// dt (-128.0,2.5)
//	m_container->addChild(back_in);
	
	KSLabelTTF* ment_label1 = KSLabelTTF::create(myLoc->getLocalForKey(kMyLocalKey_enterPasswordContent), mySGD->getFont().c_str(), 13);
	ment_label1->enableOuterStroke(ccBLACK, 0.3f, 50, true);
	ment_label1->setAnchorPoint(ccp(0.5f,0.5f));
	ment_label1->setPosition(ccp(0,30));
	m_container->addChild(ment_label1);
	
	
	CCScale9Sprite* t_back1 = CCScale9Sprite::create("common_grayblue.png", CCRectMake(0, 0, 26, 26), CCRectMake(12, 12, 2, 2));
//	t_back1->setOpacity(0);
	input_text1 = CCEditBox::create(CCSizeMake(170, 30), t_back1);
	input_text1->setPosition(ccp(240.f,217.f));
	CCDirector::sharedDirector()->getRunningScene()->getChildByTag(1)->addChild(input_text1, 99999);
	
	
	initiateEditBox(input_text1);
	
	CCLabelTTF* t_label = CCLabelTTF::create();
	KSLabelTTF* ok_label = KSLabelTTF::create(myLoc->getLocalForKey(kMyLocalKey_ok), mySGD->getFont().c_str(), 13);
	ok_label->disableOuterStroke();
	t_label->addChild(ok_label);
	
	CCScale9Sprite* ok_back = CCScale9Sprite::create("achievement_button_success.png", CCRectMake(0,0,101,44), CCRectMake(50, 21, 1, 2));
	
	CCControlButton* ok_button = CCControlButton::create(t_label, ok_back);
	ok_button->addTargetWithActionForControlEvents(this, cccontrol_selector(EnterPasswordPopup::couponAction), CCControlEventTouchUpInside);
	ok_button->setPreferredSize(CCSizeMake(101,44));
	ok_button->setPosition(ccp(0,-50));
	m_container->addChild(ok_button);
	
	ok_button->setTouchPriority(touch_priority);
	
	CommonAnimation::openPopup(this, m_container, gray, [=](){
		//		t_back->setOpacity(0);
		
	}, [=](){
		//		t_back->setOpacity(0);
		is_menu_enable = true;
		input_text1->setEnabled(true);
		input_text1->setVisible(true);
	});
}

void EnterPasswordPopup::couponAction(CCObject* sender, CCControlEvent t_event)
{
	if(!is_menu_enable)
		return;
	
	is_menu_enable = false;
	
	AudioEngine::sharedInstance()->playEffect("se_button1.mp3");
	
	if(string(input_text1->getText()) == "")
	{
		input_text1->setEnabled(false);
		input_text1->setVisible(false);
		addChild(ASPopupView::getCommonNoti(touch_priority-100, myLoc->getLocalForKey(kMyLocalKey_noti), myLoc->getLocalForKey(kMyLocalKey_passwordNotiInput), [=]()
											{
												input_text1->setEnabled(true);
												input_text1->setVisible(true);
												is_menu_enable = true;
											}), 9999);
		return;
	}
	else if(string(input_text1->getText()) != myDSH->getStringForKey(kDSH_Key_diaryPassword))
	{
		input_text1->setEnabled(false);
		input_text1->setVisible(false);
		addChild(ASPopupView::getCommonNoti(touch_priority-100, myLoc->getLocalForKey(kMyLocalKey_noti), myLoc->getLocalForKey(kMyLocalKey_passwordNotiDifferent), [=]()
											{
												input_text1->setEnabled(true);
												input_text1->setVisible(true);
												is_menu_enable = true;
											}), 9999);
		return;
	}
	
	input_text1->setEnabled(false);
	input_text1->removeFromParent();
	
	CommonAnimation::closePopup(this, m_container, gray, [=](){
		
	}, [=](){
		end_func();
		removeFromParent();
	});
}

void EnterPasswordPopup::editBoxEditingDidBegin(CCEditBox* editBox)
{
	CCLOG("edit begin");
}
void EnterPasswordPopup::editBoxEditingDidEnd(CCEditBox* editBox)
{
	CCLOG("edit end");
}
void EnterPasswordPopup::editBoxTextChanged(CCEditBox* editBox, const std::string& text)
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
void EnterPasswordPopup::editBoxReturn(CCEditBox* editBox)
{
	CCLOG("edit return");
}
void EnterPasswordPopup::initiateEditBox(CCEditBox* editbox)
{
	editbox->setAnchorPoint(ccp(0.5f, 0.5f));
	editbox->setPlaceHolder(myLoc->getLocalForKey(kMyLocalKey_passwordInput));
	editbox->setReturnType(kKeyboardReturnTypeDone);
	editbox->setFont(mySGD->getFont().c_str(), 13);
	editbox->setInputMode(kEditBoxInputModeSingleLine);
	editbox->setInputFlag(cocos2d::extension::EditBoxInputFlag::kEditBoxInputFlagPassword);
	editbox->setDelegate(this);
	//	m_container->addChild(input_text);
	editbox->setTouchPriority(touch_priority);
	editbox->setEnabled(false);
	editbox->setVisible(false);
}