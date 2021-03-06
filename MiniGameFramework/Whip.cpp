#include <algorithm>
#include <assert.h>
#include "Utils.h"
#include <iostream>
#include <fstream>
#include "Whip.h"
#include "Game.h"
#include "TourchFlame.h"
#include "Candle.h"
#include "Knight.h"

CWhip::CWhip(float x, float y) : CGameObject()
{
	SetState(WHIP_STATE_SETUP_1);
	level = WHIP_LV1;
	this->x = x;
	this->y = y;
	this->vx = 0; 
	this->vy = 0;

}

void CWhip::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	//CGameObject::Update(dt);
	
	vector<LPGAMEOBJECT> collidingObjects;
	if (state == WHIP_STATE_CRACK) {

		this->CheckColliding(coObjects, collidingObjects);
		for (UINT i = 0; i < collidingObjects.size(); i++) {
			if (dynamic_cast<CTourchFlame*>(collidingObjects.at(i))) {
				CTourchFlame *tourchFlame = dynamic_cast<CTourchFlame *>(collidingObjects.at(i));
				tourchFlame->SetVisible(false);
				tourchFlame->SetState(TOURCH_FLAME_STATE_DESTROY);
				
				DebugOut(L"[INFO] Whip is colliding with Tourch \n");
	
			}

			if (dynamic_cast<CCandle*>(collidingObjects.at(i))) {
				CCandle *candle = dynamic_cast<CCandle *>(collidingObjects.at(i));
				candle->SetState(CANDLE_STATE_DESTROY);
				DebugOut(L"[INFO] Whip is colliding with Candle \n");
	
			}

			if (dynamic_cast<CKnight*>(collidingObjects.at(i))) {
				CKnight *knight = dynamic_cast<CKnight *>(collidingObjects.at(i));
				knight->DecreaseHP(50);
				knight->IsHitted();
				
			}
		}
		state = WHIP_STATE_UNUSED;
	}

	

}


void CWhip::Render()
{
	int ani = -1;
	int alpha = 255;

	switch (state) {
	case WHIP_STATE_SETUP_1:
		ani = aniSetup1ByCurrentLevel();
		break;
	case WHIP_STATE_SETUP_2:
		ani = aniSetup2ByCurrentLevel();
		break;
	case WHIP_STATE_CRACK:
		ani = aniCrackByCurrentLevel();
		RenderBoundingBox();
		DebugOut(L"[ERR] Test colliding\n");
		break;
	}

	animation_set->at(ani)->Render(x, y, alpha);

}


void CWhip::SetState(int state)
{
	CGameObject::SetState(state);
}

void CWhip::UpgradeLevel() {
	if (level != WHIP_LV3)
		level += 1;
}


void CWhip::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == WHIP_STATE_CRACK) {
		left = x;
		top = y;
		right = x + GetBoxWidthCrackByCurrentLevel();
		bottom = top + 6;
	}
	
}

