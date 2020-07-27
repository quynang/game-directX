#include "SubWeapon.h"
#include "Utils.h"
#include "Game.h"
#include "Knight.h"
CSubWeapon::CSubWeapon() {

}


/*---------- BOOMERANG--------------*/
CBoomerang::CBoomerang(float x, float y, float limited_x) {
	CAnimationSets* animation_sets = CAnimationSets::GetInstance();
	SetAnimationSet(animation_sets->Get(ITEM_ANI_SETS));
	this->x = x;
	this->y = y;
	this->start_x = x;
	this->limited_x = limited_x;
	//DebugOut(L"[INFO] Created bomerang : \n");
}

void CBoomerang::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	CGameObject::Update(dt, coObjects);
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	
	//TODO: set isVisible = false when boomerang out of camera.

	x += dx * nx;

	if (abs(x - start_x) > limited_x)
		SetState(BOOMERANG_STATE_WAY_BACK);

	coEvents.clear();
	CalcPotentialCollisions(coObjects, coEvents);
	

		float min_tx, min_ty, nx = 0, ny;
		float rdx = 0;
		float rdy = 0;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (dynamic_cast<CKnight*>(e->obj)) {
				CKnight* knight = dynamic_cast<CKnight*>(e->obj);
				knight->DecreaseHP(100);
				knight->IsHitted();
			}
		}
	
}
void CBoomerang::Render() {
	if (isVisible) {
		animation_set->at(0)->Render(x, y);
	}
}

void CBoomerang::GetBoundingBox(float& left, float& top, float& right, float& bottom) {
	if (isVisible) {
		left = x;
		top = y;
		right = x + BOOMERANG_BOX_WIDTH;
		bottom = y + BOOMERANG_BOX_HEIGHT;
	}
}

void CBoomerang::SetState(int state) {
	CGameObject::SetState(state);
	switch (state)
	{
	case BOOMERANG_STATE_THROW_AWAY: 
		vx = BOOMERANG_SPEED_X;
		break;
	case BOOMERANG_STATE_WAY_BACK:
		vx = -BOOMERANG_SPEED_X;
	default:
		break;
	}
}