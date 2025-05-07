#include "CBrokenBrickPiece.h"
#include "AssetIDs.h"

void CBrokenBrickPiece::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_SPRITE_BROKEN_BRICK_PIECE)->Render(x, y);
}

void CBrokenBrickPiece::Update(DWORD dt)
{
	vy += ay * dt;

	x += vx * dt;
	y += vy * dt;

	if (GetTickCount64() - existStartTime > BROKEN_PIECE_EXIST_TIME)
		isDeleted = true;
}
