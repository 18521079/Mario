#pragma once
#include "GameObject.h"

#define BRICK_ANI_LEVEL	0
#define BRICK_ANI_M	1
#define BRICK_BBOX_WIDTH  16
#define BRICK_BBOX_HEIGHT 16
#define BRICK_STATE_M	100


class CHoldBrick : public CGameObject
{
	int canUp=1;
	int canDown=1;

public:
	CHoldBrick();
	CHoldBrick(int canup, int candown);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	int GetCanUp() { return canUp; };
	int GetCanDown() { return canDown; };

};
