#include "Draw.h"
#include "Sprites.h"
#include "Mario.h"
#include <string>


void CDraw::DrawNumber(int max, float x, float y, int _string)
{
	string str = to_string(_string);

	for (int i = 0; i < (max - str.size()); i++)
	{
		CSprites::GetInstance()->Get(SPRITE_ID_ZERO)->Draw(x, y);
		x += 8;
	}
	for (int i = 0; i < str.size(); i++)
	{
		CSprites::GetInstance()->Get(SPRITE_ID_ZERO + ConverToInt(str[i]))->Draw(x, y);
		x += 8;
	}
}

void CDraw::DrawItem(float x, float y, int type)
{
	CSprites* sprites = CSprites::GetInstance();

	if (type == 1) {
		sprites->Get(SPRITE_ID_MUSHROOM);
	}
	else if (type == 2) {

	}
	else if (type == 3) {

	}
}

void CDraw::DrawPower(float x, float y, int m) {
	for (int i = 0; i < m; i++)
	{
		if (i > 6) return;
		if (i != 6)
			CSprites::GetInstance()->Get(SPRITE_POWER_WHITE)->Draw(x, y);
		else if (i == 6)
			CSprites::GetInstance()->Get(SPRITE_P_CHARACTER_WHITE)->Draw(x, y);
		x += 8;
	}

	for (int i = m; i < 7; i++)
	{
		if (i > 6) return;
		if (i != 6)
			CSprites::GetInstance()->Get(SPRITE_POWER_BLACK)->Draw(x, y);
		else if (i == 6)
			CSprites::GetInstance()->Get(SPRITE_P_CHARACTER_BLACK)->Draw(x, y);
		x += 8;
	}
}

int CDraw::ConverToInt(char C)
{
	return C - '0';
}

