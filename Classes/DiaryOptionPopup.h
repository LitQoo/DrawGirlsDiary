//
//  DiaryOptionPopup.h
//  DgDiary
//
//  Created by 사원3 on 2014. 9. 13..
//
//

#ifndef __DgDiary__DiaryOptionPopup__
#define __DgDiary__DiaryOptionPopup__

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace std;

class TouchSuctionLayer;
class DiaryOptionPopup : public CCLayer
{
public:
	static DiaryOptionPopup* create(int t_touch_priority, function<void()> t_end_func);
	
private:
	int touch_priority;
	function<void()> end_func;
	
	bool is_menu_enable;
	
	TouchSuctionLayer* suction;
	
	CCSprite* gray;
	CCNode* m_container;
	CCSprite* back_case;
	
	CCScale9Sprite* back_in;
	
	CCSprite* lock_button_img;
	
	void resetLockButton();
	
	void buttonAction(CCObject* sender, CCControlEvent t_event);
	
	void myInit(int t_touch_priority, function<void()> t_end_func);
};

#endif /* defined(__DgDiary__DiaryOptionPopup__) */
