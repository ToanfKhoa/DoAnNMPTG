#pragma once
#include "GameObject.h"

#define VENUS_SPEED 0.05f

#define VENUS_BBOX_WIDTH 20
#define VENUS_BBOX_HEIGHT 26
#define VENUS_FIRE_DISTANCE_MAX 150
#define VENUS_FIRE_DISTANCE_MIN 16
#define VENUS_MOVING_OFFSET 34

#define VENUS_STATE_HIDE 100
#define VENUS_STATE_UP 200
#define VENUS_STATE_DOWN 300
#define VENUS_STATE_FIRE 400
#define VENUS_STATE_DIE 500

#define ID_ANI_VENUS_TOPLEFT 5200
#define ID_ANI_VENUS_TOPRIGHT 5201
#define ID_ANI_VENUS_BOTLEFT 5202
#define ID_ANI_VENUS_BOTRIGHT 5203
#define ID_ANI_VENUS_DIE 5204

#define ID_ANI_GREEN_VENUS_TOPLEFT 5210
#define ID_ANI_GREEN_VENUS_TOPRIGHT 5211
#define ID_ANI_GREEN_VENUS_BOTLEFT 5212
#define ID_ANI_GREEN_VENUS_BOTRIGHT 5213
#define ID_ANI_GREEN_VENUS_DIE 5214

#define VENUS_HIDE_TIME 1000
#define VENUS_APPEAR_TIME 1000
#define VENUS_DIE_TIME 400

class CBulletVenus;            
typedef CBulletVenus* LPBULLETVENUS;

class CVenus : public CGameObject
{
protected:
	int direction_x;
	int direction_y;
	LPBULLETVENUS bullet;
	bool isPlayerInRange;
	float y_start;
	BOOLEAN isGreen;

	DWORD timer;
	DWORD dieTimer;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }


public:
	CVenus(float x, float y, BOOLEAN isGreen);
	virtual void SetState(int state);
	void UpAndDown(DWORD dt);
	void Fire();
	void TrackPlayerNearby();
	void SetDirection(int x, int y) { this->direction_x = x; this->direction_y = y; }
};