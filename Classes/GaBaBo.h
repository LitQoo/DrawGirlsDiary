 #ifndef GABABO_H
#define GABABO_H

#include "cocos2d.h"
USING_NS_CC;

#include "DataStorageHub.h"
#include "CCMenuLambda.h"
#include "EasingAction.h"
#include "CurtainNodeForBonusGame.h"

static int 	kAttackGa = 1;
static int	kAttackBa = 2;
static int	kAttackBo = 3;


class GaBaBo : public CCLayerColor
{
public:
	GaBaBo();
	virtual ~GaBaBo();
	bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual bool init(int touchPriority, const std::vector<BonusGameReward>& rewards, std::function<void(int)> endFunction);
	static GaBaBo* create(int prior, const std::vector<BonusGameReward>& rewards, std::function<void(int)> endFunction)
	{
		GaBaBo* t = new GaBaBo();
		t->init(prior, rewards, endFunction);
		t->autorelease();
		return t;
	}
//	static CCScene* scene()
//	{
//		// 'scene' is an autorelease object
//		CCScene *scene = CCScene::create();
//		
//		// 'layer' is an autorelease object
//		GaBaBo *layer = GaBaBo::create();
//		layer->setAnchorPoint(ccp(0.5,0));
//		layer->setScale(myDSH->screen_convert_rate);
//		layer->setPosition(ccpAdd(layer->getPosition(), myDSH->ui_zero_point));
//		
//		scene->addChild(layer);
//		return scene;
//	}
	void showResult();
	void update(float dt);
	void initGameTime()
	{
//		m_remainTime = 5.f;
		m_remainTime = 5.f;
		m_gababoCountShowing = false;
	}
	void loadImage(int step);
	int getCurrentTimeStamp();
	void setVisibleInterface(bool r);
	void initAnimation();
	void hidingAnimation();
	virtual void registerWithTouchDispatcher();
protected:
	std::function<void(int)> m_endFunction;
	CCMenuItemToggleLambda* m_ba, *m_ga, *m_bo;
	int m_computerThink;
	std::map<int, CCSprite*> m_computerThinkSprites;
	float m_remainTime;
	bool m_resultShowing;
	bool m_gababoCountShowing;
	CCLabelBMFont* m_remainTimeFnt;
	CCSprite* m_stepSprite;
	CCSprite* m_thinkSprite;
	int m_step;
	long long m_lastChangeTime;
	int m_winCount, m_drawCount, m_loseCount;
	int m_touchPriority;
	CCSprite* m_currentRewardCursor;
};

#endif
