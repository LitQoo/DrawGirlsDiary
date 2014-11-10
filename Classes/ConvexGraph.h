//
//  ConvexGraph.h
//  DGproto
//
//  Created by 사원3 on 2014. 8. 5..
//
//

#ifndef __DGproto__ConvexGraph__
#define __DGproto__ConvexGraph__

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

using namespace std;

enum ConvexGraphType
{
	width = 0,
	height
};

class ConvexGraph : public CCNode
{
public:
	static ConvexGraph* create(string t_front_filename, CCRect t_front_9_out, CCRect t_front_9_in, CCSize t_full_size, ConvexGraphType t_type);
	void setPercentage(float t_percentage);
	
	void setBack(string t_back_filename);
	void setCover(string t_cover_filename, string t_mask_filename);
	
private:
	
	string front_filename;
	CCRect front_9_out;
	CCRect front_9_in;
	CCSize full_size;
	CCSize zero_size;
	ConvexGraphType m_type;
	CCScale9Sprite* front_img;
	float m_percentage;
	
	CCClippingNode* cover_clipping_node;
	CCScale9Sprite* cover_mask;
	CCSprite* cover_img;
	
	CCScale9Sprite* back_img;
	
	
	void myInit(string t_front_filename, CCRect t_front_9_out, CCRect t_front_9_in, CCSize t_full_size, ConvexGraphType t_type);
};

#endif /* defined(__DGproto__ConvexGraph__) */
