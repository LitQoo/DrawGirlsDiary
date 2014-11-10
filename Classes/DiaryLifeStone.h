//
//  DiaryLifeStone.h
//  DgDiary
//
//  Created by 사원3 on 2014. 9. 25..
//
//

#ifndef __DgDiary__DiaryLifeStone__
#define __DgDiary__DiaryLifeStone__

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace std;

class TouchSuctionLayer;
class DiaryLifeStone : public CCLayer
{
public:
	static DiaryLifeStone* create(int t_touch_priority, function<void()> t_end_func);
	
private:
	int touch_priority;
	function<void()> end_func;
	
	bool is_menu_enable;
	
	TouchSuctionLayer* suction;
	
	CCSprite* gray;
	CCNode* m_container;
	CCSprite* back_case;
	
	void buttonAction(CCObject* sender, CCControlEvent t_event);
	
	void myInit(int t_touch_priority, function<void()> t_end_func);
};

#endif /* defined(__DgDiary__DiaryLifeStone__) */
