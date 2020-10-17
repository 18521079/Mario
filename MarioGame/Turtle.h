#pragma once
#include "GameObject.h"

#define TURTLE_WALKING_SPEED 0.05f;

#define TURTLE_BBOX_WIDTH 16
#define TURTLE_BBOX_HEIGHT 15
#define TURTLE_BBOX_HEIGHT_DIE 9

#define TURTLE_STATE_WALKING_LEFT 100
#define TURTLE_STATE_WALKING_RIGHT 200
#define TURTLE_STATE_DIE 300

#define TURTLE_ANI_WALKING_LEFT 0
#define TURTLE_ANI_WALKING_RIGHT 1
#define TURTLE_ANI_DIE 2

class CTurtle : public CGameObject
{
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();


public:
	virtual void SetState(int state);
};
