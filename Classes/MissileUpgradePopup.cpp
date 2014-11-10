//
//  MissileUpgradePopup.cpp
//  DGproto
//
//  Created by 사원3 on 2014. 4. 20..
//
//

#include "MissileUpgradePopup.h"
#include "CCMenuLambda.h"
#include "TouchSuctionLayer.h"
#include "KSUtil.h"
#include "KSLabelTTF.h"
#include "StarGoldData.h"
#include "DataStorageHub.h"
#include "StoneMissile.h"
#include "ASPopupView.h"
#include "LoadingLayer.h"
#include "MyLocalization.h"
#include "PuzzleScene.h"
#include "MainFlowScene.h"
#include "CommonButton.h"
#include "CommonAnimation.h"
#include "FiveRocksCpp.h"

MissileUpgradePopup* MissileUpgradePopup::create(int t_touch_priority, function<void()> t_end_func, function<void()> t_upgrade_func)
{
	MissileUpgradePopup* t_mup = new MissileUpgradePopup();
	t_mup->myInit(t_touch_priority, t_end_func, t_upgrade_func);
	t_mup->autorelease();
	return t_mup;
}

void MissileUpgradePopup::myInit(int t_touch_priority, function<void()> t_end_func, function<void()> t_upgrade_func)
{
	is_menu_enable = false;
	
	use_gold_value = 0;
	
	touch_priority = t_touch_priority;
	end_func = t_end_func;
	upgrade_func = t_upgrade_func;
	
	CCSize screen_size = CCEGLView::sharedOpenGLView()->getFrameSize();
	float screen_scale_x = screen_size.width/screen_size.height/1.5f;
	if(screen_scale_x < 1.f)
		screen_scale_x = 1.f;
	
	gray = CCSprite::create("back_gray.png");
	gray->setOpacity(0);
	gray->setPosition(ccp(240,160));
	gray->setScaleX(screen_scale_x);
	gray->setScaleY(myDSH->ui_top/320.f/myDSH->screen_convert_rate);
	addChild(gray);
	
	suction = TouchSuctionLayer::create(touch_priority+1);
	addChild(suction);
	
	suction->setTouchEnabled(true);
	
	m_container = CCNode::create();
	m_container->setPosition(ccp(240,160));
	addChild(m_container);
	
	
	
	back_case = CCSprite::create("popup_large_back.png");
	back_case->setPosition(ccp(0,0));
	m_container->addChild(back_case);
	
	
	CCScale9Sprite* back_center = CCScale9Sprite::create("common_grayblue.png", CCRectMake(0, 0, 26, 26), CCRectMake(12, 12, 2, 2));
	back_center->setContentSize(CCSizeMake(251, 108));
	back_center->setPosition(ccpFromSize(back_case->getContentSize()/2.f) + ccp(0,5));
	back_case->addChild(back_center);
	
	
	CommonButton* cancel_button = CommonButton::createCloseButton(touch_priority);
	cancel_button->setPosition(ccp(back_case->getContentSize().width/2.f-22,back_case->getContentSize().height/2.f-25));
	cancel_button->setFunction([=](CCObject* sender)
							   {
								   if(!is_menu_enable)
									   return;
								   
								   is_menu_enable = false;
								   
								   AudioEngine::sharedInstance()->playEffect("se_button1.mp3");
								   
									 CommonAnimation::closePopup(this, m_container, gray, [=](){
										 
									 }, [=](){
										 end_func(); removeFromParent();
									 });
							   });
	m_container->addChild(cancel_button);
	
	
	KSLabelTTF* title_label = KSLabelTTF::create(myLoc->getLocalForKey(kMyLocalKey_missileUpgrade), mySGD->getFont().c_str(), 12);
	title_label->disableOuterStroke();
	title_label->setAnchorPoint(ccp(0.5f,0.5f));
	title_label->setPosition(ccp(-85,back_case->getContentSize().height/2.f-35));
	m_container->addChild(title_label);
	
	KSLabelTTF* sub_label = KSLabelTTF::create(myLoc->getLocalForKey(kMyLocalKey_upgradeSubMent), mySGD->getFont().c_str(), 11);
	sub_label->disableOuterStroke();
	sub_label->setColor(ccc3(20, 40, 70));
	sub_label->setAnchorPoint(ccp(0.5f,0.5f));
	sub_label->setPosition(ccp(0,73));
	m_container->addChild(sub_label);
	
	upgrade_action_node = CCNode::create();
	m_container->addChild(upgrade_action_node);
	
	CCSprite* level_case = CCSprite::create("startsetting_levelbox.png");
	level_case->setAnchorPoint(ccp(0,0.5f));
	level_case->setPosition(ccp(-back_case->getContentSize().width/2.f+30,45));
	upgrade_action_node->addChild(level_case);
	
	StoneType missile_type_code = StoneType(mySGD->getSelectedCharacterHistory().characterNo.getV()-1);
	missile_type_code = kStoneType_guided;
	
	int missile_level = mySGD->getSelectedCharacterHistory().level.getV();
	
	missile_img = NULL;
	
	if(missile_type_code == kStoneType_guided)
	{
		int grade = (missile_level-1)/5+1;
		bool rotation = false;
		if(grade == 1 || grade == 4)
			rotation = true;
		GuidedMissileForUpgradeWindow* t_gm = GuidedMissileForUpgradeWindow::createForShowWindow(CCString::createWithFormat("jack_missile_%d.png", missile_level)->getCString(),
																														 rotation);
		t_gm->beautifier((missile_level-1)/5+1, (missile_level-1)%5);
		t_gm->setPosition(ccp(0,0));

		upgrade_action_node->addChild(t_gm);
		
		
		t_gm->setShowWindowVelocityRad(M_PI / (60.f - (grade-1)*6));
		
		missile_img = t_gm;
	}
	
	missile_data_level = KSLabelTTF::create(CCString::createWithFormat(myLoc->getLocalForKey(kMyLocalKey_levelValue), missile_level)->getCString(), mySGD->getFont().c_str(), 12);
//	missile_data_level->setColor(ccc3(255, 222, 0));
	missile_data_level->disableOuterStroke();
	missile_data_level->setAnchorPoint(ccp(0.5f,0.5f));
	missile_data_level->setPosition(ccp(level_case->getContentSize().width/2.f-30.f,level_case->getContentSize().height/2.f));
	level_case->addChild(missile_data_level);
	
	missile_data_power = KSLabelTTF::create(CCString::createWithFormat(myLoc->getLocalForKey(kMyLocalKey_powerValue), KS::insert_separator(mySGD->getSelectedCharacterHistory().power.getV()).c_str())->getCString(), mySGD->getFont().c_str(), 11);
//	missile_data_power->setColor(ccc3(255, 222, 0));
	missile_data_power->disableOuterStroke();
	missile_data_power->setAnchorPoint(ccp(0.5f,0.5f));
	missile_data_power->setPosition(ccp(level_case->getContentSize().width/2.f+28.f,level_case->getContentSize().height/2.f));
	level_case->addChild(missile_data_power);
	
	
	CCLabelTTF* t_label = CCLabelTTF::create();
	
	upgrade_label = KSLabelTTF::create(CCString::createWithFormat(myLoc->getLocalForKey(kMyLocalKey_upgradeLevelValue2), missile_level+1)->getCString(), mySGD->getFont().c_str(), 13);
	upgrade_label->disableOuterStroke();
	upgrade_label->setAnchorPoint(ccp(0.5f,0.5f));
	price_back = CCScale9Sprite::create("common_in.png", CCRectMake(0,0,20,20), CCRectMake(9,9,2,2));
	price_back->setContentSize(CCSizeMake(90, 26));
	price_back->setPosition(ccp(upgrade_label->getContentSize().width + price_back->getContentSize().width/2.f + 10, upgrade_label->getContentSize().height/2.f));
	upgrade_label->addChild(price_back);
	
	if(mySGD->getGoodsValue(kGoodsType_pass3) > 0)
	{
		price_type = CCSprite::create("pass_ticket3.png");
		price_type->setPosition(ccp(price_back->getContentSize().width/2.f-29,price_back->getContentSize().height/2.f));
		price_back->addChild(price_type);
		
		CCScale9Sprite* pass_count_case = CCScale9Sprite::create("mainflow_new2.png", CCRectMake(0, 0, 20, 20), CCRectMake(9, 9, 2, 2));
		pass_count_case->setPosition(ccpFromSize(price_type->getContentSize()/2.f) + ccp(9,6));
		price_type->addChild(pass_count_case);
		
		CCLabelTTF* pass_count_label = CCLabelTTF::create(ccsf("%d", mySGD->getGoodsValue(kGoodsType_pass3)), mySGD->getFont().c_str(), 8);
		pass_count_label->setColor(ccc3(255, 255, 255));
		float min_width = 10+pass_count_label->getContentSize().width;
		if(min_width < 20)
			min_width = 20;
		pass_count_case->setContentSize(CCSizeMake(min_width, 20));
		pass_count_label->setPosition(ccp(pass_count_case->getContentSize().width/2.f-0.5f, pass_count_case->getContentSize().height/2.f+0.5f));
		pass_count_case->addChild(pass_count_label);
		
		price_label = KSLabelTTF::create(myLoc->getLocalForKey(kMyLocalKey_free), mySGD->getFont().c_str(), 15);
		price_label->disableOuterStroke();
		price_label->setPosition(ccp(price_back->getContentSize().width/2.f+10,price_back->getContentSize().height/2.f));
		price_back->addChild(price_label);
	}
	else
	{
		price_type = CCSprite::create("price_gold_img.png");
		price_type->setPosition(ccp(price_back->getContentSize().width/2.f-29,price_back->getContentSize().height/2.f));
		price_back->addChild(price_type);
		price_label = KSLabelTTF::create(
					 KS::insert_separator( CCString::createWithFormat("%d",
												mySGD->getSelectedCharacterHistory().nextPrice.getV())->getCString()).c_str(),
																mySGD->getFont().c_str(), 15);
		price_label->disableOuterStroke();
		price_label->setPosition(ccp(price_back->getContentSize().width/2.f+10,price_back->getContentSize().height/2.f));
		price_back->addChild(price_label);
	}
	
	t_label->addChild(upgrade_label);
	
	
	
	CCScale9Sprite* upgrade_back = CCScale9Sprite::create("mainbutton_purple.png", CCRectMake(0,0,215,65), CCRectMake(107, 32, 1, 1));
	
	upgrade_button = CCControlButton::create(t_label, upgrade_back);
	upgrade_button->addTargetWithActionForControlEvents(this, cccontrol_selector(MissileUpgradePopup::upgradeAction), CCControlEventTouchUpInside);
	upgrade_button->setPreferredSize(CCSizeMake(215,65));
	upgrade_button->setPosition(ccp(0,-82));
	upgrade_action_node->addChild(upgrade_button);
	
	upgrade_button->setTouchPriority(touch_priority);
	
	upgrade_label->setPositionX(-price_back->getContentSize().width/2.f-5);
	
	
	
	CommonAnimation::openPopup(this, m_container, gray, [=](){
		
	}, [=](){
		is_menu_enable = true;
	});
}

void MissileUpgradePopup::upgradeAction(CCObject* sender, CCControlEvent t_event)
{
	if(!is_menu_enable)
		return;
	
	is_menu_enable = false;
	
	AudioEngine::sharedInstance()->playEffect("se_button1.mp3", false);
	
	if(mySGD->getGoodsValue(kGoodsType_pass3) > 0)
	{
		loading_layer = LoadingLayer::create(touch_priority-100);
		addChild(loading_layer);
		
		int missile_level = mySGD->getSelectedCharacterHistory().level.getV();
		before_gold = mySGD->getGoodsValue(kGoodsType_gold);
		before_level = missile_level;
		before_damage = mySGD->getSelectedCharacterHistory().power.getV();
		
		mySGD->addChangeGoods("cu_p", kGoodsType_cu, mySGD->getSelectedCharacterHistory().characterNo.getV());
		
		mySGD->changeGoods(json_selector(this, MissileUpgradePopup::resultSaveUserData));
		
//		CharacterHistory t_history = mySGD->getSelectedCharacterHistory();
//		t_history.level = t_history.level.getV() + 1;
//		
//		vector<CommandParam> command_list;
//		command_list.clear();
//		command_list.push_back(mySGD->getUpdateCharacterHistoryParam(t_history, nullptr));
//		
//		
//		mySGD->changeGoodsTransaction(command_list, );
	}
	else
	{
		int upgrade_price = mySGD->getSelectedCharacterHistory().nextPrice.getV();
		
		if(mySGD->getGoodsValue(kGoodsType_gold) < upgrade_price)// + use_item_price_gold.getV())
		{
			addChild(ASPopupView::getNotEnoughtGoodsGoShopPopup(touch_priority-100, kGoodsType_gold, [=]()
																{
                                                                    if(mySGD->is_endless_mode)
                                                                        ((MainFlowScene*)getParent()->getParent())->showShopPopup(kSC_gold);
                                                                    else
                                                                        ((PuzzleScene*)getParent()->getParent())->showShopPopup(kSC_gold);
																}), 9999);
			is_menu_enable = true;
			return;
		}
		
		use_gold_value = upgrade_price;
		
		loading_layer = LoadingLayer::create(touch_priority-100);
		addChild(loading_layer);
		
		int missile_level = mySGD->getSelectedCharacterHistory().level.getV();
		before_gold = mySGD->getGoodsValue(kGoodsType_gold);
		before_level = missile_level;
		before_damage = mySGD->getSelectedCharacterHistory().power.getV();
		
		vector<ChangeGoodsDataDetail> t_list;
		
		ChangeGoodsDataDetail t_detail;
		t_detail.m_type = kGoodsType_gold;
		t_detail.m_value = -upgrade_price;
		t_detail.m_statsID = "";
		t_detail.m_statsValue = "";
		t_detail.m_content = "";
		t_detail.m_isPurchase = false;
		
		t_list.push_back(t_detail);
		
		ChangeGoodsDataDetail t_detail2;
		t_detail2.m_type = kGoodsType_cu;
		t_detail2.m_value = mySGD->getSelectedCharacterHistory().characterNo.getV();
		t_detail2.m_statsID = "";
		t_detail2.m_statsValue = "";
		t_detail2.m_content = "";
		t_detail2.m_isPurchase = false;
		
		t_list.push_back(t_detail2);
		
		mySGD->addChangeGoods("cu_g", t_list);
		
		mySGD->changeGoods(json_selector(this, MissileUpgradePopup::resultSaveUserData));
		
//		CharacterHistory t_history = mySGD->getSelectedCharacterHistory();
//		t_history.level = t_history.level.getV() + 1;
//		
//		vector<CommandParam> command_list;
//		command_list.clear();
//		command_list.push_back(mySGD->getUpdateCharacterHistoryParam(t_history, nullptr));
//		
//		
//		mySGD->changeGoodsTransaction(command_list, json_selector(this, MissileUpgradePopup::resultSaveUserData));
	}
}

void MissileUpgradePopup::resultSaveUserData(Json::Value result_data)
{
	CCLOG("resultSaveUserData : %s", GraphDogLib::JsonObjectToString(result_data).c_str());
	if(result_data["result"]["code"].asInt() == GDSUCCESS)
	{
		CCLOG("missile upgrade success!!");
		
//		fiverocks::FiveRocksBridge::setUserLevel(mySGD->getSelectedCharacterHistory().level.getV());
//		if(use_gold_value > 0)
//			fiverocks::FiveRocksBridge::trackEvent("UseGold", "LvUp", ccsf("Lv%02d", mySGD->getSelectedCharacterHistory().level.getV()), ccsf("Puzzle %03d", myDSH->getIntegerForKey(kDSH_Key_selectedPuzzleNumber)), use_gold_value);
		use_gold_value = 0;
		
		AudioEngine::sharedInstance()->playEffect("se_buy.mp3", false);
		AudioEngine::sharedInstance()->playEffect("se_upgrade.mp3", false);
		
		addChild(KSGradualValue<float>::create(1.f, 0.f, 0.3f, [=](float t){
			upgrade_action_node->setScaleX(t/2.f + 0.5f);
			upgrade_action_node->setScaleY(t);
		}, [=](float t){
			upgrade_action_node->setScaleX(0.5f);
			upgrade_action_node->setScaleY(0.f);
		}));
		
		CCSprite* upgrade_effect_3 = CCSprite::create("missile_upgrade_3.png");
		upgrade_effect_3->setOpacity(0);
		upgrade_effect_3->setPosition(ccp(0,0));
		m_container->addChild(upgrade_effect_3);
		
		CCSprite* upgrade_effect_4 = CCSprite::create("missile_upgrade_4.png");
		upgrade_effect_4->setScale(0);
		upgrade_effect_4->setOpacity(0);
		upgrade_effect_4->setPosition(ccp(-57,0));
		m_container->addChild(upgrade_effect_4);
		
		addChild(KSGradualValue<float>::create(0.f, 1.f, 0.25f, [=](float t){
			upgrade_effect_3->setOpacity(t*255);
			upgrade_effect_4->setOpacity(t*255);
			upgrade_effect_4->setScale(t);
		}, [=](float t){
			upgrade_effect_3->setOpacity(255);
			upgrade_effect_4->setOpacity(255);
			upgrade_effect_4->setScale(1.f);
			
			addChild(KSGradualValue<float>::create(0.f, 1.f, 0.45f, [=](float t){
				upgrade_effect_3->setScaleY(1.f - 0.8f*t);
				upgrade_effect_4->setPositionX(-57+120*t);
				upgrade_effect_4->setScale(1.f-t);
				upgrade_effect_4->setOpacity(255-t*255);
			}, [=](float t){
				upgrade_effect_3->setScaleY(0.2f);
				upgrade_effect_4->setPositionX(0);
				upgrade_effect_4->setScale(0.f);
				upgrade_effect_4->setOpacity(0);
				
				addChild(KSGradualValue<float>::create(0.f, 1.f, 0.45f, [=](float t){
					upgrade_effect_3->setScaleX(1.f+4.f*t);
					upgrade_effect_3->setScaleY(0.2f+4.8f*t);
					upgrade_effect_4->setScale(10.f*t);
				}, [=](float t){
					addChild(KSTimer::create(0.1f, [=](){
						upgrade_effect_3->removeFromParent();
						upgrade_effect_4->removeFromParent();
					}));
				}));
				
				addChild(KSGradualValue<float>::create(0.f, 1.f, 0.25f, [=](float t){
					upgrade_effect_4->setOpacity(t*255);
				}, [=](float t){
					upgrade_effect_4->setOpacity(255);
					
					addChild(KSGradualValue<float>::create(0.f, 1.f, 0.2f, [=](float t){
						upgrade_effect_3->setOpacity(255-t*255);
						upgrade_effect_4->setOpacity(255-t*255);
					}, [=](float t){
						upgrade_effect_3->setOpacity(0);
						upgrade_effect_4->setOpacity(0);
					}));
					
					addChild(KSGradualValue<float>::create(-0.2f, 1.f, 0.2f, [=](float t){
						if(t >= 0)
						{
							upgrade_action_node->setScaleX(0.5f + t*0.5f);
							upgrade_action_node->setScaleY(t);
						}
					}, [=](float t){
						upgrade_action_node->setScaleX(1.f);
						upgrade_action_node->setScaleY(1.f);
					}));
					
					setAfterUpgrade();
				}));
			}));
		}));
	}
	else
	{
		CCLOG("missile upgrade fail!!");
		use_gold_value = 0;
		
		mySGD->clearChangeGoods();
		addChild(ASPopupView::getNotEnoughtGoodsGoShopPopup(touch_priority-200, kGoodsType_gold, [=]()
															{
																((PuzzleScene*)getParent()->getParent())->showShopPopup(kSC_gold);
															}), 9999);
	}
	loading_layer->removeFromParent();
}

void MissileUpgradePopup::setAfterUpgrade()
{
	int missile_level = mySGD->getSelectedCharacterHistory().level.getV();
	
	int after_damage = mySGD->getSelectedCharacterHistory().power.getV();
	
	missile_data_level->setString(CCString::createWithFormat(myLoc->getLocalForKey(kMyLocalKey_levelValue), missile_level)->getCString());
	missile_data_power->setString(CCString::createWithFormat(myLoc->getLocalForKey(kMyLocalKey_powerValue), KS::insert_separator(after_damage).c_str())->getCString());
	
	CCPoint missile_position;
	if(missile_img)
	{
		missile_position = missile_img->getPosition();
		missile_img->removeFromParent();
	}
	
	StoneType missile_type_code = StoneType(mySGD->getSelectedCharacterHistory().characterNo.getV()-1);
	missile_type_code = kStoneType_guided;
	
	if(missile_type_code == kStoneType_guided)
	{

		int grade = (missile_level-1)/5+1;
		bool rotation = false;
		if(grade == 1 || grade == 4)
			rotation = true;

		GuidedMissileForUpgradeWindow* t_gm = GuidedMissileForUpgradeWindow::createForShowWindow(CCString::createWithFormat("jack_missile_%d.png", missile_level)->getCString(),
																															rotation);
		t_gm->beautifier((missile_level-1)/5+1, (missile_level-1)%5);
//		GuidedMissile* t_gm = GuidedMissile::createForShowWindow(CCString::createWithFormat("me_guide%d.ccbi", (missile_level-1)%5 + 1)->getCString());
		t_gm->setPosition(missile_position);
//		t_gm->beautifier((missile_level-1)/5+1, (missile_level-1)%5+1);
		upgrade_action_node->addChild(t_gm);
		
		
		t_gm->setShowWindowVelocityRad(M_PI / (60.f - (grade-1)*6));
		
		missile_img = t_gm;
	}
	
	
	if(mySGD->getSelectedCharacterHistory().isMaxLevel.getV())
	{
		upgrade_button->setEnabled(false);
		upgrade_label->setString(CCString::createWithFormat(myLoc->getLocalForKey(kMyLocalKey_maxLevel), missile_level)->getCString());
		price_type->removeFromParent();
		price_label->setFontSize(12);
		price_label->setString(myLoc->getLocalForKey(kMyLocalKey_endUpgrade));
		price_label->setPosition(ccpFromSize(price_back->getContentSize()/2.f));
		price_back->setPositionY(upgrade_label->getContentSize().height/2.f);
		price_back->setPositionX(price_back->getPositionX() + 5);
	}
	else
	{
		upgrade_label->setString(CCString::createWithFormat(myLoc->getLocalForKey(kMyLocalKey_upgradeLevelValue2), missile_level+1)->getCString());
		
		if(mySGD->getGoodsValue(kGoodsType_pass3) > 0)
		{
			CCNode* parent_node = price_type->getParent();
			CCPoint t_position = price_type->getPosition();
			price_type->removeFromParent();
			price_type = CCSprite::create("pass_ticket3.png");
			price_type->setPosition(t_position);
			parent_node->addChild(price_type);
			
			CCScale9Sprite* pass_count_case = CCScale9Sprite::create("mainflow_new2.png", CCRectMake(0, 0, 20, 20), CCRectMake(9, 9, 2, 2));
			pass_count_case->setPosition(ccpFromSize(price_type->getContentSize()/2.f) + ccp(9,6));
			price_type->addChild(pass_count_case);
			
			CCLabelTTF* pass_count_label = CCLabelTTF::create(ccsf("%d", mySGD->getGoodsValue(kGoodsType_pass3)), mySGD->getFont().c_str(), 8);
			pass_count_label->setColor(ccc3(255, 255, 255));
			float min_width = 10+pass_count_label->getContentSize().width;
			if(min_width < 20)
				min_width = 20;
			pass_count_case->setContentSize(CCSizeMake(min_width, 20));
			pass_count_label->setPosition(ccp(pass_count_case->getContentSize().width/2.f-0.5f, pass_count_case->getContentSize().height/2.f+0.5f));
			pass_count_case->addChild(pass_count_label);
			
			price_label->setString(myLoc->getLocalForKey(kMyLocalKey_free));
		}
		else
		{
			CCNode* parent_node = price_type->getParent();
			CCPoint t_position = price_type->getPosition();
			price_type->removeFromParent();
			price_type = CCSprite::create("price_gold_img.png");
			price_type->setPosition(t_position);
			parent_node->addChild(price_type);
			
			price_label->setString(KS::insert_separator(CCString::createWithFormat("%d", mySGD->getSelectedCharacterHistory().nextPrice.getV())->getCString()).c_str());
		}
	}
	
	upgrade_func();
	
	addChild(KSTimer::create(0.1f, [=](){
		CCSprite* upgrade_effect_2 = CCSprite::create("missile_upgrade_2.png");
		upgrade_effect_2->setScaleX(0.f);
		upgrade_effect_2->setPosition(ccp(80,-14));
		m_container->addChild(upgrade_effect_2);
		
		KSLabelTTF* effect_label = KSLabelTTF::create(myLoc->getLocalForKey(kMyLocalKey_power), mySGD->getFont().c_str(), 11);
		effect_label->enableOuterStroke(ccBLACK, 1.f);
		effect_label->setPosition(ccp(38,47));
		upgrade_effect_2->addChild(effect_label);
		
		KSLabelTTF* upper_damage = KSLabelTTF::create(CCString::createWithFormat("+%d", after_damage-before_damage)->getCString(), mySGD->getFont().c_str(), 20);
		upper_damage->setColor(ccc3(0,222,255));
		upper_damage->enableOuterStroke(ccBLACK, 1.f);
		upper_damage->setPosition(ccp(upgrade_effect_2->getContentSize().width/2.f, upgrade_effect_2->getContentSize().height/2.f-8));
		upgrade_effect_2->addChild(upper_damage);
		
		addChild(KSGradualValue<float>::create(0.f, 1.f, 0.2f, [=](float t){
			upgrade_effect_2->setScaleX(t);
		}, [=](float t){
			upgrade_effect_2->setScaleX(1.f);
			
			CCMoveTo* t_move1 = CCMoveTo::create(0.3f, ccp(80, 12));
			CCMoveTo* t_move2 = CCMoveTo::create(0.15f, ccp(80, -8));
			CCSequence* t_seq1 = CCSequence::createWithTwoActions(t_move1, t_move2);
			CCRepeat* t_repeat = CCRepeat::create(t_seq1, 3);
			
			CCMoveTo* t_move = CCMoveTo::create(0.3f, ccp(80, 12));
			CCScaleTo* t_scale = CCScaleTo::create(0.3f, 0.f, 1.f);
			CCSpawn* t_spawn = CCSpawn::createWithTwoActions(t_move, t_scale);
			
			CCCallFunc* t_call = CCCallFunc::create(upgrade_effect_2, callfunc_selector(CCSprite::removeFromParent));
			
			CCSequence* t_seq = CCSequence::create(t_repeat, t_spawn, t_call, NULL);
			
			upgrade_effect_2->runAction(t_seq);
			
			is_menu_enable = true;
		}));
	}));
}
