#pragma once
#include "GameObject.h"

#define TOURCH_ANI_1	0
#define TOURCH_ANI_2	1

class CTourchFlame : public CGameObject
{
	bool isVisible = false;
	virtual void GetBoundingBox(float &left, float& top, float &right, float &bottom);
	//virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render();
	
public:
	CTourchFlame();
	void SetVisible(bool type) { this->isVisible = type; };
};