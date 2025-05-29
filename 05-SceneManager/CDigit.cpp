#include "CDigit.h"
#include "debug.h"

void CDigit::Render()
{
	CSprites* s = CSprites::GetInstance();

	if (isOnScreen == true)
	{
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
	else
	{
		switch (value)
		{
		case 0:
			s->Get(SPRITE_0)->Draw(x, y);
			break;
		case 1:
			s->Get(SPRITE_1)->Draw(x, y);
			break;
		case 2:
			s->Get(SPRITE_2)->Draw(x, y);
			break;
		case 3:
			s->Get(SPRITE_3)->Draw(x, y);
			break;
		case 4:
			s->Get(SPRITE_4)->Draw(x, y);
			break;
		case 5:
			s->Get(SPRITE_5)->Draw(x, y);
			break;
		case 6:
			s->Get(SPRITE_6)->Draw(x, y);
			break;
		case 7:
			s->Get(SPRITE_7)->Draw(x, y);
			break;
		case 8:
			s->Get(SPRITE_8)->Draw(x, y);
			break;
		case 9:
			s->Get(SPRITE_9)->Draw(x, y);
			break;
		}
	}
}