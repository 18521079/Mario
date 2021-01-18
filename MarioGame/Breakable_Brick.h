#pragma once
#include "GameObject.h"

#define BRICK_BBOX_WIDTH  16
#define BRICK_BBOX_HEIGHT 16
#define BRICK_STATE_NORMAL 100
#define BRICK_STATE_DISAPPEAR	200
#define BRICK_STATE_COIN	300

#define BRICK_ANI_NORMAL	0
#define BRICK_ANI_COIN	1

class CBreakableBrick : public CGameObject
{
	int touch = 0;
	
public:
	
	CBreakableBrick();
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void SetState(int state);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	int GetTouch() { return touch; };
	void SetTouch(int t) { touch = t; };
	
	

};