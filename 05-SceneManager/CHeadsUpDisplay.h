#pragma once
#include "GameObject.h"
class CHeadsUpDisplay :public CGameObject
{
protected:
	int spriteId;
public:
	CHeadsUpDisplay(float x, float y, int spriteId) : CGameObject(x, y)
	{
		this->spriteId = spriteId;
	}

	void Render();
	void Update(DWORD dt) {};
	void GetBoundingBox(float& l, float& t, float& r, float& b) {};
};

