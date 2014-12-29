//
//  DdmkLinkPopup.h
//  DgDiary
//
//  Created by 사원3 on 2014. 12. 22..
//
//

#ifndef __DgDiary__DdmkLinkPopup__
#define __DgDiary__DdmkLinkPopup__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "jsoncpp/json.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace std;

class TouchSuctionLayer;
class DdmkLinkPopup : public CCLayer
{
public:
	static DdmkLinkPopup* create(int t_touch_priority, function<void()> t_end_func, function<void()> t_success_func);
	
private:
	int touch_priority;
	function<void()> end_func;
	function<void()> success_func;
	
	bool is_menu_enable;
	
	TouchSuctionLayer* suction;
	
	CCSprite* gray;
	CCNode* m_container;
	CCSprite* back_case;
	
	void buttonAction(CCObject* sender, CCControlEvent t_event);
	
	void myInit(int t_touch_priority, function<void()> t_end_func, function<void()> t_success_func);
};

#endif /* defined(__DgDiary__DdmkLinkPopup__) */
