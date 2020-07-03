#pragma once
#include "GameObject.h"

class CFireBombEffect
{
	bool isVisible;
	float x, y ;
	DWORD timer;
public:
	CFireBombEffect();
	void SetPosition(float x, float y) { this->x = x; this->y = y; };
	void setIsVisible(bool value) { isVisible = value; };
	virtual void Render();
};