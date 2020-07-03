#pragma once
#include "GameObject.h"
#include "Whip.h"
#define SIMON_WALKING_SPEED		0.07f 
#define SIMON_JUMP_SPEED_Y		0.3f
#define SIMON_GRAVITY			0.002f

#define SIMON_STATE_IDLE			0
#define SIMON_STATE_WALKING_RIGHT	100
#define SIMON_STATE_WALKING_LEFT	200
#define SIMON_STATE_JUMP			300
#define SIMON_STATE_STANDING_HITTING	400
#define SIMON_STATE_FREEZE	500

#define SIMON_ANI_IDLE_RIGHT	0
#define SIMON_ANI_IDLE_LEFT		1
#define SIMON_ANI_JUMP_RIGHT	2
#define SIMON_ANI_JUMP_LEFT		3
#define SIMON_ANI_WALK_RIGHT	4
#define SIMON_ANI_WALK_LEFT		5
#define SIMON_ANI_STANDING_HITTING_LEFT 6
#define SIMON_ANI_STANDING_HITTING_RIGHT 7
#define SIMON_ANI_COLOR_LEFT	8
#define SIMON_ANI_COLOR_RIGHT	9

#define SIMON_FREEZE_TIME	1000


class CSimon : public CGameObject
{
	int level;
	int untouchable;
	DWORD untouchable_start;
	float start_x;
	float start_y;
	bool isHitting = false;
	bool isJumping = false;
	bool isFreeze = false;
	CWhip* whip;
	DWORD freezeTimer = 0;
	void UseWhip(int currentFrame);

public: 
	CSimon(float x = 0.0f, float y = 0.0f);
	void Load(LPCWSTR filePath);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
	virtual void Render();
	void SetState(int state);
	void SetLevel(int l) { level = l; }
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount(); }
	void Reset();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void StartFreezeState();
};