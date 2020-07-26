#pragma once
#include "GameObject.h"
#include "HitEffect.h"
#include "FireBombEffect.h"

#define KNIGHT_WALKING_SPEED	0.02f 
#define KNIGHT_BOX_WIDTH	16
#define KNIGHT_BOX_HEIGHT	31

#define KNIGHT_ANI_WALK_LEFT	0
#define KNIGHT_ANI_WALK_RIGHT	1

#define KNINGHT_STATE_WALKING	100

class CKnight : public CGameObject
{
	bool isVisible = false;
	CHitEffect *hitEffect;
	CFireBombEffect* fireBombEffect;
	int limit_distance_x;
	float distance_gone = 0;
	float start_x;
	float start_y;
	int hp = 100;
public:
	CKnight(float x, float y, int limit_distance_x );
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
	virtual void Render();
	void SetState(int state);
	void SetVisible(bool value) { isVisible = value; }
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void IsHitted();
	void DecreaseHP(int value) { this->hp = hp - value; };
};