#include "EndScene.h"
#include"PlayScence.h"

CEndScene::CEndScene(int t)
{
	type = t;
	state = 0;
}
void CEndScene::Render()
{
	if (state == ENDSCENCE_STATE_NORMAL)
	{
		animation_set->at(0)->Render(x, y);
	}
}

void CEndScene::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
	CMario* mario = ((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	
	if (mario->GetCard() == 1)
	{
		if (used == false)
		{
			used = true;
			SetTickCount();
		}
		if (type == 0)
		{
			SetState(ENDSCENCE_STATE_NORMAL) ;
		}
		else
		{
			if (used == true)
			{
				if (GetTickCount() - act_start > 1000)
				{
					SetState(ENDSCENCE_STATE_NORMAL);

				}
			}
		}
	}

}