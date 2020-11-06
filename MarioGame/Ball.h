#pragma once
#pragma once
#include "GameObject.h"

#define BALL_FLY_SPEED 0.05f;

#define BALL_BBOX_WIDTH 8
#define BALL_BBOX_HEIGHT 8

#define BALL_STATE_ACTIVITY 100
#define BALL_STATE_INACTIVITY 200


#define BALL_ANI_FLY 0
#define BALL_ANI_DISAPPEAR 0


class CBall : public CGameObject
{
	int activity = 0;
	DWORD activity_start;
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

public:
	CBall();
	virtual void SetState(int state);
	void ActivityStart() { activity_start = GetTickCount(); activity = 1; SetState(BALL_STATE_ACTIVITY); };
	
};

