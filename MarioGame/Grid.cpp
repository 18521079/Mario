#include "Grid.h"
#include "Utils.h"
#include <fstream>
#include <iostream>
#include "QuestionBlock.h"
#include "Goomba.h"
#include"Breakable_Brick.h"
#include"Box.h"
#include"EndScene.h"
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
#include"Card.h"
#include"MovingBrick.h"

#include"PlayScence.h"

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
#define OBJECT_TYPE_CARD	20
#define OBJECT_TYPE_ENDSCENE0	21
#define OBJECT_TYPE_ENDSCENE1	22
#define OBJECT_TYPE_MOVINGBRICK			 26




CGrid::CGrid(LPCWSTR filePath)
{
	Load(filePath);
}

void CGrid::_ParseSection_SETTINGS(string line)
{
	vector<string> tokens = split(line);
	DebugOut(L"--> %s\n", ToWSTR(line).c_str());

	if (tokens.size() < 4) return; // skip invalid lines

	cellWidth = atoi(tokens[0].c_str());
	cellHeight = atoi(tokens[1].c_str());
	numCol = atoi(tokens[2].c_str());
	numRow = atoi(tokens[3].c_str());

	cells = new LPCELL[numCol];
	for (int i = 0; i < numCol; i++)
	{
		cells[i] = new Cell[numRow];
	}
}

void CGrid::_ParseSection_OBJECTS(string line)
{
	vector<string> tokens = split(line);
	DebugOut(L"--> %s\n", ToWSTR(line).c_str());

	CAnimationSets* animation_sets = CAnimationSets::GetInstance();

	if (tokens.size() < 4) return; // skip invalid lines

	int x = atoi(tokens[1].c_str());
	int y = atoi(tokens[2].c_str());

	int cellX = ((x+500) / cellWidth);
	int cellY = ((y + 500)/ cellHeight);

	int type = atoi(tokens[0].c_str());

	int ani_set_id = atoi(tokens[3].c_str());

	CGameObject* obj = NULL;

	switch (type)
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
	case OBJECT_TYPE_ENDSCENE0: obj = new CEndScene(0); break;
	case OBJECT_TYPE_ENDSCENE1: obj = new CEndScene(1); break;
	case OBJECT_TYPE_CARD: obj = new CCard(); break;
	case OBJECT_TYPE_QuestionBlock: obj = new CQuestionBlock(); break;
	case OBJECT_TYPE_BACKGROUNDCOLLISION: obj = new CBackGroundCollision(); break;
	case OBJECT_TYPE_BOX: obj = new CBox(); break;
	case OBJECT_TYPE_BREAKABLE_BRICK: obj = new CBreakableBrick(); break;
	case OBJECT_TYPE_MOVINGBRICK: obj = new CMovingBrick(); break;
	case OBJECT_TYPE_HOLDBRICK: obj = new CHoldBrick(); break;
	}

	// General object setup
	LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);

	if (obj != NULL)
	{

		obj->SetPosition(x, y);
		obj->SetAnimationSet(ani_set);
		obj->SetOrigin(x, y, obj->GetState());
		cells[cellX][cellY].Add(obj);
		obj->SetisOriginObj(false);
	}

}

void CGrid::Load(LPCWSTR filePath)
{
	DebugOut(L"[INFO] Start loading grid resources from : %s \n", filePath);

	ifstream f;
	f.open(filePath);

	// current resource section flag
	int section;

	char str[MAX_GRID_LINE];
	while (f.getline(str, MAX_GRID_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	

		if (line == "[SETTINGS]") {
			section = GRID_SECTION_SETTINGS; continue;
		}
		if (line == "[OBJECTS]") {
			section = GRID_SECTION_OBJECTS; continue;
		}
		//
		// data section
		//
		switch (section)
		{
		case GRID_SECTION_SETTINGS: _ParseSection_SETTINGS(line); break;
		case GRID_SECTION_OBJECTS: _ParseSection_OBJECTS(line); break;
		}
	}

	f.close();

	DebugOut(L"[INFO] Done loading scene resources %s\n", filePath);
}

void CGrid::GetObjects(vector<LPGAMEOBJECT>& listObject, int CamX, int CamY)
{
	CGame* game = CGame::GetInstance();

	int left=0, top=0, right=0, bottom=0;
	int i=0, j=0, k=0;

	left = ((CamX+500) / cellWidth);
	right = (CamX +300+500) / cellWidth;
	if (((CamX + 300+500) % cellWidth) != 0)
		right++;
	top = (CamY +500) / cellHeight;
	bottom = (CamY +800) / cellHeight;

	/*left = ((CamX) / 100);
	right = (CamX + game->GetScreenWidth()) / 100;
	if (((CamX + game->GetScreenWidth()) % 100) != 0)
		right++;
	top = (CamY) / 100;
	bottom = (CamY + game->GetScreenHeight()) / 100;*/

	LPGAMEOBJECT obj;

	if (right < 0 || left > numCol || bottom < 0 && top > numRow)
	{
		return;
	}

	if (right > numCol)
	{
		right = numCol;
	}
	if (bottom > numRow)
	{
		bottom = numRow;
	}
	if (left < 0)
	{
		left = 0;
	}
	if (top < 0)
	{
		top = 0;
	}

	for (i = left; i < right; i++)
	{
		for (j = top; j < bottom; j++)
		{
			if (cells)
				if (cells[i][j].GetListObjects().size() > 0)
				{
					for (k = 0; k < cells[i][j].GetListObjects().size(); k++)
					{
						if (!cells[i][j].GetListObjects().at(k)->Actived)
						{
							if (!cells[i][j].GetListObjects().at(k)->Actived)
							{
								float Ox, Oy;
								cells[i][j].GetListObjects().at(k)->GetOriginLocation(Ox, Oy);

								listObject.push_back(cells[i][j].GetListObjects().at(k));

								if (!((CPlayScene*)(CGame::GetInstance()->GetCurrentScene()))->IsInUseArea(Ox, Oy))// && cells[i][j].GetListObjects().at(k)->GetState() > 10)
								{
									cells[i][j].GetListObjects().at(k)->reset();
								}

								cells[i][j].GetListObjects().at(k)->SetActive(true);
							}
						}
					}
				}
		}
	}
	
}

void CGrid::Unload()
{
	if (this != nullptr)
		if (cells)
		{
			for (int i = 0; i < numCol; i++)
			{
				for (int j = 0; j < numRow; j++)
				{
					cells[i][j].Unload();
				}
			}
			delete cells;
			cells = NULL;
		}
}

//float Ox, Oy;
//cells[i][j].GetListObjects().at(k)->GetOriginLocation(Ox, Oy);
//if (!((CPlayScene*)(CGame::GetInstance()->GetCurrentScene()))->IsInUseArea(Ox, Oy))// && cells[i][j].GetListObjects().at(k)->GetState() > 10)
//cells[i][j].GetListObjects().at(k)->reset();


