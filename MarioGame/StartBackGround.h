#pragma once
#include "GameObject.h"


#define BACKGROUND_STATE_IDLE		0
#define BACKGROUND_STATE_DOWN		100
#define BACKGROUND_STATE_UP	200

#define BACKGROUND_ANI_FIRST		0	
#define BACKGROUND_ANI_SECOND		1
#define BACKGROUND_ANI_FINAL	2

#define BACKGROUND_TYPE_FIRST		1
#define BACKGROUND_TYPE_SECOND		2
#define BACKGROUND_TYPE_FINAL		3

class CStartBackground : public CGameObject
{
private:
	int type;
	int isFirst=1;
	int isSecond = 0;
	int isFinal = 0;
	
public:
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void SetState(int state);

};