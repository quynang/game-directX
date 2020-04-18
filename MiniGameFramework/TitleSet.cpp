#include "TitleSet.h"


TitleSet::TitleSet(int id, LPCWSTR filePath, int numRows, int numCols) {
	this->id = id;
	this->filePath = filePath;
	this->numRows = numRows;
	this->numCols = numCols;


}

TitleSet::~TitleSet() {
}

void TitleSet::loadTitleSetIntoResources() {
	CTextures* textures = CTextures::GetInstance();
	CSprites* sprites = CSprites::GetInstance();
	textures->Add(id, filePath, D3DCOLOR_XRGB(255, 255, 255));
	LPDIRECT3DTEXTURE9 texLv1 = textures->Get(id);
	int count = 0;
	for (int i = 0; i < numRows; i++)
		for (int j = 0; j < numCols; j++) {
			count++;
			sprites->Add(LV1_SPRITES_ID_PREFIX + count, j * FRAME_SIZE, i * FRAME_SIZE, j * FRAME_SIZE + FRAME_SIZE, i * FRAME_SIZE + FRAME_SIZE, texLv1);
		}
			
}

vector<LPSPRITE> TitleSet::getSprites() {

	vector<LPSPRITE> mSprites;
	CSprites* sprites = CSprites::GetInstance();
	int count = 0;
	for (int i = 0; i < numRows; i++)
		for (int j = 0; j < numCols; j++) {
			count++;
			mSprites.push_back(sprites->Get(LV1_SPRITES_ID_PREFIX + count));
		}
	return mSprites;	 	  
}
