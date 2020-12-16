#include "MenuIntro.h"
CMenuIntro::CMenuIntro()
{
}

void CMenuIntro::Render()
{
	int ani =0;
	if (state == MENU_STATE_1)
		ani = MENU_ANI_1;
	else if (state == MENU_STATE_2)
		ani = MENU_ANI_2;
	animation_set->at(ani)->Render(x, y);
}

void CMenuIntro::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{

}
void CMenuIntro::SetState(int state)
{
	CGameObject::SetState(state);

	switch (state)
	{
	case MENU_STATE_DISAPPEAR:
		/*x = -200;
		y = -200;*/
		break;
	}
	

}