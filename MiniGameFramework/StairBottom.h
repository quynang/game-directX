#pragma once
#include "GameObject.h"

#define STAIR_BOTTOM_BOX_WIDTH	15
#define STAIR_BOTTOM_BOX_HEIGHT	4
#define STAIR_DIRECTION_LEFT	1
#define STAIR_DIRECTION_RIGHT	-1

class CStairBottom : public CGameObject
{
private:

	virtual void GetBoundingBox(float &left, float& top, float &right, float &bottom);
	int direction;
	
public:
	CStairBottom(int stair_direction);
	int GetDirection() { return direction; }
	D3DXVECTOR2 getPosition() { return D3DXVECTOR2(this->x, this->y); };
	void Render();
};