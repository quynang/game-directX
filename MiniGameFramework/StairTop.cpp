#include "StairTop.h"

void CStairTop::Render() {
	RenderBoundingBox();
}

void CStairTop::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{

	left = x;
	top = y;
	right = x + STAIR_TOP_BOX_WIDTH;
	bottom = y + STAIR_TOP_BOX_HEIGHT;

}
