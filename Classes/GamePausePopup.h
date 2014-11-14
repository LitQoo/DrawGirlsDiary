//
//  GamePausePopup.h
//  DgDiary
//
//  Created by 사원3 on 2014. 11. 13..
//
//

#ifndef __DgDiary__GamePausePopup__
#define __DgDiary__GamePausePopup__

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace std;

class TouchSuctionLayer;
class GamePausePopup : public CCLayer
{
public:
	static GamePausePopup* create(int t_touch_priority, function<void()> t_end_func, function<void()> t_restart_func, function<void(int)> t_size_change_func);
	
private:
	int touch_priority;
	function<void()> end_func;
	function<void()> restart_func;
	function<void(int)> size_change_func;
	
	bool is_menu_enable;
	
	TouchSuctionLayer* suction;
	
	CCSprite* gray;
	CCNode* m_container;
	CCSprite* back_case;
	
	void myInit(int t_touch_priority, function<void()> t_end_func, function<void()> t_restart_func, function<void(int)> t_size_change_func);
};

#endif /* defined(__DgDiary__GamePausePopup__) */
