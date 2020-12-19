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

	int GetTime() { return time; }

	void SetTime(int t) { time = t; }
};

