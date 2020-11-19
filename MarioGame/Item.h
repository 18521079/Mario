#pragma once
#include "GameObject.h"

#define ITEM_BBOX_WIDTH  16
#define ITEM_BBOX_HEIGHT 16

#define ITEM_STATE_LEAF 100
#define ITEM_STATE_MUSHROOM 200
#define ITEM_STATE_DISAPPEAR 300
#define ITEM_STATE_COIN 400


class CItem : public CGameObject
{
	int activate = 0;
public:
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void SetState(int state);
	int GetActivate() { return activate; };
	void SetActivate(int act) { activate = act; };
	
	
};