#pragma once
#include "GameObject.h"

#define HIT_EFFECT	0
#define FIRE_BOMB_EFFECT	1

class CHitEffect
{
	bool isVisible;
	float x, y ;
	DWORD timer;
public:
	CHitEffect();
	void SetPosition(float x, float y) { this->x = x; this->y = y; };
	void setIsVisible(bool value) { isVisible = value; };
	virtual void Render();
};