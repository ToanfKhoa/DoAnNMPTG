#include "CEffect.h"

void CEffect::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (timer < EFFECT_TIME)
	{
		timer += dt;
		if (timer >= EFFECT_TIME)
			this->Delete();
	}
}

void CEffect::Render()
{
	CAnimations::GetInstance()->Get(ID_ANIMATION_EFFECT)->Render(x, y);
}