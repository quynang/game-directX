#pragma once
#include "GameObject.h"

#define WHIP_LV1	0
#define WHIP_LV2	1
#define WHIP_LV3	2
#define WHIP_STATE_SETUP_1	100
#define WHIP_STATE_SETUP_2	200
#define WHIP_STATE_CRACK	300

#define WHIP_LV1_ANI_SETUP_1_LEFT	0
#define WHIP_LV1_ANI_SETUP_2_LEFT	2
#define WHIP_LV1_ANI_CRACK_LEFT	4

#define WHIP_LV1_ANI_SETUP_1_RIGHT	1
#define WHIP_LV1_ANI_SETUP_2_RIGHT	3
#define WHIP_LV1_ANI_CRACK_RIGHT	5


#define WHIP_LV2_ANI_SETUP_1_LEFT	6
#define WHIP_LV2_ANI_SETUP_2_LEFT	8
#define WHIP_LV2_ANI_CRACK_LEFT	10

#define WHIP_LV2_ANI_SETUP_1_RIGHT	7
#define WHIP_LV2_ANI_SETUP_2_RIGHT	9
#define WHIP_LV2_ANI_CRACK_RIGHT	11

#define WHIP_LV3_ANI_SETUP_1_LEFT	12
#define WHIP_LV3_ANI_SETUP_2_LEFT	14
#define WHIP_LV3_ANI_CRACK_LEFT	16

#define WHIP_LV3_ANI_SETUP_1_RIGHT	13
#define WHIP_LV3_ANI_SETUP_2_RIGHT	15
#define WHIP_LV3_ANI_CRACK_RIGHT	17

#define WHIP_LV1_BOX_WIDTH	24
#define WHIP_LV1_BOX_HEIGHT	8

#define WHIP_LV2_BOX_WIDTH	24
#define WHIP_LV2_BOX_HEIGHT	6

#define WHIP_LV3_BOX_WIDTH	40
#define WHIP_LV3_BOX_HEIGHT	6


class CWhip : public CGameObject
{
	bool isVisible = false;
	int level = WHIP_LV2;
	int aniSetup1ByCurrentLevel() {
		switch (level) {
		case WHIP_LV1:
			if (nx > 0) return WHIP_LV1_ANI_SETUP_1_RIGHT;
			else return WHIP_LV1_ANI_SETUP_1_LEFT;
		case WHIP_LV2:
			if (nx > 0) return WHIP_LV2_ANI_SETUP_1_RIGHT;
			else return WHIP_LV2_ANI_SETUP_1_LEFT;
		case WHIP_LV3:
			if (nx > 0) return WHIP_LV3_ANI_SETUP_1_RIGHT;
			else return WHIP_LV3_ANI_SETUP_1_RIGHT;
		};
	};

	int aniSetup2ByCurrentLevel()
	{
		switch (level) {
		case WHIP_LV1:
			if (nx > 0) return WHIP_LV1_ANI_SETUP_2_RIGHT;
			else return WHIP_LV1_ANI_SETUP_2_LEFT;
		case WHIP_LV2:
			if (nx > 0) return WHIP_LV1_ANI_SETUP_2_RIGHT;
			else return WHIP_LV2_ANI_SETUP_2_LEFT;
		case WHIP_LV3:
			if (nx > 0) return WHIP_LV3_ANI_SETUP_2_RIGHT;
			else return WHIP_LV3_ANI_SETUP_2_LEFT;
		};
	};


	int aniCrackByCurrentLevel() {
		switch(level) {
		case WHIP_LV1:
			if (nx > 0) return WHIP_LV1_ANI_CRACK_RIGHT;
			else return WHIP_LV1_ANI_CRACK_LEFT;
		case WHIP_LV2:
			if (nx > 0) return WHIP_LV2_ANI_CRACK_RIGHT;
			else return WHIP_LV2_ANI_CRACK_LEFT;
		case WHIP_LV3:
			if (nx > 0) return WHIP_LV3_ANI_CRACK_RIGHT;
			else return WHIP_LV3_ANI_CRACK_LEFT;
		};
	};

public:
	CWhip(float x, float y);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);

	void SetDirection(int nx) { this->nx = nx; };

	void Render();

	void GetBoundingBox(float& left, float& top, float& right, float& bottom);

	void ResetLevel() { level = WHIP_LV1; }
	void UpgradeLevel();

	void SetState(int state);
};