#include "CSmallBush.h"
#include "Sprites.h"

void CSmallBush::Render()
{
	CSprites* s = CSprites::GetInstance();
	s->Get(this->spriteId)->Draw(x, y);
}
