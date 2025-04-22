#include "CKoopa.h"
#include "Debug.h"
#include "PlayScene.h"
#include "ParaGoomba.h"
#include "CQuestionBlock.h"
#include "CVenus.h"

void CKoopa::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == KOOPA_STATE_WALKING_LEFT || state == KOOPA_STATE_WALKING_RIGHT)
	{
		left = x - KOOPA_BBOX_WIDTH / 2;
		top = y - KOOPA_BBOX_HEIGHT / 2;
		right = left + KOOPA_BBOX_WIDTH;
		bottom = top + KOOPA_BBOX_HEIGHT;
	}
	else
	{
		left = x - KOOPA_BBOX_SHELL_WIDTH / 2;
		top = y - KOOPA_BBOX_SHELL_HEIGHT / 2;
		right = left + KOOPA_BBOX_SHELL_WIDTH;
		bottom = top + KOOPA_BBOX_SHELL_HEIGHT;
	}
}

void CKoopa::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	/*if (state == KOOPA_STATE_DIE)
	{
		isDeleted = true;
		return;
	}*/
	CheckAndChangeState();

	UpdateSensorBoxPosition();

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CKoopa::Render()
{
	int aniId = ID_ANI_KOOPA_WALKING_LEFT;
	if (state == KOOPA_STATE_SHELL_IDLE && GetTickCount64() - shellStartTime > KOOPA_REVIVE_TIME - KOOPA_REVIVE_BLINK_TIME)
	{
		aniId = ID_ANI_KOOPA_SHELL_UPRIGHT_REVIVE;

		//shake effect
		//(GetTickCount64() / 50) increments by 1 unit every 50ms
		float offset = ((GetTickCount64() / 50) % 2 == 0) ? -0.5 : 0.5;
		CAnimations::GetInstance()->Get(aniId)->Render(x + offset, y);
		RenderBoundingBox();
		return;
	}
	else if (state == KOOPA_STATE_SHELL_IDLE || state == KOOPA_STATE_BEING_HELD)
	{
		aniId = ID_ANI_KOOPA_SHELL_UPRIGHT_IDLE;
	}
	if (state == KOOPA_STATE_WALKING_RIGHT)
	{
		aniId = ID_ANI_KOOPA_WALKING_RIGHT;
	}
	else if (state == KOOPA_STATE_SHELL_MOVING_LEFT || state == KOOPA_STATE_SHELL_MOVING_RIGHT)
	{
		aniId = ID_ANI_KOOPA_SHELL_UPRIGHT_MOVING;
	}
	else if (state == KOOPA_STATE_DIE)
	{
		DebugOut(L"RENDER KOOPA DIE\n" );
		aniId = ID_ANI_KOOPA_DIE;
	}

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	RenderBoundingBox();
}

void CKoopa::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}

void CKoopa::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (state == KOOPA_STATE_SHELL_MOVING_LEFT || state == KOOPA_STATE_SHELL_MOVING_RIGHT)
	{
		if (dynamic_cast<CParaGoomba*>(e->obj))
			OnCollisionWithParaGoomba(e);
		else if (dynamic_cast<CGoomba*>(e->obj))
			OnCollisionWithGoomba(e);
		else if (dynamic_cast<CQuestionBlock*>(e->obj))
			OnCollisionWithQuestionBlock(e);
		else if (dynamic_cast<CVenus*>(e->obj))
			OnCollisionWithVenus(e);
		else if (dynamic_cast<CKoopa*>(e->obj))
			OnCollisionWithKoopa(e);
	}

	if (!e->obj->IsBlocking()) return;

	if (e->ny != 0) // On top of a platform or bouncing in shell form and hitting a block above
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		if(state == KOOPA_STATE_WALKING_LEFT) SetState(KOOPA_STATE_WALKING_RIGHT);
		else if(state == KOOPA_STATE_WALKING_RIGHT) SetState(KOOPA_STATE_WALKING_LEFT);
		else if (state == KOOPA_STATE_SHELL_MOVING_LEFT) SetState(KOOPA_STATE_SHELL_MOVING_RIGHT);
		else if (state == KOOPA_STATE_SHELL_MOVING_RIGHT) SetState(KOOPA_STATE_SHELL_MOVING_LEFT);
	}


}

void CKoopa::CheckAndChangeState()
{
	if(state==KOOPA_STATE_SHELL_IDLE)
	{
		if (GetTickCount64() - shellStartTime > KOOPA_REVIVE_TIME)
		{
			SetState(KOOPA_STATE_WALKING_LEFT);
		}
	}
}

void CKoopa::AlignYOnTransform()
{
	y -= (KOOPA_BBOX_HEIGHT - KOOPA_BBOX_SHELL_HEIGHT) / 2;
}

void CKoopa::UpdateSensorBoxPosition()
{
	bool changedDirection = false;
	if(!sensorBox->getIsOnPlatform())
	{
		changedDirection = true;

		if (state == KOOPA_STATE_WALKING_LEFT)
		{
			SetState(KOOPA_STATE_WALKING_RIGHT);
		}
		else if (state == KOOPA_STATE_WALKING_RIGHT)
		{
			SetState(KOOPA_STATE_WALKING_LEFT);
		}
	}

	float newX = (state == KOOPA_STATE_WALKING_LEFT) ? x - KOOPA_BBOX_WIDTH / 2 : x+ KOOPA_BBOX_WIDTH / 2;
	float newY;
	if (changedDirection) newY = y;
	else newY = sensorBox->GetY();

	sensorBox->SetPosition(newX, newY);
}

void CKoopa::OnCollisionWithGoomba(LPCOLLISIONEVENT e)
{
	CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);
	goomba->SetState(GOOMBA_STATE_DIE);
}

void CKoopa::OnCollisionWithParaGoomba(LPCOLLISIONEVENT e)
{
	CParaGoomba* paragoomba = dynamic_cast<CParaGoomba*>(e->obj);
	
	DebugOut(L"[INFO] Koopa hit ParaGoomba\n");
	if (paragoomba->GetIsGoomba() == false)
	{
		paragoomba->TurnIntoGoomba();
	}
	paragoomba->SetState(GOOMBA_STATE_DIE);
}

void CKoopa::OnCollisionWithQuestionBlock(LPCOLLISIONEVENT e)
{
	CQuestionBlock* question = dynamic_cast<CQuestionBlock*>(e->obj);

	if (e->nx != 0)
	{
		if (question->GetState() == QUESTIONBLOCK_STATE_IDLE)
		{
			question->SetState(QUESTIONBLOCK_STATE_BOUNCING_UP);
		}
	}
	
}

void CKoopa::OnCollisionWithVenus(LPCOLLISIONEVENT e)
{
	CVenus* venus = dynamic_cast<CVenus*>(e->obj);

	venus->SetState(VENUS_STATE_DIE);
}

void CKoopa::OnCollisionWithKoopa(LPCOLLISIONEVENT e)
{
	CKoopa* koopa = dynamic_cast<CKoopa*>(e->obj);
	
	if(koopa->GetState() == KOOPA_STATE_SHELL_MOVING_LEFT || koopa->GetState() == KOOPA_STATE_SHELL_MOVING_RIGHT)
	{
		SetState(KOOPA_STATE_DIE);
		koopa->SetState(KOOPA_STATE_DIE);
	}
	else if (koopa->GetState() == KOOPA_STATE_WALKING_LEFT || koopa->GetState() == KOOPA_STATE_WALKING_RIGHT || koopa->GetState() == KOOPA_STATE_SHELL_IDLE)
	{
		koopa->SetState(KOOPA_STATE_DIE);
	}
}

CKoopa::CKoopa(float x, float y)
{
	this->x = x;
	this->y = y;
	ay = KOOPA_GRAVITY;
	sensorBox = new CSensorBox(x, y, KOOPA_BBOX_WIDTH/2, KOOPA_BBOX_HEIGHT);

	CPlayScene* playScene = dynamic_cast<CPlayScene*>(CGame::GetInstance()->GetCurrentScene());
	playScene->AddObject(sensorBox);

	SetState(KOOPA_STATE_WALKING_LEFT);
}

void CKoopa::SetState(int nextState)
{
	switch (nextState)
	{
		case KOOPA_STATE_WALKING_LEFT:
			vx = -KOOPA_WALKING_SPEED;

			if(this->state != KOOPA_STATE_WALKING_LEFT && this->state != KOOPA_STATE_WALKING_RIGHT) AlignYOnTransform();
			break;

		case KOOPA_STATE_WALKING_RIGHT:
			vx = KOOPA_WALKING_SPEED;

			if (this->state != KOOPA_STATE_WALKING_LEFT && this->state != KOOPA_STATE_WALKING_RIGHT) AlignYOnTransform();
			break;

		case KOOPA_STATE_SHELL_IDLE:
			shellStartTime = GetTickCount64();
			vx = 0;
			break;
		case KOOPA_STATE_SHELL_MOVING_RIGHT:
			vx = KOOPA_WALKING_SPEED*2;
			break;
		case KOOPA_STATE_SHELL_MOVING_LEFT:
			vx = -KOOPA_WALKING_SPEED*2;
			break;
		case KOOPA_STATE_DIE:
			//isDeleted = true;
			vy = -KOOPA_BOUNCE_SPEED;
			break;
	}
	CGameObject::SetState(nextState); //need to update state later to check current state
}
