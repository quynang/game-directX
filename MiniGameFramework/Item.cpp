#include "Item.h"
#include "Utils.h"

//Factory pattern
CItem* CItem::Create(int type, float x, float y) {
	switch(type) {
		case TYPE_HEART: 
			return new CHeart(x, y);
			break;
		case TYPE_WHEAPON: 
			return new CWheapon(x, y);
			break;
		case TYPE_WHITE_BAG:
			return new CWhiteBag(x, y);
			break;
		case TYPE_PURPLE_BAG:
			return new CPurpleBag(x, y);
			break;
		case TYPE_LARGE_HEART:
			return new CLargeHeart(x, y);
			break;
		case TYPE_UNKNOWN:
			return NULL;
			break;
	}
}

CItem::CItem() {

}

/*---------- WHEAPON CLASS--------------*/
CWheapon::CWheapon(float x, float y) {
	CAnimationSets* animation_sets = CAnimationSets::GetInstance();
	SetAnimationSet(animation_sets->Get(ITEM_ANI_SETS));
	this->x = x; 
	this->y = y;
}

void CWheapon::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects) {
	CGameObject::Update(dt, coObjects);
	vy += 0.0004f*dt;
	
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	CalcPotentialCollisions(coObjects, coEvents);

	if (coEvents.size()==0)
	{
		x += dx; 
		y += dy;

	}
}
void CWheapon::Render() {
	if (this->isVisible) {
		animation_set->at(1)->Render(x, y);
		
	}
	//RenderBoundingBox();
}

void CWheapon::GetBoundingBox(float& left, float& top, float& right, float& bottom) {
	if (isVisible) {
		left = x;
		top = y;
		right = x + WHEAPON_BOX_WIDTH;
		bottom = y + WHEAPON_BOX_HEIGHT;
	}
}


/*---------- HEART CLASS--------------*/

CHeart::CHeart(float x, float y) {
	CAnimationSets* animation_sets = CAnimationSets::GetInstance();
	SetAnimationSet(animation_sets->Get(ITEM_ANI_SETS));
	this->x = x; 
	this->y = y;
}
void CHeart::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects) {
	CGameObject::Update(dt, coObjects);
	vy += 0.0002f*dt;
	
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	CalcPotentialCollisions(coObjects, coEvents);

	if (coEvents.size()==0)
	{
		x += dx; 
		y += dy;
	}
}

void CHeart::Render() {
	if (this->isVisible) {
		animation_set->at(0)->Render(x, y);
	}
}

void CHeart::GetBoundingBox(float& left, float& top, float& right, float& bottom) {
	if (isVisible) {
		left = x;
		top = y;
		right = x + HEART_BOX_WIDTH;
		bottom = y + HEART_BOX_HEIGHT;
	}
}

CLargeHeart::CLargeHeart(float x, float y) {
	CAnimationSets* animation_sets = CAnimationSets::GetInstance();
	SetAnimationSet(animation_sets->Get(ITEM_ANI_SETS));
	this->x = x; 
	this->y = y;
}
void CLargeHeart::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects) {
	CGameObject::Update(dt, coObjects);
	vy += 0.0004f*dt;
	
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	CalcPotentialCollisions(coObjects, coEvents);

	if (coEvents.size()==0)
	{
		x += dx; 
		y += dy;
	}
}

void CLargeHeart::Render() {
	if (this->isVisible) {
		animation_set->at(4)->Render(x, y);
	}
}

void CLargeHeart::GetBoundingBox(float& left, float& top, float& right, float& bottom) {
	if (isVisible) {
		left = x;
		top = y;
		right = x + LARGE_HEART_BOX_WIDTH;
		bottom = y + LARGE_HEART_BOX_HEIGHT;
	}
}



/*---------- WHITE BAG CLASS--------------*/

CWhiteBag::CWhiteBag(float x, float y) {
	CAnimationSets* animation_sets = CAnimationSets::GetInstance();
	SetAnimationSet(animation_sets->Get(ITEM_ANI_SETS));
	this->x = x; 
	this->y = y;
}
void CWhiteBag::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects) {
	CGameObject::Update(dt, coObjects);
	vy += 0.0002f*dt;
	
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	CalcPotentialCollisions(coObjects, coEvents);

	if (coEvents.size()==0)
	{
		x += dx; 
		y += dy;
	}
}

void CWhiteBag::Render() {
	if (this->isVisible) {
		animation_set->at(2)->Render(x, y);
	}
}

void CWhiteBag::GetBoundingBox(float& left, float& top, float& right, float& bottom) {
	if (isVisible) {
		left = x;
		top = y;
		right = x + BAG_BOX_WIDTH;
		bottom = y + BAG_BOX_HEIGHT;
	}
}

/*---------- WHITE BAG CLASS--------------*/

CPurpleBag::CPurpleBag(float x, float y) {
	CAnimationSets* animation_sets = CAnimationSets::GetInstance();
	SetAnimationSet(animation_sets->Get(ITEM_ANI_SETS));
	this->x = x; 
	this->y = y;
}
void CPurpleBag::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects) {
	CGameObject::Update(dt, coObjects);
	vy += 0.0002f*dt;
	
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	CalcPotentialCollisions(coObjects, coEvents);

	if (coEvents.size()==0)
	{
		x += dx; 
		y += dy;
	}
}

void CPurpleBag::Render() {
	if (this->isVisible) {
		animation_set->at(3)->Render(x, y);
	}
}

void CPurpleBag::GetBoundingBox(float& left, float& top, float& right, float& bottom) {
	if (isVisible) {
		left = x;
		top = y;
		right = x + BAG_BOX_WIDTH;
		bottom = y + BAG_BOX_HEIGHT;
	}
}