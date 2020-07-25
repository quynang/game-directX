#include "GameStatusBoard.h"
#include "Define.h"
#include "Game.h"
#include "Textures.h"
#include "Utils.h"

CGameStatusBoard::CGameStatusBoard()
{
	
	this->d3ddv = CGame::GetInstance()->GetDirect3DDevice();
	this->spriteHandler = CGame::GetInstance()->GetSpriteHandler();

	font = NULL;

	D3DXFONT_DESC FontDesc = {
		12,
		7,
		5,
		5,
		false,
		DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS,
		CLEARTYPE_QUALITY,
		FF_DONTCARE, L"resources\\font.ttf" };

	//#GameStausBoard
	//100004	0	0	200	39	900	0	0
	
	CTextures::GetInstance()->Add(99, L"resources\\game-status-board.png", D3DCOLOR_XRGB(0, 0, 0));
	LPDIRECT3DTEXTURE9 tex = CTextures::GetInstance()->Get(99);
	CSprites::GetInstance()->Add(9999, 0, 0, 200, 39, tex, 0, 0);
	sprite = CSprites::GetInstance()->Get(9999);
	D3DXCreateFontIndirect(d3ddv, &FontDesc, &font);

	int ScreenWidth = CGame::GetInstance()->GetScreenWidth();

	SetRect(&rectRowOne, 60, 5, ScreenWidth , 85);
	SetRect(&rectRowTwo, 60, 15, ScreenWidth, 85);
	SetRect(&rectRowThree, 60, 25, ScreenWidth, 85);
	inforRowOne = L"SCORE_000000 TIME 0000 STAGE 00\n";
	inforRowTwo = L"PLAYER                                         -5";
	inforRowThree = L"ENEMY                                         P-3";

}

CGameStatusBoard::~CGameStatusBoard()
{
}


void CGameStatusBoard::Update(int timeRemain)
{
	

	wstring scoreString = L"";
	while (scoreString.length() < 6)
		scoreString = L"0" + scoreString;

	wstring timeString =  to_wstring(timeRemain);
	while (timeString.length() < 4)
		timeString = L"0" + timeString;


	wstring stageString =  L"1";
	while (stageString.length() < 2)
		stageString = L"0" + stageString;


	inforRowOne = scoreString + L"             " + timeString + L"       " + stageString + L"\n";
}

void CGameStatusBoard::Render()
{
	float _cx, _cy;
    CGame::GetInstance()->GetCamPos(_cx, _cy);
	sprite->Draw( _cx + 5, -38);
	//CSprites::GetInstance()->Get(9999)->Draw( _cx - delta_x, -38);
	font->DrawText(spriteHandler, inforRowOne.c_str(), -1, &rectRowOne, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255));
	font->DrawText(spriteHandler, inforRowTwo.c_str(), -1, &rectRowTwo, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255));
	font->DrawText(spriteHandler, inforRowThree.c_str(), -1, &rectRowThree, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255));


}
