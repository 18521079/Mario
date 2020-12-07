#include "Item.h"
#include "Item.h"
#include "Utils.h"
#include "Mario.h"
#include"QuestionBlock.h"



void CItem::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();
	
	for (int i = 0; i < coObjects->size(); i++)
	{
		LPGAMEOBJECT obj = coObjects->at(i);
		if (dynamic_cast<CQuestionBlock*>(obj))
		{
			CQuestionBlock* question = dynamic_cast<CQuestionBlock*>(obj);
			if (GetTouch() == 1)
			{
				if(x==question->x )
				question->SetState(BLOCK_STATE_INACTIVITY);
			}

		}
	}
	
	if (state == ITEM_STATE_MUSHROOM)
	{
		CalcPotentialCollisions(coObjects, coEvents);
		vy += 0.0009 * dt;
		vx = 0.009*dt;
		
		if (coEvents.size() == 0)
		{
			x -= dx;
			y += dy;
		}
		else
		{

			float min_tx, min_ty, nx = 0, ny;
			float rdx = 0;
			float rdy = 0;
			// TODO: This is a very ugly designed function!!!!
			FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);
			// block object
			x += min_tx * dx + nx * 0.4f;
			y += min_ty * dy + ny * 0.4f;

			// Check collision nx to change direction
			if (nx != 0 && ny == 0)
			{
				vx = -vx;
			}

			if (ny != 0)
			{
				vy = 0;
			}
		}
	}
	else if (state == ITEM_STATE_LEAF)
	{
		y += 0.02 * dt;
		x += 0.02 * dt;
	}
	else if (state == ITEM_STATE_COIN)
	{
		
		y -= dy;

		if (y < 20 && vy>0)
		{
			vy = -vy;
		}
		else if (y > 89)
		{
			SetState(ITEM_STATE_DISAPPEAR);
		}
	}

	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}


void CItem::Render()
{
	animation_set->at(0)->Render(x, y);
}
void CItem::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case ITEM_STATE_DISAPPEAR:
		x = -100;
		y = -100;
		break;
	case ITEM_STATE_COIN:
		vy = 0.09;
		break;
	case ITEM_STATE_FALL:
		vy = 0.09;
	}

}

void CItem::GetBoundingBox(float& l, float& t, float& r, float& b)
{
		l = x;
		t = y;
		r = x + ITEM_BBOX_WIDTH;
		b = y + ITEM_BBOX_HEIGHT;
	
}
