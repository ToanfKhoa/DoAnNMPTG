#include "CItemRanDom.h"

void CItemRandom::Render()
{
	int aniId;
	switch (state)
	{
	case ITEMRANDOM_STATE_MUSHROOM:
		aniId = ID_ANI_ITEMRANDOM_MUSHROOM;
		break;
	case ITEMRANDOM_STATE_FLOWER:
		aniId = ID_ANI_ITEMRANDOM_FLOWER;
		break;
	case ITEMRANDOM_STATE_STAR:
		aniId = ID_ANI_ITEMRANDOM_STAR;
		break;
	case ITEMRANDOM_STATE_MUSHROOM_FLY:
		aniId = ID_ANI_ITEMRANDOM_MUSHROOM_FLY;
		break;
	case ITEMRANDOM_STATE_FLOWER_FLY:
		aniId = ID_ANI_ITEMRANDOM_FLOWER_FLY;
		break;
	case ITEMRANDOM_STATE_STAR_FLY:
		aniId = ID_ANI_ITEMRANDOM_STAR_FLY;
		break;
	default:
		aniId = ID_ANI_ITEMRANDOM_MUSHROOM;
	}

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
}

void CItemRandom::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	y += vy * dt;
	CheckAndChangeState();

	CGameObject::Update(dt);
}

void CItemRandom::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - ITEMRANDOM_BBOX_WIDTH / 2;
	t = y - ITEMRANDOM_BBOX_HEIGHT / 2;
	r = l + ITEMRANDOM_BBOX_WIDTH;
	b = t + ITEMRANDOM_BBOX_HEIGHT;
}

void CItemRandom::CheckAndChangeState()
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

void CItemRandom::SetState(int state)
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
