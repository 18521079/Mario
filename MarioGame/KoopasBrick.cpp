#include "KoopasBrick.h"
#include"Mario.h"


void CKoopasBrick::Render()
{
	//animation_set->at(0)->Render(x, y);
	//RenderBoundingBox();
}

void CKoopasBrick::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + 16;
	b = y + 16;
}

void CKoopasBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	float min_tx, min_ty, nx = 0, ny;
	float rdx = 0;
	float rdy = 0;

	// TODO: This is a very ugly designed function!!!!
	FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

	for (UINT i = 0; i < coEventsResult.size(); i++) {
		LPCOLLISIONEVENT e = coEventsResult[i];
		if (dynamic_cast<CMario*>(e->obj))
		{
			CMario* mario = dynamic_cast<CMario*>(e->obj);
			mario->nx = 0;
			mario->ny = 0;

		}
	}
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}
