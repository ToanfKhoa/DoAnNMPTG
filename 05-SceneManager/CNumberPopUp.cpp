#include "CNumberPopUp.h"

void CNumberPopUp::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	y += vy * dt; // Update vertical position based on velocity
	CNumber::Update(dt, coObjects);

	if(timer >= APPEAR_TIME)
	{
		this->Delete();
	}
	else
	{
		timer += dt; // Increment timer
	}
}
