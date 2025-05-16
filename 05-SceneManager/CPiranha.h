#pragma once
#include "GameObject.h"
#include "PlayScene.h"

#define PIRANHA_SPEED 0.05f

#define PIRANHA_BBOX_WIDTH 20
#define PIRANHA_BBOX_HEIGHT 10
#define PIRANHA_FIRE_DISTANCE_MAX 150
#define PIRANHA_FIRE_DISTANCE_MIN 16
#define PIRANHA_MOVING_OFFSET 29

#define PIRANHA_STATE_HIDE 100
#define PIRANHA_STATE_UP 200
#define PIRANHA_STATE_DOWN 300
#define PIRANHA_STATE_APPEAR 400
#define PIRANHA_STATE_DIE 500

#define ID_ANI_PIRANHA 18000
#define ID_ANI_PIRANHA_DIE 5204 //Use the same animation as Venus die

#define PIRANHA_HIDE_TIME 1000
#define PIRANHA_APPEAR_TIME 1000
#define PIRANHA_DIE_TIME 400

class CPiranha : public CGameObject
{
protected:
	bool isPlayerInRange;
	float y_start;

	DWORD timer;
	DWORD dieTimer;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }


public:
	CPiranha(float x, float y);
	virtual void SetState(int state);
	void UpAndDown(DWORD dt);
	void TrackPlayerNearby();
};

