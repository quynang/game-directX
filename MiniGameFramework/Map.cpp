#include "Map.h"
#include "Utils.h"
#include "Game.h"
CMap::CMap()
{

}


CMap::~CMap()
{
}

CMap* CMap::__instance = NULL;
   

CMap* CMap::GetInstance()
{
    if (__instance == NULL) __instance = new CMap();
    return __instance;
}

#define MAX_GAME_LINE 1024
#define GAME_FILE_SECTION_UNKNOWN -1
#define MAP_FILE_SECTION_TILE_SET 1
#define MAP_FILE_SECTION_MAP_MATRIX 2
void CMap::Load(LPCWSTR gameFile) {

    DebugOut(L"[INFO] Start loading game file : %s\n", gameFile);

    ifstream f;
    f.open(gameFile);
    char str[MAX_GAME_LINE];

    int section = GAME_FILE_SECTION_UNKNOWN;

    while (f.getline(str, MAX_GAME_LINE))
    {
        string line(str);

        if (line[0] == '#') continue;

        if (line == "[TILE_SET]") { section = MAP_FILE_SECTION_TILE_SET; continue; }
        if (line == "[MAP_MATRIX]") { section = MAP_FILE_SECTION_MAP_MATRIX; continue; }

        switch (section)
        {
        case MAP_FILE_SECTION_TILE_SET: _ParseSection_TILE_SET(line); break;
        case MAP_FILE_SECTION_MAP_MATRIX: _ParseSection_MAP_MATRIX(line); break;
        }
    }
}


void CMap::_ParseSection_MAP_MATRIX(string line) {
    vector<string> tokens = split(line, ",");
    vector<int> row;
    for (int i = 0; i < tokens.size(); i++) {
        int value = atoi(tokens[i].c_str());
        row.push_back(value);
    }
    this->mapMatrix.push_back(row);
}

void CMap::_ParseSection_TILE_SET(string line) {
    vector<string> tokens = split(line, "\t");

    if (tokens.size() < 4) return;

    int texID = atoi(tokens[0].c_str());
    LPCWSTR path = ToLPCWSTR(tokens[1]);
    int numRows = atoi(tokens[2].c_str());
    int numCols = atoi(tokens[3].c_str());
    mTitleSet = new CTileSet(texID, path, numRows, numCols);
}

int CMap::getWidth() {
    int numCols = this->mapMatrix.at(0).size();
    return numCols * FRAME_WIDTH;
}

int CMap::getHeight() {
    int numRows = this->mapMatrix.size();
    return numRows * FRAME_HEIGHT;
}

int CMap::valueAt(int i, int j) {
    return this->mapMatrix.at(i).at(j);
}

void CMap::Render() {
    int numCols = this->mapMatrix.at(0).size();
    int numRows = this->mapMatrix.size();
    float _cx, _cy;
    int screenWidth = CGame::GetInstance()->GetScreenWidth();
    int screenHeight = CGame::GetInstance()->GetScreenHeight();
    CGame::GetInstance()->GetCamPos(_cx, _cy);

    DebugOut(L"Camera Info x: %f y: %f \n", _cx, _cy);
    
    int cellStartX = _cx / FRAME_SIZE;
    int cellStartY = _cy / FRAME_SIZE;
    int cellEndX = ceil((float) (_cx + screenWidth) / FRAME_SIZE);
    int cellEndY = ceil((float) (_cy + screenHeight) / FRAME_SIZE);

    if (cellEndX > numCols) cellEndX = numCols;
    if (cellEndY > numRows) cellEndY = numRows;

    vector<LPSPRITE> titleSprites = mTitleSet->getSprites();
    for(int i = cellStartY; i < cellEndY; i++)
        for (int j = cellStartX; j < cellEndX; j++) {
            titleSprites.at(mapMatrix.at(i).at(j) - 1)->Draw(j * FRAME_SIZE, i * FRAME_SIZE);
        }
}

void CMap::Update() {
    
}
