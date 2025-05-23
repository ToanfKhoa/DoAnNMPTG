#include "CWoodBar.h"
#include "Sprites.h"
#include "debug.h"

void CWoodBar::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = left + WOODBAR_WIDTH;
	bottom = top + WOODBAR_HEIGHT;
}

void CWoodBar::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	x += vx * dt;
	y += vy * dt;
	DebugOut(L"WoodBar: %f, %f\n", x, y);
}

void CWoodBar::Render()
{
	RenderBoundingBox();

	CSprites* sprites = CSprites::GetInstance();

	sprites->Get(ID_SPRITE_WOODBAR_START)->Draw(x, y);
	sprites->Get(ID_SPRITE_WOODBAR_MIDDLE)->Draw(x + SPRITE_SPACING, y);
	sprites->Get(ID_SPRITE_WOODBAR_END)->Draw(x + SPRITE_SPACING * 2, y);
}

void CWoodBar::Fall()
{
	vx = 0;
	vy = WOODBAR_SPEED_Y;
}