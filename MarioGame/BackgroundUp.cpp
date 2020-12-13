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

void CBackgroundUp::Render()
{
	int ani = 0;
	if (state == BACKGROUND_STATE_FINAL)
	{
		ani = BACKGROUND_ANI_FINAL;
	}
	animation_set->at(ani)->Render(x, y);
}

void CBackgroundUp::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case BACKGROUND_STATE_FINAL:
		vx = 0;
		vy = 0;
		break;
	

	}
}