#pragma once
#include "Background.h"

#define BACKGROUND_TYPE_UP 0
#define BACKGROUND_TYPE_DOWN 1

#define BACKGROUND_ANI_FINAL 1

#define BACKGROUND_Y -35

#define BACKGROUND_STATE_FINAL 100

#define BACKGROUND_UP_SPEED_Y		0.08f
#define BACKGROUND_DOWN_SPEED_Y		0.013f

class CBackgroundUp: public CBackground
{
	int type;
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	public:
	CBackgroundUp(int type);
	void SetState(int state);


};

