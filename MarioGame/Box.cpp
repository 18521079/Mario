#include "Box.h"

void CBox::Render()
{
	animation_set->at(0)->Render(x, y);
	//RenderBoundingBox();
}

void CBox::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + 16;
	b = y+16;
}
