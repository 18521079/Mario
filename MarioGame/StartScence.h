#pragma once
#include "Game.h"
#include "Textures.h"
#include"Scence.h"
#include "GameObject.h"
#include "Mario.h"
#include "PlayScence.h"
#include"BackGroundCollision.h"
#include"Koopas.h"
#include"Goomba.h"
#include"ItemIntro.h"
#include"BackgroundUp.h"



class CStartScence : public  CScene
{
protected:

	CMario* player1;	
	CMario* player2;
	CKoopas* greenKoopas;
	CKoopas* shellKoopas;
	CKoopas* finalKoopas;
	CGoomba* goomba;
	CItemIntro* mushroom;
	CItemIntro* leaf;
	CBackgroundUp* backgroundup;
	vector<LPGAMEOBJECT> objects;


	DWORD time_count = 0;
	DWORD time_start;
	bool isTimeStart = false;

	void _ParseSection_TEXTURES(string line);
	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);
	void _ParseSection_ANIMATION_SETS(string line);
	void _ParseSection_OBJECTS(string line);

public:
	CStartScence(int id, LPCWSTR filePath);

	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();

	vector<LPGAMEOBJECT> GetObjects()
	{
		return objects;
	}


	CMario* GetPlayer1() { return player1; }

	CMario* GetPlayer2() { return player2; }

	
};

class CStartScenceKeyHandler : public CScenceKeyHandler
{

public:
	virtual void KeyState(BYTE* states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
	CStartScenceKeyHandler(CScene* s) :CScenceKeyHandler(s) {};
};
