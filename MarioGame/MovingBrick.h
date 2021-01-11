#pragma once
#include"GameObject.h"
#define MOVING_PLATTFORM_BBOX_WIDTH 48
#define MOVING_PLATTFORM_BBOX_HEIGHT 16
#define BRICK_STATE_MOVING 1
#define BRICK_STATE_FALLING 2

class CMovingBrick : public CGameObject
{

public:
	CMovingBrick();
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	virtual void SetState(int state);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);

	
};
