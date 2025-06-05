#include "CEffect.h"
#include "debug.h"

void CEffect::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	DebugOut(L"update effect x %.3f \n", x);
	DebugOut(L"update effect y %.3f \n", y);
	if (timer < EFFECT_TIME)
	{
		timer += dt;
		if (timer >= EFFECT_TIME)
			this->Delete();
	}
}

void CEffect::Render()
{
	DebugOut(L"render effect \n");
	CAnimations::GetInstance()->Get(ID_ANIMATION_EFFECT)->Render(x, y);
}