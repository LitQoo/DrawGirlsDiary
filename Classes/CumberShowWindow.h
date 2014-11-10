//
//  CumberShowWindow.h
//  DGproto
//
//  Created by ksoo k on 2013. 11. 21..
//
//

#ifndef __DGproto__CumberShowWindow__
#define __DGproto__CumberShowWindow__

#include "cocos2d.h"
#include "cocos-ext.h"
#include <vector>
#include "Well512.h"

using namespace std;
USING_NS_CC;
USING_NS_CC_EXT;

/*
 , public CCBSelectorResolver  public CCBAnimationManagerDelegate
 
 
 virtual void completedAnimationSequenceNamed(const char *name) = 0;
 
 virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName) = 0;
 virtual SEL_CallFuncN onResolveCCBCCCallFuncSelector(CCObject * pTarget, const char* pSelectorName) { return NULL; };
 virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName) = 0;
 */

enum CumberShowWindowSceneCode{
	kCumberShowWindowSceneCode_puzzle = 0,
	kCumberShowWindowSceneCode_cardChange
};

class KSSnakeBase;
class CumberShowWindow : public CCNode, public CCBSelectorResolver,  public CCBAnimationManagerDelegate
{
public:
	virtual void completedAnimationSequenceNamed(const char *name)
	{
		
	}
	
	virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
	{
		return NULL;
	}
	virtual SEL_CallFuncN onResolveCCBCCCallFuncSelector(CCObject * pTarget, const char* pSelectorName)
	{
		return NULL;
	}
	virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName)
	{
		return NULL;
	}
	static CumberShowWindow* create(int stageNumber, CumberShowWindowSceneCode t_code = kCumberShowWindowSceneCode_puzzle)
	{
		CumberShowWindow* t_blg = new CumberShowWindow();
		t_blg->init(stageNumber, t_code);
		t_blg->autorelease();
		return t_blg;
	}
	
	static CumberShowWindow* createLoading()
	{
		CumberShowWindow* t_blg = new CumberShowWindow();
		t_blg->init();
		t_blg->autorelease();
		return t_blg;
	}
	
	string start_ment;
	string clear_ment;
	string fail_ment;
	
	int boss_hp;
	double boss_speed;
	double boss_agi;
	
	bool init(int, CumberShowWindowSceneCode);
	bool init();
	
	CCBAnimationManager* m_circleAnimation;
	CCBAnimationManager* m_snakeHeadAnimation;
	std::vector<CCBAnimationManager*> m_snakeBodiesAnimation;
	CCBAnimationManager* m_snakeTailAnimation;
	
	CCNode* boss_node;
	
	CCSprite* m_circleSprite;
	KSSnakeBase* m_snakeNode;
	CCSprite* m_juniorSprite;
	CCBAnimationManager* m_juniorAnimation;
	
	
	Well512 m_well512;
	
	void startFloatMoving();
	
	CCPoint base_position;
	float a_y;
	float v_y;
	void floatMoving();
};
#endif /* defined(__DGproto__CumberShowWindow__) */
