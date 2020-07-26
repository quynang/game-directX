#include "TourchFlame.h"
#include "Game.h"
#include "PlayScence.h"
#include "Item.h"
CTourchFlame::CTourchFlame(float x, float y) {
	isVisible = true;
	hitEffect = new CHitEffect();
	fireBombEffect = new CFireBombEffect();
	this->x = x;
	this->y = y;
}
void CTourchFlame::Render()
{

	if (isVisible) {
		animation_set->at(0)->Render(x, y);
		RenderBoundingBox();
	}
	hitEffect->Render();
	fireBombEffect->Render();
}

void CTourchFlame::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	if (isVisible) {
		left = x;
		top = y;
		right = x + TOURCH_FLAME_BOX_WIDTH;
		bottom = y + TOURCH_FLAME_BOX_HEIGHT;
	}
	
}

void CTourchFlame::SetVisible(bool value) {
	this->isVisible = value;
}

void CTourchFlame::SetState(int state) {
	switch (state) {
	case TOURCH_FLAME_STATE_DESTROY:
		isVisible = false;
		CItem *item = CItem::Create(item_type, x, y);
		item->SetVisible(true);
		((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->AddObject(item);
		hitEffect->SetPosition(x + 5, y + 5);
		hitEffect->setIsVisible(true);
		fireBombEffect->SetPosition(x + 5, y + 5);
		fireBombEffect->setIsVisible(true);
		
	}
}
