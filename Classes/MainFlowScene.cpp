//
//  MainFlowScene.cpp
//  DGproto
//
//  Created by 사원3 on 2013. 12. 16..
//
//

#include "MainFlowScene.h"
#include "DataStorageHub.h"
#include "CountingBMLabel.h"
#include "StarGoldData.h"
#include "HeartTime.h"
#include "ShopPopup.h"
#include "OptionPopup.h"
#include "RankPopup.h"
#include "CardSettingPopup.h"
#include "GachaPurchase.h"
#include "EventPopup.h"
#include "ServerDataSave.h"
#include "ASPopupView.h"
#include "NoticeContent.h"
#include "TicketRequestContent.h"
#include "PuzzleScene.h"
#include "StageListDown.h"
#include "AchievePopup.h"
#include "TutorialFlowStep.h"
#include "ClearPopup.h"
#include "FailPopup.h"
#include "AlertEngine.h"
#include "PuzzleListShadow.h"
#include "InviteEventPopup.h"
#include "TouchSuctionLayer.h"
#include "ScrollMenu.h"
#include "MyLocalization.h"
#include "NewMainFlowScene.h"
#include "RankNewPopup.h"
#include "SumranMailPopup.h"
#include "LoadingLayer.h"
#include "KSLabelTTF.h"
#include "DetailConditionPopup.h"
#include "GoodsLight.h"
#include "TodayMissionPopup.h"
#include "AttendancePopup.h"
#include "PuzzleSuccessAndPerfect.h"
#include "EndlessModeOpening.h"
#include "EndlessModeResult.h"
#include "FormSetter.h"
#include "AchieveNoti.h"
#include "CommonAnimation.h"
#include "RankRewardPopup.h"
#include "TakePuzzleCardPopup.h"
#include "TypingBox.h"
#include "CollectionBookPopup.h"
#include "SDiaryInformationPopup.h"

CCScene* MainFlowScene::scene()
{
    CCScene *scene = CCScene::create();
    
    MainFlowScene *layer = MainFlowScene::create();
	layer->setAnchorPoint(ccp(0.5,0));
	layer->setScale(myDSH->screen_convert_rate);
	layer->setPosition(ccpAdd(layer->getPosition(), myDSH->ui_zero_point));
    scene->addChild(layer, 0, 1);
	
    return scene;
}

bool MainFlowScene::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
	CCLog("%s %d", __FILE__, __LINE__);
	setKeypadEnabled(true);
	
//	kind_tutorial_pvp = nullptr;
//	refresh_ing_win_func = nullptr;
//	
//	is_table_openning = false;
//    TRACE();
//	callTimeInfo();
//	
//    TRACE();
//	have_card_count_for_puzzle_index.clear();
//	
//	not_event_puzzle_list.clear();
//	
//	int puzzle_count = NSDS_GI(kSDS_GI_puzzleListCount_i);
//	for(int i=1;i<=puzzle_count;i++)
//	{
//		int t_puzzle_number = NSDS_GI(kSDS_GI_puzzleList_int1_no_i, i);
//		
//		if(!NSDS_GB(t_puzzle_number, kSDS_PZ_isEvent_b))
//		{
//			int have_card_cnt = 0;
//			int start_stage = NSDS_GI(t_puzzle_number, kSDS_PZ_startStage_i);
//			int stage_count = NSDS_GI(t_puzzle_number, kSDS_PZ_stageCount_i);
//			
//			int card_take_cnt = mySGD->getHasGottenCardsSize();
//			for(int i=0;i<card_take_cnt;i++)
//			{
//				int card_number = mySGD->getHasGottenCardsDataCardNumber(i);
//				int card_stage_number = NSDS_GI(kSDS_CI_int1_stage_i, card_number);
//				if(card_stage_number >= start_stage && card_stage_number < start_stage+stage_count)
//					have_card_cnt += NSDS_GI(kSDS_CI_int1_grade_i, card_number);
//			}
//			
//			have_card_count_for_puzzle_index.push_back(have_card_cnt);
//		
//		
//			not_event_puzzle_list.push_back(t_puzzle_number);
//		}
//	}
//	
//	is_puzzle_enter_list.clear();
//	
//    TRACE();
//	locked_puzzle_count = 0;
//	
//    TRACE();
//	for(int i=0;i<not_event_puzzle_list.size();i++)
//	{
//		int t_puzzle_number = not_event_puzzle_list[i];
//		
//		PuzzleOpenInfo t_info;
//		t_info.is_open = mySGD->getPuzzleHistory(t_puzzle_number).is_open.getV();
//		
//		string puzzle_condition = NSDS_GS(t_puzzle_number, kSDS_PZ_condition_s);
//		
//		Json::Value condition_list;
//		Json::Reader reader;
//		reader.parse(puzzle_condition, condition_list);
//		
//        TRACE();
//		if(condition_list.size() <= 0)
//			t_info.is_open = true;
//		
//		t_info.is_base_condition_success = true;
//		t_info.is_have_week_condition = false;
//		t_info.is_have_date_condition = false;
//		t_info.is_have_ruby_condition = false;
//		t_info.need_star_count = 0;
//		
//		for(int i=0;!t_info.is_open && i<condition_list.size();i++)
//		{
//			Json::Value t_condition_and = condition_list[i];
//			
//			bool and_open = true;
//			bool is_time_condition = false;
//			
//			for(int j=0;j<t_condition_and.size();j++)
//			{
//				Json::Value t_condition = t_condition_and[j];
//				string t_type = t_condition["type"].asString();
//				if(t_type == "p")
//				{
//					if(!mySGD->getPuzzleHistory(t_condition["value"].asInt()).is_clear)
//					{
//						and_open = false;
//						t_info.is_base_condition_success = false;
//					}
//				}
//				else if(t_type == "s")
//				{
//					t_info.need_star_count = t_condition["value"].asInt();
//					if(mySGD->getClearStarCount() < t_info.need_star_count)
//					{
//						and_open = false;
//						t_info.is_base_condition_success = false;
//					}
//				}
//				else if(t_type == "r")
//				{
//					t_info.need_ruby_value = t_condition["value"].asInt();
//					and_open = false;
//					t_info.is_have_ruby_condition = true;
//				}
//				else if(t_type == "w")
//				{
//					is_time_condition = true;
//					t_info.is_have_week_condition = true;
//					if(!mySGD->keep_time_info.is_loaded)
//						and_open = false;
//					else
//					{
//						int weekday = t_condition["weekday"].asInt();
//						t_info.keep_weekday = weekday;
//						if(mySGD->keep_time_info.weekday.getV() != -1 && mySGD->keep_time_info.weekday.getV() != weekday)
//							and_open = false;
//						t_info.keep_week_start = t_condition["s"].asInt();
//						t_info.keep_week_end = t_condition["e"].asInt();
//						if(mySGD->keep_time_info.hour.getV() < t_condition["s"].asInt() || mySGD->keep_time_info.hour.getV() >= t_condition["e"].asInt())
//							and_open = false;
//					}
//				}
//				else if(t_type == "d")
//				{
//					is_time_condition = true;
//					t_info.is_have_date_condition = true;
//					t_info.keep_date_start = t_condition["s"].asString();
//					if(mySGD->keep_time_info.date.getV() < t_condition["s"].asInt64() || mySGD->keep_time_info.date.getV() >= t_condition["e"].asInt64())
//						and_open = false;
//				}
//			}
//			
//            TRACE();
//			if(and_open)
//			{
//				t_info.is_open = true;
//				if(!is_time_condition)
//				{
//					PuzzleHistory t_history = mySGD->getPuzzleHistory(t_puzzle_number);
//					t_history.is_open = true;
//					t_history.open_type = "무료";
//					mySGD->setPuzzleHistory(t_history, nullptr);
//				}
//			}
//		}
//		
//		t_info.before_locked_puzzle_count = locked_puzzle_count;
//		t_info.puzzle_number = t_puzzle_number;
//		is_puzzle_enter_list.push_back(t_info);
//		
//		if(!t_info.is_open)
//			locked_puzzle_count++;
//	}
	
    TRACE();
	CCSprite* back_img = CCSprite::create("main_back.png");
	back_img->setPosition(ccp(240,160));
	addChild(back_img, kMainFlowZorder_back);
	
	CCSize screen_size = CCEGLView::sharedOpenGLView()->getFrameSize();
	float screen_scale_x = screen_size.width/screen_size.height/1.5f;
	if(screen_scale_x < 1.f)
		screen_scale_x = 1.f;
	
	if(mySGD->getMustBeShowNotice())
	{
		ASPopupView* t_popup = ASPopupView::create(-9999999);
		
		float height_value = 320.f;
		if(myDSH->screen_convert_rate < 1.f)
			height_value = 320.f/myDSH->screen_convert_rate;
		
		if(height_value < myDSH->ui_top)
			height_value = myDSH->ui_top;
		
		TRACE();
		t_popup->setDimmedSize(CCSizeMake(screen_scale_x*480.f, height_value));// /myDSH->screen_convert_rate));
		t_popup->setDimmedPosition(ccp(240, 160));
		t_popup->setBasePosition(ccp(240, 160));
		
		TRACE();
		NoticeContent* t_container = NoticeContent::create(t_popup->getTouchPriority(), [=](CCObject* sender)
														   {
															   TRACE();
															   t_popup->removeFromParent();
														   }, mySGD->getNoticeList());
		t_popup->setContainerNode(t_container);
		addChild(t_popup, kMainFlowZorder_popup+9999999);
	}

	if(myDSH->getIntegerForKey(kDSH_Key_exeCnt)%3 == 0)
	{
		SDiaryInformationPopup* t_popup = SDiaryInformationPopup::create(-999999, [=](){});
		addChild(t_popup, kMainFlowZorder_popup+999999);
	}
	
	myDSH->setIntegerForKey(kDSH_Key_exeCnt, myDSH->getIntegerForKey(kDSH_Key_exeCnt)+1);
	
	
//    TRACE();
//	start_unlock_animation = nullptr;
//
//	is_unlock_puzzle = mySGD->getIsUnlockPuzzle();
//	is_perfect_puzzle = mySGD->getIsPerfectPuzzle();
//	
//    TRACE();
//	setTable();
//	
//    TRACE();
//	CCSize screen_size = CCEGLView::sharedOpenGLView()->getFrameSize();
//	float screen_scale_x = screen_size.width/screen_size.height/1.5f;
//	if(screen_scale_x < 1.f)
//		screen_scale_x = 1.f;
//
////	CCSprite* back_shadow_left = CCSprite::create("mainflow_back_shadow_left.png");
////	back_shadow_left->setAnchorPoint(ccp(0.f,0.5f));
////	back_shadow_left->setPosition(ccp(-(screen_scale_x-1.f)*480.f/2.f,160));
////	addChild(back_shadow_left, kMainFlowZorder_top);
////	
////	CCSprite* back_shadow_right = CCSprite::create("mainflow_back_shadow_right.png");
////	back_shadow_right->setAnchorPoint(ccp(1.f,0.5f));
////	back_shadow_right->setPosition(ccp(480+(screen_scale_x-1.f)*480.f/2.f,160));
////	addChild(back_shadow_right, kMainFlowZorder_top);
//	
//    TRACE();
//	setTop();
//    TRACE();
//	setBottom();
//	
//    TRACE();
//	bool is_openning = false;
//	
//	if(mySGD->is_endless_mode && myDSH->getPuzzleMapSceneShowType() == kPuzzleMapSceneShowType_init)
//	{
//		mySGD->is_endless_mode = false;
//	}
//	
//	if(mySGD->is_endless_mode)
//	{
//        TRACE();
//		is_menu_enable = true;
//	}
//	else if(myDSH->getPuzzleMapSceneShowType() == kPuzzleMapSceneShowType_init) // 실행 후 첫 접근시
//	{
//        TRACE();
//		AudioEngine::sharedInstance()->playSound("bgm_ui.mp3", true);
//		
//		is_openning = true;
//		topOpenning();
//		bottomOpenning();
//		
//		if(mySGD->getMustBeShowNotice())
//		{
//			ASPopupView* t_popup = ASPopupView::create(-9999999);
//			
//			float height_value = 320.f;
//			if(myDSH->screen_convert_rate < 1.f)
//				height_value = 320.f/myDSH->screen_convert_rate;
//			
//			if(height_value < myDSH->ui_top)
//				height_value = myDSH->ui_top;
//			
//            TRACE();
//			t_popup->setDimmedSize(CCSizeMake(screen_scale_x*480.f, height_value));// /myDSH->screen_convert_rate));
//			t_popup->setDimmedPosition(ccp(240, 160));
//			t_popup->setBasePosition(ccp(240, 160));
//			
//            TRACE();
//			NoticeContent* t_container = NoticeContent::create(t_popup->getTouchPriority(), [=](CCObject* sender)
//															   {
//                                                                   TRACE();
//																   t_popup->removeFromParent();
//															   }, mySGD->getNoticeList());
//			t_popup->setContainerNode(t_container);
//			addChild(t_popup, kMainFlowZorder_popup+9999999);
//		}
//
//        TRACE();
//		myDSH->setPuzzleMapSceneShowType(kPuzzleMapSceneShowType_stage);
//		
//		is_menu_enable = true;
//        TRACE();
//	}
//	else if(myDSH->getPuzzleMapSceneShowType() == kPuzzleMapSceneShowType_stage)
//	{
//        TRACE();
//		bottomOpenning();
//		topOnLight();
//		
//        TRACE();
//		if(myDSH->getIntegerForKey(kDSH_Key_showedScenario) == 0 || (myDSH->getIntegerForKey(kDSH_Key_showedScenario)%1000 == 0 && myDSH->getIntegerForKey(kDSH_Key_showedScenario)/1000+1 == is_unlock_puzzle) || mySGD->is_on_attendance || mySGD->is_on_rank_reward || mySGD->is_today_mission_first || mySGD->is_new_puzzle_card.getV() || (myDSH->getIntegerForKey(kDSH_Key_isShowEndlessModeTutorial) == 0 && mySGD->getUserdataHighPiece() >= mySGD->getEndlessMinPiece()))
//		{
//			is_menu_enable = false;
//		}
//		else
//			is_menu_enable = true;
//		
//		CCSprite* title_name = CCSprite::create("temp_title_name.png");
//		title_name->setPosition(ccp(240,160));
//		title_name->setOpacity(255);
//		addChild(title_name, kMainFlowZorder_back);
//		
//        TRACE();
//		CCFadeTo* t_fade = CCFadeTo::create(0.5f, 0);
//		CCCallFunc* t_call = CCCallFunc::create(title_name, callfunc_selector(CCSprite::removeFromParent));
//		CCSequence* t_seq = CCSequence::create(t_fade, t_call, NULL);
//		title_name->runAction(t_seq);
//        TRACE();
//	}
//	else
//	{
//        TRACE();
//		is_menu_enable = true;
//        TRACE();
//	}
//	
//	
//	
//	
//	
//    TRACE();
//	if(mySGD->is_endless_mode)
//	{
//		mySGD->endless_my_victory_on = true;
//		is_menu_enable = false;
//		puzzle_table->setTouchEnabled(false);
//		
//        TRACE();
//		showEndlessResult();
//        TRACE();
//	}
//	else if(myDSH->getPuzzleMapSceneShowType() == kPuzzleMapSceneShowType_clear)
//	{
//        TRACE();
////		myDSH->setIntegerForKey(kDSH_Key_heartCnt, myDSH->getIntegerForKey(kDSH_Key_heartCnt)+1);
//		
//		int take_level;
//		take_level = mySGD->getStageGrade();
////		if(mySGD->is_exchanged && mySGD->is_showtime)		take_level = 4;
////		else if(mySGD->is_showtime)							take_level = 3;
////		else if(mySGD->is_exchanged)						take_level = 2;
////		else												take_level = 1;
//		
//        TRACE();
//		if(mySGD->isHasGottenCards(mySD->getSilType(), take_level) == 0)
//		{
////			mySGD->setClearRewardGold(NSDS_GI(kSDS_CI_int1_reward_i, NSDS_GI(mySD->getSilType(), kSDS_SI_level_int1_card_i, take_level)));
//		}
//		
//        TRACE();
//		mySGD->addHasGottenCardNumber(NSDS_GI(mySD->getSilType(), kSDS_SI_level_int1_card_i, take_level));
//		keep_card_number = NSDS_GI(mySD->getSilType(), kSDS_SI_level_int1_card_i, take_level);
//		
//		LoadingLayer* t_loading = LoadingLayer::create(-900);
//		addChild(t_loading, kMainFlowZorder_popup+1);
//		
//        TRACE();
//		updateCardHistory(t_loading);
//		
//        TRACE();
//		
//		myDSH->setPuzzleMapSceneShowType(kPuzzleMapSceneShowType_stage);
//		showClearPopup();
//        TRACE();
//	}
//	else if(myDSH->getPuzzleMapSceneShowType() == kPuzzleMapSceneShowType_fail)
//	{
//        TRACE();
//		myDSH->setPuzzleMapSceneShowType(kPuzzleMapSceneShowType_stage);
//		showFailPopup();
//        TRACE();
//	}
//	else
//	{
//        TRACE();
//		TutorialFlowStep recent_step = (TutorialFlowStep)myDSH->getIntegerForKey(kDSH_Key_tutorial_flowStep);
//		
//		if(recent_step == kTutorialFlowStep_puzzleClick)
//		{
//            TRACE();
//			TutorialFlowStepLayer* t_tutorial = TutorialFlowStepLayer::create();
//			t_tutorial->initStep(kTutorialFlowStep_puzzleClick);
//			addChild(t_tutorial, kMainFlowZorder_popup);
//			
//            TRACE();
//			tutorial_node = t_tutorial;
//			
//			puzzle_table->setTouchEnabled(false);
//		}
//		else if(recent_step == kTutorialFlowStep_cardCollectionClick)
//		{
//            TRACE();
//			TutorialFlowStepLayer* t_tutorial = TutorialFlowStepLayer::create();
//			t_tutorial->initStep(kTutorialFlowStep_cardCollectionClick);
//			addChild(t_tutorial, kMainFlowZorder_popup);
//			
//			tutorial_node = t_tutorial;
//			
//            TRACE();
//			puzzle_table->setTouchEnabled(false);
//		}
//		
//		if(is_unlock_puzzle > 0)
//		{
//            TRACE();
//			is_menu_enable = false;
//			puzzle_table->setTouchEnabled(false);
//            TRACE();
//		}
//		else if(is_unlock_puzzle == -1)
//		{
//            TRACE();
//			is_menu_enable = false;
//			puzzle_table->setTouchEnabled(false);
//			
//            TRACE();
//			start_unlock_animation = [=](function<void()> t_end_func)
//			{
//				ASPopupView* t_popup = ASPopupView::create(-999);
//				
//				CCSize screen_size = CCEGLView::sharedOpenGLView()->getFrameSize();
//				float screen_scale_x = screen_size.width/screen_size.height/1.5f;
//				if(screen_scale_x < 1.f)
//					screen_scale_x = 1.f;
//				
//				float height_value = 320.f;
//				if(myDSH->screen_convert_rate < 1.f)
//					height_value = 320.f/myDSH->screen_convert_rate;
//				
//                TRACE();
//				if(height_value < myDSH->ui_top)
//					height_value = myDSH->ui_top;
//				
//				t_popup->setDimmedSize(CCSizeMake(screen_scale_x*480.f, height_value));// /myDSH->screen_convert_rate));
//				t_popup->setDimmedPosition(ccp(240, 160));
//				t_popup->setBasePosition(ccp(240, 160));
//				
//				CCNode* t_container = CCNode::create();
//				t_popup->setContainerNode(t_container);
//				addChild(t_popup, kMainFlowZorder_popup);
//				
//				CCSprite* back_case = CCSprite::create("popup_small_back.png");
//				back_case->setPosition(ccp(0,0));
//				t_container->addChild(back_case);
//				
//				CCScale9Sprite* back_in = CCScale9Sprite::create("common_grayblue.png", CCRectMake(0, 0, 26, 26), CCRectMake(12, 12, 2, 2));
//				back_in->setContentSize(CCSizeMake(251, 113));
//				back_in->setPosition(ccp(back_case->getContentSize().width/2.f, back_case->getContentSize().height/2.f-14));
//				back_case->addChild(back_in);
//				
//                TRACE();
//				
//				KSLabelTTF* title_label = KSLabelTTF::create(myLoc->getLocalForKey(kMyLocalKey_allPuzzleClearTitle), mySGD->getFont().c_str(), 12);
//				title_label->disableOuterStroke();
//				title_label->setAnchorPoint(ccp(0.5f,0.5f));
//				title_label->setPosition(ccp(-85,back_case->getContentSize().height/2.f-35));
//				t_container->addChild(title_label);
//				
//				StyledLabelTTF* sub_label = StyledLabelTTF::create(myLoc->getLocalForKey(kMyLocalKey_allPuzzleClearMent), mySGD->getFont().c_str(), 12, 999, StyledAlignment::kCenterAlignment);
//				sub_label->setAnchorPoint(ccp(0.5f,0.5f));
//				sub_label->setPosition(ccpFromSize(back_in->getContentSize()/2.f)); 			// dt (0.0,-13.5)
//				back_in->addChild(sub_label);
//				
//				CCSprite* gray = t_popup->getDimmedSprite();
//				
//                TRACE();
//				CommonButton* ok_button = CommonButton::createCloseButton(t_popup->getTouchPriority() - 5);
//				ok_button->setFunction([=](CCObject*){
//					if(!t_popup->is_menu_enable)
//						return;
//					
//					t_popup->is_menu_enable = false;
//					
//					CommonAnimation::closePopup(t_popup, t_container, gray, [=](){
//						
//					}, [=](){
//                        TRACE();
//						endUnlockAnimation();
//						t_end_func();
//						t_popup->removeFromParent();
//					});
//				});
//				t_container->addChild(ok_button);
//				ok_button->setPosition(ccpFromSize(back_case->getContentSize()/2.f) + ccp(-25,-22)); 			// dt (1.5,-18.5)
//				ok_button->setTouchPriority(t_popup->getTouchPriority()-5);
//				setFormSetter(ok_button);
//				
//				
//				CommonAnimation::openPopup(this, t_container, gray, [=](){
//					
//				}, [=](){
//					t_popup->is_menu_enable = true;
//				});
//			};
//			is_unlock_puzzle = 0;
//			mySGD->setIsUnlockPuzzle(is_unlock_puzzle);
//		}
//		
//        TRACE();
//		tableOpenning();
//		if(!is_openning)
//			topReturnMode();
//        TRACE();
//	}
//	
//    TRACE();
////	if(!myDSH->getBoolForKey(kDSH_Key_was_opened_tutorial_dimed_main))
////	{
////		myDSH->setBoolForKey(kDSH_Key_was_opened_tutorial_dimed_main, true);
////		TouchSuctionLayer* t_suction = TouchSuctionLayer::create(-200);
////		t_suction->target_touch_began = t_suction;
////		t_suction->delegate_touch_began = callfunc_selector(TouchSuctionLayer::removeFromParent);
////		t_suction->setTouchEnabled(true);
////
////		CCSprite* dimed_tip = CCSprite::create("tutorial_dimed_main.png");
////		dimed_tip->setPosition(ccp(240,160));
////		t_suction->addChild(dimed_tip);
////
////		addChild(t_suction, kMainFlowZorder_popup);
////	}
	
	mySGD->before_cardsetting = kSceneCode_PuzzleMapScene;
	
	if(GraphDog::get()->t_cardNumber == -1)
	{
		CardSettingPopup* t_popup = CardSettingPopup::create();
		t_popup->setHideFinalAction(this, callfunc_selector(MainFlowScene::popupClose));
		addChild(t_popup, kMainFlowZorder_popup);
	}
	else
	{
		mySGD->selected_collectionbook = GraphDog::get()->t_cardNumber;
		
		CollectionBookPopup* t_popup = CollectionBookPopup::create();
		t_popup->is_direct_zoom = true;
		t_popup->setHideFinalAction(this, callfunc_selector(MainFlowScene::popupClose));
		addChild(t_popup, kMainFlowZorder_popup);
		GraphDog::get()->t_cardNumber = -1;
	}
	
	return true;
}

void MainFlowScene::updateCardHistory(CCNode *t_loading)
{
	TRACE();
	Json::Value param;
	param["memberID"] = hspConnector::get()->getSocialID();
	param["cardNo"] = keep_card_number;
	param["addCount"] = mySGD->getClearTakeCardCnt();
	
	hspConnector::get()->command("updateCardHistory", param, [=](Json::Value result_data)
								 {
									 TRACE();
									 if(result_data["result"]["code"].asInt() == GDSUCCESS)
									 {
										 TRACE();
										 mySGD->network_check_cnt = 0;
										 
										 t_loading->removeFromParent();
									 }
									 else
									 {
										 TRACE();
										 mySGD->network_check_cnt++;
										 
										 if(mySGD->network_check_cnt >= mySGD->max_network_check_cnt)
										 {
											 TRACE();
											 mySGD->network_check_cnt = 0;
											 
											 ASPopupView *alert = ASPopupView::getCommonNotiTag(-99999,myLoc->getLocalForKey(kMyLocalKey_reConnect), myLoc->getLocalForKey(kMyLocalKey_reConnectAlert4),[=](){
												 updateCardHistory(t_loading);
											 }, 1);
											 if(alert)
												 ((CCNode*)CCDirector::sharedDirector()->getRunningScene()->getChildren()->objectAtIndex(0))->addChild(alert,999999);
										 }
										 else
										 {
											 addChild(KSTimer::create(0.5f, [=]()
																	  {
																		  updateCardHistory(t_loading);
																	  }));
										 }
									 }
								 });
}

void MainFlowScene::tableOpenning()
{
	is_table_openning = true;
	
	int cell_cnt = NSDS_GI(kSDS_GI_puzzleListCount_i) + 1;
	int action_cell_count = 0;
	
	for(int i=0;i<cell_cnt;i++)
	{
		CCTableViewCell* t_cell = puzzle_table->cellAtIndex(i);
		
		if(t_cell)
		{
			CCNode* t_node = t_cell->getChildByTag(1);
			
//			CCNode* t_rate = t_node->getChildByTag(999);
//			if(t_rate)
//				t_rate->setVisible(false);
			
			float origin_x = t_node->getPositionX();
			
			t_node->setPositionX(origin_x + 70);
			KS::setOpacity(t_node, 0);
			
			float delay_value = action_cell_count*0.1f;
			
			t_node->addChild(KSTimer::create(delay_value, [=]()
											 {
												 t_node->addChild(KSGradualValue<float>::create(0.f, 1.f, 0.2f, [=](float t)
																								{
																									t_node->setPositionX(origin_x + 70-70.f*t);
																									KS::setOpacity(t_node, 255*t);
																								}, [=](float t)
																								{
																									t_node->setPositionX(origin_x);
																									KS::setOpacity(t_node, 255);
																									
//																									CCNode* t_rate = t_node->getChildByTag(999);
//																									if(t_rate)
//																										t_rate->setVisible(true);
																								}));
											 }));
			
			action_cell_count++;
		}
	}
	
	addChild(KSTimer::create(action_cell_count*0.1f+0.2f, [=]()
	{
		is_table_openning = false;
		if(mySGD->keep_time_info.is_loaded)
			tableRefresh();
	}));
}

void MainFlowScene::showClearPopup()
{
	is_menu_enable = false;
	
	ClearPopup* t_popup = ClearPopup::create();
	t_popup->setHideFinalAction(this, callfunc_selector(MainFlowScene::hideClearPopup));
	addChild(t_popup, kPuzzleZorder_popup);
}

void MainFlowScene::hideClearPopup()
{
	is_menu_enable = true;
}

void MainFlowScene::showFailPopup()
{
	is_menu_enable = false;
	
	FailPopup* t_popup = FailPopup::create();
	t_popup->setHideFinalAction(this, callfunc_selector(MainFlowScene::hideFailPopup));
	addChild(t_popup, kPuzzleZorder_popup);
}

void MainFlowScene::hideFailPopup()
{
	is_menu_enable = true;
}

void MainFlowScene::setTable()
{
	CCSize screen_size = CCEGLView::sharedOpenGLView()->getFrameSize();
	float screen_scale_x = screen_size.width/screen_size.height/1.5f;
	if(screen_scale_x < 1.f)
		screen_scale_x = 1.f;
	
	CCSize table_size = CCSizeMake(480*screen_scale_x, 245);
	
//	CCSprite* temp_back = CCSprite::create("whitePaper.png", CCRectMake(0, 0, table_size.width, table_size.height));
//	temp_back->setOpacity(100);
//	temp_back->setAnchorPoint(CCPointZero);
//	temp_back->setPosition(ccp((-480.f*screen_scale_x+480.f)/2.f, 160-table_size.height/2.f+5.f));
//	addChild(temp_back, kMainFlowZorder_table);
	
	puzzle_table = CCTableView::create(this, table_size);
	puzzle_table->setAnchorPoint(CCPointZero);
	puzzle_table->setDirection(kCCScrollViewDirectionHorizontal);
	puzzle_table->setVerticalFillOrder(kCCTableViewFillTopDown);
	puzzle_table->setPosition(ccp((-480.f*screen_scale_x+480.f)/2.f, 160-table_size.height/2.f+7.f));
	puzzle_table->setDelegate(this);
	addChild(puzzle_table, kMainFlowZorder_table);
	puzzle_table->setTouchPriority(kCCMenuHandlerPriority+1);
	
	int puzzle_number;
	
	if(is_unlock_puzzle > 0)
		puzzle_number = is_unlock_puzzle;
	else
		puzzle_number = myDSH->getIntegerForKey(kDSH_Key_selectedPuzzleNumber);
	
	if(puzzle_number == 0 || puzzle_number > 10000)
		myDSH->setIntegerForKey(kDSH_Key_selectedPuzzleNumber, NSDS_GI(kSDS_GI_puzzleList_int1_no_i, 1));
	
	int myPosition = puzzle_table->minContainerOffset().x;
	for(int i=0; i<numberOfCellsInTableView(puzzle_table); i++)
	{
		if(puzzle_number == not_event_puzzle_list[i])//NSDS_GI(kSDS_GI_puzzleList_int1_no_i, i+1))
		{
			myPosition = i+1;
			break;
		}
	}
	float xInitPosition = MAX(puzzle_table->minContainerOffset().x, -cellSizeForTable(puzzle_table).width*myPosition + puzzle_table->getViewSize().width / 2.f);
	xInitPosition = MIN(0, xInitPosition);
//	puzzle_table->setContentOffsetInDuration(ccp(xInitPosition, 0), 0.3f);
	puzzle_table->setContentOffset(ccp(xInitPosition, 0));
}

enum MainFlowTableCellTag{
	kMainFlowTableCellTag_openBase = 0,
	kMainFlowTableCellTag_buyBase = 10000,
	kMainFlowTableCellTag_ticketBase = 20000
};

void MainFlowScene::basicEnter()
{
	topPuzzleMode();
	bottomPuzzleMode();
	tableEnter([=](){puzzleLoadSuccess();});
}

void MainFlowScene::loadTempFunc(CCObject* sender)
{
	
}

void MainFlowScene::tableDownloading(function<void()> end_func)
{
	int puzzle_number = myDSH->getIntegerForKey(kDSH_Key_selectedPuzzleNumber);
	
	int cell_cnt = NSDS_GI(kSDS_GI_puzzleListCount_i)+1;
	bool is_found = false;
	
	for(int i=0;i<cell_cnt;i++)
	{
		int index_puzzle_number = NSDS_GI(kSDS_GI_puzzleList_int1_no_i, i+1);
		CCTableViewCell* t_cell = puzzle_table->cellAtIndex(i);
		
		if(is_found)
		{
			if(t_cell)
			{
				CCNode* t_node = t_cell->getChildByTag(1);
				float origin_x = t_node->getPositionX();
				t_node->addChild(KSGradualValue<float>::create(0.f, 800.f, 1.f, [=](float t)
															   {
																   t_node->setPositionX(origin_x + t);
															   }, [=](float t)
															   {
																   t_node->setPositionX(origin_x + 800.f);
															   }));
			}
		}
		else
		{
			if(index_puzzle_number == puzzle_number)
			{
				if(t_cell)
				{
					is_found = true;
					CCNode* t_node = t_cell->getChildByTag(1);
					
//					CCNode* t_rate = t_node->getChildByTag(999);
//					if(t_rate)
//						t_rate->setVisible(false);
					
					float origin_x = t_node->getPositionX();
					t_node->addChild(KSGradualValue<float>::create(0.f, 800.f, 1.f, [=](float t)
																   {
																	   t_node->setPositionX(origin_x + t);
																   }, [=](float t)
																   {
																	   t_node->setPositionX(origin_x + 800.f);
																   }));
					
					t_node->addChild(KSGradualValue<float>::create(1.f, -0.2f, 0.6f, [=](float t)
																   {
																	   if(t >= 0.f)
																		   KS::setOpacity(t_node, 255*t);
																	   else
																		   KS::setOpacity(t_node, 0);
																   }, [=](float t)
																   {
																	   end_func();
																   }));
				}
			}
			else
			{
				if(t_cell)
				{
					CCNode* t_node = t_cell->getChildByTag(1);
					float origin_x = t_node->getPositionX();
					t_node->addChild(KSGradualValue<float>::create(0.f, -800.f, 1.f, [=](float t)
																   {
																	   t_node->setPositionX(origin_x + t);
																   }, [=](float t)
																   {
																	   t_node->setPositionX(origin_x - 800.f);
																   }));
				}
			}
		}
	}
	
	if(!is_found)
	{
		addChild(KSTimer::create(0.6f, [=](){end_func();}));
	}
}

void MainFlowScene::tableEnter(function<void()> end_func)
{
	int puzzle_number = myDSH->getIntegerForKey(kDSH_Key_selectedPuzzleNumber);
	
//	mySIL->addImageAsync(CCString::createWithFormat("puzzle%d_original_top.png", puzzle_number)->getCString(), this, callfuncO_selector(MainFlowScene::loadTempFunc));
//	mySIL->addImageAsync(CCString::createWithFormat("puzzle%d_original_botton.png", puzzle_number)->getCString(), this, callfuncO_selector(MainFlowScene::loadTempFunc));
//	mySIL->addImageAsync(CCString::createWithFormat("puzzle%d_original_left.png", puzzle_number)->getCString(), this, callfuncO_selector(MainFlowScene::loadTempFunc));
//	mySIL->addImageAsync(CCString::createWithFormat("puzzle%d_original_right.png", puzzle_number)->getCString(), this, callfuncO_selector(MainFlowScene::loadTempFunc));
//	
//	int start_stage = NSDS_GI(puzzle_number, kSDS_PZ_startStage_i);
//	int stage_count = NSDS_GI(puzzle_number, kSDS_PZ_stageCount_i);
//	
//	for(int i=start_stage;i<start_stage+stage_count;i++)
//	{
//		mySIL->addImageAsync(CCString::createWithFormat("puzzle%d_original_piece%d.png", puzzle_number, NSDS_GI(puzzle_number, kSDS_PZ_stage_int1_pieceNo_i, i)-1)->getCString(), this, callfuncO_selector(MainFlowScene::loadTempFunc));
//	}
	
	CCSprite* title_name = CCSprite::create("temp_title_name.png");
	title_name->setPosition(ccp(240,160));
	title_name->setOpacity(0);
	addChild(title_name, kMainFlowZorder_back);
	
	CCFadeTo* t_fade = CCFadeTo::create(0.5f, 255);
	title_name->runAction(t_fade);
	
	int cell_cnt = NSDS_GI(kSDS_GI_puzzleListCount_i)+1;
	bool is_found = false;
	
	for(int i=0;i<cell_cnt;i++)
	{
		int index_puzzle_number = NSDS_GI(kSDS_GI_puzzleList_int1_no_i, i+1);
		CCTableViewCell* t_cell = puzzle_table->cellAtIndex(i);
		
		if(is_found)
		{
			if(t_cell)
			{
				CCNode* t_node = t_cell->getChildByTag(1);
				float origin_x = t_node->getPositionX();
				t_node->addChild(KSGradualValue<float>::create(0.f, 800.f, 1.f, [=](float t)
															   {
																   t_node->setPositionX(origin_x + t);
															   }, [=](float t)
															   {
																   t_node->setPositionX(origin_x + 800.f);
															   }));
			}
		}
		else
		{
			if(index_puzzle_number == puzzle_number)
			{
				if(t_cell)
				{
					is_found = true;
					
					CCNode* t_node = t_cell->getChildByTag(1);
					
//					CCNode* t_rate = t_node->getChildByTag(999);
//					if(t_rate)
//						t_rate->setVisible(false);
					
					t_node->addChild(KSGradualValue<float>::create(1.f, -0.2f, 0.6f, [=](float t)
																   {
																	   if(t >= 0.f)
																		   KS::setOpacity(t_node, 255*t);
																	   else
																		   KS::setOpacity(t_node, 0);
																   }, [=](float t)
																   {
																	   end_func();
																   }));
				}
			}
			else
			{
				if(t_cell)
				{
					CCNode* t_node = t_cell->getChildByTag(1);
					float origin_x = t_node->getPositionX();
					t_node->addChild(KSGradualValue<float>::create(0.f, -800.f, 1.f, [=](float t)
																   {
																	   t_node->setPositionX(origin_x + t);
																   }, [=](float t)
																   {
																	   t_node->setPositionX(origin_x - 800.f);
																   }));
				}
			}
		}
	}
	
	if(!is_found)
	{
		addChild(KSTimer::create(0.6f, [=]()
		{
			end_func();
		}));
	}
}

void MainFlowScene::puzzleLoadSuccess()
{
	mySGD->resetLabels();
	CCDirector::sharedDirector()->replaceScene(PuzzleScene::scene());
}

void MainFlowScene::cellAction(CCObject* sender)
{
	if(!is_menu_enable)
		return;
	
	AudioEngine::sharedInstance()->playEffect("se_button1.mp3", false);
	
	int tag = ((CCNode*)sender)->getTag();
//	TutorialFlowStep recent_step = (TutorialFlowStep)myDSH->getIntegerForKey(kDSH_Key_tutorial_flowStep);
//	
//	if(recent_step == kTutorialFlowStep_puzzleClick)
//	{
//		if(tag < kMainFlowTableCellTag_buyBase && tag - kMainFlowTableCellTag_openBase == 1)
//		{
//			myDSH->setIntegerForKey(kDSH_Key_tutorial_flowStep, kTutorialFlowStep_pieceClick);
//			is_menu_enable = false;
//			
//			int puzzle_number = tag - kMainFlowTableCellTag_openBase;
//			myDSH->setIntegerForKey(kDSH_Key_selectedPuzzleNumber, puzzle_number);
//			
//			StageListDown* t_sld = StageListDown::create(this, callfunc_selector(MainFlowScene::puzzleLoadSuccess), puzzle_number);
//			addChild(t_sld, kMainFlowZorder_popup);
//		}
//	}
//	else if(recent_step == kTutorialFlowStep_cardCollectionClick)
//	{
//		
//	}
//	else
//	{
		is_menu_enable = false;
		
		if(tag < kMainFlowTableCellTag_buyBase)
		{
			CCSprite* black_img = CCSprite::create("mainflow_puzzle_lock_black.png");
			black_img->setPosition(CCPointZero);
			black_img->setOpacity(100);
			CCNode* cell_node = ((CCNode*)sender)->getParent()->getParent();
			cell_node->addChild(black_img);
			
			CCNodeLoaderLibrary* nodeLoader = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
			CCBReader* reader = new CCBReader(nodeLoader);
			CCSprite* loading_progress_img = dynamic_cast<CCSprite*>(reader->readNodeGraphFromFile("loading.ccbi",this));
			loading_progress_img->setPosition(ccp(0,30));
			cell_node->addChild(loading_progress_img);
			reader->release();
			
			
			int puzzle_number = tag - kMainFlowTableCellTag_openBase;
			myDSH->setIntegerForKey(kDSH_Key_selectedPuzzleNumber, puzzle_number);
			
			StageListDown* t_sld = StageListDown::create(this, callfunc_selector(MainFlowScene::basicEnter), puzzle_number, [=](function<void()> t_func)
			{
				mySGD->is_before_stage_img_download = true;
				topOuting();
				bottomPuzzleMode();
				tableDownloading(t_func);
			}, [=](){puzzleLoadSuccess();});
			addChild(t_sld, kMainFlowZorder_popup);
		}
		else if(tag < kMainFlowTableCellTag_ticketBase) // buyBase
		{
			AudioEngine::sharedInstance()->playEffect("se_lock.mp3", false);
			
			int puzzle_number = tag - kMainFlowTableCellTag_buyBase;
			CCLOG("puzzle_number : %d", puzzle_number);
			
			ASPopupView* t_popup = ASPopupView::create(-200);
			
			CCSize screen_size = CCEGLView::sharedOpenGLView()->getFrameSize();
			float screen_scale_x = screen_size.width/screen_size.height/1.5f;
			if(screen_scale_x < 1.f)
				screen_scale_x = 1.f;
			
			t_popup->setDimmedSize(CCSizeMake(screen_scale_x*480.f, myDSH->ui_top/myDSH->screen_convert_rate));
			
			CCNode* t_container = CCNode::create();
			t_popup->setContainerNode(t_container);
			addChild(t_popup);
			
			CCScale9Sprite* case_back = CCScale9Sprite::create("popup2_case_back.png", CCRectMake(0, 0, 150, 150), CCRectMake(13, 45, 135-13, 105-13));
			case_back->setPosition(CCPointZero);
			t_container->addChild(case_back);
			
			case_back->setContentSize(CCSizeMake(230, 250));
			
			CCScale9Sprite* content_back = CCScale9Sprite::create("popup2_content_back.png", CCRectMake(0, 0, 150, 150), CCRectMake(6, 6, 144-6, 144-6));
			content_back->setPosition(ccp(0,2));
			t_container->addChild(content_back);
			
			content_back->setContentSize(CCSizeMake(202, 146));
			
			CCLabelTTF* title_label = CCLabelTTF::create(myLoc->getLocalForKey(kMyLocalKey_openRightNow), mySGD->getFont().c_str(), 20);
			title_label->setPosition(ccp(0, 102));
			t_container->addChild(title_label);
			
			CCLabelTTF* content_label = CCLabelTTF::create(CCString::createWithFormat(myLoc->getLocalForKey(kMyLocalKey_openRubyValue), NSDS_GI(puzzle_number, kSDS_PZ_point_i))->getCString(), mySGD->getFont().c_str(), 18);
			content_label->setPosition(CCPointZero);
			t_container->addChild(content_label);
			
			CCSprite* n_close = CCSprite::create("item_buy_popup_close.png");
			CCSprite* s_close = CCSprite::create("item_buy_popup_close.png");
			s_close->setColor(ccGRAY);
			
			CCMenuItemSpriteLambda* close_item = CCMenuItemSpriteLambda::create(n_close, s_close, [=](CCObject* sender)
																				{
																					is_menu_enable = true;
																					t_popup->removeFromParent();
																				});
			
			CCMenuLambda* close_menu = CCMenuLambda::createWithItem(close_item);
			close_menu->setTouchPriority(t_popup->getTouchPriority()-1);
			close_menu->setPosition(ccp(92,105));
			t_container->addChild(close_menu);
			
			if(mySGD->getGoodsValue(kGoodsType_ruby) >= NSDS_GI(puzzle_number, kSDS_PZ_point_i))
			{
				CCSprite* n_buy = CCSprite::create("popup2_buy.png");
				CCSprite* s_buy = CCSprite::create("popup2_buy.png");
				s_buy->setColor(ccGRAY);
				
				CCMenuItemSpriteLambda* buy_item = CCMenuItemSpriteLambda::create(n_buy, s_buy, [=](CCObject* sender){
					
					AudioEngine::sharedInstance()->playEffect("se_buy.mp3", false);
					
					LoadingLayer* t_loading = LoadingLayer::create(-9999);
					addChild(t_loading, 9999);
					
					mySGD->addChangeGoods(CCString::createWithFormat("p_p_%d", puzzle_number)->getCString());
					
					int open_puzzle_number = NSDS_GI(kSDS_GI_puzzleList_int1_no_i, mySGD->getOpenPuzzleCount()+1);
					PuzzleHistory t_history = mySGD->getPuzzleHistory(open_puzzle_number);
					t_history.is_open = true;
					t_history.open_type = "젬소모";
					
					mySGD->changeGoodsTransaction({mySGD->getUpdatePuzzleHistoryParam(t_history, [=](Json::Value result_data)
																					  {
																						  if(result_data["result"]["code"].asInt() != GDSUCCESS)
																						  {
																							  PuzzleHistory r_history = mySGD->getPuzzleHistory(open_puzzle_number);
																							  r_history.is_open = false;
																							  r_history.open_type = "";
																							  mySGD->setPuzzleHistoryForNotSave(r_history);
																						  }
																					  })}, [=](Json::Value result_data)
												  {
													  t_loading->removeFromParent();
													  if(result_data["result"]["code"].asInt() != GDSUCCESS)
														{
															mySGD->clearChangeGoods();
															addChild(ASPopupView::getCommonNoti(-9999, myLoc->getLocalForKey(kMyLocalKey_noti), myLoc->getLocalForKey(kMyLocalKey_failPurchase)), 9999);
														}
													  else
														{
															int found_idx = -1;
															for(int i=0;i<numberOfCellsInTableView(puzzle_table) && found_idx == -1;i++)
															{
																CCTableViewCell* t_cell = puzzle_table->cellAtIndex(i);
																if(t_cell)
																{
																	int cell_card_number = t_cell->getTag();
																	if(cell_card_number == puzzle_number)
																		found_idx = i;
																}
															}
															if(found_idx != -1)
																puzzle_table->updateCellAtIndex(found_idx);
															
															is_menu_enable = true;
															t_popup->removeFromParent();
														}
												  });
				});
				
				CCMenuLambda* buy_menu = CCMenuLambda::createWithItem(buy_item);
				buy_menu->setTouchPriority(t_popup->getTouchPriority()-1);
				buy_menu->setPosition(ccp(0,-95));
				t_container->addChild(buy_menu);
			}
			else
			{
				CCSprite* buy_img = CCSprite::create("popup2_buy.png");
				buy_img->setColor(ccc3(100, 100, 100));
				buy_img->setPosition(ccp(0,-95));
				t_container->addChild(buy_img);
			}
		}
		else // ticketBase
		{
			AudioEngine::sharedInstance()->playEffect("se_lock.mp3", false);
			
			int puzzle_number = tag - kMainFlowTableCellTag_ticketBase;
			
			ASPopupView* t_popup = ASPopupView::create(-200);
			
			CCSize screen_size = CCEGLView::sharedOpenGLView()->getFrameSize();
			float screen_scale_x = screen_size.width/screen_size.height/1.5f;
			if(screen_scale_x < 1.f)
				screen_scale_x = 1.f;
			
			t_popup->setDimmedSize(CCSizeMake(screen_scale_x*480.f, myDSH->ui_top/myDSH->screen_convert_rate));
			
			TicketRequestContent* t_container = TicketRequestContent::create(t_popup->getTouchPriority(), puzzle_number);
			t_popup->setContainerNode(t_container);
			addChild(t_popup);
			
			t_container->setRemoveAction([=](){
				is_menu_enable = true;
				t_popup->removeFromParent();
			});
		}
//	}
}

void MainFlowScene::puzzleHeartRefresh(Json::Value result_data)
{
	if(result_data["result"]["code"] == GDSUCCESS)
	{
		heart_refresh_loading->removeFromParent();
	}
	else
	{
		addChild(KSTimer::create(0.5f, [=](){mySGD->changeGoods(json_selector(this, MainFlowScene::puzzleHeartRefresh));}));
	}
}

CCTableViewCell* MainFlowScene::tableCellAtIndex(CCTableView *table, unsigned int idx)
{
	CCTableViewCell* cell = table->dequeueCell();
	
	cell = new CCTableViewCell();
	cell->init();
	cell->autorelease();
	
	CCNode* cell_node = CCNode::create();
	cell_node->setPosition(ccp(cellSizeForTable(table).width/2.f, cellSizeForTable(table).height/2.f));
	cell->addChild(cell_node, 1, 1);
	
	
	if(idx==numberOfCellsInTableView(table)-1){
		CCSprite* n_locked_back = CCSprite::create("mainflow_puzzle_lock.png"); //mySIL->getLoadedImg("mainflow_puzzle_lock.png");
		cell_node->addChild(n_locked_back);
		
//		CCLabelTTF* rate_label = CCLabelTTF::create("??/??", mySGD->getFont().c_str(), 10);
//		rate_label->setPosition(ccp(-15, -71.5f));
//		cell_node->addChild(rate_label);
		
		KSLabelTTF* locked_label = KSLabelTTF::create(myLoc->getLocalForKey(kMyLocalKey_waitForUpdate), mySGD->getFont().c_str(), 10);
		locked_label->setColor(ccc3(50, 145, 145));
		locked_label->enableOuterStroke(ccBLACK, 1.f);
		locked_label->setPosition(ccp(67.5f,95.f));
		n_locked_back->addChild(locked_label);
		
		return cell;
	}
	
	
	CCSize screen_size = CCEGLView::sharedOpenGLView()->getFrameSize();
	float screen_scale_x = screen_size.width/screen_size.height/1.5f;
	if(screen_scale_x < 1.f)
		screen_scale_x = 1.f;
	
//	CCSize table_size = CCSizeMake(480*screen_scale_x, 245);
	
	int puzzle_number = not_event_puzzle_list[idx];// NSDS_GI(kSDS_GI_puzzleList_int1_no_i, idx+1);
	cell->setTag(puzzle_number);
	
//	if(puzzle_number == is_unlock_puzzle)
//	{
//		if(NSDS_GI(puzzle_number, kSDS_PZ_point_i) <= 0 || NSDS_GI(puzzle_number, kSDS_PZ_ticket_i) <= 0)
//		{
//			int open_puzzle_number = NSDS_GI(kSDS_GI_puzzleList_int1_no_i, mySGD->getOpenPuzzleCount()+1);
//			PuzzleHistory t_history = mySGD->getPuzzleHistory(open_puzzle_number);
//			t_history.is_open = true;
//			t_history.open_type = "무료(이전퍼즐완료)";
//			mySGD->setPuzzleHistory(t_history, nullptr);
//			
//			is_open = true;
//		}
//	}
	
	PuzzleOpenInfo t_info;
	bool t_is_found = false;
	for(int i=0;!t_is_found && i<is_puzzle_enter_list.size();i++)
	{
		if(is_puzzle_enter_list[i].puzzle_number == not_event_puzzle_list[idx])
		{
			t_info = is_puzzle_enter_list[i];
			t_is_found = true;
		}
	}
	
	if(!t_is_found)
	{
		CCLOG("not found puzzle open info!!!");
		return cell;
	}
	
	if(t_info.is_open)
//	if(puzzle_number == 1 || mySGD->getPuzzleHistory(puzzle_number).is_open || (mySGD->getPuzzleHistory(puzzle_number-1).is_clear && NSDS_GI(puzzle_number, kSDS_PZ_point_i) == 0))
//	if(puzzle_number == 1 || 9999+1 >= puzzle_number)
	{
		
		addChild(KSTimer::create(rand()%10*0.2f, [=](){
			CCSprite* mainTwinkle = KS::loadCCBI<CCSprite*>(this, "main_twinkle.ccbi").first;
			mainTwinkle->setAnchorPoint(ccp(0,0));
			mainTwinkle->setPosition(ccp(mainTwinkle->getContentSize().width/2,mainTwinkle->getContentSize().height/2));
			cell_node->addChild(mainTwinkle,100);
		}));
		
		CCSprite* n_open_back = mySIL->getLoadedImg(CCString::createWithFormat("puzzleList%d_thumbnail.png", puzzle_number)->getCString());//CCSprite::create("mainflow_puzzle_open_back.png");
		CCSprite* s_open_back = mySIL->getLoadedImg(CCString::createWithFormat("puzzleList%d_thumbnail.png", puzzle_number)->getCString());//CCSprite::create("mainflow_puzzle_open_back.png");
		s_open_back->setColor(ccGRAY);
		
		
		CCMenuItem* open_item = CCMenuItemSprite::create(n_open_back, s_open_back, this, menu_selector(MainFlowScene::cellAction));
		open_item->setTag(kMainFlowTableCellTag_openBase + puzzle_number);
		
		ScrollMenu* open_menu = ScrollMenu::create(open_item, NULL);
		open_menu->setPosition(CCPointZero);
		cell_node->addChild(open_menu);
		
		int stage_count = NSDS_GI(puzzle_number, kSDS_PZ_stageCount_i);
		int total_card_cnt = stage_count*10;
		
		CCLabelTTF* rate_label = CCLabelTTF::create(CCString::createWithFormat("%d/%d", have_card_count_for_puzzle_index[idx], total_card_cnt)->getCString(), mySGD->getFont().c_str(), 10);
		rate_label->setPosition(ccp(-15, -71.5f));
		cell_node->addChild(rate_label);
		
		int t_start_stage = NSDS_GI(not_event_puzzle_list[idx], kSDS_PZ_startStage_i);
		int t_stage_count = NSDS_GI(not_event_puzzle_list[idx], kSDS_PZ_stageCount_i);
		
		CCPoint t_distance_position = ccp(8.25f, 0);
		CCPoint t_base_position = ccp(21, -72.f) - t_distance_position*2;
		
		for(int i=t_start_stage;i<t_start_stage+t_stage_count;i++)
		{
			if(mySGD->isClearPiece(i))
			{
				if(NSDS_GI(not_event_puzzle_list[idx], kSDS_PZ_stage_int1_condition_gold_i, i) > 0)
				{
					// special stage
					CCSprite* stage_clear_mark = CCSprite::create("mainflow_specialstage.png");
					stage_clear_mark->setPosition(t_base_position + t_distance_position*(i-t_start_stage));
					cell_node->addChild(stage_clear_mark);
				}
				else
				{
					// normal
					CCSprite* stage_clear_mark = CCSprite::create("mainflow_normalstage.png");
					stage_clear_mark->setPosition(t_base_position + t_distance_position*(i-t_start_stage));
					cell_node->addChild(stage_clear_mark);
				}
			}
		}
		
//		CCProgressTimer* rate_timer = CCProgressTimer::create(CCSprite::create("mainflow_puzzle_bar.png"));
//		rate_timer->setType(kCCProgressTimerTypeBar);
//		rate_timer->setMidpoint(ccp(0,0));
//		rate_timer->setBarChangeRate(ccp(1,0));
//		rate_timer->setPercentage(100.f*have_card_count_for_puzzle_index[idx]/total_card_cnt);
//		rate_timer->setPosition(ccp(22, -80));
//		cell_node->addChild(rate_timer, 0, 999);
		
		KSLabelTTF* title_label = KSLabelTTF::create(NSDS_GS(puzzle_number, kSDS_PZ_title_s).c_str(), mySGD->getFont().c_str(), 11);
		title_label->enableOuterStroke(ccBLACK, 1.f, int(255*0.6f), true);
		title_label->setPosition(ccp(0,-56.f));
		cell_node->addChild(title_label, 1);

		
//		PuzzleListShadow* shadow_node = PuzzleListShadow::create(this, cell, ccpAdd(ccp((-480.f*screen_scale_x+480.f)/2.f, 160-table_size.height/2.f), ccp(table_size.width/2.f, table_size.height/2.f)), ccp(cellSizeForTable(table).width/2.f, cellSizeForTable(table).height/2.f), ccp(1.f,0), ccp(0.2f,0));
//		cell->addChild(shadow_node, -1);
//		shadow_node->startAction();
//		
//		CCSprite* shadow_img = CCSprite::create("mainflow_puzzle_shadow.png");
//		shadow_node->addChild(shadow_img, -1);
	}
	else
	{
		CCSprite* close_back = mySIL->getLoadedImg(CCString::createWithFormat("puzzleList%d_thumbnail.png", puzzle_number)->getCString());
		close_back->setPosition(CCPointZero);
		cell_node->addChild(close_back);
		
		CCLabelTTF* rate_label = CCLabelTTF::create("0/50", mySGD->getFont().c_str(), 10);
		rate_label->setPosition(ccp(-15, -71.5f));
		cell_node->addChild(rate_label);
		
		if(t_info.is_base_condition_success)//mySGD->getPuzzleHistory(puzzle_number-1).is_clear) // 기본조건 충족 했는가
		{
			// 젬 구매 혹은 시간이 되야 열림
			
//			CCSprite* n_buy = CCSprite::create("mainflow_puzzle_open_buy.png");
//			CCSprite* s_buy = CCSprite::create("mainflow_puzzle_open_buy.png");
//			s_buy->setColor(ccGRAY);
//			
//			CCMenuItem* buy_item = CCMenuItemSprite::create(n_buy, s_buy, this, menu_selector(MainFlowScene::cellAction));
//			buy_item->setTag(kMainFlowTableCellTag_buyBase + puzzle_number);
//			
//			ScrollMenu* buy_menu = ScrollMenu::create(buy_item, NULL);
//			buy_menu->setPosition(ccp(-24, -16));
//			cell_node->addChild(buy_menu);
			
			int lock_img_number = t_info.before_locked_puzzle_count;
			if(lock_img_number > 1)
				lock_img_number = 1;
			lock_img_number++;
			
			CCSprite* not_clear_img = CCSprite::create(CCString::createWithFormat("mainflow_puzzle_lock_base%d.png", lock_img_number)->getCString());
			not_clear_img->setPosition(close_back->getPosition());
			cell_node->addChild(not_clear_img);
			
			if(t_info.before_locked_puzzle_count == 0)
			{
				KSLabelTTF* condition_title = KSLabelTTF::create(myLoc->getLocalForKey(kMyLocalKey_frameOpenConditionTitle), mySGD->getFont().c_str(), 11.5f);
				condition_title->setColor(ccc3(255, 177, 38));
				condition_title->disableOuterStroke();
				condition_title->setPosition(ccp(67.5f, 121));
				not_clear_img->addChild(condition_title);
				
				if(t_info.is_have_week_condition)
				{
					string weekday_string;
					if(t_info.keep_weekday == -1)
						weekday_string = "매일";
					else if(t_info.keep_weekday == 0)
						weekday_string = "일요일";
					else if(t_info.keep_weekday == 1)
						weekday_string = "월요일";
					else if(t_info.keep_weekday == 2)
						weekday_string = "화요일";
					else if(t_info.keep_weekday == 3)
						weekday_string = "수요일";
					else if(t_info.keep_weekday == 4)
						weekday_string = "목요일";
					else if(t_info.keep_weekday == 5)
						weekday_string = "금요일";
					else if(t_info.keep_weekday == 6)
						weekday_string = "토요일";
					
					KSLabelTTF* condition_content = KSLabelTTF::create(CCString::createWithFormat(myLoc->getLocalForKey(kMyLocalKey_frameOpenConditionContentTimeWeek), weekday_string.c_str(), t_info.keep_week_start, t_info.keep_week_end)->getCString(), mySGD->getFont().c_str(), 10);
					condition_content->disableOuterStroke();
					condition_content->setPosition(ccp(67.5f, 102.5f));
					not_clear_img->addChild(condition_content);
				}
				else if(t_info.is_have_date_condition)
				{
					KSLabelTTF* condition_content = KSLabelTTF::create(CCString::createWithFormat(myLoc->getLocalForKey(kMyLocalKey_frameOpenConditionContentTimeDate), t_info.keep_date_start.substr(4,2).c_str(), t_info.keep_date_start.substr(6,2).c_str(), t_info.keep_date_start.substr(8,2).c_str(), t_info.keep_date_start.substr(10,2).c_str())->getCString(), mySGD->getFont().c_str(), 10);
					condition_content->disableOuterStroke();
					condition_content->setPosition(ccp(67.5f, 102.5f));
					not_clear_img->addChild(condition_content);
				}
				else
				{
					KSLabelTTF* condition_content = KSLabelTTF::create(myLoc->getLocalForKey(kMyLocalKey_frameOpenConditionContentRuby), mySGD->getFont().c_str(), 10);
					condition_content->disableOuterStroke();
					condition_content->setPosition(ccp(67.5f, 102.5f));
					not_clear_img->addChild(condition_content);
				}
				
				if(t_info.is_have_ruby_condition)
				{
					CCLabelTTF* c_label = CCLabelTTF::create();
					
					CCSprite* price_type = CCSprite::create("price_ruby_img.png");
					price_type->setScale(0.7f);
					c_label->addChild(price_type);
					
					KSLabelTTF* price_value_label = KSLabelTTF::create(CCString::createWithFormat("%d  ", t_info.need_ruby_value)->getCString(), mySGD->getFont().c_str(), 10);
					price_value_label->disableOuterStroke();
					c_label->addChild(price_value_label);
					
					KSLabelTTF* detail_label = KSLabelTTF::create(myLoc->getLocalForKey(kMyLocalKey_directEnter), mySGD->getFont().c_str(), 10);
					detail_label->disableOuterStroke();
					c_label->addChild(detail_label);
					
					float t_width = price_type->getContentSize().width*price_type->getScale();
					float v_width = price_value_label->getContentSize().width;
					float d_width = detail_label->getContentSize().width;
					
					price_type->setPositionX(-(v_width+d_width - (t_width+v_width+d_width)/2.f + t_width/2.f));
					price_value_label->setPositionX(-(d_width-(t_width+v_width+d_width)/2.f + v_width/2.f));
					detail_label->setPositionX(price_value_label->getPositionX() + v_width/2.f + d_width/2.f);
					
					CCScale9Sprite* detail_back = CCScale9Sprite::create("mainflow_detail.png", CCRectMake(0, 0, 90, 43), CCRectMake(44, 21, 2, 1));

					CCControlButton* detail_button = CCControlButton::create(c_label, detail_back);
					detail_button->addTargetWithActionForControlEvents(this, cccontrol_selector(MainFlowScene::detailCondition), CCControlEventTouchUpInside);
					detail_button->setTag(10000000 + idx*10000 + t_info.need_ruby_value);
					detail_button->setPreferredSize(CCSizeMake(90, 43));
					detail_button->setPosition(ccp(67.5f,65.5f));
					not_clear_img->addChild(detail_button);
				}
				else
				{
					CCLabelTTF* c_label = CCLabelTTF::create();
					KSLabelTTF* detail_label = KSLabelTTF::create(myLoc->getLocalForKey(kMyLocalKey_detailView), mySGD->getFont().c_str(), 11.5f);
					detail_label->enableOuterStroke(ccBLACK, 1, int(255*0.5), true);
					detail_label->setPosition(ccp(0,0));
					c_label->addChild(detail_label);
				
					CCScale9Sprite* detail_back = CCScale9Sprite::create("mainflow_detail.png", CCRectMake(0, 0, 90, 43), CCRectMake(44, 21, 2, 1));
					
					CCControlButton* detail_button = CCControlButton::create(c_label, detail_back);
					detail_button->addTargetWithActionForControlEvents(this, cccontrol_selector(MainFlowScene::detailCondition), CCControlEventTouchUpInside);
					detail_button->setTag(0);
					detail_button->setPreferredSize(CCSizeMake(90, 43));
					detail_button->setPosition(ccp(67.5f,65.5f));
					not_clear_img->addChild(detail_button);
				}
			}
			else
			{
//				KSLabelTTF* not_clear_label = KSLabelTTF::create(myLoc->getLocalForKey(kMyLocalKey_beforeNotClearPuzzle), mySGD->getFont().c_str(), 12);
//				not_clear_label->enableOuterStroke(ccBLACK, 1.f);
//				not_clear_label->setPosition(ccp(67.5f,138.5f));
//				not_clear_img->addChild(not_clear_label);
			}
		}
		else
		{
			int lock_img_number = t_info.before_locked_puzzle_count;
			if(lock_img_number > 1)
				lock_img_number = 1;
			lock_img_number++;
			
			CCSprite* not_clear_img = CCSprite::create(CCString::createWithFormat("mainflow_puzzle_lock_base%d.png", lock_img_number)->getCString());
			not_clear_img->setPosition(close_back->getPosition());
			cell_node->addChild(not_clear_img);
			
			if(t_info.before_locked_puzzle_count == 0)
			{
				KSLabelTTF* condition_title = KSLabelTTF::create(myLoc->getLocalForKey(kMyLocalKey_frameOpenConditionTitle), mySGD->getFont().c_str(), 11.5f);
				condition_title->setColor(ccc3(255, 177, 38));
				condition_title->disableOuterStroke();
				condition_title->setPosition(ccp(67.5f, 121));
				not_clear_img->addChild(condition_title);
				
				KSLabelTTF* condition_content = KSLabelTTF::create(CCString::createWithFormat(myLoc->getLocalForKey(kMyLocalKey_frameOpenConditionContent), t_info.need_star_count)->getCString(), mySGD->getFont().c_str(), 10);
				condition_content->disableOuterStroke();
				condition_content->setPosition(ccp(67.5f, 102.5f));
				not_clear_img->addChild(condition_content);
				
				CCLabelTTF* c_label = CCLabelTTF::create();
				KSLabelTTF* detail_label = KSLabelTTF::create(myLoc->getLocalForKey(kMyLocalKey_detailView), mySGD->getFont().c_str(), 11.5f);
				detail_label->enableOuterStroke(ccBLACK, 1, int(255*0.5), true);
				detail_label->setPosition(ccp(0,0));
				c_label->addChild(detail_label);
				
				CCScale9Sprite* detail_back = CCScale9Sprite::create("mainflow_detail.png", CCRectMake(0, 0, 90, 43), CCRectMake(44, 21, 2, 1));
				
				CCControlButton* detail_button = CCControlButton::create(c_label, detail_back);
				detail_button->addTargetWithActionForControlEvents(this, cccontrol_selector(MainFlowScene::detailCondition), CCControlEventTouchUpInside);
				detail_button->setTag(0);
				detail_button->setPreferredSize(CCSizeMake(90, 43));
				detail_button->setPosition(ccp(67.5f,65.5f));
				not_clear_img->addChild(detail_button);
			}
			else
			{
//				KSLabelTTF* not_clear_label = KSLabelTTF::create(myLoc->getLocalForKey(kMyLocalKey_beforeNotClearPuzzle), mySGD->getFont().c_str(), 10);
//				not_clear_label->enableOuterStroke(ccBLACK, 1.f);
//				not_clear_label->setPosition(ccp(67.5f,138.5f));
//				not_clear_img->addChild(not_clear_label);
			}
		}
		
//		KSLabelTTF* title_label = KSLabelTTF::create(NSDS_GS(puzzle_number, kSDS_PZ_title_s).c_str(), mySGD->getFont().c_str(), 11);
//		title_label->setPosition(ccp(0,-56.f));
//		cell_node->addChild(title_label, 1);
		
//		PuzzleListShadow* shadow_node = PuzzleListShadow::create(this, cell, ccpAdd(ccp((-480.f*screen_scale_x+480.f)/2.f, 160-table_size.height/2.f), ccp(table_size.width/2.f, table_size.height/2.f)), ccp(cellSizeForTable(table).width/2.f, cellSizeForTable(table).height/2.f), ccp(1.f,0), ccp(0.2f,0));
//		cell->addChild(shadow_node, -1);
//		shadow_node->startAction();
//		
//		CCSprite* shadow_img = CCSprite::create("mainflow_puzzle_shadow.png");
//		shadow_node->addChild(shadow_img, -1);
	}
	
	if(puzzle_number == is_unlock_puzzle)
	{
		if(t_info.is_open)
		{
			start_unlock_animation = [=](function<void()> t_end_func)
			{
				CCSprite* puzzle_unlock_beam = CCSprite::create("puzzle_unlock_beam.png");
				puzzle_unlock_beam->setPosition(CCPointZero);
				cell_node->addChild(puzzle_unlock_beam, -1);
				puzzle_unlock_beam->setOpacity(0);
				
				CCScaleTo* beam_scale1 = CCScaleTo::create(0.2f, 1.4f);
				CCDelayTime* beam_scale_delay = CCDelayTime::create(0.5f);
				CCScaleTo* beam_scale2 = CCScaleTo::create(0.2f, 1.f);
				CCSequence* beam_scale_seq = CCSequence::create(beam_scale1, beam_scale_delay, beam_scale2, NULL);
				
				CCRotateBy* beam_rotate = CCRotateBy::create(0.9f, 80);
				
				CCFadeTo* beam_fade1 = CCFadeTo::create(0.2f, 200);
				CCDelayTime* beam_fade_delay = CCDelayTime::create(0.5f);
				CCFadeTo* beam_fade2 = CCFadeTo::create(0.2f, 0);
				CCSequence* beam_fade_seq = CCSequence::create(beam_fade1, beam_fade_delay, beam_fade2, NULL);
				
				CCDelayTime* beam_delay = CCDelayTime::create(0.5f);
				CCSpawn* beam_spawn = CCSpawn::create(beam_scale_seq, beam_rotate, beam_fade_seq, NULL);
				CCCallFunc* beam_remove = CCCallFunc::create(puzzle_unlock_beam, callfunc_selector(CCSprite::removeFromParent));
				CCSequence* beam_seq = CCSequence::create(beam_delay, beam_spawn, beam_remove, NULL);
				
				puzzle_unlock_beam->runAction(beam_seq);
				
				CCSprite* not_clear_img = CCSprite::create("mainflow_puzzle_lock_base1.png");
				not_clear_img->setPosition(CCPointZero);
				cell_node->addChild(not_clear_img);
				
				KSLabelTTF* not_clear_label = KSLabelTTF::create(myLoc->getLocalForKey(kMyLocalKey_beforeNotClearPuzzle), mySGD->getFont().c_str(), 12);
				not_clear_label->enableOuterStroke(ccBLACK, 1.f);
				not_clear_label->setPosition(ccp(67.5f,138.5f));
				not_clear_img->addChild(not_clear_label);
				
				CCDelayTime* t_delay1 = CCDelayTime::create(0.5f);
				CCFadeTo* t_fade1 = CCFadeTo::create(0.2f, 0);
				CCCallFunc* t_remove_self1 = CCCallFunc::create(not_clear_img, callfunc_selector(CCNode::removeFromParent));
				CCSequence* t_seq1 = CCSequence::create(t_delay1, t_fade1, t_remove_self1, NULL);
				not_clear_img->runAction(t_seq1);
				
				int refresh_cnt = 5 - myDSH->getIntegerForKey(kDSH_Key_heartCnt);
				if(refresh_cnt > 0)
				{
					LoadingLayer* t_loading = LoadingLayer::create(999);
					addChild(t_loading, 999);
					
					heart_refresh_loading = t_loading;
					
					mySGD->addChangeGoods("getHeart", kGoodsType_heart, refresh_cnt, "puzzleHeart", ccsf("%d", puzzle_number), "퍼즐클리어하트");
					mySGD->changeGoods(json_selector(this, MainFlowScene::puzzleHeartRefresh));
				}
				
				cell_node->addChild(KSTimer::create(0.7f, [=]()
													{
														AudioEngine::sharedInstance()->playEffect("se_puzzleopen_2.mp3", false);
														cell_node->addChild(KSGradualValue<float>::create(0.f, 3.f, 0.5f, [=](float t)
																										  {
																											  if(t < 1.f)
																											  {
																												  cell_node->setScale(1.f+0.1f*t);
																											  }
																											  else if(t < 2.f)
																											  {
																												  cell_node->setScale(1.1f);
																											  }
																											  else
																											  {
																												  cell_node->setScale(1.1f-0.1f*(t-2.f));
																											  }
																										  }, [=](float t)
																										  {
																											  cell_node->setScale(1.f);
																											  
//																											  if(myDSH->getIntegerForKey(kDSH_Key_heartCnt) < mySGD->getHeartMax())
//																											  {
//																												  myDSH->setIntegerForKey(kDSH_Key_heartCnt, mySGD->getHeartMax());
//																												  
//																												  CCNode* target_parent = heart_time->getParent();
//																												  CCPoint heart_time_position = heart_time->getPosition();
//																												  int heart_time_tag = heart_time->getTag();
//																												  
//																												  heart_time->removeFromParent();
//																												  heart_time = HeartTime::create();
//																												  heart_time->setPosition(heart_time_position);
//																												  target_parent->addChild(heart_time, 0, heart_time_tag);
//																											  }
																											  
																											  if(myDSH->getIntegerForKey(kDSH_Key_showedScenario)%1000 == 0 && myDSH->getIntegerForKey(kDSH_Key_showedScenario)/1000+1 == is_unlock_puzzle)
																												{
																													CCNode* scenario_node = CCNode::create();
																													addChild(scenario_node, 9999);
																													
																													CCSize screen_size = CCEGLView::sharedOpenGLView()->getFrameSize();
																													float screen_scale_x = screen_size.width/screen_size.height/1.5f;
																													if(screen_scale_x < 1.f)
																														screen_scale_x = 1.f;
																													
																													float screen_scale_y = myDSH->ui_top/320.f/myDSH->screen_convert_rate;
																													
																													
																													CCNode* t_stencil_node = CCNode::create();
																													
																													
																													CCClippingNode* t_clipping = CCClippingNode::create(t_stencil_node);
																													t_clipping->setAlphaThreshold(0.1f);
																													
																													float change_scale = 1.f;
																													CCPoint change_origin = ccp(0,0);
																													if(screen_scale_x > 1.f)
																													{
																														change_origin.x = -(screen_scale_x-1.f)*480.f/2.f;
																														change_scale = screen_scale_x;
																													}
																													if(screen_scale_y > 1.f)
																														change_origin.y = -(screen_scale_y-1.f)*320.f/2.f;
																													CCSize win_size = CCDirector::sharedDirector()->getWinSize();
																													t_clipping->setRectYH(CCRectMake(change_origin.x, change_origin.y, win_size.width*change_scale, win_size.height*change_scale));
																													
																													
																													CCSprite* t_gray = CCSprite::create("back_gray.png");
																													t_gray->setScaleX(screen_scale_x);
																													t_gray->setScaleY(myDSH->ui_top/myDSH->screen_convert_rate/320.f);
																													t_gray->setOpacity(0);
																													t_gray->setPosition(ccp(240,160));
																													t_clipping->addChild(t_gray);
																													
																													t_clipping->setInverted(true);
																													scenario_node->addChild(t_clipping, 0);
																													
																													TypingBox* typing_box = TypingBox::create(-9999, "kt_talkbox_purple_right.png", CCRectMake(0, 0, 85, 115), CCRectMake(40, 76, 23, 14), CCRectMake(40, 26, 23, 64), CCSizeMake(210, 60), ccp(241, 78));
																													scenario_node->addChild(typing_box, 2);
																													
																													TypingBox* typing_box2 = TypingBox::create(-9999, "kt_talkbox_blue.png", CCRectMake(0, 0, 85, 115), CCRectMake(22, 76, 23, 14), CCRectMake(22, 26, 23, 64), CCSizeMake(210, 60), ccp(239, 96));
																													scenario_node->addChild(typing_box2, 2);
																													
																													CCSprite* n_skip = CCSprite::create("kt_skip.png");
																													CCSprite* s_skip = CCSprite::create("kt_skip.png");
																													s_skip->setColor(ccGRAY);
																													
																													CCMenuLambda* skip_menu = CCMenuLambda::create();
																													skip_menu->setPosition(ccp(240-240*screen_scale_x + 35, 160+160*screen_scale_y - 25 + 150));
																													scenario_node->addChild(skip_menu, 3);
																													skip_menu->setTouchPriority(-19999);
																													skip_menu->setEnabled(false);
																													
																													CCMenuItemLambda* skip_item = CCMenuItemSpriteLambda::create(n_skip, s_skip, [=](CCObject* sender)
																																												 {
																																													 skip_menu->setEnabled(false);
																																													 
																																													 mySGD->setIsUnlockPuzzle(0);
																																													 is_unlock_puzzle = 0;
																																													 
																																													 endUnlockAnimation();
																																													 
																																													 t_end_func();
																																													 
																																													 addChild(KSTimer::create(0.1f, [=]()
																																																			  {
																																																				  scenario_node->removeFromParent();
																																																			  }));
																																												 });
																													skip_menu->addChild(skip_item);
																													
																													if(is_unlock_puzzle == 2)
																													{
																														myDSH->setIntegerForKey(kDSH_Key_showedScenario, 2000);
																														
																														CCSprite* asuka = CCSprite::create("kt_cha_asuka_1.png");
																														asuka->setAnchorPoint(ccp(0,0));
																														asuka->setPosition(ccp(240-240*screen_scale_x-asuka->getContentSize().width, 160-160*screen_scale_y));
																														scenario_node->addChild(asuka, 1);
																														
																														CCSprite* hibari = CCSprite::create("kt_cha_hibari_1.png");
																														hibari->setAnchorPoint(ccp(1,0));
																														hibari->setPosition(ccp(240+240*screen_scale_x+hibari->getContentSize().width, 160-160*screen_scale_y));
																														hibari->setVisible(false);
																														scenario_node->addChild(hibari, 1);
																														
																														CCSprite* yagyu = CCSprite::create("kt_cha_yagyu_1.png");
																														yagyu->setAnchorPoint(ccp(0,0));
																														yagyu->setPosition(ccp(240-240*screen_scale_x-yagyu->getContentSize().width, 160-160*screen_scale_y));
																														yagyu->setVisible(false);
																														scenario_node->addChild(yagyu, 1);
																														
																														typing_box->setHide();
																														
																														typing_box2->setTouchOffScrollAndButton();
																														typing_box2->setVisible(false);
																														typing_box2->setTouchSuction(false);
																														
																														typing_box->showAnimation(0.3f);
																														
																														function<void()> end_func9 = [=]()
																														{
																															skip_menu->setEnabled(false);
																															
																															mySGD->setIsUnlockPuzzle(0);
																															is_unlock_puzzle = 0;
																															
																															endUnlockAnimation();
																															
																															t_end_func();
																															
																															addChild(KSTimer::create(0.1f, [=]()
																																					 {
																																						 scenario_node->removeFromParent();
																																					 }));
																														};
																														
																														function<void()> end_func8 = [=]()
																														{
																															TypingBox::changeTypingBox(typing_box2, typing_box, hibari, yagyu);
																															typing_box->startTyping(myLoc->getLocalForKey(kMyLocalKey_scenarioMent41), end_func9);
																														};
																														
																														function<void()> end_func7 = [=]()
																														{
																															TypingBox::changeTypingBox(typing_box, typing_box2, yagyu, hibari);
																															typing_box2->startTyping(myLoc->getLocalForKey(kMyLocalKey_scenarioMent40), end_func8);
																														};
																														
																														function<void()> end_func6 = [=]()
																														{
																															hibari->setVisible(false);
																															yagyu->setVisible(true);
																															
																															scenario_node->addChild(KSGradualValue<float>::create(0.f, 1.f, 0.3, [=](float t)
																																												  {
																																													  yagyu->setPositionX(240-240*screen_scale_x-yagyu->getContentSize().width + yagyu->getContentSize().width*2.f/3.f*t);
																																												  }, [=](float t)
																																												  {
																																													  yagyu->setPositionX(240-240*screen_scale_x-yagyu->getContentSize().width + yagyu->getContentSize().width*2.f/3.f*t);
																																													  
																																													  typing_box->setVisible(true);
																																													  typing_box->setTouchSuction(true);
																																													  
																																													  typing_box2->setTouchSuction(false);
																																													  
																																													  typing_box->startTyping(myLoc->getLocalForKey(kMyLocalKey_scenarioMent39), end_func7);
																																												  }));
																															typing_box2->setTouchOffScrollAndButton();
																															typing_box2->setVisible(false);
																														};
																														
																														function<void()> end_func5 = [=]()
																														{
																															TypingBox::changeTypingBox(typing_box, typing_box2, asuka, hibari);
																															typing_box2->startTyping(myLoc->getLocalForKey(kMyLocalKey_scenarioMent38), end_func6);
																														};
																														
																														function<void()> end_func4 = [=]()
																														{
																															TypingBox::changeTypingBox(typing_box2, typing_box, hibari, asuka);
																															typing_box->startTyping(myLoc->getLocalForKey(kMyLocalKey_scenarioMent37), end_func5);
																														};
																														
																														function<void()> end_func3 = [=]()
																														{
																															TypingBox::changeTypingBox(typing_box, typing_box2, asuka, hibari);
																															typing_box2->startTyping(myLoc->getLocalForKey(kMyLocalKey_scenarioMent36), end_func4);
																														};
																														
																														function<void()> end_func2 = [=]()
																														{
																															TypingBox::changeTypingBox(typing_box2, typing_box, hibari, asuka);
																															typing_box->startTyping(myLoc->getLocalForKey(kMyLocalKey_scenarioMent35), end_func3);
																														};
																														
																														function<void()> end_func1 = [=]()
																														{
																															asuka->setVisible(false);
																															hibari->setVisible(true);
																															
																															scenario_node->addChild(KSGradualValue<float>::create(0.f, 1.f, 0.3, [=](float t)
																																												  {
																																													  hibari->setPositionX(240+240*screen_scale_x+hibari->getContentSize().width - hibari->getContentSize().width*2.f/3.f*t);
																																												  }, [=](float t)
																																												  {
																																													  hibari->setPositionX(240+240*screen_scale_x+hibari->getContentSize().width - hibari->getContentSize().width*2.f/3.f*t);
																																													  
																																													  typing_box2->setVisible(true);
																																													  typing_box2->setTouchSuction(true);
																																													  
																																													  typing_box->setTouchSuction(false);
																																													  
																																													  typing_box2->startTyping(myLoc->getLocalForKey(kMyLocalKey_scenarioMent34), end_func2);
																																												  }));
																															typing_box->setTouchOffScrollAndButton();
																															typing_box->setVisible(false);
																														};
																														
																														scenario_node->addChild(KSGradualValue<float>::create(0.f, 1.f, 0.3f, [=](float t)
																																											  {
																																												  t_gray->setOpacity(t*255);
																																												  asuka->setPositionX(240-240*screen_scale_x-asuka->getContentSize().width + asuka->getContentSize().width*2.f/3.f*t);
																																												  skip_menu->setPositionY(160+160*screen_scale_y - 25 + 150 - 150*t);
																																											  }, [=](float t)
																																											  {
																																												  t_gray->setOpacity(255);
																																												  asuka->setPositionX(240-240*screen_scale_x-asuka->getContentSize().width + asuka->getContentSize().width*2.f/3.f*t);
																																												  skip_menu->setPositionY(160+160*screen_scale_y - 25 + 150 - 150*t);
																																												  skip_menu->setEnabled(true);
																																												  
																																												  typing_box->startTyping(myLoc->getLocalForKey(kMyLocalKey_scenarioMent33), end_func1);
																																											  }));
																													}
																													else if(is_unlock_puzzle == 3)
																													{
																														myDSH->setIntegerForKey(kDSH_Key_showedScenario, 3000);
																														
																														CCSprite* hibari = CCSprite::create("kt_cha_hibari_1.png");
																														hibari->setAnchorPoint(ccp(0,0));
																														hibari->setPosition(ccp(240-240*screen_scale_x-hibari->getContentSize().width, 160-160*screen_scale_y));
																														scenario_node->addChild(hibari, 1);
																														
																														CCSprite* yagyu = CCSprite::create("kt_cha_yagyu_1.png");
																														yagyu->setAnchorPoint(ccp(1,0));
																														yagyu->setPosition(ccp(240+240*screen_scale_x+yagyu->getContentSize().width, 160-160*screen_scale_y));
																														yagyu->setVisible(false);
																														scenario_node->addChild(yagyu, 1);
																														
																														CCSprite* katsuragi = CCSprite::create("kt_cha_katsuragi_1.png");
																														katsuragi->setAnchorPoint(ccp(1,0));
																														katsuragi->setPosition(ccp(240+240*screen_scale_x+katsuragi->getContentSize().width, 160-160*screen_scale_y));
																														katsuragi->setVisible(false);
																														scenario_node->addChild(katsuragi, 1);
																														
																														CCSprite* ikaruga = CCSprite::create("kt_cha_ikaruga_1.png");
																														ikaruga->setAnchorPoint(ccp(0,0));
																														ikaruga->setPosition(ccp(240-240*screen_scale_x-ikaruga->getContentSize().width, 160-160*screen_scale_y));
																														ikaruga->setVisible(false);
																														scenario_node->addChild(ikaruga, 1);
																														
																														CCSprite* boy = CCSprite::create("kt_cha_black.png");
																														boy->setAnchorPoint(ccp(1,0));
																														boy->setPosition(ccp(240+240*screen_scale_x+boy->getContentSize().width, 160-160*screen_scale_y));
																														boy->setVisible(false);
																														scenario_node->addChild(boy, 1);
																														
																														typing_box->setHide();
																														
																														typing_box2->setTouchOffScrollAndButton();
																														typing_box2->setVisible(false);
																														typing_box2->setTouchSuction(false);
																														
																														typing_box->showAnimation(0.3f);
																														
																														function<void()> end_func11 = [=]()
																														{
																															skip_menu->setEnabled(false);
																															
																															mySGD->setIsUnlockPuzzle(0);
																															is_unlock_puzzle = 0;
																															
																															endUnlockAnimation();
																															
																															t_end_func();
																															
																															addChild(KSTimer::create(0.1f, [=]()
																																					 {
																																						 scenario_node->removeFromParent();
																																					 }));
																														};
																														
																														function<void()> end_func10 = [=]()
																														{
																															TypingBox::changeTypingBox(typing_box, typing_box2, ikaruga, katsuragi);
																															typing_box2->startTyping(myLoc->getLocalForKey(kMyLocalKey_scenarioMent52), end_func11);
																														};
																														
																														function<void()> end_func9 = [=]()
																														{
																															TypingBox::changeTypingBox(typing_box2, typing_box, katsuragi, ikaruga);
																															typing_box->startTyping(myLoc->getLocalForKey(kMyLocalKey_scenarioMent51), end_func10);
																														};
																														
																														function<void()> end_func8 = [=]()
																														{
																															typing_box2->startTyping(myLoc->getLocalForKey(kMyLocalKey_scenarioMent50), end_func9);
//																															katsuragi->setVisible(false);
//																															boy->setVisible(true);
//																															
//																															scenario_node->addChild(KSGradualValue<float>::create(0.f, 1.f, 0.3, [=](float t)
//																																												  {
//																																													  boy->setPositionX(240+240*screen_scale_x+boy->getContentSize().width - boy->getContentSize().width*2.f/3.f*t);
//																																												  }, [=](float t)
//																																												  {
//																																													  boy->setPositionX(240+240*screen_scale_x+boy->getContentSize().width - boy->getContentSize().width*2.f/3.f*t);
//																																													  
//																																													  typing_box->setVisible(true);
//																																													  typing_box->setTouchSuction(true);
//																																													  
//																																													  typing_box2->setTouchSuction(false);
//																																													  
//																																													  typing_box->startTyping(myLoc->getLocalForKey(kMyLocalKey_scenarioMent50), end_func9);
//																																												  }));
//																															typing_box2->setTouchOffScrollAndButton();
//																															typing_box2->setVisible(false);
																														};
																														
																														function<void()> end_func7 = [=]()
																														{
																															TypingBox::changeTypingBox(typing_box, typing_box2, ikaruga, katsuragi);
																															typing_box2->startTyping(myLoc->getLocalForKey(kMyLocalKey_scenarioMent49), end_func8);
																														};
																														
																														function<void()> end_func6 = [=]()
																														{
																															katsuragi->setVisible(false);
																															ikaruga->setVisible(true);
																															
																															scenario_node->addChild(KSGradualValue<float>::create(0.f, 1.f, 0.3, [=](float t)
																																												  {
																																													  ikaruga->setPositionX(240-240*screen_scale_x-ikaruga->getContentSize().width + ikaruga->getContentSize().width*2.f/3.f*t);
																																												  }, [=](float t)
																																												  {
																																													  ikaruga->setPositionX(240-240*screen_scale_x-ikaruga->getContentSize().width + ikaruga->getContentSize().width*2.f/3.f*t);
																																													  
																																													  typing_box->setVisible(true);
																																													  typing_box->setTouchSuction(true);
																																													  
																																													  typing_box2->setTouchSuction(false);
																																													  
																																													  typing_box->startTyping(myLoc->getLocalForKey(kMyLocalKey_scenarioMent48), end_func7);
																																												  }));
																															typing_box2->setTouchOffScrollAndButton();
																															typing_box2->setVisible(false);
																														};
																														
																														function<void()> end_func5 = [=]()
																														{
																															hibari->setVisible(false);
																															yagyu->setVisible(false);
																															katsuragi->setVisible(true);
																															
																															scenario_node->addChild(KSGradualValue<float>::create(0.f, 1.f, 0.3, [=](float t)
																																												  {
																																													  katsuragi->setPositionX(240+240*screen_scale_x+katsuragi->getContentSize().width - katsuragi->getContentSize().width*2.f/3.f*t);
																																												  }, [=](float t)
																																												  {
																																													  katsuragi->setPositionX(240+240*screen_scale_x+katsuragi->getContentSize().width - katsuragi->getContentSize().width*2.f/3.f*t);
																																													  
																																													  typing_box2->setVisible(true);
																																													  typing_box2->setTouchSuction(true);
																																													  
																																													  typing_box->setTouchSuction(false);
																																													  
																																													  typing_box2->startTyping(myLoc->getLocalForKey(kMyLocalKey_scenarioMent47), end_func6);
																																												  }));
																															typing_box->setTouchOffScrollAndButton();
																															typing_box->setVisible(false);
																														};
																														
																														function<void()> end_func4 = [=]()
																														{
																															TypingBox::changeTypingBox(typing_box2, typing_box, yagyu, hibari);
																															typing_box->startTyping(myLoc->getLocalForKey(kMyLocalKey_scenarioMent46), end_func5);
																														};
																														
																														function<void()> end_func3 = [=]()
																														{
																															TypingBox::changeTypingBox(typing_box, typing_box2, hibari, yagyu);
																															typing_box2->startTyping(myLoc->getLocalForKey(kMyLocalKey_scenarioMent45), end_func4);
																														};
																														
																														function<void()> end_func2 = [=]()
																														{
																															TypingBox::changeTypingBox(typing_box2, typing_box, yagyu, hibari);
																															typing_box->startTyping(myLoc->getLocalForKey(kMyLocalKey_scenarioMent44), end_func3);
																														};
																														
																														function<void()> end_func1 = [=]()
																														{
																															hibari->setVisible(false);
																															yagyu->setVisible(true);
																															
																															scenario_node->addChild(KSGradualValue<float>::create(0.f, 1.f, 0.3, [=](float t)
																																												  {
																																													  yagyu->setPositionX(240+240*screen_scale_x+yagyu->getContentSize().width - yagyu->getContentSize().width*2.f/3.f*t);
																																												  }, [=](float t)
																																												  {
																																													  yagyu->setPositionX(240+240*screen_scale_x+yagyu->getContentSize().width - yagyu->getContentSize().width*2.f/3.f*t);
																																													  
																																													  typing_box2->setVisible(true);
																																													  typing_box2->setTouchSuction(true);
																																													  
																																													  typing_box->setTouchSuction(false);
																																													  
																																													  typing_box2->startTyping(myLoc->getLocalForKey(kMyLocalKey_scenarioMent43), end_func2);
																																												  }));
																															typing_box->setTouchOffScrollAndButton();
																															typing_box->setVisible(false);
																														};
																														
																														scenario_node->addChild(KSGradualValue<float>::create(0.f, 1.f, 0.3f, [=](float t)
																																											  {
																																												  t_gray->setOpacity(t*255);
																																												  hibari->setPositionX(240-240*screen_scale_x-hibari->getContentSize().width + hibari->getContentSize().width*2.f/3.f*t);
																																												  skip_menu->setPositionY(160+160*screen_scale_y - 25 + 150 - 150*t);
																																											  }, [=](float t)
																																											  {
																																												  t_gray->setOpacity(255);
																																												  hibari->setPositionX(240-240*screen_scale_x-hibari->getContentSize().width + hibari->getContentSize().width*2.f/3.f*t);
																																												  skip_menu->setPositionY(160+160*screen_scale_y - 25 + 150 - 150*t);
																																												  skip_menu->setEnabled(true);
																																												  
																																												  typing_box->startTyping(myLoc->getLocalForKey(kMyLocalKey_scenarioMent42), end_func1);
																																											  }));
																													}
																													else if(is_unlock_puzzle == 4)
																													{
																														myDSH->setIntegerForKey(kDSH_Key_showedScenario, 4000);
																														
																														skip_menu->setEnabled(false);
																														
																														mySGD->setIsUnlockPuzzle(0);
																														is_unlock_puzzle = 0;
																														
																														endUnlockAnimation();
																														
																														t_end_func();
																														
																														addChild(KSTimer::create(0.1f, [=]()
																																				 {
																																					 scenario_node->removeFromParent();
																																				 }));
																													}
																													else if(is_unlock_puzzle == 5)
																													{
																														myDSH->setIntegerForKey(kDSH_Key_showedScenario, 5000);
																														
																														skip_menu->setEnabled(false);
																														
																														mySGD->setIsUnlockPuzzle(0);
																														is_unlock_puzzle = 0;
																														
																														endUnlockAnimation();
																														
																														t_end_func();
																														
																														addChild(KSTimer::create(0.1f, [=]()
																																				 {
																																					 scenario_node->removeFromParent();
																																				 }));
																													}
																												}
																											  else
																												{
																													mySGD->setIsUnlockPuzzle(0);
																													is_unlock_puzzle = 0;
																													
																													endUnlockAnimation();
																													
																													t_end_func();
																												}
																										  }));
													}));
			};
		}
		else
		{
			start_unlock_animation = [=](function<void()> t_end_func)
			{
				int refresh_cnt = 5 - myDSH->getIntegerForKey(kDSH_Key_heartCnt);
				if(refresh_cnt > 0)
				{
					LoadingLayer* t_loading = LoadingLayer::create(999);
					addChild(t_loading, 999);
					
					heart_refresh_loading = t_loading;
					
					mySGD->addChangeGoods("getHeart", kGoodsType_heart, refresh_cnt, "puzzleHeart", ccsf("%d", puzzle_number), "퍼즐클리어하트");
					mySGD->changeGoods(json_selector(this, MainFlowScene::puzzleHeartRefresh));
				}
				
				cell_node->addChild(KSTimer::create(0.7f, [=]()
													{
														cell_node->addChild(KSGradualValue<float>::create(0.f, 3.f, 0.5f, [=](float t)
																										  {
																											  if(t < 1.f)
																											  {
																												  cell_node->setScale(1.f+0.1f*t);
																											  }
																											  else if(t < 2.f)
																											  {
																												  cell_node->setScale(1.1f);
																											  }
																											  else
																											  {
																												  cell_node->setScale(1.1f-0.1f*(t-2.f));
																											  }
																										  }, [=](float t)
																										  {
																											  cell_node->setScale(1.f);
																											  
//																											  if(myDSH->getIntegerForKey(kDSH_Key_heartCnt) < mySGD->getHeartMax())
//																											  {
//																												  myDSH->setIntegerForKey(kDSH_Key_heartCnt, mySGD->getHeartMax());
//																												  
//																												  CCNode* target_parent = heart_time->getParent();
//																												  CCPoint heart_time_position = heart_time->getPosition();
//																												  int heart_time_tag = heart_time->getTag();
//																												  
//																												  heart_time->removeFromParent();
//																												  heart_time = HeartTime::create();
//																												  heart_time->setPosition(heart_time_position);
//																												  target_parent->addChild(heart_time, 0, heart_time_tag);
//																											  }
																											  
																											  if(!t_info.is_base_condition_success)
																											  {
																												  ASPopupView* t_popup = ASPopupView::create(-999);
																												  
																												  CCSize screen_size = CCEGLView::sharedOpenGLView()->getFrameSize();
																												  float screen_scale_x = screen_size.width/screen_size.height/1.5f;
																												  if(screen_scale_x < 1.f)
																													  screen_scale_x = 1.f;
																												  
																												  float height_value = 320.f;
																												  if(myDSH->screen_convert_rate < 1.f)
																													  height_value = 320.f/myDSH->screen_convert_rate;
																												  
																												  if(height_value < myDSH->ui_top)
																													  height_value = myDSH->ui_top;
																												  
																												  t_popup->setDimmedSize(CCSizeMake(screen_scale_x*480.f, height_value));// /myDSH->screen_convert_rate));
																												  t_popup->setDimmedPosition(ccp(240, 160));
																												  t_popup->setBasePosition(ccp(240, 160));
																												  
																												  CCNode* t_container = CCNode::create();
																												  t_popup->setContainerNode(t_container);
																												  addChild(t_popup, kMainFlowZorder_popup);
																												  
																												  CCSprite* back_case = CCSprite::create("popup_small_back.png");
																												  back_case->setPosition(ccp(0,0));
																												  t_container->addChild(back_case);
																												  
																												  startFormSetter(this);
																												  CCScale9Sprite* back_in = CCScale9Sprite::create("common_grayblue.png", CCRectMake(0, 0, 26, 26), CCRectMake(12, 12, 2, 2));
																												  back_in->setContentSize(CCSizeMake(251, 113));
																												  back_in->setPosition(ccp(back_case->getContentSize().width/2.f, back_case->getContentSize().height/2.f-12));
																												  back_case->addChild(back_in);
																												  
																												  
																												  KSLabelTTF* title_label = KSLabelTTF::create(myLoc->getLocalForKey(kMyLocalKey_notOpenPuzzleNotEnoughtStarTitle), mySGD->getFont().c_str(), 12);
																												  title_label->disableOuterStroke();
																												  title_label->setAnchorPoint(ccp(0.5f,0.5f));
																												  title_label->setPosition(ccp(-85,back_case->getContentSize().height/2.f-35));
																												  t_container->addChild(title_label);
																												  
																												  StyledLabelTTF* sub_label = StyledLabelTTF::create(CCString::createWithFormat(myLoc->getLocalForKey(kMyLocalKey_notOpenPuzzleNotEnoughtStarContent), t_info.need_star_count)->getCString(), mySGD->getFont().c_str(), 12, 999, StyledAlignment::kCenterAlignment);
																												  sub_label->setAnchorPoint(ccp(0.5f,0.5f));
																												  sub_label->setPosition(ccpFromSize(back_in->getContentSize()/2.f)); 			// dt (0.0,-13.5)
																												  back_in->addChild(sub_label);
																												  
																												  
																												  
																												  setFormSetter(back_case);
																												  setFormSetter(back_in);
																												  setFormSetter(title_label);
																												  setFormSetter(sub_label);
																												  CCSprite* gray = t_popup->getDimmedSprite();
																												  
																												  CommonButton* ok_button = CommonButton::createCloseButton(t_popup->getTouchPriority() - 5);
																												  ok_button->setFunction([=](CCObject*){
																													  if(!t_popup->is_menu_enable)
																														  return;
																													  
																													  t_popup->is_menu_enable = false;
																													  
																													  CommonAnimation::closePopup(t_popup, t_container, gray, [=](){
																														  
																													  }, [=](){
																														  endUnlockAnimation();
																														  t_end_func();
																														  t_popup->removeFromParent();
																													  });
																												  });
																												  t_container->addChild(ok_button);
																												  ok_button->setPosition(ccpFromSize(back_case->getContentSize()/2.f) + ccp(-25,-22)); 			// dt (1.5,-18.5)
																												  ok_button->setTouchPriority(t_popup->getTouchPriority()-5);
																												  setFormSetter(ok_button);
																												  
																												  
																												  CommonAnimation::openPopup(this, t_container, gray, [=](){
																													  
																												  }, [=](){
																													  t_popup->is_menu_enable = true;
																												  });
																											  }
																											  else
																											  {
																												  endUnlockAnimation();
																												  t_end_func();
																											  }
																											  
																											  mySGD->setIsUnlockPuzzle(0);
																											  is_unlock_puzzle = 0;
																										  }));
													}));
			};
		}
	}
	else if(puzzle_number == is_perfect_puzzle)
	{
		LoadingLayer* loading_layer = LoadingLayer::create(-9999);
		addChild(loading_layer, 9999);
		
		mySGD->addChangeGoods("b_pft", kGoodsType_ruby, 0, "", CCString::createWithFormat("%d", puzzle_number)->getCString());
		mySGD->changeGoods([=](Json::Value result_data)
						   {
							   if(result_data["result"]["code"].asInt() == GDSUCCESS)
							   {
//								   PuzzleSuccessAndPerfect* t_popup = PuzzleSuccessAndPerfect::create(-99999, [=](){
									   loading_layer->removeFromParent();
//								   }, false);
//								   addChild(t_popup, kMainFlowZorder_popup);
								   
								   mySGD->setIsPerfectPuzzle(0);
								   is_perfect_puzzle = 0;
							   }
						   });
	}
	
	return cell;
}

void MainFlowScene::detailCondition(CCObject* sender, CCControlEvent t_event)
{
	if(!is_menu_enable)
		return;
	
	is_menu_enable = false;
	
	int tag = ((CCNode*)sender)->getTag();
	
	AudioEngine::sharedInstance()->playEffect("se_button1.mp3", false);
	
	if(tag == 0)
	{
		StyledLabelTTF* content_label = StyledLabelTTF::create(myLoc->getLocalForKey(kMyLocalKey_detailConditionPopupContent), mySGD->getFont().c_str(), 12,999,StyledAlignment::kCenterAlignment);
		content_label->setAnchorPoint(ccp(0.5f,0.5f));
		
		ASPopupView* t_popup = ASPopupView::getCommonNoti(-800,
																											myLoc->getLocalForKey(kMyLocalKey_detailConditionPopupTitle),
																											(CCNode*)content_label, [=](){is_menu_enable = true;},
																											12.f, CCPointZero,true);
		
	//	DetailConditionPopup* t_popup = DetailConditionPopup::create(-800, [=](){is_menu_enable = true;});
		addChild(t_popup, kMainFlowZorder_popup);
	}
	else
	{
		int t_index = (tag-10000000)/10000;
		int t_need_ruby = tag%10000;
		
		LoadingLayer* t_loading = LoadingLayer::create(-9999);
		addChild(t_loading, 9999);
		
		int puzzle_number = not_event_puzzle_list[t_index];// NSDS_GI(kSDS_GI_puzzleList_int1_no_i, t_index+1);
		PuzzleHistory t_history = mySGD->getPuzzleHistory(puzzle_number);
		t_history.is_open = true;
		t_history.open_type = "젬결제";
		
		mySGD->addChangeGoods(CCString::createWithFormat("p_p_%d", puzzle_number)->getCString());
		
		vector<CommandParam> command_list;
		
		command_list.push_back(mySGD->getUpdatePuzzleHistoryParam(t_history, nullptr));
		
		mySGD->changeGoodsTransaction(command_list, [=](Json::Value result_data)
									  {
										  t_loading->removeFromParent();
										  if(result_data["result"]["code"].asInt() == GDSUCCESS)
										  {
											  is_menu_enable = true;
											  puzzle_table->updateCellAtIndex(t_index);
										  }
										  else
										  {
											  mySGD->clearChangeGoods();
											  PuzzleHistory t_history = mySGD->getPuzzleHistory(puzzle_number);
											  t_history.is_open = false;
											  t_history.open_type = "";
											  mySGD->setPuzzleHistoryForNotSave(t_history);
											  
											  addChild(ASPopupView::getCommonNoti(-9999, myLoc->getLocalForKey(kMyLocalKey_noti), myLoc->getLocalForKey(kMyLocalKey_rubyNotEnought)), 9999);
											  
//											  addChild(ASPopupView::getNotEnoughtGoodsGoShopPopup(-9999, kGoodsType_ruby, [=]()
//											  {
//												  is_menu_enable = false;
//												  ShopPopup* t_shop = ShopPopup::create();
//												  t_shop->setHideFinalAction(this, callfunc_selector(MainFlowScene::popupClose));
//												  t_shop->targetHeartTime(heart_time);
//												  t_shop->setShopCode(kSC_ruby);
//												  t_shop->setShopBeforeCode(kShopBeforeCode_mainflow);
//												  t_shop->addGray();
//												  addChild(t_shop, kMainFlowZorder_popup);
//											  }), 9999);
											  
											  is_menu_enable = true;
										  }
									  });
	}
}

void MainFlowScene::endUnlockAnimation()
{
	puzzle_table->setTouchEnabled(true);
	puzzle_table->setTouchPriority(kCCMenuHandlerPriority+1);
	is_menu_enable = true;
}

void MainFlowScene::scrollViewDidScroll(CCScrollView* view){}
void MainFlowScene::scrollViewDidZoom(CCScrollView* view){}
void MainFlowScene::tableCellTouched(CCTableView* table, CCTableViewCell* cell){}
CCSize MainFlowScene::cellSizeForTable(CCTableView *table)
{
	return CCSizeMake(126, 245);//132, 245);
}
unsigned int MainFlowScene::numberOfCellsInTableView(CCTableView *table)
{
	int puzzle_count = not_event_puzzle_list.size();//NSDS_GI(kSDS_GI_puzzleListCount_i);
	
	int view_count = puzzle_count - locked_puzzle_count;
	view_count += mySGD->getUnlockFrameCnt() + 1;
	
	if(view_count > puzzle_count + 1)
		view_count = puzzle_count + 1;
	
	return view_count;
	
//	return NSDS_GI(kSDS_GI_puzzleListCount_i);// eventListCount_i);
}

enum MainFlowMenuTag{
	kMainFlowMenuTag_rubyShop = 1,
	kMainFlowMenuTag_goldShop,
	kMainFlowMenuTag_heartShop,
	kMainFlowMenuTag_friendPointContent,
	kMainFlowMenuTag_postbox,
	kMainFlowMenuTag_option,
	kMainFlowMenuTag_tip,
	kMainFlowMenuTag_rank,
	kMainFlowMenuTag_shop,
	kMainFlowMenuTag_cardSetting,
	kMainFlowMenuTag_mission,
	kMainFlowMenuTag_friendManagement,
	kMainFlowMenuTag_gacha,
	kMainFlowMenuTag_achievement,
	kMainFlowMenuTag_event,
	kMainFlowMenuTag_endlessMode
};

void MainFlowScene::showShopPopup(int t_code)
{
    is_menu_enable = false;
    
    ShopPopup* t_shop = ShopPopup::create();
    t_shop->setHideFinalAction(this, callfunc_selector(MainFlowScene::popupClose));
    t_shop->targetHeartTime(heart_time);
    t_shop->setShopCode((ShopCode)t_code);
    t_shop->setShopBeforeCode(kShopBeforeCode_mainflow);
//    t_shop->addGray();
    addChild(t_shop, kMainFlowZorder_popup+100);
}

void MainFlowScene::menuAction(CCObject* sender)
{
	if(!is_menu_enable)
		return;
	
	AudioEngine::sharedInstance()->playEffect("se_button1.mp3", false);
	
	int tag = ((CCNode*)sender)->getTag();
	TutorialFlowStep recent_step = (TutorialFlowStep)myDSH->getIntegerForKey(kDSH_Key_tutorial_flowStep);
	
	if(recent_step == kTutorialFlowStep_puzzleClick)
	{
		return;
	}
	else if(recent_step == kTutorialFlowStep_cardCollectionClick)
	{
		if(tag == kMainFlowMenuTag_cardSetting)
		{
			myDSH->setIntegerForKey(kDSH_Key_tutorial_flowStep, kTutorialFlowStep_upgradeClick);
			is_menu_enable = false;
			
			mySGD->before_cardsetting = kSceneCode_PuzzleMapScene;
			CardSettingPopup* t_popup = CardSettingPopup::create();
			t_popup->setHideFinalAction(this, callfunc_selector(MainFlowScene::tutorialCardSettingClose));
			addChild(t_popup, kMainFlowZorder_popup);
			
			removeChild(tutorial_node);
		}
	}
	else
	{
		is_menu_enable = false;
		
		if(tag == kMainFlowMenuTag_rubyShop)
		{
			addChild(ASPopupView::getCommonNoti(-9999, myLoc->getLocalForKey(kMyLocalKey_noti), myLoc->getLocalForKey(kMyLocalKey_afterOpenCBT), [=](){is_menu_enable = true;}), 9999);
//			ShopPopup* t_shop = ShopPopup::create();
//			t_shop->setHideFinalAction(this, callfunc_selector(MainFlowScene::popupClose));
//			t_shop->targetHeartTime(heart_time);
//			t_shop->setShopCode(kSC_ruby);
//			t_shop->setShopBeforeCode(kShopBeforeCode_mainflow);
//			t_shop->addGray();
//			addChild(t_shop, kMainFlowZorder_popup);
		}
		else if(tag == kMainFlowMenuTag_goldShop)
		{
			ShopPopup* t_shop = ShopPopup::create();
			t_shop->setHideFinalAction(this, callfunc_selector(MainFlowScene::popupClose));
			t_shop->targetHeartTime(heart_time);
			t_shop->setShopCode(kSC_gold);
			t_shop->setShopBeforeCode(kShopBeforeCode_mainflow);
			t_shop->addGray();
			addChild(t_shop, kMainFlowZorder_popup);
		}
		else if(tag == kMainFlowMenuTag_heartShop)
		{
			ShopPopup* t_shop = ShopPopup::create();
			t_shop->setHideFinalAction(this, callfunc_selector(MainFlowScene::popupClose));
			t_shop->targetHeartTime(heart_time);
			t_shop->setShopCode(kSC_heart);
			t_shop->setShopBeforeCode(kShopBeforeCode_mainflow);
			t_shop->addGray();
			addChild(t_shop, kMainFlowZorder_popup);
		}
		else if(tag == kMainFlowMenuTag_friendPointContent)
		{
			TouchSuctionLayer* t_suction = TouchSuctionLayer::create(-300);
			t_suction->setTouchEnabled(true);
			t_suction->target_touch_began = this;
			t_suction->delegate_touch_began = callfunc_selector(MainFlowScene::closeFriendPoint);
			
			CCSize screen_size = CCEGLView::sharedOpenGLView()->getFrameSize();
			float screen_scale_x = screen_size.width/screen_size.height/1.5f;
			if(screen_scale_x < 1.f)
				screen_scale_x = 1.f;
			
			float screen_scale_y = myDSH->ui_top/320.f/myDSH->screen_convert_rate;
			CCSprite* stencil_node = CCSprite::create("whitePaper.png", CCRectMake(0, 0, 78, 150));
			stencil_node->setPosition(ccp(336,229+160.f*(screen_scale_y-1.f)));
			CCClippingNode* cliping_node = CCClippingNode::create(stencil_node);
			float change_scale = 1.f;
			CCPoint change_origin = ccp(0,0);
			if(screen_scale_x > 1.f)
			{
				change_origin.x = -(screen_scale_x-1.f)*480.f/2.f;
				change_scale = screen_scale_x;
			}
			if(screen_scale_y > 1.f)
				change_origin.y = -(screen_scale_y-1.f)*320.f/2.f;
			CCSize win_size = CCDirector::sharedDirector()->getWinSize();
//			cliping_node->setRectYH(CCRectMake(change_origin.x, change_origin.y, win_size.width*change_scale, win_size.height*change_scale));
			cliping_node->setAlphaThreshold(0.05f);
			cliping_node->setPosition(CCPointZero);
			t_suction->addChild(cliping_node);
			
			CCSprite* inner_img = CCSprite::create("candy_popup.png");
			inner_img->setPosition(ccp(336,229+160.f*(screen_scale_y-1.f)+150));
			cliping_node->addChild(inner_img);
			
			CCMoveTo* t_move_down = CCMoveTo::create(0.3f, ccp(336,229+160.f*(screen_scale_y-1.f)));
			inner_img->runAction(t_move_down);
			
			close_friend_point_action = [=](){
				t_suction->target_touch_began = NULL;
				t_suction->delegate_touch_began = NULL;
				
				CCMoveTo* t_move_up = CCMoveTo::create(0.3f, ccp(336,229+160.f*(screen_scale_y-1.f)+150));
				CCCallFunc* t_call = CCCallFunc::create(t_suction, callfunc_selector(CCLayer::removeFromParent));
				CCSequence* t_seq = CCSequence::create(t_move_up, t_call, NULL);
				inner_img->runAction(t_seq);
			};
			addChild(t_suction, kMainFlowZorder_top-1);
			
			is_menu_enable = true;
		}
		else if(tag == kMainFlowMenuTag_postbox)
		{
            TRACE();
			SumranMailPopup* t_pp = SumranMailPopup::create(this, callfunc_selector(MainFlowScene::mailPopupClose), bind(&MainFlowScene::heartRefresh, this));
			addChild(t_pp, kMainFlowZorder_popup);
			
			postbox_count_case->setVisible(false);
            TRACE();
		}
		else if(tag == kMainFlowMenuTag_option)
		{
			OptionPopup* t_popup = OptionPopup::create();
			t_popup->setHideFinalAction(this, callfunc_selector(MainFlowScene::popupClose));
			addChild(t_popup, kMainFlowZorder_popup);
			
			t_popup->open_message_popup_func = [=]()
			{
				is_menu_enable = false;
				SumranMailPopup* t_pp = SumranMailPopup::create(this, callfunc_selector(MainFlowScene::mailPopupClose), bind(&MainFlowScene::heartRefresh, this));
				addChild(t_pp, kMainFlowZorder_popup);
				
				postbox_count_case->setVisible(false);
			};
		}
		else if(tag == kMainFlowMenuTag_tip)
		{
			TouchSuctionLayer* t_suction = TouchSuctionLayer::create(-200);
			t_suction->target_touch_began = t_suction;
			t_suction->delegate_touch_began = callfunc_selector(TouchSuctionLayer::removeFromParent);
			t_suction->setTouchEnabled(true);
			
			CCSprite* dimed_tip = CCSprite::create("tutorial_dimed_main.png");
			dimed_tip->setPosition(ccp(240,160));
			t_suction->addChild(dimed_tip);
			
			addChild(t_suction, kMainFlowZorder_popup);
			
			is_menu_enable = true;
		}
		else if(tag == kMainFlowMenuTag_rank)
		{
			RankNewPopup* t_popup = RankNewPopup::create();
			t_popup->setHideFinalAction(this, callfunc_selector(MainFlowScene::popupClose));
			addChild(t_popup, kMainFlowZorder_popup);
			
//			RankPopup* t_rp = RankPopup::create(this, callfunc_selector(MainFlowScene::popupClose));
//			addChild(t_rp, kMainFlowZorder_popup);
		}
		else if(tag == kMainFlowMenuTag_shop)
		{
			ShopPopup* t_shop = ShopPopup::create();
			t_shop->setHideFinalAction(this, callfunc_selector(MainFlowScene::popupClose));
			t_shop->targetHeartTime(heart_time);
			t_shop->setShopCode(kSC_gold);
			t_shop->setShopBeforeCode(kShopBeforeCode_mainflow);
			t_shop->addGray();
			addChild(t_shop, kMainFlowZorder_popup);
		}
		else if(tag == kMainFlowMenuTag_cardSetting)
		{
			puzzle_table->setTouchEnabled(false);
			mySGD->before_cardsetting = kSceneCode_PuzzleMapScene;
			CardSettingPopup* t_popup = CardSettingPopup::create();
			t_popup->setHideFinalAction(this, callfunc_selector(MainFlowScene::tutorialCardSettingClose));
			addChild(t_popup, kMainFlowZorder_popup);
		}
		else if(tag == kMainFlowMenuTag_mission)
		{
			TodayMissionPopup* t_popup = TodayMissionPopup::create(-300, [=](){is_menu_enable = true;});
			addChild(t_popup, kMainFlowZorder_popup);
		}
		else if(tag == kMainFlowMenuTag_friendManagement)
		{
			is_menu_enable = true;

			InviteEventPopup* t_rp = InviteEventPopup::create(this, callfunc_selector(MainFlowScene::tutorialCardSettingClose));

			addChild(t_rp, kMainFlowZorder_popup);

		}
		else if(tag == kMainFlowMenuTag_gacha)
		{
			GachaPurchase* t_gp = GachaPurchase::create();
			addChild(t_gp, kMainFlowZorder_popup);
			
			t_gp->setHideFinalAction(this, callfunc_selector(MainFlowScene::popupClose));
			t_gp->setOutAllObjectAction(NULL, NULL);
			t_gp->setInAllObjectAction(this, callfunc_selector(MainFlowScene::popupClose));
		}
		else if(tag == kMainFlowMenuTag_achievement)
		{
			AchievePopup* t_ap = AchievePopup::create();
			addChild(t_ap, kMainFlowZorder_popup);
			
			t_ap->setHideFinalAction(this, callfunc_selector(MainFlowScene::achievePopupClose));
		}
		else if(tag == kMainFlowMenuTag_event)
		{
			is_menu_enable = true;
			string serverUrl = myHSP->getServerAddress();
			string os="ios";
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
			os="android";
#endif
			string lang = KS::getLocalCode();
			string cc = myHSP->getCountryCode();
			string tz = myHSP->getTimeZone();
			myHSP->openHSPUrl(serverUrl+"/event.php?lang="+lang+"&country="+cc+"&timezone="+tz+"&os="+os);
//			CCDirector::sharedDirector()->replaceScene(NewMainFlowScene::scene());
			
//			is_menu_enable = true; // 임시
//			EventPopup* t_popup = EventPopup::create();
//			t_popup->setHideFinalAction(this, callfunc_selector(MainFlowScene::popupClose));
//			addChild(t_popup, kMainFlowZorder_popup);
		}
		else if(tag == kMainFlowMenuTag_endlessMode)
		{
			if(mySGD->getUserdataHighPiece() < mySGD->getEndlessMinPiece())
			{
				StyledLabelTTF* sub_label = StyledLabelTTF::create(CCString::createWithFormat(myLoc->getLocalForKey(kMyLocalKey_endlessOpenConditionContent), mySGD->getEndlessMinPiece())->getCString(), mySGD->getFont().c_str(), 12, 999, StyledAlignment::kCenterAlignment);
				sub_label->setAnchorPoint(ccp(0.5f,0.5f));
				
				addChild(ASPopupView::getCommonNoti(-999,
																						myLoc->getLocalForKey(kMyLocalKey_endlessOpenConditionTitle), sub_label, [=](){is_menu_enable = true;},
																						12.f, ccp(0,0), true), 999);
				
//				ASPopupView* t_popup = ASPopupView::create(-999);
//				
//				CCSize screen_size = CCEGLView::sharedOpenGLView()->getFrameSize();
//				float screen_scale_x = screen_size.width/screen_size.height/1.5f;
//				if(screen_scale_x < 1.f)
//					screen_scale_x = 1.f;
//				
//				float height_value = 320.f;
//				if(myDSH->screen_convert_rate < 1.f)
//					height_value = 320.f/myDSH->screen_convert_rate;
//				
//				if(height_value < myDSH->ui_top)
//					height_value = myDSH->ui_top;
//				
//				t_popup->setDimmedSize(CCSizeMake(screen_scale_x*480.f, height_value));// /myDSH->screen_convert_rate));
//				t_popup->setDimmedPosition(ccp(240, 160));
//				t_popup->setBasePosition(ccp(240, 160));
//				
//				CCNode* t_container = CCNode::create();
//				t_popup->setContainerNode(t_container);
//				addChild(t_popup, 999);
//				
//				CCScale9Sprite* back_case = CCScale9Sprite::create("mainpopup_back.png", CCRectMake(0,0,50,50), CCRectMake(24,24,2,2));
//				back_case->setContentSize(CCSizeMake(240,120));
//				back_case->setPosition(ccp(0,0));
//				t_container->addChild(back_case);
//				
//				CCScale9Sprite* back_in = CCScale9Sprite::create("mainpopup_front.png", CCRectMake(0, 0, 50, 50), CCRectMake(24, 24, 2, 2));
//				back_in->setContentSize(CCSizeMake(back_case->getContentSize().width-10, back_case->getContentSize().height-46));
//				back_in->setPosition(ccp(back_case->getContentSize().width/2.f, back_case->getContentSize().height/2.f-17));
//				back_case->addChild(back_in);
//				
//				KSLabelTTF* title_label = KSLabelTTF::create(myLoc->getLocalForKey(kMyLocalKey_endlessOpenConditionTitle), mySGD->getFont().c_str(), 15);
//				title_label->setColor(ccc3(255, 170, 20));
//				title_label->setAnchorPoint(ccp(0.5,0.5f));
//				title_label->setPosition(ccp(0,back_case->getContentSize().height/2.f-25));
//				t_container->addChild(title_label);
//				
//				StyledLabelTTF* sub_label = StyledLabelTTF::create(CCString::createWithFormat(myLoc->getLocalForKey(kMyLocalKey_endlessOpenConditionContent), mySGD->getEndlessMinPiece())->getCString(), mySGD->getFont().c_str(), 12, 999, StyledAlignment::kCenterAlignment);
//				sub_label->setPosition(ccp(0,-10));
//				sub_label->setOldAnchorPoint();
//				t_container->addChild(sub_label);
//				
//				CCSprite* gray = t_popup->getDimmedSprite();
//				
//				CommonButton* close_button = CommonButton::createCloseButton(t_popup->getTouchPriority()-5);
//				close_button->setPosition(ccp(back_case->getContentSize().width/2.f-25,back_case->getContentSize().height/2.f-25));
//				close_button->setFunction([=](CCObject* sender)
//										  {
//											  if(!t_popup->is_menu_enable)
//												  return;
//											  
//											  t_popup->is_menu_enable = false;
//											  
//												CommonAnimation::closePopup(this, t_container, gray, [=](){
//													
//												}, [=](){
//													is_menu_enable = true;
//													t_popup->removeFromParent();
////													end_func(); removeFromParent();
//												});
//										  });
//				t_container->addChild(close_button);
//				
//				CommonAnimation::openPopup(this, t_container, gray, [=](){
//					
//				}, [=](){
//					t_popup->is_menu_enable = true;
//				});
			}
			else
				showEndlessOpening();
		}
	}
}

void MainFlowScene::showEndlessOpening()
{
	mySGD->is_endless_mode = false;
	mySGD->resetReplayPlayingInfo();
	
	if(kind_tutorial_pvp != nullptr)
	{
		kind_tutorial_pvp();
		kind_tutorial_pvp = nullptr;
	}
	
	puzzle_table->setTouchEnabled(false);
	EndlessModeOpening* t_popup = EndlessModeOpening::create();
	t_popup->setHideFinalAction(this, callfunc_selector(MainFlowScene::tutorialCardSettingClose));
	t_popup->refresh_ing_win_func = refresh_ing_win_func;
	addChild(t_popup, kMainFlowZorder_popup);
}

void MainFlowScene::showEndlessResult()
{
    TRACE();
	puzzle_table->setTouchEnabled(false);
	TRACE();
    EndlessModeResult* t_popup = EndlessModeResult::create();
	TRACE();
    t_popup->setHideFinalAction(this, callfunc_selector(MainFlowScene::showEndlessOpening));
	t_popup->refresh_achieve_func = bind(&MainFlowScene::countingAchievement, this);
	TRACE();
    addChild(t_popup, kMainFlowZorder_popup);
	TRACE();
    if(refresh_ing_win_func != nullptr)
        refresh_ing_win_func();
    TRACE();
}

void MainFlowScene::bottomOpenning()
{
	for(int i=0;i<bottom_list.size();i++)
	{
		CCPoint original_position = bottom_list[i]->getPosition();
		bottom_list[i]->setPositionY(original_position.y-100);
		
		CCDelayTime* t_delay = CCDelayTime::create(i*0.1f);
		CCMoveTo* t_move = CCMoveTo::create(0.2f, original_position);
		CCSequence* t_seq = CCSequence::create(t_delay, t_move, NULL);
		
		bottom_list[i]->runAction(t_seq);
	}
}

void MainFlowScene::bottomPuzzleMode()
{
	for(int i=0;i<bottom_list.size();i++)
	{
		CCDelayTime* t_delay = CCDelayTime::create(i*0.05f);
		CCMoveTo* t_move = CCMoveTo::create(0.1f, ccp(bottom_list[i]->getPositionX(), bottom_list[i]->getPositionY()-100));
		CCSequence* t_seq = CCSequence::create(t_delay, t_move, NULL);
		
		bottom_list[i]->runAction(t_seq);
	}
}

void MainFlowScene::setBottom()
{
	bottom_list.clear();
	
//	CCNode* bottom_case = CCNode::create();
//	bottom_case->setAnchorPoint(ccp(0.5f,0.5f));
//	bottom_case->setPosition(ccp(240,-(myDSH->puzzle_ui_top-320.f)/2.f+10));
//	addChild(bottom_case, kMainFlowZorder_uiButton);
//	
//	bottom_list.push_back(bottom_case);
	
	
	CCSprite* n_rank = CCSprite::create("mainflow_rank.png");
	KSLabelTTF* n_rank_label = KSLabelTTF::create(myLoc->getLocalForKey(kMyLocalKey_ranking), mySGD->getFont().c_str(), 12);
	n_rank_label->enableOuterStroke(ccBLACK, 1.f);
	n_rank_label->setPosition(ccp(n_rank->getContentSize().width/2.f, 7));
	n_rank->addChild(n_rank_label);
	CCSprite* s_rank = CCSprite::create("mainflow_rank.png");
	s_rank->setColor(ccGRAY);
	KSLabelTTF* s_rank_label = KSLabelTTF::create(myLoc->getLocalForKey(kMyLocalKey_ranking), mySGD->getFont().c_str(), 12);
	s_rank_label->enableOuterStroke(ccBLACK, 1.f);
	s_rank_label->setPosition(ccp(s_rank->getContentSize().width/2.f, 7));
	s_rank->addChild(s_rank_label);
	
	CCMenuItem* rank_item = CCMenuItemSprite::create(n_rank, s_rank, this, menu_selector(MainFlowScene::menuAction));
	rank_item->setTag(kMainFlowMenuTag_rank);
	
	CCMenu* rank_menu = CCMenu::createWithItem(rank_item);
	rank_menu->setPosition(ccp(240,-(myDSH->puzzle_ui_top-320.f)/2.f+10) + ccp(32-240, n_rank->getContentSize().height/2.f+6));//ccp(-205, n_rank->getContentSize().height/2.f));
//	bottom_case->addChild(rank_menu);
	addChild(rank_menu, kMainFlowZorder_uiButton);
	bottom_list.push_back(rank_menu);
	
	rank_menu->setTouchPriority(kCCMenuHandlerPriority-1);
	
//	{
//		CCSprite* t_bar = CCSprite::create("mainflow_bottom_case_bar.png");
//		t_bar->setPosition(ccp(43-240+214.f/8.f, n_rank->getContentSize().height/2.f-4));
//		bottom_case->addChild(t_bar, -1);
//	}
	
	
	CCSprite* n_shop = CCSprite::create("mainflow_shop.png");
	KSLabelTTF* n_shop_label = KSLabelTTF::create(myLoc->getLocalForKey(kMyLocalKey_shop), mySGD->getFont().c_str(), 12);
	n_shop_label->enableOuterStroke(ccBLACK, 1.f);
	n_shop_label->setPosition(ccp(n_shop->getContentSize().width/2.f, 7));
	n_shop->addChild(n_shop_label);
	CCSprite* s_shop = CCSprite::create("mainflow_shop.png");
	s_shop->setColor(ccGRAY);
	KSLabelTTF* s_shop_label = KSLabelTTF::create(myLoc->getLocalForKey(kMyLocalKey_shop), mySGD->getFont().c_str(), 12);
	s_shop_label->enableOuterStroke(ccBLACK, 1.f);
	s_shop_label->setPosition(ccp(s_shop->getContentSize().width/2.f, 7));
	s_shop->addChild(s_shop_label);
	
	if(NSDS_GB(kSDS_GI_shop_isEvent_b))
	{
		CCSprite* n_shop_event = CCSprite::create("mainflow_new.png");
		n_shop_event->setPosition(ccp(n_shop->getContentSize().width-8, n_shop->getContentSize().height-n_shop_event->getContentSize().height+8));
		n_shop->addChild(n_shop_event);
		
		CCSprite* s_shop_event = CCSprite::create("mainflow_new.png");
		s_shop_event->setPosition(ccp(s_shop->getContentSize().width-8, s_shop->getContentSize().height-s_shop_event->getContentSize().height+8));
		s_shop->addChild(s_shop_event);
		s_shop_event->setColor(ccGRAY);
	}
	
	CCMenuItem* shop_item = CCMenuItemSprite::create(n_shop, s_shop, this, menu_selector(MainFlowScene::menuAction));
	shop_item->setTag(kMainFlowMenuTag_shop);
	
	CCMenu* shop_menu = CCMenu::createWithItem(shop_item);
	shop_menu->setPosition(ccp(240,-(myDSH->puzzle_ui_top-320.f)/2.f+10) + ccp(32-240+55, n_shop->getContentSize().height/2.f+6));//ccp(-73, n_shop->getContentSize().height/2.f));
//	bottom_case->addChild(shop_menu);
	addChild(shop_menu, kMainFlowZorder_uiButton);
	bottom_list.push_back(shop_menu);
	
	shop_menu->setTouchPriority(kCCMenuHandlerPriority-1);
	
//	{
//		CCSprite* t_bar = CCSprite::create("mainflow_bottom_case_bar.png");
//		t_bar->setPosition(ccp(43-240+214.f/8.f*3.f, n_rank->getContentSize().height/2.f-4));
//		bottom_case->addChild(t_bar, -1);
//	}
		
	CCSprite* n_cardsetting = CCSprite::create("mainflow_cardsetting.png");
	KSLabelTTF* n_cardsetting_label = KSLabelTTF::create(myLoc->getLocalForKey(kMyLocalKey_mycard), mySGD->getFont().c_str(), 12);
	n_cardsetting_label->enableOuterStroke(ccBLACK, 1.f);
	n_cardsetting_label->setPosition(ccp(n_cardsetting->getContentSize().width/2.f, 7));
	n_cardsetting->addChild(n_cardsetting_label);
	CCSprite* s_cardsetting = CCSprite::create("mainflow_cardsetting.png");
	s_cardsetting->setColor(ccGRAY);
	KSLabelTTF* s_cardsetting_label = KSLabelTTF::create(myLoc->getLocalForKey(kMyLocalKey_mycard), mySGD->getFont().c_str(), 12);
	s_cardsetting_label->enableOuterStroke(ccBLACK, 1.f);
	s_cardsetting_label->setPosition(ccp(s_cardsetting->getContentSize().width/2.f, 7));
	s_cardsetting->addChild(s_cardsetting_label);
	
	CCMenuItem* cardsetting_item = CCMenuItemSprite::create(n_cardsetting, s_cardsetting, this, menu_selector(MainFlowScene::menuAction));
	cardsetting_item->setTag(kMainFlowMenuTag_cardSetting);
	
	CCMenu* cardsetting_menu = CCMenu::createWithItem(cardsetting_item);
	cardsetting_menu->setPosition(ccp(240,-(myDSH->puzzle_ui_top-320.f)/2.f+10) + ccp(32-240+55*2.f, n_cardsetting->getContentSize().height/2.f+6));//ccp(-7, n_cardsetting->getContentSize().height/2.f));
//	bottom_case->addChild(cardsetting_menu);
	addChild(cardsetting_menu, kMainFlowZorder_uiButton);
	bottom_list.push_back(cardsetting_menu);
	
	cardsetting_menu->setTouchPriority(kCCMenuHandlerPriority-1);
	
//	{
//		CCSprite* t_bar = CCSprite::create("mainflow_bottom_case_bar.png");
//		t_bar->setPosition(ccp(43-240+214.f/8.f*5.f, n_rank->getContentSize().height/2.f-4));
//		bottom_case->addChild(t_bar, -1);
//	}
	
	
	CCSprite* n_mission = CCSprite::create("mainflow_mission.png");
	KSLabelTTF* n_mission_label = KSLabelTTF::create(myLoc->getLocalForKey(kMyLocalKey_todaymission), mySGD->getFont().c_str(), 10);
	n_mission_label->enableOuterStroke(ccBLACK, 1.f);
	n_mission_label->setPosition(ccp(n_mission->getContentSize().width/2.f, 7));
	n_mission->addChild(n_mission_label);
	CCSprite* s_mission = CCSprite::create("mainflow_mission.png");
	s_mission->setColor(ccGRAY);
	KSLabelTTF* s_mission_label = KSLabelTTF::create(myLoc->getLocalForKey(kMyLocalKey_todaymission), mySGD->getFont().c_str(), 10);
	s_mission_label->enableOuterStroke(ccBLACK, 1.f);
	s_mission_label->setPosition(ccp(s_mission->getContentSize().width/2.f, 7));
	s_mission->addChild(s_mission_label);
	
	
	if(mySGD->today_mission_info.goal_count.getV() != 0)
	{
		float t_percent = 100.f*mySGD->today_mission_info.ing_count.getV()/mySGD->today_mission_info.goal_count.getV();
		if(t_percent < 100.f)
		{
			CCScale9Sprite* n_percent_back = CCScale9Sprite::create("mainflow_new2.png", CCRectMake(0, 0, 20, 20), CCRectMake(9, 9, 2, 2));
			n_percent_back->setPosition(ccp(n_mission->getContentSize().width-8, n_mission->getContentSize().height-n_percent_back->getContentSize().height));
			n_mission->addChild(n_percent_back);
			
			CCLabelTTF* n_percent_label = CCLabelTTF::create(CCString::createWithFormat("%.0f%%", t_percent)->getCString(), mySGD->getFont().c_str(), 8);
			n_percent_back->setContentSize(CCSizeMake(15+n_percent_label->getContentSize().width, 20));
			n_percent_label->setPosition(ccp(n_percent_back->getContentSize().width/2.f, n_percent_back->getContentSize().height/2.f));
			n_percent_back->addChild(n_percent_label);
			
			CCScale9Sprite* s_percent_back = CCScale9Sprite::create("mainflow_new2.png", CCRectMake(0, 0, 20, 20), CCRectMake(9, 9, 2, 2));
			s_percent_back->setPosition(ccp(s_mission->getContentSize().width-8, s_mission->getContentSize().height-s_percent_back->getContentSize().height));
			s_mission->addChild(s_percent_back);
			
			CCLabelTTF* s_percent_label = CCLabelTTF::create(CCString::createWithFormat("%.0f%%", t_percent)->getCString(), mySGD->getFont().c_str(), 8);
			s_percent_back->setContentSize(CCSizeMake(15+s_percent_label->getContentSize().width, 20));
			s_percent_label->setPosition(ccp(s_percent_back->getContentSize().width/2.f, s_percent_back->getContentSize().height/2.f));
			s_percent_back->addChild(s_percent_label);
		}
	}
	
	CCMenuItem* mission_item = CCMenuItemSprite::create(n_mission, s_mission, this, menu_selector(MainFlowScene::menuAction));
	mission_item->setTag(kMainFlowMenuTag_mission);
	
	CCMenu* mission_menu = CCMenu::createWithItem(mission_item);
	mission_menu->setPosition(ccp(240,-(myDSH->puzzle_ui_top-320.f)/2.f+10) + ccp(32-240+55*3.f, n_mission->getContentSize().height/2.f+6));
//	bottom_case->addChild(mission_menu);
	addChild(mission_menu, kMainFlowZorder_uiButton);
	bottom_list.push_back(mission_menu);
	
	mission_menu->setTouchPriority(kCCMenuHandlerPriority-1);

	
	
	Json::Value v = mySGD->cgp_data;
//	Json::Reader r;
//	r.parse(R"( {"buttonurl":"http://images.hangame.co.kr/mobile/cgp/2012.10/cgp_icon_wooproo.png","eventurl":"","typecode":1,"promotionstate":"CGP_PROMOTION_EXISTS","bubbletext":""} )",
//					v);
	std::string pState = v["promotionstate"].asString();
	
	// 아무것도 하지마!!
	if(pState == "CGP_NONE")
	{
		/* 출력값
		 {
		 "callback" : null,
		 "param" : null,
		 "promotionstate" : "CGP_NONE"
		 }
		 
		 */
	}
	// 홍보해야 될 것이 존재
	else if(pState == "CGP_PROMOTION_EXISTS")
	{
		/* 출력값
		 {
		 "bubbletext" : "",
		 "buttonurl" : "http://images.hangame.co.kr/mobile/cgp/10150_wara/wara_cgp.png",
		 "callback" : null,
		 "eventurl" : "",
		 "param" : null,
		 "promotionstate" : "CGP_PROMOTION_EXISTS",
		 "typecode" : 1
		 }
		 
		 */
		
		CCSprite* n_cgp = GDWebSprite::create(v["buttonurl"].asString(), "mainflow_event.png");
		KSLabelTTF* n_cgp_label = KSLabelTTF::create(myLoc->getLocalForKey(kMyLocalKey_event), mySGD->getFont().c_str(), 12);
		n_cgp_label->enableOuterStroke(ccBLACK, 1.f);
		n_cgp_label->setPosition(ccp(n_cgp->getContentSize().width/2.f, 15));
		n_cgp->addChild(n_cgp_label);
		
		CCSprite* s_cgp = GDWebSprite::create(v["buttonurl"].asString(), "mainflow_event.png");
		s_cgp->setColor(ccGRAY);
		KSLabelTTF* s_cgp_label = KSLabelTTF::create(myLoc->getLocalForKey(kMyLocalKey_event), mySGD->getFont().c_str(), 12);
		s_cgp_label->enableOuterStroke(ccBLACK, 1.f);
		s_cgp_label->setPosition(ccp(s_cgp->getContentSize().width/2.f, 15));
		s_cgp->addChild(s_cgp_label);
		
		CCMenuLambda* cgp_menu = CCMenuLambda::create();
		cgp_menu->setPosition(ccp(240,-(myDSH->puzzle_ui_top-320.f)/2.f+10) + ccp(32-240+55*4.f, n_cgp->getContentSize().height/2.f+6));
		//		etc_frame->addChild(cgp_menu);
		addChild(cgp_menu, kMainFlowZorder_uiButton);
		bottom_list.push_back(cgp_menu);
		
		cgp_menu->setTouchPriority(kCCMenuHandlerPriority-1);
		
		CCMenuItemLambda* cgp_item = CCMenuItemSpriteLambda::create(n_cgp, s_cgp, [=](CCObject* sender){
			if(cgp_item->isEnabled() == false)
				return;
			cgp_item->setEnabled(false);
			hspConnector::get()->launchPromotion();
			
			auto iter = find(bottom_list.begin(), bottom_list.end(), cgp_menu);
			if(iter != bottom_list.end())
			{
				bottom_list.erase(iter);
			}
			
			cgp_menu->removeFromParent();
//			CCSprite* n_etc_img = CCSprite::create("mainflow_etc_event.png");
//			KSLabelTTF* n_etc_label = KSLabelTTF::create(myLoc->getLocalForKey(kMyLocalKey_event), mySGD->getFont().c_str(), 12);
//			n_etc_label->enableOuterStroke(ccBLACK, 1.f);
//			n_etc_label->setPosition(ccp(n_etc_img->getContentSize().width/2.f, 7));
//			n_etc_img->addChild(n_etc_label);
//			
//			//			KSLabelTTF* n_event_ment = KSLabelTTF::create(mySGD->getEventString().c_str(), mySGD->getFont().c_str(), 12);
//			auto tt = mySGD->getEventString().c_str();
//			
//			KSLabelTTF* n_event_ment = KSLabelTTF::create(tt, mySGD->getFont().c_str(), 12);
//			n_event_ment->setPosition(ccpFromSize(n_etc_img->getContentSize())/2.f + ccp(0,15));
//			n_etc_img->addChild(n_event_ment);
//			
//			CCSprite* s_etc_img = CCSprite::create("mainflow_etc_event.png");
//			s_etc_img->setColor(ccGRAY);
//			KSLabelTTF* s_etc_label = KSLabelTTF::create(myLoc->getLocalForKey(kMyLocalKey_event), mySGD->getFont().c_str(), 12);
//			s_etc_label->enableOuterStroke(ccBLACK, 1.f);
//			s_etc_label->setPosition(ccp(s_etc_img->getContentSize().width/2.f, 7));
//			s_etc_img->addChild(s_etc_label);
//			KSLabelTTF* s_event_ment = KSLabelTTF::create(mySGD->getEventString().c_str(), mySGD->getFont().c_str(), 12);
//			s_event_ment->setPosition(ccpFromSize(s_etc_img->getContentSize())/2.f + ccp(0,15));
//			s_etc_img->addChild(s_event_ment);
//			
//			CCMenuItemLambda* etc_item = CCMenuItemSpriteLambda::create(n_etc_img, s_etc_img, [=](CCObject* sender){
//				if(!is_menu_enable)
//					return;
//				
//				is_menu_enable = false;
//				
//				int puzzle_number = mySGD->getSpecialEventPuzzleNumber();
//				myDSH->setIntegerForKey(kDSH_Key_selectedPuzzleNumber, puzzle_number);
//				
//				StageListDown* t_sld = StageListDown::create(this, callfunc_selector(MainFlowScene::basicEnter), puzzle_number, [=](function<void()> t_func)
//															 {
//																 mySGD->is_before_stage_img_download = true;
//																 topOuting();
//																 bottomPuzzleMode();
//																 tableDownloading(t_func);
//															 }, [=](){puzzleLoadSuccess();});
//				addChild(t_sld, kMainFlowZorder_popup);
//			});
//			
//			cgp_menu->addChild(etc_item);
//			CCArray* t_menu_array = cgp_menu->getChildren();
//			int array_cnt = cgp_menu->getChildrenCount();
//			bool is_removed = false;
//			for(int i=0;!is_removed && i<array_cnt;i++)
//			{
//				CCMenuItemLambda* t_lambda_item = ((CCMenuItemLambda*)t_menu_array->objectAtIndex(i));
//				if(t_lambda_item == etc_item)
//					continue;
//				else
//				{
//					is_removed = true;
//					t_lambda_item->removeFromParent();
//					break;
//				}
//			}
		});
		
		cgp_menu->addChild(cgp_item);
	}
	// 일반 보상
	else if(pState == "CGP_REWARD_REQUIRED")
	{
		/* 출력값
		 {
		 "callback" : null,
		 "param" : null,
		 "promotionstate" : "CGP_REWARD_REQUIRED",
		 "rewards" :
		 [
		 {
		 "promotiontype" : 2,
		 "rewardcode" : "10289_test",
		 "rewardvalue" : 1
		 }
		 ]
		 }
		 */
		
		ASPopupView* t_popup = ASPopupView::create(-999);
		
		CCSize screen_size = CCEGLView::sharedOpenGLView()->getFrameSize();
		float screen_scale_x = screen_size.width/screen_size.height/1.5f;
		if(screen_scale_x < 1.f)
			screen_scale_x = 1.f;
		float height_value = 320.f;
		if(myDSH->screen_convert_rate < 1.f)
			height_value = 320.f/myDSH->screen_convert_rate;
		
		if(height_value < myDSH->ui_top)
			height_value = myDSH->ui_top;
		
		t_popup->setDimmedSize(CCSizeMake(screen_scale_x*480.f, height_value));// /myDSH->screen_convert_rate));
		t_popup->setDimmedPosition(ccp(240, 160));
		
		CCNode* t_container = CCNode::create();
		t_popup->setContainerNode(t_container);
		addChild(t_popup, kMainFlowZorder_popup);
		
		t_popup->setBasePosition(ccp(240, 160));
		
		CCScale9Sprite* back_case = CCScale9Sprite::create("subpop_back.png", CCRectMake(0,0,100,100), CCRectMake(49,49,2,2));
		back_case->setContentSize(CCSizeMake(350,280));
		back_case->setPosition(ccp(0,0));
		t_container->addChild(back_case);
		
		KSLabelTTF* title_label = KSLabelTTF::create(myLoc->getLocalForKey(kMyLocalKey_cgpNormalTitle), mySGD->getFont().c_str(), 16);;
		title_label->setPosition(ccp(0,100));
		t_container->addChild(title_label);
		
		KSLabelTTF* ment_label = KSLabelTTF::create(myLoc->getLocalForKey(kMyLocalKey_cgpNormalContent), mySGD->getFont().c_str(), 12);
		ment_label->setPosition(ccp(0,0));
		t_container->addChild(ment_label);
		
		CCLabelTTF* t_label = CCLabelTTF::create();
		KSLabelTTF* take_label = KSLabelTTF::create(myLoc->getLocalForKey(kMyLocalKey_getReward), mySGD->getFont().c_str(), 13);
		take_label->setPosition(ccp(0,0));
		t_label->addChild(take_label);
		
		CCScale9Sprite* take_back = CCScale9Sprite::create("subpop_red.png", CCRectMake(0,0,34,34), CCRectMake(16, 16, 2, 2));
		
		CCControlButton* take_button = CCControlButton::create(t_label, take_back);
		take_button->addTargetWithActionForControlEvents(this, cccontrol_selector(MainFlowScene::cgpReward), CCControlEventTouchUpInside);
		take_button->setPreferredSize(CCSizeMake(150,65));
		take_button->setPosition(ccp(0,-85));
		t_container->addChild(take_button);
		
		take_button->setTouchPriority(t_popup->getTouchPriority()-5);
		
		CommonAnimation::openPopup(this, t_container, nullptr, [=](){
			
		}, [=](){
		});
	}
	// 전체 팝업보상
	else if(pState == "CGP_PROMOTION_REWARD_EXISTS")
	{
		ASPopupView* t_popup = ASPopupView::create(-999);
		
		CCSize screen_size = CCEGLView::sharedOpenGLView()->getFrameSize();
		float screen_scale_x = screen_size.width/screen_size.height/1.5f;
		if(screen_scale_x < 1.f)
			screen_scale_x = 1.f;
		float height_value = 320.f;
		if(myDSH->screen_convert_rate < 1.f)
			height_value = 320.f/myDSH->screen_convert_rate;
		
		if(height_value < myDSH->ui_top)
			height_value = myDSH->ui_top;
		
		t_popup->setDimmedSize(CCSizeMake(screen_scale_x*480.f, height_value));// /myDSH->screen_convert_rate));
		t_popup->setDimmedPosition(ccp(240, 160));
		
		CCNode* t_container = CCNode::create();
		t_popup->setContainerNode(t_container);
		addChild(t_popup, kMainFlowZorder_popup);
		
		t_popup->setBasePosition(ccp(240, 160));
		
		CCScale9Sprite* back_case = CCScale9Sprite::create("subpop_back.png", CCRectMake(0,0,100,100), CCRectMake(49,49,2,2));
		back_case->setContentSize(CCSizeMake(350,280));
		back_case->setPosition(ccp(0,0));
		t_container->addChild(back_case);
		
		KSLabelTTF* title_label = KSLabelTTF::create(myLoc->getLocalForKey(kMyLocalKey_cgpAllPopupTitle), mySGD->getFont().c_str(), 16);;
		title_label->setPosition(ccp(0,100));
		t_container->addChild(title_label);
		
		KSLabelTTF* ment_label = KSLabelTTF::create(myLoc->getLocalForKey(kMyLocalKey_cgpNormalContent), mySGD->getFont().c_str(), 12);
		ment_label->setPosition(ccp(0,0));
		t_container->addChild(ment_label);
		
		CCLabelTTF* t_label = CCLabelTTF::create();
		KSLabelTTF* take_label = KSLabelTTF::create(myLoc->getLocalForKey(kMyLocalKey_getReward), mySGD->getFont().c_str(), 13);
		take_label->setPosition(ccp(0,0));
		t_label->addChild(take_label);
		
		CCScale9Sprite* take_back = CCScale9Sprite::create("subpop_red.png", CCRectMake(0,0,34,34), CCRectMake(16, 16, 2, 2));
		
		CCControlButton* take_button = CCControlButton::create(t_label, take_back);
		take_button->addTargetWithActionForControlEvents(this, cccontrol_selector(MainFlowScene::cgpAllReward), CCControlEventTouchUpInside);
		take_button->setPreferredSize(CCSizeMake(150,65));
		take_button->setPosition(ccp(0,-85));
		t_container->addChild(take_button);
		
		take_button->setTouchPriority(t_popup->getTouchPriority()-5);
		
		CommonAnimation::openPopup(this, t_container, nullptr, [=](){
			
		}, [=](){
		});
	}
	
	
//	CCSprite* t_bar = CCSprite::create("mainflow_bottom_case_bar.png");
//	t_bar->setPosition(ccp(43-240+214.f/8.f*7.f, n_rank->getContentSize().height/2.f-4));
//	bottom_case->addChild(t_bar, -1);
	
	int puzzle_number = mySGD->getSpecialEventPuzzleNumber();
	int menuoffset = 0;
	if(!puzzle_number){
		menuoffset += 174/2.f;
	}
	
	
	GraySprite* n_endless = GraySprite::create("mainflow_endless.png");
//	KSLabelTTF* n_endless_label = KSLabelTTF::create(myLoc->getLocalForKey(kMyLocalKey_endlessMode), mySGD->getFont().c_str(), 12);
//	n_endless_label->enableOuterStroke(ccBLACK, 1.f);
//	n_endless_label->setPosition(ccp(n_endless->getContentSize().width/2.f, 7));
//	n_endless->addChild(n_endless_label);
	GraySprite* s_endless = GraySprite::create("mainflow_endless.png");
	s_endless->setColor(ccGRAY);
//	KSLabelTTF* s_endless_label = KSLabelTTF::create(myLoc->getLocalForKey(kMyLocalKey_endlessMode), mySGD->getFont().c_str(), 12);
//	s_endless_label->enableOuterStroke(ccBLACK, 1.f);
//	s_endless_label->setPosition(ccp(s_endless->getContentSize().width/2.f, 7));
//	s_endless->addChild(s_endless_label);
	
	CCMenuItem* endless_item = CCMenuItemSprite::create(n_endless, s_endless, this, menu_selector(MainFlowScene::menuAction));
	endless_item->setTag(kMainFlowMenuTag_endlessMode);
	
	CCMenu* endless_menu = CCMenu::createWithItem(endless_item);
	endless_menu->setPosition(ccp(240,-(myDSH->puzzle_ui_top-320.f)/2.f+10) + ccp(52-240+290.f, n_endless->getContentSize().height/2.f+3));
//	bottom_case->addChild(endless_menu);
	addChild(endless_menu, kMainFlowZorder_uiButton2);
	bottom_list.push_back(endless_menu);
	
	endless_menu->setTouchPriority(kCCMenuHandlerPriority-1);
	
	if(mySGD->getUserdataHighPiece() < mySGD->getEndlessMinPiece())
	{
		n_endless->setGray(true);
		s_endless->setColor(ccc3(50, 50, 50));
	}
	else
	{
		if(mySGD->getUserdataEndlessIngWeek() != mySGD->recent_week_no.getV())
		{
			n_endless->runAction(CCRepeatForever::create(CCSequence::create(CCShow::create(), CCDelayTime::create(0.3f), CCHide::create(), CCDelayTime::create(0.3f), NULL)));
		}
		else
		{
			int ing_win;
			ing_win = mySGD->endless_my_victory.getV();
			if(ing_win > 0)
			{
				CCScale9Sprite* n_win_back = CCScale9Sprite::create("mainflow_new3.png", CCRectMake(0, 0, 60, 20), CCRectMake(29, 9, 2, 2));
				n_endless->addChild(n_win_back);
				
				KSLabelTTF* n_win_label = KSLabelTTF::create(CCString::createWithFormat(myLoc->getLocalForKey(kMyLocalKey_endlessIngWin), ing_win)->getCString(), mySGD->getFont().c_str(), 9.5f);
				n_win_label->enableOuterStroke(ccBLACK, 1, int(255*0.5), true);
				n_win_back->addChild(n_win_label);
				
//				n_win_back->setContentSize(CCSizeMake(15+n_win_label->getContentSize().width, 20));
				n_win_back->setPosition(ccp(n_endless->getContentSize().width-30, n_endless->getContentSize().height-n_win_back->getContentSize().height+13));
				n_win_label->setPosition(ccp(n_win_back->getContentSize().width/2.f, n_win_back->getContentSize().height/2.f) + ccp(0,1));
				
				CCScale9Sprite* s_win_back = CCScale9Sprite::create("mainflow_new3.png", CCRectMake(0, 0, 60, 20), CCRectMake(29, 9, 2, 2));
				s_endless->addChild(s_win_back);
				
				KSLabelTTF* s_win_label = KSLabelTTF::create(CCString::createWithFormat(myLoc->getLocalForKey(kMyLocalKey_endlessIngWin), ing_win)->getCString(), mySGD->getFont().c_str(), 9.5f);
				s_win_label->enableOuterStroke(ccBLACK, 1, int(255*0.5), true);
				s_win_back->addChild(s_win_label);
				
//				s_win_back->setContentSize(CCSizeMake(15+s_win_label->getContentSize().width, 20));
				s_win_back->setPosition(ccp(s_endless->getContentSize().width-30, s_endless->getContentSize().height-s_win_back->getContentSize().height+13));
				s_win_label->setPosition(ccp(s_win_back->getContentSize().width/2.f, s_win_back->getContentSize().height/2.f) + ccp(0,1));
				
				refresh_ing_win_func = [=]()
				{
					if(mySGD->endless_my_victory.getV() > 0)
					{
						n_win_label->setString(CCString::createWithFormat(myLoc->getLocalForKey(kMyLocalKey_endlessIngWin), mySGD->endless_my_victory.getV())->getCString());
						s_win_label->setString(CCString::createWithFormat(myLoc->getLocalForKey(kMyLocalKey_endlessIngWin), mySGD->endless_my_victory.getV())->getCString());
					}
					else
					{
						n_win_back->removeFromParent();
						s_win_back->removeFromParent();
						refresh_ing_win_func = nullptr;
					}
				};
			}
			else
			{
				refresh_ing_win_func = [=]()
				{
					if(mySGD->endless_my_victory.getV() > 0)
					{
						CCScale9Sprite* n_win_back = CCScale9Sprite::create("mainflow_new3.png", CCRectMake(0, 0, 60, 20), CCRectMake(29, 9, 2, 2));
						n_endless->addChild(n_win_back);
						
						KSLabelTTF* n_win_label = KSLabelTTF::create(CCString::createWithFormat(myLoc->getLocalForKey(kMyLocalKey_endlessIngWin), mySGD->endless_my_victory.getV())->getCString(), mySGD->getFont().c_str(), 9.5f);
						n_win_label->enableOuterStroke(ccBLACK, 1, int(255*0.5), true);
						n_win_back->addChild(n_win_label);
						
//						n_win_back->setContentSize(CCSizeMake(15+n_win_label->getContentSize().width, 20));
						n_win_back->setPosition(ccp(n_endless->getContentSize().width-30, n_endless->getContentSize().height-n_win_back->getContentSize().height+13));
						n_win_label->setPosition(ccp(n_win_back->getContentSize().width/2.f, n_win_back->getContentSize().height/2.f) + ccp(0,1));
						
						CCScale9Sprite* s_win_back = CCScale9Sprite::create("mainflow_new3.png", CCRectMake(0, 0, 60, 20), CCRectMake(29, 9, 2, 2));
						s_endless->addChild(s_win_back);
						
						KSLabelTTF* s_win_label = KSLabelTTF::create(CCString::createWithFormat(myLoc->getLocalForKey(kMyLocalKey_endlessIngWin), mySGD->endless_my_victory.getV())->getCString(), mySGD->getFont().c_str(), 9.5f);
						s_win_label->enableOuterStroke(ccBLACK, 1, int(255*0.5), true);
						s_win_back->addChild(s_win_label);
						
//						s_win_back->setContentSize(CCSizeMake(15+s_win_label->getContentSize().width, 20));
						s_win_back->setPosition(ccp(s_endless->getContentSize().width-30, s_endless->getContentSize().height-s_win_back->getContentSize().height+13));
						s_win_label->setPosition(ccp(s_win_back->getContentSize().width/2.f, s_win_back->getContentSize().height/2.f) + ccp(0,1));
					}
				};
			}
		}
	}
	
	
//	CCSprite* left_back = CCSprite::create("mainflow_bottom_case_left.png");
//	left_back->setPosition(ccp(39-240,left_back->getContentSize().height/2.f));
//	bottom_case->addChild(left_back, -1);
//	
//	CCSprite* right_back = CCSprite::create("mainflow_bottom_case_right.png");
//	right_back->setPosition(ccp(262-240,right_back->getContentSize().height/2.f));
//	bottom_case->addChild(right_back, -1);
//	
//	CCSprite* center_back = CCSprite::create("mainflow_bottom_case_center.png");
//	center_back->setAnchorPoint(ccp(0,0.5));
//	center_back->setPosition(ccp(39-240+left_back->getContentSize().width/2.f,center_back->getContentSize().height/2.f));
//	bottom_case->addChild(center_back, -1);
	
	
//	CCSprite* etc_frame = CCSprite::create("mainflow_event_frame.png");
//	etc_frame->setAnchorPoint(ccp(0.5,0));
//	etc_frame->setPosition(ccp(385,-(myDSH->puzzle_ui_top-320.f)/2.f+11));
//	addChild(etc_frame, kMainFlowZorder_uiButton);
//	
//	KSLabelTTF* event_ment = KSLabelTTF::create(mySGD->getEventString().c_str(), mySGD->getFont().c_str(), 12);
//	event_ment->setPosition(ccpFromSize(etc_frame->getContentSize())/2.f + ccp(18,-3));
//	etc_frame->addChild(event_ment);
//
//	bottom_list.push_back(etc_frame);
	
	
	

	CCSprite* n_etc_img = GraySprite::create("mainflow_etc_event.png");
	((GraySprite*)n_etc_img)->setGray(!puzzle_number);
	
	CCSprite* n_event_ment_case = CCSprite::create("puzzle_event.png");
	n_event_ment_case->setPosition(ccpFromSize(n_etc_img->getContentSize())/2.f + ccp(n_etc_img->getContentSize().width/2.f-n_event_ment_case->getContentSize().width/2.f,18));
	n_etc_img->addChild(n_event_ment_case);
	
	if(puzzle_number)
	{
		KSLabelTTF* n_event_ment = KSLabelTTF::create(mySGD->getEventString().c_str(), mySGD->getFont().c_str(), 10);
		n_event_ment->setPosition(ccpFromSize(n_etc_img->getContentSize())/2.f);
		n_event_ment_case->addChild(n_event_ment);
	}
	
	
	CCSprite* s_etc_img = GraySprite::create("mainflow_etc_event.png");
	if(puzzle_number)
		s_etc_img->setColor(ccGRAY);
	else
		((GraySprite*)s_etc_img)->setDeepGray(!puzzle_number);
	
	CCSprite* s_event_ment_case = CCSprite::create("puzzle_event.png");
	s_event_ment_case->setPosition(ccpFromSize(s_etc_img->getContentSize())/2.f + ccp(s_etc_img->getContentSize().width/2.f-s_event_ment_case->getContentSize().width/2.f,18));
	s_etc_img->addChild(s_event_ment_case);
	
	if(puzzle_number)
	{
		KSLabelTTF* s_event_ment = KSLabelTTF::create(mySGD->getEventString().c_str(), mySGD->getFont().c_str(), 10);
		s_event_ment->setPosition(ccpFromSize(s_etc_img->getContentSize())/2.f);
		s_event_ment_case->addChild(s_event_ment);
	}
	
	
	CCMenuLambda* etc_menu = CCMenuLambda::create();
	etc_menu->setPosition(ccp(385,-(myDSH->puzzle_ui_top-320.f)/2.f+10) + ccp(43-240+240.f, n_etc_img->getContentSize().height/2.f+3));
	//		etc_frame->addChild(etc_menu);
	addChild(etc_menu, kMainFlowZorder_uiButton);
	bottom_list.push_back(etc_menu);
	
	etc_menu->setTouchPriority(kCCMenuHandlerPriority-1);
	
	CCMenuItemLambda* etc_item = CCMenuItemSpriteLambda::create(n_etc_img, s_etc_img, [=](CCObject* sender){
		if(!is_menu_enable)
			return;
		
		is_menu_enable = false;
		
		addChild(ASPopupView::getCommonNoti(-9999, myLoc->getLocalForKey(kMyLocalKey_noti), myLoc->getLocalForKey(kMyLocalKey_afterOpenCBT), [=](){is_menu_enable = true;}), 9999);
		
		
//			myDSH->setIntegerForKey(kDSH_Key_selectedPuzzleNumber, puzzle_number);
//
//			StageListDown* t_sld = StageListDown::create(this, callfunc_selector(MainFlowScene::basicEnter), puzzle_number, [=](function<void()> t_func)
//														 {
//															 mySGD->is_before_stage_img_download = true;
//															 topOuting();
//															 bottomPuzzleMode();
//															 tableDownloading(t_func);
//														 }, [=](){puzzleLoadSuccess();});
//			addChild(t_sld, kMainFlowZorder_popup);
	});
	
	etc_menu->addChild(etc_item);
}

void MainFlowScene::cgpReward(CCObject* sender, CCControlEvent t_event)
{
	AudioEngine::sharedInstance()->playEffect("se_button1.mp3", false);
	
	Json::Value v = mySGD->cgp_data;
	
	Json::Value rewards = v["rewards"];
	for(int i=0; i<rewards.size(); i++)
	{
		int rewardValue = rewards[i]["rewardvalue"].asInt();
		CCLOG("reward !!! : %d", rewardValue);
	}
	
	LoadingLayer* t_loading = LoadingLayer::create(-9999);
	addChild(t_loading, 9999);
	
	mySGD->addChangeGoods("cgp_n");
	mySGD->changeGoods([=](Json::Value result_data){
		t_loading->removeFromParent();
		if(result_data["result"]["code"].asInt() == GDSUCCESS)
		{
			hspConnector::get()->completePromotion();
			
			AudioEngine::sharedInstance()->playEffect("se_buy.mp3", false);
			
			mySGD->cgp_data.clear();
			mySGD->cgp_data["promotionstate"] = "CGP_NONE";
			
			((CCNode*)sender)->getParent()->getParent()->removeFromParent();
		}
		else
		{
			
		}
	});
}

void MainFlowScene::cgpAllReward(CCObject* sender, CCControlEvent t_event)
{
	AudioEngine::sharedInstance()->playEffect("se_button1.mp3", false);
	
	Json::Value v = mySGD->cgp_data;
	
	Json::Value rewards = v["rewards"];
	for(int i=0; i<rewards.size(); i++)
	{
		int rewardValue = rewards[i]["rewardvalue"].asInt();
		CCLOG("reward !!! : %d", rewardValue);
	}
	
	LoadingLayer* t_loading = LoadingLayer::create(-9999);
	addChild(t_loading, 9999);
	
	mySGD->addChangeGoods("cgp_ap");
	mySGD->changeGoods([=](Json::Value result_data){
		t_loading->removeFromParent();
		if(result_data["result"]["code"].asInt() == GDSUCCESS)
		{
			hspConnector::get()->completeInstallPromotion();
			
			AudioEngine::sharedInstance()->playEffect("se_buy.mp3", false);
			
			mySGD->cgp_data.clear();
			mySGD->cgp_data["promotionstate"] = "CGP_NONE";
			
			((CCNode*)sender)->getParent()->getParent()->removeFromParent();
		}
		else
		{
			
		}
	});
}

void MainFlowScene::heartRefresh()
{
	CCPoint heart_position = heart_time->getPosition();
	CCNode* heart_parent = heart_time->getParent();
	
	heart_time->removeFromParent();
	
	heart_time = HeartTime::create();
	heart_time->setPosition(heart_position);
	heart_parent->addChild(heart_time);
}

void MainFlowScene::topOpenning()
{
	for(int i=0;i<top_list.size();i++)
	{
		CCPoint original_position = top_list[i]->getPosition();
		top_list[i]->setPositionY(original_position.y+200);
		if(i == 0)
		{
			top_list[i]->addChild(KSGradualValue<float>::create(1.f, 0.f, 0.2f, [=](float t)
																{
																	top_list[i]->setPositionY(original_position.y+200.f*t);
																}, [=](float t)
																{
																	top_list[i]->setPositionY(original_position.y);
																}));
		}
		else
		{
			CCDelayTime* t_delay = CCDelayTime::create(i*0.1f);
			CCMoveTo* t_move = CCMoveTo::create(0.2f, original_position);
			CCSequence* t_seq = CCSequence::create(t_delay, t_move, NULL);
			
			top_list[i]->runAction(t_seq);
		}
	}
	
	CCDelayTime* t_delay = CCDelayTime::create(top_list.size()*0.1f + 0.1f);
	CCCallFunc* t_call = CCCallFunc::create(this, callfunc_selector(MainFlowScene::topOnLight));
	CCSequence* t_seq = CCSequence::create(t_delay, t_call, NULL);
	runAction(t_seq);
}

void MainFlowScene::topOnLight()
{
	GoodsLight* gold_light = GoodsLight::create(CCSprite::create("price_gold_img_mask.png"));
	gold_light->setPosition(ccp(gold_img->getContentSize().width/2.f, gold_img->getContentSize().height/2.f));
	gold_img->addChild(gold_light);
	
	GoodsLight* ruby_light = GoodsLight::create(CCSprite::create("price_ruby_img_mask.png"));
	ruby_light->setPosition(ccp(ruby_img->getContentSize().width/2.f, ruby_img->getContentSize().height/2.f));
	ruby_img->addChild(ruby_light);
	
	
	function<void()> pvp_tutorial = [=]()
	{
		myDSH->setIntegerForKey(kDSH_Key_isShowEndlessModeTutorial, 1);
		
		CCNode* scenario_node = CCNode::create();
		addChild(scenario_node, 9999);
		
		CCSize screen_size = CCEGLView::sharedOpenGLView()->getFrameSize();
		float screen_scale_x = screen_size.width/screen_size.height/1.5f;
		if(screen_scale_x < 1.f)
			screen_scale_x = 1.f;
		
		float screen_scale_y = myDSH->ui_top/320.f/myDSH->screen_convert_rate;
		
		
		CCNode* t_stencil_node = CCNode::create();
		
		
		CCClippingNode* t_clipping = CCClippingNode::create(t_stencil_node);
		t_clipping->setAlphaThreshold(0.1f);
		
		float change_scale = 1.f;
		CCPoint change_origin = ccp(0,0);
		if(screen_scale_x > 1.f)
		{
			change_origin.x = -(screen_scale_x-1.f)*480.f/2.f;
			change_scale = screen_scale_x;
		}
		if(screen_scale_y > 1.f)
			change_origin.y = -(screen_scale_y-1.f)*320.f/2.f;
		CCSize win_size = CCDirector::sharedDirector()->getWinSize();
		t_clipping->setRectYH(CCRectMake(change_origin.x, change_origin.y, win_size.width*change_scale, win_size.height*change_scale));
		
		
		CCSprite* t_gray = CCSprite::create("back_gray.png");
		t_gray->setScaleX(screen_scale_x);
		t_gray->setScaleY(myDSH->ui_top/myDSH->screen_convert_rate/320.f);
		t_gray->setOpacity(0);
		t_gray->setPosition(ccp(240,160));
		t_clipping->addChild(t_gray);
		
		t_clipping->setInverted(true);
		scenario_node->addChild(t_clipping, 0);
		
		
		CCSprite* ikaruga = CCSprite::create("kt_cha_ikaruga_1.png");
		ikaruga->setAnchorPoint(ccp(0,0));
		ikaruga->setPosition(ccp(240-240*screen_scale_x-ikaruga->getContentSize().width, 160-160*screen_scale_y));
		scenario_node->addChild(ikaruga, 1);
		
		TypingBox* typing_box = TypingBox::create(-9999, "kt_talkbox_purple_right.png", CCRectMake(0, 0, 85, 115), CCRectMake(40, 76, 23, 14), CCRectMake(40, 26, 23, 64), CCSizeMake(210, 60), ccp(241, 78));
		typing_box->setHide();
		scenario_node->addChild(typing_box, 2);
		
		CCSprite* n_skip = CCSprite::create("kt_skip.png");
		CCSprite* s_skip = CCSprite::create("kt_skip.png");
		s_skip->setColor(ccGRAY);
		
		CCMenuLambda* skip_menu = CCMenuLambda::create();
		skip_menu->setPosition(ccp(240-240*screen_scale_x + 35, 160+160*screen_scale_y - 25 + 150));
		scenario_node->addChild(skip_menu, 3);
		skip_menu->setTouchPriority(-19999);
		skip_menu->setEnabled(false);
		
		CCMenuItemLambda* skip_item = CCMenuItemSpriteLambda::create(n_skip, s_skip, [=](CCObject* sender)
																	 {
																		 skip_menu->setEnabled(false);
																		 kind_tutorial_pvp = nullptr;
																		 addChild(KSTimer::create(0.1f, [=]()
																								  {
//																									  is_menu_enable = true;
																									  showEndlessOpening();
																									  scenario_node->removeFromParent();
																								  }));
																	 });
		skip_menu->addChild(skip_item);
		
		
		typing_box->showAnimation(0.3f);
		
		function<void()> end_func2 = [=]()
		{
			skip_menu->setEnabled(false);
			
			addChild(KSTimer::create(0.1f, [=]()
									 {
//										 is_menu_enable = true;
										 showEndlessOpening();
										 scenario_node->removeFromParent();
									 }));
		};
		
		function<void()> end_func1 = [=]()
		{
			typing_box->setTouchOffScrollAndButton();
			typing_box->setTouchSuction(false);
			typing_box->setVisible(false);
			
			CCSprite* t_arrow1 = CCSprite::create("kt_arrow_big.png");
			t_arrow1->setRotation(-90);
			t_arrow1->setPosition(ccp(240,-(myDSH->puzzle_ui_top-320.f)/2.f+10) + ccp(52-240+290.f, 50/2.f+3) + ccp(0,60));
			scenario_node->addChild(t_arrow1);
			
			CCMoveTo* t_up = CCMoveTo::create(0.4f, t_arrow1->getPosition() + ccp(0,30));
			CCMoveTo* t_down = CCMoveTo::create(0.4f, t_arrow1->getPosition());
			CCSequence* t_seq = CCSequence::create(t_up, t_down, NULL);
			
			CCRepeatForever* t_repeat = CCRepeatForever::create(t_seq);
			
			t_arrow1->runAction(t_repeat);
			
			CCScale9Sprite* t_stencil1 = CCScale9Sprite::create("rank_normal1.png", CCRectMake(0, 0, 31, 31), CCRectMake(15, 15, 1, 1));
			t_stencil1->setContentSize(CCSizeMake(80, 45));
			t_stencil1->setPosition(ccp(240,-(myDSH->puzzle_ui_top-320.f)/2.f+10) + ccp(52-240+290.f, 50/2.f+3));
			t_stencil_node->addChild(t_stencil1);
			
			kind_tutorial_pvp = [=]()
			{
				skip_menu->setEnabled(false);
				addChild(KSTimer::create(0.1f, [=]()
										 {
											 scenario_node->removeFromParent();
										 }));
				kind_tutorial_pvp = nullptr;
			};
			
			TouchSuctionLayer* t_suction = TouchSuctionLayer::create(-9999);
			scenario_node->addChild(t_suction);
			t_suction->setTouchEnabled(true);
			is_menu_enable = true;
			t_suction->setNotSwallowRect(CCRectMake(t_stencil1->getPositionX()-t_stencil1->getContentSize().width/2.f, t_stencil1->getPositionY()-t_stencil1->getContentSize().height/2.f, t_stencil1->getContentSize().width, t_stencil1->getContentSize().height));
			
//			t_suction->touch_began_func = [=]()
//			{
//				skip_menu->setVisible(true);
//				t_suction->is_on_touch_began_func = false;
//				t_stencil_node->removeAllChildren();
//				t_arrow1->removeFromParent();
//				end_func2();
//				t_suction->removeFromParent();
//			};
//			t_suction->is_on_touch_began_func = true;
		};
		
		scenario_node->addChild(KSGradualValue<float>::create(0.f, 1.f, 0.3f, [=](float t)
															  {
																  t_gray->setOpacity(t*255);
																  ikaruga->setPositionX(240-240*screen_scale_x-ikaruga->getContentSize().width + ikaruga->getContentSize().width*2.f/3.f*t);
																  skip_menu->setPositionY(160+160*screen_scale_y - 25 + 150 - 150*t);
															  }, [=](float t)
															  {
																  t_gray->setOpacity(255);
																  ikaruga->setPositionX(240-240*screen_scale_x-ikaruga->getContentSize().width + ikaruga->getContentSize().width*2.f/3.f*t);
																  skip_menu->setPositionY(160+160*screen_scale_y - 25 + 150 - 150*t);
																  skip_menu->setEnabled(true);
																  
																  typing_box->startTyping(myLoc->getLocalForKey(kMyLocalKey_scenarioMent53), end_func1);
															  }));
	};
	
	if(myDSH->getIntegerForKey(kDSH_Key_isShowEndlessModeTutorial) == 0 && mySGD->getUserdataHighPiece() >= mySGD->getEndlessMinPiece())
	{
		mySGD->is_on_attendance = false;
		mySGD->is_on_rank_reward = false;
		mySGD->is_today_mission_first = false;
	}
	
	
	if(myDSH->getIntegerForKey(kDSH_Key_showedScenario) == 0)
	{
		myDSH->setIntegerForKey(kDSH_Key_showedScenario, 1);
		
		mySGD->is_on_attendance = false;
		mySGD->is_on_rank_reward = false;
		mySGD->is_today_mission_first = false;
		
		CCNode* scenario_node = CCNode::create();
		addChild(scenario_node, 9999);
		
		CCSize screen_size = CCEGLView::sharedOpenGLView()->getFrameSize();
		float screen_scale_x = screen_size.width/screen_size.height/1.5f;
		if(screen_scale_x < 1.f)
			screen_scale_x = 1.f;
		
		float screen_scale_y = myDSH->ui_top/320.f/myDSH->screen_convert_rate;
		
		
		CCNode* t_stencil_node = CCNode::create();
		
		
		CCClippingNode* t_clipping = CCClippingNode::create(t_stencil_node);
		t_clipping->setAlphaThreshold(0.1f);
		
		float change_scale = 1.f;
		CCPoint change_origin = ccp(0,0);
		if(screen_scale_x > 1.f)
		{
			change_origin.x = -(screen_scale_x-1.f)*480.f/2.f;
			change_scale = screen_scale_x;
		}
		if(screen_scale_y > 1.f)
			change_origin.y = -(screen_scale_y-1.f)*320.f/2.f;
		CCSize win_size = CCDirector::sharedDirector()->getWinSize();
		t_clipping->setRectYH(CCRectMake(change_origin.x, change_origin.y, win_size.width*change_scale, win_size.height*change_scale));
		
		
		CCSprite* t_gray = CCSprite::create("back_gray.png");
		t_gray->setScaleX(screen_scale_x);
		t_gray->setScaleY(myDSH->ui_top/myDSH->screen_convert_rate/320.f);
		t_gray->setOpacity(0);
		t_gray->setPosition(ccp(240,160));
		t_clipping->addChild(t_gray);
		
		t_clipping->setInverted(true);
		scenario_node->addChild(t_clipping, 0);
		
		
		CCSprite* asuka = CCSprite::create("kt_cha_asuka_1.png");
		asuka->setAnchorPoint(ccp(0,0));
		asuka->setPosition(ccp(240-240*screen_scale_x-asuka->getContentSize().width, 160-160*screen_scale_y));
		scenario_node->addChild(asuka, 1);
		
		CCSprite* ikaruga = CCSprite::create("kt_cha_ikaruga_1.png");
		ikaruga->setAnchorPoint(ccp(1,0));
		ikaruga->setPosition(ccp(240+240*screen_scale_x+ikaruga->getContentSize().width, 160-160*screen_scale_y));
		ikaruga->setVisible(false);
		scenario_node->addChild(ikaruga, 1);
		
		TypingBox* typing_box = TypingBox::create(-9999, "kt_talkbox_purple_right.png", CCRectMake(0, 0, 85, 115), CCRectMake(40, 76, 23, 14), CCRectMake(40, 26, 23, 64), CCSizeMake(210, 60), ccp(241, 78));
		typing_box->setHide();
		scenario_node->addChild(typing_box, 2);
		
		TypingBox* typing_box2 = TypingBox::create(-9999, "kt_talkbox_blue.png", CCRectMake(0, 0, 85, 115), CCRectMake(22, 76, 23, 14), CCRectMake(22, 26, 23, 64), CCSizeMake(210, 60), ccp(239, 96));
		scenario_node->addChild(typing_box2, 2);
		
		CCSprite* n_skip = CCSprite::create("kt_skip.png");
		CCSprite* s_skip = CCSprite::create("kt_skip.png");
		s_skip->setColor(ccGRAY);
		
		CCMenuLambda* skip_menu = CCMenuLambda::create();
		skip_menu->setPosition(ccp(240-240*screen_scale_x + 35, 160+160*screen_scale_y - 25 + 150));
		scenario_node->addChild(skip_menu, 3);
		skip_menu->setTouchPriority(-19999);
		skip_menu->setEnabled(false);
		
		CCMenuItemLambda* skip_item = CCMenuItemSpriteLambda::create(n_skip, s_skip, [=](CCObject* sender)
																	 {
																		 skip_menu->setEnabled(false);
																		 int puzzle_number = 1000-999;
																		 myDSH->setIntegerForKey(kDSH_Key_selectedPuzzleNumber, puzzle_number);
																		 
																		 StageListDown* t_sld = StageListDown::create(this, callfunc_selector(MainFlowScene::basicEnter), puzzle_number, [=](function<void()> t_func)
																													  {
																														  mySGD->is_before_stage_img_download = true;
																														  topOuting();
																														  bottomPuzzleMode();
																														  tableDownloading(t_func);
																													  }, [=](){puzzleLoadSuccess();});
																		 addChild(t_sld, kMainFlowZorder_popup);
																		 
																		 addChild(KSTimer::create(0.1f, [=]()
																								  {
																									  is_menu_enable = true;
																									  scenario_node->removeFromParent();
																								  }));
																	 });
		skip_menu->addChild(skip_item);
		
		
		typing_box2->setTouchOffScrollAndButton();
		typing_box2->setVisible(false);
		typing_box2->setTouchSuction(false);
		
		typing_box->showAnimation(0.3f);
		
		function<void()> end_func13 = [=]()
		{
			skip_menu->setVisible(false);
			
			ikaruga->removeFromParent();
			asuka->removeFromParent();
			typing_box->removeFromParent();
			t_stencil_node->removeAllChildren();
			t_clipping->removeChildByTag(2);
			
			int puzzle_number = 1000-999;
			myDSH->setIntegerForKey(kDSH_Key_selectedPuzzleNumber, puzzle_number);
			
			StageListDown* t_sld = StageListDown::create(this, callfunc_selector(MainFlowScene::basicEnter), puzzle_number, [=](function<void()> t_func)
														 {
															 mySGD->is_before_stage_img_download = true;
															 topOuting();
															 bottomPuzzleMode();
															 tableDownloading(t_func);
														 }, [=](){puzzleLoadSuccess();});
			addChild(t_sld, kMainFlowZorder_popup);
			
			scenario_node->addChild(KSGradualValue<float>::create(0.f, 1.f, 0.3f, [=](float t)
												   {
													   t_gray->setOpacity(255-255*t);
												   }, [=](float t)
												   {
													   t_gray->setOpacity(0);
													   is_menu_enable = true;
													   scenario_node->removeFromParent();
												   }));
			typing_box2->removeFromParent();
		};
		
		function<void()> end_func12 = [=]()
		{
			TypingBox::changeTypingBox(typing_box, typing_box2, asuka, ikaruga);
			typing_box2->startTyping(myLoc->getLocalForKey(kMyLocalKey_scenarioMent12), end_func13);
			
			CCScale9Sprite* t_stencil1 = CCScale9Sprite::create("rank_normal1.png", CCRectMake(0, 0, 31, 31), CCRectMake(15, 15, 1, 1));
			t_stencil1->setContentSize(CCSizeMake(120, 210));
			t_stencil1->setPosition(ccp((-480.f*screen_scale_x+480.f)/2.f + 63,177));
			t_stencil_node->addChild(t_stencil1);
			
			CCSprite* t_arrow1 = CCSprite::create("kt_arrow_big.png");
			t_arrow1->setRotation(0);
			t_arrow1->setPosition(ccp(170,160));
			t_clipping->addChild(t_arrow1, 0, 2);
		};
		
		function<void()> end_func11 = [=]()
		{
			asuka->setVisible(true);
			
			typing_box->setVisible(true);
			typing_box->setTouchSuction(true);
			
			typing_box->startTyping(myLoc->getLocalForKey(kMyLocalKey_scenarioMent11), end_func12);
		};
		
		function<void()> end_func10 = [=]()
		{
			skip_menu->setVisible(false);
			
			ikaruga->setVisible(false);
			
			typing_box2->setTouchOffScrollAndButton();
			typing_box2->setVisible(false);
			
			
			CCSprite* t_arrow1 = CCSprite::create("kt_arrow.png");
			t_arrow1->setRotation(0);
			t_arrow1->setPosition(ccp(26, (myDSH->puzzle_ui_top-320.f)/2.f + 320.f-22 - 40));
			t_clipping->addChild(t_arrow1);
			
			StyledLabelTTF* t_ment2 = StyledLabelTTF::create(myLoc->getLocalForKey(kMyLocalKey_mainflowDimmed2), mySGD->getFont().c_str(), 15, 999, StyledAlignment::kLeftAlignment);
			t_ment2->setAnchorPoint(ccp(0.5f,1));
			t_ment2->setPosition(t_arrow1->getPosition() + ccp(0, -t_arrow1->getContentSize().height/2.f - 3));
			t_clipping->addChild(t_ment2);
			
			
			CCScale9Sprite* t_arrow2 = CCScale9Sprite::create("kt_arrow.png", CCRectMake(0, 0, 20, 24), CCRectMake(7, 16, 6, 1));
			t_arrow2->setContentSize(CCSizeMake(20, 40));
			t_arrow2->setPosition(ccp(374,(myDSH->puzzle_ui_top-320.f)/2.f + 320.f-20 - 43));
			t_clipping->addChild(t_arrow2);
			
			StyledLabelTTF* t_ment3 = StyledLabelTTF::create(myLoc->getLocalForKey(kMyLocalKey_mainflowDimmed3), mySGD->getFont().c_str(), 15, 999, StyledAlignment::kCenterAlignment);
			t_ment3->setAnchorPoint(ccp(0.5f,1));
			t_ment3->setPosition(t_arrow2->getPosition() + ccp(0, -t_arrow2->getContentSize().height/2.f - 3));
			t_clipping->addChild(t_ment3);
			
			
			CCSprite* t_arrow3 = CCSprite::create("kt_arrow.png");
			t_arrow3->setAnchorPoint(ccp(0.5f,1));
			t_arrow3->setPosition(ccp(401,(myDSH->puzzle_ui_top-320.f)/2.f + 320.f-20 - 43 + t_arrow2->getContentSize().height/2.f));
			t_clipping->addChild(t_arrow3);
			
			StyledLabelTTF* t_ment4 = StyledLabelTTF::create(myLoc->getLocalForKey(kMyLocalKey_mainflowDimmed4), mySGD->getFont().c_str(), 15, 999, StyledAlignment::kCenterAlignment);
			t_ment4->setAnchorPoint(ccp(0.5f,1));
			t_ment4->setPosition(t_arrow3->getPosition() + ccp(0, -t_arrow3->getContentSize().height - 3));
			t_clipping->addChild(t_ment4);
			
			
			CCScale9Sprite* t_arrow4 = CCScale9Sprite::create("kt_arrow.png", CCRectMake(0, 0, 20, 24), CCRectMake(7, 16, 6, 1));
			t_arrow4->setContentSize(CCSizeMake(20, 40));
			t_arrow4->setPosition(ccp(429,(myDSH->puzzle_ui_top-320.f)/2.f + 320.f-20 - 43));
			t_clipping->addChild(t_arrow4);
			
			StyledLabelTTF* t_ment5 = StyledLabelTTF::create(myLoc->getLocalForKey(kMyLocalKey_mainflowDimmed5), mySGD->getFont().c_str(), 15, 999, StyledAlignment::kCenterAlignment);
			t_ment5->setAnchorPoint(ccp(0.5f,1));
			t_ment5->setPosition(t_arrow4->getPosition() + ccp(0, -t_arrow4->getContentSize().height/2.f - 3));
			t_clipping->addChild(t_ment5);
			
			
			CCSprite* t_arrow5 = CCSprite::create("kt_arrow.png");
			t_arrow5->setAnchorPoint(ccp(0.5f,1));
			t_arrow5->setPosition(ccp(458,(myDSH->puzzle_ui_top-320.f)/2.f + 320.f-20 - 43 + t_arrow2->getContentSize().height/2.f));
			t_clipping->addChild(t_arrow5);
			
			StyledLabelTTF* t_ment6 = StyledLabelTTF::create(myLoc->getLocalForKey(kMyLocalKey_mainflowDimmed6), mySGD->getFont().c_str(), 15, 999, StyledAlignment::kCenterAlignment);
			t_ment6->setAnchorPoint(ccp(0.5f,1));
			t_ment6->setPosition(t_arrow5->getPosition() + ccp(0, -t_arrow5->getContentSize().height - 3));
			t_clipping->addChild(t_ment6);
			
			
			CCSprite* t_arrow6 = CCSprite::create("kt_arrow_big.png");
			t_arrow6->setScale(0.6f);
			t_arrow6->setPosition(ccp(32,-(myDSH->puzzle_ui_top-320.f)/2.f+38 + 58));
			t_arrow6->setRotation(-90);
			t_clipping->addChild(t_arrow6);
			
			StyledLabelTTF* t_ment7 = StyledLabelTTF::create(myLoc->getLocalForKey(kMyLocalKey_mainflowDimmed7), mySGD->getFont().c_str(), 15, 999, StyledAlignment::kCenterAlignment);
			t_ment7->setAnchorPoint(ccp(0.5f,0));
			t_ment7->setPosition(t_arrow6->getPosition() + ccp(0, t_arrow6->getContentSize().height/2.f*t_arrow6->getScale() + 3));
			t_clipping->addChild(t_ment7);
			
			
			CCSprite* t_arrow7 = CCSprite::create("kt_arrow_big.png");
			t_arrow7->setScale(0.6f);
			t_arrow7->setPosition(ccp(32+55, -(myDSH->puzzle_ui_top-320.f)/2.f+38 + 58));
			t_arrow7->setRotation(-90);
			t_clipping->addChild(t_arrow7);
			
			StyledLabelTTF* t_ment8 = StyledLabelTTF::create(myLoc->getLocalForKey(kMyLocalKey_mainflowDimmed8), mySGD->getFont().c_str(), 15, 999, StyledAlignment::kCenterAlignment);
			t_ment8->setAnchorPoint(ccp(0.5f,0));
			t_ment8->setPosition(t_arrow7->getPosition() + ccp(0, t_arrow7->getContentSize().height/2.f*t_arrow7->getScale() + 3));
			t_clipping->addChild(t_ment8);
			
			
			CCSprite* t_arrow8 = CCSprite::create("kt_arrow_big.png");
			t_arrow8->setScale(0.6f);
			t_arrow8->setPosition(ccp(32+55*2.f, -(myDSH->puzzle_ui_top-320.f)/2.f+38 + 58));
			t_arrow8->setRotation(-90);
			t_clipping->addChild(t_arrow8);
			
			StyledLabelTTF* t_ment9 = StyledLabelTTF::create(myLoc->getLocalForKey(kMyLocalKey_mainflowDimmed9), mySGD->getFont().c_str(), 15, 999, StyledAlignment::kCenterAlignment);
			t_ment9->setAnchorPoint(ccp(0.5f,0));
			t_ment9->setPosition(t_arrow8->getPosition() + ccp(0, t_arrow8->getContentSize().height/2.f*t_arrow8->getScale() + 3));
			t_clipping->addChild(t_ment9);
			
			
			CCSprite* t_arrow9 = CCSprite::create("kt_arrow_big.png");
			t_arrow9->setScale(0.6f);
			t_arrow9->setPosition(ccp(32+55*3.f, -(myDSH->puzzle_ui_top-320.f)/2.f+38 + 58));
			t_arrow9->setRotation(-90);
			t_clipping->addChild(t_arrow9);
			
			StyledLabelTTF* t_ment10 = StyledLabelTTF::create(myLoc->getLocalForKey(kMyLocalKey_mainflowDimmed10), mySGD->getFont().c_str(), 15, 999, StyledAlignment::kCenterAlignment);
			t_ment10->setAnchorPoint(ccp(0.5f,0));
			t_ment10->setPosition(t_arrow9->getPosition() + ccp(0, t_arrow9->getContentSize().height/2.f*t_arrow9->getScale() + 3));
			t_clipping->addChild(t_ment10);
			
			
			
			CCScale9Sprite* t_stencil1 = CCScale9Sprite::create("rank_normal1.png", CCRectMake(0, 0, 31, 31), CCRectMake(15, 15, 1, 1));
			t_stencil1->setContentSize(CCSizeMake(50, 40));
			t_stencil1->setPosition(ccp(26, (myDSH->puzzle_ui_top-320.f)/2.f + 320.f-22));
			t_stencil_node->addChild(t_stencil1);
			
			CCScale9Sprite* t_stencil2 = CCScale9Sprite::create("rank_normal1.png", CCRectMake(0, 0, 31, 31), CCRectMake(15, 15, 1, 1));
			t_stencil2->setContentSize(CCSizeMake(125, 38));
			t_stencil2->setPosition(ccp(416,(myDSH->puzzle_ui_top-320.f)/2.f + 320.f-20));
			t_stencil_node->addChild(t_stencil2);
			
			CCScale9Sprite* t_stencil3 = CCScale9Sprite::create("rank_normal1.png", CCRectMake(0, 0, 31, 31), CCRectMake(15, 15, 1, 1));
			t_stencil3->setContentSize(CCSizeMake(235, 65));
			t_stencil3->setPosition(ccp(119,-(myDSH->puzzle_ui_top-320.f)/2.f+42));
			t_stencil_node->addChild(t_stencil3);
			
			
			TouchSuctionLayer* t_suction = TouchSuctionLayer::create(-9999);
			scenario_node->addChild(t_suction);
			t_suction->setTouchEnabled(true);
			t_suction->touch_began_func = [=]()
			{
				skip_menu->setVisible(true);
				t_suction->is_on_touch_began_func = false;
				t_stencil_node->removeAllChildren();
				t_arrow1->removeFromParent();
				t_arrow2->removeFromParent();
				t_arrow3->removeFromParent();
				t_arrow4->removeFromParent();
				t_arrow5->removeFromParent();
				t_arrow6->removeFromParent();
				t_arrow7->removeFromParent();
				t_arrow8->removeFromParent();
				t_arrow9->removeFromParent();
				t_ment2->removeFromParent();
				t_ment3->removeFromParent();
				t_ment4->removeFromParent();
				t_ment5->removeFromParent();
				t_ment6->removeFromParent();
				t_ment7->removeFromParent();
				t_ment8->removeFromParent();
				t_ment9->removeFromParent();
				t_ment10->removeFromParent();
				end_func11();
				t_suction->removeFromParent();
			};
			t_suction->is_on_touch_began_func = true;
			
			typing_box2->setTouchSuction(false);
		};
		
		function<void()> end_func9 = [=](){
			TypingBox::changeTypingBox(typing_box, typing_box2, asuka, ikaruga);
			typing_box2->startTyping(myLoc->getLocalForKey(kMyLocalKey_scenarioMent10), end_func10);
		};
		
		function<void()> end_func8 = [=](){
			TypingBox::changeTypingBox(typing_box2, typing_box, ikaruga, asuka);
			typing_box->startTyping(myLoc->getLocalForKey(kMyLocalKey_scenarioMent9), end_func9);
		};
		
		function<void()> end_func7 = [=](){
			TypingBox::changeTypingBox(typing_box, typing_box2, asuka, ikaruga);
			typing_box2->startTyping(myLoc->getLocalForKey(kMyLocalKey_scenarioMent8), end_func8);
		};
		
		function<void()> end_func6 = [=](){
			typing_box->startTyping(myLoc->getLocalForKey(kMyLocalKey_scenarioMent7), end_func7);
		};
		
		function<void()> end_func5 = [=](){
			TypingBox::changeTypingBox(typing_box2, typing_box, ikaruga, asuka);
			typing_box->startTyping(myLoc->getLocalForKey(kMyLocalKey_scenarioMent6), end_func6);
		};
		
		function<void()> end_func4 = [=](){
			TypingBox::changeTypingBox(typing_box, typing_box2, asuka, ikaruga);
			typing_box2->startTyping(myLoc->getLocalForKey(kMyLocalKey_scenarioMent5), end_func5);
		};
		
		function<void()> end_func3 = [=](){
			TypingBox::changeTypingBox(typing_box2, typing_box, ikaruga, asuka);
			typing_box->startTyping(myLoc->getLocalForKey(kMyLocalKey_scenarioMent4), end_func4);
		};
		
		function<void()> end_func2 = [=](){
			asuka->setVisible(false);
			ikaruga->setVisible(true);
			
			scenario_node->addChild(KSGradualValue<float>::create(0.f, 1.f, 0.3, [=](float t)
																  {
																	  ikaruga->setPositionX(240+240*screen_scale_x+ikaruga->getContentSize().width - ikaruga->getContentSize().width*2.f/3.f*t);
																  }, [=](float t)
																  {
																	  ikaruga->setPositionX(240+240*screen_scale_x+ikaruga->getContentSize().width - ikaruga->getContentSize().width*2.f/3.f*t);
																	  
																	  typing_box2->setVisible(true);
																	  typing_box2->setTouchSuction(true);
																	  
																	  typing_box->setTouchSuction(false);
																	  
																	  typing_box2->startTyping(myLoc->getLocalForKey(kMyLocalKey_scenarioMent3), end_func3);
																  }));
			typing_box->setTouchOffScrollAndButton();
			typing_box->setVisible(false);
		};
		
		function<void()> end_func1 = [=](){
			typing_box->startTyping(myLoc->getLocalForKey(kMyLocalKey_scenarioMent2), end_func2);
		};
		
		scenario_node->addChild(KSGradualValue<float>::create(0.f, 1.f, 0.3f, [=](float t)
															  {
																  t_gray->setOpacity(t*255);
																  asuka->setPositionX(240-240*screen_scale_x-asuka->getContentSize().width + asuka->getContentSize().width*2.f/3.f*t);
																  skip_menu->setPositionY(160+160*screen_scale_y - 25 + 150 - 150*t);
															  }, [=](float t)
															  {
																  t_gray->setOpacity(255);
																  asuka->setPositionX(240-240*screen_scale_x-asuka->getContentSize().width + asuka->getContentSize().width*2.f/3.f*t);
																  skip_menu->setPositionY(160+160*screen_scale_y - 25 + 150 - 150*t);
																  skip_menu->setEnabled(true);
																  
																  typing_box->startTyping(myLoc->getLocalForKey(kMyLocalKey_scenarioMent1), end_func1);
															  }));
	}
	else if(mySGD->is_on_attendance)
	{
		is_menu_enable = false;
		
		AttendancePopup* t_popup = AttendancePopup::create(-300, [=]()
														   {
															   if(mySGD->is_on_rank_reward)
																{
																	RankRewardPopup* t_popup = RankRewardPopup::create(-300, [=]()
																													   {
																														   if(mySGD->is_today_mission_first)
																														   {
																															   mySGD->is_today_mission_first = false;
																															   
																															   TodayMissionPopup* t_popup = TodayMissionPopup::create(-300, [=](){is_menu_enable = true;});
																															   addChild(t_popup, kMainFlowZorder_popup);
																														   }
																														   else
																														   {
																															   is_menu_enable = true;
																														   }
																													   });
																	addChild(t_popup, kMainFlowZorder_popup);
																}
															   else
																{
																	if(mySGD->is_today_mission_first)
																	{
																		mySGD->is_today_mission_first = false;
																		
																		TodayMissionPopup* t_popup = TodayMissionPopup::create(-300, [=](){is_menu_enable = true;});
																		addChild(t_popup, kMainFlowZorder_popup);
																	}
																	else
																	{
																		is_menu_enable = true;
																	}
																}
														   });
		addChild(t_popup, kMainFlowZorder_popup);
	}
	else if(mySGD->is_new_puzzle_card.getV())
	{
		TakePuzzleCardPopup* t_popup = TakePuzzleCardPopup::create(-300, [=]()
																   {
																	   function<void()> t_after_func = [=]()
																	   {
																		   if(mySGD->is_on_rank_reward)
																		   {
																			   RankRewardPopup* t_popup = RankRewardPopup::create(-300, [=]()
																																  {
																																	  if(mySGD->is_today_mission_first)
																																	  {
																																		  mySGD->is_today_mission_first = false;
																																		  
																																		  TodayMissionPopup* t_popup = TodayMissionPopup::create(-300, [=]()
																																																 {
																																																	 if(myDSH->getIntegerForKey(kDSH_Key_isShowEndlessModeTutorial) == 0 && mySGD->getUserdataHighPiece() >= mySGD->getEndlessMinPiece())
																																																	 {
																																																		 myDSH->setIntegerForKey(kDSH_Key_isShowEndlessModeTutorial, 1);
																																																		 
																																																		 pvp_tutorial();
																																																	 }
																																																	 else
																																																		 is_menu_enable = true;
																																																 });
																																		  addChild(t_popup, kMainFlowZorder_popup);
																																	  }
																																	  else
																																	  {
																																		  if(myDSH->getIntegerForKey(kDSH_Key_isShowEndlessModeTutorial) == 0 && mySGD->getUserdataHighPiece() >= mySGD->getEndlessMinPiece())
																																		  {
																																			  myDSH->setIntegerForKey(kDSH_Key_isShowEndlessModeTutorial, 1);
																																			  
																																			  pvp_tutorial();
																																		  }
																																		  else
																																			  is_menu_enable = true;
																																	  }
																																  });
																			   addChild(t_popup, kMainFlowZorder_popup);
																		   }
																	   };
																	   
																	   if(start_unlock_animation != nullptr)
																		{
																			start_unlock_animation(t_after_func);
																		}
																	   else
																		{
																			t_after_func();
																		}
																   });
		addChild(t_popup, kMainFlowZorder_popup);
	}
	else if(mySGD->is_on_rank_reward)
	{
		RankRewardPopup* t_popup = RankRewardPopup::create(-300, [=]()
														   {
															   if(mySGD->is_today_mission_first)
															   {
																   mySGD->is_today_mission_first = false;
																   
																   TodayMissionPopup* t_popup = TodayMissionPopup::create(-300, [=]()
																   {
																	   if(myDSH->getIntegerForKey(kDSH_Key_isShowEndlessModeTutorial) == 0 && mySGD->getUserdataHighPiece() >= mySGD->getEndlessMinPiece())
																	   {
																		   myDSH->setIntegerForKey(kDSH_Key_isShowEndlessModeTutorial, 1);
																		   
																		   pvp_tutorial();
																	   }
																	   else
																		   is_menu_enable = true;
																   });
																   addChild(t_popup, kMainFlowZorder_popup);
															   }
															   else
															   {
																   if(myDSH->getIntegerForKey(kDSH_Key_isShowEndlessModeTutorial) == 0 && mySGD->getUserdataHighPiece() >= mySGD->getEndlessMinPiece())
																   {
																	   myDSH->setIntegerForKey(kDSH_Key_isShowEndlessModeTutorial, 1);
																	   
																	   pvp_tutorial();
																   }
																   else
																	   is_menu_enable = true;
															   }
														   });
		addChild(t_popup, kMainFlowZorder_popup);
	}
	else if(mySGD->is_today_mission_first)
	{
		is_menu_enable = false;
		
		mySGD->is_today_mission_first = false;
		
		TodayMissionPopup* t_popup = TodayMissionPopup::create(-300, [=]()
		{
			if(myDSH->getIntegerForKey(kDSH_Key_isShowEndlessModeTutorial) == 0 && mySGD->getUserdataHighPiece() >= mySGD->getEndlessMinPiece())
			{
				myDSH->setIntegerForKey(kDSH_Key_isShowEndlessModeTutorial, 1);
				
				pvp_tutorial();
			}
			else
				is_menu_enable = true;
		});
		addChild(t_popup, kMainFlowZorder_popup);
	}
	else if(myDSH->getIntegerForKey(kDSH_Key_isShowEndlessModeTutorial) == 0 && mySGD->getUserdataHighPiece() >= mySGD->getEndlessMinPiece())
	{
		myDSH->setIntegerForKey(kDSH_Key_isShowEndlessModeTutorial, 1);
		
		pvp_tutorial();
	}
}

void MainFlowScene::topOuting()
{
	for(int i=0;i<top_list.size();i++)
	{
		if(i == 0)
		{
			CCPoint original_position = top_list[i]->getPosition();
			
			top_list[i]->addChild(KSGradualValue<float>::create(0.f, 1.f, 0.2f, [=](float t)
																{
																	top_list[i]->setPositionY(original_position.y+200.f*t);
																}, [=](float t)
																{
																	top_list[i]->setPositionY(original_position.y+200.f);
																}));
		}
		else
		{
			CCDelayTime* t_delay = CCDelayTime::create(i*0.1f);
			CCMoveTo* t_move = CCMoveTo::create(0.2f, top_list[i]->getPosition() + ccp(0,200));
			CCSequence* t_seq = CCSequence::create(t_delay, t_move, NULL);
			
			top_list[i]->runAction(t_seq);
		}
	}
}

void MainFlowScene::topReturnMode()
{
	CCPoint original_position = top_list[0]->getPosition();
	top_list[0]->setPosition(original_position + ccp(-150,0));
	top_list[0]->addChild(KSGradualValue<float>::create(1.f, 0.f, 0.3f, [=](float t)
														{
															top_list[0]->setPositionX(original_position.x-150.f*t);
														}, [=](float t)
														{
															top_list[0]->setPositionX(original_position.x);
														}));
}

void MainFlowScene::topPuzzleMode()
{
	CCPoint original_position = top_list[0]->getPosition();
	
	top_list[0]->addChild(KSGradualValue<float>::create(0.f, 1.f, 0.3f, [=](float t)
														{
															top_list[0]->setPositionX(original_position.x-150.f*t);
														}, [=](float t)
														{
															top_list[0]->setPositionX(original_position.x-150.f);
														}));
}

void MainFlowScene::onEnterTransitionDidFinish()
{
    CCLayer::onEnterTransitionDidFinish();
    TRACE();
}

void MainFlowScene::setTop()
{
	top_list.clear();
	
	CCNode* t_star_node = CCNode::create();
	t_star_node->setPosition(ccp(28,(myDSH->puzzle_ui_top-320.f)/2.f + 320.f-22));
	addChild(t_star_node, kMainFlowZorder_top);
	
	total_star = KS::loadCCBI<CCSprite*>(this, "main_star.ccbi").first;
	total_star->setPosition(ccp(-2,0));
	t_star_node->addChild(total_star);
	
	KSLabelTTF* star_count = KSLabelTTF::create(CCString::createWithFormat("%d", mySGD->getClearStarCount())->getCString(), mySGD->getFont().c_str(), 12);
	star_count->enableOuterStroke(ccBLACK, 0.8f);
	star_count->setPosition(ccp(-2,0));
	t_star_node->addChild(star_count);
	
	top_list.push_back(t_star_node);
	
	CCSprite* top_heart = CCSprite::create("mainflow_top_heart.png");
	top_heart->setAnchorPoint(ccp(0.5f,1.f));
	top_heart->setPosition(ccp(108,(myDSH->puzzle_ui_top-320.f)/2.f + 320.f-8)); // 114
	addChild(top_heart, kMainFlowZorder_top);
	
	top_list.push_back(top_heart);
	
//	CCSprite* top_case = CCSprite::create("mainflow_top.png");
//	top_case->setAnchorPoint(ccp(0.f,1.f));
//	top_case->setPosition(ccp(0,(myDSH->puzzle_ui_top-320.f)/2.f + 320.f-3));
//	addChild(top_case, kMainFlowZorder_top);
//	
//	CCSprite* top_case2 = CCSprite::create("mainflow_top2.png");
//	top_case2->setAnchorPoint(ccp(0.f,1.f));
//	top_case2->setPosition(ccp(top_case->getContentSize().width,top_case->getContentSize().height));
//	top_case->addChild(top_case2);
	
	heart_time = HeartTime::create();
	heart_time->setPosition(ccp(top_heart->getContentSize().width/2.f-49.f,top_heart->getContentSize().height/2.f));
	top_heart->addChild(heart_time);
	
	CCSprite* n_heart = CCSprite::create("mainflow_top_shop.png");
	CCSprite* s_heart = CCSprite::create("mainflow_top_shop.png");
	s_heart->setColor(ccGRAY);
	
	CCMenuItem* heart_item = CCMenuItemSprite::create(n_heart, s_heart, this, menu_selector(MainFlowScene::menuAction));
	heart_item->setTag(kMainFlowMenuTag_heartShop);
	
	CCMenu* heart_menu = CCMenu::createWithItem(heart_item);
	heart_menu->setPosition(ccp(top_heart->getContentSize().width/2.f+49.5f,top_heart->getContentSize().height/2.f));
	top_heart->addChild(heart_menu);
	
	
	CCSprite* top_gold = CCSprite::create("mainflow_top_gold.png");
	top_gold->setAnchorPoint(ccp(0.5f,1.f));
	top_gold->setPosition(ccp(221.5f,(myDSH->puzzle_ui_top-320.f)/2.f + 320.f-8)); // 227
	addChild(top_gold, kMainFlowZorder_top);
	
	top_list.push_back(top_gold);
	
	gold_img = CCSprite::create("price_gold_img.png");
	gold_img->setPosition(ccp(top_gold->getContentSize().width/2.f-39.f, top_gold->getContentSize().height/2.f+1));
	top_gold->addChild(gold_img);
	
	gold_label = CountingBMLabel::create(CCString::createWithFormat("%d", mySGD->getGoodsValue(kGoodsType_gold))->getCString(), "mainflow_top_font1.fnt", 0.3f, "%d");
	gold_label->setPosition(ccp(top_gold->getContentSize().width/2.f,top_gold->getContentSize().height/2.f-6));
	top_gold->addChild(gold_label);
	
	mySGD->setGoldLabel(gold_label);
	
	CCSprite* n_gold = CCSprite::create("mainflow_top_shop.png");
	CCSprite* s_gold = CCSprite::create("mainflow_top_shop.png");
	s_gold->setColor(ccGRAY);
	
	CCMenuItem* gold_item = CCMenuItemSprite::create(n_gold, s_gold, this, menu_selector(MainFlowScene::menuAction));
	gold_item->setTag(kMainFlowMenuTag_goldShop);
	
	CCMenu* gold_menu = CCMenu::createWithItem(gold_item);
	gold_menu->setPosition(ccp(top_gold->getContentSize().width/2.f+40,top_gold->getContentSize().height/2.f));
	top_gold->addChild(gold_menu);

	
	CCSprite* top_ruby = CCSprite::create("mainflow_top_ruby.png");
	top_ruby->setAnchorPoint(ccp(0.5f,1.f));
	top_ruby->setPosition(ccp(313,(myDSH->puzzle_ui_top-320.f)/2.f + 320.f-8)); // 325+5
	addChild(top_ruby, kMainFlowZorder_top);
	
	top_list.push_back(top_ruby);
	
	ruby_img = CCSprite::create("price_ruby_img.png");
	ruby_img->setPosition(ccp(top_ruby->getContentSize().width/2.f-27, top_gold->getContentSize().height/2.f));
	top_ruby->addChild(ruby_img);
	
	ruby_label = CountingBMLabel::create(CCString::createWithFormat("%d", mySGD->getGoodsValue(kGoodsType_ruby))->getCString(), "mainflow_top_font1.fnt", 0.3f, "%d");
	ruby_label->setPosition(ccp(top_ruby->getContentSize().width/2.f - 1,top_ruby->getContentSize().height/2.f-6));
	top_ruby->addChild(ruby_label);
	
	mySGD->setStarLabel(ruby_label);
	
	CCSprite* n_ruby = CCSprite::create("mainflow_top_shop.png");
	CCSprite* s_ruby = CCSprite::create("mainflow_top_shop.png");
	s_ruby->setColor(ccGRAY);
	
	CCMenuItem* ruby_item = CCMenuItemSprite::create(n_ruby, s_ruby, this, menu_selector(MainFlowScene::menuAction));
	ruby_item->setTag(kMainFlowMenuTag_rubyShop);
	
	CCMenu* ruby_menu = CCMenu::createWithItem(ruby_item);
	ruby_menu->setPosition(ccp(top_ruby->getContentSize().width/2.f+28,top_ruby->getContentSize().height/2.f));
	top_ruby->addChild(ruby_menu);
	
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	friend_point_label =  CountingBMLabel::create(CCString::createWithFormat("%d", mySGD->getFriendPoint())->getCString(), "mainflow_top_font1.fnt", 0.3f, "%d");
//	friend_point_label->setPosition(ccp(338,top_case->getContentSize().height/2.f-5));
//	top_case->addChild(friend_point_label);
//	
//	mySGD->setFriendPointLabel(friend_point_label);
	
//	CCSprite* n_friend_point = CCSprite::create("mainflow_top_shop.png");
//	CCSprite* s_friend_point = CCSprite::create("mainflow_top_shop.png");
//	s_friend_point->setColor(ccGRAY);
//	
//	CCMenuItem* friend_point_item = CCMenuItemSprite::create(n_friend_point, s_friend_point, this, menu_selector(MainFlowScene::menuAction));
//	friend_point_item->setTag(kMainFlowMenuTag_friendPointContent);
//	
//	CCMenu* friend_point_menu = CCMenu::createWithItem(friend_point_item);
//	friend_point_menu->setPosition(ccp(362,top_case->getContentSize().height/2.f));
//	top_case->addChild(friend_point_menu);
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	CCSprite* n_option = CCSprite::create("mainflow_new_option.png");
	CCSprite* s_option = CCSprite::create("mainflow_new_option.png");
	s_option->setColor(ccGRAY);
	
	CCMenuItem* option_item = CCMenuItemSprite::create(n_option, s_option, this, menu_selector(MainFlowScene::menuAction));
	option_item->setTag(kMainFlowMenuTag_option);
	
	CCMenu* option_menu = CCMenu::createWithItem(option_item);
	option_menu->setPosition(ccp(429,(myDSH->puzzle_ui_top-320.f)/2.f + 320.f-20)); // 461
	addChild(option_menu, kMainFlowZorder_top);
	
	
	CCNode* achieve_node = CCNode::create();
	addChild(achieve_node, kMainFlowZorder_top);
	
	CCSprite* n_achieve = CCSprite::create("mainflow_new_achievement.png");
	CCSprite* s_achieve = CCSprite::create("mainflow_new_achievement.png");
	s_achieve->setColor(ccGRAY);
	
	CCMenuItem* achieve_item = CCMenuItemSprite::create(n_achieve, s_achieve, this, menu_selector(MainFlowScene::menuAction));
	achieve_item->setTag(kMainFlowMenuTag_achievement);
	
	CCMenu* achieve_menu = CCMenu::createWithItem(achieve_item);
	achieve_menu->setPosition(ccp(401,(myDSH->puzzle_ui_top-320.f)/2.f + 320.f-20)); // 429
	achieve_node->addChild(achieve_menu);
	

	CCNode* postbox_node = CCNode::create();
	addChild(postbox_node, kMainFlowZorder_top);
	
	CCSprite* n_postbox = CCSprite::create("mainflow_new_postbox.png");
	CCSprite* s_postbox = CCSprite::create("mainflow_new_postbox.png");
	s_postbox->setColor(ccGRAY);
	
	CCMenuItem* postbox_item = CCMenuItemSprite::create(n_postbox, s_postbox, this, menu_selector(MainFlowScene::menuAction));
	postbox_item->setTag(kMainFlowMenuTag_postbox);
	
	CCMenu* postbox_menu = CCMenu::createWithItem(postbox_item);
	postbox_menu->setPosition(ccp(374,(myDSH->puzzle_ui_top-320.f)/2.f + 320.f-20)); // 397
	postbox_node->addChild(postbox_menu);
	
	top_list.push_back(postbox_node);
	
	top_list.push_back(achieve_node);
	
	top_list.push_back(option_menu);
	
	
	postbox_count_case = CCScale9Sprite::create("mainflow_new2.png", CCRectMake(0, 0, 20, 20), CCRectMake(9, 9, 2, 2));//"mainflow_new.png");
	postbox_count_case->setContentSize(CCSizeMake(20, 20));
	postbox_count_case->setPosition(postbox_menu->getPosition() + ccp(6,6));
	postbox_node->addChild(postbox_count_case);
	
	CCScaleTo* t_scale1 = CCScaleTo::create(0.1f, 1.3f);
	CCScaleTo* t_scale2 = CCScaleTo::create(0.2f, 1.f);
	CCDelayTime* t_delay1 = CCDelayTime::create(0.5f);
	CCScaleTo* t_scale3 = CCScaleTo::create(0.1f, 1.3f);
	CCScaleTo* t_scale4 = CCScaleTo::create(0.2f, 1.f);
	CCDelayTime* t_delay2 = CCDelayTime::create(5.f);
	CCSequence* t_seq1 = CCSequence::create(t_scale1, t_scale2, t_delay1, t_scale3, t_scale4, t_delay2, NULL);
	CCRepeatForever* t_repeat1 = CCRepeatForever::create(t_seq1);
	postbox_count_case->runAction(t_repeat1);
	
	postbox_count_case->setVisible(false);
	
//	postbox_count_case->addChild(KSSchedule::create([=](float dt)
//													{
//														if(postbox_menu->getPositionY() >= (myDSH->puzzle_ui_top-320.f)/2.f + 320.f-20)
//															KS::setOpacity(postbox_count_case, 0);
//														else
//															KS::setOpacity(postbox_count_case, 255);
//														return true;
//													}));
	
	postbox_count_label = CCLabelTTF::create("0", mySGD->getFont().c_str(), 8);
	postbox_count_label->setColor(ccc3(255, 255, 255));
	postbox_count_label->setPosition(ccp(postbox_count_case->getContentSize().width/2.f-0.5f, postbox_count_case->getContentSize().height/2.f+0.5f));
	postbox_count_case->addChild(postbox_count_label);
	
    TRACE();
	countingMessage();
	TRACE();
	
	
	achievement_count_case = CCScale9Sprite::create("mainflow_new2.png", CCRectMake(0, 0, 20, 20), CCRectMake(9, 9, 2, 2));
	achievement_count_case->setContentSize(CCSizeMake(20, 20));
	achievement_count_case->setPosition(achieve_menu->getPosition() + ccp(6, 6));
	achieve_node->addChild(achievement_count_case);
	
	achievement_count_label = CCLabelTTF::create("", mySGD->getFont().c_str(), 8);
	achievement_count_label->setPosition(ccp(achievement_count_case->getContentSize().width/2.f, achievement_count_case->getContentSize().height/2.f + 0));
	achievement_count_case->addChild(achievement_count_label);
	
	CCScaleTo* t_scale5 = CCScaleTo::create(0.1f, 1.3f);
	CCScaleTo* t_scale6 = CCScaleTo::create(0.2f, 1.f);
	CCDelayTime* t_delay3 = CCDelayTime::create(0.5f);
	CCScaleTo* t_scale7 = CCScaleTo::create(0.1f, 1.3f);
	CCScaleTo* t_scale8 = CCScaleTo::create(0.2f, 1.f);
	CCDelayTime* t_delay4 = CCDelayTime::create(5.f);
	CCSequence* t_seq2 = CCSequence::create(t_scale5, t_scale6, t_delay3, t_scale7, t_scale8, t_delay4, NULL);
	CCRepeatForever* t_repeat2 = CCRepeatForever::create(t_seq2);
	achievement_count_case->runAction(t_repeat2);
	
	achievement_count_case->setVisible(false);
	
//	achievement_count_case->addChild(KSSchedule::create([=](float dt)
//													{
//														if(achieve_menu->getPositionY() >= (myDSH->puzzle_ui_top-320.f)/2.f + 320.f-20)
//															KS::setOpacity(achievement_count_case, 0);
//														else
//															KS::setOpacity(achievement_count_case, 255);
//														return true;
//													}));
	
	TRACE();
	countingAchievement();
	
	TRACE();
	
	CCSprite* n_event = CCSprite::create("mainflow_new_event.png");
	CCSprite* s_event = CCSprite::create("mainflow_new_event.png");
	s_event->setColor(ccGRAY);
	
	CCMenuItem* event_item = CCMenuItemSprite::create(n_event, s_event, this, menu_selector(MainFlowScene::menuAction));
	event_item->setTag(kMainFlowMenuTag_event);
	
	CCMenu* event_menu = CCMenu::createWithItem(event_item);
	event_menu->setPosition(ccp(458,(myDSH->puzzle_ui_top-320.f)/2.f + 320.f-20));
	addChild(event_menu, kMainFlowZorder_top);
	
	top_list.push_back(event_menu);
    
	TRACE();
//	CCSprite* n_tip = CCSprite::create("mainflow_tip.png");
//	CCSprite* s_tip = CCSprite::create("mainflow_tip.png");
//	s_tip->setColor(ccGRAY);
//	
//	CCMenuItem* tip_item = CCMenuItemSprite::create(n_tip, s_tip, this, menu_selector(MainFlowScene::menuAction));
//	tip_item->setTag(kMainFlowMenuTag_tip);
//	
//	CCMenu* tip_menu = CCMenu::createWithItem(tip_item);
//	tip_menu->setPosition(ccp(465,top_case->getContentSize().height/2.f));
//	top_case->addChild(tip_menu);
}

void MainFlowScene::countingMessage()
{
	TRACE();
	postbox_count_case->setVisible(false);
	Json::Value p;
	p["memberID"]=hspConnector::get()->getSocialID();
	// 0 이 아니면 해당하는 타입의 메시지가 들어옴.
	//USE GETMESSAGELIST
	hspConnector::get()->command("checkgiftboxhistory",p,[=](Json::Value r)
								 {
									 TRACE();
									 GraphDogLib::JsonToLog("checkgiftboxhistory", r);
									 
									 if(r["result"]["code"].asInt() != GDSUCCESS)
										{
											TRACE();
											return;
										}
									 
									 int message_cnt = r.get("haveNewGiftCnt", 0).asInt();
									 
									 if(message_cnt > 0)
									 {
										 int t_count = message_cnt;
										 int base_width = 20;
										 while (t_count/10 > 0)
										 {
											 base_width+=5;
											 t_count /= 10;
										 }
										 
										 postbox_count_case->setContentSize(CCSizeMake(base_width, 20));
									 }
									 
									 postbox_count_case->setVisible(message_cnt > 0);
									 postbox_count_label->setString(CCString::createWithFormat("%d", message_cnt)->getCString());
									 postbox_count_label->setPosition(ccpFromSize(postbox_count_case->getContentSize()/2.f));
									 TRACE();
								 }, -1);
	TRACE();
}

void MainFlowScene::countingAchievement()
{
	achievement_count_case->setVisible(false);
	
	int reward_count = 0;
	
	for(int i=kAchievementCode_base+1;i<kAchievementCode_end;i++)
	{
		if(!myAchieve->isCompleted((AchievementCode)i) &&
		   myAchieve->isAchieve((AchievementCode)i))
		{
			reward_count++;
		}
	}
	
	for(int i=kAchievementCode_hidden_base+1;i<kAchievementCode_hidden_end;i++)
	{
		if(!myAchieve->isCompleted((AchievementCode)i) &&
		   myAchieve->isAchieve((AchievementCode)i))
		{
			reward_count++;
		}
	}
	
	if(reward_count > 0)
	{
		int t_count = reward_count;
		int base_width = 20;
		while (t_count/10 > 0)
		{
			base_width+=5;
			t_count /= 10;
		}

		achievement_count_case->setContentSize(CCSizeMake(base_width, 20));
		
		achievement_count_case->setVisible(true);
		achievement_count_label->setString(CCString::createWithFormat("%d", reward_count)->getCString());
	}
	
	achievement_count_label->setPosition(ccp(achievement_count_case->getContentSize().width/2.f, achievement_count_case->getContentSize().height/2.f + 0));
}

void MainFlowScene::popupClose()
{
	is_menu_enable = true;
}

void MainFlowScene::achievePopupClose()
{
	countingAchievement();
	is_menu_enable = true;
}

void MainFlowScene::mailPopupClose()
{
    TRACE();
	countingMessage();
	is_menu_enable = true;
    TRACE();
}

void MainFlowScene::tutorialCardSettingClose()
{
	is_menu_enable = true;
	puzzle_table->setTouchEnabled(true);
	puzzle_table->setTouchPriority(kCCMenuHandlerPriority+1);
}

void MainFlowScene::closeFriendPoint()
{
	close_friend_point_action();
}

void MainFlowScene::callTimeInfo()
{
	TRACE();
	mySGD->keep_time_info.is_loaded = false;
	hspConnector::get()->command("gettimeinfo", Json::Value(), [=](Json::Value result_data)
								 {
									 TRACE();
									if(result_data["result"]["code"].asInt() == GDSUCCESS)
									{
										TRACE();
										mySGD->keep_time_info.timestamp = result_data["timestamp"].asUInt();
										mySGD->keep_time_info.weekNo = result_data["weekNo"].asUInt();
										mySGD->keep_time_info.weekday = result_data["weekday"].asInt();
										mySGD->keep_time_info.date = result_data["date"].asInt64();
										mySGD->keep_time_info.hour = result_data["hour"].asInt();
										mySGD->keep_time_info.is_loaded = true;
										
										if(!is_table_openning)
											tableRefresh();
										TRACE();
									}
									else
									{
										TRACE();
										addChild(KSTimer::create(1.f, [=](){callTimeInfo();}));
									}
								 }, -1);
}

void MainFlowScene::tableRefresh()
{
	if(!is_menu_enable)
	{
		addChild(KSTimer::create(0.1f, [=](){tableRefresh();}));
		return;
	}
	
	CCPoint origin_offset = puzzle_table->getContentOffset();
	puzzle_table->reloadData();
	puzzle_table->setContentOffset(origin_offset);
}

MainFlowScene::~MainFlowScene()
{
	hspConnector::get()->removeTarget(this);
}

void MainFlowScene::alertAction(int t1, int t2)
{
	if(t1 == 1 && t2 == 0)
	{
		CCDirector::sharedDirector()->end();
	}
}

void MainFlowScene::keyBackClicked()
{
	AlertEngine::sharedInstance()->addDoubleAlert("Exit", MyLocal::sharedInstance()->getLocalForKey(kMyLocalKey_exit), "Ok", "Cancel", 1, this, alertfuncII_selector(MainFlowScene::alertAction));
}
