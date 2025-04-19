#include "CColorBlock.h"

void CColorBlock::Render()
{
	if (this->length_x <= 0 || this->length_y <= 0) return;

	float xx = x;
	float yy = y;
	CSprites* s = CSprites::GetInstance();

	for (int i = 0; i < this->length_x; i++)
	{
		for (int j = 0; j < this->length_y; j++)
		{
			if (i == 0 && j == 0) s->Get(this->spriteIdBotLeft)->Draw(xx, yy);
			else if (i == 0 && j < this->length_y - 1) s->Get(this->spriteIdLeft)->Draw(xx, yy);
			else if (i == 0 && j == length_y - 1) s->Get(this->spriteIdTopLeft)->Draw(xx, yy);
			else if (i == length_x - 1 && j == 0) s->Get(this->spriteIdBotRight)->Draw(xx, yy);
			else if (i == length_x - 1 && j < this->length_y - 1) s->Get(this->spriteIdRight)->Draw(xx, yy);
			else if (i == length_x - 1 && j == length_y - 1) s->Get(this->spriteIdTopRight)->Draw(xx, yy);
			else if (j == 0) s->Get(this->spriteIdBot)->Draw(xx, yy);
			else if (j == length_y - 1) s->Get(this->spriteIdTop)->Draw(xx, yy);
			else s->Get(this->spriteIdMiddle)->Draw(xx, yy);

			yy -= this->cellHeight;
		}
		yy = y;
		xx += this->cellWidth;
	}
	
}

void CColorBlock::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	float cellWidth_div_2 = this->cellWidth / 2;
	l = x - cellWidth_div_2;
	t = y - this->cellHeight / 2;
	r = l + this->cellWidth * this->length_x;
	b = t + this->cellHeight * this->length_y;

}

int CColorBlock::IsDirectionColliable(float nx, float ny)
{
	if (nx == 0 && ny == -1) return 1;
	else return 0;
}
