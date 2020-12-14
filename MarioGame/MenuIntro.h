#pragma once
#include"GameObject.h"
#define MENU_STATE_1	100
#define MENU_STATE_2	200
#define MENU_STATE_DISAPPEAR	300

#define MENU_ANI_1	1
#define MENU_ANI_2	2
class CMenuIntro :public CGameObject
{
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	public:
	CMenuIntro();
	void SetState(int state);

};

