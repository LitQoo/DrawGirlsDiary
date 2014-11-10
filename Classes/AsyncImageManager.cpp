//
//  AsyncImageManager.cpp
//  DGproto
//
//  Created by 사원3 on 2014. 10. 12..
//
//

#include "AsyncImageManager.h"
#include "AsyncImage.h"
#include <algorithm>
#include "KSUtil.h"

AsyncImageInfo::~AsyncImageInfo()
{
    CCLOG("~AsyncImageInfo : %s", load_filename.c_str());
}

AsyncImageManager* AsyncImageManager::sharedInstance()
{
	static AsyncImageManager* t_aim = NULL;
	if(t_aim == NULL)
	{
		t_aim = new AsyncImageManager();
		t_aim->myInit();
	}
	return t_aim;
}

void AsyncImageManager::regiAsyncImage(AsyncImage* t_ai)
{
	if(ready_ai_list.empty())
	{
		AsyncImageInfo* t_info = new AsyncImageInfo();
		t_info->load_filename = t_ai->m_filename;
		t_info->m_ai_list.push_back(t_ai);
		ready_ai_list.push_back(t_info);
        CCLOG("push : %s", t_info->load_filename.c_str());
		t_ai->is_loading = true;
		t_info->is_loading = true;
		CCTextureCache::sharedTextureCache()->addImageAsync(t_info->load_filename.c_str(), this, callfuncO_selector(AsyncImageManager::asyncedImage), false, "", true);
	}
	else
	{
		vector<AsyncImageInfo*>::iterator t_iter;
		for(t_iter=ready_ai_list.begin();t_iter!=ready_ai_list.end();++t_iter)
		{
			if((*t_iter)->load_filename == t_ai->m_filename)
				break;
		}
		
		if(t_iter == ready_ai_list.end())
		{
			AsyncImageInfo* t_info = new AsyncImageInfo();
			t_info->load_filename = t_ai->m_filename;
			t_info->m_ai_list.push_back(t_ai);
			ready_ai_list.push_back(t_info);
            CCLOG("push2 : %s", t_info->load_filename.c_str());
		}
		else
		{
			t_ai->is_loading = (*t_iter)->is_loading;
			(*t_iter)->m_ai_list.push_back(t_ai);
		}
	}
}

void AsyncImageManager::unregiAsyncImage(AsyncImage* t_ai)
{
    CCLOG("unregiAsyncImage : %s", t_ai->m_filename.c_str());
    
	vector<AsyncImageInfo*>::iterator t_iter;
	for(t_iter=ready_ai_list.begin();t_iter!=ready_ai_list.end();++t_iter)
	{
		if((*t_iter)->load_filename == t_ai->m_filename)
			break;
	}
	
	if(t_iter != ready_ai_list.end())
	{
        vector<AsyncImage*>::iterator t_iter2 = find((*t_iter)->m_ai_list.begin(), (*t_iter)->m_ai_list.end(), t_ai);
		if(t_iter2 != (*t_iter)->m_ai_list.end())
		{
			(*t_iter)->m_ai_list.erase(t_iter2);
			if(!(*t_iter)->is_loading && (*t_iter)->m_ai_list.empty())
			{
                CCLOG("unregi erase : %s", (*t_iter)->load_filename.c_str());
                (*t_iter)->release();
				ready_ai_list.erase(t_iter);
			}
		}
	}
}

void AsyncImageManager::asyncedImage(CCObject* t_obj)
{
	CCLOG("loaded image : %s", t_obj->getStringData().c_str());
	
	myAIM->loaded_cnt++;
	bool is_removeUnusedTexture = false;
	if(myAIM->loaded_cnt >= 6)
	{
        myAIM->loaded_cnt = 0;
		is_removeUnusedTexture = true;
	}
	
	for(int i=0;i<ready_ai_list.size();i++)
	{
		if(ready_ai_list[i]->is_loading)
		{
			ready_ai_list[i]->is_loading = false;
			for(int j=0;j<ready_ai_list[i]->m_ai_list.size();j++)
			{
				AsyncImage* t_ai = ready_ai_list[i]->m_ai_list[j];
				t_ai->is_loading = false;
				t_ai->loadedImage((CCTexture2D*)t_obj, is_removeUnusedTexture);
                if(is_removeUnusedTexture)
                    is_removeUnusedTexture = false;
			}
			
			vector<AsyncImageInfo*>::iterator t_iter;
			for(t_iter=ready_ai_list.begin();t_iter!=ready_ai_list.end();++t_iter)
			{
				if((*t_iter)->load_filename == ready_ai_list[i]->load_filename)
					break;
			}
			
			if(t_iter != ready_ai_list.end())
			{
                CCLOG("erase : %s", (*t_iter)->load_filename.c_str());
                (*t_iter)->release();
                ready_ai_list.erase(t_iter);
			}
			break;
		}
	}
	
    if(!ready_ai_list.empty())
    {
        AsyncImageInfo* t_info = ready_ai_list.front();
        CCLOG("next filename : %s", t_info->load_filename.c_str());
        t_info->is_loading = true;
        for(int i=0;i<t_info->m_ai_list.size();i++)
        {
            t_info->m_ai_list[i]->is_loading = true;
        }
        CCLOG("next addImageAsync : %s", t_info->load_filename.c_str());
        CCTextureCache::sharedTextureCache()->addImageAsync(t_info->load_filename.c_str(), this, callfuncO_selector(AsyncImageManager::asyncedImage), false, "", true);
    }
}

