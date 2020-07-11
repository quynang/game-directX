#include "TourchFlame.h"
#include "Game.h"
#include "PlayScence.h"
#include "Item.h"
CTourchFlame::CTourchFlame() {
	isVisible = true;
	hitEffect = new CHitEffect();
	fireBombEffect = new CFireBombEffect();
}
void CTourchFlame::Render()
{

	hitEffect->Render();
	fireBombEffect->Render();
	if (isVisible) {
		animation_set->at(0)->Render(x, y);
		RenderBoundingBox();
	}

}

void CTourchFlame::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	if (isVisible) {
		left = x;
		top = y;
		right = x + 16;
		bottom = y + 30;
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
		hitEffect->SetPosition(x + 5, y + 5);
		hitEffect->setIsVisible(true);
		fireBombEffect->SetPosition(x + 5, y + 5);
		fireBombEffect->setIsVisible(true);
		((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->AddObject(item);
	}
}
