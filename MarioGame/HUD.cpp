#include "HUD.h"
#include "Game.h"
#include <string>
#include"Mario.h"
#include"PlayScence.h"

CHUD* CHUD::instance = NULL;

CHUD* CHUD::GetInstance()
{
	if (instance == NULL)
		instance = new CHUD();

	return instance;
}

void CHUD::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (isStop)
	{
		return;
	}

	if (GetTickCount() - count >= 1000)
	{
		if (time > 0)
			time--;
		count = GetTickCount();
	}

	if (timeItem > 0)
	{
		if (GetTickCount() - timeItem >= 10000)
		{
			number = 0;
			timeItem = 0;
		}
	}

	CMario* mario = ((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer();

	/*if (mario->numItem == 1) {
		it1 = mario->GetItem();
	}
	else if (mario->numItem == 2) {
		it2 = mario->GetItem();
	}
	else if (mario->numItem == 3) {
		it3 = mario->GetItem();
	}
	else if (mario->numItem > 3) {
		it1 = it2 = it3 = -1;
		mario->numItem -= 3;
	}*/
}

void CHUD::Render()
{
	CGame* game = CGame::GetInstance();
	CMario* mario = ((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer();

	float cx=0.0f;
	float cy=0.0f;
	game->SetCamPos(cx, cy);


	CSprites* sprite = CSprites::GetInstance();
	sprite->Get(50000)->Draw(cx, cy + game->GetScreenHeight() - HUD_BBOX_HEIGHT);
	sprite->Get(SPRITE_M_CHARACTER)->Draw(cx + 10, cy + game->GetScreenHeight() - 20);

	string str = to_string(mario->GetCoin());

	event->DrawNumber(3, cx + 132, cy + game->GetScreenHeight() - 19, time);
	event->DrawNumber(7, cx + 58, cy + game->GetScreenHeight() - 19, mario->GetScore());
	//event->DrawNumber(1, cx + 40, cy + game->GetScreenHeight() - 19, mario->GetLive());
	//event->DrawNumber(1, cx + 42, cy + game->GetScreenHeight() - 27, game->GetCurrentSceneId());
	event->DrawNumber(str.size(), cx + 140, cy + game->GetScreenHeight() - 27, mario->GetCoin());

	//event->DrawPower(cx + 58, cy + game->GetScreenHeight() - 27, mario->metter);

	/*if (it1 != -1) {
		event->DrawItem(cx + 171, cy + game->GetScreenHeight() - 28, it1);
	}
	if (it2 != -1) {
		event->DrawItem(cx + 195, cy + game->GetScreenHeight() - 28, it2);
	}
	if (it3 != -1) {
		event->DrawItem(cx + 219, cy + game->GetScreenHeight() - 28, it3);
	}*/
}

