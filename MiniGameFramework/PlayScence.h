#pragma once
#include "Game.h"
#include "Textures.h"
#include "Scence.h"
#include "Map.h"
#include "GameObject.h"
#include "Simon.h"


class CPlayScene : public CScene //Chú ý nha. Cái này kế thừa từ thằng CScence
{
protected:

	CSimon* player;				// A play scene has to have player, right? 

	vector<LPGAMEOBJECT> objects;
	void _ParseSection_OBJECTS();
	void _ParseSection_MAP(string line);
	void _ParseSection_PLAYER(string line);
	bool offUpdation = false;
	DWORD timerFlag = 0;

public:
	CPlayScene(int id, LPCWSTR filePath);
	
	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();
	virtual void AddObject(LPGAMEOBJECT object);
	void TurnOffGameUpdationByTimer(DWORD timer);

	CSimon* GetPlayer() { return player; }

	//friend class CPlayScenceKeyHandler;
};

class CPlayScenceKeyHandler : public CScenceKeyHandler
{
public:
	virtual void KeyState(BYTE* states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
	CPlayScenceKeyHandler(CScene* s) :CScenceKeyHandler(s) {};
	
};

