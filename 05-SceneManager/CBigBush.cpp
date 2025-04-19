#include "CBigBush.h"

void CBigBush::Render()
{
	if(this->length <= 0) return;

	int xx = x;
	int yy = y;
	CSprites* s = CSprites::GetInstance();

	for(int i = 0; i < 2; i++)
	{
		for(int j = 0; j < this->length; j++)
		{
			if(i == 0 && j == this->length - 1)
				s->Get(this->spriteIdTopLeft)->Draw(xx, yy);
			else if( i == 1 && j == this->length - 1)
				s->Get(this->spriteIdTopRight)->Draw(xx, yy);
			else if(i == 0)
				s->Get(this->spriteIdLeft)->Draw(xx, yy);
			else
				s->Get(this->spriteIdRight)->Draw(xx, yy);

			yy -= this->cellHeight;
		}
		xx += this->cellWidth;
	}
}
