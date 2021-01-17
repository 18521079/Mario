#pragma once
#include "GameObject.h"
#include "Game.h"

class CCell
{
	vector<LPGAMEOBJECT> listGameObjectCell;
public:
	CCell();
	~CCell();
	void AddObjectIntoCell(LPGAMEOBJECT object) { listGameObjectCell.emplace_back(object); }
	vector<LPGAMEOBJECT> GetListGameObjectCell() { return listGameObjectCell; }
};

typedef CCell* LPCELL;