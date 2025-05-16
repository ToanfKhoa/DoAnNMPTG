#pragma once
#include "GameObject.h"
#include "CDigit.h"

#define DIGIT_SPACING 8

class CNumber : public CGameObject
{
protected:
	int digitCount;
	int value;
	vector<CGameObject*> digits;
public:
	CNumber(float x, float y, int digitCount);

	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void SetValue(int value) { this->value = value; }
	int GetValue() { return this->value; }
	int GetDigitCount() { return this->digitCount; }
	void GetBoundingBox(float& left, float& top, float& right, float& bottom) {};
	void Render();
};

