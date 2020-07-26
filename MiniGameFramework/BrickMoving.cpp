#include "BrickMoving.h"
#include "Game.h"
#include "PlayScence.h"

CBrickMoving::CBrickMoving(float x, float y, int limit_distance_x) : CGameObject() {
	isVisible = true;
	this->limit_distance_x = limit_distance_x;
	start_x = x;
	start_y = y;
	this->x = x;
	this->y = y;
	vx = BRICK_MOVING_SPEED;
}
void CBrickMoving::Render()
{

	if (isVisible) {
		animation_set->at(0)->Render(x, y);
		RenderBoundingBox();
	}
}

void CBrickMoving::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects) {
	CGameObject::Update(dt);
	x += dx;
	if (x - start_x > limit_distance_x) {
		vx = -BRICK_MOVING_SPEED;
		nx = -1;
	}
	else if (x < start_x ) {
		vx = BRICK_MOVING_SPEED;
		nx = 1;
	}
}

void CBrickMoving::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	if (isVisible) {
		left = x;
		top = y;
		right = x + BRICK_MOVING_BOX_WIDTH;
		bottom = y + BRICK_MOVING_BOX_HEIGHT;
	}
	
}
