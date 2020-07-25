#include <iostream>
#include <fstream>
#include "Textures.h"
#include "Sprites.h"
#include "PlayScence.h"
#include "Utils.h"
#include "Portal.h"
#include "ResourceManager.h"
#include "GameStatusBoard.h"

using namespace std;

CPlayScene::CPlayScene(int id, LPCWSTR filePath) :
	CScene(id, filePath)
{
	key_handler = new CPlayScenceKeyHandler(this);
	gameStatusBoard = new CGameStatusBoard();
}

#define SCENE_SECTION_UNKNOWN -1
#define SCENE_SECTION_TEXTURES 2
#define SCENE_SECTION_SPRITES 3
#define SCENE_SECTION_ANIMATIONS 4
#define SCENE_SECTION_ANIMATION_SETS	5
#define SCENE_SECTION_OBJECTS	6
#define SCENE_SECTION_MAP	7
#define SCENE_SECTION_PLAYER	8

#define OBJECT_TYPE_PORTAL	50

#define MAX_SCENE_LINE 1024

void CPlayScene::_ParseSection_MAP(string line)
{
	LPCWSTR path = ToLPCWSTR(line);
	CMap::GetInstance()->Load(path);
	
}

void CPlayScene::_ParseSection_PLAYER(string line)
{
	CAnimationSets* animation_sets = CAnimationSets::GetInstance();
	CGameObject* obj = NULL;
	vector<string> tokens = split(line);

	if (tokens.size() < 3) return; // skip invalid lines - an object set must have at least id, x, y

	LPCWSTR path = ToLPCWSTR(tokens[0]);
	float x = atof(tokens[1].c_str());
	float y = atof(tokens[2].c_str());
	player = new CSimon(x, y);
	
	player->Load(path);
	int ani_set_id = atoi(tokens[3].c_str());
	objects.push_back(player);
	
}

void CPlayScene::Load()
{
	DebugOut(L"[INFO] Start loading scene resources from : %s \n", sceneFilePath);

	ifstream f;
	f.open(sceneFilePath);

	// current resource section flag
	int section = SCENE_SECTION_UNKNOWN;

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	

		if (line == "[MAP]") {
			section = SCENE_SECTION_MAP; continue;
		}
		if (line == "[PLAYER]") {
			section = SCENE_SECTION_PLAYER; continue;
		}
		if (line == "[TEXTURES]") { section = SCENE_SECTION_TEXTURES; continue; }
		if (line == "[SPRITES]") {
			section = SCENE_SECTION_SPRITES; continue;
		}
		if (line == "[ANIMATIONS]") {
			section = SCENE_SECTION_ANIMATIONS; continue;
		}
		if (line == "[ANIMATION_SETS]") {
			section = SCENE_SECTION_ANIMATION_SETS; continue;
		}
		if (line == "[OBJECTS]") {
			section = SCENE_SECTION_OBJECTS; continue;
		}
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }

		//
		// data section
		//
		switch (section)
		{
		case SCENE_SECTION_MAP: _ParseSection_MAP(line); break;
		case SCENE_SECTION_TEXTURES: CResourceManager::GetInstance()->_ParseSection_TEXTURES(line); break;
		case SCENE_SECTION_SPRITES: CResourceManager::GetInstance()->_ParseSection_SPRITES(line); break;
		case SCENE_SECTION_ANIMATIONS: CResourceManager::GetInstance()->_ParseSection_ANIMATIONS(line); break;
		case SCENE_SECTION_ANIMATION_SETS: CResourceManager::GetInstance()->_ParseSection_ANIMATION_SETS(line); break;
		case SCENE_SECTION_OBJECTS: CResourceManager::GetInstance()->_ParseSection_OBJECTS(line, objects); break;
		case SCENE_SECTION_PLAYER: _ParseSection_PLAYER(line); break;
		}
	}

	f.close();
	CTextures::GetInstance()->Add(-100, L"resources\\bbox.png", D3DCOLOR_XRGB(255, 255, 255));

	DebugOut(L"[INFO] Done loading scene resources %s\n", sceneFilePath);
}

void CPlayScene::Update(DWORD dt)
{
	if (offUpdation) {
		if (GetTickCount() - timerFlag > 3000) {
			offUpdation = false;
			timerFlag = 0;
		}
	}

	timeLimit;
	timeGone +=  dt;
	int timeRemain =  timeLimit - (int)timeGone * 0.001;
	gameStatusBoard->Update(timeRemain);


	if (!offUpdation) {
		float cx, cy;
		player->GetPosition(cx, cy);

		CGame* game = CGame::GetInstance();
		cx -= game->GetScreenWidth() / 2;
		cy -= game->GetScreenHeight() / 2;
		if (cx < 0) cx = 0;

		//TODO: Make it more readable. Perhaps create a method check is camera reached bounder map then handle cx. 
		if (cx > CMap::GetInstance()->getWidth() - game->GetScreenWidth()  ) cx = CMap::GetInstance()->getWidth() - game->GetScreenWidth();
		CGame::GetInstance()->SetCamPos(cx, 0.0f /*cy*/);
		vector<LPGAMEOBJECT> coObjects;
		for (size_t i = 0; i < objects.size() - 1; i++)
		{
			coObjects.push_back(objects[i]);
		}

	
		for (size_t i = 0; i < objects.size(); i++)
		{
			objects[i]->Update(dt, &coObjects);
		}
	}
}

void CPlayScene::TurnOffGameUpdationByTimer(DWORD timer) {
	offUpdation = true;
	timerFlag = GetTickCount();
}
void CPlayScene::Render()
{
	
	CMap::GetInstance()->Render();
	for (int i = 0; i < objects.size(); i++)
		objects[i]->Render();

	gameStatusBoard->Render();
}

void CPlayScene::AddObject(LPGAMEOBJECT obj)
{
	objects.insert(objects.begin(), obj);
}

/*
	Unload current scene
*/
void CPlayScene::Unload()
{
	for (int i = 0; i < objects.size(); i++)
		delete objects[i];

	objects.clear();
	player = NULL;

	DebugOut(L"[INFO] Scene %s unloaded! \n", sceneFilePath);
}

void CPlayScenceKeyHandler::OnKeyDown(int KeyCode)
{

	CSimon* simon = ((CPlayScene*)scence)->GetPlayer();
	switch (KeyCode)
	{
	case DIK_X:
		if(!simon->checkIsClimbing() && simon->checkCanJump())
			simon->SetState(SIMON_STATE_JUMP);
		break;
	case DIK_A:
		simon->Reset();
		break;
	case DIK_Z: 
		if (simon->checkIsClimbing()) simon->SetState(SIMON_STATE_HITTING_ON_STAIR);
		else if (simon->checkIsDucking()) simon->SetState(SIMON_STATE_SITTING_AND_HITTING);
		else simon->SetState(SIMON_STATE_STANDING_HITTING);
		break;
	case DIK_1: 
		CGame::GetInstance()->SwitchScene(1);
		break;
	case DIK_2: 
		CGame::GetInstance()->SwitchScene(2);
		break;
	case DIK_3: 
		CGame::GetInstance()->SwitchScene(3);
		break;
	}
}

void CPlayScenceKeyHandler::OnKeyUp(int KeyCode)
{
	CSimon* simon = ((CPlayScene*)scence)->GetPlayer();
	switch (KeyCode)
	{

	case DIK_DOWN:
		if (simon->checkIsClimbing())
			simon->SetState(SIMON_STATE_IDLE_ON_STAIR);
		else
			simon->setIsDucking(false);
			simon->SetState(SIMON_STATE_IDLE);
		break;
	case DIK_RIGHT:
		if(simon->checkIsClimbing())
			simon->SetState(SIMON_STATE_IDLE_ON_STAIR);
		else
			simon->SetState(SIMON_STATE_IDLE);
		break;
	case DIK_LEFT:
		if(simon->checkIsClimbing())
			simon->SetState(SIMON_STATE_IDLE_ON_STAIR);
		else
			simon->SetState(SIMON_STATE_IDLE);
		break;
	case DIK_UP:
		if(simon->checkIsClimbing())
			simon->SetState(SIMON_STATE_IDLE_ON_STAIR);
		break;

	}
}
void CPlayScenceKeyHandler::KeyState(BYTE* states)
{
	CGame* game = CGame::GetInstance();
	CSimon* simon = ((CPlayScene*)scence)->GetPlayer();

	if (game->IsKeyDown(DIK_DOWN))
		if (simon->checkCanClimbDown()) {
			simon->setIsClimbing(true);
			simon->SetState(SIMON_STATE_CLIMBING_DOWN);
		} else {

			simon->SetState(SIMON_STATE_DUCKING);

		}

	if (game->IsKeyDown(DIK_Z)) {
		if (simon->checkIsClimbing()) simon->SetState(SIMON_STATE_HITTING_ON_STAIR);
	
		else if (simon->checkIsDucking()) { simon->SetState(SIMON_STATE_SITTING_AND_HITTING);}

		else simon->SetState(SIMON_STATE_STANDING_HITTING);
	}
	if (game->IsKeyDown(DIK_RIGHT)) {
		if (simon->checkIsClimbing()) {
			simon->SetState(SIMON_STATE_CLIMBING_UP);
		}
		else {
			simon->SetState(SIMON_STATE_WALKING_RIGHT);
		}
	}
	if (game->IsKeyDown(DIK_LEFT))
		if (simon->checkIsClimbing()) {
			simon->SetState(SIMON_STATE_CLIMBING_DOWN);
		}
		else {
			simon->SetState(SIMON_STATE_WALKING_LEFT);
		}
	if (game->IsKeyDown(DIK_UP))
		if (simon->checkCanClimbUp()) {
			simon->SetState(SIMON_STATE_CLIMBING_UP);
			simon->setIsClimbing(true);
		}
			

}