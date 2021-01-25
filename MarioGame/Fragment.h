#pragma once

#include "GameObject.h"
#include"Background.h"
#define OBJECT_TYPE_FRAGMENT_LEFTTOP	31
#define OBJECT_TYPE_FRAGMENT_RIGHTTOP	32
#define OBJECT_TYPE_FRAGMENT_LEFTBOTTOM	33
#define OBJECT_TYPE_FRAGMENT_RIGHTBOTTOM	34
#define FRAGMENT_STATE_DISAPPEAR		100
#define FRAGMENT_STATE_APPEAR			200
#define FRAGMENT_APPEAR_ANI				0

// define speed of fragment
#define SPEED_FRAGMENT_VX				0.15
#define SPEED_FRAGMENT_VY				0.15
#define FRAGMENT_GRAVITY_FALLING		0.0008
#define TIME_FOR_FRAGMENT_DISAPPEARING	400

class CPiece : public CBackground
{
private:
	bool isUsed = false;
	int typeOfFragment = 0;

	DWORD disappear_start;
	bool isDisappear = false;
public:
	/*CPiece();*/
	CPiece(int type);
	virtual void Render();
	virtual void GetBoundingBox(double& l, double& t, double& r, double& b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void SetState(int state);

	void SetIsUsed(bool value) { isUsed = value; }

	bool getIsUsed() { return isUsed; }
	int GetTypeOfFragment() { return typeOfFragment; }
};

