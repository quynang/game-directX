#pragma on
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "Utils.h"
#include "TitleSet.h"
#include "debug.h"
#include "Camera.h"
#include "define.h"
using namespace std;
#define FRAME_WIDTH  32
#define FRAME_HEIGHT 32

class Map {
public:
	Map();
	~Map();
	int getWidth();
	int getHeight();
	void loadMap();
	void Render();
	void parseMapMatrixFromTxt(LPCWSTR filePath);
	int valueAt(int i, int j);
	TitleSet* getTitleSet();
	void setCamera(Camera* mCamera);
	void updateCameraPositionX(int x);
private:
	Camera* mCamera;
	vector< vector<int> > mapMatrix;
	TitleSet* mTitleSet;
	char* txtFilePath;
	char* tileSetFilePath;
	void loadResources();

};