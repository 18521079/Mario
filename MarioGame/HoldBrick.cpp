#include "HoldBrick.h"
void CHoldBrick::Render()
{
	int ani = BRICK_ANI_LEVEL;
	if (state == BRICK_STATE_M)
		ani = BRICK_ANI_M;
	animation_set->at(ani)->Render(x, y);
	//RenderBoundingBox();
}

void CHoldBrick::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + 16;
	b = y + 16;
}
