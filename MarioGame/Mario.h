#pragma once
#include "GameObject.h"

#define MARIO_WALKING_SPEED		0.15f 
#define MARIO_WALKING_FAST_SPEED		0.9f 
//0.1f
#define MARIO_JUMP_SPEED_Y		0.5f
#define MARIO_JUMP_HIGHT_SPEED_Y		0.15f

#define MARIO_JUMP_DEFLECT_SPEED 0.5f
#define MARIO_GRAVITY			0.002f
#define MARIO_DIE_DEFLECT_SPEED	 0.5f

#define MARIO_STATE_IDLE			0
#define MARIO_STATE_WALKING_RIGHT	100
#define MARIO_STATE_WALKING_LEFT	200
#define MARIO_STATE_JUMP			300
#define MARIO_STATE_DIE				400
#define MARIO_STATE_KICK			500
#define MARIO_STATE_SIT				600

#define MARIO_STATE_JUMP_HIGHT			700
#define MARIO_STATE_FAST_WALKING			800



#define MARIO_ANI_BIG_IDLE_RIGHT		0
#define MARIO_ANI_BIG_IDLE_LEFT			1
#define MARIO_ANI_SMALL_IDLE_RIGHT		2
#define MARIO_ANI_SMALL_IDLE_LEFT			3

#define MARIO_ANI_TAIL_IDLE_RIGHT		19
#define MARIO_ANI_TAIL_IDLE_LEFT		20
#define MARIO_ANI_TAIL_WALKING_RIGHT			21
#define MARIO_ANI_TAIL_WALKING_LEFT			22

#define MARIO_ANI_BIG_WALKING_RIGHT			4
#define MARIO_ANI_BIG_WALKING_LEFT			5
#define MARIO_ANI_SMALL_WALKING_RIGHT		6
#define MARIO_ANI_SMALL_WALKING_LEFT		7
#define MARIO_ANI_SMALL_STOP_RIGHT	17
#define	MARIO_ANI_SMALL_STOP_LEFT		18


#define MARIO_ANI_BIG_JUMP_RIGHT		11
#define MARIO_ANI_BIG_JUMP_LEFT		12
#define MARIO_ANI_SMALL_JUMP_RIGHT		13
#define MARIO_ANI_SMALL_JUMP_LEFT		14
#define MARIO_ANI_TAIL_JUMP_RIGHT		23
#define MARIO_ANI_TAIL_JUMP_LEFT		24
#define MARIO_ANI_FIRE_JUMP_RIGHT		31
#define MARIO_ANI_FIRE_JUMP_LEFT		32

#define MARIO_ANI_BIG_KICK_RIGHT		16
#define MARIO_ANI_BIG_KICK_LEFT		15

#define MARIO_ANI_FIRE_IDLE_RIGHT		27
#define MARIO_ANI_FIRE_IDLE_LEFT		28
#define MARIO_ANI_FIRE_WALKING_RIGHT			29
#define MARIO_ANI_FIRE_WALKING_LEFT			30

#define MARIO_ANI_BIG_SIT_RIGHT		35
#define MARIO_ANI_BIG_SIT_LEFT		36
#define MARIO_ANI_TAIL_SIT_RIGHT	37
#define MARIO_ANI_TAIL_SIT_LEFT		38

#define MARIO_ANI_TAIL_FLY_RIGHT		39
#define MARIO_ANI_TAIL_FLY_LEFT		40



#define MARIO_ANI_DIE				8


#define	MARIO_LEVEL_SMALL	1
#define	MARIO_LEVEL_BIG		2
#define MARIO_LEVEL_TAIL	3
#define MARIO_LEVEL_FIRE	4

#define MARIO_BIG_BBOX_WIDTH  15
#define MARIO_BIG_BBOX_HEIGHT 27

#define MARIO_SMALL_BBOX_WIDTH  13
#define MARIO_SMALL_BBOX_HEIGHT 15

#define MARIO_UNTOUCHABLE_TIME 5000


class CMario : public CGameObject
{
	int level;
	int Jump = 0;
	int untouchable;
	DWORD untouchable_start;

	float start_x;			// initial position of Mario at scene
	float start_y;
	

public:

	CMario(float x = 0.0f, float y = 0.0f);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	virtual void Render();
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount(); }
	void SetState(int state);
	void SetLevel(int l) { level = l; }
	int Jumping() { return Jump; };
	void SetJumping(int jump) { Jump = jump; };
	void Reset();

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};