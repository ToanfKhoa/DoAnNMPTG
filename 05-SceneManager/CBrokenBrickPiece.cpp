#include "CBrokenBrickPiece.h"
#include "AssetIDs.h"
#include "debug.h"

void CBrokenBrickPiece::Render()
{
	CSprites* s = CSprites::GetInstance();
	s->Get(ID_SPRITE_BROKEN_BRICK_PIECE)->Draw(x, y);
}

void CBrokenBrickPiece::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;

	x += vx * dt;
	y += vy * dt;

	if (GetTickCount64() - existStartTime > BROKEN_PIECE_EXIST_TIME)
		isDeleted = true;
}
