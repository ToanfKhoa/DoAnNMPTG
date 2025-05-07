#pragma once
#include "GameObject.h"

#define BROKEN_PIECE_GRAVITY 0.002f
#define BROKEN_PIECE_SPEED 0.05f
#define BROKEN_PIECE_EXIST_TIME 500
#define BROKEN_PIECE_BOUNCE_SPEED 0.2f

class CBrokenBrickPiece :public CGameObject
{
protected:
	float ay;
public:
	CBrokenBrickPiece(float x, float y) : CGameObject(x, y) {}

	void Render();
	void Update(DWORD dt) {};
	void GetBoundingBox(float& l, float& t, float& r, float& b) {};
};

