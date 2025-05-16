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
#define KOOPA_BBOX_HEIGHT 24
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

#define ID_ANI_GREEN_KOOPA_WALKING_LEFT 15008
#define ID_ANI_GREEN_KOOPA_WALKING_RIGHT 15009
#define ID_ANI_GREEN_KOOPA_SHELL_UPRIGHT_IDLE 15010
#define ID_ANI_GREEN_KOOPA_SHELL_UPRIGHT_MOVING 15011
#define ID_ANI_GREEN_KOOPA_SHELL_UPRIGHT_REVIVE 15012
#define ID_ANI_GREEN_KOOPA_SHELL_FLIPPED_IDLE 15013
#define ID_ANI_GREEN_KOOPA_SHELL_FLIPPED_MOVING 15014
#define ID_ANI_GREEN_KOOPA_SHELL_FLIPPED_REVIVE 15015

class CKoopa :public CGameObject
{
protected:
	float ay;
	boolean isFlipped;
	ULONGLONG shellStartTime;
	CSensorBox* sensorBox;
	boolean isGreen;
	
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void RenderRedKoopa();
	virtual void RenderGreenKoopa();

	virtual int IsCollidable() { return state!=KOOPA_STATE_DIE; }
	virtual int IsOverlappable() { return state!=KOOPA_STATE_DIE; }

	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
	virtual void OnOverlapWith(LPCOLLISIONEVENT e);
	virtual void CheckAndChangeState();
	virtual void UpdateSensorBoxPosition();

	virtual void OnCollisionWithGoomba(LPCOLLISIONEVENT e);
	virtual void OnCollisionWithParaGoomba(LPCOLLISIONEVENT e);
	virtual void OnCollisionWithQuestionBlock(LPCOLLISIONEVENT e);
	virtual void OnCollisionWithVenus(LPCOLLISIONEVENT e);
	virtual void OnCollisionWithParaKoopa(LPCOLLISIONEVENT e);
	virtual void OnCollisionWithKoopa(LPCOLLISIONEVENT e);
	virtual void OnCollisionWithBrick(LPCOLLISIONEVENT e);

	virtual void OnOverlapWithGoomba(LPCOLLISIONEVENT e);
	virtual void OnOverlapWithParaGoomba(LPCOLLISIONEVENT e);
	virtual void OnOverlapWithVenus(LPCOLLISIONEVENT e);
	virtual void OnOverlapWithParaKoopa(LPCOLLISIONEVENT e);
	virtual void OnOverlapWithKoopa(LPCOLLISIONEVENT e);
	virtual void OnOverlapWithBrick(LPCOLLISIONEVENT e);
	virtual void OnOverlapWithQuestionBlock(LPCOLLISIONEVENT e);
	virtual void OnOverlapWithPipe(LPCOLLISIONEVENT e);
	virtual void OnOverlapWithGround(LPCOLLISIONEVENT e);
	virtual void OnOverlapWithWoodBlock(LPCOLLISIONEVENT e);

public:
	CKoopa(float x, float y, boolean isGreen);
	virtual void SetState(int nextState);
	virtual void AlignYOnTransform();
};

