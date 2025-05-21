#include "CPSwitch.h"
#include "PlayScene.h"
#include "Coin.h"

void CPSwitch::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	if (state == PSWITCH_STATE_IDLE)
		animations->Get(ID_ANI_PSWITCH_IDLE)->Render(x, y);
	else if (state == PSWITCH_STATE_EFFECT || state == PSWITCH_STATE_USED)
		animations->Get(ID_ANI_PSWITCH_USED)->Render(x, y);

	//RenderBoundingBox();
}

void CPSwitch::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (state == PSWITCH_STATE_EFFECT)
	{
		if (GetTickCount64() - timeEffectStart > PSWITCH_EFFECT_TIME)
		{
			Switch();
			SetState(PSWITCH_STATE_USED);
		}
	}
	CGameObject::Update(dt, coObjects);
}

void CPSwitch::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - PSWITCH_BBOX_WIDTH / 2;
	t = y - PSWITCH_BBOX_HEIGHT / 2;
	r = l + PSWITCH_BBOX_WIDTH;
	b = t + PSWITCH_BBOX_HEIGHT;
}

void CPSwitch::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case PSWITCH_STATE_IDLE:
		break;
	case PSWITCH_STATE_EFFECT:
		Switch();
		timeEffectStart = GetTickCount64();
		break;
	case PSWITCH_STATE_USED:
		break;
	default:
		break;
	}
}

void CPSwitch::Switch()
{
	CPlayScene* scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
	vector<LPGAMEOBJECT> objs = scene->GetObjects();

	for (UINT i = 0; i < objs.size(); i++)
	{
		float obj_x = 0, obj_y = 0;
		CBrick* brick = dynamic_cast<CBrick*>(objs[i]);
		CCoin* coin = dynamic_cast<CCoin*>(objs[i]);
		if (brick != NULL)
		{
			brick->GetPosition(obj_x, obj_y);
			if (obj_x <= x + PSWITCH_EFFECT_RANGE_X && obj_x >= x - PSWITCH_EFFECT_RANGE_X && brick->GetState()==BRICK_STATE_IDLE)
			{
				brick->Delete();
				CCoin* newCoin = new CCoin(obj_x, obj_y);
				newCoin->SetStatic();
				scene->AddObject(newCoin);
			}
		}
		if(coin != NULL)
		{
			coin->GetPosition(obj_x, obj_y);
			if (obj_x <= x + PSWITCH_EFFECT_RANGE_X && obj_x >= x - PSWITCH_EFFECT_RANGE_X)
			{
				coin->Delete();
				CBrick* newBrick = new CBrick(obj_x, obj_y, 0);
				scene->AddObject(newBrick);
			}
		}
	}
}
