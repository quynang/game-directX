#pragma once
#include "GameObject.h"

#define ITEM_ANI_SETS	41
#define TYPE_HEART	1
#define TYPE_WHEAPON	2
#define TYPE_WHITE_BAG	3
#define TYPE_PURPLE_BAG	4
#define TYPE_LARGE_HEART	5
#define TYPE_UNKNOWN	-1

#define WHEAPON_BOX_WIDTH	16
#define WHEAPON_BOX_HEIGHT	16
#define ITEM_ANI_SET	4

#define HEART_BOX_WIDTH	8
#define HEART_BOX_HEIGHT	8

#define LARGE_HEART_BOX_WIDTH	12
#define LARGE_HEART_BOX_HEIGHT	10

#define BAG_BOX_WIDTH	15
#define BAG_BOX_HEIGHT	15

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

class CLargeHeart : public CItem
{
public:
	CLargeHeart(float x, float y);
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

class CWhiteBag : public CItem
{
public:
	CWhiteBag(float x, float y);
	void GetBoundingBox(float &left, float& top, float &right, float &bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	void Render();
};

class CPurpleBag : public CItem
{
public:
	CPurpleBag(float x, float y);
	void GetBoundingBox(float &left, float& top, float &right, float &bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	void Render();
};

//TODO: Implement CBag class.