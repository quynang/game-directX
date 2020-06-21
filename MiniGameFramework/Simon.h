#pragma once
#include "GameObject.h"

#define SIMON_WALKING_SPEED		0.07f 
#define SIMON_JUMP_SPEED_Y		0.3f
#define SIMON_GRAVITY			0.002f

#define SIMON_STATE_IDLE			0
#define SIMON_STATE_WALKING_RIGHT	100
#define SIMON_STATE_WALKING_LEFT	200
#define SIMON_STATE_JUMP			300
#define SIMON_STATE_STANDING_HITTING	400

#define SIMON_ANI_IDLE_RIGHT	0
#define SIMON_ANI_IDLE_LEFT		1
#define SIMON_ANI_JUMP_RIGHT	2
#define SIMON_ANI_JUMP_LEFT		3
#define SIMON_ANI_WALK_RIGHT	4
#define SIMON_ANI_WALK_LEFT		5
#define SIMON_ANI_STANDING_HITTING_LEFT 6
#define SIMON_ANI_STANDING_HITTING_RIGHT 7


class CSimon : public CGameObject
{
	int level;
	int untouchable;
	DWORD untouchable_start;
	float start_x;			// initial position of Mario at scene
	float start_y;
	bool isHitting = false;
public: 
	CSimon(float x = 0.0f, float y = 0.0f);
	void Load(LPCWSTR filePath);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
	virtual void Render();
	void SetState(int state);
	void SetLevel(int l) { level = l; }
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount(); }
	void Reset();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};