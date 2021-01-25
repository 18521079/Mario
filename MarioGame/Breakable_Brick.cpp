#include "Breakable_Brick.h"
#include"Pbell.h"
#include"FRAGMENT.h"


CBreakableBrick::CBreakableBrick()
{
	SetState(BRICK_STATE_NORMAL);
	//SetState(FRAGMENT_STATE_APPEAR);


}
void CBreakableBrick::Render()
{
	if (state != BRICK_STATE_DISAPPEAR) {
		int ani = BRICK_ANI_NORMAL;
		if (state == BRICK_STATE_COIN)
			ani = BRICK_ANI_COIN;
		else if (state == BRICK_STATE_NORMAL)
		{
			ani = BRICK_ANI_NORMAL;
		}
		animation_set->at(ani)->Render(x, y);
	}

	//RenderBoundingBox();
}

void CBreakableBrick::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	if (state != BRICK_STATE_DISAPPEAR)
	{
		l = x;
		t = y;
		r = x + BRICK_BBOX_WIDTH;
		b = y + BRICK_BBOX_WIDTH;
	}
}
void CBreakableBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

	CGameObject::Update(dt, coObjects);
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	coEvents.clear();

	//CMario* mario = ((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer();

	if (state == BRICK_STATE_DISAPPEAR)
	{

		if (!hasUsed && isCoin == false && state != BRICK_STATE_COIN)
		{
			for (size_t i = 0; i < coObjects->size(); i++)
			{
				LPGAMEOBJECT obj = coObjects->at(i);
				if (dynamic_cast<CPiece*>(obj))
				{
					CPiece* fragment = dynamic_cast<CPiece*>(obj);
					if (fragment->getIsUsed() == false)
					{
						fragment->SetIsUsed(true);
						fragment->SetState(FRAGMENT_STATE_APPEAR);
						switch (fragment->GetTypeOfFragment())
						{
						case OBJECT_TYPE_FRAGMENT_LEFTTOP:
							fragment->SetPosition(this->x, this->y);
							break;
						case OBJECT_TYPE_FRAGMENT_RIGHTTOP:
							fragment->SetPosition(this->x + 16, this->y);
							break;
						case OBJECT_TYPE_FRAGMENT_LEFTBOTTOM:
							fragment->SetPosition(this->x, this->y + 16);
							break;
						case OBJECT_TYPE_FRAGMENT_RIGHTBOTTOM:
							fragment->SetPosition(this->x + 16, this->y + 16);
							break;
						}
					}
					countFragment++;
					if (countFragment > 4)
					{
						hasUsed = true;
						SetPosition(-100, -100);
					}
				}
			}
		}
	}



	for (int i = 0; i < coObjects->size(); i++)
	{
		LPGAMEOBJECT obj = coObjects->at(i);
		if (dynamic_cast<CPbell*>(obj))
		{
			CPbell* bell = dynamic_cast<CPbell*>(obj);
			if (bell->GetTouch() == 1 && state != BRICK_STATE_DISAPPEAR)
			{
				state = BRICK_STATE_COIN;
				//isCoin = true;

			}
			else if (bell->GetTouch() == 2 && state== BRICK_STATE_COIN)
			{
				state = BRICK_STATE_NORMAL;
				//isCoin = false;
			}
		}
	}
}
void CBreakableBrick::SetState(int state)
{

	CGameObject::SetState(state);
	switch (state)
	{
		/*case BRICK_STATE_DISAPPEAR:
			x = -100;
			y = -100;*/
	}
}