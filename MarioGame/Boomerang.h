#pragma once
#include "GameObject.h"
#define BOOMERANG_BBOX_WIDTH	16
#define BOOMERANG_BBOX_HEIGHT	16

#define BOOMERANG_STATE_UP	100
#define BOOMERANG_STATE_DOWN	200
#define BOOMERANG_STATE_AGAIN	300


class CBoomerang : public CGameObject
{
	int down=0;
	int up=0;
	int again=0;
	DWORD down_start;
	DWORD up_start;
	DWORD again_start;


	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void SetState(int state);
	public:
	CBoomerang();
	void StartDown() { down = 1, down_start = GetTickCount(); };
	void StartUp() { up = 1, up_start = GetTickCount(); };
	void StartAgain() { again = 1, again_start = GetTickCount(); };

};

