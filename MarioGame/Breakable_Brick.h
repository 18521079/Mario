#pragma once
#include "GameObject.h"

#define BRICK_BBOX_WIDTH  16
#define BRICK_BBOX_HEIGHT 16
#define BRICK_STATE_NORMAL 100
#define BRICK_STATE_DISAPPEAR	200

class CBreakableBrick : public CGameObject
{
public:
	CBreakableBrick();
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void SetState(int state);
};