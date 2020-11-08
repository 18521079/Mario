#pragma once
#include "GameObject.h"

#define GOOMBA_WALKING_SPEED 0.05f;

#define GOOMBA_BBOX_WIDTH 16
#define GOOMBA_BBOX_HEIGHT 15
#define GOOMBA_BBOX_HEIGHT_DIE 9

#define GOOMBA_STATE_WALKING 100
#define GOOMBA_STATE_DIE 200
#define GOOMBA_STATE_DISAPPEAR 300
#define GOOMBA_STATE_DIE_FALL 400

#define GOOMBA_ANI_WALKING 0
#define GOOMBA_ANI_DIE 1


class CGoomba : public CGameObject
{
	int Die = 0;
	DWORD Die_start = 0;
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

public:
	CGoomba();
	virtual void SetState(int state);
	void SetTickCount() { Die_start = GetTickCount(); };
	void GoombaDie() { Die = 1; };
};