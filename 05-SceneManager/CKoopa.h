#pragma once
#include "GameObject.h"
#include "CSensorBox.h"

#define KOOPA_GRAVITY 0.002f
#define KOOPA_WALKING_SPEED 0.05f
#define KOOPA_SHELL_MOVING_SPEED 0.2f
#define KOOPA_REVIVE_TIME 8000
#define KOOPA_REVIVE_BLINK_TIME 2000
#define KOOPA_BOUNCE_SPEED 0.4f

#define KOOPA_BBOX_WIDTH 16
#define KOOPA_BBOX_HEIGHT 26
#define KOOPA_BBOX_SHELL_WIDTH 16
#define KOOPA_BBOX_SHELL_HEIGHT 14

#define KOOPA_STATE_WALKING_LEFT 0
#define KOOPA_STATE_WALKING_RIGHT 1
#define KOOPA_STATE_SHELL_IDLE 2
#define KOOPA_STATE_SHELL_MOVING_LEFT 3
#define KOOPA_STATE_SHELL_MOVING_RIGHT 4
#define KOOPA_STATE_SHELL_REVIVE 5
#define KOOPA_STATE_BEING_HELD 6
#define KOOPA_STATE_DIE 7

#define ID_ANI_KOOPA_WALKING_LEFT 15000
#define ID_ANI_KOOPA_WALKING_RIGHT 15001
#define ID_ANI_KOOPA_SHELL_UPRIGHT_IDLE 15002
#define ID_ANI_KOOPA_SHELL_UPRIGHT_MOVING 15003
#define ID_ANI_KOOPA_SHELL_UPRIGHT_REVIVE 15004
#define ID_ANI_KOOPA_SHELL_FLIPPED_IDLE 15005
#define ID_ANI_KOOPA_SHELL_FLIPPED_MOVING 15006
#define ID_ANI_KOOPA_SHELL_FLIPPED_REVIVE 15007

class CKoopa :public CGameObject
{
protected:
	float ay;
	boolean isFlipped;
	ULONGLONG shellStartTime;
	CSensorBox * sensorBox;
	
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();

	int IsCollidable() { return state!=KOOPA_STATE_DIE; }
	int IsOverlappable() { return state!=KOOPA_STATE_DIE; }

	int IsBlocking() { return 0; }
	void OnNoCollision(DWORD dt);

	void OnCollisionWith(LPCOLLISIONEVENT e);
	void OnOverlapWith(LPCOLLISIONEVENT e);
	void CheckAndChangeState();
	void UpdateSensorBoxPosition();

	void OnCollisionWithGoomba(LPCOLLISIONEVENT e);
	void OnCollisionWithParaGoomba(LPCOLLISIONEVENT e);
	void OnCollisionWithQuestionBlock(LPCOLLISIONEVENT e);
	void OnCollisionWithVenus(LPCOLLISIONEVENT e);
	void OnCollisionWithKoopa(LPCOLLISIONEVENT e);
	void OnCollisionWithBrick(LPCOLLISIONEVENT e);

	void OnOverlapWithGoomba(LPCOLLISIONEVENT e);
	void OnOverlapWithParaGoomba(LPCOLLISIONEVENT e);
	void OnOverlapWithVenus(LPCOLLISIONEVENT e);
	void OnOverlapWithKoopa(LPCOLLISIONEVENT e);
	void OnOverlapWithBrick(LPCOLLISIONEVENT e);
	void OnOverlapWithQuestionBlock(LPCOLLISIONEVENT e);
	void OnOverlapWithPipe(LPCOLLISIONEVENT e);
	void OnOverlapWithGround(LPCOLLISIONEVENT e);
	void OnOverlapWithWoodBlock(LPCOLLISIONEVENT e);

public:
	CKoopa(float x, float y);
	void SetState(int nextState);
	void AlignYOnTransform();
};

