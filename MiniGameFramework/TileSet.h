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

class CTileSet {
public:
	CTileSet(int id, LPCWSTR filePath, int numRows, int numCols);
	~CTileSet();
	void loadTileSetIntoResources();
	vector<LPSPRITE> getSprites();
private:
	int id;
	int numRows;
	int numCols;
	LPCWSTR filePath;
};
typedef CTileSet* LPTILESET;