#include "Breakable_Brick.h"
#include"Pbell.h"

CBreakableBrick::CBreakableBrick()
{
	SetState(BRICK_STATE_NORMAL);
}
void CBreakableBrick::Render()
{
	int ani = BRICK_ANI_NORMAL;
	if (state == BRICK_STATE_COIN)
		ani = BRICK_ANI_COIN;
	else if (state == BRICK_STATE_NORMAL)
	{
		ani = BRICK_ANI_NORMAL;
	}
	animation_set->at(ani)->Render(x, y);

	//RenderBoundingBox();
}

void CBreakableBrick::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + 16;
	b = y + 16;
}
void CBreakableBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

	CGameObject::Update(dt, coObjects);
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	coEvents.clear();
	
	for (int i = 0; i < coObjects->size(); i++)
	{
		LPGAMEOBJECT obj = coObjects->at(i);
		if (dynamic_cast<CPbell*>(obj))
		{
			CPbell* bell = dynamic_cast<CPbell*>(obj);
			if (bell->GetTouch() == 1)
			{
				state = BRICK_STATE_COIN;
				//StartPfeature();
			}
			else if (bell->GetTouch() == 2)
			{
				state = BRICK_STATE_NORMAL;
			}

			

		}
	}
}
void CBreakableBrick::SetState(int state)
{

	CGameObject::SetState(state);
	switch (state)
	{
	case BRICK_STATE_DISAPPEAR:
		x = -100;
		y = -100;
	}
}