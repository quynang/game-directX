#include <algorithm>
#include <assert.h>
#include "Utils.h"
#include <iostream>
#include <fstream>
#include "Whip.h"
#include "Game.h"
#include "TourchFlame.h"

CWhip::CWhip(float x, float y) : CGameObject()
{
	SetState(WEAPON_STATE_SETUP_1);
	level = WEAPON_LV1;
	this->x = x;
	this->y = y;
	this->vx = 0; 
	this->vy = 0;

}

void CWhip::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
	vector<LPGAMEOBJECT> collidingObjects;
	if (state == WEAPON_STATE_CRACK) {
		this->CheckColliding(coObjects, collidingObjects);
		for (UINT i = 0; i < collidingObjects.size(); i++) {
			if (dynamic_cast<CTourchFlame*>(collidingObjects.at(i))) {
				CTourchFlame *goomba = dynamic_cast<CTourchFlame *>(collidingObjects.at(i));
				goomba->SetVisible(false);
			}
				
		}
	
		
	}

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

	animation_set->at(ani)->Render(x, y, alpha);

}


void CWhip::SetState(int state)
{
	CGameObject::SetState(state);
}


void CWhip::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + 24;
	bottom = y + 8;
}