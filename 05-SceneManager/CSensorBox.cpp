#include "CSensorBox.h"

CSensorBox::CSensorBox(float x, float y, int BBOX_WIDTH, int BBOX_HEIGHT): CGameObject(x, y)
{
	this->x = x;
	this->y = y;
	this->bboxWidth = BBOX_WIDTH;
	this->bboxHeight = BBOX_HEIGHT;
}
void CSensorBox::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}
void CSensorBox::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - bboxWidth / 2;
	t = y - bboxHeight / 2;
	r = l + bboxWidth;
	b = t + bboxHeight;
}

void CSensorBox::OnNoCollision(DWORD dt)
{
	isOnPlatform = false;
}
void CSensorBox::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (e->ny != 0 && e->obj->IsBlocking())
	{
		if (e->ny < 0) isOnPlatform = true;
	}
}