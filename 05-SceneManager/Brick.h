#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_BRICK 10000
#define ID_ANI_BRICK_USED 10001

#define BRICK_WIDTH 16
#define BRICK_BBOX_WIDTH 16
#define BRICK_BBOX_HEIGHT 16

#define BRICK_BOUNCING_SPEED 0.1f
#define BRICK_BOUNCE_HEIGHT 5


#define BRICK_STATE_IDLE 0
#define BRICK_STATE_USED 100
#define BRICK_STATE_BROKEN 200
#define BRICK_STATE_BOUNCING_UP 300
#define BRICK_STATE_BOUNCING_DOWN 400

class CBrick : public CGameObject {
protected:
	ULONGLONG bounce_start;
	float y_start;
	//int itemType;	
	//CGameObject* spawnedItem;

	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);

	virtual void OnNoCollision(DWORD dt);

	void Bouncing();

public:
	CBrick(float x, float y);
	void SetState(int state);
};