#pragma once

#include "GameObject.h"

#define KOOPAS_WALKING_SPEED 0.03f;

#define KOOPAS_BBOX_WIDTH 16
#define KOOPAS_BBOX_HEIGHT 26
#define KOOPAS_BBOX_HEIGHT_DIE 16

#define KOOPAS_STATE_WALKING 100
#define KOOPAS_STATE_DIE 200
#define KOOPAS_STATE_PREREVIVE 300
#define KOOPAS_STATE_SHELL 400


#define KOOPAS_ANI_WALKING_LEFT 0
#define KOOPAS_ANI_WALKING_RIGHT 1
#define KOOPAS_ANI_DIE 2
#define KOOPAS_ANI_PREREVIVE 3

#define KOOPAS_ANI_SHELL_WALKING_RIGHT 4
#define KOOPAS_ANI_SHELL_WALKING_LEFT 5

#define	KOOPAS_LEVEL_NORMAL	1
#define	KOOPAS_LEVEL_SHELL		2


class CKoopas : public CGameObject
{
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	int PREREVIVE =0;
	int REVIVE = 0;
	int level;
	int MarioKick = 0;
	DWORD Prerevive_start;
	DWORD Revive_start;


public:
	CKoopas();
	virtual void SetState(int state);
	void SetLevel(int l) { level = l; };
	int GetLevel() { return level; };
	void SetMarioKick(int kick) { MarioKick = kick; };
	int GetMarioKick() { return MarioKick; };
	void StartPRE_REVIVE() { PREREVIVE = 1; SetLevel(KOOPAS_LEVEL_SHELL); Prerevive_start = GetTickCount(); }
	void StartRevive() { REVIVE = 1;  SetLevel(KOOPAS_LEVEL_NORMAL); Revive_start = GetTickCount(); }
	
};