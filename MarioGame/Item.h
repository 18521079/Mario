#pragma once
#include "GameObject.h"

#define ITEM_BBOX_WIDTH  16
#define ITEM_BBOX_HEIGHT 16

#define ITEM_STATE_LEAF 100
#define ITEM_STATE_MUSHROOM 200
#define ITEM_STATE_GREENMUSHROOM 600
#define ITEM_STATE_DISAPPEAR 300
#define ITEM_STATE_COIN 400
#define COIN_STATE_MOVING_DOWN 500
#define ITEM_STATE_COINS 700

#define ITEM_COINS_SPEED	-0.2f
#define ITEM_MUSHROOM_GRAVITY_FALL 0.0009f
#define ITEM_MUSHROOM_SPEED -0.003 f


class CItem : public CGameObject
{
	int touch = 0;
	int count = 0;
	//dung cho dong xu
	/*WORD time_Moveup_start = 0;
	DWORD time_Movedown_start = 0;*/
	bool isUsed = false;
public:
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void SetState(int state);
	int GetTouch() { return touch; };
	void SetTouch(int act) { touch = act; };
	int GetCount() { return count; };
	void SetCount(int act) { count = act; };
};