#include "BackgroundUp.h"
CBackgroundUp::CBackgroundUp(int type)
{
	this->type = type;
}
void CBackgroundUp::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
	if (type == BACKGROUND_TYPE_UP)
		y -= BACKGROUND_UP_SPEED_Y*dt;
	else
	{
		if(y< BACKGROUND_Y)
		y += BACKGROUND_DOWN_SPEED_Y * dt;
	}
}

void CBackgroundUp::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case BACKGROUND_STATE_UP:
		vx = 0;
		vy = BACKGROUND_UP_SPEED_Y;
		break;
	case BACKGROUND_STATE_DOWN:
		vx = 0;
		vy = BACKGROUND_DOWN_SPEED_Y;

	}
}