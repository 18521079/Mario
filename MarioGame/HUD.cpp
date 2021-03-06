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
	int power;
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

	if (mario->GetPreFly() == 1 || mario->GetCanFly() == 1)
		power = 1;
	else
		power = 0;

	/*if (mario->GetPreFly()==1 || mario->GetCanFly()==1 )
	{
		int x = 0;
		for (int i = 0; i < 6; i++)
		{
				sprite->Get(SPRITE_POWER_WHITE)->Draw(cx + 53 + x, cy + game->GetScreenHeight() - 25);
				x += 8;
		}
		sprite->Get(SPRITE_P_CHARACTER_WHITE)->Draw(cx + 101, cy + game->GetScreenHeight() - 25);
	}
	else
	{
		int x = 0;
		for (int i = 0; i < 6; i++)
		{
			sprite->Get(SPRITE_POWER_BLACK)->Draw(cx + 53 + x, cy + game->GetScreenHeight() - 25);
			x += 8;
		}
		sprite->Get(SPRITE_P_CHARACTER_BLACK)->Draw(cx + 101, cy + game->GetScreenHeight() - 25);
	}*/

	if (mario->GetCard() == 1)
	{
		sprite->Get(SPRITE_ID_MUSHROOM)->Draw(cx + 165, cy + game->GetScreenHeight() - 25);
	}
	
	
	string str = to_string(mario->GetCoin());

	event->DrawNumber(3, cx + 125, cy + game->GetScreenHeight() - 18, time);
	event->DrawNumber(7, cx + 51, cy + game->GetScreenHeight() - 19, mario->GetScore());
	event->DrawNumber(str.size(), cx + 133, cy + game->GetScreenHeight() - 27, mario->GetCoin());

	if (mario->GetPreFly() == 1 || mario->GetCanFly() == 1)
	event->DrawPowerWhite(cx + 50, cy + game->GetScreenHeight() - 25);
	else
	event->DrawPowerBlack(cx + 50, cy + game->GetScreenHeight() - 25);

	
}

