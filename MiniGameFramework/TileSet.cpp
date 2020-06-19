#include "TileSet.h"


CTileSet::CTileSet(int id, LPCWSTR filePath, int numRows, int numCols) {
	this->id = id;
	this->filePath = filePath;
	this->numRows = numRows;
	this->numCols = numCols;
	loadTileSetIntoResources();
}

CTileSet::~CTileSet() {
}

void CTileSet::loadTileSetIntoResources() {
	CTextures* textures = CTextures::GetInstance();
	CSprites* sprites = CSprites::GetInstance();
	textures->Add(id, filePath, D3DCOLOR_XRGB(255, 255, 255));
	LPDIRECT3DTEXTURE9 _texture = textures->Get(id);
	int count = 0;

	/*
		why id + count ? Because we going to get id of sprite. Id as a prefix to avoid duplication of id in sprites resource
	*/
	for (int i = 0; i < numRows; i++)
		for (int j = 0; j < numCols; j++) {
			count++;
			sprites->Add(id + count, j * FRAME_SIZE, i * FRAME_SIZE, j * FRAME_SIZE + FRAME_SIZE, i * FRAME_SIZE + FRAME_SIZE, _texture);
		}
			
}

vector<LPSPRITE> CTileSet::getSprites() {

	vector<LPSPRITE> mSprites;
	CSprites* sprites = CSprites::GetInstance();
	int count = 0;
	for (int i = 0; i < numRows; i++)
		for (int j = 0; j < numCols; j++) {
			count++;
			mSprites.push_back(sprites->Get(id + count));
		}
	return mSprites;	 	  
}
