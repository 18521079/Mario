#include "StartScence.h"
#include "StartScence.h"
#include"Utils.h"
#include <iostream>
#include <fstream>
#include"BackGroundCollision.h"
#include"Background.h"
#include"StartBackground.h"
#include"BackgroundUp.h"
#include"Koopas.h"
#include"ItemIntro.h"



using namespace std;



CStartScence::CStartScence(int id, LPCWSTR filePath) :
	CScene(id, filePath)
{
	key_handler = new CStartScenceKeyHandler(this);
	CGame::GetInstance()->SetCamPos(0, -20);
}



#define SCENE_SECTION_UNKNOWN -1
#define SCENE_SECTION_TEXTURES 2
#define SCENE_SECTION_SPRITES 3
#define SCENE_SECTION_ANIMATIONS 4
#define SCENE_SECTION_ANIMATION_SETS	5
#define SCENE_SECTION_OBJECTS	6

#define OBJECT_TYPE_RED_MARIO			 0
#define OBJECT_TYPE_GREEN_MARIO			 10
#define OBJECT_TYPE_BACKGROUNDCOLLISION	1
#define OBJECT_TYPE_BACKGROUND	2
#define OBJECT_TYPE_BACKGROUNDUP	3
#define OBJECT_TYPE_BACKGROUNDDOWN	4
#define OBJECT_TYPE_KOOPAS_GREEN	16
#define OBJECT_TYPE_Goomba	5
#define OBJECT_TYPE_MUSHROOM	11
#define OBJECT_TYPE_LEAF	12
#define OBJECT_TYPE_SHELL_GREEN	7
#define OBJECT_TYPE_KOOPAS_GREEN_FINAL	6
#define OBJECT_TYPE_MENU	8

#define OBJECT_TYPE_PORTAL	50


#define MARIO_TIME_COUNT  1000

#define MAX_SCENE_LINE 1024
#define MARIO_TYPE_RED	0
#define MARIO_TYPE_GREEN	1

void CStartScence::_ParseSection_TEXTURES(string line)
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

void CStartScence::_ParseSection_SPRITES(string line)
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

void CStartScence::_ParseSection_ANIMATIONS(string line)
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

void CStartScence::_ParseSection_ANIMATION_SETS(string line)
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
void CStartScence::_ParseSection_OBJECTS(string line)
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
	case OBJECT_TYPE_RED_MARIO:
		obj = new CMario(MARIO_TYPE_RED, x, y);
		player1 = (CMario*)obj;
		//DebugOut(L"[INFO] Player1 created!\n");
		break;
	case OBJECT_TYPE_GREEN_MARIO:
		obj = new CMario(MARIO_TYPE_GREEN, x, y);
		player2 = (CMario*)obj;
		//DebugOut(L"[INFO] Player2 object created!\n");
		break;

	case OBJECT_TYPE_BACKGROUNDCOLLISION: obj = new CBackGroundCollision(); break;
	case OBJECT_TYPE_BACKGROUND: obj = new CBackground(); break;
	case OBJECT_TYPE_BACKGROUNDUP: obj = new CBackgroundUp(0); break;
	case OBJECT_TYPE_MENU: obj = new CMenuIntro();
		menu = (CMenuIntro*)obj;
		break;
	case OBJECT_TYPE_BACKGROUNDDOWN: obj = new CBackgroundUp(1); 
		backgrounddown = (CBackgroundUp*)obj;
		break;
		break;
	case OBJECT_TYPE_KOOPAS_GREEN: obj = new CKoopas(2);
		greenKoopas = (CKoopas*)obj;
		break;
	case OBJECT_TYPE_SHELL_GREEN: obj = new CKoopas(4);
		shellKoopas= (CKoopas*)obj;
		break;
	case OBJECT_TYPE_Goomba: obj = new CGoomba();
		goomba = (CGoomba*)obj;
		break;
	case OBJECT_TYPE_MUSHROOM: obj = new CItemIntro(0);
		mushroom = (CItemIntro*)obj;
		break;
	case OBJECT_TYPE_LEAF: obj = new CItemIntro(1);
		leaf = (CItemIntro*)obj;
		break;

	case OBJECT_TYPE_KOOPAS_GREEN_FINAL: obj = new CKoopas(3);
		finalKoopas = (CKoopas*)obj;
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

void CStartScence::Load()
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

void CStartScence::Update(DWORD dt)
{
	//item->SetState(ITEM_STATE_DISAPPEAR);
	player1->nx = -1;
	player2->SetState(MARIO_STATE_IDLE);
	player1->SetState(MARIO_STATE_IDLE);
	greenKoopas->SetState(KOOPAS_STATE_SHELL);
	goomba->SetState(GOOMBA_STATE_IDLE);
	shellKoopas->SetState(KOOPAS_STATE_SHELL);
	//finalKoopas->SetState(KOOPAS_STATE_SHELL);

	float x, y;
	player2->GetPosition(x, y);

	float x1, y1;
	greenKoopas->GetPosition(x1, y1);

	if (!isTimeStart)
	{
		player1->SetIsAppeared(false);
		player2->SetIsAppeared(false);
		time_start = GetTickCount();
		isTimeStart = true;
	}
	else if (GetTickCount() - time_start > 800)
	{
		player1->SetIsAppeared(true);
		player2->SetIsAppeared(true);
	}
	if (GetTickCount() - time_start > 1100)
	{
		player2->SetJumpingGreen(1);
		player2->SetState(MARIO_STATE_WALKING_RIGHT);
		player1->SetState(MARIO_STATE_WALKING_LEFT);

	}



	if (GetTickCount() - time_start >= 1300)
	{
		player2->SetJumpingGreen(1);
		player2->SetState(GREEN_MARIO_STATE_JUMP_UP);


	}
	if (GetTickCount() - time_start > 1700)
	{
		player2->SetState(GREEN_MARIO_STATE_JUMP_DOWN);
	}
	if (GetTickCount() - time_start > 2000)
	{
		player2->SetState(GREEN_MARIO_STATE_JUMP_UP);
		player1->SetState(MARIO_STATE_SIT);
	}
	if (GetTickCount() - time_start > 2500)
	{
		player1->SetState(MARIO_STATE_IDLE);
	}

	if (GetTickCount() - time_start > 2600)
	{
		player2->SetState(GREEN_MARIO_STATE_JUMP_DOWN);
	}
	if (GetTickCount() - time_start > 3000)
	{
		greenKoopas->SetState(SHELL_STATE_FALL);
		shellKoopas->SetState(SHELL_STATE_FALL);
		goomba->SetState(GOOMBA_STATE_FALL);
		mushroom->SetState(ITEM_STATE_FALL);
		leaf->SetState(ITEM_STATE_FALL);
		player2->SetJumpingGreen(0);
		player2->SetState(MARIO_STATE_WALKING_RIGHT);
	}
	if (GetTickCount() - time_start > 5500)
	{
		backgrounddown->SetState(BACKGROUND_STATE_FINAL);
	}
	if (GetTickCount() - time_start > 5900)
	{
		mushroom->SetState(ITEM_STATE_WALKING_LEFT);
	}
	if (GetTickCount() - time_start > 6000)
	{
		if (player1->GetJumping() == 0)
		{
			player1->SetState(MARIO_STATE_JUMP);
			player1->SetJumping(1);

		}
		player2->SetPosition(x, 120);
		player2->nx = -1;
		player2->SetState(MARIO_STATE_WALKING_LEFT);
	
	}
	if (GetTickCount() - time_start > 6090)
	{
		goomba->SetState(GOOMBA_STATE_WALKING);
	}
	if (GetTickCount() - time_start > 6100)
	{
		player1->SetLevel(MARIO_LEVEL_TAIL);
		leaf->SetState(ITEM_STATE_DISAPPEAR);
		player1->SetState(RED_MARIO_STATE_FALL);
		player1->SetJumping(0);
	}
	if (GetTickCount() - time_start > 6500)
	{
		goomba->SetState(GOOMBA_STATE_DIE);
	}
	if (GetTickCount() - time_start > 7000)
	{
		player1->SetState(MARIO_STATE_WALKING_RIGHT);
	}

	if (GetTickCount() - time_start > 7100)
	{
		goomba->SetState(GOOMBA_STATE_DISAPPEAR);
	}
	if (GetTickCount() - time_start > 7800)
	{
		greenKoopas->SetState(SHELL_STATE_WALKING_LEFT);
	}
	if (GetTickCount() - time_start > 8000)
	{
		shellKoopas->SetState(KOOPAS_STATE_DIE_FALL);
	}
	
	if (GetTickCount() - time_start > 8300 /*&& GetTickCount() - time_start < 8400*/)
	{
		player1->SetState(MARIO_STATE_IDLE);
		player2->SetAniHolding(1);
		player2->SetHolding(1);
		greenKoopas->SetHolding(1);

	}
	if (GetTickCount() - time_start > 8400)
	{
		player1->SetState(MARIO_STATE_WALKING_LEFT);

	}
	if(GetTickCount() - time_start > 9000)
	{
		player2->SetState(MARIO_STATE_IDLE);
		player2->SetHolding(0);
		greenKoopas->nx = 1;
		greenKoopas->SetHolding(0);
		greenKoopas->SetState(SHELL_STATE_WALKING_RIGHT);

	}
	if (GetTickCount() - time_start > 9400)
	{
		greenKoopas->SetState(KOOPAS_STATE_SHELL);
		player1->SetState(MARIO_STATE_WALKING_RIGHT);
		//greenKoopas->SetState(SHELL_STATE_WALKING_RIGHT);

	}

	if (GetTickCount() - time_start > 9500)
	{
		greenKoopas->SetState(KOOPAS_STATE_SHELL);

	}
	if (GetTickCount() - time_start > 10300)
	{
		greenKoopas->SetState(SHELL_STATE_WALKING_LEFT);
		player1->SetState(MARIO_STATE_IDLE);
		player2->SetState(MARIO_STATE_WALKING_RIGHT);

	}

	if (GetTickCount() - time_start > 10600)
	{
		player1->SetLevel(MARIO_LEVEL_SMALL);
		//player1->SetState(MARIO_STATE_WALKING_RIGHT);

	}
	if (GetTickCount() - time_start > 11800)
	{
		player1->SetState(MARIO_STATE_WALKING_RIGHT);
		menu->SetState(MENU_STATE_1);

	}
	if (GetTickCount() - time_start > 12300)
	{
		player1->SetIsAppeared(false);
	}





	vector<LPGAMEOBJECT> coObjects;
	for (size_t i = 0; i < objects.size(); i++)
	{
		coObjects.push_back(objects[i]);
	}


	for (size_t i = 0; i < objects.size(); i++)
	{
		objects[i]->Update(dt, &coObjects);
	}


	// skip the rest if scene was already unloaded (Mario::Update might trigger PlayScene::Unload)
	if (player1 == NULL) return;

	if (player2 == NULL) return;
	// Update camera to follow mario	



}

void CStartScence::Render()
{
	for (int i = 0; i < objects.size(); i++)
		objects[i]->Render();
}

/*
	Unload current scene
*/
void CStartScence::Unload()
{
	for (int i = 0; i < objects.size(); i++)
		delete objects[i];

	objects.clear();
	player1 = NULL;
	player2 = NULL;

	DebugOut(L"[INFO] Scene %s unloaded! \n", sceneFilePath);
}

void CStartScenceKeyHandler::OnKeyDown(int KeyCode)
{
	//DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
	CMenuIntro* menu = ((CStartScence*)scence)->GetMenuIntro();
	switch (KeyCode)
	{
	case DIK_3:
		CGame::GetInstance()->SwitchScene(3);
		break;
	case DIK_W:
		CGame::GetInstance()->SwitchScene(2);
		break;
	
			
	case DIK_Q:
		menu->SetState(MENU_STATE_2);
			break;
	}
}
void CStartScenceKeyHandler::OnKeyUp(int KeyCode)
{

}
void CStartScenceKeyHandler::KeyState(BYTE* states)
{

}