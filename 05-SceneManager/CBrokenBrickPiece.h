#pragma once
#include "GameObject.h"

#define BROKEN_PIECE_GRAVITY 0.001f
#define BROKEN_PIECE_EXIST_TIME 1000

class CBrokenBrickPiece :public CGameObject
{
protected:
	float ay;
	ULONGLONG existStartTime;
public:
	CBrokenBrickPiece(float x, float y, float speed, float bounceSpeed) : CGameObject(x, y) 
	{
		this->ay = BROKEN_PIECE_GRAVITY;
		this->vx = speed;
		this->vy = bounceSpeed;
		this->existStartTime = GetTickCount64();
	}

	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b) {};
	int IsBlocking() { return 0; }
};

