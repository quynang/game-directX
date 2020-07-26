#pragma once
#include "GameObject.h"
#include "HitEffect.h"
#include "FireBombEffect.h"
#include "Item.h"

#define TOURCH_ANI_1	0
#define TOURCH_ANI_2	1
#define TOURCH_FLAME_STATE_DESTROY 100
#define TOURCH_FLAME_STATE_NORMAL	200
#define TOURCH_FLAME_BOX_WIDTH	16
#define TOURCH_FLAME_BOX_HEIGHT	30
class CTourchFlame : public CGameObject
{
	bool isVisible = false;
	virtual void GetBoundingBox(float &left, float& top, float &right, float &bottom);
	//virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render();
	CHitEffect *hitEffect;
	CFireBombEffect* fireBombEffect;
public:
	CTourchFlame(float x, float y);
	void SetVisible(bool value);
	void SetState(int state);
};