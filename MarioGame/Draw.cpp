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
		CSprites::GetInstance()->Get(ConverToInt(str[i]))->Draw(x, y);
		x += 8;
	}
}


int CDraw::ConverToInt(char C)
{
	return C - '0';
}