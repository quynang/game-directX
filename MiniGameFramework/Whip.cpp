#include <algorithm>
#include <assert.h>
#include "Utils.h"
#include <iostream>
#include <fstream>
#include "Whip.h"
#include "Game.h"

CWhip::CWhip(float x, float y) : CGameObject()
{
	SetState(WEAPON_STATE_SETUP_1);
	level = WEAPON_LV1;
	this->x = x;
	this->y = y;
}

void CWhip::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
}


void CWhip::Render()
{
	int ani = -1;
	int alpha = 255;


	switch (state) {
	case WEAPON_STATE_SETUP_1:
		ani = aniSetup1ByCurrentLevel();
		break;
	case WEAPON_STATE_SETUP_2:
		ani = aniSetup2ByCurrentLevel();
		break;
	case WEAPON_STATE_CRACK:
		ani = aniCrackByCurrentLevel();
		break;
	}

	DebugOut(L"[INFO] Whip STATE: %d \n", state);


	DebugOut(L"[INFO] Whip ani id: %d \n", ani);

	animation_set->at(ani)->Render(x, y, alpha);

}


void CWhip::SetState(int state)
{
	CGameObject::SetState(state);
}

void CWhip::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
}
