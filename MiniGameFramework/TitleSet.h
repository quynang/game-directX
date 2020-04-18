#pragma on
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "Sprites.h"
#include "Textures.h"
#include "Utils.h"
#include "debug.h"
#include "define.h"
using namespace std;

class TitleSet {
public:
	TitleSet(int id, LPCWSTR filePath, int numRows, int numCols);
	~TitleSet();
	void loadTitleSetIntoResources();
	vector<LPSPRITE> getSprites();
private:
	int id;
	int numRows;
	int numCols;
	LPCWSTR filePath;
};