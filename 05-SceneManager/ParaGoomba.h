#pragma once
#include "GameObject.h"
#include "Goomba.h"

#define PARAGOOMBA_GRAVITY 0.002f
#define PARAGOOMBA_WALKING_SPEED 0.05f
#define PARAGOOMBA_FLYING_SPEED 0.2f
#define PARAGOOMBA_JUMPING_SPEED 0.15f

#define PARAGOOMBA_BBOX_WIDTH 16
#define PARAGOOMBA_BBOX_HEIGHT 14
#define PARAGOOMBA_BBOX_HEIGHT_DIE 7

#define PARAGOOMBA_STATE_WALKING 300
#define PARAGOOMBA_STATE_FLYING_UP 400
#define PARAGOOMBA_STATE_FLYING_DOWN 500

#define ID_ANI_PARAGOOMBA_WALKING 5100
#define ID_ANI_PARAGOOMBA_FLYING 5101
#define ID_ANI_PARAGOOMBA_DIE 5102
#define ID_ANI_PARAGOOMBA_ISGOOMBA_WALK 5103

#define PARAGOOMBA_FLY_TIME 500
#define PARAGOOMBA_FLY_PERIOD 1000
#define PARAGOOMBA_JUMP_PERIOD 300

class CParaGoomba : public CGoomba
{
protected:
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	boolean isGoomba;
	ULONGLONG fly_start;
	DWORD jumpTimer;
public:
	CParaGoomba(float x, float y);
	void SetState(int state);
	void Flying();
	boolean GetIsGoomba() { return isGoomba; }
	void TurnIntoGoomba();
};