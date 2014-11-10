//
//  InterlockPopup.h
//  DgDiary
//
//  Created by 사원3 on 2014. 9. 5..
//
//

#ifndef __DgDiary__InterlockPopup__
#define __DgDiary__InterlockPopup__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "jsoncpp/json.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace std;

class TouchSuctionLayer;
class InterlockPopup : public CCLayer
{
public:
	static InterlockPopup* create(int t_touch_priority, function<void()> t_end_func);
	
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
	void resultGetCommonSetting(Json::Value result_data);
};

#endif /* defined(__DgDiary__InterlockPopup__) */
