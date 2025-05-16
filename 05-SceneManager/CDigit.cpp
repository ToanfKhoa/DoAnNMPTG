#include "CDigit.h"

void CDigit::Render()
{
	CSprites* s = CSprites::GetInstance();

	switch (value) 
	{
		case 0:
			s->Get(SPRITE_0)->DrawOnScreen(x, y);
			break;
		case 1:
			s->Get(SPRITE_1)->DrawOnScreen(x, y);
			break;
		case 2:
			s->Get(SPRITE_2)->DrawOnScreen(x, y);
			break;
		case 3:
			s->Get(SPRITE_3)->DrawOnScreen(x, y);
			break;
		case 4:
			s->Get(SPRITE_4)->DrawOnScreen(x, y);
			break;
		case 5:
			s->Get(SPRITE_5)->DrawOnScreen(x, y);
			break;
		case 6:
			s->Get(SPRITE_6)->DrawOnScreen(x, y);
			break;
		case 7:
			s->Get(SPRITE_7)->DrawOnScreen(x, y);
			break;
		case 8:
			s->Get(SPRITE_8)->DrawOnScreen(x, y);
			break;
		case 9:
			s->Get(SPRITE_9)->DrawOnScreen(x, y);
			break;
	}
}
