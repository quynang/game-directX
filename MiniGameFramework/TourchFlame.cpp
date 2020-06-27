#include "TourchFlame.h"


CTourchFlame::CTourchFlame() {
	isVisible = true;
}
void CTourchFlame::Render()
{
	if (isVisible) {
		animation_set->at(0)->Render(x, y);
		//RenderBoundingBox();
	}
}

void CTourchFlame::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y;
	right = x + 16;
	bottom = y + 30;
}
