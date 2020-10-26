#include "Flower.h"

CFlower::CFlower()
{
	SetState(FLOWER_STATE_WALKING);
}

void CFlower::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + FLOWER_BBOX_WIDTH;
	bottom = y + FLOWER_BBOX_HEIGHT;
}

void CFlower::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);

	//
	// TO-DO: make sure Goomba can interact with the world and to each of them too!
	// 
	if (y>70)
	{
		y -= 0.09;
	}
	

	if (y < 70.05)
	{
		y +=0.05;
	}
	
}

void CFlower::Render()
{
	int ani = FLOWER_ANI_WALKING_LEFT;
	

	animation_set->at(ani)->Render(x, y);

	//RenderBoundingBox();
}

void CFlower::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	
	case FLOWER_STATE_WALKING:
		vx = -FLOWER_WALKING_SPEED;
	}
}

