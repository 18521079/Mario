#include "WingGoomba.h"
#include"Mario.h"

CWingGoomba::CWingGoomba()
{
	SetState(GOOMBAWING_STATE_WALKING);
}

void CWingGoomba::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + GOOMBA_BBOX_WIDTH;

	if (state == GOOMBA_STATE_DIE)
		bottom = y + 14;
	else if(state == GOOMBAWING_STATE_WALKING)
		bottom = y + 24;
	else
		bottom = y + GOOMBA_BBOX_HEIGHT;
}

void CWingGoomba::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{


	if (GetTickCount() - Die_start > 600 && Die == true)
	{
		SetState(GOOMBA_STATE_DISAPPEAR);
	}

	CGameObject::Update(dt, coObjects);
	vy += MARIO_GRAVITY * dt;
	vector<LPCOLLISIONEVENT>  coEvents;
	vector<LPCOLLISIONEVENT>  coEventsResult;

	coEvents.clear();

	CalcPotentialCollisions(coObjects, coEvents);

	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{
		if (state == GOOMBAWING_STATE_WALKING)
			vy = -0.1f;

		float min_tx, min_ty, nx = 0, ny;
		float rdx, rdy;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		x += min_tx * dx + nx * 0.04f;
		y += min_ty * dy + ny * 0.04f;

	}
	for (UINT i = 0; i < coEvents.size(); i++)
		delete coEvents[i];
	if (vx < 0 && x < 624)
	{
		x = 624;
		vx = -vx;
	}
	if (vx > 0 && x > 1200)
	{
		x = 1200;
		vx = -vx;
	}
	

	
}

void CWingGoomba::Render()
{
	int ani = GOOMBAWING_ANI_WALKING;
	if (state == GOOMBA_STATE_DIE) {
		ani = GOOMBA_ANI_WALKING;
	}
	 if (state == GOOMBA_STATE_WALKING) 
	{
		ani = GOOMBA_ANI_WALKING;
	}
	animation_set->at(ani)->Render(x, y);

	//RenderBoundingBox();
}
void CWingGoomba::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case GOOMBA_STATE_DIE:
		//y += GOOMBA_BBOX_HEIGHT - GOOMBA_BBOX_HEIGHT_DIE + 1;
		/*vx = 0;
		vy = 0;*/
		vx = -GOOMBA_WALKING_SPEED;
		y = 119;
		break;
	case GOOMBA_STATE_WALKING:
		vx = -GOOMBA_WALKING_SPEED;
		break;

	case GOOMBA_STATE_DISAPPEAR:
		y = -100;
		x = -100;
		vx = 0;
		vy = 0;
		break;
	case GOOMBAWING_STATE_WALKING:
		vx = -GOOMBA_WALKING_SPEED;
		break;
	}
}


