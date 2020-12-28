#pragma once
#include "GameObject.h"

#define COIN_BBOX_WIDTH  8
#define COIN_BBOX_HEIGHT 8

#define COIN_STATE_NORMAL 100
#define COIN_STATE_DISAPPEAR 200

#define COIN_ANI_NORMAL 0
#define COIN_ANI_DISAPPEAR 1

class CCoin : public CGameObject
{
	int type;
public:
	
	virtual void Render();
	virtual void SetState(int state);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	
};