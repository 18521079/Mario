#include "Boomerang.h"
CBoomerang::CBoomerang()
{/*
	StartAgain();
	StartUp();
	StartDown();*/
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
	CGameObject::Update(dt, coObjects);
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
		vx = 0.5f;
		vy = 0.9f;
		break;
	
	}
}