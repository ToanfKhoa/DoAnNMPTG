#include "CGround.h"
void CGround::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_GROUND)->Render(x, y);
	//RenderBoundingBox();
}

void CGround::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - GROUND_BBOX_WIDTH / 2;
	t = y - GROUND_BBOX_HEIGHT / 2;
	r = l + GROUND_BBOX_WIDTH;
	b = t + GROUND_BBOX_HEIGHT;
}