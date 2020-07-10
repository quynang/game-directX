#include <algorithm>
#include <assert.h>
#include "Utils.h"
#include <iostream>
#include <fstream>
#include "Simon.h"
#include "Game.h"
#include "Textures.h"
#include "Sprites.h"
#include "ResourceManager.h"
#include "Portal.h"
#include "Item.h"
#include "TourchFlame.h"
#include "PlayScence.h"
#include"Brick.h"
#include "StairBottom.h"
#include "StairTop.h"

CSimon::CSimon(float x, float y) : CGameObject()
{
	untouchable = 0;
	SetState(SIMON_STATE_IDLE);

	start_x = x;
	start_y = y;
	this->x = x;
	this->y = y;
}

#define PLAYER_SECTION_UNKNOWN -1
#define PLAYER_SECTION_TEXTURES 2
#define PLAYER_SECTION_SPRITES 3
#define PLAYER_SECTION_ANIMATIONS 4
#define PLAYER_SECTION_ANIMATION_SETS	5
#define MAX_PLAYER_LINE 1024

void CSimon::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	whip->Update(dt, coObjects);
	CGameObject::Update(dt);
	if(!isClimbing)
		vy += SIMON_GRAVITY*dt;

	if (isFreeze && (GetTickCount() - freezeTimer > SIMON_FREEZE_TIME)) 
	{
		freezeTimer = 0;
		isFreeze = false;
		//SetState(SIMON_STATE_IDLE);
	}

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	vector<LPGAMEOBJECT> objectsColliding;
	this->CheckColliding(coObjects, objectsColliding);
	if (objectsColliding.size() == 0 && !isClimbing) {
		canClimbDown = false;
		canClimbUp = false;
	}	else {
		for (UINT i = 0; i < objectsColliding.size(); i++) {
			if (dynamic_cast<CStairBottom*>(objectsColliding.at(i))) {
				canClimbUp = true;
				CStairBottom* stairBottom = dynamic_cast<CStairBottom*>(objectsColliding.at(i));
				if (isClimbing && canClimbUp && !canClimbDown) { x = stairBottom->getPosition().x + 4;} 
				nx_stair = stairBottom->GetDirection();

				bool isReachedBottomOfStair = stairBottom->getPosition().y - this->y < 28;
				if (isClimbing && isReachedBottomOfStair && canClimbUp && canClimbDown) { y = stairBottom->getPosition().y - SIMON_BOX_HEIGHT ;  x = stairBottom->getPosition().x - 1; canClimbUp = false;  canClimbDown = false; isClimbing = false; }
			}

			if (dynamic_cast<CStairTop*>(objectsColliding.at(i))) {
				CStairTop* stairTop = dynamic_cast<CStairTop*>(objectsColliding.at(i));
				bool isReachedTopOfStair = stairTop->getPosition().y - this->y > 20;
				if (isClimbing && isReachedTopOfStair) { y = stairTop->getPosition().y - SIMON_BOX_HEIGHT + 10;  x = stairTop->getPosition().x + 1; canClimbUp = false; isClimbing = false;}
				canClimbDown = true;

			}
		}

	}

	//DebugOut(L"[INFO] Simon can climb down  : %d \n", canClimbDown);
	//DebugOut(L"[INFO] Simon can climb up  : %d \n", canClimbUp);

	coEvents.clear();

	CalcPotentialCollisions(coObjects, coEvents);

	if (coEvents.size()==0)
	{
		x += dx; 
		y += dy;

	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		float rdx = 0; 
		float rdy = 0;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		x += min_tx*dx + nx*0.4f;
		y += min_ty*dy + ny*0.4f;

		if (nx!=0) vx = 0;
		if (ny!=0) vy = 0;


		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			if (dynamic_cast<CWheapon*>(e->obj))
			{
				CWheapon* wheapon = dynamic_cast<CWheapon*>(e->obj);
				wheapon->SetVisible(false);
				whip->UpgradeLevel();
				SetState(SIMON_STATE_FREEZE);
				StartFreezeState();
			}

			if (dynamic_cast<CTourchFlame*>(e->obj)) {
				x += dx;
				if (e->ny < 0) {
					y += dy;
				}
			}

			if (dynamic_cast<CStairBottom*>(e->obj)) {
				CStairBottom* stairBottom = dynamic_cast<CStairBottom*>(e->obj);
				x += dx;
				if (e->ny < 0) {
					y += dy;
	
				}
			}

			if (dynamic_cast<CStairTop*>(e->obj)) {
				x += dx;
				if (e->ny < 0) {
					y += dy;
				}
			}
	
			if (dynamic_cast<CHeart*>(e->obj)) {
				CHeart* heart = dynamic_cast<CHeart*>(e->obj);
				heart->SetVisible(false);
				//((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->TurnOffGameUpdationByTimer(3000);
			}

			if (dynamic_cast<CBrick*>(e->obj)) {
				CBrick* brick = dynamic_cast<CBrick*>(e->obj);
				if (e->ny > 0 || isClimbing) {
					y += dy;
				}
				//((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->TurnOffGameUpdationByTimer(3000);
			}
		}
	}

	
}

void CSimon::Render()
{
	int ani = -1;
	int alpha = 255;

	switch (state) {
		case SIMON_STATE_JUMP:
			if (nx > 0) ani = SIMON_ANI_JUMP_RIGHT;
			else ani = SIMON_ANI_JUMP_LEFT;
			isJumping = true;
			break;
		case SIMON_STATE_WALKING_RIGHT:
			if(isJumping) ani = SIMON_ANI_JUMP_RIGHT;
			else ani = SIMON_ANI_WALK_RIGHT;
			break;
		case SIMON_STATE_WALKING_LEFT:
			if(isJumping) ani = SIMON_ANI_JUMP_LEFT;
			else ani = SIMON_ANI_WALK_LEFT;
			break;
		case SIMON_STATE_STANDING_HITTING:
			if (nx > 0) ani = SIMON_ANI_STANDING_HITTING_RIGHT;
			else ani = SIMON_ANI_STANDING_HITTING_LEFT;
			isHitting = true;
			break;
		case SIMON_STATE_FREEZE:
			if (nx > 0) ani = SIMON_ANI_COLOR_RIGHT;
			else ani = SIMON_ANI_COLOR_LEFT;
			break;
		case SIMON_STATE_CLIMBING_UP:
			if (nx_stair > 0) ani = SIMON_ANI_CLIMBING_UP_RIGHT;
			else ani = SIMON_ANI_CLIMBING_UP_LEFT;
			break;
		case SIMON_STATE_CLIMBING_DOWN:
			if (nx_stair > 0) ani = SIMON_ANI_CLIMBING_DOWN_LEFT;
			else ani = SIMON_ANI_CLIMBING_DOWN_RIGHT;
		 	break;
		case SIMON_STATE_IDLE_ON_STAIR_UP:
		 	if (nx_stair > 0) ani = SIMON_ANI_IDLE_ON_STAIR_UP_RIGHT;
		 	else ani = SIMON_ANI_IDLE_ON_STAIR_UP_LEFT;
		 	break;
		case SIMON_STATE_IDLE_ON_STAIR_DOWN:
		 	if (nx_stair < 0) ani = SIMON_ANI_IDLE_ON_STAIR_DOWN_RIGHT;
		 	else ani = SIMON_ANI_IDLE_ON_STAIR_DOWN_LEFT;
			break;
		default:
			if (nx > 0) ani = SIMON_ANI_IDLE_RIGHT;
			else ani = SIMON_ANI_IDLE_LEFT;
	};

	animation_set->at(ani)->Render(x, y, alpha);
	if(isHitting) UseWhip(animation_set->at(ani)->GetCurrentFrame());

	if (isHitting == true && animation_set->at(ani)->isLastFrame()) isHitting = false;
	
	
	if (vy > 0) isJumping = false;
	
	 if ((isHitting == false || isJumping == false) && !isClimbing) {
	 	SetState(SIMON_STATE_IDLE);
	 }

	RenderBoundingBox();
}

void CSimon::StartFreezeState() {
	isFreeze = true;
	freezeTimer = GetTickCount();
}

void CSimon::UseWhip(int currentFrame) {
	whip->SetDirection(nx);
	switch(currentFrame) {
		case 0:
			if(nx > 0) whip->SetPosition(this->x - 15, this->y + 6);
			else whip->SetPosition(this->x + 24, this->y + 6);
			whip->SetState(WHIP_STATE_SETUP_1);
			break;
		case 1:
			if (nx > 0) whip->SetPosition(this->x - 16, this->y + 6);
			else whip->SetPosition(this->x + 16, this->y + 5);
			whip->SetState(WHIP_STATE_SETUP_2);
			break;
		case 2:
			if (nx > 0) whip->SetPosition(this->x + 20, this->y + 6);
			else whip->SetPosition(this->x - 30, this->y + 6);
			whip->SetState(WHIP_STATE_CRACK);
			//whip->RenderBoundingBox();
			break;
	};

	whip->Render();
}


void CSimon::SetState(int state)
{
	if (!isHitting && !isJumping && !isFreeze) {
		CGameObject::SetState(state);

		switch (state)
		{
		case SIMON_STATE_WALKING_RIGHT:
			vx = SIMON_WALKING_SPEED;
			nx = 1;
			break;
		case SIMON_STATE_WALKING_LEFT:
			vx = -SIMON_WALKING_SPEED;
			nx = -1;
			break;
		case SIMON_STATE_IDLE:
			vx = 0;
			break;
		case SIMON_STATE_JUMP:
			vy = -SIMON_JUMP_SPEED_Y;
			break;
		case SIMON_STATE_STANDING_HITTING:
			vx = 0;
			break;
		case SIMON_STATE_CLIMBING_UP:
			vx = SIMON_WALKING_SPEED;
			vy = -0.07f;
			break;
		case SIMON_STATE_CLIMBING_DOWN:
			vx = -SIMON_WALKING_SPEED;
			vy = 0.07f;
			break;
		case SIMON_STATE_IDLE_ON_STAIR_UP:
			vx = 0;
			vy = 0;
		case SIMON_STATE_IDLE_ON_STAIR_DOWN:
			vx = 0;
			vy = 0;
			break;
		case SIMON_STATE_FREEZE:
			vx = 0;
			vy = 0;
			break;

		}
	}
}

void CSimon::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y;
	right = x + SIMON_BOX_WIDTH;
	bottom = y + SIMON_BOX_HEIGHT;
}


/*
	Reset Mario status to the beginning state of a scene
*/
void CSimon::Reset()
{
	SetState(SIMON_STATE_IDLE);
	SetPosition(start_x, start_y);
	SetSpeed(0, 0);
}


void CSimon::Load(LPCWSTR filePath) {
	DebugOut(L"[INFO] Start loading scene resources from : %s \n", filePath);

	ifstream f;
	f.open(filePath);

	// current resource section flag
	int section = PLAYER_SECTION_UNKNOWN;

	char str[MAX_PLAYER_LINE];
	while (f.getline(str, MAX_PLAYER_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	

		if (line == "[TEXTURES]") { section = PLAYER_SECTION_TEXTURES; continue; }
		if (line == "[SPRITES]") {
			section = PLAYER_SECTION_SPRITES; continue;
		}
		if (line == "[ANIMATIONS]") {
			section = PLAYER_SECTION_ANIMATIONS; continue;
		}
		if (line == "[ANIMATION_SETS]") {
			section = PLAYER_SECTION_ANIMATION_SETS; continue;
		}

		if (line[0] == '[') { section = PLAYER_SECTION_UNKNOWN; continue; }

		switch (section)
		{
			case PLAYER_SECTION_TEXTURES: CResourceManager::GetInstance()->_ParseSection_TEXTURES(line); break;
			case PLAYER_SECTION_SPRITES: CResourceManager::GetInstance()->_ParseSection_SPRITES(line); break;
			case PLAYER_SECTION_ANIMATIONS: CResourceManager::GetInstance()->_ParseSection_ANIMATIONS(line); break;
			case PLAYER_SECTION_ANIMATION_SETS: CResourceManager::GetInstance()->_ParseSection_ANIMATION_SETS(line); break;
		}
	}

	f.close();

	CAnimationSets * animation_sets = CAnimationSets::GetInstance();
	LPANIMATION_SET ani_set = animation_sets->Get(1);
	LPANIMATION_SET whip_ani_set = animation_sets->Get(21);
	this->SetAnimationSet(ani_set);
	whip = new CWhip(0, 0);
	whip->SetAnimationSet(whip_ani_set);
	//DebugOut(L"[INFO] whip animation sets %d\n", whip_ani_set->size());

	DebugOut(L"[INFO] Done loading scene resources %s\n", filePath);

}
