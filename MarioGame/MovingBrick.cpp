#include "MovingBrick.h"
#include"Game.h"
#include"PlayScence.h"
#include"Scence.h"
#include"GameObject.h"
void CMovingBrick::GetBoundingBox(float& left, float& top,
	float& right, float& bottom, bool isEnable)
{
	left = x;
	top = y;
	right = x + MOVING_PLATTFORM_BBOX_WIDTH;
	bottom = y + MOVING_PLATTFORM_BBOX_HEIGHT;
}

void CMovingBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (state == MOVING_PLATTFORM_STATE_INACTIVE)
		return;

	CGameObject::Update(dt, coObjects);


	if (this->state == MOVING_PLATTFORM_STATE_FALLING)
		vy += dt * MOVING_PLATTFORM_GRAVITY;

	x += dx;
	y += dy;
	if (isBeingTouched)
	{
		CPlayScene* playScene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
		CMario* mario = playScene->GetPlayer();
		if (mario->GetisTouchingPlattform())
		{
			
				mario->SetisTouchingPlattform(false) ;
				isBeingTouched = false;
				mario->vy = 0;
			
		}
		else
		{
			isBeingTouched = false;
		}
	}
}
void CMovingBrick::Render()
{
	if (state == MOVING_PLATTFORM_STATE_INACTIVE)
		return;

	int ani = 0;

	animation_set->at(ani)->Render(nx, ny);
	//RenderBoundingBox();
}



void CMovingBrick::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case MOVING_PLATTFORM_STATE_MOVING:
		vx = -0.003f;
		vy = 0;
		break;
	case MOVING_PLATTFORM_STATE_FALLING:
		vx = 0;
		break;
	case MOVING_PLATTFORM_STATE_INACTIVE:
		x = entryX;
		y = entryY;
		isBeingTouched = false;
		break;
	}
}




CMovingBrick::CMovingBrick(float entryX, float entryY)
{

	isAbleToActive = true;

	this->entryX = entryX;
	this->entryY = entryY;
	this->x = entryX;
	this->y = entryY;


	this->SetState(MOVING_PLATTFORM_STATE_MOVING);

	
}
