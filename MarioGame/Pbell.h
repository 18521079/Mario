#pragma once
#include"GameObject.h"

#define BELL_BBOX_WIDTH  16
#define BELL_BBOX_HEIGHT 16
#define BELL_STATE_ACTIVITY 0
#define BELL_STATE_INACTIVITY 1
#define BELL_STATE_DISSAPPEAR 2

#define BELL_ANI_P 0
#define BELL_ANI_DISSAPPEAR 1


class CPbell: public CGameObject
{
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	public:
	int touch = 0;
	CPbell();
	int GetTouch() { return touch; };
	void SetTouch(int t) { touch = t; };
	//virtual void SetState(int state);
};

