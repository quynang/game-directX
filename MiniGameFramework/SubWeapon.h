#pragma once
#include "GameObject.h"

#define ITEM_ANI_SETS	50
#define TYPE_BOOMERANG	1
#define TYPE_DAGGER	2
#define TYPE_AXE	3
#define TYPE_UNKNOWN	-1

#define BOOMERANG_SPEED_X	0.12f
#define BOOMERANG_STATE_THROW_AWAY	100
#define BOOMERANG_STATE_WAY_BACK	200
#define BOOMERANG_BOX_WIDTH	15
#define BOOMERANG_BOX_HEIGHT	14


class CSubWeapon : public CGameObject
{
protected:
	bool isVisible = false;
	DWORD timer = 0; //TODO: Set visible time for each item.
public:
	CSubWeapon();
	void SetVisible(bool value) { this->isVisible = value; };
	void setDirection(int nx) { this->nx = nx; }
};

class CBoomerang : public CSubWeapon
{
	float start_x;
	float limited_x;
public:
	
	CBoomerang(float x, float y, float limited_x);
	void GetBoundingBox(float &left, float& top, float &right, float &bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	void Render();
	void SetState(int state);
};
