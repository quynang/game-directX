#include "Candle.h"
#include "Game.h"
#include "PlayScence.h"
#include "Item.h"
CCandle::CCandle(float x, float y) {
	isVisible = true;
	hitEffect = new CHitEffect();
	fireBombEffect = new CFireBombEffect();
	this->x = x;
	this->y = y;
}
void CCandle::Render()
{

	hitEffect->Render();
	fireBombEffect->Render();
	if (isVisible) {
		animation_set->at(0)->Render(x, y);
		RenderBoundingBox();
	}

}

void CCandle::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	if (isVisible) {
		left = x;
		top = y;
		right = x + CANDLE_BOX_WIDTH;
		bottom = y + CANDLE_BOX_HEIGHT;
	}
	
}

void CCandle::SetVisible(bool value) {
	this->isVisible = value;
}

void CCandle::SetState(int state) {
	switch (state) {
	case CANDLE_STATE_DESTROY: 
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
