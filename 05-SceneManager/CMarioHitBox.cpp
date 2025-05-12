#include "CMarioHitBox.h"
#include "CVenus.h"
#include "Goomba.h"
#include "ParaGoomba.h"
#include "CKoopa.h"
#include "CQuestionBlock.h"
#include "Brick.h"

CMarioHitBox::CMarioHitBox(float x, float y, int BBOX_WIDTH, int BBOX_HEIGHT)
{
	this->x = x;
	this->y = y;
	this->bboxWidth = BBOX_WIDTH;
	this->bboxHeight = BBOX_HEIGHT;
	isActive = false;
}

void CMarioHitBox::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	DebugOut(L"isactive %d\n", isActive);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CMarioHitBox::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - bboxWidth / 2;
	t = y - bboxHeight / 2;
	r = l + bboxWidth;
	b = t + bboxHeight;
}


void CMarioHitBox::OnOverlapWith(LPCOLLISIONEVENT e)
{
	if (!isActive) return;
	DebugOut(L"overlap\n");
	if (dynamic_cast<CGoomba*>(e->obj))
		OnOverlapWithGoomba(e);
	else if (dynamic_cast<CVenus*>(e->obj))
		OnOverlapWithVenus(e);
	else if (dynamic_cast<CKoopa*>(e->obj))
		OnOverlapWithKoopa(e);
	else if (dynamic_cast<CBrick*>(e->obj))
		OnOverlapWithBrick(e);
	else if (dynamic_cast<CQuestionBlock*>(e->obj))
		OnOverlapWithQuestionBlock(e);
}

void CMarioHitBox::OnOverlapWithGoomba(LPCOLLISIONEVENT e)
{

	CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);
	if (goomba->GetState() == GOOMBA_STATE_DIE || goomba->GetState() == GOOMBA_STATE_BOUNCE_DEATH) return;

	SetState(KOOPA_STATE_DIE);

	goomba->SetState(GOOMBA_STATE_BOUNCE_DEATH);

}

void CMarioHitBox::OnOverlapWithParaGoomba(LPCOLLISIONEVENT e)
{
	CParaGoomba* paraGoomba = dynamic_cast<CParaGoomba*>(e->obj);
	if (paraGoomba->GetState() == GOOMBA_STATE_DIE || paraGoomba->GetState() == GOOMBA_STATE_BOUNCE_DEATH) return;

	SetState(KOOPA_STATE_DIE);

	paraGoomba->SetState(GOOMBA_STATE_BOUNCE_DEATH);
}

void CMarioHitBox::OnOverlapWithVenus(LPCOLLISIONEVENT e)
{
	SetState(KOOPA_STATE_DIE);

	CVenus* venus = dynamic_cast<CVenus*>(e->obj);

	venus->SetState(VENUS_STATE_DIE);
}

void CMarioHitBox::OnOverlapWithKoopa(LPCOLLISIONEVENT e)
{

	CKoopa* koopa = dynamic_cast<CKoopa*>(e->obj);

	if (koopa->GetState() == KOOPA_STATE_DIE || koopa->GetState() == KOOPA_STATE_DIE) return;

	SetState(KOOPA_STATE_DIE);

	if (koopa->GetState() == KOOPA_STATE_SHELL_MOVING_LEFT || koopa->GetState() == KOOPA_STATE_SHELL_MOVING_RIGHT)
	{
		koopa->SetState(KOOPA_STATE_DIE);
	}
	else if (koopa->GetState() == KOOPA_STATE_WALKING_LEFT || koopa->GetState() == KOOPA_STATE_WALKING_RIGHT || koopa->GetState() == KOOPA_STATE_SHELL_IDLE)
	{
		koopa->SetState(KOOPA_STATE_DIE);
	}
}

void CMarioHitBox::OnOverlapWithBrick(LPCOLLISIONEVENT e)
{
	CBrick* brick = dynamic_cast<CBrick*>(e->obj);
	if(brick->GetState() == BRICK_STATE_IDLE)
		brick->SetState(BRICK_STATE_BROKEN);
}

void CMarioHitBox::OnOverlapWithQuestionBlock(LPCOLLISIONEVENT e)
{
	DebugOut(L"brick\n");
	CQuestionBlock* questionBlock = dynamic_cast<CQuestionBlock*>(e->obj);
	if (questionBlock->GetState() == QUESTIONBLOCK_STATE_IDLE)
		questionBlock->SetState(QUESTIONBLOCK_STATE_BOUNCING_UP);
}




