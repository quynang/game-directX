#pragma once
#include "GameObject.h"

#define BRICK_MOVING_SPEED	0.02f 
#define BRICK_MOVING_BOX_WIDTH	32
#define BRICK_MOVING_BOX_HEIGHT	8

class CBrickMoving : public CGameObject
{
	bool isVisible = false;
	int limit_distance_x;
	float distance_gone = 0;
	float start_x;
	float start_y;
public:
	CBrickMoving(float x, float y, int limit_distance_x );
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
	virtual void Render();
	void SetVisible(bool value) { isVisible = value; }
	float getMovingSpeed() { return this->vx; }
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};