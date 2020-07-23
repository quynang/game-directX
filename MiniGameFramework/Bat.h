#pragma once
#include "GameObject.h"
#include "HitEffect.h"
#include "FireBombEffect.h"

#define BAT_FLY_SPEED	0.02f 
#define BAT_BOX_WIDTH	16
#define BAT_BOX_HEIGHT	16

#define BAT_ANI_SLEEPING	0
#define BAT_ANI_FLY_LEFT	1
#define BAT_ANI_FLY_RIGHT	2

#define BAT_STATE_SLEEPING	100
#define BAT_STATE_FLYING	200

class CBat : public CGameObject
{
	bool isVisible = false;
	CHitEffect *hitEffect;
	CFireBombEffect* fireBombEffect;
	int hp = 50;
	DWORD timer = 0;
	float start_x;
	float start_y;
public:
	CBat(float x, float y );
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
	virtual void Render();
	void SetState(int state);
	void SetVisible(bool value) { isVisible = value; }
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void IsHitted();
	void DecreaseHP(int value) { this->hp = hp - value; };
};