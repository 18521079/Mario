#include "Flower.h"
#include "Ball.h"

CBall* ball;


CFlower::CFlower()
{
	SetState(FLOWER_STATE_WALKING);
	vy = 0.01f;
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
	y -= dy;

	if (y<72 && vy>0)
	{
		vy = -vy;
	}
	else if (y > 120)
	{
		vy = -vy;
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
		vy = -FLOWER_WALKING_SPEED;
	}
}

