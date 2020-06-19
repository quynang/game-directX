#include <iostream>
#include <fstream>
#include "Textures.h"
#include "Sprites.h"
#include "PlayScence.h"
#include "Utils.h"
#include "Portal.h"
#include "ResourceManager.h"

using namespace std;

CPlayScene::CPlayScene(int id, LPCWSTR filePath) :
	CScene(id, filePath)
{
	key_handler = new CPlayScenceKeyHandler(this);
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
	LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);
	player->SetAnimationSet(ani_set);
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
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }

		//
		// data section
		//
		switch (section)
		{
		case SCENE_SECTION_MAP: _ParseSection_MAP(line); break;
		case SCENE_SECTION_PLAYER: _ParseSection_PLAYER(line); break;
		}
	}

	f.close();


	DebugOut(L"[INFO] Done loading scene resources %s\n", sceneFilePath);
}

void CPlayScene::Update(DWORD dt)
{
	//TODO
	float cx, cy;
	player->GetPosition(cx, cy);

	CGame* game = CGame::GetInstance();
	cx -= game->GetScreenWidth() / 2;
	cy -= game->GetScreenHeight() / 2;
	if (cx < 0) cx = 0;
	if (cx > 410) cx = 410;
	CGame::GetInstance()->SetCamPos(cx, 10.0f /*cy*/);
	player->Update(dt);
}

void CPlayScene::Render()
{
	//TODO
	CMap::GetInstance()->Render();
	player->Render();
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
	case DIK_SPACE:
		simon->SetState(SIMON_STATE_JUMP);
		break;
	case DIK_A:
		simon->Reset();
		break;
	}
}

void CPlayScenceKeyHandler::KeyState(BYTE* states)
{
	CGame* game = CGame::GetInstance();
	CMap* map = CMap::GetInstance();
	CSimon* simon = ((CPlayScene*)scence)->GetPlayer();

	if (game->IsKeyDown(DIK_RIGHT)) {
		simon->SetState(SIMON_STATE_WALKING_RIGHT);
	} else if (game->IsKeyDown(DIK_LEFT))
		simon->SetState(SIMON_STATE_WALKING_LEFT);
	else
		simon->SetState(SIMON_STATE_IDLE);
}