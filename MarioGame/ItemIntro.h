#pragma once
#include"GameObject.h"
#include"Background.h"
#define ITEM_STATE_DISAPPEAR 100
#define ITEM_STATE_FALL 200
#define ITEM_STATE_IDLE 300
#define ITEM_STATE_WALKING_LEFT 400

class CItemIntro : public  CBackground
{
	int type;
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
public:
	CItemIntro(int type);
	void SetState(int state);
};

