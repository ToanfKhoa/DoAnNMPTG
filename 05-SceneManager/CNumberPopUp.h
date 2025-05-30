#pragma once
#include "CNumber.h"

#define APPEAR_TIME 1000.0f // Time in milliseconds for the number to appear
#define SPEED_Y 0.02f;

#define DIGIT_POP_UP_SPACING 4

class CNumberPopUp : public CNumber
{
protected:
	DWORD timer; 

public:
	CNumberPopUp(float x, float y, int digitCount, int value);

	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) override;
	void Render();
};

