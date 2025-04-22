#include "CWoodBlock.h"

void CWoodBlock::Render()
{
	CAnimations* animation = CAnimations::GetInstance();
	animation->Get(ID_ANI_WOODBLOCK)->Render(x, y);
}

void CWoodBlock::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - WOODBLOCK_BBOX_WIDTH / 2;
	t = y - WOODBLOCK_BBOX_HEIGHT / 2;
	r = l + WOODBLOCK_BBOX_WIDTH;
	b = t + WOODBLOCK_BBOX_HEIGHT;
}
