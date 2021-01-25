#include "Boomerang.h"
CBoomerang::CBoomerang()
{/*
	StartAgain();
	StartUp();
	StartDown();*/
	state == BOOMERANG_STATE_UP;
	vx = 0.03;
	vy = 0.04;
}
void CBoomerang::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + BOOMERANG_BBOX_WIDTH;
	b = y + BOOMERANG_BBOX_HEIGHT;

}
void CBoomerang::Render()
{
	animation_set->at(0)->Render(x, y);
}
void CBoomerang::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	/*CGameObject::Update(dt, coObjects);
	x += dx;
	y += dy;
	if (again == 1 && GetTickCount() - again_start > 20000)
	{
		again = 0;
		again_start = 0;
	}
	if ( up == 1 && GetTickCount() - up_start > 700)
	{
		up = 0;
		up_start = 0;
	}
	if (down == 1 && GetTickCount() - down_start > 1400)
	{
		down = 0;
		down_start = 0;
	}
	if (again == 1 && up == 1)
	{
		SetState(BOOMERANG_STATE_UP);
	}
	else if (again == 1 && down == 1 && up == 0)
	{
		SetState(BOOMERANG_STATE_DOWN);
	}*/
	
	CGameObject::Update(dt);

	// Simple fall down
	vy += 0.000009 * dt;
	


	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	CalcPotentialCollisions(coObjects, coEvents);
	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;

	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		float rdx = 0;
		float rdy = 0;

		// TODO: This is a very ugly designed function!!!!
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		x += min_tx * dx + nx * 0.4f;
		y += min_ty * dy + ny * 0.4f;

		if (ny != 0) vy = 0;
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			//if (dynamic_cast<CGoomba*>(e->obj)) // if e->obj is Goomba
			//{
			//	CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);
			//	vx = -vx;
			//	goomba->vx = -goomba->vx;
			//}

			//else if (nx != 0 /*&& ny == 0*/)
			//{
			//	nx = -nx;
			//	vx = -vx;
			//}
			if (nx != 0)
			{
				vx = -vx;
			}
		}


		for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	}

}

void CBoomerang::SetState(int state)
{

	CGameObject::SetState(state);
	switch (state)
	{
	case BOOMERANG_STATE_DOWN:
		vx = 0.5f;
		vy = -0.9f;
		break;
	case BOOMERANG_STATE_UP:
		vx = 0.005f;
		vy = 0.009f;
		break;
	
	}
}