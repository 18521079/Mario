#include "BackGroundCollision.h"
#include"Game.h"
#include"Scence.h"

void CBackGroundCollision::Render()
{
	animation_set->at(0)->Render(x, y);
	//RenderBoundingBox();
}

void CBackGroundCollision::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	int id = CGame::GetInstance()->GetCurrentScene()->GetId();
	l = x;
	t = y;
	if (id == 1)
	{
		r = x + 256;
		b = y + 37;
	}
	else {
		r = x + 16;
		b = y + 16;
	}
}