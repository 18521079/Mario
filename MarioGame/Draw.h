#pragma once

#include "Game.h"
#include "GameObject.h"
#include "mario.h"
#include"Sprites.h"

#define SPRITE_ID_ZERO	0

#define SPRITE_ID_MUSHROOM	91001
#define	SPRITE_ID_FLOWER	91002
#define SPRITE_ID_STAR		91003

#define SPRITE_M_CHARACTER	91004
#define SPRITE_L_CHARACTER	91005

#define SPRITE_POWER_BLACK	91012
#define SPRITE_POWER_WHITE	91011
#define SPRITE_P_CHARACTER_BLACK	91014
#define SPRITE_P_CHARACTER_WHITE	91013

class CDraw
{
	/*int time;
	DWORD count;*/
public:
	/*void StartCount() { count = GetTickCount(); }*/
	void DrawNumber(int max, float x, float y, int number = 0);
	void DrawPowerBlack(float x, float y);
	void DrawPowerWhite(float x, float y);
	int ConverToInt(char C);
};
