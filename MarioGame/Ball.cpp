#include "Ball.h"

CBall::CBall()
{
	SetState(BALL_STATE_INACTIVITY);
}

void CBall::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + BALL_BBOX_WIDTH;
	bottom = y + BALL_BBOX_HEIGHT;
}

void CBall::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
	x -= dx;
	y += dy;

	if (GetTickCount()- activity_start>1000 && activity==1)
	{
		activity_start = 0;
		SetState(BALL_STATE_ACTIVITY);
		SetPosition(16,119);
	}
	
	
}

void CBall::Render()
{
	int ani = BALL_ANI_DISAPPEAR;
	if (state == BALL_STATE_ACTIVITY) {
		ani = BALL_ANI_FLY;
	}
	animation_set->at(ani)->Render(x, y);

	RenderBoundingBox();
}

void CBall::SetState(int state)
{

	CGameObject::SetState(state);
	switch (state)
	{
	case BALL_STATE_ACTIVITY:
		vx = 0.01;
		vy = 0.009;
	}
}