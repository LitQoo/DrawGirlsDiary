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
#include "CCMenuLambda.h"
#include "GamePausePopup.h"
#include "MyLocalization.h"
#include "LoadingLayer.h"
#include "ASPopupView.h"

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
	t_po->init();
	t_po->myInit(t_texture, t_rect);
	t_po->autorelease();
	return t_po;
}

void PieceOne::myInit(CCTexture2D* t_texture, CCRect t_rect)
{
	cell_img = CCSprite::createWithTexture(t_texture, t_rect);
	cell_img->setPosition(ccpFromSize(cell_img->getContentSize()/2.f));
	addChild(cell_img);
}

bool PieceOne::isContainsPoint(CCPoint t_point)
{
	CCPoint touchLocation = t_point;
	CCPoint local = convertToNodeSpace(touchLocation);
	
	CCRect t_rect = CCRectMake(0, 0, cell_img->getContentSize().width, cell_img->getContentSize().height);
	return t_rect.containsPoint(local);
}

bool PieceOne::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	if(check_on_touch())
		return false;
	
	before_touch_position = getPosition();
	CCPoint touchLocation = pTouch->getLocation();
	touch_begin_point = touchLocation;
	touch_move_point = touch_begin_point;
	CCPoint local = convertToNodeSpace(touchLocation);
	
	CCRect t_rect = CCRectMake(0, 0, cell_img->getContentSize().width, cell_img->getContentSize().height);
	if(t_rect.containsPoint(local))
	{
		cell_img->setColor(ccGRAY);
		getParent()->reorderChild((CCSprite*)this, 1);
		set_on_touch(true);
		touch_light_func(getPosition(), false);
		return true;
	}
	else
		return false;
}
void PieceOne::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
	CCPoint touchLocation = pTouch->getLocation();
	setPosition(getPosition() + ccpMult(touchLocation - touch_move_point, 1.f/getParent()->getScale()));
	touch_move_point = touchLocation;
	touch_light_func(getPosition(), false);
}
void PieceOne::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	cell_img->setColor(ccWHITE);
	getParent()->reorderChild((CCSprite*)this, 0);
	CCPoint touchLocation = pTouch->getLocation();
	change_position(before_touch_position, touchLocation, this);
	set_on_touch(false);
	touch_light_func(getPosition(), true);
}
void PieceOne::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{
	cell_img->setColor(ccWHITE);
	getParent()->reorderChild((CCSprite*)this, 0);
	CCPoint touchLocation = pTouch->getLocation();
	change_position(before_touch_position, touchLocation, this);
	set_on_touch(false);
	touch_light_func(getPosition(), true);
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
	
	is_menu_enable = false;
	is_on_touch = false;
	
	srand(time(NULL));
	
	light_img = NULL;
	
	CCSprite* main_back = CCSprite::create("main_back.png");
	main_back->setPosition(ccp(240,myDSH->ui_center_y));
	addChild(main_back);
	
	target_node = CCNode::create();
	target_node->setScale((430.f-14.f)/320.f);
	addChild(target_node, 1);
	
	CCSprite* t_container = CCSprite::create("whitepaper2.png", CCRectMake(0, 0, 40, 430.f*target_node->getScale()));
	
	t_controler = ZoomScrollView::create(CCSizeMake(40, myDSH->ui_top));
	t_controler->setPosition(ccp(0,0));
	t_controler->setDirection(CCScrollViewDirection::kCCScrollViewDirectionVertical);
	t_controler->setContainer(t_container);
	t_controler->setDelegate(this);
	addChild(t_controler);
	t_controler->setTouchEnabled(false);
	
	map_case = NULL;
	mini_map = NULL;
	
	img_case = NULL;
	img_back = NULL;
	
	piece_list.clear();
	
	if(myDSH->is_linked)
	{
		CCSprite* life_stone_back = CCSprite::create("subapp_stonecount.png");
		life_stone_back->setPosition(ccp(life_stone_back->getContentSize().width/2.f - 4, myDSH->ui_top - 50 - life_stone_back->getContentSize().height/2.f));
		addChild(life_stone_back, 2);
		
		KSLabelTTF* life_stone_label = KSLabelTTF::create(myLoc->getLocalForKey(kMyLocalKey_haveLifeStoneCount), mySGD->getFont().c_str(), 11);
		life_stone_label->enableOuterStroke(ccBLACK, 1, 128, true);
		life_stone_label->setPosition(ccpFromSize(life_stone_back->getContentSize()/2.f) + ccp(0,9));
		life_stone_back->addChild(life_stone_label);
		
		life_stone_count = KSLabelTTF::create(ccsf("%d", mySGD->getGoodsValue(GoodsType::kGoodsType_pass6)), mySGD->getFont().c_str(), 18);
		life_stone_count->setColor(ccc3(255, 170, 20));
		life_stone_count->enableOuterStroke(ccBLACK, 1, 128, true);
		life_stone_count->setAnchorPoint(ccp(0,0.5f));
		life_stone_count->setPosition(ccpFromSize(life_stone_back->getContentSize()/2.f) + ccp(0,-9));
		life_stone_back->addChild(life_stone_count);
	}
	
	
	createPauseMenu();
	
	size_value = 1;
	initGame();
	
	return true;
}

void PieceGame::createPauseMenu()
{
	CCSprite* n_pause = CCSprite::create("subapp_stop.png");
	KSLabelTTF* n_menu = KSLabelTTF::create(myLoc->getLocalForKey(kMyLocalKey_menu), mySGD->getFont().c_str(), 15);
	n_menu->enableOuterStroke(ccBLACK, 1.f, 170, true);
	n_menu->setPosition(ccpFromSize(n_pause->getContentSize()/2.f));
	n_pause->addChild(n_menu);
	CCSprite* s_pause = CCSprite::create("subapp_stop.png");
	s_pause->setColor(ccGRAY);
	KSLabelTTF* s_menu = KSLabelTTF::create(myLoc->getLocalForKey(kMyLocalKey_menu), mySGD->getFont().c_str(), 15);
	s_menu->enableOuterStroke(ccBLACK, 1.f, 170, true);
	s_menu->setPosition(ccpFromSize(s_pause->getContentSize()/2.f));
	s_pause->addChild(s_menu);
	
	CCMenuItemSpriteLambda* pause_item = CCMenuItemSpriteLambda::create(n_pause, s_pause, [=](CCObject* sender)
																		{
																			if(!is_menu_enable || is_on_touch)
																				return;
																			
																			is_menu_enable = false;
																			is_on_touch = true;
																			
																			AudioEngine::sharedInstance()->playEffect("se_button1.mp3", false);
																			
																			GamePausePopup* t_popup = GamePausePopup::create(-300, [=]()
																															 {
																																 is_menu_enable = true;
																																 is_on_touch = false;
																															 }, [=]()
																															 {
																																 initGame();
																															 }, [=](int t_i)
																															 {
																																 size_value = t_i;
																																 initGame();
																															 });
																			addChild(t_popup, 999);
																		});
	pause_item->setPosition(ccp(n_pause->getContentSize().width/2.f - 4, myDSH->ui_top - n_pause->getContentSize().height/2.f));
	
	CCMenuLambda* ui_menu = CCMenuLambda::create();
	ui_menu->setPosition(CCPointZero);
	addChild(ui_menu, 2);
	ui_menu->setTouchPriority(-200);
	
	ui_menu->addChild(pause_item);
}

void PieceGame::onSizeMenu()
{
	CCSprite* back_img = CCSprite::create("whitePaper.png", CCRectMake(0, 0, 170, 280));
	back_img->setPosition(ccp(240,myDSH->ui_center_y));
	addChild(back_img, 4);
	
	CCSprite* gray = CCSprite::create("whitePaper.png");
	gray->setColor(ccBLACK);
	gray->setOpacity(100);
	gray->setScaleY(myDSH->ui_top/320.f);
	gray->setPosition(ccpFromSize(back_img->getContentSize()/2.f));
	back_img->addChild(gray, -1);
	
	CCMenuLambda* size_menu = CCMenuLambda::create();
	size_menu->setPosition(ccpFromSize(back_img->getContentSize()/2.f));
	back_img->addChild(size_menu);
	
	CCSprite* n_1 = CCSprite::create("whitePaper.png", CCRectMake(0, 0, 150, 60));
	n_1->setColor(ccGREEN);
	CCSprite* s_1 = CCSprite::create("whitePaper.png", CCRectMake(0, 0, 150, 60));
	s_1->setColor(ccGRAY);
	
	CCMenuItemSpriteLambda* item_1 = CCMenuItemSpriteLambda::create(n_1, s_1, [=](CCObject* sender)
																	{
																		if(!is_menu_enable)
																			return;
																		
																		is_menu_enable = false;
																		
																		createPauseMenu();
																		
																		size_value = 1;
																		initGame();
																		back_img->removeFromParent();
																	});
	item_1->setPosition(ccp(0,5+60+10+30));
	size_menu->addChild(item_1);
	
	CCSprite* n_2 = CCSprite::create("whitePaper.png", CCRectMake(0, 0, 150, 60));
	n_2->setColor(ccc3(0, 255, 255));
	CCSprite* s_2 = CCSprite::create("whitePaper.png", CCRectMake(0, 0, 150, 60));
	s_2->setColor(ccGRAY);
	
	CCMenuItemSpriteLambda* item_2 = CCMenuItemSpriteLambda::create(n_2, s_2, [=](CCObject* sender)
																	{
																		if(!is_menu_enable)
																			return;
																		
																		is_menu_enable = false;
																		
																		createPauseMenu();
																		
																		size_value = 2;
																		initGame();
																		back_img->removeFromParent();
																	});
	item_2->setPosition(ccp(0,5+30));
	size_menu->addChild(item_2);
	
	CCSprite* n_3 = CCSprite::create("whitePaper.png", CCRectMake(0, 0, 150, 60));
	n_3->setColor(ccc3(0, 0, 255));
	CCSprite* s_3 = CCSprite::create("whitePaper.png", CCRectMake(0, 0, 150, 60));
	s_3->setColor(ccGRAY);
	
	CCMenuItemSpriteLambda* item_3 = CCMenuItemSpriteLambda::create(n_3, s_3, [=](CCObject* sender)
																	{
																		if(!is_menu_enable)
																			return;
																		
																		is_menu_enable = false;
																		
																		createPauseMenu();
																		
																		size_value = 3;
																		initGame();
																		back_img->removeFromParent();
																	});
	item_3->setPosition(ccp(0,-5-30));
	size_menu->addChild(item_3);
	
	CCSprite* n_4 = CCSprite::create("whitePaper.png", CCRectMake(0, 0, 150, 60));
	n_4->setColor(ccc3(255, 0, 255));
	CCSprite* s_4 = CCSprite::create("whitePaper.png", CCRectMake(0, 0, 150, 60));
	s_4->setColor(ccGRAY);
	
	CCMenuItemSpriteLambda* item_4 = CCMenuItemSpriteLambda::create(n_4, s_4, [=](CCObject* sender)
																	{
																		if(!is_menu_enable)
																			return;
																		
																		is_menu_enable = false;
																		
																		createPauseMenu();
																		
																		size_value = 4;
																		initGame();
																		back_img->removeFromParent();
																	});
	item_4->setPosition(ccp(0,-5-60-10-30));
	size_menu->addChild(item_4);
	
	is_menu_enable = true;
}

void PieceGame::touchLightCase(CCPoint t_position, bool is_end)
{
	if(is_end)
	{
		if(light_img)
		{
			light_img->removeFromParent();
			light_img = NULL;
		}
		
		return;
	}
	
	CCSize light_size;
	if(size_value == 1)
		light_size = CCSizeMake(100, 100);
	else if(size_value == 2)
		light_size = CCSizeMake(80, 80);
	else if(size_value == 3)
		light_size = CCSizeMake(60, 60);
	else if(size_value == 4)
		light_size = CCSizeMake(50, 50);
	
	if(!light_img)
	{
		light_img = CCScale9Sprite::create("common_select.png", CCRectMake(0, 0, 34, 34), CCRectMake(16, 16, 2, 2));
		light_img->setContentSize(light_size + CCSizeMake(10,10));
		target_node->addChild(light_img, 2);
	}
	
	light_img->setPosition(t_position + ccpFromSize(light_size/2.f));
}

void PieceGame::initGame()
{
	if(mini_map)
	{
		mini_map->removeFromParent();
		mini_map = NULL;
	}
	
	if(map_case)
	{
		map_case->removeFromParent();
		map_case = NULL;
	}
	
	if(img_case)
	{
		img_case->removeFromParent();
		img_case = NULL;
	}
	
	if(img_back)
	{
		img_back->removeFromParent();
		img_back = NULL;
	}
	
	for(int i=0;i<piece_list.size();i++)
	{
		piece_list[i]->CCLayer::onExit();
	}
	
	img_back = CCSprite::create("subapp_frame_back.png");
	img_back->setPosition(ccp(290,myDSH->ui_center_y));
	img_back->setScaleX(380.f/img_back->getContentSize().width);
	img_back->setScaleY(myDSH->ui_top/img_back->getContentSize().height);
	addChild(img_back);
	
	img_case = CCScale9Sprite::create("subapp_frame.png", CCRectMake(0, 0, 360, 320), CCRectMake(6, 6, 348, 308));
	img_case->setPosition(ccp(290,myDSH->ui_center_y));
	img_case->setContentSize(CCSizeMake(380, myDSH->ui_top));
	addChild(img_case);
	
	target_node->removeAllChildren();
	target_node->setScale((430.f-14.f)/320.f);
	target_node->setPosition(ccp(290,myDSH->ui_center_y));
	t_controler->setZoomScale(1.f);
	t_controler->setContentOffset(ccp(0,t_controler->minContainerOffset().y/2.f));
	
	CCTexture2D* t_texture;
	
	if(myDSH->is_linked && mySGD->getHasGottenCardsSize() > 0)
	{
		int has_gotten_card_size = mySGD->getHasGottenCardsSize();
		int random_value = rand()%has_gotten_card_size;
		
		CardSortInfo t_info = mySGD->getHasGottenCardData(random_value);
		
		t_texture = mySIL->addImage(ccsf("card%d_visible.png", t_info.card_number.getV()));
	}
	else
	{
		t_texture = CCTextureCache::sharedTextureCache()->addImage(ccsf("default_img%d.png", rand()%10+1));
	}
	
	batch_node = CCSpriteBatchNode::createWithTexture(t_texture);
	batch_node->setPosition(ccp(0,0));
	target_node->addChild(batch_node);
	
	float vertical_height, horizen_width;
	int width_cnt, height_cnt;
	float box_size;
	if(size_value == 1)
	{
		vertical_height = 15.f;
		horizen_width = 10.f;
		width_cnt = 3;
		height_cnt = 4;
		box_size = 100.f;
	}
	else if(size_value == 2)
	{
		vertical_height = 15.f;
		horizen_width = 0.f;
		width_cnt = 4;
		height_cnt = 5;
		box_size = 80.f;
	}
	else if(size_value == 3)
	{
		vertical_height = 5.f;
		horizen_width = 10.f;
		width_cnt = 5;
		height_cnt = 7;
		box_size = 60.f;
	}
	else if(size_value == 4)
	{
		vertical_height = 15.f;
		horizen_width = 10.f;
		width_cnt = 6;
		height_cnt = 8;
		box_size = 50.f;
	}
	
	CCSprite* top_img = CCSprite::createWithTexture(t_texture, CCRectMake(0, 0, 320, vertical_height));
	top_img->setPosition(ccp(0,215-vertical_height/2.f));
	batch_node->addChild(top_img);
	
	CCSprite* bottom_img = CCSprite::createWithTexture(t_texture, CCRectMake(0, 430-vertical_height, 320, vertical_height));
	bottom_img->setPosition(ccp(0,-215+vertical_height/2.f));
	batch_node->addChild(bottom_img);
	
	if(horizen_width >= 1.f)
	{
		CCSprite* left_img = CCSprite::createWithTexture(t_texture, CCRectMake(0, vertical_height, horizen_width, 430-vertical_height*2.f));
		left_img->setPosition(ccp(-160 + horizen_width/2.f, 0));
		batch_node->addChild(left_img);
		
		CCSprite* right_img = CCSprite::createWithTexture(t_texture, CCRectMake(320-horizen_width, vertical_height, horizen_width, 430-vertical_height*2.f));
		right_img->setPosition(ccp(160 - horizen_width/2.f, 0));
		batch_node->addChild(right_img);
	}
	
	vector<int> rand_list;
	rand_list.clear();
	for(int j=0;j<height_cnt;j++)
	{
		for(int i=0;i<width_cnt;i++)
		{
			rand_list.push_back(i + j*width_cnt);
		}
	}
	
	random_shuffle(rand_list.begin(), rand_list.end());
	
	piece_list.clear();
	
	for(int j=0;j<height_cnt;j++)
	{
		for(int i=0;i<width_cnt;i++)
		{
			int pos_i = rand_list[i + j*width_cnt]%width_cnt;
			int pos_j = rand_list[i + j*width_cnt]/width_cnt;
			
			PieceOne* t_img = PieceOne::createWithTexture(t_texture, CCRectMake(horizen_width + i*box_size, 430 - (vertical_height+(j+1)*box_size), box_size, box_size));
			t_img->setAnchorPoint(CCPointZero);
			t_img->setPosition(ccp(-160 + horizen_width,-215 + vertical_height) + ccp(pos_i*box_size,pos_j*box_size));
			target_node->addChild((CCSprite*)t_img);
			t_img->on_point = ccp(-160 + horizen_width,-215 + vertical_height) + ccp(i*box_size,j*box_size);
			
			t_img->change_position = bind(&PieceGame::changePosition, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
			t_img->check_on_touch = [=]()
			{
				return this->is_on_touch;
			};
			t_img->set_on_touch = [=](bool t_b)
			{
				this->is_on_touch = t_b;
			};
			t_img->touch_light_func = bind(&PieceGame::touchLightCase, this, std::placeholders::_1, std::placeholders::_2);
			
			piece_list.push_back(t_img);
		}
	}
	
	mini_map = CCSprite::createWithTexture(t_texture);
	mini_map->setScale(0.27f);
	mini_map->setAnchorPoint(ccp(0,0));
	mini_map->setPosition(ccp(2, 4) + ccp(4,4));
	addChild(mini_map);
	
	map_case = CCSprite::create("guide_frame.png");
	map_case->setPosition(ccpFromSize(map_case->getContentSize()/2.f) + ccp(2,5));
	addChild(map_case);
	
	t_controler->setZoomScale(myDSH->ui_top/(430.f * (430.f/320.f)));
	target_node->setPositionY(myDSH->ui_center_y);
	
	is_on_touch = false;
	is_menu_enable = true;
	
	addChild(KSTimer::create(0.1f, [=]()
							 {
								 for(int i=0;i<piece_list.size();i++)
								 {
									 piece_list[i]->CCLayer::onEnter();
									 piece_list[i]->setTouchEnabled(true);
								 }
							 }));
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
			touched_target->setPosition(piece_list[i]->getPosition());
			piece_list[i]->setPosition(before_position);
		}
	}
	
	if(!is_found)
	{
		touched_target->setPosition(before_position);
	}
	
	bool is_all_on = true;
	for(int i=0;is_all_on && i<piece_list.size();i++)
	{
		if(!piece_list[i]->getPosition().equals(piece_list[i]->on_point))
			is_all_on = false;
	}
	
	if(is_all_on)
	{
		is_on_touch = true;
		success_label = KSLabelTTF::create("성공!!", mySGD->getFont().c_str(), 35);
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
												   
												   if(myDSH->is_linked)
													{
														// 통신해서 생명의 돌 줌
														t_loading = LoadingLayer::create(-99999, true);
														addChild(t_loading, 99999);
														t_loading->startLoading();
														
														string ex_id;
														if(size_value == 1)
															ex_id = "diaryRewardLow";
														else if(size_value == 2)
															ex_id = "diaryRewardMid";
														else if(size_value == 3)
															ex_id = "diaryRewardHigh";
														else if(size_value == 4)
															ex_id = "diaryRewardTopHigh";
														
														mySGD->addChangeGoods(ex_id.c_str());
														mySGD->changeGoods(json_selector(this, PieceGame::resultReward));
													}
												   else
													{
														addChild(KSTimer::create(0.5f, [=]()
																				 {
																					 success_label->removeFromParent();
																					 initGame();
																				 }));
													}
											   }));
	}
}

void PieceGame::resultReward(Json::Value result_data)
{
	if(result_data["result"]["code"].asInt() == GDSUCCESS)
	{
		t_loading->removeFromParent();
		
		mySGD->network_check_cnt = 0;
		
		life_stone_count->setString(ccsf("%d", mySGD->getGoodsValue(GoodsType::kGoodsType_pass6)));
		addChild(KSTimer::create(0.5f, [=]()
								 {
									 success_label->removeFromParent();
									 initGame();
								 }));
	}
	else
	{
		mySGD->network_check_cnt++;
		
		if(mySGD->network_check_cnt >= mySGD->max_network_check_cnt)
		{
			mySGD->network_check_cnt = 0;
			
			ASPopupView *alert = ASPopupView::getCommonNotiTag(-99999,myLoc->getLocalForKey(kMyLocalKey_reConnect), myLoc->getLocalForKey(kMyLocalKey_reConnectAlert4),[=](){
				mySGD->changeGoods(json_selector(this, PieceGame::resultReward));
			}, 1);
			if(alert)
				((CCNode*)CCDirector::sharedDirector()->getRunningScene()->getChildren()->objectAtIndex(0))->addChild(alert,999999);
		}
		else
		{
			addChild(KSTimer::create(0.5f, [=]()
									 {
										 mySGD->changeGoods(json_selector(this, PieceGame::resultReward));
									 }));
		}
	}
}

void PieceGame::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
}

void PieceGame::scrollViewDidScroll(CCScrollView* view)
{
	target_node->setPositionY(myDSH->ui_center_y + (view->getContentOffset().y-view->minContainerOffset().y/2.f));
}
void PieceGame::scrollViewDidZoom(CCScrollView* view)
{
	target_node->setScale((430.f-14.f)/320.f * view->getZoomScale());
//	if(mini_map)
//		mini_map->setScale(0.2f/view->getZoomScale());
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