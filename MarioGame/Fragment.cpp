#include "Fragment.h"

//CPiece::CPiece()
//{
//	SetState(FRAGMENT_STATE_DISAPPEAR);
//	//this->layerRender = 1200;
//}

CPiece::CPiece(int type)
{
	typeOfFragment = type;
	SetState(FRAGMENT_STATE_DISAPPEAR);
	//this->layerRender = 1200;
}

void CPiece::Render()
{

	if (state != FRAGMENT_STATE_DISAPPEAR)
	{
		animation_set->at(FRAGMENT_APPEAR_ANI)->Render(x, y);
	}

}

void CPiece::GetBoundingBox(double& l, double& t, double& r, double& b)
{
}

void CPiece::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
	vy += FRAGMENT_GRAVITY_FALLING * dt;
	x += dx;
	y += dy;
	/*if (isUsed == true)
	{
		SetState(FRAGMENT_STATE_APPEAR);
	}*/
	if (state == FRAGMENT_STATE_APPEAR)
	{
		if (!isDisappear)
		{
			isDisappear = true;
			disappear_start = GetTickCount();
		}
		else
		{
			if (GetTickCount() - disappear_start > TIME_FOR_FRAGMENT_DISAPPEARING)
			{
				SetState(FRAGMENT_STATE_DISAPPEAR);
				isUsed = false;
				isDisappear = false;
			}
		}
	}
}

void CPiece::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case FRAGMENT_STATE_DISAPPEAR:
		vx = 0;
		vy = 0;
	case FRAGMENT_STATE_APPEAR:
		switch (typeOfFragment)
		{
		case OBJECT_TYPE_FRAGMENT_LEFTTOP:
			vx = -SPEED_FRAGMENT_VX;
			vy = -SPEED_FRAGMENT_VY;
			break;
		case OBJECT_TYPE_FRAGMENT_RIGHTTOP:
			vx = SPEED_FRAGMENT_VX;
			vy = -SPEED_FRAGMENT_VY;
			break;
		case OBJECT_TYPE_FRAGMENT_LEFTBOTTOM:
			vx = -SPEED_FRAGMENT_VX;
			vy = SPEED_FRAGMENT_VY;
			break;
		case OBJECT_TYPE_FRAGMENT_RIGHTBOTTOM:
			vx = SPEED_FRAGMENT_VX;
			vy = SPEED_FRAGMENT_VY;
			break;
		}
	default:
		break;
	}
}