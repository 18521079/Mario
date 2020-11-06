#include "Fire_Ball.h"
#include"Mario.h"
#include"PlayScence.h"
#include"Scence.h"
#include "Utils.h"


#include <iostream>
#include <fstream>
#include"Background.h"
#include "PlayScence.h"
#include "Utils.h"
#include "Textures.h"
#include "Sprites.h"
#include "Portal.h"
#include "QuestionBlock.h"
#include "Goomba.h"
#include"Breakable_Brick.h"
#include"Box.h"
#include "Flower.h"
#include "Koopas.h"
#include "BackGroundCollision.h"
#include "Ball.h"
#include"Coin.h"



void CFireBall::Render()
{
	if(Fly==1)
	animation_set->at(0)->Render(x, y);
	//RenderBoundingBox();
}

void CFireBall::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + FIREBALL_BBOX_WIDTH;
	b = y + 8;
}

void CFireBall::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CMario* mario = ((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	CGameObject::Update(dt, coObjects);
	if (GetTickCount() - Firinng_start > 4000 && Fly == 1)
	{
		vx = 0;
		Fly = 0;
	}
	
	
	if (mario->GetShoot() == 1 && GetFly() == 0)
	{
		 SetPosition(mario->x, mario->y);
		 SetY(mario->y);
		 SetFly(1);
		 FiringStart();
		 mario->SetShoot(0);

	}
	
	if (Fly == 1)
	{
		vector<LPCOLLISIONEVENT> coEvents;
		vector<LPCOLLISIONEVENT> coEventsResult;
		coEvents.clear();
		CalcPotentialCollisions(coObjects, coEvents);
		vy = 0.05f;
		vx = 0.05f;
		if (coEvents.size() == 0)
		{
			x += dx;
			y += dy;
			if (y < Y && vy < 0)
			{
				vy = -vy;
			}

		}
		else
		{
			float min_tx, min_ty, nx = 0, ny;
			float rdx = 0;
			float rdy = 0;

			// TODO: This is a very ugly designed function!!!!
			FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

			if (ny != 0)
			{
				vy = -vy;
				if (ny > 0)
				{
					Y = y;
				}
			}
			else if (nx != 0)
			{
				vx = 0;
				Fly = 0;
			}
			y += min_ty * dy + ny * 0.4f;
			x += min_tx * dx + nx * 0.4f;
		}

	}
}