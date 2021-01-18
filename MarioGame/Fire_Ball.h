#pragma once
#include"GameObject.h"

#define FIREBALL_BBOX_WIDTH  7
#define FIREBALL_BBOX_HEIGHT 8

#define	FIREBALL_ANI_FLY 0


class CFireBall : public CGameObject
{
	int Fly =0;
	//int count = 0;
	float Y;
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	public:
	int GetFly() { return Fly; };
	void SetFly(int fly) { Fly = fly; };
	DWORD Firinng_start;
	void FiringStart() { Fly = 1; Firinng_start = GetTickCount(); };
	void SetY(float y) { Y = y; };
	CFireBall();
};

