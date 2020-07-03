#pragma once
#include "GameObject.h"

#define ITEM_ANI_SETS	41
#define TYPE_HEART	1
#define TYPE_WHEAPON	2
#define TYPE_UNKNOWN	-1

#define WHEAPON_BOX_WIDTH	16
#define WHEAPON_BOX_HEIGHT	16
#define ITEM_ANI_SET	4

#define HEART_BOX_WIDTH	8
#define HEART_BOX_HEIGHT	8

class CItem : public CGameObject
{
protected:
	bool isVisible = false;
	DWORD timer = 0; //TODO: Set visible time for each item.
public:
	CItem();
	void SetVisible(bool value) { this->isVisible = value; };
	static CItem* Create(int type, float x, float y);
};

class CHeart : public CItem
{
public:
	CHeart(float x, float y);
	void GetBoundingBox(float &left, float& top, float &right, float &bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	void Render();
};

class CWheapon : public CItem
{
public:
	CWheapon(float x, float y);
	void GetBoundingBox(float &left, float& top, float &right, float &bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	void Render();
};

//TODO: Implement CBag class.