#ifndef EscapeTheSpace_KsLocalization_h
#define EscapeTheSpace_KsLocalization_h

#include "cocos2d.h"
#include "platform/android/jni/Java_org_cocos2dx_lib_Cocos2dxHelper.h"

using namespace cocos2d;
using namespace std;
#include <map>
#include <string>
/*
 
 myLoc->getLocalForKey(kKsLocalKey_tutorial7)
 
 */

#define getLocal(X) (KsLocal::sharedInstance()->getLocalForKey(X))
enum class LK
{
	kItem1,
	kReGacha,
	kRewardConfirm,
	kRewardTitle,
	kBonusGame,
	kBonusGameStart,
	kBonusGameDesc,
	kBonusGameGababo,
	kGababoDesc1,
	kGababoDesc2,
	kBonusGameTouch,
	kTouchDesc1,
	kTouchDesc2,
	kBonusCong,
	kAccountConf,
	kLinkingGoogle,
	kLinkingFacebook,
	kLinkingX,
	kLinkingUnknown,
	kLinkingAccount,
	kMemberNo,
	kSaveDesc1,
	kGoogleButton,
	kSaveDesc2,
	kFacebookButton,
	kWarningDesc,
	kAnotherHistory,
	kLoadPreviousData,
	kSaveCurrentData,
	kNetworkError,
	kCantLinking,
	kRetryLinking,
	kAccountDesc,
	kLinkingCommand,
	kLinked,
	kForeverDeleteAccount1,
	kForeverDeleteAccount2,
	kUnlinkAccount1,
	kLinkAccount1
};
class KsLocal
{
	
public:
	
	static KsLocal* sharedInstance();
	
	~KsLocal()
	{
		
	}
	
	const char* getLocalForKey(LK key);
	const char* getSupportLocalCode();
	std::string getLocalCode();
private:
	KsLocal()
	{
		languageType = "";
		this->initLocal();
	}
	void initLocal();
	void setLocal();
	void ko();
	void en();
	void ja();
	std::string languageType;
	std::map<std::string, std::map<LK, std::string>> m_mapper;
};



#endif
