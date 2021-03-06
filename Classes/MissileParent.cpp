//
//  MissileParent.cpp
//  DrawingJack
//
//  Created by 사원3 on 12. 12. 6..
//
//

#include "MissileParent.h"
#include "LogData.h"
#include "KSCircleBase.h"
#include "StageImgLoader.h"
#include "AttackPattern.h"
#include "StarGoldData.h"
#include "StoneMissile.h"
#include "ks19937.h"
#include <boost/format.hpp>

void MissileParent::bombCumber( CCObject* target )
{
	KSCumberBase* cumber = (KSCumberBase*)target;
	bool cancelSound = false;
	if(myGD->getCommunication("CP_getMainCumberSheild") == 0)
	{
		bool canceled = false;
		for(auto i : cumber->getCharges())
		{
			i->cancelCharge();
			canceled = true;
			
			cancelSound = true;
		}
		
		if(canceled)
		{
			myGD->communication("Main_hideScreenSideWarning"); // 화면에 빨간 테두리 지우는 함수
		}

		//if(target == myGD->getCommunicationNode("CP_getMainCumberPointer"))
		//{
			//for(int i=0;i<chargeArray->count();i++)
			//{
				//ChargeParent* t_cn = (ChargeNode*)chargeArray->objectAtIndex(i);
				//t_cn->cancelCharge();
			//}
		//}
	}
	
	
	if(cumber->getAttackPattern())
	{
		auto temp = cumber->getAttackPattern();
		temp->stopMyAction();
		cumber->setAttackPattern(nullptr);
		cancelSound = true;
	}
	
	
	if(cancelSound)
	{
		AudioEngine::sharedInstance()->playEffect(CCString::createWithFormat("ment_pattern_cancel%d.mp3", ks19937::getIntValue(1, 4))->getCString(), false, true);
//		AudioEngine::sharedInstance()->playEffect(CCString::createWithFormat("ment_pattern_cancel%d.mp3", rand()%4+1)->getCString());
	}
	//if(target == myGD->getCommunicationNode("CP_getMainCumberPointer") && saveAP)
	//{
		//saveAP->stopMyAction();
		//endIngActionAP();
	//}
}

void MissileParent::createJackMissile( int jm_type, int cmCnt, float missile_speed, CCPoint missile_position )
{

	return;
//	CCLOG("createJackMissile inner : %d, %d, %.2f", jm_type, cmCnt, missile_speed);
	
	int card_number;
	card_number = myDSH->getIntegerForKey(kDSH_Key_selectedCard);
	
	if(card_number > 0)
	{
		if(jm_type%10 >= 0 && jm_type%10 <= 3)
		{
//			CCLOG("base JackMissile");
			vector<KSCumberBase*> subCumberArray = myGD->getSubCumberVector();
			int cumberCnt = subCumberArray.size();
			int random_value;
			
			int boss_count = myGD->getMainCumberCount();
			
			for(int i=0;i<cmCnt;i++)
			{
				if(i < boss_count)
				{
					JackMissile* t_jm = JM_BasicMissile::create(myGD->getMainCumberCCNodeVector()[i], jm_type, missile_speed, missile_position);
					jack_missile_node->addChild(t_jm);
					t_jm->startMoving();
				}
				else
				{
					if(cumberCnt == 0)
					{
						JackMissile* t_jm = JM_BasicMissile::create(myGD->getMainCumberCCNodeVector()[0], jm_type, missile_speed, missile_position);
						jack_missile_node->addChild(t_jm);
						t_jm->startMoving();
					}
					else
					{
						random_value = rand()%cumberCnt;
						
						JackMissile* t_jm = JM_BasicMissile::create((CCNode*)subCumberArray[random_value], jm_type, missile_speed, missile_position);
						jack_missile_node->addChild(t_jm);
						t_jm->startMoving();
					}
				}
			}
			
			CCSprite* card_img = CCSprite::createWithTexture(mySIL->addNakedImage(CCString::createWithFormat("card%d_thumbnail.png", card_number)->getCString()));
			card_img->setScale(0.f);
			card_img->setPosition(missile_position);
			jack_missile_node->addChild(card_img);
			
			CCScaleTo* t_scale = CCScaleTo::create(0.2f, 0.5f/myGD->game_scale);
			CCDelayTime* t_delay = CCDelayTime::create(0.8f);
			CCFadeTo* t_fade = CCFadeTo::create(0.5f, 0);
			CCCallFunc* t_call = CCCallFunc::create(card_img, callfunc_selector(CCSprite::removeFromParent));
			CCSequence* t_seq = CCSequence::create(t_scale, t_delay, t_fade, t_call, NULL);
			card_img->runAction(t_seq);
			
			CCSprite* no_img = CCSprite::create("cardchange_noimg.png");
			no_img->setScale(1.f/0.73f);
			no_img->setPosition(ccp(card_img->getContentSize().width/2.f, card_img->getContentSize().height/2.f));
			card_img->addChild(no_img);
			
			CCDelayTime* t_delay2 = CCDelayTime::create(1.f);
			CCFadeTo* t_fade2 = CCFadeTo::create(0.5f, 0);
			CCSequence* t_seq2 = CCSequence::create(t_delay2, t_fade2, NULL);
			no_img->runAction(t_seq2);
		}
		else if(jm_type%10 >= 4 && jm_type%10 <= 6)
		{
//			CCLOG("Upgrade JackMissile");
			UM_creator* t_c = UM_creator::create(cmCnt, jm_type, missile_speed, missile_position);
			jack_missile_node->addChild(t_c);
			t_c->startPetCreate();
			
			float t_missile_speed = missile_speed;
			
			if(t_missile_speed < 2.f)
				t_missile_speed = 2.f;
			else if(t_missile_speed > 9.f)
				t_missile_speed = 9.f;
			else
				t_missile_speed = t_missile_speed;
			int shoot_frame = t_missile_speed*3;
			shoot_frame *= cmCnt;
			
			CCSprite* card_img = CCSprite::createWithTexture(mySIL->addNakedImage(CCString::createWithFormat("card%d_thumbnail.png", card_number)->getCString()));
			card_img->setScale(0.f);
			card_img->setPosition(missile_position);
			jack_missile_node->addChild(card_img);
			
			CCScaleTo* t_scale = CCScaleTo::create(0.2f, 0.5f/myGD->game_scale);
			CCDelayTime* t_delay = CCDelayTime::create(0.8f);
			CCFadeTo* t_fade = CCFadeTo::create(shoot_frame/60.f+0.5f, 0);
			CCCallFunc* t_call = CCCallFunc::create(card_img, callfunc_selector(CCSprite::removeFromParent));
			CCSequence* t_seq = CCSequence::create(t_scale, t_delay, t_fade, t_call, NULL);
			card_img->runAction(t_seq);
			
			CCSprite* no_img = CCSprite::create("cardchange_noimg.png");
			no_img->setScale(1.f/0.73f);
			no_img->setPosition(ccp(card_img->getContentSize().width/2.f, card_img->getContentSize().height/2.f));
			card_img->addChild(no_img);
			
			CCDelayTime* t_delay2 = CCDelayTime::create(1.f);
			CCFadeTo* t_fade2 = CCFadeTo::create(shoot_frame/60.f+0.5f, 0);
			CCSequence* t_seq2 = CCSequence::create(t_delay2, t_fade2, NULL);
			no_img->runAction(t_seq2);
		}
	}
	else
	{
		CCSprite* no_img = CCSprite::create("cardchange_noimg.png");
		no_img->setScale(0.5f/myGD->game_scale);
		no_img->setPosition(missile_position);
		jack_missile_node->addChild(no_img);
		
		CCDelayTime* t_delay = CCDelayTime::create(1.f);
		CCFadeTo* t_fade2 = CCFadeTo::create(0.5f, 0);
		CCSequence* t_seq2 = CCSequence::create(t_delay, t_fade2, NULL);
		no_img->runAction(t_seq2);
	}
}

void MissileParent::createJackMissileWithStone(StoneType stoneType, int grade, int level, float missileNumbers, CCPoint initPosition, int missile_damage)
{
	int power = missile_damage;
	AttackOption ao = getAttackOption(stoneType, grade);
	int missileNumbersInt = floor(missileNumbers);
	stoneType = StoneType::kStoneType_guided;
	if(stoneType == StoneType::kStoneType_guided)
	{
		addChild(KSSchedule::create([=](float dt)
																{
																	return false; // stop
																}));
		for(int i=0; i<missileNumbersInt; i++)
		{
			auto creator = [=](){
				string fileName = boost::str(boost::format("jack_missile_%||.png") % ((grade - 1) * 5 + level));
				KSCumberBase* target = nullptr;
				std::vector<KSCumberBase*> targets;
				targets.insert(targets.end(), myGD->getMainCumberVector().begin(), myGD->getMainCumberVector().end());
				targets.insert(targets.end(), myGD->getSubCumberVector().begin(), myGD->getSubCumberVector().end());
				target = targets[ks19937::getIntValue(0, targets.size() - 1)];
							
				CCPoint minDis = ccp(99999, 99999);
				KSCumberBase* nearCumber = myGD->getMainCumberVector()[0];
				for(int i = 0; i<myGD->getMainCumberCount();i++){
					KSCumberBase* cumber = myGD->getMainCumberVector()[i];
					CCPoint nowDis = cumber->getPosition()-myGD->getJackPoint().convertToCCP();
					if(ccpLength(nowDis)<ccpLength(minDis))
					{
						nearCumber=cumber;
						minDis = nowDis;
					}
				}
				
				for(int i = 0; i<myGD->getSubCumberCount();i++){
					KSCumberBase* cumber = myGD->getSubCumberVector()[i];
					CCPoint nowDis = cumber->getPosition()-myGD->getJackPoint().convertToCCP();
					if(ccpLength(nowDis)<ccpLength(minDis))
					{
						nearCumber=cumber;
						minDis = nowDis;
					}
				}
				
				int random_value = rand()%7 - 3;
				float random_float = random_value/10.f;
				bool selfRotation = false;
				if(grade == 1 || grade == 4)
					selfRotation = true;
				random_float = 0.f;
				
				GuidedMissile* gm = GuidedMissile::create(nearCumber, myGD->getJackPoint().convertToCCP(),
																									fileName,
																									1.4f+random_float + grade / 10.f, power, 10 + 15 * grade,
																									ao, selfRotation
																									);
				gm->beautifier(grade, level);
				jack_missile_node->addChild(gm);
			};
			addChild(KSTimer::create(0.30 * (i + 1), [=](){
				creator();
			}));
		}
	}
	else if(stoneType == StoneType::kStoneType_mine)
	{
		for(int i=0; i<missileNumbersInt; i++)
		{
			IntPoint mapPoint;
			bool found = myGD->getEmptyRandomPoint(&mapPoint, 5);
			if(found == true)
			{
				MineAttack* ma = MineAttack::create(initPosition, ip2ccp(mapPoint), 10 + 3 * grade, power, ao);
				jack_missile_node->addChild(ma);	
			}
		}
	}
	else if(stoneType == StoneType::kStoneType_laser)
	{
		//LaserAttack* la = LaserAttack::create(0, 400, 33.f, AttackOption::kNoOption);
		LaserWrapper* lw = LaserWrapper::create(2 + MIN((grade-1), 3), 60*2 + missileNumbers * 60, 
																						power / 3.f, ao);
		jack_missile_node->addChild(lw);
	}

	else if(stoneType == StoneType::kStoneType_range)
	{
		RangeAttack* ra = RangeAttack::create(initPosition, 30 + missileNumbers * 10, 60 * 3 + 60 * grade,
																				 	power / 3.f, 30 - 3 * grade, ao);
		addChild(ra);
	}

	else if(stoneType == StoneType::kStoneType_global)
	{
		for(int i=0; i<=4 + 2 * missileNumbersInt; i++)
		{
			RandomBomb* rb = RandomBomb::create(40 + grade * 20, power, ao);
			addChild(rb);
		}
	}
	else if(stoneType == StoneType::kStoneType_spirit)
	{
		for(int i=0; i<missileNumbersInt; i++)
		{
			IntPoint mapPoint2;
			bool found2 = myGD->getEmptyRandomPoint(&mapPoint2, 5);
			if(found2 == true)
			{
				string fileName = boost::str(boost::format("me_pet%||.ccbi") % level);
				SpiritAttack* sa = SpiritAttack::create(initPosition, ip2ccp(mapPoint2), fileName, 
																								3 + grade * 1, power / 2.f, 1.2f, 30, ao);
				jack_missile_node->addChild(sa);	
			}
		}
	}
	else if(stoneType == StoneType::kStoneType_spread)
	{
		addChild(KSIntervalCall::create(20, missileNumbers, [=](int seq){
			int adderForGrade = 0;
			if(grade == 1){
				adderForGrade = 4;
			}
			else if(grade == 2){
				adderForGrade = 6;
			}
			else if(grade == 3){
				adderForGrade = 8;
			}
			else if(grade == 4){
				adderForGrade = 12;
			}
			else if(grade == 5){
				adderForGrade = 16;
			}
			else{
				adderForGrade = 0;
			}
			string fileName = boost::str(boost::format("me_redial%||.ccbi") % level);
			KSCumberBase* target = nullptr;
			std::vector<KSCumberBase*> targets;
			targets.insert(targets.end(), myGD->getMainCumberVector().begin(), myGD->getMainCumberVector().end());
			targets.insert(targets.end(), myGD->getSubCumberVector().begin(), myGD->getSubCumberVector().end());
			target = targets[ks19937::getIntValue(0, targets.size() - 1)];
			SpreadMissile* sm = SpreadMissile::create(target, initPosition,
																								fileName,
																								2.2f + 0.3f * grade, power, adderForGrade, ao);
			jack_missile_node->addChild(sm);
			
		}));
	}


	
	

	
}
AttackOption MissileParent::getAttackOption(StoneType st, int grade)
{
	
	if(st == StoneType::kStoneType_guided)
	{
		return AttackOption::kStiffen;
	}
	else if(st == StoneType::kStoneType_spread)
	{
		return AttackOption::kStiffen;
	}
	else if(st == StoneType::kStoneType_laser)
	{
		return AttackOption::kStiffen;
	}
	else if(st == StoneType::kStoneType_mine)
	{
		return AttackOption::kStiffen;
	}
	else if(st == StoneType::kStoneType_spirit)
	{
		return AttackOption::kStiffen;
	}
	else if(st == StoneType::kStoneType_range)
	{
		return AttackOption::kStiffen;
	}

	else if(st == StoneType::kStoneType_global)
	{
		return AttackOption::kStiffen;
	}
// 등급에 따라 옵션이 붙게 하는 코든데 없앰.
#if 0 
	if(st == StoneType::kStoneType_guided)
	{
		switch(grade)
		{
			case 1:
				return AttackOption::kNoOption;
			case 2:
				return AttackOption::kGold;
			case 3:
				return AttackOption::kCancelCasting | AttackOption::kGold;
			case 4:
				return AttackOption::kCancelCasting | AttackOption::kGold | AttackOption::kStiffen;
			case 5:
				return AttackOption::kCancelCasting | AttackOption::kGold | AttackOption::kStiffen | AttackOption::kPlusScore;
			default:
				
				return AttackOption::kNoOption;
		}
	}
	else if(st == StoneType::kStoneType_spread)
	{
		switch(grade)
		{
			case 1:
				return AttackOption::kNoOption;
			case 2:
				return AttackOption::kGold;
			case 3:
				return AttackOption::kGold | AttackOption::kCancelCasting;
			case 4:
				return AttackOption::kGold | AttackOption::kCancelCasting | AttackOption::kStiffen;
			case 5:
				return AttackOption::kGold | AttackOption::kCancelCasting | AttackOption::kStiffen | AttackOption::kPlusScore;
			default:
				
				return AttackOption::kNoOption;
		}
	}
	else if(st == StoneType::kStoneType_laser)
	{
		switch(grade)
		{
			case 1:
				return AttackOption::kNoOption;
			case 2:
				return AttackOption::kGold;
			case 3:
				return AttackOption::kGold | AttackOption::kCancelCasting;
			case 4:
				return AttackOption::kGold | AttackOption::kCancelCasting | AttackOption::kUnbeatable;
			case 5:
				return AttackOption::kGold | AttackOption::kCancelCasting | AttackOption::kUnbeatable | AttackOption::kPlusScore;
			default:
				
				return AttackOption::kNoOption;
		}
	}
	else if(st == StoneType::kStoneType_mine)
	{
		switch(grade)
		{
			case 1:
				return AttackOption::kNoOption;
			case 2:
				return AttackOption::kGold;
			case 3:
				return AttackOption::kGold | AttackOption::kCancelCasting;
			case 4:
				return AttackOption::kGold | AttackOption::kCancelCasting | AttackOption::kMonsterSpeedDown;
			case 5:
				return AttackOption::kGold | AttackOption::kCancelCasting | AttackOption::kMonsterSpeedDown | AttackOption::kPlusScore;
			default:
				
				return AttackOption::kNoOption;
		}
	}
	else if(st == StoneType::kStoneType_spirit)
	{
		switch(grade)
		{
			case 1:
				return AttackOption::kNoOption;
			case 2:
				return AttackOption::kGold;
			case 3:
				return AttackOption::kGold | AttackOption::kCancelCasting;
			case 4:
				return AttackOption::kGold | AttackOption::kCancelCasting | AttackOption::kJackSpeedUp;
			case 5:
				return AttackOption::kGold | AttackOption::kCancelCasting | AttackOption::kJackSpeedUp | AttackOption::kPlusScore;
			default:
				
				return AttackOption::kNoOption;
		}
	}


	else if(st == StoneType::kStoneType_range)
	{
		switch(grade)
		{
			case 1:
				return AttackOption::kNoOption;
			case 2:
				return AttackOption::kGold;
			case 3:
				return AttackOption::kGold | AttackOption::kCancelCasting;
			case 4:
				return AttackOption::kGold | AttackOption::kCancelCasting | AttackOption::kJackSpeedUp;
			case 5:
				return AttackOption::kGold | AttackOption::kCancelCasting | AttackOption::kJackSpeedUp | AttackOption::kPlusScore;
			default:
				
				return AttackOption::kNoOption;
		}
	}

	else if(st == StoneType::kStoneType_global)
	{
		switch(grade)
		{
			case 1:
				return AttackOption::kNoOption;
			case 2:
				return AttackOption::kGold;
			case 3:
				return AttackOption::kGold | AttackOption::kCancelCasting;
			case 4:
				return AttackOption::kGold | AttackOption::kCancelCasting | AttackOption::kPoisonedNiddle;
			case 5:
				return AttackOption::kGold | AttackOption::kCancelCasting | AttackOption::kPoisonedNiddle | AttackOption::kPlusScore;
			default:
				
				return AttackOption::kNoOption;
		}
	}
#endif
	return AttackOption::kNoOption;
}
int MissileParent::getJackMissileCnt()
{
	return jack_missile_node->getChildrenCount();
}

void MissileParent::removeAllPattern()
{
	pattern_container->removeAllChildren();
}
void MissileParent::subOneDie()
{
	vector<KSCumberBase*> subCumberArray = myGD->getSubCumberVector();
	std::mt19937 rEngine(std::random_device{}());
	std::uniform_int_distribution<> r(0, subCumberArray.size() - 1);
	if(subCumberArray.size() > 0)
	{
		JackMissile* t_jm = JM_BasicMissile::create((CCNode*)subCumberArray[r(rEngine)], 80+kMyElementalLife, 999999.f);
		addChild(t_jm);
		t_jm->startMoving();
	}
	else
	{
		
		JackMissile* t_jm = JM_BasicMissile::create((CCNode*)myGD->getMainCumberVector()[0], 80+kMyElementalLife, mySGD->getSelectedCharacterHistory().power.getV()*5.f);
		addChild(t_jm);
		t_jm->startMoving();
	}
}

//void MissileParent::endIngActionAP()
//{
//	CCLOG("saveAP = null");
////	saveAP = NULL;
//}


int MissileParent::attackWithKSCode(CCPoint startPosition, std::string &patternDParam, KSCumberBase* cb, bool exe)
{
	Json::Value patternData;
	int valid = 1;
	int invalid = 0;
	// Attack Queue 가 있으면 patternD 무시하고 Attack Queue 에서 하나하나 빼서 씀.
	if(cb->getAttackQueue().empty() == false && cb->getAttackQueue().size()>0)
	{
//        CCLOG("A");
		patternData = cb->getAttackQueue().front();
		cb->getAttackQueue().pop_front();
	}  
	else
	{
		// 사냥꾼 미션이고 부하몹이 0 이하라면 부하몹 생성.
		if(mySD->getClearCondition() == kCLEAR_subCumberCatch && myGD->getSubCumberCount() <= 0)
		{
//			CCLOG("B");
			Json::Reader reader;
			Json::Value createCumberPattern;
			reader.parse(R"({
									 "atype" : "special",
									 "childs" : 1,
									 "name" : "부하몹리젠",
									 "pattern" : 1020,
									 "percent" : 1,
									 "target" : "no"
									 } )", patternData);
		}
		else
		{
			patternData = patternDParam;
		}
	}
    
	if(patternData.isNull() || patternData.asString()=="" || patternData.isBool()){
//		CCLOG("it's null in attackWithKSCode");
		patternData = patternDParam;
	}
	
//	KS::KSLog("%", patternData);
	if(patternData["pattern"].asInt() == 1020)
	{
		Json::Reader reader;
		Json::Value root;
		reader.parse(mySDS->getStringForKey(kSDF_stageInfo, mySD->getSilType(), "junior"), root);
		
		// 기본값으로 서버에서 설정된 부하몹 개수로 함.
		int n = MIN(patternData.get("maxchilds", root.size()).asInt() - myGD->getSubCumberCount(), patternData.get("childs", 1).asInt());
		if(n <= 0) // 부하몹 생성할것이 없다면 false 리턴함.
		{
			return invalid;
		}
	}
	
	std::string patternD = patternData.asString();
//	CCLOG(".. %s", patternDParam.c_str());
//	CCLOG("%s", boost::str(boost::format("%||") % patternData).c_str());
	int castFrame = patternData.get("castframe", 120).asInt();
	// 캐스팅 실패하면 캐스팅 시간 점점 줄음.
	castFrame = MAX(30, castFrame - (castFrame * 0.1f)* cb->getCastingCancelCount());
	
	
	std::string pattern = patternData["pattern"].asString();
	std::string atype = patternData["atype"].asString();
	auto castBranch = [=](const std::string atype, std::function<void(CCObject*)> func, const std::string& warningFileName)
	{
		if(atype == "crash")
		{
			CrashChargeNodeLambda* t_ccn =
			CrashChargeNodeLambda::create(startPosition, castFrame,
										  func, cb, patternData);
			t_ccn->setChargeColor(ccc4f(0.00, 0.00, 0.00, 1.00));
			cb->getParent()->addChild(t_ccn);
			t_ccn->startCharge();
//			CCLOG("%x", t_ccn);
			
			cb->getCharges().push_back(t_ccn);
//			cb->m_cumberState |= kCumberStateAttack; // 지금 공격중이라는 정보 넣음.
//			m_charges.push_back(t_ccn);
//			cb->setChargeParent(t_ccn);
		}
		else if(atype == "special")
		{
			SpecialChargeNodeLambda* t_ccn =
			SpecialChargeNodeLambda::create(startPosition, castFrame,
											func, cb, patternData);
			
			t_ccn->setChargeColor(ccc4f(0.80, 1.00, 1.00, 1.00));
			cb->getParent()->addChild(t_ccn);
			t_ccn->startCharge();
			
			cb->getCharges().push_back(t_ccn);
//			cb->m_cumberState |= kCumberStateAttack; // 지금 공격중이라는 정보 넣음.
//			cb->setChargeParent(t_ccn);
		}
		else // normal
		{
			ChargeNodeLambda* t_ccn =
			ChargeNodeLambda::create(startPosition, castFrame,
									 func, cb, patternData);
			
			t_ccn->setChargeColor(ccc4f(0.80, 1.00, 1.00, 1.00));
			cb->getParent()->addChild(t_ccn);
			t_ccn->startCharge();
			
			cb->getCharges().push_back(t_ccn);
//			cb->m_cumberState |= kCumberStateAttack; // 지금 공격중이라는 정보 넣음.

//			cb->setChargeParent(t_ccn);
		}
		cb->m_lastCastTime = cb->m_cumberTimer;
		cb->setDamageMeasure(0.f);
		myGD->communication("Main_showScreenSideWarning"); // 화면에 빨간 테두리 만드는 함수
		myGD->showDetailMessage(warningFileName, "w");
		myGD->communication("Main_showThumbWarning", startPosition);
	};
	string warningFileName = "warning_" + pattern + ".ccbi";
	
	if(cb->m_cumberTimer - 1.f >= cb->m_lastCastTime)
	{
		if(pattern == "1")
		{
			if(exe)
			{
				startFirePosition = startPosition;
				
				//			myGD->communication("CP_setMainCumberState", CUMBER_STATE::CUMBERSTATEATTACKREADY); // cumberStateAttackReady
				auto func = [=](CCObject* cb)
				{
					UnusedMissile1* t = UnusedMissile1::create(startFirePosition, dynamic_cast<KSCumberBase*>(cb), patternD);
					pattern_container->addChild(t);
					KSCumberBase* cumber = (KSCumberBase*)cb;
					cumber->setAttackPattern(t);
				};
				castBranch(atype, func, warningFileName);
			}
		}
		
		else if(pattern == "2")
		{
			if(exe)
			{
				startFirePosition = startPosition;
				auto func = [=](CCObject* cb)
				{
					UnusedMissile6* t = UnusedMissile6::create(startFirePosition, dynamic_cast<KSCumberBase*>(cb), patternD);
					pattern_container->addChild(t);
					KSCumberBase* cumber = (KSCumberBase*)cb;
					cumber->setAttackPattern(t);
					
				};
				castBranch(atype, func, warningFileName);
			}
		}
		else if(pattern == "3")
		{
			if(exe)
			{
				startFirePosition = startPosition;
				auto func = [=](CCObject* cb)
				{
					UnusedMissile7* t = UnusedMissile7::create(startFirePosition, dynamic_cast<KSCumberBase*>(cb), patternD);
					pattern_container->addChild(t);
					KSCumberBase* cumber = (KSCumberBase*)cb;
					cumber->setAttackPattern(t);
					
				};
				castBranch(atype, func, warningFileName);
				
			}
		}
		else if(pattern == "4")
		{
			if(exe)
			{
				startFirePosition = startPosition;
				auto func = [=](CCObject* cb)
				{
					UnusedMissile8* t = UnusedMissile8::create(startFirePosition, dynamic_cast<KSCumberBase*>(cb), patternD);
					pattern_container->addChild(t);
					KSCumberBase* cumber = (KSCumberBase*)cb;
					cumber->setAttackPattern(t);
					
				};
				castBranch(atype, func, warningFileName);
				
			}
		}
		else if(pattern == "5")
		{
			if(exe)
			{
				startFirePosition = startPosition;
				auto func = [=](CCObject* cb)
				{
					UnusedMissile9* t = UnusedMissile9::create(startFirePosition, dynamic_cast<KSCumberBase*>(cb), patternD);
					pattern_container->addChild(t);
					KSCumberBase* cumber = (KSCumberBase*)cb;
					cumber->setAttackPattern(t);
					
				};
				castBranch(atype, func, warningFileName);
				
			}
		}
		else if(pattern == "6")
		{
			if(exe)
			{
				startFirePosition = startPosition;
				auto func = [=](CCObject* cb)
				{
					UnusedMissile10* t = UnusedMissile10::create(startFirePosition, dynamic_cast<KSCumberBase*>(cb), patternD);
					pattern_container->addChild(t);
					KSCumberBase* cumber = (KSCumberBase*)cb;
					cumber->setAttackPattern(t);
					
				};
				castBranch(atype, func, warningFileName);
				
				
			}
		}
		else if(pattern == "7")
		{
			if(exe)
			{
				startFirePosition = startPosition;
				auto func = [=](CCObject* cb)
				{
					UnusedMissile11* t = UnusedMissile11::create(startFirePosition, dynamic_cast<KSCumberBase*>(cb), patternD);
					pattern_container->addChild(t);
					KSCumberBase* cumber = (KSCumberBase*)cb;
					cumber->setAttackPattern(t);
					
				};
				castBranch(atype, func, warningFileName);
				
				
			}
		}
		else if(pattern == "8")
		{
			if(exe)
			{
				startFirePosition = startPosition;
				auto func = [=](CCObject* cb)
				{
					Mugunghwa* t = Mugunghwa::create(startFirePosition, dynamic_cast<KSCumberBase*>(cb), patternD);
					pattern_container->addChild(t);
					KSCumberBase* cumber = (KSCumberBase*)cb;
					cumber->setAttackPattern(t);
					
				};
				castBranch(atype, func, warningFileName);
			}
		}
		else if(pattern == "9")
		{
			if(exe)
			{
				startFirePosition = startPosition;
				auto func = [=](CCObject* cb)
				{
					CaromWrapper* t = CaromWrapper::create(startFirePosition, dynamic_cast<KSCumberBase*>(cb), patternD);
					pattern_container->addChild(t);
				};
				castBranch(atype, func, warningFileName);
				
			}
		}
		
		else if(pattern == "101")
		{
			if(exe)
			{
				
				startFirePosition = startPosition;
				auto func = [=](CCObject* cb)
				{
					UnusedMissile1* t = UnusedMissile1::create(startFirePosition, dynamic_cast<KSCumberBase*>(cb), patternD);
					pattern_container->addChild(t);
					KSCumberBase* cumber = (KSCumberBase*)cb;
					cumber->setAttackPattern(t);
					
				};
				castBranch(atype, func, warningFileName);
				
				
			}
		}
		else if(pattern == "102")
		{
			if(exe)
			{
				startFirePosition = startPosition;
				auto func = [=](CCObject* cb)
				{
					UnusedMissile2* t = UnusedMissile2::create(startFirePosition, dynamic_cast<KSCumberBase*>(cb), patternD);
					pattern_container->addChild(t);
					KSCumberBase* cumber = (KSCumberBase*)cb;
					cumber->setAttackPattern(t);
					
				};
				castBranch(atype, func, warningFileName);
				
			}
		}
		else if(pattern == "103")
		{
			if(exe)
			{
				startFirePosition = startPosition;
				auto func = [=](CCObject* cb)
				{
					UnusedMissile3* t = UnusedMissile3::create(startFirePosition, dynamic_cast<KSCumberBase*>(cb), patternD);
					pattern_container->addChild(t);
					KSCumberBase* cumber = (KSCumberBase*)cb;
					cumber->setAttackPattern(t);
					
				};
				castBranch(atype, func, warningFileName);
			}
		}
		else if(pattern == "104")
		{
			if(exe)
			{
				startFirePosition = startPosition;
				auto func = [=](CCObject* cb)
				{
					UnusedMissile4* t = UnusedMissile4::create(startFirePosition, dynamic_cast<KSCumberBase*>(cb), patternD);
					pattern_container->addChild(t);
					KSCumberBase* cumber = (KSCumberBase*)cb;
					cumber->setAttackPattern(t);
					
				};
				castBranch(atype, func, warningFileName);
			}
		}
		else if(pattern == "105") // 나무 토막
		{
			if(exe)
			{
				startFirePosition = startPosition;
				
				//			myGD->communication("CP_setMainCumberState", CUMBER_STATE::CUMBERSTATEATTACKREADY); // cumberStateAttackReady
				auto func = [=](CCObject* cb)
				{
					SawWrapper* t = SawWrapper::create(startFirePosition, dynamic_cast<KSCumberBase*>(cb), patternD);
					pattern_container->addChild(t);
				};
				castBranch(atype, func, warningFileName);
				
				
			}
		}
		else if(pattern == "106") // 사과 던지기.
		{
			if(exe)
			{
				startFirePosition = startPosition;
				auto func = [=](CCObject* cb)
				{
					SmallSawWrapper* t = SmallSawWrapper::create(startFirePosition, dynamic_cast<KSCumberBase*>(cb), patternD);
					pattern_container->addChild(t);
				};
				castBranch(atype, func, warningFileName);
				
			}
		}
		else if(pattern == "107") // 태양광선.
		{
			if(exe)
			{
				startFirePosition = startPosition;
				auto func = [=](CCObject* cb)
				{
					CrashLazerWrapper* t = CrashLazerWrapper::create(startFirePosition, dynamic_cast<KSCumberBase*>(cb), patternD);
					pattern_container->addChild(t);
				};
				castBranch(atype, func, warningFileName);
				
			}
		}
		else if(pattern == "108") // 다용도
		{
			if(exe)
			{
				startFirePosition = startPosition;
				auto func = [=](CCObject* cb)
				{
					CommonBulletPattern* t = CommonBulletPattern::create(startFirePosition, dynamic_cast<KSCumberBase*>(cb), patternD);
					pattern_container->addChild(t);
				};
				castBranch(atype, func, warningFileName);
			}
		}
		else if(pattern == "109") // 개돌
		{
			if(exe)
			{
				startFirePosition = startPosition;
				auto func = [=](CCObject* cb)
				{
					KSCumberBase* t = dynamic_cast<KSCumberBase*>(cb);
					
					int totalFrame = patternData.get("totalframe", 300).asInt();
					t->furyModeOn(totalFrame);
				};
				castBranch(atype, func, warningFileName);
				
			}
		}
		else if(pattern == "110") // 폭죽
		{
			if(exe)
			{
				startFirePosition = startPosition;
				auto func = [=](CCObject* cb)
				{
					FireWorkWrapper* t = FireWorkWrapper::create(startFirePosition, dynamic_cast<KSCumberBase*>(cb), patternD);
					pattern_container->addChild(t);
				};
				castBranch(atype, func, warningFileName);
			}
		}
		else if(pattern == "111") // 움직이는 해바라기
		{
			if(exe)
			{
				startFirePosition = startPosition;
				auto func = [=](CCObject* cb)
				{
					MovingSunflowerWrapper* t = MovingSunflowerWrapper::create(startFirePosition, dynamic_cast<KSCumberBase*>(cb), patternD);
					pattern_container->addChild(t);
					
				};
				castBranch(atype, func, warningFileName);
				
				
			}
		}
		else if(pattern == "112") // 폭탄 여러개 던지기
		{
			if(exe)
			{
				startFirePosition = startPosition;
				auto func = [=](CCObject* cb)
				{
					ThrowBombWrapper* t = ThrowBombWrapper::create(startFirePosition, dynamic_cast<KSCumberBase*>(cb), patternD);
					pattern_container->addChild(t);
				};
				castBranch(atype, func, warningFileName);
				
			}
		}
		else if(pattern == "113") // 리버 스크럽
		{
			if(exe)
			{
				startFirePosition = startPosition;
				auto func = [=](CCObject* cb)
				{
					ScarabWrapper* t = ScarabWrapper::create(startFirePosition, dynamic_cast<KSCumberBase*>(cb), patternD);
					pattern_container->addChild(t);
				};
				castBranch(atype, func, warningFileName);
				
			}
		}
		else if(pattern == "114") // 닳는 톱니.
		{
			if(exe)
			{
				startFirePosition = startPosition;
				auto func = [=](CCObject* cb)
				{
					RunDownSawWrapper* t = RunDownSawWrapper::create(startFirePosition, dynamic_cast<KSCumberBase*>(cb), patternD);
					pattern_container->addChild(t);
				};
				castBranch(atype, func, warningFileName);
			}
		}
		else if(pattern == "1001")
		{
			if(exe)
			{
				startFirePosition = startPosition;
				auto func = [=](CCObject* cb)
				{
					int totalFrame = patternData.get("totalframe", 400).asInt();
					TornadoWrapper* t_m21 = TornadoWrapper::create(startFirePosition, totalFrame, 1.5f,
																												 dynamic_cast<KSCumberBase*>(cb));
					pattern_container->addChild(t_m21);
					
				};
				castBranch(atype, func, warningFileName);
			}
		}
		
		else if(pattern == "1002")
		{
			if(exe)
			{
				startFirePosition = startPosition;
				auto func = [=](CCObject* cb)
				{
					KSCumberBase* cumber = (KSCumberBase*)cb;
					if(cumber->getSightOutAttack())
					{
						cumber->getSightOutAttack()->updateSightOut();
					}
					else
					{
						int totalFrame = patternData.get("totalframe", 300).asInt();
						SightOutAttack* t_m24 = SightOutAttack::create(totalFrame, cumber);
						pattern_container->addChild(t_m24);
						cumber->setSightOutAttack(t_m24);
					}
					//		SightOutWrapper* t = SightOutWrapper::create(startFirePosition, dynamic_cast<KSCumberBase*>(cb));
					//		pattern_container->addChild(t);
					//
				};
				castBranch(atype, func, warningFileName);
			}
		}
		else if(pattern == "1003")
		{
			if(exe)
			{
				startFirePosition = startPosition;
				auto func = [=](CCObject* cb)
				{
					KSCumberBase* cumber = (KSCumberBase*)cb;
					if(cumber->getCobWebAttack())
					{
						cumber->getCobWebAttack()->updateCobWeb();
					}
					else
					{
						//					int totalFrame = patternData.get("totalframe", 60*4).asInt();
						
						//					Cobweb* t_m23 = Cobweb::create(totalFrame);
						CobWeb* t_m23 = CobWeb::create(startFirePosition, dynamic_cast<KSCumberBase*>(cb), patternD);
						pattern_container->addChild(t_m23);
						cumber->setCobWebAttack(t_m23);
					}
					
					
				};
				castBranch(atype, func, warningFileName);
			}
		}
		else if(pattern == "1004")
		{
			if(exe)
			{
				startFirePosition = startPosition;
				auto func = [=](CCObject* cb)
				{
					//				int random_value = rand()%2 + 1;
					int radius = 80;//pattern.get("radius", 100).asInt();
					int objcnt = patternData.get("totalframe", 240).asInt();
					PrisonPattern* t_m28 = PrisonPattern::create(startFirePosition, radius, objcnt, dynamic_cast<KSCumberBase*>(cb));
					pattern_container->addChild(t_m28);
					t_m28->startMyAction();
					KSCumberBase* cumber = (KSCumberBase*)cb;
					
				};
				castBranch(atype, func, warningFileName);
			}
		}
		else if(pattern == "1005") // 빙결.
		{
			if(exe)
			{
				startFirePosition = startPosition;
				auto func = [=](CCObject* cb)
				{
					KSCumberBase* cumber = (KSCumberBase*)cb;
					if(cumber->getFreezeAttack())
					{
						cumber->getFreezeAttack()->updateFreeze();
					}
					else
					{
						int totalFrame = patternData.get("totalframe", 200).asInt();
						FreezeAttack* t_m26 = FreezeAttack::create(totalFrame, cumber);
						pattern_container->addChild(t_m26);
						cumber->setFreezeAttack(t_m26);
					}
					
				};
				castBranch(atype, func, warningFileName);
				
			}
			
		}
		else if(pattern == "1006") // 혼란
		{
			if(exe)
			{
				startFirePosition = startPosition;
				auto func = [=](CCObject* cb)
				{
					KSCumberBase* cumber = (KSCumberBase*)cb;
					if(cumber->getChaosAttack())
					{
						cumber->getChaosAttack()->updateChaos();
					}
					else
					{
						int totalFrame = patternData.get("totalframe", 300).asInt();
						ChaosAttack* t_m33 = ChaosAttack::create(totalFrame, cumber);
						pattern_container->addChild(t_m33);
						cumber->setChaosAttack(t_m33);
					}
					
				};
				castBranch(atype, func, warningFileName);
			}
		}
		else if(pattern == "1007") // 텔포.
		{
			if(exe)
			{
				startFirePosition = startPosition;
				auto func = [=](CCObject* cb)
				{
					TeleportWrapper* t_m32 = TeleportWrapper::create();
					pattern_container->addChild(t_m32);
					KSCumberBase* cumber = (KSCumberBase*)cb;
					cumber->setAttackPattern(nullptr);
				};
				castBranch(atype, func, warningFileName);
			}
		}
		else if(pattern == "1008") // 인비지블
		{
			if(exe)
			{
				startFirePosition = startPosition;
				auto func = [=](CCObject* cb)
				{
					int totalFrame = patternData.get("totalframe", 300).asInt();
					((KSCumberBase*)cb)->startInvisible(totalFrame);
					KSCumberBase* cumber = (KSCumberBase*)cb;
					cumber->setAttackPattern(nullptr);
					myGD->communication("CP_onPatternEndOf", cb);
				};
				castBranch(atype, func, warningFileName);
				
			}
		}
		else if(pattern == "1009") // 불지르기
		{
			if(exe)
			{
				startFirePosition = startPosition;
				auto func = [=](CCObject* cb)
				{
					int totalFrame = patternData.get("totalframe", 60*3).asInt();
					IntPoint mainCumberPoint = myGD->getMainCumberPoint((CCNode*)cb);
					CCPoint mainCumberPosition = ccp((mainCumberPoint.x-1)*pixelSize+1,(mainCumberPoint.y-1)*pixelSize+1);
					FlameWrapper* t_m15 = FlameWrapper::create(mainCumberPosition, (KSCumberBase*)cb, 10, totalFrame);
					pattern_container->addChild(t_m15);
				};
				castBranch(atype, func, warningFileName);
			}
		}
		else if(pattern == "1010") // 위성빔.
		{
			if(exe)
			{
				startFirePosition = startPosition;
				auto func = [=](CCObject* cb)
				{
					// 2.f 하는 이유는 AP12 의 myAction 이 1/60 이 아니고 1/30.f 이라서.
					int targetingFrame = patternData.get("targetingframe", 120).asInt() / 2.f;
					int shootFrame = patternData.get("shootframe", 180).asInt() / 2.f;
					int random_value = rand()%2 + 1;
					
					IntPoint mainCumberPoint = myGD->getMainCumberPoint((CCNode*)cb);
					CCPoint mainCumberPosition = ccp((mainCumberPoint.x-1)*pixelSize+1,(mainCumberPoint.y-1)*pixelSize+1);
					ThunderBoltWrapper* t_m12 = ThunderBoltWrapper::create(mainCumberPosition, (KSCumberBase*)cb, random_value, targetingFrame, shootFrame);
					pattern_container->addChild(t_m12);
					
					//				myGD->communication("CP_onPatternEndOf", cb);
					
				};
				castBranch(atype, func, warningFileName);
			}
		}
		else if(pattern == "1011") // 레이저 스캔.
		{
			if(exe)
			{
				startFirePosition = startPosition;
				auto func = [=](CCObject* cb)
				{
					LazerScanWrapper* t_m6 = LazerScanWrapper::create(startFirePosition, dynamic_cast<KSCumberBase*>(cb), patternD);
					pattern_container->addChild(t_m6);
				};
				castBranch(atype, func, warningFileName);
				
			}
		}
		else if(pattern == "1012") // 방사능 라인
		{
			if(exe)
			{
				startFirePosition = startPosition;
				auto func = [=](CCObject* cb)
				{
					RadioactivityWrapper* t = RadioactivityWrapper::create(startFirePosition, dynamic_cast<KSCumberBase*>(cb), patternD);
					pattern_container->addChild(t);
				};
				castBranch(atype, func, warningFileName);
			}
		}
		else if(pattern == "1013") // 메테오
		{
			if(exe)
			{
				startFirePosition = startPosition;
				auto func = [=](CCObject* cb)
				{
					int mType = 1;
					int number = patternData.get("number", 3).asInt();
					
					MeteorWrapper* t_m16 = MeteorWrapper::create(mType, number, 60, patternData.get("area", 50).asInt(),
																											 dynamic_cast<KSCumberBase*>(cb));
					pattern_container->addChild(t_m16);
					
					//				cumber->setAttackPattern(t_m16);
					
					//				cumber->setAttackPattern(t_m16);
					
				};
				castBranch(atype, func, warningFileName);
			}
		}
		else if(pattern == "1014") // 떨어지는 돌
		{
			if(exe)
			{
				startFirePosition = startPosition;
				auto func = [=](CCObject* cb)
				{
					int totalframe = patternData.get("totalframe", 300).asInt();
					int shootframe = patternData.get("shootframe", 30).asInt();
					float speed = patternData.get("speed", 250.f).asDouble() / 100.f;
					FallingStoneWrapper* t_m9 = FallingStoneWrapper::create(totalframe, (KSCumberBase*)cb, shootframe, speed, CCSizeMake(25, 25), 1);
					pattern_container->addChild(t_m9);
					KSCumberBase* cumber = (KSCumberBase*)cb;
				};
				castBranch(atype, func, warningFileName);
				
			}
		}
		else if(pattern == "1015") // 풍차벽.
		{
			if(exe)
			{
				int totalframe = patternData.get("totalframe", 800).asInt();
				
				startFirePosition = startPosition;
				WindmillObject* t_to = WindmillObject::create(ccp2ip(startPosition), totalframe);
				pattern_container->addChild(t_to);
				
				return invalid; // 노 캐스팅
			}
		}
		else if(pattern == "1016") // 다이너마이트.
		{
			if(exe)
			{
				startFirePosition = startPosition;
				int remainSecond = patternData.get("remainsecond", 9).asInt();
				int crashArea = patternData.get("area", 50).asInt();
				TickingTimeBomb* t_ttb = TickingTimeBomb::create(ccp2ip(startPosition), 120, remainSecond, crashArea, 1, tickingArray, this, callfunc_selector(MissileParent::resetTickingTimeBomb));
				pattern_container->addChild(t_ttb);
				return invalid; // 노 캐스팅
			}
		}
		else if(pattern == "1017") // 선을 따라가는 공격
		{
			if(exe)
			{
				startFirePosition = startPosition;
				auto func = [=](CCObject* cb)
				{
					AlongOfTheLineWrapper* t = AlongOfTheLineWrapper::create(startFirePosition, dynamic_cast<KSCumberBase*>(cb), patternD);
					pattern_container->addChild(t);
					//cumber->setAttackPattern(t);
				};
				castBranch(atype, func, warningFileName);
				
			}
		}
		else if(pattern == "1018") // 폭탄 구름.
		{
			if(exe)
			{
				startFirePosition = startPosition;
				auto func = [=](CCObject* cb)
				{
					CloudWrapper* t = CloudWrapper::create(startFirePosition, dynamic_cast<KSCumberBase*>(cb), patternD);
					pattern_container->addChild(t);
					//cumber->setAttackPattern(t);
					
				};
				castBranch(atype, func, warningFileName);
				
			}
		}
		else if(pattern == "1019") // 복어 공격.
		{
			if(exe)
			{
				startFirePosition = startPosition;
				auto func = [=](CCObject* cb)
				{
					int totalFrame = patternData.get("totalframe", 300).asInt();
					float scale = patternData.get("scale", 2.f).asFloat();
					((KSCumberBase*)cb)->startSwell(scale, totalFrame);
					
					KSCumberBase* cumber = (KSCumberBase*)cb;
					cumber->setAttackPattern(nullptr);
					myGD->communication("CP_onPatternEndOf", cb);
				};
				castBranch(atype, func, warningFileName);
				
			}
		}
		else if(pattern == "1020") // 자식들 낳기 공격
		{
			if(exe)
			{
				startFirePosition = startPosition;
				auto func = [=](CCObject* cb)
				{
					PutChildWrapper* t = PutChildWrapper::create(startFirePosition, dynamic_cast<KSCumberBase*>(cb), patternD);
					pattern_container->addChild(t);
				};
				castBranch(atype, func, warningFileName);
				
			}
		}
		else if(pattern.size() >= 2 && pattern[0] == 'a' && pattern[1] == 't') // ccb 관련 공격.
		{
			CircleCCBPieceBase* ccbPiece = dynamic_cast<CircleCCBPieceBase*>(cb);
			if(!ccbPiece)
				return invalid;
			
			if(atype == "crash")
			{
				//			AudioEngine::sharedInstance()->playEffect("sound_attackpattern_crash.mp3", false);
				AudioEngine::sharedInstance()->playEffect("ment_cast_crash.mp3", false, true);
				myGD->communication("Main_showWarning", 2);
				
				AudioEngine::sharedInstance()->playEffect("se_castmap.mp3", true);
				//			AudioEngine::sharedInstance()->playEffect("sound_casting_crash.mp3", true);
				
			}
			else if(atype == "special")
			{
				AudioEngine::sharedInstance()->playEffect("se_castspecial.mp3", true);
				AudioEngine::sharedInstance()->playEffect("ment_cast_special.mp3", false, true);
				//			AudioEngine::sharedInstance()->playEffect("sound_casting_option.mp3", true);
			}
			else // normal
			{
				myGD->communication("Main_showWarning", 1);
				AudioEngine::sharedInstance()->playEffect("se_castmissile.mp3", true);
				//			AudioEngine::sharedInstance()->playEffect("sound_casting_attack.mp3", true);
				//			AudioEngine::sharedInstance()->playEffect("sound_attackpattern_base.mp3", false);
				AudioEngine::sharedInstance()->playEffect("ment_cast_missile.mp3", false, true);
			}
			ccbPiece->runTimeline(patternData); // "at" 같은게 넘어감.
		}
		else
		{
			return invalid;
		}
	}
//	else
//	{
//		return invalid;
//	}
	
	
	
	//	if(!invalid)
	{
		myLog->addLog(kLOG_attackPattern_i, myGD->getCommunication("UI_getUseTime"), atoi(pattern.c_str()));
	}
	return valid;
}





void MissileParent::explosion( CCPoint bombPosition, ccColor4F t_color, float t_angle )
{
	AudioEngine::sharedInstance()->playEffect("sound_jack_missile_bomb.mp3",false);
	initParticle(bombPosition, t_color, t_angle);
}

void MissileParent::createTickingTimeBomb( IntPoint t_point, int t_bombFrameOneTime, int t_bombTimes, int t_rangeCode )
{
	bool is_check = false;
	for(int i=0;i<tickingArray->count();i++)
	{
		TickingTimeBomb* t_ttb = (TickingTimeBomb*)tickingArray->objectAtIndex(i);
		IntPoint settedPoint = t_ttb->getSettedPoint();
		if(settedPoint.x == t_point.x && settedPoint.y == t_point.y)
		{
			is_check = true;
			break;
		}
	}
	
	if(!is_check)
	{
		TickingTimeBomb* t_ttb = TickingTimeBomb::create(t_point, t_bombFrameOneTime, t_bombTimes, 50, t_rangeCode, tickingArray, this, callfunc_selector(MissileParent::resetTickingTimeBomb));
		addChild(t_ttb);
	}
}

void MissileParent::resetTickingTimeBomb()
{
	while(tickingArray->count() > 0)
	{
		TickingTimeBomb* t_ttb = (TickingTimeBomb*)tickingArray->lastObject();
		removeChild(t_ttb, true);
		tickingArray->removeObject(t_ttb);
	}
}


void MissileParent::shootPetMissile( int jm_type, int cmCnt, float damage_per, CCPoint s_p )
{
	AudioEngine::sharedInstance()->playEffect("sound_jack_basic_missile_shoot.mp3", false);
	if(jm_type >= 0 && jm_type <= 3)
	{
		vector<KSCumberBase*> subCumberArray = myGD->getSubCumberVector();
		int cumberCnt = subCumberArray.size();

		int random_value;
		
		int boss_count = myGD->getMainCumberCount();
		
		for(int i=0;i<cmCnt;i++)
		{
			if(i < boss_count)
			{
				JackMissile* t_jm = JM_BasicMissile::create(myGD->getMainCumberCCNodeVector()[i], jm_type, damage_per, s_p);
				addChild(t_jm);
				t_jm->startMoving();
			}
			else
			{
				if(cumberCnt == 0)
				{
					JackMissile* t_jm = JM_BasicMissile::create(myGD->getMainCumberCCNodeVector()[0], jm_type, damage_per, s_p);
					addChild(t_jm);
					t_jm->startMoving();
				}
				else
				{
					random_value = rand()%cumberCnt;
					JackMissile* t_jm = JM_BasicMissile::create((CCNode*)subCumberArray[random_value], jm_type, damage_per, s_p);
					addChild(t_jm);
					t_jm->startMoving();
				}
			}
		}
	}
	else if(jm_type >= 4 && jm_type <= 6)
	{
		UM_creator* t_c = UM_creator::create(cmCnt, jm_type, damage_per, s_p);
		addChild(t_c);
		t_c->startPetCreate();
	}
}

void MissileParent::initParticle( CCPoint startPosition, ccColor4F t_color, float t_angle )
{
	CCSprite* t_explosion = CCSprite::createWithTexture(explosion_node->getTexture(), CCRectMake(0, 0, 167, 191));
	t_explosion->setScale(1.f/myGD->game_scale);
	t_explosion->setRotation(-t_angle-90);
	t_explosion->setPosition(startPosition);
	explosion_node->addChild(t_explosion);
	
	CCAnimation* t_animation = CCAnimation::create();
	t_animation->setDelayPerUnit(0.1f);
	t_animation->addSpriteFrameWithTexture(explosion_node->getTexture(), CCRectMake(0, 0, 167, 191));
	for(int i=0;i<2;i++)
		for(int j=0;j<3;j++)
			t_animation->addSpriteFrameWithTexture(explosion_node->getTexture(), CCRectMake(j*167, i*191, 167, 191));
	
	CCAnimate* t_animate = CCAnimate::create(t_animation);
	CCFadeTo* t_fade = CCFadeTo::create(0.2f, 0);
	CCRemoveSelf* t_remove = CCRemoveSelf::create();
	CCSequence* t_seq = CCSequence::create(t_animate, t_fade, t_remove, NULL);
	t_explosion->runAction(t_seq);
	
	
	//	particle = CCParticleSystemQuad::createWithTotalParticles(25);
	//	particle->setPositionType(kCCPositionTypeRelative);
	//	CCTexture2D* texture = CCTextureCache::sharedTextureCache()->addImage("circle1.png");
	//	particle->setTexture(texture);
	//	particle->setEmissionRate(2500.00); // inf
	//	particle->setAngle(90.0);
	//	particle->setAngleVar(360.0);
	//	ccBlendFunc blendFunc = {GL_SRC_ALPHA, GL_ONE};
	//	particle->setBlendFunc(blendFunc);
	//	particle->setDuration(0.01);
	//	particle->setEmitterMode(kCCParticleModeGravity);
	//	particle->setStartColor(t_color);
	//	ccColor4F startColorVar = {0,0,0,0};
	//	particle->setStartColorVar(startColorVar);
	//	ccColor4F endColor = {0.00,0.00,0.00,1.00};
	//	particle->setEndColor(endColor);
	//	ccColor4F endColorVar = {0,0,0,0};
	//	particle->setEndColorVar(endColorVar);
	//	particle->setStartSize(0.00);
	//	particle->setStartSizeVar(2.0);
	//	particle->setEndSize(10.0);
	//	particle->setEndSizeVar(2.0);
	//	particle->setGravity(ccp(2.0,10.0));
	//	particle->setRadialAccel(0.0);
	//	particle->setRadialAccelVar(10.0);
	//	particle->setSpeed(50);
	//	particle->setSpeedVar(5);
	//	particle->setTangentialAccel(0);
	//	particle->setTangentialAccelVar(10);
	//	particle->setTotalParticles(25);
	//	particle->setLife(0.50);
	//	particle->setLifeVar(0.1);
	//	particle->setStartSpin(0.0);
	//	particle->setStartSpinVar(0.0);
	//	particle->setEndSpin(0.0);
	//	particle->setEndSpinVar(0.0);
	//	particle->setPosition(startPosition);
	//	particle->setPosVar(ccp(0,0));
	//	particle->setAutoRemoveOnFinish(true);
	//	addChild(particle);
}

void MissileParent::myInit( CCNode* boss_eye )
{
	//chargeArray = new CCArray(1);
	pattern_container = CCNode::create();
	addChild(pattern_container);
	tickingArray = new CCArray(1);
	
	mySW = SW_Parent::create();
	addChild(mySW);
	
	explosion_node = CCSpriteBatchNode::create("fx_monster_hit.png");
	addChild(explosion_node);
	
	jack_missile_node = CCNode::create();
	addChild(jack_missile_node, 10);
//	lastCastTime = 0;
	myGD->I_CCPStrCumberBaseB["MP_attackWithKSCode"] = std::bind(&MissileParent::attackWithKSCode, this, _1, _2, _3, _4);
	myGD->V_CCO["MP_removeChargeInArray"] = std::bind(&MissileParent::removeChargeInArray, this, _1);
	myGD->V_IIFCCP["MP_createJackMissile"] = std::bind(&MissileParent::createJackMissile, this, _1, _2, _3, _4);
	myGD->V_CCO["MP_bombCumber"] = std::bind(&MissileParent::bombCumber, this, _1);
	myGD->createJackMissileWithStoneFunctor = std::bind(&MissileParent::createJackMissileWithStone, this,
																											_1, _2, _3, _4, _5, _6);
	myGD->V_CCPCOLORF["MP_explosion"] = std::bind(&MissileParent::explosion, this, _1, _2, _3);
	myGD->V_IIFCCP["MP_shootPetMissile"] = std::bind(&MissileParent::shootPetMissile, this, _1, _2, _3, _4);
	myGD->V_V["MP_resetTickingTimeBomb"] = std::bind(&MissileParent::resetTickingTimeBomb, this);
	myGD->V_V["MP_subOneDie"] = std::bind(&MissileParent::subOneDie, this);
	myGD->I_V["MP_getJackMissileCnt"] = std::bind(&MissileParent::getJackMissileCnt, this);
	myGD->removeAllPattern = std::bind(&MissileParent::removeAllPattern, this);
}

void MissileParent::removeChargeInArray( CCObject* remove_charge )
{
//	auto iter = find(m_charges.begin(), m_charges.end(), remove_charge);
//	if(iter != m_charges.end())
//		m_charges.erase(iter);
//	chargeArray->removeObject(remove_charge);
}

void MissileParent::movingMainCumber()
{
	myGD->communication("CP_movingMainCumber");
}

MissileParent* MissileParent::create( CCNode* boss_eye )
{
	MissileParent* t_mp = new MissileParent();
	t_mp->myInit(boss_eye);
	t_mp->autorelease();
	return t_mp;
}



UM_creator* UM_creator::create( int t_um_tcnt, int t_create_type, float t_missile_speed )
{
	UM_creator* t_c = new UM_creator();
	t_c->myInit(t_um_tcnt, t_create_type, t_missile_speed);
	t_c->autorelease();
	return t_c;
}

UM_creator* UM_creator::create( int t_um_tcnt, int t_create_type, float t_missile_speed, CCPoint s_p )
{
	UM_creator* t_c = new UM_creator();
	t_c->myInit(t_um_tcnt, t_create_type, t_missile_speed, s_p);
	t_c->autorelease();
	return t_c;
}

void UM_creator::startCreate()
{
	ing_frame = 0;
	ing_um_cnt = 0;
	schedule(schedule_selector(UM_creator::creating));
}

void UM_creator::startPetCreate()
{
	ing_frame = 0;
	ing_um_cnt = 0;
	schedule(schedule_selector(UM_creator::petCreating));
}

void UM_creator::creating()
{
	ing_frame++;
	
	if(ing_frame%shoot_frame == 0)
	{
		if(ing_frame/shoot_frame <= 1)
		{
			JackMissile* t_jm = JM_UpgradeMissile::create(myGD->getMainCumberCCNodeVector()[ing_frame/shoot_frame-1], create_type, missile_speed);
			getParent()->addChild(t_jm);
			t_jm->startMoving();
		}
		else
		{
			vector<KSCumberBase*> subCumberArray = myGD->getSubCumberVector();
			int cumberCnt = subCumberArray.size();
			int random_value;
			
			if(cumberCnt == 0)
			{
				JackMissile* t_jm = JM_UpgradeMissile::create(myGD->getMainCumberCCNodeVector()[0], create_type, missile_speed);
				getParent()->addChild(t_jm);
				t_jm->startMoving();
			}
			else
			{
				random_value = rand()%cumberCnt;
				JackMissile* t_jm = JM_UpgradeMissile::create((CCNode*)subCumberArray[random_value], create_type, missile_speed);
				getParent()->addChild(t_jm);
				t_jm->startMoving();
			}
		}
		ing_um_cnt++;
	}
	
	if(ing_um_cnt >= um_tcnt)
	{
		stopCreate();
	}
}

void UM_creator::petCreating()
{
	ing_frame++;
	
	if(ing_frame%shoot_frame == 0)
	{
		if(ing_frame/shoot_frame <= 1)
		{
			JackMissile* t_jm = JM_UpgradeMissile::create(myGD->getMainCumberCCNodeVector()[ing_frame/shoot_frame-1], create_type, missile_speed, start_position);
			getParent()->addChild(t_jm);
			t_jm->startMoving();
		}
		else
		{
			vector<KSCumberBase*> subCumberArray = myGD->getSubCumberVector();
			int cumberCnt = subCumberArray.size();
			int random_value;
			
			if(cumberCnt == 0)
			{
				JackMissile* t_jm = JM_UpgradeMissile::create(myGD->getMainCumberCCNodeVector()[0], create_type, missile_speed, start_position);
				getParent()->addChild(t_jm);
				t_jm->startMoving();
			}
			else
			{
				random_value = rand()%cumberCnt;
				JackMissile* t_jm = JM_UpgradeMissile::create((CCNode*)subCumberArray[random_value], create_type, missile_speed, start_position);
				getParent()->addChild(t_jm);
				t_jm->startMoving();
			}
		}
		ing_um_cnt++;
	}
	
	if(ing_um_cnt >= um_tcnt)
	{
		stopPetCreate();
	}
}

void UM_creator::stopCreate()
{
	unschedule(schedule_selector(UM_creator::creating));
	removeFromParentAndCleanup(true);
}

void UM_creator::stopPetCreate()
{
	unschedule(schedule_selector(UM_creator::petCreating));
	removeFromParentAndCleanup(true);
}

void UM_creator::myInit( int t_um_tcnt, int t_create_type, float t_missile_speed )
{
	if(t_missile_speed < 2.f)
		missile_speed = 2.f;
	else if(t_missile_speed > 9.f)
		missile_speed = 9.f;
	else
		missile_speed = t_missile_speed;
	shoot_frame = missile_speed*3;
	um_tcnt = t_um_tcnt;
	create_type = t_create_type;
}

void UM_creator::myInit( int t_um_tcnt, int t_create_type, float t_missile_speed, CCPoint s_p )
{
	start_position = s_p;
	myInit(t_um_tcnt, t_create_type, t_missile_speed);
}
