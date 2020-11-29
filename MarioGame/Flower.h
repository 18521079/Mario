#pragma once

#include "GameObject.h"

#define FLOWER_WALKING_SPEED 0.05f;

#define FLOWER_BBOX_WIDTH 16
#define FLOWER_BBOX_HEIGHT 26

#define FLOWER_STATE_WALKING_UP 0
#define FLOWER_STATE_WALKING_DOWN 100
#define FLOWER_STATE_IDLE 200
#define FLOWER_STATE_DIE 300

#define FLOWER_ANI_WALKING_LEFT 0
#define FLOWER_ANI_WALKING_RIGHT 1
#define FLOWER_ANI_SHOOT_RIGHT 2
#define FLOWER_ANI_SHOOT_LEFT 3

#define GREENFLOWER_ANI_WALKING_UP 0
#define GREENFLOWER_ANI_WALKING_DOWN 1



class CFlower : public CGameObject
{
	
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	DWORD timeFiring_start;
	bool FirstFiring = false;
	bool hasFired = false;
	int ID;
	

public:
	CFlower();
	virtual void SetState(int state);
	void SetHasFired(bool value) { hasFired = value; };
	bool GetHasFired() { return hasFired; };



	
};
