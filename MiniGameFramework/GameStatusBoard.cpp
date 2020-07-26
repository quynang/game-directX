#include "GameStatusBoard.h"
#include "Define.h"
#include "Game.h"
#include "Textures.h"
#include "Utils.h"

CGameStatusBoard* CGameStatusBoard::__instance = NULL;
   

CGameStatusBoard* CGameStatusBoard::GetInstance()
{
    if (__instance == NULL) __instance = new CGameStatusBoard();
    return __instance;
}
CGameStatusBoard::CGameStatusBoard()
{
	
	this->d3ddv = CGame::GetInstance()->GetDirect3DDevice();
	this->spriteHandler = CGame::GetInstance()->GetSpriteHandler();

	font = NULL;

	D3DXFONT_DESC FontDesc = {
		12,
		6,
		600,
		5,
		false,
		DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS,
		CLEARTYPE_QUALITY,
		FF_DONTCARE, L"resources\\font.ttf" };

	//#GameStausBoard
	//100004	0	0	200	39	900	0	0
	
	CTextures::GetInstance()->Add(99, L"resources\\game-status-board.png", D3DCOLOR_XRGB(0, 0, 0));
	CTextures::GetInstance()->Add(88, L"resources\\hp.png", D3DCOLOR_XRGB(0, 0, 0));
	LPDIRECT3DTEXTURE9 status_board_tex = CTextures::GetInstance()->Get(99);
	LPDIRECT3DTEXTURE9 hp_tex = CTextures::GetInstance()->Get(88);
	CSprites::GetInstance()->Add(9999, 0, 0, 200, 39, status_board_tex, 0, 0);
	CSprites::GetInstance()->Add(8001, 0, 0, 5, 8, hp_tex, 0, 0);
	CSprites::GetInstance()->Add(8002, 6, 0, 11, 8, hp_tex, 0, 0);
	CSprites::GetInstance()->Add(8003, 12, 0, 17, 8, hp_tex, 0, 0);
	statusBoardSprite = CSprites::GetInstance()->Get(9999);
	
	hpSprite1 = CSprites::GetInstance()->Get(8001);
	hpSprite2 = CSprites::GetInstance()->Get(8002);
	hpSprite3 = CSprites::GetInstance()->Get(8003);

	D3DXCreateFontIndirect(d3ddv, &FontDesc, &font);

	int ScreenWidth = CGame::GetInstance()->GetScreenWidth();

	SetRect(&rectRowOne, 60, 5, ScreenWidth , 85);
	SetRect(&rectRowTwo, 202, 15, ScreenWidth, 85);
	SetRect(&rectRowThree, 60, 25, ScreenWidth, 85);
	inforRowOne = L"";
	inforRowTwo = L"";
	inforRowThree = L"";

}

CGameStatusBoard::~CGameStatusBoard()
{
}


void CGameStatusBoard::Update(int timeRemain)
{
	

	wstring scoreString = to_wstring(score);
	while (scoreString.length() < 6)
		scoreString = L"0" + scoreString;

	wstring timeString =  to_wstring(timeRemain);
	while (timeString.length() < 4)
		timeString = L"0" + timeString;

	wstring heartString =  to_wstring(heart);
	while (heartString.length() < 2)
		heartString = L"0" + heartString;

	wstring stageString =  L"1";
	while (stageString.length() < 2)
		stageString = L"0" + stageString;


	inforRowOne = scoreString + L"            " + timeString + L"      TAGE" + stageString + L"\n";
	inforRowTwo = heartString;
}

void CGameStatusBoard::Render()
{
	float _cx, _cy;
    CGame::GetInstance()->GetCamPos(_cx, _cy);
	statusBoardSprite->Draw( _cx + 5, -38);
	for (int i = 1; i <= 16; i++) {
		hpSprite2->Draw( _cx + 52 + i*6, -22);
	}

	for (int i = 1; i <= 5; i++) {
		hpSprite1->Draw( _cx + 52 + i*6, -22);
	}

	for (int i = 1; i <= 16; i++) {
		hpSprite3->Draw(_cx + 52 + i*6, -13);
	}
	
	//CSprites::GetInstance()->Get(80001)->Draw( _cx + 5, -38);
	font->DrawText(spriteHandler, inforRowOne.c_str(), -1, &rectRowOne, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255));
	font->DrawText(spriteHandler, inforRowTwo.c_str(), -1, &rectRowTwo, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255));
	font->DrawText(spriteHandler, inforRowThree.c_str(), -1, &rectRowThree, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255));


}
