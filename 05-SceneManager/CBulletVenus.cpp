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
    float length = sqrt(direction_x * direction_x + direction_y * direction_y);

    // Tránh chia cho 0
    if (length == 0.0f)
    {
        vx = 0;
        vy = 0;
        return;
    }

    // Normalize the direction vector, avoid bullet speed being too fast
    float norm_x = direction_x / length;
    float norm_y = direction_y / length;

    vx = norm_x * BULLET_SPEED;
    vy = norm_y * BULLET_SPEED;
}

void CBulletVenus::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - BULLETVENUS_BBOX_WIDTH / 2;
	t = y - BULLETVENUS_BBOX_HEIGHT / 2;
	r = l + BULLETVENUS_BBOX_WIDTH;
	b = t + BULLETVENUS_BBOX_HEIGHT;
}