
#include "MovingBrick.h"
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



	x += -0.008*dt;
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
		/*case MOVING_PLATTFORM_STATE_MOVING:
			vx = -0.003f;
			vy = 0;
			break;
		case MOVING_PLATTFORM_STATE_FALLING:
			vx = 0;
			break;
		case MOVING_PLATTFORM_STATE_INACTIVE:
			x = entryX;
			y = entryY;
			isBeingTouched = false;
			break;
		}*/
	}
}

CMovingBrick::CMovingBrick()
{

	vx = 0.003f;


}