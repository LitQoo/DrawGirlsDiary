//
//  EnterPasswordPopup.h
//  DgDiary
//
//  Created by 사원3 on 2014. 9. 18..
//
//

#ifndef __DgDiary__EnterPasswordPopup__
#define __DgDiary__EnterPasswordPopup__

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace std;

class TouchSuctionLayer;
class KSLabelTTF;
class EnterPasswordPopup : public CCLayer, public CCEditBoxDelegate
{
public:
	static EnterPasswordPopup* create(int t_touch_priority, function<void()> t_end_func);
	
private:
	int touch_priority;
	function<void()> end_func;
	
	bool is_menu_enable;
	
	TouchSuctionLayer* suction;
	
	CCSprite* gray;
	
	CCNode* m_container;
	
	CCEditBox* input_text1;
	
	CCSprite* back_case;
	
	void myInit(int t_touch_priority, function<void()> t_end_func);
	
	void couponAction(CCObject* sender, CCControlEvent t_event);
	
	void initiateEditBox(CCEditBox* editbox);
	virtual void editBoxEditingDidBegin(CCEditBox* editBox);
    virtual void editBoxEditingDidEnd(CCEditBox* editBox);
    virtual void editBoxTextChanged(CCEditBox* editBox, const std::string& text);
    virtual void editBoxReturn(CCEditBox* editBox);
};

#endif /* defined(__DgDiary__EnterPasswordPopup__) */
