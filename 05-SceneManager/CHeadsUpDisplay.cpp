#include "CHeadsUpDisplay.h"
#include "Game.h"
#include "PlayScene.h"

void CHeadsUpDisplay::Render()
{
	CSprites* s = CSprites::GetInstance();
	s->Get(this->spriteId)->DrawOnScreen(x, y);

	CPlayScene* playScene = dynamic_cast<CPlayScene*>(CGame::GetInstance()->GetCurrentScene());
	
	CMario* player = dynamic_cast<CMario*>(playScene->GetPlayer());
	float powerCount = player->GetRunPower() / MARIO_MAX_RUN_POWER * 6;

	//Run power bar
	if (powerCount > 0)
	{
		for (int i = 0; i <= powerCount; i++)
		{
			if (i == powerCount && powerCount == 6)
			{
				if((GetTickCount64() / 100) % 2 == 0) //Blink effect
					s->Get(SPRITE_FULL_POWER)->DrawOnScreen(x - 105 + i * 9, y - 16);
			}
			else
				s->Get(SPRITE_POWER_ACTIVE)->DrawOnScreen(x - 110 + i * 9, y - 16);
		}
	}

	// Draw the numbers
	numberCoin->Render();
	numberPoint->Render();
	numberTime->Render();
}

void CHeadsUpDisplay::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	// Update the number of coins, time, points;
	CPlayScene* playScene = dynamic_cast<CPlayScene*>(CGame::GetInstance()->GetCurrentScene());
	CMario* player = dynamic_cast<CMario*>(playScene->GetPlayer());
	
	numberCoin->SetValue(player->GetCoins());
	numberCoin->Update(dt, coObjects);

	numberTime->SetValue(player->GetPlayTime());
	numberTime->Update(dt, coObjects);

	numberPoint->SetValue(player->GetPoints());
	numberPoint->Update(dt, coObjects);
}
