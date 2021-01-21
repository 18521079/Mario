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

CGrid::CGrid()
{

}
CGrid::CGrid(LPCWSTR path)
{
	ifstream f;
	f.open(path);
	int section = GRID_SECTION_UNKNOWN;

	char str[MAX_GRID_LINE];
	while (f.getline(str, MAX_GRID_LINE))
	{
		string line(str);
		if (line[0] == '#') continue;	// skip comment lines	

		if (line == "[SETTINGS]") { section = GRID_SECTION_SETTINGS; continue; }
		if (line == "[OBJECTS]") {
			section = GRID_SECTION_OBJECTS; continue;
		}
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }
		switch (section)
		{
		case GRID_SECTION_SETTINGS:
			_ParseSection_SETTINGS(line);
			break;
		case GRID_SECTION_OBJECTS:
			_PareseSection_OBJECTS(line);
			break;

		}
	}

	f.close();

	
}
void CGrid::_ParseSection_SETTINGS(string line)
{
	vector<string> tokens = split(line);
	if (tokens.size() < 2) return;
	else
	{
		sizeCell = atoi(tokens[0].c_str());
		numRows = atoi(tokens[1].c_str());
		numColumns = atoi(tokens[2].c_str());
	}

	cells = new LPCELL[numRows];
	for (int i = 0; i < numRows; i++)
	{
		cells[i] = new CCell[numColumns];
	}
}

void CGrid::_PareseSection_OBJECTS(string line)
{
	vector<string> tokens = split(line);
	if (tokens.size() < 3) return; // skip invalid lines - an object set must have at least id, x, y

	int object_type = atoi(tokens[0].c_str());
	double x = atof(tokens[1].c_str());
	double y = atof(tokens[2].c_str());


	CAnimationSets* animation_sets = CAnimationSets::GetInstance();
	int ani_set_id = atoi(tokens[3].c_str());

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
	case OBJECT_TYPE_ENDSCENE0: obj = new CEndScene(0); break;
	case OBJECT_TYPE_ENDSCENE1: obj = new CEndScene(1); break;
	case OBJECT_TYPE_CARD: obj = new CCard(); break;
	case OBJECT_TYPE_QuestionBlock: obj = new CQuestionBlock(); break;
	case OBJECT_TYPE_BACKGROUNDCOLLISION: obj = new CBackGroundCollision(); break;
	case OBJECT_TYPE_BOX: obj = new CBox(); break;
	case OBJECT_TYPE_BREAKABLE_BRICK: obj = new CBreakableBrick(); break;
	case OBJECT_TYPE_HOLDBRICK: obj = new CHoldBrick(); break;
	}
	LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);
	if (obj != NULL)
	{
		obj->SetPosition(x, y);
		obj->SetOriginPosition(x, y);
		obj->SetAnimationSet(ani_set);
		int indexRow = x / sizeCell;
		int indexColumn = (y) / sizeCell;
		if (indexRow < numRows && indexColumn < numColumns)
		{
			cells[indexRow][indexColumn].AddObjectIntoCell(obj);
		}
	}

}

CGrid::~CGrid()
{
	delete cells;
	cells = NULL;
}

void CGrid::UpdateCell()
{

}

void CGrid::HandleGrid(vector<LPGAMEOBJECT>* coObjects, double camX, double camY, double screenWidth, double screenHeight)
{
	
	/*int indexLeftRow = max(0, camX / sizeCell);
	int indexRightRow = min(numRows - 1, (camX + screenWidth) / sizeCell);
	int indexTopColumn = max(0, (camY) / sizeCell);
	int indexBottomColumn = min(numColumns - 1, (camY + screenHeight) / sizeCell);

	if (indexLeftRow == currentLeftRow && indexRightRow == currentRightRow
		&& indexTopColumn == currentTopColumn && indexBottomColumn == currentTopColumn)
		return;

	currentLeftRow = indexLeftRow;
	currentRightRow = indexRightRow;
	currentTopColumn = indexTopColumn;
	currentBottomColumn = indexBottomColumn;
	

	for (int i = indexLeftRow; i <= indexRightRow; i++)
	{
		for (int j = indexTopColumn; j <= indexBottomColumn; j++)
		{
			if (!cells[i][j].GetListGameObjectCell().empty())
			{
				for (int m = 0; m < cells[i][j].GetListGameObjectCell().size(); m++)
				{
					if (cells[i][j].GetListGameObjectCell().at(m)->GetIsActive() == false)
					{
						coObjects->emplace_back(cells[i][j].GetListGameObjectCell().at(m));
						cells[i][j].GetListGameObjectCell().at(m)->SetIsActive(true);
					}
				}
			}
		}
	}*/

}

