#pragma once
#include "Game.h"
#include "Textures.h"
#include "Scence.h"
#include "GameObject.h"
#include "BackGroundCollision.h"
#include "Mario.h"
#include "Goomba.h"
#include"HUD.h"
#include"Grid.h"
#include"Map.h"
//#include "Koopas.h"

#define IN_USE_WIDTH		330
#define IN_USE_HEIGHT		300
#define SCENE_SECTION_GRID	8


class CPlayScene : public CScene
{
protected:
	CMario* player;					// A play scene has to have player, right?
	CHUD* HUD;
	CGrid* grid;
	Map* map;
	float cx1 = 10;

	vector<LPGAMEOBJECT> objects;

	void _ParseSection_TEXTURES(string line);
	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);
	void _ParseSection_ANIMATION_SETS(string line);
	void _ParseSection_OBJECTS(string line);
	void _ParseSection_GRID(string line);
	void _ParseSection_MAP(string line);


public:
	CPlayScene(int id, LPCWSTR filePath);
	bool IsInUseArea(float x, float y);

	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();

	CMario* GetPlayer() { return player; }

	//friend class CPlayScenceKeyHandler;
};

class CPlayScenceKeyHandler : public CScenceKeyHandler
{
public:
	virtual void KeyState(BYTE* states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
	CPlayScenceKeyHandler(CScene* s) :CScenceKeyHandler(s) {};
};


