#include "CSensorBox.h"
#include "debug.h"
#include "CKoopa.h"
CSensorBox::CSensorBox(float x, float y, int BBOX_WIDTH, int BBOX_HEIGHT): CGameObject(x, y)
{
	this->x = x;
	this->y = y;
	isOnPlatform = true;
	ay = SENSORBOX_GRAVITY;
	vy = 0;
	this->bboxWidth = BBOX_WIDTH;
	this->bboxHeight = BBOX_HEIGHT;
}
void CSensorBox::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;

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
	/*if (noCollisionStart == 0) noCollisionStart = GetTickCount64();

	if (GetTickCount64() - noCollisionStart > SENSORBOX_NO_COLLISION_THRESHOLD)
	{
		isOnPlatform = false;
	}*/

	isOnPlatform = false;

	y += vy * dt;
}
void CSensorBox::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CKoopa*>(e->obj)) return;

	if (e->ny < 0 && e->obj->IsBlocking())
	{
		vy = 0;
		isOnPlatform = true;
	}
}