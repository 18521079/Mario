#include "Ball.h"
#include"Flower.h"
#include"Mario.h"
#include"PlayScence.h"
#include"Game.h"

CBall::CBall()
{
	SetState(BALL_STATE_ACTIVITY);
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
	CMario* mario = ((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer();

	x += dx;
	y += dy;
	for (int i = 0; i < coObjects->size(); i++)
	{
		LPGAMEOBJECT obj = coObjects->at(i);
		if (dynamic_cast<CFlower*>(obj))
		{
			CFlower* flower = dynamic_cast<CFlower*>(obj);

			if (isFiring == false)
			{

				if (flower->GetState() == FLOWER_STATE_IDLE && !flower->GetHasFired() && flower->x!=2084)
				{
					flower->SetHasFired(true);
					isFiring = true;
					if (mario->x > 1828)
					{
						SetPosition(2190, 55);
						if (mario->x < 2190) nx = -1;
						else
							nx = 1;
					}
					else
					{
						SetPosition(flower->x, flower->y);
						nx = flower->nx;
					}

					
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

	//RenderBoundingBox();
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