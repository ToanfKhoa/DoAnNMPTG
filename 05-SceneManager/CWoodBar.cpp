#include "CWoodBar.h"
#include "Sprites.h"
#include "debug.h"

void CWoodBar::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - WOODBAR_WIDTH / 2;
	top = y - WOODBAR_HEIGHT / 2;
	right = left + WOODBAR_WIDTH;
	bottom = top + WOODBAR_HEIGHT;
}

void CWoodBar::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	x += vx * dt;
	y += vy * dt;
	DebugOut(L"WoodBar: %f, %f\n", x, y);
}

void CWoodBar::Render()
{
	RenderBoundingBox();

	CSprites* sprites = CSprites::GetInstance();

	sprites->Get(ID_SPRITE_WOODBAR_START)->Draw(x - SPRITE_SPACING, y);
	sprites->Get(ID_SPRITE_WOODBAR_MIDDLE)->Draw(x, y);
	sprites->Get(ID_SPRITE_WOODBAR_END)->Draw(x + SPRITE_SPACING, y);
}

void CWoodBar::Fall()
{
	vx = 0;
	ay = WOODBAR_GRAVITY;
}