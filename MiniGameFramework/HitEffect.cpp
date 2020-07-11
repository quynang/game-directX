#include "HitEffect.h"

CHitEffect::CHitEffect() {
	isVisible = false;
	timer = 0;
}
void CHitEffect::Render() {
	if (isVisible) {
		if(timer == 0) timer = GetTickCount();
		CAnimationSets::GetInstance()->Get(31)->at(0)->Render(x, y);
		//CAnimations::GetInstance()->Get(301)->Render(x, y);
		if (GetTickCount() - timer > 300) {
			timer = 0;
			isVisible = false;
		}
	}
}