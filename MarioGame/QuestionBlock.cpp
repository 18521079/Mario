#include"QuestionBlock.h"
#include "Item.h"

CQuestionBlock::CQuestionBlock()
{
	SetState(BLOCK_STATE_ACTIVITY);
}
void CQuestionBlock::Render()
{
	int ani = BLOCK_ANI_QUESTIONMARK;
	if (state == BLOCK_STATE_INACTIVITY) {
		ani = BLOCK_ANI_NORMAL;
	}
	animation_set->at(ani)->Render(x, y);
	//RenderBoundingBox();
}

void CQuestionBlock::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
	if (state == BLOCK_STATE_INACTIVITY)
	{
		if (isMovingUp)
		{

			if (countTimeUp > 4)
			{
				isMovingUp = false;
			}
			else
			{
				y -= 1;
				countTimeUp++;
			}
		}
		else
		{
			if (countTimeUp != 0)
			{
				y += 1;
				countTimeUp--;
			}
		}
	}
}


void CQuestionBlock::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + 16;
	b = y + 16;
}
