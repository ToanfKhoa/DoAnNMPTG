#include "CNumber.h"
#include "Game.h"
#include "PlayScene.h"

CNumber::CNumber(float x, float y, int digitCount):CGameObject(x, y)
{
	this->digitCount = digitCount;
	this->value = 0;
	for (int i = 0; i < digitCount; i++)
	{
		CDigit* digit = new CDigit(x - i * DIGIT_SPACING, y);
		digit->SetIsOnScreen(true);
		digits.push_back(digit);
	}
}

void CNumber::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CPlayScene* currentScene = dynamic_cast<CPlayScene*>(CGame::GetInstance()->GetCurrentScene());

	for (int i = 0; i < digitCount; i++)
	{
		int digitValue = (value / (int)pow(10, i)) % 10;
		CDigit* digit = dynamic_cast<CDigit*>(digits[i]);
		if (digit)
		{
			digit->SetValue(digitValue);
		}
	}
}

void CNumber::Render()
{
	for (int i = 0; i < digits.size(); i++)
	{
		digits[i]->Render();
	}
}
