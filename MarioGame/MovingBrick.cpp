
#include "MovingBrick.h"

CMovingBrick::CMovingBrick()
{
	SetState(BRICK_STATE_MOVING);
}

void CMovingBrick::GetBoundingBox(float& left, float& top,
	float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + MOVING_PLATTFORM_BBOX_WIDTH;
	bottom = y + MOVING_PLATTFORM_BBOX_HEIGHT;
}
void CMovingBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	

	CGameObject::Update(dt, coObjects);

	x += dx;
	y += dy;
	
		
}

void CMovingBrick::Render()
{
	

	animation_set->at(0)->Render(x, y);
}

void CMovingBrick::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
		case BRICK_STATE_MOVING:
			vx = -0.01f;
			vy = 0;
			break;
		case BRICK_STATE_FALLING:
			vx = 0;
			vy = 0.09f;
			break;
		/*case MOVING_PLATTFORM_STATE_INACTIVE:
			x = entryX;
			y = entryY;
			isBeingTouched = false;
			break;*/
		}
	
}

