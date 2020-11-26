#include "Ball.h"
#include"Flower.h"

CBall::CBall()
{
	//SetState(BALL_STATE_ACTIVITY);
}

void CBall::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + BALL_BBOX_WIDTH;
	bottom = y + BALL_BBOX_HEIGHT;
}

void CBall::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
	/*x -= dx;
	y += dy;

	if (y > 199)
	{
		x = 409;
		y = 72;
	}

	if (GetTickCount()- activity_start>6000 && activity==1)
	{
		activity_start = 0;
		SetState(BALL_STATE_ACTIVITY);
		SetPosition(16,119);
		activity = 0;
	}*/
	//ActivityStart();
	x += dx;
	y += dy;
	for (int i = 0; i < coObjects->size(); i++)
	{
		LPGAMEOBJECT obj = coObjects->at(i);
		if (dynamic_cast<CFlower*>(obj))
		{
			CFlower* flower = dynamic_cast<CFlower*>(obj);

			// Set isFiring before setting hasFired for flower
			if (isFiring == false)
			{
				if (flower->GetState() == FLOWER_STATE_IDLE && !flower->GetHasFired())
				{
					flower->SetHasFired(true);
					isFiring = true;
					SetPosition(flower->x, flower->y);
					nx = flower->nx;
				}
			}
		}
	}
	if (isFiring == true)
	{
		SetState(BALL_STATE_ACTIVITY);
		if (flagTimeFiring == false)
		{
			timeFirinng_start = GetTickCount();
			flagTimeFiring = true;
		}
		else
		{
			if (GetTickCount() - timeFirinng_start > 5000)
			{
				SetState(BALL_STATE_INACTIVITY);
				flagTimeFiring = false;
				isFiring = false;
			}
		}
	}
	else
	{
		SetState(BALL_STATE_INACTIVITY);
	}
	
	
}

void CBall::Render()
{
	int ani = BALL_ANI_DISAPPEAR;
	if (state == BALL_STATE_ACTIVITY) {
		ani = BALL_ANI_FLY;
	}
	animation_set->at(ani)->Render(x, y);

	RenderBoundingBox();
}

void CBall::SetState(int state)
{

	CGameObject::SetState(state);
	switch (state)
	{
	case BALL_STATE_ACTIVITY:
		vx = nx* 0.045;
		vy = 0.027;
		break;
	case BALL_STATE_INACTIVITY:
		vx = 0;
		vy = 0;
		break;
	}
}