#pragma once

#include "GameObject.h"

#define KOOPAS_WALKING_SPEED 0.03f;

#define KOOPAS_BBOX_WIDTH 16
#define KOOPAS_BBOX_HEIGHT 26
#define KOOPAS_BBOX_HEIGHT_DIE 16

#define KOOPAS_STATE_WALKING 100
#define KOOPAS_STATE_DIE 200
#define KOOPAS_STATE_HoiSinh 300

#define KOOPAS_ANI_WALKING_LEFT 0
#define KOOPAS_ANI_WALKING_RIGHT 1
#define KOOPAS_ANI_DIE 2
#define KOOPAS_ANI_HoiSinh 3

class CKoopas : public CGameObject
{
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	int HoiSinh =0;
	DWORD HoiSinh_start;


public:
	CKoopas();
	void SetTickCount() { HoiSinh_start = GetTickCount(); };
	void BDHoiSinh() { HoiSinh = 1; };
	virtual void SetState(int state);
	//void StartHoiSinh() { HoiSinh = 1; HoiSinh_start = GetTickCount(); }
};