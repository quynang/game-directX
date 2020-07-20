#include "StairBottom.h"
CStairBottom::CStairBottom(float x, float y, int stair_diretion) {
	this->direction = stair_diretion;
	this->x = x;
	this->y = y;
}

void CStairBottom::Render() {
	RenderBoundingBox();
}

void CStairBottom::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{

	left = x;
	top = y;
	right = x + STAIR_BOTTOM_BOX_WIDTH;
	bottom = y + STAIR_BOTTOM_BOX_HEIGHT;

}
