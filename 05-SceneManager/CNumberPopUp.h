#pragma once
#include "CNumber.h"

#define APPEAR_TIME 1000.0f // Time in milliseconds for the number to appear
#define SPEED_Y 0.01f;

class CNumberPopUp : public CNumber
{
protected:
	DWORD timer; 

public:
	CNumberPopUp(float x, float y, int digitCount) : CNumber(x, y, digitCount)
	{
		this->value = 0;
		timer = 0;
		vy = -SPEED_Y;
		for (int i = 0; i < digitCount; i++)
		{
			CGameObject* digit = new CDigit(x - i * DIGIT_SPACING, y);
			digits.push_back(digit);
		}
	}

	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) override;
};

