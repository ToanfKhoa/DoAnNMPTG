#pragma once
#include "GameObject.h"

#define EFFECT_TIME 100
#define ID_ANIMATION_EFFECT 21000

class CEffect : public CGameObject
{
protected:
	DWORD timer;
public:
	CEffect(float x, float y) : CGameObject(x, y) { timer = 0; };
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
};

