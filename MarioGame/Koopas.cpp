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
	//SetMarioKick(0);
}

void CKoopas::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + KOOPAS_BBOX_WIDTH;

	if (state == KOOPAS_STATE_DIE || state==KOOPAS_STATE_PREREVIVE)
		bottom = y + KOOPAS_BBOX_HEIGHT_DIE;
	else
		bottom = y + KOOPAS_BBOX_HEIGHT;
}

void CKoopas::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
	x += dx;
	y += dy;
	if (GetState() == KOOPAS_STATE_WALKING)
	{
		if (vx < 0 && x < 593) {
			x = 593; vx = -vx; /*y = 94*/;
		}

		if (vx > 0 && x > 705) {
			x = 705; vx = -vx; /*y = 94*/;
		}
	}
	else if (GetState() == SHELL_STATE_WALKING)
	{
		if (vx < 0 && x < 575) {
			x = 560; vx = -vx; y = 135;
		}

		if (vx > 0 && x > 720) {
			x = 740; vx = -vx; y = 135;
		}
	}
	//vector<LPCOLLISIONEVENT> coEvents;
	//vector<LPCOLLISIONEVENT> coEventsResult;
	//coEvents.clear();
	//CalcPotentialCollisions(coObjects, coEvents);
	//if (coEvents.size() == 0)
	//{
	//	
	//	x += dx;
	//	y += dy;

	//}
	//else
	//{
	//	float min_tx, min_ty, nx = 0, ny;
	//	float rdx = 0;
	//	float rdy = 0;

	//	// TODO: This is a very ugly designed function!!!!
	//	FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

	//	
	//	y += min_ty * dy + ny * 0.4f;
	//	x += min_tx * dx + nx * 0.4f;
	//}
	//
	
	//
	// TO-DO: make sure Koopas can interact with the world and to each of them too!
	// 
	

	if (GetTickCount() - Prerevive_start > 5000 &&  PREREVIVE == true)
	{
		Prerevive_start = 0;
		SetState(KOOPAS_STATE_PREREVIVE);
		SetLevel(KOOPAS_LEVEL_SHELL);
	}

	if (GetTickCount() - Revive_start > 8000 && REVIVE == true)
	{
		SetState(KOOPAS_STATE_WALKING);
		SetLevel(KOOPAS_LEVEL_NORMAL);
		
		if (GetState()!= KOOPAS_STATE_DIE )
		{
			float x1, y2;
			GetPosition(x1, y2);
			SetPosition(x1, 94);
		}	

	}
	if (state == KOOPAS_STATE_DIE)
	{
		if (Hold == 1)
		{
			CMario* mario = ((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
			if (mario->GetHolding() == 0)
			{
				Hold = 0;
				StartPRE_REVIVE();
				StartRevive();
				SetLevel(KOOPAS_LEVEL_NORMAL);
			}
			else
			{
				x = mario->vx;
				y = mario->vy;
			}
			vx = 0;
		}


	}

}

void CKoopas::Render()
{
	int ani = KOOPAS_ANI_WALKING_LEFT;
	if (state == KOOPAS_STATE_DIE) {
		ani = KOOPAS_ANI_DIE;

	}
	else if (state == KOOPAS_STATE_PREREVIVE)
		ani = KOOPAS_ANI_PREREVIVE;
	else if (state == SHELL_STATE_WALKING)
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
	case KOOPAS_STATE_DIE:
		y += KOOPAS_BBOX_HEIGHT - KOOPAS_BBOX_HEIGHT_DIE + 1;
		vx = 0;
		vy = 0;
		break;
	case KOOPAS_STATE_WALKING:
		vx = KOOPAS_WALKING_SPEED;
		vy = 0;
		break;
	case KOOPAS_STATE_PREREVIVE:
		vx = 0;
		break;
	case SHELL_STATE_WALKING:
		vx = KOOPAS_WALKING_SPEED;
		SetLevel(KOOPAS_LEVEL_SHELL);
		break;
		
	}

}
