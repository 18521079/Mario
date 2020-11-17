#include "Item.h"
#include "Item.h"
#include "Utils.h"
#include "Mario.h"



void CItem::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
	if (state == ITEM_STATE_LEAF)
	{
		y += 0.03 * dt;
	}
	else
	{

	}
	
	
}


void CItem::Render()
{
	animation_set->at(0)->Render(x, y);
}
void CItem::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
		
	}

}

void CItem::GetBoundingBox(float& l, float& t, float& r, float& b)
{
		l = x;
		t = y;
		r = x + ITEM_BBOX_WIDTH;
		b = y + ITEM_BBOX_HEIGHT;
	
}
