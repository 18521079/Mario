#include "Background.h"
void CBackground::Render()
{
	animations[0]->Render(x, y);
	//RenderBoundingBox();
}

void CBackground::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + BRICK_BBOX_WIDTH;
	b = y + BRICK_BBOX_HEIGHT;
}

void CTree::Render()
{
	animations[0]->Render(x, y);
	//RenderBoundingBox();
}

void CTree::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + BRICK_BBOX_WIDTH;
	b = y + BRICK_BBOX_HEIGHT;
}

void CCloud::Render()
{
	animations[0]->Render(x, y);
	//RenderBoundingBox();
}

void CCloud::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + BRICK_BBOX_WIDTH;
	b = y + BRICK_BBOX_HEIGHT;
}

void CBoxblue::Render()
{
	animations[0]->Render(x, y);
	//RenderBoundingBox();
}

void CBoxblue::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + BRICK_BBOX_WIDTH;
	b = y + BRICK_BBOX_HEIGHT;
}

void CBoxgreen::Render()
{
	animations[0]->Render(x, y);
	//RenderBoundingBox();
}

void CBoxgreen::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + BRICK_BBOX_WIDTH;
	b = y + BRICK_BBOX_HEIGHT;
}

