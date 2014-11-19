//
//  PieceGame.h
//  DgDiary
//
//  Created by 사원3 on 2014. 11. 12..
//
//

#ifndef __DgDiary__PieceGame__
#define __DgDiary__PieceGame__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "jsoncpp/json.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace std;

class ZoomScrollView : public CCScrollView
{
public:
	static ZoomScrollView* create(CCSize t_init_size);
private:
	void myInit();
};

class PieceOne : public CCLayer
{
public:
	static PieceOne* createWithTexture(CCTexture2D* t_texture, CCRect t_rect);
	function<void(CCPoint before_position, CCPoint after_touch_point, PieceOne* touched_target)> change_position;
	function<bool()> check_on_touch;
	function<void(bool)> set_on_touch;
	function<void(CCPoint, bool)> touch_light_func;
	bool isContainsPoint(CCPoint t_point);
	CCPoint on_point;
	
private:
	
	CCPoint touch_begin_point;
	CCPoint touch_move_point;
	CCPoint before_touch_position;
	
	CCSprite* cell_img;
	
	void myInit(CCTexture2D* t_texture, CCRect t_rect);
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);
	
	virtual void registerWithTouchDispatcher(void);
};

class LoadingLayer;
class KSLabelTTF;
class PieceGame : public CCLayer, public CCScrollViewDelegate
{
public:
	virtual bool init();
	static cocos2d::CCScene* scene();
	CREATE_FUNC(PieceGame);
	
	virtual void onEnterTransitionDidFinish();
	
	void changePosition(CCPoint before_position, CCPoint after_touch_point, PieceOne* touched_target);
	bool is_on_touch;
	void touchLightCase(CCPoint t_position, bool is_end);
	
private:
	
	vector<PieceOne*> piece_list;
	
	LoadingLayer* t_loading;
	KSLabelTTF* life_stone_count;
	KSLabelTTF* success_label;
	
	CCScale9Sprite* light_img;
	CCSprite* mini_map;
	CCNode* target_node;
	CCSpriteBatchNode* batch_node;
	ZoomScrollView* t_controler;
	
	CCSprite* map_case;
	CCScale9Sprite* img_case;
	CCSprite* img_back;
	
	bool is_menu_enable;
	int size_value;
	
	void onSizeMenu();
	
	void createPauseMenu();
	
	void initGame();
	void scrollViewDidScroll(CCScrollView* view);
	void scrollViewDidZoom(CCScrollView* view);
	void resultReward(Json::Value result_data);
};

#endif /* defined(__DgDiary__PieceGame__) */
