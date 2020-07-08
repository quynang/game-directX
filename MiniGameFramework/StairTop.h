#pragma once
#include "GameObject.h"

#define STAIR_TOP_BOX_WIDTH	8
#define STAIR_TOP_BOX_HEIGHT	8

class CStairTop : public CGameObject
{
	virtual void GetBoundingBox(float &left, float& top, float &right, float &bottom);
public:
	CStairTop();
	void Render();
	D3DXVECTOR2 getPosition() { return D3DXVECTOR2(this->x, this->y); };
};