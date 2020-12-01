#pragma once
#include"Goomba.h"
//#define GOOMBANORMAL_STATE_WALKING 100
//#define GOOMBANORMAL_STATE_DIE 200
#define GOOMBAWING_STATE_WALKING 500
//
//#define GOOMBANORMAL_ANI_WALKING 0
//#define GOOMBANORMAL_ANI_DIE 1
#define GOOMBAWING_ANI_WALKING 2
#define GOOMBA_STATE_DIE_FALL 400



class CWingGoomba: public CGoomba
{
	int Die = 0;
	int Y;
	DWORD Die_start = 0;
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	public:
	CWingGoomba();
	void SetTickCount() { Die_start = GetTickCount(); };
	void GoombaDie() { Die = 1; };

	virtual void SetState(int state);
};

