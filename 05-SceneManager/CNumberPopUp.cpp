#include "CNumberPopUp.h"
#include "debug.h"
#include "PlayScene.h"

CNumberPopUp::CNumberPopUp(float x, float y, int digitCount, int value)	: CNumber(x, y, digitCount)
{
	this->value = value;
	timer = 0;
	vy = -SPEED_Y;

	for (int i = 0; i < digitCount; i++)
	{
		CDigit* digit = dynamic_cast<CDigit*>(digits[i]);
		digit->SetPosition(x - i * DIGIT_POP_UP_SPACING, y);
		digit->SetIsOnScreen(false);
	}
}

void CNumberPopUp::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	y += vy * dt; // Update vertical position based on velocity
	DebugOut(L"y of numberpopup: %.3f \n", y);
	for (int i = 0; i < digitCount; i++)
	{
		digits[i]->SetPosition(x - i * DIGIT_POP_UP_SPACING, y);
		DebugOut(L"y of digitpopup: %.3f \n", y);
	}

	//CNumber::Update(dt, coObjects);

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

	if(timer >= APPEAR_TIME)
	{
		this->Delete();
	}
	else
	{
		timer += dt; // Increment timer
	}
}

void CNumberPopUp::Render()
{
	CNumber::Render();
}
