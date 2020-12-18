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


	CMario* mario = ((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer();

}

void CHUD::Render()
{
	CGame* game = CGame::GetInstance();
	CMario* mario = ((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer();

	float cx=0.0f;
	float cy=0.0f;
	game->SetCamPos(cx, cy);


	CSprites* sprite = CSprites::GetInstance();
	sprite->Get(66661)->Draw(cx, cy + game->GetScreenHeight() - HUD_BBOX_HEIGHT + 5);
	sprite->Get(66660)->Draw(cx, cy + game->GetScreenHeight() - HUD_BBOX_HEIGHT+8);
	sprite->Get(66662)->Draw(cx+160, cy + game->GetScreenHeight() - HUD_BBOX_HEIGHT + 8);

	sprite->Get(SPRITE_M_CHARACTER)->Draw(cx + 3, cy + game->GetScreenHeight() - 20);
	sprite->Get(4)->Draw(cx + 38, cy + game->GetScreenHeight() - 18);
	sprite->Get(1)->Draw(cx + 38, cy + game->GetScreenHeight() - 25);
	sprite->Get(SPRITE_POWER_BLACK)->Draw(cx + 53, cy + game->GetScreenHeight() - 25);
	sprite->Get(SPRITE_POWER_BLACK)->Draw(cx + 61, cy + game->GetScreenHeight() - 25);
	sprite->Get(SPRITE_POWER_BLACK)->Draw(cx + 69, cy + game->GetScreenHeight() - 25);
	sprite->Get(SPRITE_POWER_BLACK)->Draw(cx + 77, cy + game->GetScreenHeight() - 25);
	sprite->Get(SPRITE_POWER_BLACK)->Draw(cx + 85, cy + game->GetScreenHeight() - 25);
	sprite->Get(SPRITE_POWER_BLACK)->Draw(cx + 93, cy + game->GetScreenHeight() - 25);

	if (mario->GetCard() == 1)
	{
		sprite->Get(SPRITE_ID_MUSHROOM)->Draw(cx + 165, cy + game->GetScreenHeight() - 25);
	}
	
	sprite->Get(SPRITE_P_CHARACTER_BLACK)->Draw(cx + 101, cy + game->GetScreenHeight() - 25);
	string str = to_string(mario->GetCoin());

	event->DrawNumber(3, cx + 125, cy + game->GetScreenHeight() - 18, time);
	event->DrawNumber(7, cx + 51, cy + game->GetScreenHeight() - 19, mario->GetScore());
	event->DrawNumber(str.size(), cx + 133, cy + game->GetScreenHeight() - 27, mario->GetCoin());
	
}

