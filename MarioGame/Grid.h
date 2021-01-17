#pragma once
#include"Cell.h"
#define MAX_GRID_LINE	1024
#define GRID_SECTION_UNKNOWN	-1
#define GRID_SECTION_SETTINGS	2
#define GRID_SECTION_OBJECTS	3
#define SCENE_SECTION_UNKNOWN			-1
class CGrid
{
	int sizeCell;
	int numColumns;
	int numRows;
	CCell** cells;

	int currentLeftRow = -1;
	int currentRightRow = -1;
	int currentTopColumn = -1;
	int currentBottomColumn = -1;
public:
	CGrid();
	CGrid(LPCWSTR path);
	void HandleGrid(vector<LPGAMEOBJECT>* coObjects, double camX, double camY, double screenWidth, double screenHeight);
	void _ParseSection_SETTINGS(string line);
	void _PareseSection_OBJECTS(string line);
	void UpdateCell();
	~CGrid();
};

