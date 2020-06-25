#include "TourchFlame.h"

void CTourchFlame::Render()
{	
	animation_set->at(0)->Render(x, y);
}

void CTourchFlame::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + 16;
	b = y + 30;
}