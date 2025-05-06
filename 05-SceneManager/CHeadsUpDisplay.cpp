#include "CHeadsUpDisplay.h"

void CHeadsUpDisplay::Render()
{
	CSprites* s = CSprites::GetInstance();
	s->Get(this->spriteId)->DrawOnScreen(x, y);
}
