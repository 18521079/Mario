#include "Koopas.h"

CKoopas::CKoopas()
{
	SetState(KOOPAS_STATE_WALKING);
	SetLevel(KOOPAS_LEVEL_NORMAL);
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
	
	//
	// TO-DO: make sure Koopas can interact with the world and to each of them too!
	// 

	x += dx;
	y += dy;

	if (vx < 0 && x < 593) {
		x = 593; vx = -vx; y = 94;
	}

	if (vx > 0 && x > 705) {
		x = 705; vx = -vx; y = 94;
	}

	if (GetTickCount() - Prerevive_start > 4000 &&  PREREVIVE == true)
	{
		Prerevive_start = 0;
		SetState(KOOPAS_STATE_PREREVIVE);
		SetLevel(KOOPAS_LEVEL_SHELL);
		
	}

	if (GetTickCount() - Revive_start > 8000 && REVIVE == true)
	{
		SetState(KOOPAS_STATE_WALKING);
		SetLevel(KOOPAS_LEVEL_NORMAL);

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
	else if (state == KOOPAS_STATE_SHELL)
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
		break;
	case KOOPAS_STATE_PREREVIVE:
		vx = 0;
		vy = 0;
		break;
	case KOOPAS_STATE_SHELL:
		vx = KOOPAS_WALKING_SPEED;
		SetMarioKick(1);
		break;
		
	}

}
