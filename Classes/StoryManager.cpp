//
//  StoryManager.cpp
//  DGproto
//
//  Created by 사원3 on 2014. 3. 11..
//
//

#include "StoryManager.h"
#include "StarGoldData.h"
#include "utf8.h"
#include "AudioEngine.h"
#include "DataStorageHub.h"

void StoryManager::addMent(bool is_left, string t_name, string t_namefile, string t_ment, function<void(void)> t_end_func,
						   CCSize t_size/* = CCSizeMake(350,100)*/, CCPoint t_point/* = ccp(0,-110)*/, int t_font_size/* = 12*/, bool is_typing_sound/* = false*/)
{
	ment_node->removeAllChildren();
	
	is_on_typing_sound = is_typing_sound;
	
	CCScale9Sprite* ment_box = CCScale9Sprite::create("talk_mentbox.png", CCRectMake(0, 0, 35, 35), CCRectMake(12, 12, 23-12, 23-12));
	ment_box->setContentSize(t_size);
	ment_box->setPosition(t_point + ccp(0, myDSH->ui_zero_point.y));
	ment_box->setScale(myDSH->screen_convert_rate);
	ment_node->addChild(ment_box);
	
	recent_ment = t_ment;
	
	ment_label = CCLabelTTF::create("", mySGD->getFont().c_str(), t_font_size);
	ment_label->setAnchorPoint(ccp(0,1));
	ment_label->setPosition(ccp(12, 100-12));
	ment_label->setHorizontalAlignment(kCCTextAlignmentLeft);
	ment_box->addChild(ment_label);
	
	next_label = CCLabelTTF::create("TAP_", mySGD->getFont().c_str(), 12);
	next_label->setAnchorPoint(ccp(1,0));
	next_label->setPosition(ccp(t_size.width-12, 12));
	next_label->setVisible(false);
	ment_box->addChild(next_label);
	
	
	if(!t_name.empty() && !t_namefile.empty())
	{
		CCLabelTTF* name_label = CCLabelTTF::create(t_name.c_str(), mySGD->getFont().c_str(), 14);
		name_label->setAnchorPoint(ccp(0,1));
		
		CCScale9Sprite* name_tag = CCScale9Sprite::create(t_namefile.c_str(), CCRectMake(0, 0, 35, 35), CCRectMake(12, 12, 23-12, 23-12));
		name_tag->setContentSize(CCSizeMake(name_label->getContentSize().width+24, name_label->getContentSize().height+24));
		if(is_left)
		{
			name_tag->setAnchorPoint(ccp(0,0.5));
			name_tag->setPosition(ccp(-175, -45));
		}
		else
		{
			name_tag->setAnchorPoint(ccp(1,0.5));
			name_tag->setPosition(ccp(175, -45));
		}
		name_label->setPosition(ccp(12,35-8));
		name_tag->addChild(name_label);
		ment_node->addChild(name_tag);
	}
	
	end_func = t_end_func;
	is_click_effect = true;
	
	typing_sound_number = 1;
	
	startMent();
}

void StoryManager::cleanSM()
{
	ment_node->removeAllChildren();
}

void StoryManager::mentAction()
{
	ing_ment_cnt++;
	
	int frame_value;
	if(is_boosting)
		frame_value = 1;
	else
		frame_value = 3;
	
	if(ing_ment_cnt%frame_value == 0)
	{

		
		ment_recent_length++;
		basic_string<wchar_t> result;
		utf8::utf8to16(recent_ment.begin(), recent_ment.end(), back_inserter(result));
		int ment_length = result.length();
		
		if(is_on_typing_sound)
		{
			if(!(result[ment_recent_length]==' ' || result[ment_recent_length]=='\n'))
			{
				AudioEngine::sharedInstance()->playEffect("se_typing_5.mp3", false);//ccsf("se_typing_%d.mp3", typing_sound_number++), false);
				if(typing_sound_number > 4)
					typing_sound_number = 1;
			}
		}
		
		result = result.substr(0, ment_recent_length);
		string conver;
		utf8::utf16to8(result.begin(), result.end(), back_inserter(conver));
		if(ment_recent_length < ment_length)
			conver = conver + "_";
		ment_label->setString(conver.c_str());
		
		if(ment_recent_length >= ment_length)
		{
			
			//끝날때도 한번 재생
//			if(is_on_typing_sound)
//				AudioEngine::sharedInstance()->playEffect("sound_crashed_map.mp3", false);
			
			next_label->setVisible(true);
//			if(is_on_typing_sound)
//				AudioEngine::sharedInstance()->stopEffect("sound_crashed_map.mp3");
			unschedule(schedule_selector(StoryManager::mentAction));
			is_menting = false;
		}
	}
}

bool StoryManager::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	touch_count++;
	is_boosting = true;
	if(!is_menting && !is_delaying && end_func)
	{
		if(is_click_effect)
		{
			AudioEngine::sharedInstance()->playEffect("se_button1.mp3");
			is_click_effect = false;
			end_func();
		}
	}
	
	return true;
}

void StoryManager::ccTouchMoved( CCTouch *pTouch, CCEvent *pEvent )
{
	
}

void StoryManager::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
{
	touch_count--;
	if(touch_count <= 0)
	{
		touch_count = 0;
		is_boosting = false;
	}
}

void StoryManager::ccTouchCancelled( CCTouch *pTouch, CCEvent *pEvent )
{
	touch_count--;
	if(touch_count <= 0)
	{
		touch_count = 0;
		is_boosting = false;
	}
}

void StoryManager::registerWithTouchDispatcher()
{
	CCTouchDispatcher* pDispatcher = CCDirector::sharedDirector()->getTouchDispatcher();
	pDispatcher->addTargetedDelegate(this, m_touch_priority, true);
}