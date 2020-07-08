#include "StairBottom.h"
CStairBottom::CStairBottom(int stair_diretion) {
	this->direction = stair_diretion;
}

void CStairBottom::Render() {

}

void CStairBottom::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{

	left = x;
	top = y;
	right = x + STAIR_BOTTOM_BOX_WIDTH;
	bottom = y + STAIR_BOTTOM_BOX_HEIGHT;

}
