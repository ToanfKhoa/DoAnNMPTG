#include "CQuestionBlock.h"
#include "CPowerUpItem.h"
#include "CCoinItem.h"
#include "PlayScene.h"
#include "debug.h"

CQuestionBlock::CQuestionBlock(float x, float y, int itemType) : CGameObject(x, y)
{
	this->y_start = y;
	this->state = QUESTIONBLOCK_STATE_IDLE;

	this->itemType = itemType;
	if ( itemType == QUESTIONBLOCK_ITEM_TYPE_POWERUP )
	{
		this->spawnedItem = new CPowerUpItem(x, y);

		CPlayScene* playScene = dynamic_cast<CPlayScene*>(CGame::GetInstance()->GetCurrentScene());
		if (playScene != NULL)
		{
			playScene->AddObject(spawnedItem);
		}
	} else if( itemType == QUESTIONBLOCK_ITEM_TYPE_COIN )
	{
		this->spawnedItem = new CCoinItem(x, y);
		CPlayScene* playScene = dynamic_cast<CPlayScene*>(CGame::GetInstance()->GetCurrentScene());
		if (playScene != NULL)
		{
			playScene->AddObject(spawnedItem);
		}
	}
	else
	{
		DebugOut(L"[ERROR] CQuestionBlock::CQuestionBlock: Invalid item type\n");
	}
	
}

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
		break;
	case QUESTIONBLOCK_STATE_BOUNCING_DOWN:

		//kich hoat item phu hop
		spawnedItem->SetPosition(x, y);
		if (itemType == QUESTIONBLOCK_ITEM_TYPE_POWERUP)
		{
			ActivatePowerUpItem();
		}
		else if (itemType == QUESTIONBLOCK_ITEM_TYPE_COIN)
		{
			ActivateCoinItem();
		}

		vy = QUESTIONBLOCK_BOUNCING_SPEED;
		break;

	}
}

void CQuestionBlock::Bouncing() 
{
	if (state == QUESTIONBLOCK_STATE_BOUNCING_UP )
	{
		if (y <= y_start - QUESTIONBLOCK_BOUNCE_HEIGTH)
		{
			y = y_start - QUESTIONBLOCK_BOUNCE_HEIGTH;
			SetState(QUESTIONBLOCK_STATE_BOUNCING_DOWN); 
		}
	}

	else if (GetState() == QUESTIONBLOCK_STATE_BOUNCING_DOWN )
	{
		if (y >= y_start)
		{
			y = y_start;
			SetState(QUESTIONBLOCK_STATE_USED);
		}
	}
}

void CQuestionBlock::ActivatePowerUpItem()
{
	//chon powerup phu hop voi level mario
	CPlayScene* playScene = dynamic_cast<CPlayScene*>(CGame::GetInstance()->GetCurrentScene());
	if (playScene != NULL)
	{
		int marioLevel = (dynamic_cast<CMario*>(playScene->GetPlayer()))->GetLevel();

		CPowerUpItem* powerUp = dynamic_cast<CPowerUpItem*>(spawnedItem);
		if (powerUp == NULL)
		{
			DebugOut(L"[ERROR] CQuestionBlock::SetState: spawnedItem is NULL\n");
			return;
		}

		if (marioLevel == MARIO_LEVEL_SMALL)
		{
			powerUp->SetIsSuperLeaf(false);
		}
		else
		{
			powerUp->SetIsSuperLeaf(true);
		}
	}
	else
	{
		DebugOut(L"[ERROR] CQuestionBlock::CQuestionBlock: Scene is NULL\n");
	}

	spawnedItem->SetState(POWERUPITEM_STATE_EMERGING);
}

void CQuestionBlock::ActivateCoinItem()
{
	spawnedItem->SetState(COINITEM_STATE_BOUNCING_UP);
}

