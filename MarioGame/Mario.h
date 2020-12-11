#pragma once
#include "GameObject.h"

#define MARIO_WALKING_SPEED		0.15f 
#define MARIO_WALKING_FAST_SPEED		0.2f 
//0.1f
#define MARIO_JUMP_SPEED_Y		0.5f
#define MARIO_FLY_SPEED_Y		0.2f

#define MARIO_JUMP_HIGHT_SPEED_Y		0.6f


#define MARIO_JUMP_DEFLECT_SPEED 0.5f
#define MARIO_GRAVITY			0.002f
#define MARIO_GRAVITY_FALL		0.0000000005f
#define MARIO_DIE_DEFLECT_SPEED	 0.5f

#define MARIO_STATE_IDLE			0
#define MARIO_STATE_WALKING_RIGHT	100
#define MARIO_STATE_WALKING_LEFT	200
#define MARIO_STATE_JUMP			300
#define MARIO_STATE_DIE				400
#define MARIO_STATE_KICK			500
#define MARIO_STATE_SIT				600
#define MARIO_STATE_HOLDKOOPAS				900
#define MARIO_STATE_FLY			700
#define MARIO_STATE_FAST_WALKING			800
#define MARIO_STATE_HIGHT_JUMP			1000
#define MARIO_STATE_SPIN			1010
#define MARIO_STATE_FALL			1020

#define MARIO_STATE_FLY_RIGHT			1030
#define MARIO_STATE_FLY_LEFT			1040

#define MARIO_STATE_FAST_WALKING_RIGHT			1050
#define MARIO_STATE_FAST_WALKING_LEFT			1060
#define GREEN_MARIO_STATE_JUMP_UP			1070
#define GREEN_MARIO_STATE_JUMP_DOWN			1080
#define RED_MARIO_STATE_FALL			1090

#define MARIO_ANI_BIG_IDLE_RIGHT		0
#define MARIO_ANI_BIG_IDLE_LEFT			1
#define MARIO_ANI_SMALL_IDLE_RIGHT		2
#define MARIO_ANI_SMALL_IDLE_LEFT			3

#define MARIO_ANI_TAIL_IDLE_RIGHT		19
#define MARIO_ANI_TAIL_IDLE_LEFT		20
#define MARIO_ANI_TAIL_WALKING_RIGHT			21
#define MARIO_ANI_TAIL_HOLD_LEFT			22

#define MARIO_ANI_TAIL_WALKING_LEFT			45

#define MARIO_ANI_TAIL_WALKING_FAST_RIGHT			52
#define MARIO_ANI_TAIL_WALKING_FAST_LEFT			53
#define MARIO_ANI_BIG_WALKING_FAST_RIGHT			54
#define MARIO_ANI_BIG_WALKING_FAST_LEFT			55
#define MARIO_ANI_BIG_BRAKING_RIGHT			56
#define MARIO_ANI_BIG_BRAKING_LEFT		57

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
#define MARIO_ANI_TAIL_SPIN		49

#define MARIO_ANI_TAIL_FLY_RIGHT		39
#define MARIO_ANI_TAIL_FLY_LEFT		40

#define MARIO_ANI_TAIL_FALL_RIGHT		50
#define MARIO_ANI_TAIL_FALL_LEFT		51

#define MARIO_ANI_SMALL_HOLD_RIGHT		41
#define MARIO_ANI_SMALL_HOLD_LEFT		42
#define MARIO_ANI_BIG_HOLD_RIGHT		43
#define MARIO_ANI_BIG_HOLD_LEFT		44
#define MARIO_ANI_TAIL_HOLD_RIGHT		46
#define MARIO_ANI_FIRE_HOLD_RIGHT		47
#define MARIO_ANI_FIRE_HOLD_LEFT		48

#define MARIO_ANI_DIE				8

#define GREEN_MARIO_ANI_BIG_IDLE_RIGHT			54
#define GREEN_MARIO_ANI_BIG_IDLE_LEFT		55
#define GREEN_MARIO_ANI_BIG_WALKING_RIGHT			56
#define GREEN_MARIO_ANI_BIG_WALKING_LEFT			57
#define GREEN_MARIO_ANI_JUMP_RIGHT		58
#define GREEN_MARIO_ANI_JUMP_LEFT		59

#define	MARIO_LEVEL_SMALL	1
#define	MARIO_LEVEL_BIG		2
#define MARIO_LEVEL_TAIL	3
#define MARIO_LEVEL_FIRE	4

#define MARIO_TYPE_RED	0
#define MARIO_TYPE_GREEN	1

#define MARIO_BIG_BBOX_WIDTH  15
#define MARIO_BIG_BBOX_HEIGHT 27

#define MARIO_SMALL_BBOX_WIDTH  13
#define MARIO_SMALL_BBOX_HEIGHT 15

#define MARIO_UNTOUCHABLE_TIME 5000


class CMario : public CGameObject
{
	int level;
	int type;
	int jump = 0;
	int greenJump = 0;
	int hold=0;
	int aniHold = 0;
	int shootFire=0;
	int untouchable;
	//int preidle=0;
	int KickKoopas=0;
	int AniKick = 0;
	int Spin = 0;

	bool isAppeared = true;
	bool isGreenAbleWalk = true;
	bool isRedAbleWalk = true;

	int FirstTimeFly=0;
	int CanFly=0;
	DWORD fly_start = 0;

	//DWORD flying_start = 0;
	DWORD untouchable_start;
	DWORD kick_start;
	DWORD spin_start;
	float start_x;			// initial position of Mario at scene
	float start_y;
	DWORD preIDLE_start;
	DWORD speedup_start;

	int speedLevel = 1;
	int score=0;
	int coin=0;


public:

	CMario(float x = 0.0f, float y = 0.0f);
	CMario(int type, float x = 0.0f, float y = 0.0f);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	virtual void Render();
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount(); }
	void StartKick() { kick_start = GetTickCount(); }
	/*void StartPreIdle() { preidle = 1; preIDLE_start = GetTickCount(); }*/
	void SetState(int state);
	void SetLevel(int l) { level = l; }
	int GetLevel() { return level; };
	int Jumping() { return jump; };
	void SetJumping(int jump) { this->jump = jump; };
	int GetJumping() { return jump; };

	int JumpingGreen() { return greenJump; };
	void SetJumpingGreen(int jump) { greenJump = jump; };
	int GetJumpingGreen() { return greenJump; };
	void Reset();

	void SetKickKoopas(int kickkoopas) { KickKoopas = kickkoopas; };
	int GetKickKoopas() { return KickKoopas; };

	void SetAniKick(int kick) { AniKick = kick; };
	int GetAniKick() { return AniKick; };
	int GetHolding() { return this->hold; };
	void SetHolding(int hold) {
		this->hold = hold;
	};

	int GetAniHolding() { return this->aniHold; };
	void SetAniHolding(int anihold) { this->aniHold = anihold; };

	void SetSpin(int s) { Spin = s; }
	int GetSpin() { return Spin; };
	void StartSpin() { spin_start = GetTickCount(); };

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void SetShoot(int s) { shootFire = s; };
	int GetShoot() { return shootFire; };
	int GetFirstTimeFly() { return FirstTimeFly; };
	void SetFirstTimeFly(int fly) { FirstTimeFly = fly; };
	int GetCanFly() { return CanFly; };
	void SetCanFly(int fly) { CanFly = fly; };

	void SetFlyingStart() { fly_start = GetTickCount(); }
	DWORD GetFlyingStart() { return fly_start; };
	void StartFlying() { fly_start = GetTickCount(); }

	DWORD Getspeedup_start(){ return speedup_start; }
	void Setspeedup_start(int value) { speedup_start = value; };
	
	void StartSpeedup() { speedup_start = GetTickCount(); }
	int GetspeedLevel() { return speedLevel; }
	void SetspeedLevel(int value) { speedLevel = value; }
	int GetType(){ return type; }
	void SetType(int type){ this->type = type; }

	void SetIsAppeared(bool value) { isAppeared = value; }
	void SetIsAbleGreenWalk(bool value) { isGreenAbleWalk = value; }
	void SetIsAbleRedWalk(bool value) { isRedAbleWalk = value; }
	int GetScore() { return score; };
	int GetCoin() { return coin; };


};