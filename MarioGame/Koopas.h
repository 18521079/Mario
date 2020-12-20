#pragma once

#include "GameObject.h"

#define KOOPAS_WALKING_SPEED 0.09f;
#define KOOPAS_BBOX_WIDTH 16
#define KOOPAS_BBOX_HEIGHT 26
#define KOOPAS_BBOX_HEIGHT_DIE 16

#define KOOPAS_STATE_WALKING_RIGHT 100
#define KOOPAS_STATE_WALKING_LEFT 700
#define KOOPAS_STATE_SHELL 200
#define KOOPAS_STATE_SHELL_MARIOSPIN 800
#define KOOPAS_STATE_RENEW 300
#define SHELL_STATE_WALKING_RIGHT 400
#define SHELL_STATE_WALKING_LEFT 600
#define SHELL_STATE_FALL 900
#define KOOPAS_STATE_DIE 500
#define KOOPAS_STATE_DIE_FALL 1000
#define KOOPAS_STATE_WALKING_RIGHT_INTRO 1100


#define KOOPAS_ANI_WALKING_LEFT 0
#define KOOPAS_ANI_WALKING_RIGHT 1
#define KOOPAS_ANI_SHELL 2
#define GREENKOOPAS_ANI_SHELL 10
#define KOOPAS_ANI_PREREVIVE 3
#define BACK_KOOPAS_ANI_SHELL 12

#define GREENKOOPAS_ANI_FLYING_LEFT 8
#define GREENKOOPAS_ANI_FLYING_RIGHT 9

#define GREENKOOPAS_ANI_WALKING_LEFT 6
#define GREENKOOPAS_ANI_WALKING_RIGHT 7



#define KOOPAS_ANI_SHELL_WALKING_RIGHT 4
#define GREENKOOPAS_ANI_SHELL_WALKING_RIGHT 11
#define KOOPAS_ANI_SHELL_WALKING_LEFT 5
#define GREENKOOPAS_ANI_SHELL_WALKING_LEFT 11

#define	KOOPAS_LEVEL_NORMAL	1
#define	KOOPAS_LEVEL_SHELL		2

#define KOOPAS_TYPE_RED 1
#define KOOPAS_TYPE_GREEN 2
#define KOOPAS_TYPE_WING 3
#define KOOPAS_TYPE_SHELL 4



class CKoopas : public CGameObject
{
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	//int level;
	int MarioKick=0;
	int Hold=0;
	int type;

	DWORD timeRenew_start;
	bool isRenewStart = false;
	DWORD timeWalking_start;

	



public:
	CKoopas(int type);
	virtual void SetState(int state);
	/*void SetLevel(int l) { level = l; };
	int GetLevel() { return level; };*/
	void SetMarioKick(int kick) { MarioKick = kick; };
	int GetMarioKick() { return MarioKick; };
	void SetHolding(int h) { Hold = h; };
	int GetHolding() { return Hold; };
	void SetType(int t) { type = t; };
	int GetType() { return type; };

};