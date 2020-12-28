#pragma once
#include"GameObject.h"
#include"Background.h"

#define	ENDSCENE_STATE_DISAPPEAR	0
#define	ENDSCENCE_STATE_NORMAL	1


class CEndScene :public CBackground
{
	int type;
	bool used=false;
	DWORD act_start = 0;
public:

	void SetTickCount() { act_start = GetTickCount(); used == true; };
	CEndScene(int type);
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	//virtual void SetState(int state);
	//virtual void GetBoundingBox(float& l, float& t, float& r, float& b);

};

