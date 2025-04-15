#include "CBulletVenus.h"

void CBulletVenus::Render()
{
	RenderBoundingBox();
	CAnimations::GetInstance()->Get(ID_ANI_BULLETVENUS)->Render(x, y);
}

void CBulletVenus::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	x += vx * dt;
	y += vy * dt;
}

void CBulletVenus::Fire(float direction_x, float direction_y)
{
	vx = direction_x * BULLET_SPEED;
	vy = direction_y * BULLET_SPEED;
}

void CBulletVenus::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - BULLETVENUS_BBOX_WIDTH / 2;
	t = y - BULLETVENUS_BBOX_HEIGHT / 2;
	r = l + BULLETVENUS_BBOX_WIDTH;
	b = t + BULLETVENUS_BBOX_HEIGHT;
}