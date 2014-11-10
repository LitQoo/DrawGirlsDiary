//
//  PatternTutorialContent.h
//  DGproto
//
//  Created by 사원3 on 2013. 12. 3..
//
//

#ifndef __DGproto__PatternTutorialContent__
#define __DGproto__PatternTutorialContent__

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace std;

class KSLabelTTF;
class PatternTutorialContent : public CCNode//, public CCBAnimationManagerDelegate
{
public:
	static PatternTutorialContent* create(int t_touch_priority, function<void(CCObject*)> t_selector, const vector<int>& t_pattern_list);
	
private:
	int touch_priority;
	CCMenu* close_menu;
	vector<int> pattern_list;
	function<void(CCObject*)> end_selector;
	CCSprite* show_content;
	KSLabelTTF* pattern_title;
	KSLabelTTF* pattern_content;
	
	int ing_close_cnt;
	
	bool is_menu_enable;
	
	CCNode* show_node;
	
	void menuAction(CCObject* sender);
	int getTitleLocalKeyForPatternNumber(int t_pattern);
	int getContentLocalKeyForPatternNumber(int t_pattern);
	void myInit(int t_touch_priority, function<void(CCObject*)> t_selector, const vector<int>& t_pattern_list);
};

#endif /* defined(__DGproto__PatternTutorialContent__) */
