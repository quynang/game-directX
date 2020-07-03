#pragma once
#include "GameObject.h"

#define WEAPON_LV1	0
#define WEAPON_LV2	1
#define WEAPON_LV3	2
#define WEAPON_STATE_SETUP_1	100
#define WEAPON_STATE_SETUP_2	200
#define WEAPON_STATE_CRACK	300

#define WEAPON_LV1_ANI_SETUP_1_LEFT	0
#define WEAPON_LV1_ANI_SETUP_2_LEFT	2
#define WEAPON_LV1_ANI_CRACK_LEFT	4

#define WEAPON_LV1_ANI_SETUP_1_RIGHT	1
#define WEAPON_LV1_ANI_SETUP_2_RIGHT	3
#define WEAPON_LV1_ANI_CRACK_RIGHT	5


#define WEAPON_LV2_ANI_SETUP_1_LEFT	6
#define WEAPON_LV2_ANI_SETUP_2_LEFT	8
#define WEAPON_LV2_ANI_CRACK_LEFT	10

#define WEAPON_LV2_ANI_SETUP_1_RIGHT	7
#define WEAPON_LV2_ANI_SETUP_2_RIGHT	9
#define WEAPON_LV2_ANI_CRACK_RIGHT	11

#define WEAPON_LV3_ANI_SETUP_1_LEFT	12
#define WEAPON_LV3_ANI_SETUP_2_LEFT	14
#define WEAPON_LV3_ANI_CRACK_LEFT	16

#define WEAPON_LV3_ANI_SETUP_1_RIGHT	13
#define WEAPON_LV3_ANI_SETUP_2_RIGHT	15
#define WEAPON_LV3_ANI_CRACK_RIGHT	17

#define WHIP_LV1_BOX_WIDTH	24
#define WHIP_LV1_BOX_HEIGHT	8

#define WHIP_LV2_BOX_WIDTH	24
#define WHIP_LV2_BOX_HEIGHT	6

#define WHIP_LV3_BOX_WIDTH	40
#define WHIP_LV3_BOX_HEIGHT	6


class CWhip : public CGameObject
{
	bool isVisible = false;
	int level = WEAPON_LV2;
	int aniSetup1ByCurrentLevel() {
		switch (level) {
		case WEAPON_LV1:
			if (nx > 0) return WEAPON_LV1_ANI_SETUP_1_RIGHT;
			else return WEAPON_LV1_ANI_SETUP_1_LEFT;
		case WEAPON_LV2:
			if (nx > 0) return WEAPON_LV2_ANI_SETUP_1_RIGHT;
			else return WEAPON_LV2_ANI_SETUP_1_LEFT;
		case WEAPON_LV3:
			if (nx > 0) return WEAPON_LV3_ANI_SETUP_1_RIGHT;
			else return WEAPON_LV3_ANI_SETUP_1_RIGHT;
		};
	};

	int aniSetup2ByCurrentLevel()
	{
		switch (level) {
		case WEAPON_LV1:
			if (nx > 0) return WEAPON_LV1_ANI_SETUP_2_RIGHT;
			else return WEAPON_LV1_ANI_SETUP_2_LEFT;
		case WEAPON_LV2:
			if (nx > 0) return WEAPON_LV1_ANI_SETUP_2_RIGHT;
			else return WEAPON_LV2_ANI_SETUP_2_LEFT;
		case WEAPON_LV3:
			if (nx > 0) return WEAPON_LV3_ANI_SETUP_2_RIGHT;
			else return WEAPON_LV3_ANI_SETUP_2_LEFT;
		};
	};


	int aniCrackByCurrentLevel() {
		switch(level) {
		case WEAPON_LV1:
			if (nx > 0) return WEAPON_LV1_ANI_CRACK_RIGHT;
			else return WEAPON_LV1_ANI_CRACK_LEFT;
		case WEAPON_LV2:
			if (nx > 0) return WEAPON_LV2_ANI_CRACK_RIGHT;
			else return WEAPON_LV2_ANI_CRACK_LEFT;
		case WEAPON_LV3:
			if (nx > 0) return WEAPON_LV3_ANI_CRACK_RIGHT;
			else return WEAPON_LV3_ANI_CRACK_LEFT;
		};
	};

public:
	CWhip(float x, float y);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);

	void SetDirection(int nx) { this->nx = nx; };

	void Render();

	void GetBoundingBox(float& left, float& top, float& right, float& bottom);

	void ResetLevel() { level = WEAPON_LV1; }
	void UpgradeLevel();

	void SetState(int state);
};