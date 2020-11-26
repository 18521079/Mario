#include "Flower.h"
#include "Ball.h"
#include"Mario.h"
#include"PlayScence.h"
#include"Game.h"

CBall* ball;


CFlower::CFlower()
{
	SetState(FLOWER_STATE_WALKING_UP);
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

	/*if (y<72 && vy>0)
	{
		vy = -vy;
	}
	else if (y > 120)
	{
		vy = -vy;
	}*/


	CMario* mario = ((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	if (mario->x < this->x)
	{
		nx = -1;
	}
	else if (mario->x > this->x)
	{
		nx = 1;
	}

	if (state != FLOWER_STATE_IDLE)
	{
		hasFired = false;
	}

	if (state != FLOWER_STATE_DIE)
	{
		if (y > 120)
		{
			SetState(FLOWER_STATE_WALKING_UP);
		}
		else
		{
			if (y < 72)
			{
				if (FirstFiring == false)
				{
					FirstFiring = true;
					timeFiring_start = GetTickCount();
				}
				if (FirstFiring && GetTickCount() - timeFiring_start > 3000)
				{
					SetState(FLOWER_STATE_WALKING_DOWN);
					FirstFiring = false;
				}
				else
				{
					SetState(FLOWER_STATE_IDLE);
				}
			}
		}
	}
	
}

void CFlower::Render()
{
	int ani = FLOWER_ANI_WALKING_LEFT;
	if (vy==0)
	{
		if (nx ==- 1)
			ani = FLOWER_ANI_SHOOT_RIGHT;
		else
			ani = FLOWER_ANI_SHOOT_LEFT;
	}
	if (state != FLOWER_STATE_DIE && vy!=0)
	{
		if (nx == -1)
		{
			ani = FLOWER_ANI_WALKING_LEFT;
		}
		else
		{
			ani = FLOWER_ANI_WALKING_RIGHT;
		}
	}


	animation_set->at(ani)->Render(x, y);

	//RenderBoundingBox();
}

void CFlower::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	
	case FLOWER_STATE_WALKING_UP:
		vy = FLOWER_WALKING_SPEED;
		break;
	case FLOWER_STATE_WALKING_DOWN:
		vy= -FLOWER_WALKING_SPEED;
		break;
	case FLOWER_STATE_IDLE:
		vy = 0;
		break;


	}
}

