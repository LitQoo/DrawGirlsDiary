//
//  LinkPopup.h
//  DgDiary
//
//  Created by 사원3 on 2014. 11. 14..
//
//

#ifndef __DgDiary__LinkPopup__
#define __DgDiary__LinkPopup__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "jsoncpp/json.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace std;

class TouchSuctionLayer;
class LoadingLayer;
class LinkPopup : public CCLayer, public CCEditBoxDelegate
{
public:
	static LinkPopup* create(int t_touch_priority, function<void()> t_end_func, function<void()> t_success_func);
	
private:
	int touch_priority;
	function<void()> end_func;
	function<void()> success_func;
	
	bool is_menu_enable;
	
	TouchSuctionLayer* suction;
	LoadingLayer* t_loading;
	
	CCSprite* gray;
	CCNode* m_container;
	CCSprite* back_case;
	
	void buttonAction(CCObject* sender, CCControlEvent t_event);
	
	CCEditBox* input_text1;
	
	virtual void editBoxEditingDidBegin(CCEditBox* editBox);
	virtual void editBoxEditingDidEnd(CCEditBox* editBox);
	virtual void editBoxTextChanged(CCEditBox* editBox, const std::string& text);
	virtual void editBoxReturn(CCEditBox* editBox);
	
	void myInit(int t_touch_priority, function<void()> t_end_func, function<void()> t_success_func);
	void resultLink(Json::Value result_data);
};

#endif /* defined(__DgDiary__LinkPopup__) */
