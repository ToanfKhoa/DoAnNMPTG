#include "CCoinItem.h"

void CCoinItem::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_COINITEM)->Render(x, y);
}

void CCoinItem::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - COINITEM_BBOX_WIDTH / 2;
	t = y - COINITEM_BBOX_HEIGHT / 2;
	r = l + COINITEM_BBOX_WIDTH;
	b = t + COINITEM_BBOX_HEIGHT;
}


