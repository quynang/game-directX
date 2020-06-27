#pragma once
#include "Utils.h"
#include "Textures.h"
#include "Sprites.h"
#include "Animations.h"
#include "GameObject.h"
class CResourceManager
{
	static CResourceManager* __instance;
public:
	void _ParseSection_TEXTURES(string line);
	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);
	void _ParseSection_ANIMATION_SETS(string line);
	void _ParseSection_OBJECTS(string line, vector<LPGAMEOBJECT> &objects);
	void LoadTextures(LPCWSTR filePath);
	void LoadAnimations(LPCWSTR filePath);
	void LoadSprites(LPCWSTR filePath);
	void LoadAnimationSets(LPCWSTR filePath);
	static CResourceManager* GetInstance();

};