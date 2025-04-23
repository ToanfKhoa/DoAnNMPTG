#include "CPit.h"
#include "Mario.h"

CPit::CPit(float x, float y, int BBOX_WIDTH, int BBOX_HEIGHT)
{
	this->x = x;
	this->y = y;
	this->bboxWidth = BBOX_WIDTH;
	this->bboxHeight = BBOX_HEIGHT;
}

void CPit::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CPit::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - bboxWidth / 2;
	t = y - bboxHeight / 2;
	r = l + bboxWidth;
	b = t + bboxHeight;
}
void CPit::OnCollisionWith(LPCOLLISIONEVENT e)
{
	CMario* mario = dynamic_cast<CMario*>(e->obj);
	DebugOut(L"Pit collision with mario\n");
	mario->SetState(MARIO_STATE_DIE);
	DebugOut(L"Pit, mario state %d\n", mario->GetState());
}
