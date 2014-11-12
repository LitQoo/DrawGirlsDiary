//
//  PieceGame.cpp
//  DgDiary
//
//  Created by 사원3 on 2014. 11. 12..
//
//

#include "PieceGame.h"
#include "StageImgLoader.h"
#include "DataStorageHub.h"
#include <algorithm>
#include "KSUtil.h"
#include "KSLabelTTF.h"
#include "StarGoldData.h"

ZoomScrollView* ZoomScrollView::create(CCSize t_init_size)
{
	ZoomScrollView* t_wsv = new ZoomScrollView();
	t_wsv->initWithViewSize(t_init_size);
	t_wsv->myInit();
	t_wsv->autorelease();
	return t_wsv;
}
void ZoomScrollView::myInit()
{
	m_fMinScale = myDSH->ui_top/(430.f * (430.f/320.f));
	m_fMaxScale = 1.f;
}

PieceOne* PieceOne::createWithTexture(CCTexture2D* t_texture, CCRect t_rect)
{
	PieceOne* t_po = new PieceOne();
	t_po->initWithTexture(t_texture, t_rect);
	t_po->CCSprite::autorelease();
	return t_po;
}

bool PieceOne::isContainsPoint(CCPoint t_point)
{
	CCPoint touchLocation = t_point;
	CCPoint local = CCSprite::convertToNodeSpace(touchLocation);
	
	CCRect t_rect = CCRectMake(0, 0, CCSprite::getContentSize().width, CCSprite::getContentSize().height);
	return t_rect.containsPoint(local);
}

bool PieceOne::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	if(check_on_touch())
		return false;
	
	before_touch_position = CCSprite::getPosition();
	CCPoint touchLocation = pTouch->getLocation();
	touch_begin_point = touchLocation;
	touch_move_point = touch_begin_point;
	CCPoint local = CCSprite::convertToNodeSpace(touchLocation);
	
	CCRect t_rect = CCRectMake(0, 0, CCSprite::getContentSize().width, CCSprite::getContentSize().height);
	if(t_rect.containsPoint(local))
	{
		setColor(ccGRAY);
		CCSprite::getParent()->reorderChild((CCSprite*)this, 1);
		set_on_touch(true);
		return true;
	}
	else
		return false;
}
void PieceOne::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
	CCPoint touchLocation = pTouch->getLocation();
	CCSprite::setPosition(CCSprite::getPosition() + ccpMult(touchLocation - touch_move_point, 1.f/CCSprite::getParent()->getParent()->getScale()));
	touch_move_point = touchLocation;
}
void PieceOne::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	setColor(ccWHITE);
	CCSprite::getParent()->reorderChild((CCSprite*)this, 0);
	CCPoint touchLocation = pTouch->getLocation();
	change_position(before_touch_position, touchLocation, this);
	set_on_touch(false);
}
void PieceOne::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{
	setColor(ccWHITE);
	CCSprite::getParent()->reorderChild((CCSprite*)this, 0);
	CCPoint touchLocation = pTouch->getLocation();
	change_position(before_touch_position, touchLocation, this);
	set_on_touch(false);
}

void PieceOne::registerWithTouchDispatcher()
{
	CCDirector* pDirector = CCDirector::sharedDirector();
	pDirector->getTouchDispatcher()->addTargetedDelegate(this, this->getTouchPriority(), true);
}

CCScene* PieceGame::scene()
{
	CCScene *scene = CCScene::create();
	PieceGame *layer = PieceGame::create();
	scene->addChild(layer);
	
	return scene;
}

bool PieceGame::init()
{
	if ( !CCLayer::init() )
	{
		return false;
	}
	
	is_on_touch = false;
	
	srand(time(NULL));
	
	target_node = CCNode::create();
	target_node->setScale(430.f/320.f);
	addChild(target_node);
	
	CCSprite* t_container = CCSprite::create("whitepaper2.png", CCRectMake(0, 0, 40, 430.f*target_node->getScale()));
	
	t_controler = ZoomScrollView::create(CCSizeMake(40, myDSH->ui_top));
	t_controler->setPosition(ccp(0,0));
	t_controler->setDirection(CCScrollViewDirection::kCCScrollViewDirectionVertical);
	t_controler->setContainer(t_container);
	t_controler->setDelegate(this);
	addChild(t_controler);
	
	mini_map = NULL;
	piece_list.clear();
	initGame();
	
	return true;
}

void PieceGame::initGame()
{
	if(mini_map)
	{
		mini_map->removeFromParent();
		mini_map = NULL;
	}
	
	for(int i=0;i<piece_list.size();i++)
	{
		piece_list[i]->CCLayer::onExit();
	}
	
	target_node->removeAllChildren();
	target_node->setScale(430.f/320.f);
	target_node->setPosition(ccp(480-160*target_node->getScale(),myDSH->ui_center_y));
	t_controler->setZoomScale(1.f);
	t_controler->setContentOffset(ccp(0,t_controler->minContainerOffset().y/2.f));
	
	int has_gotten_card_size = mySGD->getHasGottenCardsSize();
	int random_value = rand()%has_gotten_card_size;
	
	CardSortInfo t_info = mySGD->getHasGottenCardData(random_value);
	
	CCTexture2D* t_texture = mySIL->addImage(ccsf("card%d_visible.png", t_info.card_number.getV()));
	batch_node = CCSpriteBatchNode::createWithTexture(t_texture);
	batch_node->setPosition(ccp(0,0));
	target_node->addChild(batch_node);
	
	CCSprite* top_img = CCSprite::createWithTexture(t_texture, CCRectMake(0, 0, 320, 15));
	top_img->setPosition(ccp(0,207.5f));
	batch_node->addChild(top_img);
	
	CCSprite* bottom_img = CCSprite::createWithTexture(t_texture, CCRectMake(0, 415, 320, 15));
	bottom_img->setPosition(ccp(0,-207.5f));
	batch_node->addChild(bottom_img);
	
	vector<int> rand_list;
	rand_list.clear();
	for(int j=0;j<5;j++)
	{
		for(int i=0;i<4;i++)
		{
			rand_list.push_back(i + j*4);
		}
	}
	
	random_shuffle(rand_list.begin(), rand_list.end());
	
	piece_list.clear();
	
	for(int j=0;j<5;j++)
	{
		for(int i=0;i<4;i++)
		{
			int pos_i = rand_list[i + j*4]%4;
			int pos_j = rand_list[i + j*4]/4;
			
			PieceOne* t_img = PieceOne::createWithTexture(t_texture, CCRectMake(i*80, 430 - (15+(j+1)*80), 80, 80));
			t_img->CCSprite::setAnchorPoint(CCPointZero);
			t_img->CCSprite::setPosition(ccp(-160 + 0,-200 + 0) + ccp(pos_i*80,pos_j*80));
			batch_node->addChild((CCSprite*)t_img);
			t_img->on_point = ccp(-160 + 0,-200 + 0) + ccp(i*80,j*80);
			
			t_img->change_position = bind(&PieceGame::changePosition, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
			t_img->check_on_touch = [=]()
			{
				return this->is_on_touch;
			};
			t_img->set_on_touch = [=](bool t_b)
			{
				this->is_on_touch = t_b;
			};
			
			piece_list.push_back(t_img);
		}
	}
	
	mini_map = CCSprite::createWithTexture(t_texture);
	mini_map->setScale(0.15f);
	mini_map->setAnchorPoint(ccp(0,1));
	mini_map->setPosition(ccp(0, myDSH->ui_top));
	addChild(mini_map);
}

void PieceGame::changePosition(CCPoint before_position, CCPoint after_touch_point, PieceOne* touched_target)
{
	bool is_found = false;
	for(int i=0;!is_found && i<piece_list.size();i++)
	{
		if(piece_list[i] == touched_target)
			continue;
		
		if(piece_list[i]->isContainsPoint(after_touch_point))
		{
			is_found = true;
			touched_target->CCSprite::setPosition(piece_list[i]->CCSprite::getPosition());
			piece_list[i]->CCSprite::setPosition(before_position);
		}
	}
	
	if(!is_found)
	{
		touched_target->CCSprite::setPosition(before_position);
	}
	
	bool is_all_on = true;
	for(int i=0;is_all_on && i<piece_list.size();i++)
	{
		if(!piece_list[i]->CCSprite::getPosition().equals(piece_list[i]->on_point))
			is_all_on = false;
	}
	
	if(is_all_on)
	{
		is_on_touch = true;
		KSLabelTTF* success_label = KSLabelTTF::create("성공!!", mySGD->getFont().c_str(), 35);
		success_label->setColor(ccGREEN);
		success_label->enableOuterStroke(ccBLACK, 1.f, 255, true);
		success_label->setPosition(ccp(0,0));
		success_label->setRotation(-15);
		success_label->setScale(5.f);
		success_label->setOpacity(0);
		target_node->addChild(success_label);
		
		addChild(KSGradualValue<int>::create(0, 255, 1.f, [=](int t_i)
											 {
												 success_label->setOpacity(t_i);
											 }, [=](int t_i)
											 {
												 success_label->setOpacity(t_i);
											 }));
		addChild(KSGradualValue<float>::create(5.f, 1.f, 1.f, [=](float t_f)
											   {
												   success_label->setScale(t_f);
											   }, [=](float t_f)
											   {
												   success_label->setScale(t_f);
												   addChild(KSTimer::create(0.5f, [=]()
																   {
																	   success_label->removeFromParent();
																	   initGame();
																	   addChild(KSTimer::create(0.1f, [=]()
																								{
																									for(int i=0;i<piece_list.size();i++)
																									{
																										piece_list[i]->CCLayer::onEnter();
																										piece_list[i]->setTouchEnabled(true);
																									}
																								}));
																   }));
											   }));
	}
}

void PieceGame::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
	
	addChild(KSTimer::create(0.1f, [=]()
							 {
								 for(int i=0;i<piece_list.size();i++)
								 {
									 piece_list[i]->CCLayer::onEnter();
									 piece_list[i]->setTouchEnabled(true);
								 }
							 }));
}

void PieceGame::scrollViewDidScroll(CCScrollView* view)
{
	target_node->setPositionY(myDSH->ui_center_y + (view->getContentOffset().y-view->minContainerOffset().y/2.f));
}
void PieceGame::scrollViewDidZoom(CCScrollView* view)
{
	target_node->setScale(430.f/320.f * view->getZoomScale());
	if(mini_map)
		mini_map->setScale(0.15f/view->getZoomScale());
	CCPoint oldPoint, min, max;
	float newX, newY;
	
	min = view->minContainerOffset();
	max = view->maxContainerOffset();
	
	oldPoint = view->getContentOffset();
	
	newX     = oldPoint.x;
	newY     = oldPoint.y;
	
	newY     = MIN(newY, max.y);
	newY     = MAX(newY, min.y);
	
	
	if (newY != oldPoint.y || newX != oldPoint.x)
	{
		view->setContentOffset(ccp(newX, newY), false);
	}
}