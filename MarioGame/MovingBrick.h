#pragma once
#include"GameObject.h"
#define MOVING_PLATTFORM_BBOX_WIDTH 48
#define MOVING_PLATTFORM_BBOX_HEIGHT 16

class CMovingBrick : public CGameObject
{

public:
	
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	virtual void SetState(int state);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	CMovingBrick();
	
};
