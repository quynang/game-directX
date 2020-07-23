#include "Knight.h"
#include "Game.h"
#include "PlayScence.h"
#include "Item.h"
#include "Brick.h"
CKnight::CKnight(float x, float y, int limit_distance_x) : CGameObject() {
	isVisible = true;
	hitEffect = new CHitEffect();
	fireBombEffect = new CFireBombEffect();
	this->limit_distance_x = limit_distance_x;
	SetState(KNINGHT_STATE_WALKING);
	start_x = x;
	start_y = y;
	this->x = x;
	this->y = y;
}
void CKnight::Render()
{

	if (isVisible) {
		int ani = -1;
		switch (state) {
			case KNINGHT_STATE_WALKING:
				if (nx > 0) ani = KNIGHT_ANI_WALK_RIGHT;
				else ani = KNIGHT_ANI_WALK_LEFT;
				break;
			default: 
				DebugOut(L"[ERR] Unknow ani type of Knight");
		}

		animation_set->at(ani)->Render(x, y);
		RenderBoundingBox();
	}
	hitEffect->Render();
	fireBombEffect->Render();
}

void CKnight::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects) {
	CGameObject::Update(dt);
	x += dx;
	if (x - start_x > limit_distance_x) {
		vx = -KNIGHT_WALKING_SPEED;
		nx = -1;
	}
	else if (x < start_x ) {
		vx = KNIGHT_WALKING_SPEED;
		nx = 1;
	}
}

void CKnight::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	if (isVisible) {
		left = x;
		top = y;
		right = x + KNIGHT_BOX_WIDTH;
		bottom = y + KNIGHT_BOX_HEIGHT;
	}
	
}

void CKnight::SetState(int state) {
	CGameObject::SetState(state);
	switch (state) {
	case KNINGHT_STATE_WALKING:
		vx = KNIGHT_WALKING_SPEED;
		break;

	}

}
void CKnight::IsHitted() {
	hitEffect->SetPosition(x + 5, y + 5);
	hitEffect->setIsVisible(true);
	if (hp <= 0) {
		fireBombEffect->SetPosition(x + 5, y + 5);
		fireBombEffect->setIsVisible(true);
		isVisible = false;
	}
}