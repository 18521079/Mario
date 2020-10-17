#include "Turtle.h"


void CTurtle::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + TURTLE_BBOX_WIDTH;

	if (state == TURTLE_STATE_DIE)
		bottom = y + TURTLE_BBOX_HEIGHT_DIE;
	else
		bottom = y + TURTLE_BBOX_HEIGHT;
}

void CTurtle::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);

	//
	// TO-DO: make sure Goomba can interact with the world and to each of them too!
	// 
	y = 125;
	x += dx;
	y += dy;

	if (vx < 0 && x < 390) {
		x = 390; vx = -vx;
	}

	if (vx > 0 && x > 465) {
		x = 465; vx = -vx;
	}
}

void CTurtle::Render()
{
	int ani = TURTLE_ANI_WALKING_LEFT;
	if (state == TURTLE_STATE_DIE) {
		ani = TURTLE_ANI_DIE;
	}
	else if (vx>0)
		ani = TURTLE_ANI_WALKING_RIGHT;
	

	animations[ani]->Render(x, y);
	//RenderBoundingBox();
}

void CTurtle::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case TURTLE_STATE_DIE:
		y += TURTLE_BBOX_HEIGHT - TURTLE_BBOX_HEIGHT_DIE + 1;
		vx = 0;
		vy = 0;
		break;
	case TURTLE_STATE_WALKING_LEFT:
		vx = -TURTLE_WALKING_SPEED;
		nx = -1;
		break;
	case TURTLE_STATE_WALKING_RIGHT:
		vx = TURTLE_WALKING_SPEED;
		nx = 1;
		break;

	}
}

