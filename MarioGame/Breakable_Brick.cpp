#include "Breakable_Brick.h"

CBreakableBrick::CBreakableBrick()
{
	SetState(BRICK_STATE_NORMAL);
}
void CBreakableBrick::Render()
{
	if(state==BRICK_STATE_NORMAL)
	animation_set->at(0)->Render(x, y);
	//RenderBoundingBox();
}

void CBreakableBrick::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + 16;
	b = y + 16;
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