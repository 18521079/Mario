
#pragma once
#include"GameObject.h"

#define MOVING_PLATTFORM_BBOX_WIDTH 48
#define MOVING_PLATTFORM_BBOX_HEIGHT 16
#define MOVING_PLATTFORM_STATE_INACTIVE 2
#define MOVING_PLATTFORM_STATE_FALLING 1
#define MOVING_PLATTFORM_GRAVITY 0.0001f
#define MOVING_PLATTFORM_STATE_MOVING 0
class CMovingBrick : public CGameObject
{
	float entryX, entryY;

public:
	bool isAbleToActive = true;
	bool isBeingTouched = false;

	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	virtual void SetState(int state);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b, bool isEnable);
	CMovingBrick(float entryX, float entryY);
	void AbleToActive();
};

