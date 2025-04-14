#include "CQuestionBlock.h"
#include "debug.h"
void CQuestionBlock::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	if (state == QUESTIONBLOCK_STATE_IDLE)
	{
		animations->Get(ID_ANI_QUESTIONBLOCK)->Render(x, y);
	}
	else
	{
		animations->Get(ID_ANI_QUESTIONBLOCK_USED)->Render(x, y);
	}

}

void CQuestionBlock::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (state != QUESTIONBLOCK_STATE_USED)
	{
		Bouncing();

		CCollision::GetInstance()->Process(this, dt, coObjects);
	}


	CGameObject::Update(dt, coObjects);
}


void CQuestionBlock::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - QUESTIONBLOCK_BBOX_WIDTH / 2;
	t = y - QUESTIONBLOCK_BBOX_HEIGHT / 2;
	r = l + QUESTIONBLOCK_BBOX_WIDTH;
	b = t + QUESTIONBLOCK_BBOX_HEIGHT;
}

void CQuestionBlock::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}

//int CQuestionBlock::IsDirectionColliable(float nx, float ny)
//{
//	if (nx == 0 && ny == 1 && state != QUESTIONBLOCK_STATE_USED) return 1;
//	else return 0;
//}

void CQuestionBlock::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case QUESTIONBLOCK_STATE_USED:
		vx = 0;
		vy = 0;
		break;
	case QUESTIONBLOCK_STATE_IDLE:
		vx = 0;
		vy = 0;
		break;
	case QUESTIONBLOCK_STATE_BOUNCING_UP:
		vy = -QUESTIONBLOCK_BOUNCING_SPEED;
		bounce_start = GetTickCount64();
		break;
	case QUESTIONBLOCK_STATE_BOUNCING_DOWN:
		vy = QUESTIONBLOCK_BOUNCING_SPEED;
		break;

	}
}

void CQuestionBlock::Bouncing() 
{
	if (state == QUESTIONBLOCK_STATE_BOUNCING_UP && GetTickCount64() - bounce_start >= QUESTIONBLOCK_BOUNCE_TIME / 2)
	{
		if (y <= y_start - QUESTIONBLOCK_BOUNCE_HEIGTH)
		{
			y = y_start - QUESTIONBLOCK_BOUNCE_HEIGTH;
			SetState(QUESTIONBLOCK_STATE_BOUNCING_DOWN);
		}
	}

	else if (GetState() == QUESTIONBLOCK_STATE_BOUNCING_DOWN && GetTickCount64() - bounce_start >= QUESTIONBLOCK_BOUNCE_TIME / 2)
	{
		if (y >= y_start)
		{
			y = y_start;
			SetState(QUESTIONBLOCK_STATE_USED);
		}
	}
}