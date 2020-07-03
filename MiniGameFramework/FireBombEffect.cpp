#include "FireBombEffect.h"

CFireBombEffect::CFireBombEffect() {
	isVisible = false;
	timer = 0;
}
void CFireBombEffect::Render() {
	if (isVisible) {
		if(timer == 0) timer = GetTickCount();
		CAnimationSets::GetInstance()->Get(31)->at(1)->Render(x, y);
		if (GetTickCount() - timer > 200) {
			timer = 0;
			isVisible = false;
		}
	}
}