#include "CDigit.h"

void CDigit::Render()
{
	switch (value) 
	{
		case 0:
			CAnimations::GetInstance()->Get(SPRITE_0)->Render(x, y);
			break;
		case 1:
			CAnimations::GetInstance()->Get(SPRITE_1)->Render(x, y);
			break;
		case 2:
			CAnimations::GetInstance()->Get(SPRITE_2)->Render(x, y);
			break;
		case 3:
			CAnimations::GetInstance()->Get(SPRITE_3)->Render(x, y);
			break;
		case 4:
			CAnimations::GetInstance()->Get(SPRITE_4)->Render(x, y);
			break;
		case 5:
			CAnimations::GetInstance()->Get(SPRITE_5)->Render(x, y);
			break;
		case 6:
			CAnimations::GetInstance()->Get(SPRITE_6)->Render(x, y);
			break;
		case 7:
			CAnimations::GetInstance()->Get(SPRITE_7)->Render(x, y);
			break;
		case 8:
			CAnimations::GetInstance()->Get(SPRITE_8)->Render(x, y);
			break;
		case 9:
			CAnimations::GetInstance()->Get(SPRITE_9)->Render(x, y);
			break;
	}
}
