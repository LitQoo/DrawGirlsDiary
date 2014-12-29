
//
//  Created by LitQoo on 13. 2. 14..
//  www.graphdog.net
//

// test brench!

#include "GraphDog.h"
#include <sstream>
#include <cstdlib>
#include <unistd.h>
#include "JNIKelper.h"

#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
#include "jni.h"
#if COCOS2D_VERSION<0x00020000
#include "android/jni/JniHelper.h"
#else
#include "platform/android/jni/JniHelper.h"
#endif
#endif


#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
#include <sys/types.h>
#include <sys/sysctl.h>
//#include "OpenUDID.h"
#endif
#include "BaseXX.h"
#include "CipherUtils.h"
#include "EncryptCharsA.h"
#include "KSUtil.h"
#include "hspConnector.h"
#include "DataStorageHub.h"

int AutoIncrease::cnt = 0;
size_t GraphDog::WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp){
	
	size_t realsize = size * nmemb;
	struct GDStruct *mem = (struct GDStruct *)userp;
	
	mem->memory = (char *)realloc(mem->memory, mem->size + realsize + 1);
	
	if (mem->memory == NULL) {
		/* out of memory! */
		exit(EXIT_FAILURE);
	}
	memcpy(&(mem->memory[mem->size]), contents, realsize);
	mem->size += realsize;
	mem->memory[mem->size] = 0;
	return realsize;
}


void GraphDog::setUdid(string _id){
	udid=_id;
}

void GraphDog::setGraphDogVersion(int version){
	std::ostringstream ostr;
	ostr << version;
	this->gdVersion=ostr.str();
}

string GraphDog::getGraphDogVersion(){
	return this->gdVersion;
}

void GraphDog::setMemberID(long long int _memberID){
	memberID = _memberID;
}

long long int GraphDog::getMemberID(){
	return memberID.getV();
}

void GraphDog::setSocialID(string _kakaoID){
	socialID=_kakaoID;
}

string GraphDog::getSocialID(){
	return socialID.getV();
}

void GraphDog::setup(string secretKey,string _appVersion){
  
	
	this->setup("", secretKey, "", _appVersion);
	
}
void GraphDog::setup(string appID,string secretKey,string _packageName,string _appVersion){
	
	aID=appID;
	sKey=secretKey;
	
	this->packageName=_packageName;
	//string deviceId = getDeviceID();
	//this->setUdid(deviceId);
  //  std::ostringstream ostr;
  //  ostr << _appVersion;
	this->appVersion=_appVersion;
	
#if COCOS2D_VERSION<0x00020000
	// in cocos2d-x 1.x
	CCScheduler::sharedScheduler()->scheduleSelector(schedule_selector(GraphDog::receivedCommand), this, 0,false);
#else
	// in cocos2d-x 2.x
	CCDirector::sharedDirector()->getScheduler()->scheduleSelector(schedule_selector(GraphDog::receivedCommand), this, 0.f, kCCRepeatForever, 0.f, false);
	//	CCDirector::sharedDirector()->getScheduler()->scheduleSelector(schedule_selector(GraphDog::receivedCommand), this, 0.f, false, kCCRepeatForever, 0);
#endif
	//	setLanguage(GraphDogLib::getLocalCode());
}

void GraphDog::setAuID(string appuserID){
	CCUserDefault::sharedUserDefault()->setStringForKey("GRAPHDOG_AUID", appuserID.c_str());
	CCUserDefault::sharedUserDefault()->flush();
}
string GraphDog::getAuID(){
	return CCUserDefault::sharedUserDefault()->getStringForKey("GRAPHDOG_AUID");
}
string GraphDog::getUdid(){
	return udid;
}
int GraphDog::getAppVersion(){
	return atoi(appVersion.c_str());
}
string GraphDog::getAppVersionString(){
	return appVersion;
}
void GraphDog::setEmail(string email){
	CCUserDefault::sharedUserDefault()->setStringForKey("GRAPHDOG_EMAIL", email);
	CCUserDefault::sharedUserDefault()->flush();
}

string GraphDog::getEmail(){
	return CCUserDefault::sharedUserDefault()->getStringForKey("GRAPHDOG_EMAIL");
}
string GraphDog::getPlatform(){
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
	return "ios";
#elif CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
	return "android";
#else
	return "null";
#endif
}

void GraphDog::setCTime(string cTime){
	CCUserDefault::sharedUserDefault()->setStringForKey("GRAPHDOG_CTIME", cTime);
	CCUserDefault::sharedUserDefault()->flush();
}

string GraphDog::getCTime(){
	string ctime= CCUserDefault::sharedUserDefault()->getStringForKey("GRAPHDOG_CTIME");
	if(ctime=="")ctime="9999";
	return ctime;
}

string GraphDog::getToken(){
	
	string udid=getUdid();
	string auid=getAuID();
	string email=getEmail();
	string nick=getNick();
	string flag=getFlag();
	string lang=getLanguage();
	string platform=getPlatform();
	string cTime=getCTime();
	string dInfo="";//getDeviceInfo();
	string token=GraphDogLib::GDCreateToken(auid,udid,flag,lang,nick,email,platform,cTime,sKey,dInfo);
	//	CCLOG("%s", token.c_str());
	//	CCLOG("%s", unBase64NextUnDes("GDSK3388", token).c_str());
	return token;
}

void GraphDog::setNick(string nick){
	GraphDogLib::replaceString(nick,"|","l");
	CCUserDefault::sharedUserDefault()->setStringForKey("GRAPHDOG_NICK", nick);
	CCUserDefault::sharedUserDefault()->flush();
}

string GraphDog::getNick(){
	return CCUserDefault::sharedUserDefault()->getStringForKey("GRAPHDOG_NICK");
}

void GraphDog::setFlag(string flag){
	CCUserDefault::sharedUserDefault()->setStringForKey("GRAPHDOG_FLAG", flag);
	CCUserDefault::sharedUserDefault()->flush();
}

string GraphDog::getFlag(){
	return CCUserDefault::sharedUserDefault()->getStringForKey("GRAPHDOG_FLAG");
}

void GraphDog::setLanguage(string lang){
	CCUserDefault::sharedUserDefault()->setStringForKey("GRAPHDOG_LANG", lang);
	CCUserDefault::sharedUserDefault()->flush();
}

bool GraphDog::isExistApp()
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
	jboolean ret = false;
//	JniMethodInfo minfo;
//	jobject jobj;
	CCLOG("isExistApp");
	
//	if(JniHelper::getStaticMethodInfo(minfo, packageName.c_str(), "getActivity", "()Ljava/lang/Object;"))
//	{
//		jobj = minfo.env->NewGlobalRef(minfo.env->CallStaticObjectMethod(minfo.classID, minfo.methodID));
		JniMethodInfo __minfo;
//		__minfo.classID = 0;
//		__minfo.env = 0;
//		__minfo.methodID = 0;
		
		
		if(JniHelper::getMethodInfo(__minfo, JNIKelper::getInstance()->getClassName().c_str(), "isExistApp", "(Ljava/lang/String;)Z"))
		{
			CCLOG("found isExistApp");
			jstring param1 = __minfo.env->NewStringUTF("com.nhnent.SKSUMRAN");
			
			ret = __minfo.env->CallBooleanMethod(JNIKelper::getInstance()->getJobj(), __minfo.methodID, param1);
			CCLOG("ret = %d ", ret);
			__minfo.env->DeleteLocalRef(__minfo.classID);
			__minfo.env->DeleteLocalRef(param1);
		}
//		minfo.env->DeleteGlobalRef(jobj);
//		minfo.env->DeleteLocalRef(minfo.classID);
//	}
	
	return (bool)ret;
#elif CC_TARGET_PLATFORM == CC_PLATFORM_IOS
	return (bool)[[UIApplication sharedApplication]canOpenURL:[NSURL URLWithString:@"SKSUMRAN://"]];
#endif
}

string GraphDog::getGameDownUrl()
{
	string return_value = "";
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
	JniMethodInfo __minfo;
	
	if(JniHelper::getMethodInfo(__minfo, JNIKelper::getInstance()->getClassName().c_str(), "getGameDownUrl", "()Ljava/lang/String;"))
	{
		jstring ret = (jstring)__minfo.env->CallObjectMethod(JNIKelper::getInstance()->getJobj(), __minfo.methodID);
		__minfo.env->DeleteLocalRef(__minfo.classID);
		return_value = JniHelper::jstring2string(ret);
		__minfo.env->DeleteLocalRef(ret);
	}
	//		minfo.env->DeleteGlobalRef(jobj);
	//		minfo.env->DeleteLocalRef(minfo.classID);
	//	}
	
#elif CC_TARGET_PLATFORM == CC_PLATFORM_IOS
	return_value = "";
#endif
	
	return return_value;
}

void GraphDog::openOriginalApp()
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
	//	JniMethodInfo minfo;
	//	jobject jobj;
	
	//	if(JniHelper::getStaticMethodInfo(minfo, packageName.c_str(), "getActivity", "()V"))
	//	{
	//		jobj = minfo.env->NewGlobalRef(minfo.env->CallStaticObjectMethod(minfo.classID, minfo.methodID));
	JniMethodInfo __minfo;
	//		__minfo.classID = 0;
	//		__minfo.env = 0;
	//		__minfo.methodID = 0;
	
	CCLOG("before find method : originalAppExe");
	if(JniHelper::getMethodInfo(__minfo, JNIKelper::getInstance()->getClassName().c_str(), "originalAppExe", "()V"))
	{
		CCLOG("before call method : originalAppExe");
		__minfo.env->CallVoidMethod(JNIKelper::getInstance()->getJobj(), __minfo.methodID);
		__minfo.env->DeleteLocalRef(__minfo.classID);
		CCLOG("after call method : originalAppExe");
	}
	//		minfo.env->DeleteGlobalRef(jobj);
	//		minfo.env->DeleteLocalRef(minfo.classID);
	//	}
	
#elif CC_TARGET_PLATFORM == CC_PLATFORM_IOS
	[[UIApplication sharedApplication]openURL:[NSURL URLWithString:@"SKSUMRAN://"]];
#endif
}

void GraphDog::checkIntentData()
{
	is_returned_checkIntentData = false;
	
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
	//	JniMethodInfo minfo;
	//	jobject jobj;
	
	//	if(JniHelper::getStaticMethodInfo(minfo, packageName.c_str(), "getActivity", "()V"))
	//	{
	//		jobj = minfo.env->NewGlobalRef(minfo.env->CallStaticObjectMethod(minfo.classID, minfo.methodID));
	JniMethodInfo __minfo;
	//		__minfo.classID = 0;
	//		__minfo.env = 0;
	//		__minfo.methodID = 0;
	
	if(JniHelper::getMethodInfo(__minfo, JNIKelper::getInstance()->getClassName().c_str(), "checkIntentData", "()V"))
	{
		__minfo.env->CallVoidMethod(JNIKelper::getInstance()->getJobj(), __minfo.methodID);
		__minfo.env->DeleteLocalRef(__minfo.classID);
	}
	//		minfo.env->DeleteGlobalRef(jobj);
	//		minfo.env->DeleteLocalRef(minfo.classID);
	//	}
	
#elif CC_TARGET_PLATFORM == CC_PLATFORM_IOS
	is_returned_checkIntentData = true;
#endif
}

#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

#ifdef __cplusplus
extern "C" {
#endif
	void Java_com_litqoo_lib_KSActivityBase_interlockAction(JNIEnv *env, jobject thiz, jstring tt_memberID, jstring tt_diaryCode, int tt_cardNumber)
	{
		CCLOG("setted memberID and diaryCode and cardNumber 1");
		jboolean isCopy1 = JNI_FALSE;
		const char* ttt_memberID = env->GetStringUTFChars(tt_memberID, &isCopy1);
		
		jboolean isCopy2 = JNI_FALSE;
		const char* ttt_diaryCode = env->GetStringUTFChars(tt_diaryCode, &isCopy2);
		
		
		GraphDog::get()->t_memberID = ttt_memberID;
		GraphDog::get()->t_diaryCode = ttt_diaryCode;
		GraphDog::get()->t_cardNumber = tt_cardNumber;
		GraphDog::get()->is_returned_checkIntentData = true;
		CCLOG("setted memberID and diaryCode and cardNumber 2");
		//env->ReleaseStringUTFChars(ttt_memberID, ttt_diaryCode);
	}
#ifdef __cplusplus
}
#endif

#endif

string GraphDog::getLanguage(){
	
	string lang = CCUserDefault::sharedUserDefault()->getStringForKey("GRAPHDOG_LANG");
	if(lang=="")lang="en";
	return lang;
}

CURL* GraphDog::getCURL(){
	return curl_handle;
}

bool GraphDog::command(const std::vector<CommandParam>& params,int errorCnt)
{
	string udid=getUdid();
	string email=getEmail();
	string auid=getAuID();
	//string token;
	//저장되어있는 토큰불러오기. 없으면 생성
	//token=getToken();
	
	int insertIndex = AutoIncrease::get();
	std::vector<CommandType> cmdCollect;
	CommandsType cmdQueue;
	// cmdQueue 에 명령 추가하고...
	//@ JsonBox::Object jsonTotalCmd;
	Json::Value jsonTotalCmd;
	cmdQueue.chunk = GDStruct((char*)malloc(1), 0, CURLE_AGAIN);
	cmdQueue.errorCnt=errorCnt;
	int i=0;
	for(std::vector<CommandParam>::const_iterator iter = params.begin(); iter != params.end(); ++iter, i++)
	{
		//		ostringstream oss;
		//		oss << (iter->param);
		char buf[20];
		sprintf(buf, "%d", i);
		//@ JsonBox::Object param;
		Json::Value param;
		param["p"] = iter->param;
		param["a"] = iter->action;
		jsonTotalCmd[buf] = param; // dict 로
		//@@ CommandType cmd = {iter->target, iter->selector, GraphDogLib::JsonObjectToString(iter->param), iter->action};
		//@@ CommandType cmd = {iter->target, iter->selector, GraphDogLib::JsonObjectToString(iter->param), iter->action};
		CommandType cmd = {iter->func, GraphDogLib::JsonObjectToString(iter->param), iter->action};
		cmdQueue.commands[buf] = cmd;
		cmdCollect.push_back(cmd);
	}
    
    if(i==0){
        TRACE();
				return false;
    }
//    CCAssert(i!=0, "funck why i == 0");
	
	
	jsonTotalCmd["country"]=hspConnector::get()->getCountryCode();
	jsonTotalCmd["timezone"]=myDSH->getStringForKey(kDSH_Key_timeZone);
	jsonTotalCmd["memberID"]=getMemberID();
	jsonTotalCmd["socialID"]=getSocialID();
	jsonTotalCmd["deviceID"]=this->deviceID;
	jsonTotalCmd["lang"]=KS::getLocalCode();
	jsonTotalCmd["dontcheck"] = true;
	
	
	#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
	jsonTotalCmd["os"]="android";
	#elif CC_TARGET_PLATFORM == CC_PLATFORM_IOS
	jsonTotalCmd["os"]="ios";
	#endif
	
	
	#if !defined(COCOS2D_DEBUG) || COCOS2D_DEBUG == 0
	
	#elif COCOS2D_DEBUG == 1
		jsonTotalCmd["log"]="true";
	#endif
	
	
	//ostringstream oss2;
	//oss2 << jsonTotalCmd;
	cmdQueue.commandStr = GraphDogLib::JsonObjectToString(jsonTotalCmd); //oss2.str();
	cmdQueue.caller = this;
	commandQueue[insertIndex] = cmdQueue;
	pthread_t p_thread;
	int thr_id;
	
	// 쓰레드 생성 아규먼트로 1 을 넘긴다.
    TRACE();
	thr_id = pthread_create(&p_thread, NULL, t_function, (void*)insertIndex);
	TRACE();
    if (thr_id < 0)
	{
		//쓰레드생성오류시
		//@ JsonBox::Object resultobj;
        CCLOG("thread create error!!!!");
		TRACE();
        Json::Value resultobj;
		//@		resultobj["state"]= JsonBox::Value("error");
		//@		resultobj["errorMsg"]=JsonBox::Value("don't create thread");
		//@		resultobj["errorCode"]=JsonBox::Value(1001);
		
		resultobj["result"]["code"]=GDDONTMAKETHREAD;
		
		resultobj["state"]= "error";
		resultobj["errorMsg"]="don't create thread";
		resultobj["errorCode"]=1001;
        
        TRACE();
		for(std::vector<CommandType>::const_iterator iter = cmdCollect.begin(); iter != cmdCollect.end(); ++iter)
		{
			//@@if( iter->target != 0 && iter->selector != 0)
			//@@	((iter->target)->*(iter->selector))(resultobj);
			if(iter->func!=NULL)iter->func(resultobj);
		}
		
        TRACE();
		if( cmdQueue.chunk.memory )
			free(cmdQueue.chunk.memory);
		commandQueue.erase(insertIndex);
		
        TRACE();
        return false;
	}
	
	return true;
}
//@ bool GraphDog::command(string action, const JsonBox::Object* const param,CCObject *target,GDSelType selector){
//@@bool GraphDog::command(string action, const Json::Value param,CCObject *target,GDSelType selector){
bool GraphDog::command(string action, const Json::Value param,function<void(Json::Value)> func,int errorCnt){
	CommandParam cp;
	cp.action = action;
	if(param != 0){
		cp.param = param;
		//@ cp.param = *param;
	}
	//@@	cp.target = target;
	//@@	cp.selector = selector;
	cp.func=func;
	std::vector<CommandParam> p;
	p.push_back(cp);
	this->command(p,errorCnt);
	return true;
}


//@ bool GraphDog::test(string action, const JsonBox::Object* const param,CCObject *target, GDSelType selector, JsonBox::Object result){
bool GraphDog::test(string action, const Json::Value param,CCObject *target, GDSelType selector, Json::Value result){
	//@ result["param"] = *param;
	result["param"]=param;
	if(target!=0 && selector!=0) ((target)->*(selector))(result);
	return true;
}

//@ bool GraphDog::test(string action, const JsonBox::Object* const param,CCObject *target, GDSelType selector, string result){
bool GraphDog::test(string action, const Json::Value param,CCObject *target, GDSelType selector, string result){
	Json::Value resultObj = GraphDogLib::StringToJsonObject(result);
	
	this->test(action,param,target,selector,resultObj);
	return true;
}


void GraphDog::log(string logtext){
	
	int b = 256;
	int a = logtext.length()/b+1;
	
	for(int i=0;i<a;i++){
		int endi = b;
		
		if(endi>logtext.length()-i*b)endi=logtext.length()-i*b;
		string log = logtext.substr(i*b,endi+10);
		CCLOG("%s",log.c_str());
	}
	
}

//쓰레드펑션
void* GraphDog::t_function(void *_insertIndex)
{
	int insertIndex = (int)_insertIndex;
	
	//   CCLOG("t_function1");
	//	std::map<int, CommandType>& commands = graphdog->commands;
	//	pthread_mutex_lock(&graphdog->cmdsMutex);
	CommandsType& command = graphdog->commandQueue[insertIndex];
	Json::Value costr = command.commandStr;
	
	
	
	pthread_mutex_lock(&command.caller->t_functionMutex);
    
    
    int add = (int)(rand()%10)+1;
	GraphDog::get()->lastCmdNo += add;
	costr["cmdNo"]=GraphDog::get()->lastCmdNo;
	command.commandStr = costr.asString();
	CCLOG("cmdNo is %d",GraphDog::get()->lastCmdNo);
    
	//CCLOG("t_function2");
	//string token="";
	//CCLOG("t_function2");
	string paramStr =  CipherUtils::encryptAESBASE64(encryptChars("nonevoidmodebase").c_str(), command.commandStr.c_str()); //toBase64(desEncryption(graphdog->sKey, command.commandStr));
	CCLOG("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ command start, t_function @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
	CCLOG("request %s",command.commandStr.c_str());
	string dataset = "gid="+GraphDog::get()->aID+ "&command=" + paramStr + "&appver=" + GraphDog::get()->getAppVersionString() + "&version="+GRAPHDOG_VERSION;
	CCLOG("t_function3");
	//string commandurl = "http://litqoo.com/dgserver/data.php";
	string commandurl = GraphDog::get()->getServerURL()+"/command.php"; //"http://182.162.201.147:10010/command.php"; //"http://182.162.201.147:10010/data.php"; //
	
	CCLOG("call graphdog : %s",commandurl.c_str());
	CCLOG("-------------senddata-----------------");
	GraphDog::get()->log(dataset+"\n ------- senddataend ---------");
	CCLOG("-------------senddatareal1-----------------");
	
	CCLOG("call graphdog : %s",dataset.c_str());
	CCLOG("-------------senddatareal2-----------------");
	//commandurl=commandurl.append(GraphDog::get()->getGraphDogVersion());
	//commandurl=commandurl.append("/");
	//commandurl=commandurl.append(GraphDog::get()->aID);
	// << "&param=" << paramStr
	//curl으로 명령을 날리고 겨로가를 얻는다.
	CURL *handle = GraphDog::get()->getCURL();
	curl_easy_setopt(handle, CURLOPT_URL, commandurl.c_str());
	curl_easy_setopt(handle, CURLOPT_POSTFIELDS,dataset.c_str());
	curl_easy_setopt(handle, CURLOPT_WRITEDATA, (void *)&command.chunk);

  
	CCLOG("t_function4");
	//		curl_setopt($ch,CURLOPT_TIMEOUT,1000);
	//	pthread_mutex_unlock(&graphdog->cmdsMutex);
	CURLcode resultCode = curl_easy_perform(handle);
	CCLOG("result code is %d",resultCode);
	//##
	//@ JsonBox::Object resultobj;
	Json::Value resultobj;
	string resultStr;
	if(resultCode == CURLE_OK)
	{
		//CCLOG("t_function OK1");
		resultStr = command.chunk.memory;// gdchunk.memory;
		GraphDog::get()->log("------ get str --------\n"+resultStr+"\n ------- end get str ---------");
		if(*resultStr.rbegin() == '#') // success
		{
			try
			{
				
				CCLOG("check1");
				vector<char> encText = base64To(std::string(resultStr.begin(), resultStr.end() - 1) ); // unbase64
				//resultStr = desDecryption(graphdog->sKey, std::string(encText.begin(), encText.end())); // des Decryption
				
				CCLOG("check2");
				resultStr = CipherUtils::decryptAESBASE64(encryptChars("nonevoidmodebase").c_str(), resultStr.c_str());
				
				CCLOG("check3");
				resultobj = GraphDogLib::StringToJsonObject(resultStr);// result.getObject();
				
				GraphDog::get()->log("------ check4 result obj --------\n"+resultobj.asString()+"\n ------- end check4 result obj  ---------");
				Json::Value commandParam = command.commandStr;
				if(commandParam["cmdNo"].asInt()!=resultobj["cmdNo"].asInt()){
					
					resultCode = CURLE_CHUNK_FAILED;
					CCLOG("cmd check error %s",resultobj.asString().c_str());
					//CCAssert(false, "정상적인 이용으로는 이곳에 들어오면 안된다.");
				}else{
					
					CCLOG("reset by server cmdNo is %d",GraphDog::get()->lastCmdNo);
					GraphDog::get()->lastCmdNo=commandParam["cmdNo"].asInt();
				}
				//CCLOG("t_function OK2 %s",resultStr.c_str());
			}
			catch(const std::string& msg)
			{
				CCLOG("t_function FAILED1");
				resultCode = CURLE_CHUNK_FAILED;
			}
			catch(stlencoders::decode_error &error)
			{
				CCLOG("t_function FAILED2");
				resultCode = CURLE_CHUNK_FAILED;
			}
			catch(...){
				CCLOG("t_function FAILED3");
				resultCode = CURLE_CHUNK_FAILED;
			}
		}
		else
		{
			//CCLOG("t_function FAILED2");
			
			CCLOG("t_function5 set CURLE_CHUNK_FAILED");
			resultCode = CURLE_CHUNK_FAILED;
		}
	}
	else
	{
		CCLOG("omg %d",resultCode);
		//resultCode = CURLE_CHUNK_FAILED;
	}
	
	
	CCLOG("check5");
	//callbackparam 통신과 무관함. 넣어준거 그대로 피드백.
	for(auto iter = command.commands.begin(); iter != command.commands.end(); ++iter)
	{
		if(iter->second.paramStr != "")
		{
			//@ JsonBox::Object param = GraphDogLib::StringToJsonObject(iter->second.paramStr);
			Json::Value param = GraphDogLib::StringToJsonObject(iter->second.paramStr);
			//@ resultobj[iter->first]["param"] = JsonBox::Value(param);
			resultobj[iter->first]["param"] = param;
			resultobj[iter->first]["param"]["action"]=iter->second.action;
		}
	}
	
	CCLOG("check6");
	//	bool newToken = false;
	//	// 새토큰발급일 경우
	//	//if(resultobj["tokenUpdate"].getString()=="ok"){
	//		//정상결과시 AuID,Token 다시 세팅
	//		if(resultobj["state"].getString()=="ok"){
	//			command.caller->setAuID(resultobj["auID"].getString());
	//			command.caller->setCTime(resultobj["createTime"].getString());
	//			command.caller->isLogin=true;
	//		}else{
	//			command.caller->setCTime("9999");
	//		}
	//		//첫실행일경우 받아온 nick,flag 저장.
	////		if(resultobj["isFirst"].getBoolean()==true){
	////			command.caller->setNick(resultobj["nick"].getString());
	////			command.caller->setFlag(resultobj["flag"].getString());
	////		}
	//		//기존명령 다시 등록
	//		std::vector<CommandParam> vcp;
	//		for(std::map<string, CommandType>::const_iterator iter = command.commands.begin(); iter != command.commands.end(); ++iter)
	//		{
	//			JsonBox::Value param;
	//			param.loadFromString(iter->second.paramStr);
	//			vcp.push_back(CommandParam(iter->second.action, param.getObject(), iter->second.target, iter->second.selector ));
	//		}
	//		command.caller->command(vcp);
	//
	//		for(std::map<string, CommandType>::iterator iter = command.commands.begin(); iter != command.commands.end(); ++iter)
	//		{
	//			iter->second.target = 0;
	//			iter->second.selector = 0;
	//		}
	//		newToken = true;
	//	}
	
	//CCLOG("t_function 11");
	
	//@ if(resultobj["errorcode"].getInt()==9999){
	if(resultobj["errorcode"].asInt()==9999){
		//CCLOG("t_function errorcode");
		command.caller->setCTime("9999");
		command.caller->errorCount++;
		if(command.caller->errorCount<5){
			std::vector<CommandParam> vcp;
			for(std::map<string, CommandType>::const_iterator iter = command.commands.begin(); iter != command.commands.end(); ++iter)
			{
				//@ JsonBox::Value param;
				Json::Value param;
				
				//@param.loadFromString(iter->second.paramStr);
				param = GraphDogLib::StringToJsonObject(iter->second.paramStr);
				CommandParam cp;
				cp.action = iter->second.action;
				//@ cp.param = param.getObject();
				cp.param = param;
				//@@cp.selector = iter->second.selector;
				//@@cp.target = iter->second.target;
				cp.func=iter->second.func;
				vcp.push_back(cp);
			}
			command.caller->command(vcp);
			for(std::map<string, CommandType>::iterator iter = command.commands.begin(); iter != command.commands.end(); ++iter)
			{
				//@@iter->second.target = 0;
				//@@iter->second.selector = 0;
				iter->second.func=NULL;
			}
		}
		//newToken = true;
	}
	
	//	if(newToken == false) // 새토큰 발급이 아닌 경우.
	//	{
	//		for(auto iter = command.commands.begin(); iter != command.commands.end(); ++iter)
	//		{
	//			CommandType test = iter->second;
	//			CCLOG("dummy");
	//		}
	
	
	CCLOG("check8");
	//CCLOG("t_function 12");
	//@if(resultobj["state"].getString()=="ok"){
	if(resultobj["state"].asString()=="ok"){
		
		//CCLOG("t_function 13");
		command.caller->errorCount=0;
	}
	
	
	//CCLOG("t_function 14");
	//@ if(resultobj["timestamp"].getInt()<GraphDog::get()->timestamp){
//	if(resultobj["timestamp"].asInt64()<GraphDog::get()->timestamp && resultCode != CURLE_CHUNK_FAILED){
//		
//		CCLOG("t_function error hack!!! %lld,%lld",resultobj["timestamp"].asInt64(),GraphDog::get()->timestamp);
//		resultCode=CURLE_CHUNK_FAILED;
//		resultobj["state"]="error";
//		resultobj["errorMsg"]="hack!!";
//		resultobj["result"]["code"]=GDSECURITY;
//		//@ GraphDog::get()->timestamp=resultobj["timestamp"].getInt();
//		
//	}
	
	CCLOG("check9");
	GraphDog::get()->timestamp=resultobj.get("timestamp", 0).asInt64();
	GraphDog::get()->date=resultobj.get("date", 0).asInt64();
	GraphDog::get()->weekNo=resultobj.get("weekNo", 0).asInt();
	GraphDog::get()->localTimestamp=GraphDog::get()->getTime();
	
	
	CCLOG("check10");
	command.result = resultobj;
	command.chunk.resultCode = resultCode;
	//	}
	
	CCLOG("check11");
	pthread_mutex_unlock(&command.caller->t_functionMutex);
	
	CCLOG("check12");
	return NULL;
}

void GraphDog::removeCommand(cocos2d::CCObject *target)
{
  
	return;
	//GDDelegator::getInstance()->removeCommand(target);
	//	pthread_mutex_lock(&cmdsMutex);
	
	/* //@@
	 for(std::map<int, CommandsType>::iterator iter = commandQueue.begin(); iter != commandQueue.end(); ++iter)
	 {
	 for(std::map<string, CommandType>::iterator iter2 = iter->second.commands.begin(); iter2 != iter->second.commands.end(); ++iter2)
	 {
	 
	 if(iter2->second.target == target)
	 {
	 iter2->second.target = 0;
	 iter2->second.selector = 0;
	 }
	 }
	 }
	 */
	
	//	pthread_mutex_unlock(&cmdsMutex);
}


void GraphDog::receivedCommand(float dt)
{
	//##
	for(std::map<int, CommandsType>::iterator commandQueueIter = commandQueue.begin(); commandQueueIter != commandQueue.end();)
	{
		CommandsType commands = commandQueueIter->second;
		try {
			if(commands.chunk.resultCode == CURLE_AGAIN)
			{
				//CCLOG("commands.chunk.resultCode == CURLE_AGAIN");
				throw commands.chunk.resultCode;
			}
			else if(commands.chunk.resultCode != CURLE_OK)
			{
				
				CCLOG("commands.chunk.resultCode != CURLE_OK");
				//다시시도하시겠습니까 팝업펑크가 있으면 띄운다.
				if(commandRetryFunc!=nullptr && commands.errorCnt>=0){
					CCLOG("commandRetryFunc!=nullptr");
					std::vector<CommandParam> vcp;
					for(std::map<string, CommandType>::const_iterator iter = commands.commands.begin(); iter != commands.commands.end(); ++iter)
					{
						Json::Value param;
						param = GraphDogLib::StringToJsonObject(iter->second.paramStr);
						CommandParam cp;
						cp.action = iter->second.action;
						cp.param = param;
						cp.func=iter->second.func;
						vcp.push_back(cp);
					}
					
					CCLOG("commands.errorCnt<=1");
					if(commands.errorCnt<=1){
						CCLOG("commands.chunk.resultCode != CURLE_OK");
						this->command(vcp,commands.errorCnt+1);
					}else{
						commandRetryFunc(vcp);
					}
				}else{
				
					for(std::map<string, CommandType>::iterator commandTypeIter = commandQueueIter->second.commands.begin(); commandTypeIter != commandQueueIter->second.commands.end(); ++commandTypeIter)
					{
						CCLOG("receivedCommand error");
						//@ JsonBox::Object resultobj;
						Json::Value resultobj;
						CommandType command = commandTypeIter->second;
						resultobj["state"] = "error";
						resultobj["errorMsg"] = "check your network state";
						resultobj["errorCode"] = 1002;
						resultobj["result"]["code"]=GDCHECKNETWORK;
						
						//callbackparam
						if(command.paramStr!=""){
							//@ JsonBox::Object param =  GraphDogLib::StringToJsonObject(command.paramStr);
							Json::Value param =  GraphDogLib::StringToJsonObject(command.paramStr);
							//@ resultobj["param"]=JsonBox::Value(param);
							resultobj["param"]=param;
						}
						//@@if(command.target!=0 && command.selector!=0)
						//@@((command.target)->*(command.selector))(resultobj);
						CCLOG("graphdog:: error call func for %s",command.action.c_str());
						if(command.func!=NULL){
							command.func(resultobj);
						}else{
							CCLOG("graphdog:: error call func back is null for %s",command.action.c_str());
						}
						if(commandFinishedFunc!=nullptr)commandFinishedFunc();
						CCLOG("graphdog:: error call func finished for %s",command.action.c_str());
					}
				
				}
				throw commands.chunk.resultCode;
			}
			
			//@ JsonBox::Object resultobj = commands.result; //GraphDogLib::StringToJsonObject(resultStr);// result.getObject();
			CCLOG("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ get data, sendSize:%d, getSize:%d $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$",commands.commandStr.length()*2,commands.chunk.size);
			Json::Value resultobj = commands.result;
			
			if(resultobj.get("checkDeviceError", false).asBool()){
				CCLOG("GRAPHDOGERROR CHECKDEVICEERROR!!!!!!!!!!!!!!!!!!!!! client dviceID is %d , cmdNo is %d",this->deviceID,this->lastCmdNo);
				this->log("resultobj : "+resultobj.asString());
				this->lastCmdNo=0;
				if(this->duplicateLoginFunc!=nullptr)this->duplicateLoginFunc();
				
			}else if(resultobj.get("cmdNoError", false).asBool()){
				CCLOG("GRAPHDOGERROR CMDNOERROR!!!!!!!!!!!!!!!!!!!!! client dviceID is %d , cmdNo is %d",this->deviceID,this->lastCmdNo);
				this->log("resultobj : "+resultobj.asString());
				this->lastCmdNo=0;
				if(this->cmdNoErrorFunc!=nullptr)this->cmdNoErrorFunc();
				
			}else if(resultobj.get("longTimeError", false).asBool()){
				
				CCLOG("GRAPHDOGERROR LONGTIMEERROR!!!!!!!!!!!!!!!!!!!!! client dviceID is %d , cmdNo is %d",this->deviceID,this->lastCmdNo);
				this->log("resultobj : "+resultobj.asString());
				this->lastCmdNo=0;
				if(this->longTimeErrorFunc!=nullptr)this->longTimeErrorFunc();
			
			}else{
				bool retryCnt=false;
				std::vector<CommandParam> vcp;
				for(std::map<string, CommandType>::iterator iter2 = commands.commands.begin(); iter2 != commands.commands.end(); ++iter2)
				{
					CommandType ct = iter2->second;
					Json::Value oParam =  ct.paramStr;
					
					if(ct.action=="login"){
						if(resultobj.get("deviceID", 0).asInt()!=0){
							this->deviceID=resultobj.get("deviceID", 0).asInt();
							//this->lastCmdNo=1;
							CCLOG("getDevice ID login is %d",this->deviceID);
						}else{
							this->deviceID=0;
							CCLOG("fail login");
						}
					}else if(ct.action=="join"){
						this->deviceID=resultobj.get("deviceID", 0).asInt();
						//this->lastCmdNo=1;
						CCLOG("getDevice ID join is %d",this->deviceID);
					}else if(ct.action=="dropoutuser"){
						this->deviceID=0;
						this->lastCmdNo=0;
					}
					
					if(resultobj[iter2->first.c_str()]["log"].isArray()){
						CCLOG("###################################[START for %s ]##########################################",ct.action.c_str());
						for(int i=0;i<resultobj[iter2->first.c_str()]["log"].size();i++){
									string log = resultobj[iter2->first.c_str()]["log"][i].asString();
									CCLOG("%s",log.c_str());
									
						}
						resultobj[iter2->first.c_str()]["log"].clear();
						Json::StyledStreamWriter w;
						
						CCLOG("=====================================[ Result ]=============================================");
						CCLOG("Name : %s, Code : %d, Message: %s",resultobj[iter2->first.c_str()]["result"].get("name", "None").asString().c_str(),resultobj[iter2->first.c_str()]["result"].get("code", 0).asInt(),resultobj[iter2->first.c_str()]["result"].get("message", "message is nothing").asString().c_str());
						
						
						Json::StyledWriter wr;
						CCLOG("%s",wr.write(resultobj[iter2->first.c_str()]).c_str());
						CCLOG("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@[END for %s ]@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@",ct.action.c_str());
					}
					
					
					if(!oParam.get("retry", false).asBool() || resultobj[iter2->first.c_str()]["result"].get("code", 0).asInt()==GDSUCCESS || oParam.get("passCode", -1).asInt()==resultobj[iter2->first.c_str()]["result"].get("code", 0).asInt()){
						
						
						CCLOG("graphdog:: call func for %s",ct.action.c_str());
						if(ct.func!=NULL){
							ct.func(resultobj[iter2->first.c_str()]);
						}else{
							CCLOG("graphdog:: call func is null for %s",ct.action.c_str());
						}
						CCLOG("graphdog:: call func finished for %s",ct.action.c_str());
						if(commandFinishedFunc!=nullptr)commandFinishedFunc();
						CCLOG("graphdog:: call commandFinishedFunc finished for %s",ct.action.c_str());
					
					}else if(resultobj[iter2->first.c_str()]["result"].get("code", 0).asInt()!=GDSUCCESS){
						retryCnt=true;
						Json::Value param;
						param = GraphDogLib::StringToJsonObject(iter2->second.paramStr);
						CommandParam cp;
						cp.action = iter2->second.action;
						cp.param = param;
						cp.func=iter2->second.func;
						vcp.push_back(cp);
					}
				}
				
				if(retryCnt){
					if(commands.errorCnt<=1){
                        CCLOG("commands.errorCnt<=1");
						this->command(vcp,commands.errorCnt+1);
					}else{
                        CCLOG("!! commands.errorCnt<=1");
						commandRetryFunc(vcp);
					}
				}
			}
			
			//메모리도 해제
			if(commands.chunk.memory)
				free(commands.chunk.memory);
			
			//명령을 삭제한다.
			commandQueue.erase(commandQueueIter++);
		}
		catch (const CURLcode& resultCode) {
			if(resultCode == CURLE_AGAIN)
			{
				++commandQueueIter;
			}
			else if(resultCode != CURLE_OK)
			{
				if(commands.chunk.memory)
					free(commands.chunk.memory);
				commandQueue.erase(commandQueueIter++);
			}
		}
	}
}
//std::string GraphDog::getDeviceID() {
//	//    string _id;
//	//
//	//#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
//	////    char* macAddress=(char*)malloc(18);
//	////	std::string ifName="en0";
//	////	int  success;
//	////	struct ifaddrs * addrs;
//	////	struct ifaddrs * cursor;
//	////	const struct sockaddr_dl * dlAddr;
//	////	const unsigned char* base;
//	////	int i;
//	////
//	////	success = getifaddrs(&addrs) == 0;
//	////	if (success) {
//	////		cursor = addrs;
//	////		while (cursor != 0) {
//	////			if ( (cursor->ifa_addr->sa_family == AF_LINK)
//	////				&& (((const struct sockaddr_dl *) cursor->ifa_addr)->sdl_type == 0x06) && strcmp(ifName.c_str(),  cursor->ifa_name)==0 ) {
//	////				dlAddr = (const struct sockaddr_dl *) cursor->ifa_addr;
//	////				base = (const unsigned char*) &dlAddr->sdl_data[dlAddr->sdl_nlen];
//	////				strcpy(macAddress, "");
//	////				for (i = 0; i < dlAddr->sdl_alen; i++) {
//	////					if (i != 0) {
//	////						strcat(macAddress, ":");
//	////					}
//	////					char partialAddr[3];
//	////					sprintf(partialAddr, "%02X", base[i]);
//	////					strcat(macAddress, partialAddr);
//	////
//	////				}
//	////			}
//	////			cursor = cursor->ifa_next;
//	////		}
//	////
//	////		freeifaddrs(addrs);
//	////	}
//	////    _id = macAddress;
//	//    _id = [[OpenUDID value] UTF8String];
//	//
//	//#elif CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
//	//	//_id = JNIKelper::getInstance()->callJava_getUDID();
//	//	JniMethodInfo minfo;
//	//	jobject jobj;
//	//
//	//	CCLOG("call getdeviceid");
//	//
//	//	if(JniHelper::getStaticMethodInfo(minfo, packageName.c_str(), "getActivity", "()Ljava/lang/Object;"))
//	//	{
//	//		jobj = minfo.env->NewGlobalRef(minfo.env->CallStaticObjectMethod(minfo.classID, minfo.methodID));
//	//		JniMethodInfo __minfo;
//	//		__minfo.classID = 0;
//	//		__minfo.env = 0;
//	//		__minfo.methodID = 0;
//	//		if(JniHelper::getMethodInfo(__minfo, packageName.c_str(), "getUDID", "()Ljava/lang/String;"))
//	//		{
//	//			jstring jstrTitle = (jstring) __minfo.env->CallObjectMethod(jobj, __minfo.methodID);
//	//
//	//			if(jstrTitle)
//	//			{
//	//				char* pszTitle = (char*)__minfo.env->GetStringUTFChars(jstrTitle, JNI_FALSE);
//	//
//	//				_id = pszTitle;
//	//				__minfo.env->ReleaseStringUTFChars(jstrTitle, pszTitle);
//	//				__minfo.env->DeleteLocalRef(jstrTitle);
//	//
//	//			}
//	//			__minfo.env->DeleteLocalRef(__minfo.classID);
//	//		}
//	//
//	//		minfo.env->DeleteGlobalRef(jobj);
//	//		minfo.env->DeleteLocalRef(minfo.classID);
//	//	}
//	//
//	//#endif
//	//    //string _id = base64_decode(macAddress);
//	//	return toBase64(_id);
//	CCAssert(true, "assert");
//	CCAssert(false, "assert");
//	return "none";
//}
//std::string	GraphDog::getDeviceInfo()
//{
//
//	//	if(this->deviceInfo!="")return deviceInfo;
//	//	string ret = "unknown";
//	//#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
//	//	size_t size;
//	//	string _h = "h";
//	//	string _w = "w";
//	//	string _dot = ".";
//	//	string _m = "m";
//	//	string _a = "a";
//	//	string _c = "c";
//	//	string _i = "i";
//	//	string _n = "n";
//	//	string _e = "e";
//	//	string hw_machine = _h + _w + _dot + _m + _a + _c + _h + _i + _n + _e;
//	//
//	//	sysctlbyname(hw_machine.c_str(), NULL, &size, NULL, 0);
//	//	char *machine = (char*)malloc(size);
//	//	sysctlbyname(hw_machine.c_str(), machine, &size, NULL, 0);
//	//	ret = machine;
//	//	free(machine);
//	//#elif CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
//	//	JniMethodInfo minfo;
//	//	jobject jobj;
//	//
//	//	CCLOG("call getdeviceinfo");
//	//
//	//	if(JniHelper::getStaticMethodInfo(minfo, packageName.c_str(), "getActivity", "()Ljava/lang/Object;"))
//	//	{
//	//		jobj = minfo.env->NewGlobalRef(minfo.env->CallStaticObjectMethod(minfo.classID, minfo.methodID));
//	//		JniMethodInfo __minfo;
//	//		__minfo.classID = 0;
//	//		__minfo.env = 0;
//	//		__minfo.methodID = 0;
//	//
//	//		if(JniHelper::getMethodInfo(__minfo, packageName.c_str(), "getDeviceInfo", "()Ljava/lang/String;"))
//	//		{
//	//			jstring jstrTitle = (jstring) __minfo.env->CallObjectMethod(jobj, __minfo.methodID);
//	//
//	//			if(jstrTitle)
//	//			{
//	//				char* pszTitle = (char*)__minfo.env->GetStringUTFChars(jstrTitle, JNI_FALSE);
//	//
//	//				ret = pszTitle;
//	//				__minfo.env->ReleaseStringUTFChars(jstrTitle, pszTitle);
//	//				__minfo.env->DeleteLocalRef(jstrTitle);
//	//
//	//			}
//	//			__minfo.env->DeleteLocalRef(__minfo.classID);
//	//		}
//	//		minfo.env->DeleteGlobalRef(jobj);
//	//		minfo.env->DeleteLocalRef(minfo.classID);
//	//	}
//	//
//	//#endif
//	//	return ret;
//	//	return toBase64( desEncryption(sKey, ret) );
//	//	return GraphDogLib::gdkeyEnc(ret, sKey);
//
//	CCAssert(true, "assert");
//	CCAssert(false, "assert");
//	return "none";
//}

GraphDog* graphdog; // = GraphDog::get();
