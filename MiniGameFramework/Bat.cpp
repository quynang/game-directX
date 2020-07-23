#include "Bat.h"
#include "Game.h"
#include "PlayScence.h"
#include <cmath>
#include <iostream>
#define PI 3.141592
CBat::CBat(float x, float y) : CGameObject() {
	isVisible = true;
	hitEffect = new CHitEffect();
	fireBombEffect = new CFireBombEffect();
	SetState(BAT_STATE_FLYING);
	this->x = x;
	this->y = y;
}

void CBat::Render()
{

	if (isVisible) {
		int ani = -1;
		switch (state) {
			case BAT_STATE_SLEEPING:
				ani = BAT_ANI_SLEEPING;
				break;
			case BAT_STATE_FLYING:
				if (nx > 0) ani = BAT_ANI_FLY_RIGHT;
				else ani = BAT_ANI_FLY_LEFT;
				timer = GetTickCount();
				break;
			default: 
				DebugOut(L"[ERR] Unknow ani type of Bat Object");
		}

		animation_set->at(ani)->Render(x, y);
		RenderBoundingBox();
	}

	hitEffect->Render();
	fireBombEffect->Render();
}

void CBat::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects) {
	CGameObject::Update(dt);
	x += dx;
	y += dy;
	int A = 10;
	float _cam_x, _cam_y;
	CGame* game = CGame::GetInstance();
	game->GetCamPos(_cam_x, _cam_y);
	if (this->x >= _cam_x + game->GetScreenWidth()) {
		isVisible = false;
	}

	//DebugOut(L"[INFOR] Bat isvisible: %d \n", isVisible);
}

void CBat::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	if (isVisible) {
		left = x;
		top = y;
		right = x + BAT_BOX_WIDTH;
		bottom = y + BAT_BOX_HEIGHT;
	}

	

	
}

void CBat::SetState(int state) {
	CGameObject::SetState(state);
	switch (state) {
	case BAT_STATE_SLEEPING:
		vx = 0;
		vy = 0;
		break;
	case BAT_STATE_FLYING:
		vx = BAT_FLY_SPEED;
		break;

	}

}
void CBat::IsHitted() {
	hitEffect->SetPosition(x + 5, y + 5);
	hitEffect->setIsVisible(true);
	if (hp <= 0) {
		fireBombEffect->SetPosition(x + 5, y + 5);
		fireBombEffect->setIsVisible(true);
		isVisible = false;
	}
}