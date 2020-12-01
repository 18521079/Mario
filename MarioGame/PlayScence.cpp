#include <iostream>
#include <fstream>
#include"Background.h"
#include "PlayScence.h"
#include "Utils.h"
#include "Textures.h"
#include "Sprites.h"
#include "Portal.h"
#include "QuestionBlock.h"
#include "Goomba.h"
#include"Breakable_Brick.h"
#include"Box.h"
#include "Flower.h"
#include "Koopas.h"
#include "BackGroundCollision.h"
#include "Ball.h"
#include"Coin.h"
#include"Fire_Ball.h"
#include"Item.h"
#include"KoopasBrick.h"
#include"WingGoomba.h"
#include"Pbell.h"
#include"HoldBrick.h"


using namespace std;

CPlayScene::CPlayScene(int id, LPCWSTR filePath) :
	CScene(id, filePath)
{
	key_handler = new CPlayScenceKeyHandler(this);
}

/*
	Load scene resources from scene file (textures, sprites, animations and objects)
	See scene1.txt, scene2.txt for detail format specification
*/

#define SCENE_SECTION_UNKNOWN -1
#define SCENE_SECTION_TEXTURES 2
#define SCENE_SECTION_SPRITES 3
#define SCENE_SECTION_ANIMATIONS 4
#define SCENE_SECTION_ANIMATION_SETS	5
#define SCENE_SECTION_OBJECTS	6




#define OBJECT_TYPE_MARIO	0
#define OBJECT_TYPE_BACKGROUNDCOLLISION	1
#define OBJECT_TYPE_BACKGROUND	2
#define OBJECT_TYPE_QuestionBlock	3
#define OBJECT_TYPE_Goomba	4
#define OBJECT_TYPE_BREAKABLE_BRICK	5
#define OBJECT_TYPE_BOX	6
#define OBJECT_TYPE_KOOPAS_RED	7
#define OBJECT_TYPE_FLOWER	8
#define OBJECT_TYPE_BALL	9
#define OBJECT_TYPE_COIN	10
#define OBJECT_TYPE_FIREBALL	11
#define OBJECT_TYPE_ITEM	12
#define OBJECT_TYPE_KOOPASBRICK	13
#define OBJECT_TYPE_WINGGOOMBA	14
#define OBJECT_TYPE_PBELL	15
#define OBJECT_TYPE_KOOPAS_GREEN	16
#define OBJECT_TYPE_KOOPAS_WING	17
#define OBJECT_TYPE_HOLDBRICK	18

#define OBJECT_TYPE_PORTAL	50

#define MAX_SCENE_LINE 1024


void CPlayScene::_ParseSection_TEXTURES(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 5) return; // skip invalid lines

	int texID = atoi(tokens[0].c_str());
	wstring path = ToWSTR(tokens[1]);
	int R = atoi(tokens[2].c_str());
	int G = atoi(tokens[3].c_str());
	int B = atoi(tokens[4].c_str());

	CTextures::GetInstance()->Add(texID, path.c_str(), D3DCOLOR_XRGB(R, G, B));
}

void CPlayScene::_ParseSection_SPRITES(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 6) return; // skip invalid lines

	int ID = atoi(tokens[0].c_str());
	int l = atoi(tokens[1].c_str());
	int t = atoi(tokens[2].c_str());
	int r = atoi(tokens[3].c_str());
	int b = atoi(tokens[4].c_str());
	int texID = atoi(tokens[5].c_str());

	LPDIRECT3DTEXTURE9 tex = CTextures::GetInstance()->Get(texID);
	if (tex == NULL)
	{
		DebugOut(L"[ERROR] Texture ID %d not found!\n", texID);
		return;
	}

	CSprites::GetInstance()->Add(ID, l, t, r, b, tex);
}

void CPlayScene::_ParseSection_ANIMATIONS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 3) return; // skip invalid lines - an animation must at least has 1 frame and 1 frame time

	//DebugOut(L"--> %s\n",ToWSTR(line).c_str());

	LPANIMATION ani = new CAnimation();

	int ani_id = atoi(tokens[0].c_str());
	for (int i = 1; i < tokens.size(); i += 2)	// why i+=2 ?  sprite_id | frame_time  
	{
		int sprite_id = atoi(tokens[i].c_str());
		int frame_time = atoi(tokens[i + 1].c_str());
		ani->Add(sprite_id, frame_time);
	}

	CAnimations::GetInstance()->Add(ani_id, ani);
}

void CPlayScene::_ParseSection_ANIMATION_SETS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 2) return; // skip invalid lines - an animation set must at least id and one animation id

	int ani_set_id = atoi(tokens[0].c_str());

	LPANIMATION_SET s = new CAnimationSet();

	CAnimations* animations = CAnimations::GetInstance();

	for (int i = 1; i < tokens.size(); i++)
	{
		int ani_id = atoi(tokens[i].c_str());

		LPANIMATION ani = animations->Get(ani_id);
		s->push_back(ani);
	}

	CAnimationSets::GetInstance()->Add(ani_set_id, s);
}

/*
	Parse a line in section [OBJECTS]
*/
void CPlayScene::_ParseSection_OBJECTS(string line)
{
	vector<string> tokens = split(line);

	//DebugOut(L"--> %s\n",ToWSTR(line).c_str());

	if (tokens.size() < 3) return; // skip invalid lines - an object set must have at least id, x, y

	int object_type = atoi(tokens[0].c_str());
	float x = atof(tokens[1].c_str());
	float y = atof(tokens[2].c_str());

	int ani_set_id = atoi(tokens[3].c_str());

	CAnimationSets* animation_sets = CAnimationSets::GetInstance();

	CGameObject* obj = NULL;

	switch (object_type)
	{
	case OBJECT_TYPE_BACKGROUND: obj = new CBackground(); break;
	case OBJECT_TYPE_FLOWER: obj = new CFlower(); break;
	case OBJECT_TYPE_ITEM: obj = new CItem(); break;
	case OBJECT_TYPE_KOOPAS_RED: obj = new CKoopas(1); break;
	case OBJECT_TYPE_KOOPAS_GREEN: obj = new CKoopas(2); break;
	case OBJECT_TYPE_KOOPAS_WING: obj = new CKoopas(3); break;
	case OBJECT_TYPE_Goomba: obj = new CGoomba(); break;
	case OBJECT_TYPE_BALL: obj = new CBall(); break;
	case OBJECT_TYPE_COIN: obj = new CCoin(); break;
	case OBJECT_TYPE_FIREBALL: obj = new CFireBall(); break;
	case OBJECT_TYPE_KOOPASBRICK: obj = new CKoopasBrick(); break;
	case OBJECT_TYPE_WINGGOOMBA: obj = new CWingGoomba(); break;
	case OBJECT_TYPE_PBELL: obj = new CPbell(); break;
	case OBJECT_TYPE_MARIO:
		if (player != NULL)
		{
			DebugOut(L"[ERROR] MARIO object was created before!\n");
			return;
		}
		obj = new CMario(x, y);
		player = (CMario*)obj;

		DebugOut(L"[INFO] Player object created!\n");
		break;
	case OBJECT_TYPE_QuestionBlock: obj = new CQuestionBlock(); break;
	case OBJECT_TYPE_BACKGROUNDCOLLISION: obj = new CBackGroundCollision(); break;
	case OBJECT_TYPE_BOX: obj = new CBox(); break;
	case OBJECT_TYPE_BREAKABLE_BRICK: obj = new CBreakableBrick(); break;
	case OBJECT_TYPE_HOLDBRICK: obj = new CHoldBrick(); break;
	case OBJECT_TYPE_PORTAL:
	{
		float r = atof(tokens[4].c_str());
		float b = atof(tokens[5].c_str());
		int scene_id = atoi(tokens[6].c_str());
		obj = new CPortal(x, y, r, b, scene_id);
	}
	break;
	default:
		DebugOut(L"[ERR] Invalid object type: %d\n", object_type);
		return;
	}

	// General object setup
	obj->SetPosition(x, y);

	LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);

	obj->SetAnimationSet(ani_set);
	objects.push_back(obj);
}

void CPlayScene::Load()
{
	DebugOut(L"[INFO] Start loading scene resources from : %s \n", sceneFilePath);

	ifstream f;
	f.open(sceneFilePath);

	// current resource section flag
	int section = SCENE_SECTION_UNKNOWN;

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	

		if (line == "[TEXTURES]") { section = SCENE_SECTION_TEXTURES; continue; }
		if (line == "[SPRITES]") {
			section = SCENE_SECTION_SPRITES; continue;
		}
		if (line == "[ANIMATIONS]") {
			section = SCENE_SECTION_ANIMATIONS; continue;
		}
		if (line == "[ANIMATION_SETS]") {
			section = SCENE_SECTION_ANIMATION_SETS; continue;
		}
		if (line == "[OBJECTS]") {
			section = SCENE_SECTION_OBJECTS; continue;
		}
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }

		//
		// data section
		//
		switch (section)
		{
		case SCENE_SECTION_TEXTURES: _ParseSection_TEXTURES(line); break;
		case SCENE_SECTION_SPRITES: _ParseSection_SPRITES(line); break;
		case SCENE_SECTION_ANIMATIONS: _ParseSection_ANIMATIONS(line); break;
		case SCENE_SECTION_ANIMATION_SETS: _ParseSection_ANIMATION_SETS(line); break;
		case SCENE_SECTION_OBJECTS: _ParseSection_OBJECTS(line); break;
		}
	}

	f.close();

	CTextures::GetInstance()->Add(ID_TEX_BBOX, L"textures\\bbox.png", D3DCOLOR_XRGB(255, 255, 255));

	DebugOut(L"[INFO] Done loading scene resources %s\n", sceneFilePath);
}

void CPlayScene::Update(DWORD dt)
{
	// We know that Mario is the first object in the list hence we won't add him into the colliable object list
	// TO-DO: This is a "dirty" way, need a more organized way 

	vector<LPGAMEOBJECT> coObjects;
	for (size_t i = 1; i < objects.size(); i++)
	{
		coObjects.push_back(objects[i]);
	}

	for (size_t i = 0; i < objects.size(); i++)
	{
		objects[i]->Update(dt, &coObjects);
	}

	// skip the rest if scene was already unloaded (Mario::Update might trigger PlayScene::Unload)
	if (player == NULL) return;

	// Update camera to follow mario
	float cx, cy;
	player->GetPosition(cx, cy);

	CGame* game = CGame::GetInstance();
	cx -= game->GetScreenWidth() / 2;
	cy -= game->GetScreenHeight() / 2;

	if (cx < 0) cx = 0;
	CGame::GetInstance()->SetCamPos(round(cx), 0.0f /*cy*/);
	if(player->GetLevel() == MARIO_LEVEL_TAIL /*&& player->GetState()==MARIO_STATE_FLY*/ )
	{
		if (cy > -40)
		{
			CGame::GetInstance()->SetCamPos(round(cx), -35.0f);
		}
		
		
			CGame::GetInstance()->SetCamPos(round(cx), round(cy));
		
	}
}

void CPlayScene::Render()
{
	for (int i = 0; i < objects.size(); i++)
		objects[i]->Render();
}

/*
	Unload current scene
*/
void CPlayScene::Unload()
{
	for (int i = 0; i < objects.size(); i++)
		delete objects[i];

	objects.clear();
	player = NULL;

	DebugOut(L"[INFO] Scene %s unloaded! \n", sceneFilePath);
}

void CPlayScenceKeyHandler::OnKeyDown(int KeyCode)
{
	//DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);

	CMario* mario = ((CPlayScene*)scence)->GetPlayer();
	float x, y;
	mario->GetPosition(x, y);
	switch (KeyCode)
	{
	case DIK_SPACE:
		if (mario->GetJumping() == 0)
		{
			mario->SetState(MARIO_STATE_JUMP);
			mario->ny = 1;
			mario->SetJumping(1);
		}

		break;
	case DIK_O:
		if (mario->GetJumping() == 0)
		{
			mario->SetState(MARIO_STATE_HIGHT_JUMP);
			mario->ny = 1;
			mario->SetJumping(1);
		}
	case DIK_Q:
		mario->SetPosition(x, y - 16.0f);
		mario->SetLevel(MARIO_LEVEL_BIG);
		break;
	case DIK_W:
		mario->SetState(MARIO_STATE_KICK);
		break;
	case DIK_A:
		mario->Reset();
		break;
	case DIK_E:
		mario->SetLevel(MARIO_LEVEL_TAIL);
		break;
	case DIK_R:
		mario->SetLevel(MARIO_LEVEL_FIRE);
		break;
		/*case DIK_DOWN:
			mario->SetState(MARIO_STATE_SIT);*/
	case DIK_U:
		//mario->SetState(MARIO_STATE_HOLDKOOPAS);
		if (mario->GetLevel() == MARIO_LEVEL_FIRE)
			mario->SetShoot(1);
		break;
	case DIK_P:
		mario->SetHolding(1);
		break;
	case DIK_S:
		mario->SetSpin(1);
		mario->StartSpin();
		break;
	case DIK_D:
		if (mario->GetFirstTimeFly() == 0)
		{
			if (mario->vx > MARIO_WALKING_SPEED)
			{
				mario->SetFirstTimeFly(1);
				mario->SetFlyingStart();
			}
		}
		
		if (mario->GetFirstTimeFly() == 1 && GetTickCount() - mario->GetFlyingStart() <= 5000)
		{
			mario->SetState(MARIO_STATE_FLY);
		}
		else
		{
			mario->SetState(MARIO_STATE_FALL);
		}
		break;
	case DIK_F:
		/*if (mario->vx > 0)
		{*/
			if (mario->vx > 0.2f)
			{
				mario->SetCanFly(1);
			}
			if (mario->GetFirstTimeFly() == 0 && mario->GetCanFly()==1)
			{
				mario->SetFirstTimeFly(1);
				mario->SetFlyingStart();
			}
			if (mario->GetFirstTimeFly() == 1 && GetTickCount() - mario->GetFlyingStart() <= 5000)
			{
				mario->SetState(MARIO_STATE_FLY);
			}
			else
			{
				mario->SetState(MARIO_STATE_FALL);
				mario->SetCanFly(0);
			}

			break;
		/*}*/

	}
}

void CPlayScenceKeyHandler::OnKeyUp(int KeyCode)
{
	//DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);

	CMario* mario = ((CPlayScene*)scence)->GetPlayer();
	float x, y;
	mario->GetPosition(x, y);
	switch (KeyCode)
	{
	case DIK_P:
		mario->SetHolding(0);
		mario->SetKickKoopas(1);
		break;
	case DIK_D:
		mario->SetCanFly(0);
		break;
	/*case DIK_F:
		mario->SetState(MARIO_STATE_FLY);*/

		break;
	}
}

void CPlayScenceKeyHandler::KeyState(BYTE* states)
{

	CGame* game = CGame::GetInstance();
	CMario* mario = ((CPlayScene*)scence)->GetPlayer();

	float x, y;
	mario->GetPosition(x, y);

	// disable control key when Mario die 
	if (mario->GetState() == MARIO_STATE_DIE) return;
	if (game->IsKeyDown(DIK_RIGHT))
		if (game->IsKeyDown(DIK_LSHIFT))
		{
			if (mario->Getspeedup_start() == 0)
				mario->StartSpeedup();
			mario->SetState(MARIO_STATE_FAST_WALKING_RIGHT);
			if (GetTickCount() - mario->Getspeedup_start() > 30)
			{
				mario->SetspeedLevel(mario->GetspeedLevel() + 1);
				mario->Setspeedup_start(0);
			}
		}
		else
		{

			mario->SetState(MARIO_STATE_WALKING_RIGHT);
		}
	else if (game->IsKeyDown(DIK_LEFT))
	{
		if (game->IsKeyDown(DIK_LSHIFT))
		{
			if (mario->Getspeedup_start() == 0)
				mario->StartSpeedup();
				mario->SetState(MARIO_STATE_FAST_WALKING_LEFT);
				if (GetTickCount() - mario->Getspeedup_start() > 30 && mario->GetspeedLevel() <= 100)
				{
					mario->SetspeedLevel(mario->GetspeedLevel() + 1);
					mario->Setspeedup_start(0);
				}
		}
		else
		{
			mario->SetspeedLevel(0);
			mario->SetState(MARIO_STATE_WALKING_LEFT);
		}
	}
	else if (game->IsKeyDown(DIK_LSHIFT))
		mario->SetState(MARIO_STATE_KICK);

	else if (game->IsKeyDown(DIK_Y))
	{
		mario->SetState(MARIO_STATE_FLY);
		mario->ny = 1;
	}

	else if (game->IsKeyDown(DIK_SPACE))
	{
		mario->ny = 1;
	}
	else if (game->IsKeyDown(DIK_DOWN))
	{
		mario->SetState(MARIO_STATE_SIT);
		//mario->SetPosition(x, y - 1.0f);
	}
	else if (game->IsKeyDown(DIK_T))
	{
		mario->SetState(MARIO_STATE_FAST_WALKING);
	}
	/*else if (game->IsKeyDown(DIK_U))
	{
		mario->SetState(MARIO_STATE_HOLDKOOPAS);
	}*/
	/*else if (game->IsKeyDown(DIK_D))
	{
		mario->SetCanFly(1);
		if (mario->GetLevel() == MARIO_LEVEL_TAIL && (mario->GetCanFly() == 1))
		{
			if (mario->nx > 0)
			{
				mario->SetState(MARIO_STATE_FLY_RIGHT);
			}
			else
			{
				mario->SetState(MARIO_STATE_FLY_LEFT);

			}
			if (mario->GetFlyingStart() == 0)
			{
				mario->StartFlying();
			}
			mario->SetFlying(true);
		}
		else
		{
			if (mario->GetCanFall() == true)
			{
				mario->SetState(MARIO_STATE_FALL);
				mario->SetFalling(1);
			}

		}
	}*/
	else
	
		mario->SetState(MARIO_STATE_IDLE);

}