#pragma once
#include "GameObject.h"
#include "Whip.h"
#define SIMON_WALKING_SPEED		0.07f 
#define SIMON_JUMP_SPEED_Y		0.35f
#define SIMON_GRAVITY			0.0018f
#define SIMON_JUMP_DEFLECT_SPEED 0.001f

#define SIMON_STATE_IDLE			0
#define SIMON_STATE_WALKING_RIGHT	100
#define SIMON_STATE_WALKING_LEFT	200
#define SIMON_STATE_JUMP			300
#define SIMON_STATE_STANDING_HITTING	400
#define SIMON_STATE_CLIMBING_UP	500
#define SIMON_STATE_CLIMBING_DOWN	600
#define SIMON_STATE_IDLE_ON_STAIR	700
#define SIMON_STATE_SITTING_AND_HITTING	800
#define SIMON_STATE_DUCKING	900
#define SIMON_STATE_HITTING_ON_STAIR	1000
#define SIMON_STATE_FREEZE	1100
#define SIMON_STATE_ON_MOVING_BRICK	1200
#define SIMON_STATE_DIE	1300
#define SIMON_STATE_USE_SUBWEAPON	1400

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
#define SIMON_ANI_ASCENDING_STAIR_RIGHT_AND_HITTING	22
#define SIMON_ANI_DESCENDING_STAIR_RIGHT_AND_HITTING	23
#define SIMON_ANI_SITTING_AND_HITTING_LEFT	24
#define SIMON_ANI_SITTING_AND_HITTING_RIGHT	25

#define SIMON_HAND_OFFSET_X	4
#define SIMON_HAND_OFFSET_Y 6


#define SIMON_FREEZE_TIME	1000
#define SIMON_JUMPING_TIME	400
#define SIMON_UNTOUCHABLE_TIME	5000

#define SIMON_BOX_WIDTH	16
#define SIMON_BOX_HEIGHT	30

class CSimon : public CGameObject
{
	int level;
	int untouchable;
	int hp = 1600;
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
	bool isUseSubWeapon = false;
	bool canJump = true;
	int nx_stair = 1;
	DWORD start_jump;
	CWhip* whip;
	DWORD freezeTimer = 0;
	bool isOnMovingBrick = false;

	void UseWhip(int currentFrame);
	void UseSubWeapon();

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
	bool checkIsDucking() { return isDucking; }
	bool checkCanJump() { return canJump; }
	bool checkIsJumping() { return isJumping; }
	bool checkIsHitting() { return isHitting; }
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount(); }
	void Reset();
	int getHP() { return hp; }
	void decreaseHP(int _hp) { hp -= _hp; }
	void StartJump() { start_jump = GetTickCount(); }
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void StartFreezeState();
	void useSimonBackupWithInfoNeeded(
		int whipLevel,
		bool isClimbing,
		bool canClimbUp,
		bool canClimbDown,
		int state,
		int hp
	);

	void getSimonBackupInfoNeeded(
		int& whipLevel,
		bool& isClimbing,
		bool& canClimbUp,
		bool& canClimbDown,
		int& state,
		int& hp
	)
	{
		whipLevel = this->whip->getCurrentLevel();
		isClimbing = this->isClimbing;
		canClimbUp = this->canClimbUp;
		canClimbDown = this->canClimbDown;
		state = this->state;
		hp = this->hp;
	};
};