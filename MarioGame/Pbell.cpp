#include "Pbell.h"
#include"Breakable_Brick.h"

CPbell::CPbell()
{
	SetState(BELL_STATE_DISSAPPEAR);
}

void CPbell::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	if (state == BELL_STATE_INACTIVITY)
	{
		r = x + 8;
		b = y + 8;
	}
	else {
		r = x + 16;
		b = y + 16;
	}
}

void CPbell::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

	CGameObject::Update(dt, coObjects);

	if (pFeature == 1 && GetTickCount() - pFeature_start > 5000)
	{
		pFeature_start = 0;
		pFeature = 0;
		touch = 2;

	}
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	coEvents.clear();

	for (int i = 0; i < coObjects->size(); i++)
	{
		LPGAMEOBJECT obj = coObjects->at(i);
		if (dynamic_cast<CBreakableBrick*>(obj))
		{
			CBreakableBrick* brick = dynamic_cast<CBreakableBrick*>(obj);
			if (touch == 1 || touch==2)
			{
				SetState(BELL_STATE_INACTIVITY);
				y = 97;
			}
			else if(brick->GetTouch() == 1)
			{
				state = BELL_STATE_ACTIVITY;

			}

		}
	}
}
void CPbell::Render()
{
	int ani;
	if (state == BELL_STATE_ACTIVITY)
	{
		ani = BELL_ANI_P;
	}
	else if (state == BELL_STATE_INACTIVITY)
	{
		ani = BELL_ANI_DISSAPPEAR;
	}
	if(state != BELL_STATE_DISSAPPEAR) 
	animation_set->at(ani)->Render(x, y);

	//RenderBoundingBox();
}