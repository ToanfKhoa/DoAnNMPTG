#pragma once
#include "GameObject.h"

class CMarioHitBox : public CGameObject
{
protected:
	int bboxWidth;
	int bboxHeight;
	BOOLEAN isActive;
public:
	CMarioHitBox(float x, float y, int BBOX_WIDTH, int BBOX_HEIGHT);
	void Render() { /*RenderBoundingBox();*/ }
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	void GetBoundingBox(float& l, float& t, float& r, float& b);

	void OnOverlapWith(LPCOLLISIONEVENT e);
	void OnOverlapWithGoomba(LPCOLLISIONEVENT e);
	void OnOverlapWithParaGoomba(LPCOLLISIONEVENT e);
	void OnOverlapWithVenus(LPCOLLISIONEVENT e);
	void OnOverlapWithParaKoopa(LPCOLLISIONEVENT e);
	void OnOverlapWithPiranha(LPCOLLISIONEVENT e);
	void OnOverlapWithKoopa(LPCOLLISIONEVENT e);
	void OnOverlapWithBrick(LPCOLLISIONEVENT e);
	void OnOverlapWithQuestionBlock(LPCOLLISIONEVENT e);
	void OnOverlapWithBoomerangBros(LPCOLLISIONEVENT e);

	int IsBlocking() { return 0; }
	int IsCollidable() { return 1; }
	int IsOverlappable() { return 1; }
	void SetIsActive(BOOLEAN b) { isActive = b; }
};

