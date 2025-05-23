#include "CItemRanDom.h"

void CItemRanDom::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	y += vy * dt;
	CheckAndChangeState();

	CGameObject::Update(dt);
}

void CItemRanDom::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - ITEMRANDOM_BBOX_WIDTH / 2;
	t = y - ITEMRANDOM_BBOX_HEIGHT / 2;
	r = l + ITEMRANDOM_BBOX_WIDTH;
	b = t + ITEMRANDOM_BBOX_HEIGHT;
}

void CItemRanDom::CheckAndChangeState()
{
	if (GetTickCount64() - start_time > ITEMRANDOM_RANDOM_TIME)
	{
		switch (state)
		{
		case ITEMRANDOM_STATE_MUSHROOM:
			SetState(ITEMRANDOM_STATE_FLOWER);
			break;
		case ITEMRANDOM_STATE_FLOWER:
			SetState(ITEMRANDOM_STATE_STAR);
			break;
		case ITEMRANDOM_STATE_STAR:
			SetState(ITEMRANDOM_STATE_MUSHROOM);
			break;
		default:
			break;
		}
	}
}

void CItemRanDom::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case ITEMRANDOM_STATE_MUSHROOM:
	case ITEMRANDOM_STATE_FLOWER:
	case ITEMRANDOM_STATE_STAR:
		vy = 0;
		start_time = GetTickCount64();
		break;

	case ITEMRANDOM_STATE_MUSHROOM_FLY:
	case ITEMRANDOM_STATE_FLOWER_FLY:
	case ITEMRANDOM_STATE_STAR_FLY:
		vy = ITEMRANDOM_FLY_SPEED;
		break;
	default:
		break;
	}
}
