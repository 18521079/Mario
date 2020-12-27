#pragma once
#include "GameObject.h"

#define BRICK_BBOX_WIDTH  16
#define BRICK_BBOX_HEIGHT 16

#define BLOCK_ANI_QUESTIONMARK 0
#define BLOCK_ANI_NORMAL 1

#define BLOCK_STATE_ACTIVITY 1
#define BLOCK_STATE_INACTIVITY 2

class CQuestionBlock : public CGameObject
{
	bool isMovingUp = true;
	int countTimeUp = 0;
public:
	CQuestionBlock();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	
};
