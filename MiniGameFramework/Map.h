#pragma on
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "Utils.h"
#include "TileSet.h"
#include "define.h"
using namespace std;
#define FRAME_WIDTH  32
#define FRAME_HEIGHT 32

class CMap {
	static CMap* __instance;
public:
	CMap();
	~CMap();
	int getWidth();
	int getHeight();
	void Load(LPCWSTR gameFile);
	void Render();
	void Update();
	int valueAt(int i, int j);
	static CMap* GetInstance();
private:
	void _ParseSection_TILE_SET(string line);
	void _ParseSection_MAP_MATRIX(string line);
	vector< vector<int> > mapMatrix;
	LPTILESET mTitleSet;
};