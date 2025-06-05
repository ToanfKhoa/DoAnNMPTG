#include "CItemRanDom.h"
#include "Game.h"
#include "CDecoration.h"
#include "PlayScene.h"

#define COURSE_CLEAR 102014
#define YOU_GOT 102015

#define CARD_MUSHROOM 102016
#define CARD_FLOWER 102017
#define CARD_STAR 102018

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

	if(this->state == ITEMRANDOM_STATE_MUSHROOM_FLY ||
	   this->state == ITEMRANDOM_STATE_FLOWER_FLY ||
	   this->state == ITEMRANDOM_STATE_STAR_FLY)
	{
		if (GetTickCount64() - start_time > ITEMRANDOM_WAIT_TIME)
		{
			LoadNextScene();
			return;
		}
		if (GetTickCount64() - start_time > ITEMRANDOM_SPAWN_TEXT_TIME && isSpawnText==0)
		{
			isSpawnText = 1;
			SpawnText(x - 20, y_start - 64, COURSE_CLEAR);
		}
		if (GetTickCount64() - start_time > ITEMRANDOM_SPAWN_TEXT_TIME + 500 && isSpawnText==1)
		{
			CPlayScene* playScene = dynamic_cast<CPlayScene*>(CGame::GetInstance()->GetCurrentScene());
			CMario* player = dynamic_cast<CMario*>(playScene->GetPlayer());
			player->AddCard(state == ITEMRANDOM_STATE_MUSHROOM_FLY ? 1 : state == ITEMRANDOM_STATE_FLOWER_FLY ? 2 : 3);

			isSpawnText = 2;
			SpawnText(x - 36, y_start - 38, YOU_GOT);
			SpawnText(x + 43, y_start - 38, state == ITEMRANDOM_STATE_MUSHROOM_FLY ? CARD_MUSHROOM :
				state == ITEMRANDOM_STATE_FLOWER_FLY ? CARD_FLOWER : CARD_STAR);
		}
	}
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

void CItemRandom::LoadNextScene()
{
	CGame* game = CGame::GetInstance();
	game->InitiateSwitchScene(nextScene_id);
}

void CItemRandom::SpawnText( float obj_x, float obj_y, int spriteId)
{
	CDecoration* text = new CDecoration(obj_x, obj_y, spriteId);
	CPlayScene* scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
	scene->AddObject(text);
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
		start_time = GetTickCount64();
		vy = ITEMRANDOM_FLY_SPEED;
		break;

	default:
		break;
	}
}
