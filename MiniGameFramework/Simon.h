#pragma once
#include "GameObject.h"
#include "Whip.h"
#define SIMON_WALKING_SPEED		0.07f 
#define SIMON_JUMP_SPEED_Y		0.35f
#define SIMON_GRAVITY			0.0018f

#define SIMON_STATE_IDLE			0
#define SIMON_STATE_WALKING_RIGHT	100
#define SIMON_STATE_WALKING_LEFT	200
#define SIMON_STATE_JUMP			300
#define SIMON_STATE_STANDING_HITTING	400
#define SIMON_STATE_CLIMBING_UP	500
#define SIMON_STATE_CLIMBING_DOWN	600
#define SIMON_STATE_IDLE_ON_STAIR_UP	700
#define SIMON_STATE_IDLE_ON_STAIR_DOWN	800
#define SIMON_STATE_DUCKING	900
#define SIMON_STATE_HITTING_ON_STAIR	1000
#define SIMON_STATE_FREEZE	1100

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
#define SIMON_ANI_CLIMBING_UP_LEFT	10
#define SIMON_ANI_CLIMBING_UP_RIGHT	11
#define SIMON_ANI_CLIMBING_DOWN_LEFT	12
#define SIMON_ANI_CLIMBING_DOWN_RIGHT	13
#define SIMON_ANI_IDLE_ON_STAIR_UP_LEFT	14
#define SIMON_ANI_IDLE_ON_STAIR_UP_RIGHT	15
#define SIMON_ANI_IDLE_ON_STAIR_DOWN_LEFT	16
#define SIMON_ANI_IDLE_ON_STAIR_DOWN_RIGHT	17
#define SIMON_ANI_DUCKING_RIGHT	18
#define SIMON_ANI_DUCKING_LEFT	19
#define SIMON_ANI_ASCENDING_STAIR_LEFT_AND_HITTING	20
#define SIMON_ANI_DESCENDING_STAIR_LEFT_AND_HITTING	21
#define SIMON_ANI_ASCENDING_RIGHT_AND_HITTING	22
#define SIMON_ANI_DESCENDING_RIGHT_AND_HITTIN	23


#define SIMON_FREEZE_TIME	1000

#define SIMON_BOX_WIDTH	16
#define SIMON_BOX_HEIGHT	30

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
	bool isClimbing = false;
	bool canClimbDown = false;
	bool canClimbUp = false;
	bool isDucking = false;
	int nx_stair = 1;
	CWhip* whip;
	DWORD freezeTimer = 0;
	D3DXVECTOR2 handPosition;

	void UseWhip(int currentFrame);

public: 
	CSimon(float x = 0.0f, float y = 0.0f);
	void Load(LPCWSTR filePath);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
	virtual void Render();
	void SetState(int state);
	void SetLevel(int l) { level = l; }
	bool checkCanClimbUp() { return canClimbUp;  }
	bool checkCanClimbDown() { return canClimbDown;  }
	bool checkIsClimbing() { return isClimbing;  }
	void setIsClimbing(bool value) { isClimbing = value; }
	void setIsDucking(bool value) { isDucking = value; }
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount(); }
	void Reset();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void StartFreezeState();
};