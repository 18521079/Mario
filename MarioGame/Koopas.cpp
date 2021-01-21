#include "Koopas.h"
#include "GameObject.h"
#include"Mario.h"
#include"GameObject.h"
#include"Scence.h"
#include"PlayScence.h"
#include"Item.h"
#include"StartScence.h"

CKoopas::CKoopas(int t)
{
	type = t;
	if (type != KOOPAS_TYPE_GREEN_WING)
	{
		SetState(KOOPAS_STATE_WALKING_LEFT);
		vx = KOOPAS_WALKING_SPEED;
		nx = -1;
		vx = -0.02;
	}
	else
	{
		vy = 0.0000000002f;
		vx = 0;
	}
	//SetMarioKick(0);
}

void CKoopas::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + KOOPAS_BBOX_WIDTH;
	left = x;
	top = y;
	right = x + KOOPAS_BBOX_WIDTH;

	if (state == KOOPAS_STATE_SHELL || state == KOOPAS_STATE_SHELL_MARIOSPIN || state == SHELL_STATE_FALL || state == KOOPAS_STATE_RENEW)
		bottom = y + KOOPAS_BBOX_HEIGHT_DIE;
	else if (state == SHELL_STATE_WALKING_RIGHT || state == SHELL_STATE_WALKING_LEFT)
	{
		right = x + KOOPAS_BBOX_WIDTH - 4;
		bottom = y + 16;
	}
	else
		bottom = y + KOOPAS_BBOX_HEIGHT;

}

void CKoopas::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

	CGameObject::Update(dt, coObjects);
	vy += MARIO_GRAVITY * dt;

	CMario* mario = ((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer();

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	if (state != KOOPAS_STATE_DIE_FALL || type != KOOPAS_TYPE_GREEN_WING)
		CalcPotentialCollisions(coObjects, coEvents);
	int id = CGame::GetInstance()->GetCurrentScene()->GetId();
	if (state == KOOPAS_STATE_SHELL && id != 1 && Hold !=1) {


		if (!isRenewStart)
		{
			timeRenew_start = GetTickCount();
			isRenewStart = true;
		}

		// Set for the Koopas renews if enough time to renew
		else
		{
			if (GetTickCount() - timeRenew_start > 5000)
			{

				SetPosition(x,y - 10.0f);
				SetState(KOOPAS_STATE_RENEW);
				isRenewStart = false;
				timeWalking_start = GetTickCount();
			}
		}
	}
	if (type == 3)
	{
		if (!isFLying)
		{
			timeFlying_start = GetTickCount();
			isFLying = true;
		}
		else
		{
			// Set time for Koopas flying
			if (GetTickCount() - timeFlying_start < 150)
			{
				vy = -0.25f;
			}

			if (GetTickCount() - timeFlying_start > 2000)
			{
				isFLying = false;
			}
		}
	}
	if (type == KOOPAS_TYPE_GREEN_WING)
	{

		y += vy * dt;
		if (y > 160)
		{
			y = 159;
			vy = -vy;
		}
		else if (y < 112)
		{
			y = 114;
			vy = -vy;
		}



	}
	if (state == KOOPAS_STATE_RENEW)
	{
		if (GetTickCount() - timeWalking_start > 2000)
		{
			SetState(KOOPAS_STATE_WALKING_RIGHT);
			vx = 0.02f;
			SetPosition(this->x, this->y - 10.0f);

		}
	}
	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
		if (isAbleFall == false && (state == KOOPAS_STATE_WALKING_LEFT || state == KOOPAS_STATE_WALKING_RIGHT))
		{
			if (y - prePositionOnGround >= 1.0f)
			{
				y -= 5;
				if (vx < 0)
				{
					x += 12;
				}
				else
				{
					x -= 12;
				}
				vx = -vx;
				isAbleFall = true;
			}
		}
	
	}

	else
	{
		float min_tx, min_ty, nx = 0, ny;
		float rdx = 0;
		float rdy = 0;

		// TODO: This is a very ugly designed function!!!!
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		x += min_tx * dx + nx * 0.4f;
		y += min_ty * dy + ny * 0.4f;

		if (ny != 0) vy = 0;
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (nx != 0 && ny == 0)
			{
				nx = -nx;
				vx = -vx;
			}
			//if (dynamic_cast<CItem*>(e->obj)) // if e->obj is Goomba 
			//{
			//	CItem* item = dynamic_cast<CItem*>(e->obj);
			//	item->SetTouch(1);
			//	if (item->x == 800 && item->y == 118)
			//	{
			//		item->y = 70;
			//		item->SetState(ITEM_STATE_LEAF);
			//	}
			//}
			if (nx == 0 && (dynamic_cast<CBreakableBrick*>(e->obj) 
				|| dynamic_cast<CBox*>(e->obj)))
			{
				//vy = 0;
				if (type == KOOPAS_TYPE_RED && (state == KOOPAS_STATE_WALKING_LEFT	|| state == KOOPAS_STATE_WALKING_RIGHT))
				{
					if (dynamic_cast<CBreakableBrick*>(e->obj))
					{
						CBreakableBrick* breakbrick = dynamic_cast<CBreakableBrick*>(e->obj);

						if (breakbrick->GetState() != BRICK_STATE_COIN)
						{
							prePositionOnGround = y;
							isAbleFall = false;
						}

					}
					else
					{
						prePositionOnGround = y;
						isAbleFall = false;
					}
				}
			}

		}

		for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];


		if (x <= 0)
			if (vx < 0)
				vx = -vx;
	}
	
	if (mario->GetHolding() == 0)
	{
		Hold = 0;
	}
	if (Hold == 1 /*|| mario->GetAniHolding()== 1*/) {
		
		if (mario->GetLevel() != MARIO_LEVEL_SMALL)
		{
			x = mario->x + 10 * mario->nx;
			y = mario->y + 5;
		}
		else
		{
			x = mario->x + 10 * mario->nx;
			y = mario->y - 3;
		}
		vy = 0;
	}
	if (id == 1)
	{
		CMario* mario2 = ((CStartScence*)CGame::GetInstance()->GetCurrentScene())->GetPlayer2();
		if (Hold == 1) {

			if (mario2->GetLevel() != MARIO_LEVEL_SMALL)
			{
				x = mario2->x + 10 * mario->nx;
				y = mario2->y + 5;
			}
			else
			{
				x = mario2->x + 10 * mario2->nx;
				y = mario2->y - 3;
			}
			vy = 0;
		}
	}

	if (y > 140)
	{
		if (type == 3 && (state == KOOPAS_STATE_WALKING_LEFT || state == KOOPAS_STATE_WALKING_RIGHT))
			SetPosition(1620, 20);
		else if (type == 2 && (state == KOOPAS_STATE_WALKING_LEFT || state == KOOPAS_STATE_WALKING_RIGHT))
			SetPosition(1642, 80);
	}
	//int id = CGame::GetInstance()->GetCurrentScene()->GetId();
	/*if (type ==1 && (state == KOOPAS_STATE_WALKING_LEFT || state == KOOPAS_STATE_WALKING_RIGHT) && id == 3)
	{
		if (x > 700)
		{
			x = 699;
			vx = -vx;
		}
		if (x < 590)
		{
			x = 591;
			vx = -vx;
		}
	}*/



	else if (type == 2 && id == 4 && (state == KOOPAS_STATE_WALKING_LEFT || state == KOOPAS_STATE_WALKING_RIGHT))
	{
		if (x < 1042)
		{
			x = 1044;
			vx = -vx;
		}
		if (x > 1104)
		{
			x = 1100;
			vx = -vx;
		}
	}





}



void CKoopas::Render()
{
	int ani;
	if (type == KOOPAS_TYPE_RED)
	{
		ani = KOOPAS_ANI_WALKING_LEFT;
		if (state == KOOPAS_STATE_SHELL || state == KOOPAS_STATE_SHELL_MARIOSPIN) {
			ani = KOOPAS_ANI_SHELL;

		}
		else if (state == KOOPAS_STATE_RENEW)
			ani = KOOPAS_ANI_PREREVIVE;
		else if (state == SHELL_STATE_WALKING_RIGHT)
			ani = KOOPAS_ANI_SHELL_WALKING_LEFT;
		else if (state == SHELL_STATE_WALKING_LEFT)
			ani = KOOPAS_ANI_SHELL_WALKING_LEFT;
		else if (vx > 0) ani = KOOPAS_ANI_WALKING_RIGHT;
		else if (vx <= 0) ani = KOOPAS_ANI_WALKING_LEFT;
	}
	else if (type == 2)
	{
		ani = GREENKOOPAS_ANI_WALKING_LEFT;
		if (state == KOOPAS_STATE_SHELL || state == KOOPAS_STATE_SHELL_MARIOSPIN || state == SHELL_STATE_FALL) {
			ani = GREENKOOPAS_ANI_SHELL;

		}
		else if (state == KOOPAS_STATE_RENEW)
			ani = KOOPAS_ANI_PREREVIVE;
		else if (state == SHELL_STATE_WALKING_RIGHT)
			ani = GREENKOOPAS_ANI_SHELL_WALKING_LEFT;
		else if (state == SHELL_STATE_WALKING_LEFT)
			ani = GREENKOOPAS_ANI_SHELL_WALKING_LEFT;
		else if (vx > 0) ani = GREENKOOPAS_ANI_WALKING_RIGHT;
		else if (vx <= 0) ani = GREENKOOPAS_ANI_WALKING_LEFT;

	}

	else if (type == KOOPAS_TYPE_WING || type == KOOPAS_TYPE_GREEN_WING)
	{
		ani = GREENKOOPAS_ANI_FLYING_LEFT;
		if (state == KOOPAS_STATE_SHELL || state == KOOPAS_STATE_SHELL_MARIOSPIN) {
			ani = GREENKOOPAS_ANI_SHELL;

		}
		else if (state == KOOPAS_STATE_RENEW)
			ani = KOOPAS_ANI_PREREVIVE;
		else if (state == SHELL_STATE_WALKING_RIGHT)
			ani = GREENKOOPAS_ANI_SHELL_WALKING_LEFT;
		else if (state == SHELL_STATE_WALKING_LEFT)
			ani = GREENKOOPAS_ANI_SHELL_WALKING_LEFT;
		else if (state == KOOPAS_STATE_SHELL)
			ani = GREENKOOPAS_ANI_SHELL;


		/*else if(state==KOOPAS_STATE_WALKING_LEFT)
			ani = GREENKOOPAS_ANI_WALKING_LEFT;
		else if(state == KOOPAS_STATE_WALKING_RIGHT_INTRO)
			ani = GREENKOOPAS_ANI_WALKING_RIGHT;*/

		else if (vx > 0) ani = GREENKOOPAS_ANI_FLYING_RIGHT;
		else if (vx <= 0) ani = GREENKOOPAS_ANI_FLYING_LEFT;
	}
	else if (type == KOOPAS_TYPE_SHELL)
	{
		ani = BACK_KOOPAS_ANI_SHELL;
	}
	animation_set->at(ani)->Render(x, y);

	//RenderBoundingBox();
}

void CKoopas::SetState(int state)
{

	CGameObject::SetState(state);
	switch (state)
	{
	case KOOPAS_STATE_SHELL:
		//y += KOOPAS_BBOX_HEIGHT - KOOPAS_BBOX_HEIGHT_DIE + 1;
		vx = 0;
		vy = 0;
		break;
	case KOOPAS_STATE_WALKING_RIGHT:
		if (type == 3)
		{
			vx = 2 * KOOPAS_WALKING_SPEED;
		}
		else
		{
			vx = 0.02f;
			nx = 1;
		}
		break;
	case KOOPAS_STATE_WALKING_LEFT:
		if (type == 3)
		{
			vx = -2 * KOOPAS_WALKING_SPEED;
		}
		else
		{
			vx = -0.02;
			nx = -1;
		}
		break;

	case SHELL_STATE_WALKING_LEFT:
		vx = 3.0f * KOOPAS_WALKING_SPEED;
		break;
	case SHELL_STATE_WALKING_RIGHT:
		vx = -3.0 * KOOPAS_WALKING_SPEED;
		break;

	case KOOPAS_STATE_DIE:
		vx = 0;
		vy = 0;
		break;
	case KOOPAS_STATE_SHELL_MARIOSPIN:
		y = 100;
		vy = 2 * KOOPAS_WALKING_SPEED;
		vx = 0;
		break;
	case SHELL_STATE_FALL:
		vy = KOOPAS_WALKING_SPEED;
		break;
	case KOOPAS_STATE_DIE_FALL:
		vy = KOOPAS_WALKING_SPEED;
		break;
	case KOOPAS_STATE_WALKING_RIGHT_INTRO:
		if (type == 3)
		{
			vx = 2 * KOOPAS_WALKING_SPEED;
		}
		else
			vx = KOOPAS_WALKING_SPEED;
		nx = 1;
		break;

	}

}