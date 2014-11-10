//
//  SDiaryInformationPopup.h
//  DgDiary
//
//  Created by 사원3 on 2014. 10. 7..
//
//

#ifndef __DgDiary__SDiaryInformationPopup__
#define __DgDiary__SDiaryInformationPopup__

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace std;

class TouchSuctionLayer;
class SDiaryInformationPopup : public CCLayer
{
public:
	static SDiaryInformationPopup* create(int t_touch_priority, function<void()> t_end_func);
	
private:
	int touch_priority;
	function<void()> end_func;
	
	bool is_menu_enable;
	
	TouchSuctionLayer* suction;
	
	CCSprite* gray;
	CCNode* m_container;
	CCSprite* back_case;
	CCControlButton* close_button;
	
	void myInit(int t_touch_priority, function<void()> t_end_func);
};

#endif /* defined(__DgDiary__SDiaryInformationPopup__) */
