#pragma once
#include "GameObject.h"
#include "CDigit.h"

#define DIGIT_SPACING 10

class CNumber : public CGameObject
{
protected:
	int digitCount;
	int value;
	vector<CGameObject*> digits;
public:
	CNumber(float x, float y, int digitCount) : CGameObject(x, y)
	{
		this->digitCount = digitCount;
		this->value = 0;
		for (int i = 0; i < digitCount; i++)
		{
			CGameObject* digit = new CDigit(x + i * DIGIT_SPACING, y);
			digits.push_back(digit);
		}
	}

	void Update();
	void SetValue(int value) { this->value = value; }
	int GetValue() { return this->value; }
	int GetDigitCount() { return this->digitCount; }
};

