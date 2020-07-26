#include "Sprites.h"
#include "Game.h"
#include "Utils.h"

CSprite::CSprite(int id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex, float dx, float dy)
{
	this->id = id;
	this->left = left;
	this->top = top;
	this->right = right;
	this->bottom = bottom;
	this->texture = tex;
	this->dx = dx;
	this->dy = dy;
}

CSprites* CSprites::__instance = NULL;

CSprites* CSprites::GetInstance()
{
	if (__instance == NULL) __instance = new CSprites();
	return __instance;
}

void CSprite::Draw(float x, float y, int alpha)
{
	CGame* game = CGame::GetInstance();
	game->Draw(x, y + 38, texture, left, top, right, bottom, alpha, dx, dy);
}

void CSprites::Add(int id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex, float dx, float dy)
{
	LPSPRITE s = new CSprite(id, left, top, right, bottom, tex, dx, dy);
	sprites[id] = s;

	DebugOut(L"[INFO] sprite added: %d, %d, %d, %d, %d %f %f \n", id, left, top, right, bottom, dx, dy);
}

LPSPRITE CSprites::Get(int id)
{
	return sprites[id];
}

/*
	Clear all loaded textures
*/
void CSprites::Clear()
{

	int globalSprites[] = {9999, 8001, 8002, 8003};
	 
	for (auto x : sprites)
	{
		if (find(begin(globalSprites), end(globalSprites), x.first) == end(globalSprites)) {
			LPSPRITE s = x.second;
			delete s;
		}
	}

	sprites.clear();
}