#include "Coin.h"

void CCoin::Render()
{
	int ani = COIN_ANI_NORMAL;
	if (state == COIN_STATE_DISAPPEAR)
		ani = COIN_ANI_DISAPPEAR;
	animation_set->at(ani)->Render(x, y);
	//RenderBoundingBox();
}

void CCoin::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + COIN_BBOX_WIDTH;
	b = y + 8;
}

void CCoin::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case COIN_STATE_DISAPPEAR:
		y = -100;
		x = -100;
		vx = 0;
		vy = 0;
		break;
	}
}