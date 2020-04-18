#include "Map.h"

Map::Map()
{
    loadResources();
}


Map::~Map()
{
}

void Map::loadResources() {
    parseMapMatrixFromTxt(L"lv1.txt");
    mTitleSet = new TitleSet(30, L"textures\\lv1.png", 1, 23);
    mTitleSet->loadTitleSetIntoResources();
}

void Map::setCamera(Camera* mCamera) {
    this->mCamera = mCamera;
}

void Map::parseMapMatrixFromTxt(LPCWSTR filePath) {
	ifstream infile(filePath);
    string line;
    while (getline(infile, line)) {
        vector<int> row = split(line, ",");
        this->mapMatrix.push_back(row);
    }
}

int Map::getWidth() {
    int numCols = this->mapMatrix.at(0).size();
    return numCols * FRAME_WIDTH;

}

int Map::getHeight() {
    int numRows = this->mapMatrix.size();
    return numRows * FRAME_HEIGHT;
}

int Map::valueAt(int i, int j) {
    return this->mapMatrix.at(i).at(j);
}


TitleSet* Map::getTitleSet() {
    return this->mTitleSet;
}

void Map::Render() {

    int cellStartX = mCamera->getPostion().x / FRAME_SIZE;
    int cellStartY = mCamera->getPostion().y / FRAME_SIZE;
    int cellEndX = ceil((mCamera->getWidth() + mCamera->getPostion().x) / FRAME_SIZE);
    int cellEndY = (mCamera->getHeight() + mCamera->getPostion().y) / FRAME_SIZE;
 
    vector<LPSPRITE> titleSprites = mTitleSet->getSprites();
    for(int i = cellStartY; i < cellEndY; i++)
        for (int j = cellStartX; j < cellEndX; j++) {
            titleSprites.at(mapMatrix.at(i).at(j) - 1)->Draw(j * FRAME_SIZE -  mCamera->getPostion().x, i * FRAME_SIZE - mCamera->getPostion().y);
        }

}

void Map::updateCameraPosition(int x, int y) {

    if (x > 0) {
       
        if (mCamera->getBound().right < (this->getWidth() - (FRAME_SIZE + x))) {
            mCamera->setPostion(mCamera->getPostion().x + x, 0);
        }

    }
    else {
        if (mCamera->getBound().left > 0) {
            mCamera->setPostion(mCamera->getPostion().x + x, 0);
        }
    }
   
       
}