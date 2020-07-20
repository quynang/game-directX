#pragma once
#include "GameObject.h"
#include "HitEffect.h"
#include "FireBombEffect.h"
#include "Item.h"

#define CANDLE_STATE_DESTROY 100
#define CANDLE_STATE_NORMAL	200

#define CANDLE_BOX_WIDTH	8
#define CANDLE_BOX_HEIGHT	14
class CCandle : public CGameObject
{
	bool isVisible = false;
	virtual void GetBoundingBox(float &left, float& top, float &right, float &bottom);
	virtual void Render();
	CHitEffect *hitEffect;
	CFireBombEffect* fireBombEffect;
public:
	CCandle(float x, float y);
	void SetVisible(bool value);
	void SetState(int state);
};