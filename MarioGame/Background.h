#pragma once
#include "GameObject.h"
class CBackground : public CGameObject
{
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};

