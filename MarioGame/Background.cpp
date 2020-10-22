#include "Background.h"
void CBackground::Render()
{
	animation_set->at(0)->Render(x, y);
	//RenderBoundingBox();
}
void CBackground::GetBoundingBox(float& l, float& t, float& r, float& b)
{

}