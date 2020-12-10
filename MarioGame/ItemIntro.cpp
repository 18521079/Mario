#include "ItemIntro.h"
CItemIntro::CItemIntro(int type)
{
	this->type = type;
	SetState(ITEM_STATE_IDLE);

}
void CItemIntro::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
	y += dy;
	x += dx;
}

void CItemIntro::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case ITEM_STATE_DISAPPEAR:
		x = -100;
		y = -100;
		vx = 0;
		vy = 0;
		break;
	case ITEM_STATE_FALL:
		vx = 0.0f;
		vy = 0.06f;
		break;
	case ITEM_STATE_IDLE:
		vx = 0.0f;
		vy = 0.0f;
		break;
	case ITEM_STATE_WALKING_LEFT:
		vx = -0.06;
		vy = 0;
	}
}