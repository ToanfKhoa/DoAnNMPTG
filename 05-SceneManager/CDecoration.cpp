#include "CDecoration.h"
#include "Sprites.h"

void CDecoration::Render()
{
	CSprites* s = CSprites::GetInstance();
	s->Get(this->spriteId)->DrawWithParallax(x, y, layer);
}
