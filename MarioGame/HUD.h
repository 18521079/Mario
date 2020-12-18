#pragma once

#include "Game.h"
#include "GameObject.h"
#include "mario.h"
#include "Draw.h"


#define HUD_BBOX_WIDTH	245
#define HUD_BBOX_HEIGHT	42

class CHUD
{
	int time;
	DWORD count;
	int number;
	int dola;
	int score;

	bool isStop;
	DWORD timeItem;

	CDraw* event;

	static CHUD* instance;
public:
	CHUD()
	{
		time = 300;
		count = GetTickCount();
		isStop = false;
		number = 0;
		dola = 0;
		score = 0;
		timeItem = 0;
		event = new CDraw();
	}
	~CHUD()
	{
		if (event == NULL)
			delete event;

		event = NULL;
	}

	static CHUD* GetInstance();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObject = NULL);
	void Render();

	void TimeCountDown()
	{
		if (GetTickCount() - count >= 1 && time > 0)
		{
			time--;
			count = GetTickCount();
		}
	}

	void SetNumber(int n)
	{
		this->number = n;
		timeItem = GetTickCount();
	}

	int GetTime() { return time; }

	void SetTime(int t) { time = t; }
};

