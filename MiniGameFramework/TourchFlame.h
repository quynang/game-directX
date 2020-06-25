#pragma once
#include "GameObject.h"

#define TOURCH_ANI_1	0
#define TOURCH_ANI_2	1

class CTourchFlame : public CGameObject
{
	bool isVisible = false;
	


public:

	void Render();

	void GetBoundingBox(float& left, float& top, float& right, float& bottom);

};