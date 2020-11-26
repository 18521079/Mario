
#pragma once
#include "GameObject.h"

#define BRICK_BBOX_WIDTH  16
#define BRICK_BBOX_HEIGHT 16

class CKoopasBrick : public CGameObject
{
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
public:
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);

};


