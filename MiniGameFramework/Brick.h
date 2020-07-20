#pragma once
#include "GameObject.h"

#define BRICK_BBOX_WIDTH  32
#define BRICK_BBOX_HEIGHT 32

class CBrick : public CGameObject
{
public:
	CBrick(float x, float y) { this->x = x; this->y = y; }
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
};