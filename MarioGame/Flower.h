#pragma once

#include "GameObject.h"

#define FLOWER_WALKING_SPEED 0.05f;

#define FLOWER_BBOX_WIDTH 16
#define FLOWER_BBOX_HEIGHT 26

#define FLOWER_STATE_WALKING 100
#define FLOWER_STATE_BALL 200

#define FLOWER_ANI_WALKING_LEFT 0
#define FLOWER_ANI_WALKING_RIGHT 1
#define FLOWER_ANI_BALL 2

class CFlower : public CGameObject
{
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

public:
	CFlower();
	virtual void SetState(int state);
};
