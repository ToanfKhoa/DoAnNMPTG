#include "Brick.h"
#include "CBrokenBrickPiece.h"
#include "CExtraLifeMushroom.h"
#include "CPSwitch.h"
#include "PlayScene.h"
#include "CCoinItem.h"
#include "CPowerUpitem.h"

void CBrick::Render()
{
	CAnimations* animations = CAnimations::GetInstance();

	if (state == BRICK_STATE_IDLE || itemType == 0)
	{
		animations->Get(ID_ANI_BRICK_IDLE)->Render(x, y); //brick is idle, mario small
	}
	else if (itemType != 0 && state != BRICK_STATE_USED)
	{
		animations->Get(ID_ANI_BRICK_IDLE)->Render(x, y);
	}
	else 
		animations->Get(ID_ANI_BRICK_USED)->Render(x, y); //brick's item was used
		
	//RenderBoundingBox();
}

void CBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (state != BRICK_STATE_USED && state != BRICK_STATE_BROKEN)
	{
		Bouncing();

		CCollision::GetInstance()->Process(this, dt, coObjects);
	}

	CGameObject::Update(dt, coObjects);
}

void CBrick::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x - BRICK_BBOX_WIDTH/2;
	t = y - BRICK_BBOX_HEIGHT/2;
	r = l + BRICK_BBOX_WIDTH;
	b = t + BRICK_BBOX_HEIGHT;
}

void CBrick::OnNoCollision(DWORD dt)
{
	y += vy * dt;
}

void CBrick::Bouncing()
{
	if (state == BRICK_STATE_BOUNCING_UP)
	{
		if (y <= y_start - BRICK_BOUNCE_HEIGHT)
		{
			y = y_start - BRICK_BOUNCE_HEIGHT;
			SetState(BRICK_STATE_BOUNCING_DOWN);
		}
	}

	else if (GetState() == BRICK_STATE_BOUNCING_DOWN)
	{
		if (y >= y_start)
		{
			y = y_start;

			if (itemType != 0 && itemCount <= 0)
			{
				SetState(BRICK_STATE_USED);
			}
			else
			{
				itemCount--;
				SetState(BRICK_STATE_IDLE);
			}
		}
	}
}

void CBrick::SpawnBrokenPieces()
{
	CBrokenBrickPiece* pieceTopLeft = new CBrokenBrickPiece(x, y, -0.1f, -0.4f);
	CBrokenBrickPiece* pieceTopRight = new CBrokenBrickPiece(x, y, 0.1f, -0.4f);
	CBrokenBrickPiece* pieceBotLeft = new CBrokenBrickPiece(x, y, -0.12f, -0.15f);
	CBrokenBrickPiece* pieceBotRight = new CBrokenBrickPiece(x, y, 0.12f, -0.15f);

	CPlayScene* playScene = dynamic_cast<CPlayScene*>(CGame::GetInstance()->GetCurrentScene());
	if (playScene != NULL)
	{
		playScene->AddObject(pieceTopLeft);
		playScene->AddObject(pieceTopRight);
		playScene->AddObject(pieceBotLeft);
		playScene->AddObject(pieceBotRight);
	}
}

CBrick::CBrick(float x, float y, int itemType) : CGameObject(x, y) 
{
	this->x = x;
	this->y = y;
	y_start = y;
	this->itemType = itemType;
	SetState(BRICK_STATE_IDLE);

	if (itemType == 1)
	{
		this->spawnedItem = new CExtraLifeMushroom(x, y);
		CPlayScene* playScene = dynamic_cast<CPlayScene*>(CGame::GetInstance()->GetCurrentScene());
		if (playScene != NULL)
		{
			playScene->AddObject(spawnedItem);
		}
	}
	else if (itemType == 2)
	{
		this->spawnedItem = new CPSwitch(x, y);
		CPlayScene* playScene = dynamic_cast<CPlayScene*>(CGame::GetInstance()->GetCurrentScene());
		if (playScene != NULL)
		{
			playScene->AddObject(spawnedItem);
		}
	}
	else if (itemType == 3)
	{
		this->spawnedItem = new CCoinItem(x, y);
		CPlayScene* playScene = dynamic_cast<CPlayScene*>(CGame::GetInstance()->GetCurrentScene());
		if (playScene != NULL)
		{
			playScene->AddObject(spawnedItem);
		}
		itemCount = 6; //brick will spawn 7 coins
	}
	else if (itemType == 4)
	{
		this->spawnedItem = new CPowerUpItem(x, y);
		CPlayScene* playScene = dynamic_cast<CPlayScene*>(CGame::GetInstance()->GetCurrentScene());
		if (playScene != NULL)
		{
			playScene->AddObject(spawnedItem);
		}
	}
	else
	{
		spawnedItem = NULL;
	}
}

void CBrick::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case BRICK_STATE_USED:
		vy = 0;
		break;
	case BRICK_STATE_IDLE:
		vy = 0;
		break;
	case BRICK_STATE_BOUNCING_UP:
		vy = -BRICK_BOUNCING_SPEED;
		break;
	case BRICK_STATE_BOUNCING_DOWN:
		vy = BRICK_BOUNCING_SPEED;

		//activate item
		if (itemType == 1)
		{
			spawnedItem->SetPosition(x, y); 
			spawnedItem->SetState(EXTRALIFEMUSHROOM_STATE_EMERGING);
		}
		else if (itemType == 2)
		{
			spawnedItem->SetPosition(x, y - BRICK_BBOX_HEIGHT / 2);
			spawnedItem->SetState(PSWITCH_STATE_IDLE);
		}
		else if (itemType == 3)
		{
			spawnedItem->SetPosition(x, y - BRICK_BBOX_HEIGHT / 2);
			spawnedItem->SetState(COINITEM_STATE_BOUNCING_UP);

			this->spawnedItem = new CCoinItem(x, y);
			CPlayScene* playScene = dynamic_cast<CPlayScene*>(CGame::GetInstance()->GetCurrentScene());
			if (playScene != NULL)
			{
				playScene->AddObject(spawnedItem);
			}
		}
		else if (itemType == 4)
		{
			CPlayScene* playScene = dynamic_cast<CPlayScene*>(CGame::GetInstance()->GetCurrentScene());
			CMario* player = dynamic_cast<CMario*>(playScene);
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

			spawnedItem->SetPosition(x + 2, y - BRICK_BBOX_HEIGHT / 1.5);
			spawnedItem->SetState(POWERUPITEM_STATE_EMERGING);
		}
		else
			spawnedItem = NULL;

		break;
	case BRICK_STATE_BROKEN:

		//brick cant break if it contains an item
		if (itemType != 0)
		{
			SetState(BRICK_STATE_BOUNCING_UP);
			return;
		}

		SpawnBrokenPieces();
		isDeleted = true;
		break;
	}
}
