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

CSimon::CSimon(float x, float y) : CGameObject()
{
	//level = MARIO_LEVEL_BIG;
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

		//
		// data section
		//
		switch (section)
		{
			case PLAYER_SECTION_TEXTURES: CResourceManager::GetInstance()->_ParseSection_TEXTURES(line); break;
			case PLAYER_SECTION_SPRITES: CResourceManager::GetInstance()->_ParseSection_SPRITES(line); break;
			case PLAYER_SECTION_ANIMATIONS: CResourceManager::GetInstance()->_ParseSection_ANIMATIONS(line); break;
			case PLAYER_SECTION_ANIMATION_SETS: CResourceManager::GetInstance()->_ParseSection_ANIMATION_SETS(line); break;
		}
	}

	f.close();


	DebugOut(L"[INFO] Done loading scene resources %s\n", filePath);

}



void CSimon::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

	CGameObject::Update(dt);
	x += dx;
	y += dy;

	vy += SIMON_GRAVITY * dt;
	if (y > 130) y = 130;
	//TODO: Xử lý va chạm tại đây
}

void CSimon::Render()
{
	int ani = -1;
	int alpha = 255;
	switch (state) {
	case SIMON_STATE_WALKING_RIGHT:
		ani = SIMON_ANI_WALK_RIGHT;
		break;
	case SIMON_STATE_WALKING_LEFT:
		ani = SIMON_ANI_WALK_LEFT;
		break;
	case SIMON_STATE_JUMP:
		if (nx > 0) ani = SIMON_ANI_JUMP_RIGHT;
		else ani = SIMON_ANI_JUMP_LEFT;
		break;
	default:
		if (nx > 0) ani = SIMON_ANI_IDLE_RIGHT;
		else ani = SIMON_ANI_IDLE_LEFT;
	}

	animation_set->at(ani)->Render(x, y, alpha);

	RenderBoundingBox();
}

void CSimon::SetState(int state)
{
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
		vy = - SIMON_JUMP_SPEED_Y;
	}
}

void CSimon::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
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

