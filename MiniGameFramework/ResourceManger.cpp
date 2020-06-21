#include "ResourceManager.h"
#include <iostream>
#include <fstream>

CResourceManager* CResourceManager::__instance = NULL;
CResourceManager* CResourceManager::GetInstance()
{
	if (__instance == NULL) __instance = new CResourceManager();
	return __instance;
}

void CResourceManager::_ParseSection_TEXTURES(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 5) return; // skip invalid lines

	int texID = atoi(tokens[0].c_str());
	wstring path = ToWSTR(tokens[1]);
	int R = atoi(tokens[2].c_str());
	int G = atoi(tokens[3].c_str());
	int B = atoi(tokens[4].c_str());

	CTextures::GetInstance()->Add(texID, path.c_str(), D3DCOLOR_XRGB(R, G, B));
}

void CResourceManager::_ParseSection_SPRITES(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 6) return; // skip invalid lines

	int ID = atoi(tokens[0].c_str());
	int l = atoi(tokens[1].c_str());
	int t = atoi(tokens[2].c_str());
	int r = atoi(tokens[3].c_str());
	int b = atoi(tokens[4].c_str());
	int texID = atoi(tokens[5].c_str());

	LPDIRECT3DTEXTURE9 tex = CTextures::GetInstance()->Get(texID);
	if (tex == NULL)
	{
		DebugOut(L"[ERROR] Texture ID %d not found!\n", texID);
		return;
	}

	CSprites::GetInstance()->Add(ID, l, t, r, b, tex);
}

void CResourceManager::_ParseSection_ANIMATIONS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 3) return; // skip invalid lines - an animation must at least has 1 frame and 1 frame time

	LPANIMATION ani = new CAnimation();

	int ani_id = atoi(tokens[0].c_str());
	for (int i = 1; i < tokens.size(); i += 2)	// why i+=2 ?  sprite_id | frame_time  
	{
		int sprite_id = atoi(tokens[i].c_str());
		int frame_time = atoi(tokens[i + 1].c_str());
		ani->Add(sprite_id, frame_time);
	}

	CAnimations::GetInstance()->Add(ani_id, ani);
}

void CResourceManager::_ParseSection_ANIMATION_SETS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 2) return; // skip invalid lines - an animation set must at least id and one animation id

	int ani_set_id = atoi(tokens[0].c_str());

	LPANIMATION_SET s = new CAnimationSet();

	CAnimations* animations = CAnimations::GetInstance();

	for (int i = 1; i < tokens.size(); i++)
	{
		int ani_id = atoi(tokens[i].c_str());

		LPANIMATION ani = animations->Get(ani_id);
		s->push_back(ani);
	}

	CAnimationSets::GetInstance()->Add(ani_set_id, s);

	DebugOut(L"Done add animation test \n", ani_set_id);
}


/*
	Parse a line in section [OBJECTS]
*/

void CResourceManager::_ParseSection_OBJECTS()
{
	//TODO
}

#define SCENE_SECTION_UNKNOWN -1
#define SCENE_SECTION_TEXTURES 2
#define SCENE_SECTION_SPRITES 3
#define SCENE_SECTION_ANIMATIONS 4
#define SCENE_SECTION_ANIMATION_SETS	5
#define SCENE_SECTION_OBJECTS	6
#define SCENE_SECTION_MAP	7
#define SCENE_SECTION_PLAYER	8

#define MAX_SCENE_LINE 1024
void CResourceManager::LoadTextures(LPCWSTR filePath)
{
	DebugOut(L"[INFO] Start loading Textures resources from : %s \n", filePath);

	ifstream f;
	f.open(filePath);

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	

		_ParseSection_TEXTURES(line);
	}

	f.close();


	DebugOut(L"[INFO] Done loading Textures resources from %s\n", filePath);

}

void CResourceManager::LoadSprites(LPCWSTR filePath)
{
	DebugOut(L"[INFO] Start loading Sprites from : %s \n", filePath);

	ifstream f;
	f.open(filePath);

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	

		_ParseSection_SPRITES(line);
	}

	f.close();

	DebugOut(L"[INFO] Done loading Sprites resources from %s\n", filePath);

}

void CResourceManager::LoadAnimations(LPCWSTR filePath)
{
	DebugOut(L"[INFO] Start loading Animations resource from : %s \n", filePath);

	ifstream f;
	f.open(filePath);

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	

		_ParseSection_ANIMATIONS(line);
	}

	f.close();

	DebugOut(L"[INFO] Done loading Animations resources from %s\n", filePath);

}

void CResourceManager::LoadAnimationSets(LPCWSTR filePath)
{
	DebugOut(L"[INFO] Start loading Animation Sets resource from : %s \n", filePath);

	ifstream f;
	f.open(filePath);

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	

		_ParseSection_ANIMATION_SETS(line);
	}

	f.close();

	DebugOut(L"[INFO] Done loading Animation Sets resources from %s\n", filePath);

}