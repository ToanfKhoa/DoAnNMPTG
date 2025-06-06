#include "CCoinItem.h"
#include "PlayScene.h"

void CCoinItem::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	if (state == COINITEM_STATE_IDLE) return;
	animations->Get(ID_ANI_COINITEM)->Render(x, y);
}

void CCoinItem::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (state == COINITEM_STATE_BOUNCING_UP)
	{
		vy = -COINITEM_BOUNCE_SPEED;
	}
	else if (state == COINITEM_STATE_BOUNCING_DOWN)
	{
		vy = COINITEM_BOUNCE_SPEED;
	}

	if (y <= y_start - COINITEM_BOUNCE_HEIGHT)
	{
		SetState(COINITEM_STATE_BOUNCING_DOWN);
	}
	else if (y >= y_start - COINITEM_BOUNCE_DELETE_HEIGHT && state == COINITEM_STATE_BOUNCING_DOWN)
	{
		CPlayScene* playScene = dynamic_cast<CPlayScene*>(CGame::GetInstance()->GetCurrentScene());
		CMario* player = dynamic_cast<CMario*>(playScene->GetPlayer());
		player->AddPoints(100, this);

		isDeleted = true;
	}

	y += vy * dt;
}

void CCoinItem::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - COINITEM_BBOX_WIDTH / 2;
	t = y - COINITEM_BBOX_HEIGHT / 2;
	r = l + COINITEM_BBOX_WIDTH;
	b = t + COINITEM_BBOX_HEIGHT;
}


