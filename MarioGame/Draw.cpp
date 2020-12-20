#include "Draw.h"
#include "Sprites.h"
#include "Mario.h"
#include <string>


void CDraw::DrawNumber(int size, float x, float y, int number)
{
	string str = to_string(number);

	for (int i = 0; i < (size - str.size()); i++)
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