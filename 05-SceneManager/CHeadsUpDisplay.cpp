#include "CHeadsUpDisplay.h"
#include "Game.h"
#include "PlayScene.h"

void CHeadsUpDisplay::Render()
{
	CSprites* s = CSprites::GetInstance();

	numberCoin->Render();
	numberPoint->Render();
	numberTime->Render();
	s->Get(this->spriteId)->DrawOnScreen(x, y);
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
