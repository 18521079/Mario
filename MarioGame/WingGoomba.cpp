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
	else if (state == GOOMBAWING_STATE_WALKING)
		bottom = y + 24;
	else
		bottom = y + GOOMBA_BBOX_HEIGHT;
}

void CWingGoomba::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{


	if (GetTickCount() - Die_start > 600 && Die == 1)
	{
		SetState(GOOMBA_STATE_DISAPPEAR);
	}

	CGameObject::Update(dt, coObjects);
	vy += MARIO_GRAVITY * dt;
	vector<LPCOLLISIONEVENT>  coEvents;
	vector<LPCOLLISIONEVENT>  coEventsResult;

	coEvents.clear();

	if (!isFLying)
	{
		timeFlying_start = GetTickCount();
		isFLying = true;
	}
	else
	{
		// Set time for Goomba flying
		if (GetTickCount() - timeFlying_start < 100)
		{
			vy = -0.25f;
		}
		// when time is greater than 2000, set isFlying = false to return wal
		if (GetTickCount() - timeFlying_start > 2000)
		{
			isFLying = false;
		}
	}

	if (state != GOOMBA_STATE_DIE_FALL)
	CalcPotentialCollisions(coObjects, coEvents);

	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{
		/*if (state == GOOMBAWING_STATE_WALKING)
			vy = -0.1f;*/

		float min_tx, min_ty, nx = 0, ny;
		float rdx, rdy;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		x += min_tx * dx + nx * 0.04f;
		y += min_ty * dy + ny * 0.04f;
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (dynamic_cast<CGoomba*>(e->obj)) // if e->obj is Goomba
			{
				CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);
				goomba->SetPosition(x, y - 10.0f);
				vx = -vx;
				goomba->vx = -goomba->vx;
				
			}

			else if (nx != 0 && ny == 0)
			{
				nx = -nx;
				vx = -vx;
			}
			

		}
		for (UINT i = 0; i < coEvents.size(); i++)
			delete coEvents[i];
		if (vx < 0 && x < 700)
		{
			x = 700;
			vx = -vx;
		}
		if (vx > 0 && x > 1200)
		{
			x = 1200;
			vx = -vx;
		}

	}

}

void CWingGoomba::Render()
{
	int ani = GOOMBAWING_ANI_WALKING;
	if (state == GOOMBA_STATE_DIE) {
		ani = GOOMBA_ANI_WALKING;
	}
	if (state == GOOMBA_STATE_WALKING || state==GOOMBA_STATE_DIE_FALL)
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
		vx = -2.0f*GOOMBA_WALKING_SPEED;
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
