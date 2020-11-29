#include "Koopas.h"
#include "GameObject.h"
#include"Mario.h"
#include"GameObject.h"
#include"Scence.h"
#include"PlayScence.h"
#include"Item.h"

CKoopas::CKoopas(int t)
{
	type = t;
	SetState(KOOPAS_STATE_WALKING_LEFT);
	vx = KOOPAS_WALKING_SPEED;
	nx = -1;
	vx = -0.02;
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

	if (state == KOOPAS_STATE_SHELL || state == KOOPAS_STATE_SHELL_MARIOSPIN)
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

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	if (state != KOOPAS_STATE_DIE)
		CalcPotentialCollisions(coObjects, coEvents);
	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
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
			if (dynamic_cast<CItem*>(e->obj)) // if e->obj is Goomba 
			{
				CItem* item = dynamic_cast<CItem*>(e->obj);
				item->SetTouch(1);
				if (item->x == 800 && item->y == 118)
				{
					item->y = 70;
					item->SetState(ITEM_STATE_LEAF);
				}
			}

		}

		for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];

		
		if (x <= 0)
			if (vx < 0)
				vx = -vx;
	}
	/*if (state == SHELL_STATE_WALKING_RIGHT || state == SHELL_STATE_WALKING_LEFT)
	{
		CMario* mario = ((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
		mario->SetAniKick(1);
		mario->StartKick();
	}*/
	//if (state == KOOPAS_STATE_SHELL)
	//{
		CMario* mario = ((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
		if (Hold == true) {
			
			if (mario->GetHolding() == false)
			{
				Hold = false;
				mario->SetAniHolding(0);
				mario->SetAniKick(1);
				mario->StartKick();
				if (mario->nx > 0)
				{
	
					SetState(SHELL_STATE_WALKING_RIGHT);
				}
				else
					SetState(SHELL_STATE_WALKING_LEFT);


			}

			if (mario->GetLevel() != MARIO_LEVEL_SMALL)
			{
				x = mario->x + 10 * mario->nx;
				y = mario->y + 5;
			}
			else
			{
				x = mario->x + 10 * mario->nx;
				y = mario->y-3;
			}
			vy = 0;
		}
		
		if (y > 140)
		{
			if(type==3 && state==KOOPAS_STATE_WALKING_LEFT || state == KOOPAS_STATE_WALKING_RIGHT)
			SetPosition(1620, 20);
			else if(type==2 && state == KOOPAS_STATE_WALKING_LEFT || state == KOOPAS_STATE_WALKING_RIGHT)
				SetPosition(1642, 80);
		}
		if (type == 1 && state==KOOPAS_STATE_WALKING_LEFT || state == KOOPAS_STATE_WALKING_RIGHT)
		{
			if (x > 700)
			{
				vx = -vx;
			}
			if (x < 595)
			{
				vx = -vx;
			}
		}
		/*else if(mario->GetKickKoopas()==1)
		{
			mario->SetAniKick(1);
			mario->StartKick();
			if (nx > 0)
				SetState(SHELL_STATE_WALKING_RIGHT);
			else
				SetState(SHELL_STATE_WALKING_LEFT);
		}*/

	//}
	//x += dx;
	//y += dy;

	//if (vx < 0 && x < 593) {
	//	x = 593; vx = -vx; y = 94;
	//}
	//if (GetState() == KOOPAS_STATE_WALKING)
	//{

	//	if (vx > 0 && x > 705) {
	//		x = 705; vx = -vx; y = 94;
	//		if (vx < 0 && x < 593) {
	//			x = 593; vx = -vx; /*y = 94*/;
	//		}

	//		if (vx > 0 && x > 705) {
	//			x = 705; vx = -vx; /*y = 94*/;
	//		}
	//	}
	//	else if (GetState() == SHELL_STATE_WALKING)
	//	{
	//		if (vx < 0 && x < 580) {
	//			x = 580; vx = -vx; /*y = 94*/;
	//		}
	//	}


		if (GetTickCount() - Prerevive_start > 5000 && PREREVIVE == true)
		{
			Prerevive_start = 0;
			SetState(KOOPAS_STATE_PREREVIVE);
		}

		/*if (GetTickCount() - Revive_start > 8000 && REVIVE == true)
		{

			SetState(KOOPAS_STATE_WALKING);

		}*/
	//	if (state == KOOPAS_STATE_DIE)
	//	{
	//		if (Hold == 1)
	//		{
	//			CMario* mario = ((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	//			if (mario->GetHolding() == 0)
	//			{
	//				Hold = 0;
	//				StartPRE_REVIVE();
	//				StartRevive();
	//				SetLevel(KOOPAS_LEVEL_NORMAL);
	//			}
	//			else
	//			{
	//				x = mario->vx;
	//				y = mario->vy;
	//			}
	//			vx = 0;
	//		}


		//}

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
		else if (state == KOOPAS_STATE_PREREVIVE)
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
		if (state ==KOOPAS_STATE_SHELL || state == KOOPAS_STATE_SHELL_MARIOSPIN) {
			ani = GREENKOOPAS_ANI_SHELL;

		}
		else if (state == KOOPAS_STATE_PREREVIVE)
			ani = KOOPAS_ANI_PREREVIVE;
		else if (state == SHELL_STATE_WALKING_RIGHT)
			ani = GREENKOOPAS_ANI_SHELL_WALKING_LEFT;
		else if (state == SHELL_STATE_WALKING_LEFT)
			ani = GREENKOOPAS_ANI_SHELL_WALKING_LEFT;
		else if (vx > 0) ani = GREENKOOPAS_ANI_WALKING_RIGHT;
		else if (vx <= 0) ani = GREENKOOPAS_ANI_WALKING_LEFT;

	}

	else if (type == KOOPAS_TYPE_WING)
	{
		ani = GREENKOOPAS_ANI_FLYING_LEFT;
		if (state == KOOPAS_STATE_SHELL || state == KOOPAS_STATE_SHELL_MARIOSPIN) {
			ani = GREENKOOPAS_ANI_SHELL;

		}
		else if (state == KOOPAS_STATE_PREREVIVE)
			ani = KOOPAS_ANI_PREREVIVE;
		else if (state == SHELL_STATE_WALKING_RIGHT)
			ani = GREENKOOPAS_ANI_SHELL_WALKING_LEFT;
		else if (state == SHELL_STATE_WALKING_LEFT)
			ani = GREENKOOPAS_ANI_SHELL_WALKING_LEFT;
		else if (vx > 0) ani = GREENKOOPAS_ANI_FLYING_RIGHT;
		else if (vx <= 0) ani = GREENKOOPAS_ANI_FLYING_LEFT;
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
			vx = 2*KOOPAS_WALKING_SPEED;
		}
		else
			vx = KOOPAS_WALKING_SPEED;
		nx = 1;
		break;
	case KOOPAS_STATE_WALKING_LEFT:
		if (type == 3)
		{
			vx = -2 * KOOPAS_WALKING_SPEED;
		}
		else
		vx = -KOOPAS_WALKING_SPEED;
		nx = -1;
		break;
	case KOOPAS_STATE_PREREVIVE:
		vx = KOOPAS_WALKING_SPEED;
		vy = KOOPAS_WALKING_SPEED;
		break;
	case SHELL_STATE_WALKING_LEFT:
			vx = 3.0f* KOOPAS_WALKING_SPEED ;
		break;
	case SHELL_STATE_WALKING_RIGHT:
		vx = -3.0* KOOPAS_WALKING_SPEED;
		break;
	
	case KOOPAS_STATE_DIE:
		vx = 0;
		vy = 0;
		break;
	case KOOPAS_STATE_SHELL_MARIOSPIN:
		y = 100;
		vy = 2*KOOPAS_WALKING_SPEED;
		vx = 0;
	}

}
