#include "CPipe.h"
#include "Textures.h"
#include "Game.h"
#include "debug.h"

void CPipe::Render()
{
	if (this->length <= 0) return;
	float yy = y;
	CSprites* s = CSprites::GetInstance();

	for (int i = 1; i <= this->length - 1; i++)
	{
		s->Get(this->spriteIdMiddle)->Draw(x, yy);
		yy -= this->cellHeight;
	}
	if (length > 1)
		s->Get(this->spriteIdEnd)->Draw(x, yy);
}

void CPipe::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	float cellWidth_div_2 = this->cellWidth / 2;
	float cellHeight_div_2 = this->cellHeight / 2;

	l = x - cellWidth_div_2;
	r = l + this->cellWidth;
	b = y + cellHeight_div_2;
	t = b - this->cellHeight * this->length;
}

int CPipe::IsDirectionColliable(float nx, float ny)
{
	return 1;
}