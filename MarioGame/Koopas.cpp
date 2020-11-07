#include "Koopas.h"
#include "GameObject.h"
#include"Mario.h"
#include"GameObject.h"
#include"Scence.h"
#include"PlayScence.h"

CKoopas::CKoopas()
{
	SetState(KOOPAS_STATE_WALKING);
	SetLevel(KOOPAS_LEVEL_NORMAL);
	vx = KOOPAS_WALKING_SPEED;
	nx = 1;
	vx = 0.02;
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

	if (state == KOOPAS_STATE_SHELL)
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
			if (nx != 0 && ny == 0)
			{
				nx = -nx;
				vx = -vx;
			}
		}
		for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];

		if (x <= 0)
			if (vx < 0)
				vx = -vx;
	}

	if (state == KOOPAS_STATE_SHELL)
	{
		if (Hold == true) {
			CMario* mario = ((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
			if (mario->GetHolding() == false)
			{
				Hold = false;
				mario->SetAniHolding(0);

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
	}
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

		if (GetTickCount() - Revive_start > 8000 && REVIVE == true)
		{
			SetState(KOOPAS_STATE_WALKING);

		}
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
	int ani = KOOPAS_ANI_WALKING_LEFT;
	if (state == KOOPAS_STATE_SHELL) {
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

	animation_set->at(ani)->Render(x, y);

	RenderBoundingBox();
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
	case KOOPAS_STATE_WALKING:
			vx = KOOPAS_WALKING_SPEED;
		break;
	case KOOPAS_STATE_PREREVIVE:
		vx = 0;
		break;
	case SHELL_STATE_WALKING_LEFT:
			vx = KOOPAS_WALKING_SPEED;
		break;
	case SHELL_STATE_WALKING_RIGHT:
		vx = -KOOPAS_WALKING_SPEED;
		break;
	
	case KOOPAS_STATE_DIE:
		vx = 0;
		vy = 0;
		
	}

}
