#include "CKoopa.h"
#include "Debug.h"
#include "PlayScene.h"
#include "ParaGoomba.h"
#include "CQuestionBlock.h"
#include "CVenus.h"
#include "Brick.h"
#include "CPipe.h"
#include "CGround.h"
#include "CWoodBlock.h"
#include "CParaKoopa.h"
#include "CPiranha.h"
#include "CEffect.h"

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

	//only red koopa check sensorbox
	if(isGreen == 0) UpdateSensorBoxPosition();

	//Check if is held
	if (state == KOOPA_STATE_BEING_HELD)
		ay = 0;
	else
		ay = KOOPA_GRAVITY;

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CKoopa::Render()
{
	if (isGreen)
	{
		RenderGreenKoopa();
	}
	else
		RenderRedKoopa();
	//RenderBoundingBox();
}

void CKoopa::RenderRedKoopa()
{
	int aniId = ID_ANI_KOOPA_WALKING_LEFT;
	if ((state == KOOPA_STATE_SHELL_IDLE || state == KOOPA_STATE_BEING_HELD) && GetTickCount64() - shellStartTime > KOOPA_REVIVE_TIME - KOOPA_REVIVE_BLINK_TIME)
	{
		aniId = ID_ANI_KOOPA_SHELL_UPRIGHT_REVIVE;
		if (isFlipped) aniId = ID_ANI_KOOPA_SHELL_FLIPPED_REVIVE;

		//shake effect
		//(GetTickCount64() / 50) increments by 1 unit every 50ms
		float offset = ((GetTickCount64() / 50) % 2 == 0) ? -0.5 : 0.5;
		CAnimations::GetInstance()->Get(aniId)->Render(x + offset, y);
		return;
	}
	else if (state == KOOPA_STATE_SHELL_IDLE || state == KOOPA_STATE_BEING_HELD)
	{
		aniId = ID_ANI_KOOPA_SHELL_UPRIGHT_IDLE;
		if (isFlipped) aniId = ID_ANI_KOOPA_SHELL_FLIPPED_IDLE;
	}
	if (state == KOOPA_STATE_WALKING_RIGHT)
	{
		aniId = ID_ANI_KOOPA_WALKING_RIGHT;
	}
	else if (state == KOOPA_STATE_SHELL_MOVING_LEFT || state == KOOPA_STATE_SHELL_MOVING_RIGHT)
	{
		aniId = ID_ANI_KOOPA_SHELL_UPRIGHT_MOVING;
		if (isFlipped) aniId = ID_ANI_KOOPA_SHELL_FLIPPED_MOVING;
	}
	else if (state == KOOPA_STATE_DIE)
	{
		aniId = ID_ANI_KOOPA_SHELL_FLIPPED_IDLE;
	}

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);

}

void CKoopa::RenderGreenKoopa()
{
	int aniId = ID_ANI_GREEN_KOOPA_WALKING_LEFT;
	if ((state == KOOPA_STATE_SHELL_IDLE || state == KOOPA_STATE_BEING_HELD) && GetTickCount64() - shellStartTime > KOOPA_REVIVE_TIME - KOOPA_REVIVE_BLINK_TIME)
	{
		aniId = ID_ANI_GREEN_KOOPA_SHELL_UPRIGHT_REVIVE;
		if (isFlipped) aniId = ID_ANI_GREEN_KOOPA_SHELL_FLIPPED_REVIVE;

		//shake effect
		//(GetTickCount64() / 50) increments by 1 unit every 50ms
		float offset = ((GetTickCount64() / 50) % 2 == 0) ? -0.5 : 0.5;
		CAnimations::GetInstance()->Get(aniId)->Render(x + offset, y);
		return;
	}
	else if (state == KOOPA_STATE_SHELL_IDLE || state == KOOPA_STATE_BEING_HELD)
	{
		aniId = ID_ANI_GREEN_KOOPA_SHELL_UPRIGHT_IDLE;
		if (isFlipped) aniId = ID_ANI_GREEN_KOOPA_SHELL_FLIPPED_IDLE;
	}
	if (state == KOOPA_STATE_WALKING_RIGHT)
	{
		aniId = ID_ANI_GREEN_KOOPA_WALKING_RIGHT;
	}
	else if (state == KOOPA_STATE_SHELL_MOVING_LEFT || state == KOOPA_STATE_SHELL_MOVING_RIGHT)
	{
		aniId = ID_ANI_GREEN_KOOPA_SHELL_UPRIGHT_MOVING;
		if (isFlipped) aniId = ID_ANI_GREEN_KOOPA_SHELL_FLIPPED_MOVING;
	}
	else if (state == KOOPA_STATE_DIE)
	{
		aniId = ID_ANI_GREEN_KOOPA_SHELL_FLIPPED_IDLE;
	}

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
}

void CKoopa::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}

void CKoopa::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (state == KOOPA_STATE_SHELL_MOVING_LEFT || state == KOOPA_STATE_SHELL_MOVING_RIGHT || state == KOOPA_STATE_BEING_HELD)
	{
		if (dynamic_cast<CParaGoomba*>(e->obj))
			OnCollisionWithParaGoomba(e);
		else if (dynamic_cast<CGoomba*>(e->obj))
			OnCollisionWithGoomba(e);
		else if (dynamic_cast<CQuestionBlock*>(e->obj))
			OnCollisionWithQuestionBlock(e);
		else if (dynamic_cast<CVenus*>(e->obj))
			OnCollisionWithVenus(e);
		else if (dynamic_cast<CParaKoopa*>(e->obj))
			OnCollisionWithParaKoopa(e);
		else if (dynamic_cast<CKoopa*>(e->obj))
			OnCollisionWithKoopa(e);
		else if (dynamic_cast<CPiranha*>(e->obj))
			OnCollisionWithPiranha(e);
		else if (dynamic_cast<CBrick*>(e->obj))
			OnCollisionWithBrick(e);
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

void CKoopa::OnOverlapWith(LPCOLLISIONEVENT e)
{

	if (state == KOOPA_STATE_SHELL_MOVING_LEFT || state == KOOPA_STATE_SHELL_MOVING_RIGHT || state == KOOPA_STATE_BEING_HELD)
	{
		if (dynamic_cast<CParaGoomba*>(e->obj))
			OnOverlapWithParaGoomba(e);
		else if (dynamic_cast<CGoomba*>(e->obj))
			OnOverlapWithGoomba(e);
		else if (dynamic_cast<CVenus*>(e->obj))
			OnOverlapWithVenus(e);
		else if (dynamic_cast<CParaKoopa*>(e->obj))
			OnOverlapWithParaKoopa(e);
		else if (dynamic_cast<CKoopa*>(e->obj))
			OnOverlapWithKoopa(e);
		else if (dynamic_cast<CVenus*>(e->obj))
			OnOverlapWithPiranha(e);
		else if (dynamic_cast<CBrick*>(e->obj))
			OnOverlapWithBrick(e);
		else if (dynamic_cast<CQuestionBlock*>(e->obj))
			OnOverlapWithQuestionBlock(e);
		else if (dynamic_cast<CPipe*>(e->obj))
			OnOverlapWithPipe(e);
		else if (dynamic_cast<CGround*>(e->obj))
			OnOverlapWithGround(e);
		else if (dynamic_cast<CWoodBlock*>(e->obj))
			OnOverlapWithWoodBlock(e);
	}
}

void CKoopa::CheckAndChangeState()
{
	if(state == KOOPA_STATE_SHELL_IDLE || state == KOOPA_STATE_BEING_HELD)
	{
		if (GetTickCount64() - shellStartTime > KOOPA_REVIVE_TIME)
		{
			if (isGreen)
			{
				TurnToMario();
			}
			else
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

	// Koopa just turned back while walking, sensorbox freely falls to detect cliffs 
	if (changedDirection || (state!=KOOPA_STATE_WALKING_LEFT && state!= KOOPA_STATE_WALKING_RIGHT)) newY = y;
	else newY = sensorBox->GetY();

	
	if (sensorBox->GetY() - y >= KOOPA_BBOX_HEIGHT / 2) newY = y;

	sensorBox->SetPosition(newX, newY);
}

void CKoopa::TurnToMario()
{
	CPlayScene* playScene = dynamic_cast<CPlayScene*>(CGame::GetInstance()->GetCurrentScene());
	float marioX = 0, marioY = 0;
	CMario* mario = dynamic_cast<CMario*>(playScene->GetPlayer());
	if (mario != NULL)
	{
		mario->GetPosition(marioX, marioY);
	}
	
	if (marioX <= this->x) SetState(KOOPA_STATE_WALKING_LEFT);
	else SetState(KOOPA_STATE_WALKING_RIGHT);
}

void CKoopa::OnCollisionWithGoomba(LPCOLLISIONEVENT e)
{
	CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);

	if (state == KOOPA_STATE_BEING_HELD)
	{
		SetState(KOOPA_STATE_DIE);
	}

	if(goomba->GetState() != GOOMBA_STATE_BOUNCE_DEATH)
		goomba->SetState(GOOMBA_STATE_BOUNCE_DEATH);

	CPlayScene* playScene = dynamic_cast<CPlayScene*>(CGame::GetInstance()->GetCurrentScene());
	CMario* player = dynamic_cast<CMario*>(playScene->GetPlayer());
	player->AddComboPoints(e->obj);
}

void CKoopa::OnCollisionWithParaGoomba(LPCOLLISIONEVENT e)
{
	CParaGoomba* paragoomba = dynamic_cast<CParaGoomba*>(e->obj);
	
	if (state == KOOPA_STATE_BEING_HELD)
	{
		SetState(KOOPA_STATE_DIE);
	}

	if (paragoomba->GetIsGoomba() == false)
	{
		paragoomba->TurnIntoGoomba();
	}

	if(paragoomba->GetState() != GOOMBA_STATE_BOUNCE_DEATH)
		paragoomba->SetState(GOOMBA_STATE_BOUNCE_DEATH);

	CPlayScene* playScene = dynamic_cast<CPlayScene*>(CGame::GetInstance()->GetCurrentScene());
	CMario* player = dynamic_cast<CMario*>(playScene->GetPlayer());
	player->AddComboPoints(e->obj);
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

	if (state == KOOPA_STATE_BEING_HELD)
	{
		SetState(KOOPA_STATE_DIE);
	}

	venus->SetState(VENUS_STATE_DIE);

	CPlayScene* playScene = dynamic_cast<CPlayScene*>(CGame::GetInstance()->GetCurrentScene());
	CMario* player = dynamic_cast<CMario*>(playScene->GetPlayer());
	player->AddComboPoints(e->obj);
}

void CKoopa::OnCollisionWithParaKoopa(LPCOLLISIONEVENT e)
{
	CParaKoopa* paraKoopa = dynamic_cast<CParaKoopa*>(e->obj);
	if (paraKoopa->GetIsKoopa())
	{
		OnCollisionWithKoopa(e);
		return;
	}
	if (state == KOOPA_STATE_BEING_HELD)
	{
		SetState(KOOPA_STATE_DIE);
	}
	paraKoopa->TurnIntoKoopa();

	CPlayScene* playScene = dynamic_cast<CPlayScene*>(CGame::GetInstance()->GetCurrentScene());
	CMario* player = dynamic_cast<CMario*>(playScene->GetPlayer());
	player->AddComboPoints(e->obj);

	paraKoopa->SetState(KOOPA_STATE_DIE);
}
void CKoopa::OnCollisionWithPiranha(LPCOLLISIONEVENT e)
{
	CPiranha* piranha = dynamic_cast<CPiranha*>(e->obj);
	if (piranha->GetState() == PIRANHA_STATE_DIE) return;

	if (state == KOOPA_STATE_BEING_HELD)
	{
		SetState(KOOPA_STATE_DIE);
	}

	piranha->SetState(PIRANHA_STATE_DIE);


	CPlayScene* playScene = dynamic_cast<CPlayScene*>(CGame::GetInstance()->GetCurrentScene());
	CMario* player = dynamic_cast<CMario*>(playScene->GetPlayer());
	player->AddComboPoints(e->obj);
}

void CKoopa::OnCollisionWithKoopa(LPCOLLISIONEVENT e)
{
	CKoopa* koopa = dynamic_cast<CKoopa*>(e->obj);
	if (koopa->GetState() == KOOPA_STATE_DIE) return;
	
	if (state == KOOPA_STATE_BEING_HELD)
	{
		SetState(KOOPA_STATE_DIE);
	}

	if(koopa->GetState() == KOOPA_STATE_SHELL_MOVING_LEFT || koopa->GetState() == KOOPA_STATE_SHELL_MOVING_RIGHT)
	{
		SetState(KOOPA_STATE_DIE);
		koopa->SetState(KOOPA_STATE_DIE);
	}
	else if (koopa->GetState() == KOOPA_STATE_WALKING_LEFT || koopa->GetState() == KOOPA_STATE_WALKING_RIGHT || koopa->GetState() == KOOPA_STATE_SHELL_IDLE)
	{
		koopa->SetState(KOOPA_STATE_DIE);
	}

	CPlayScene* playScene = dynamic_cast<CPlayScene*>(CGame::GetInstance()->GetCurrentScene());
	CMario* player = dynamic_cast<CMario*>(playScene->GetPlayer());
	player->AddComboPoints(e->obj);

	CEffect* effect = new CEffect(e->obj->GetX(), e->obj->GetY());
	playScene->AddObject(effect);
}

void CKoopa::OnCollisionWithBrick(LPCOLLISIONEVENT e)
{
	CBrick* brick = dynamic_cast<CBrick*>(e->obj);

	if (e->nx != 0)
	{
		if (brick->GetState() == BRICK_STATE_IDLE)
		{
			brick->SetState(BRICK_STATE_BROKEN);
		}
	}
}

void CKoopa::OnOverlapWithGoomba(LPCOLLISIONEVENT e)
{

	CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);
	if (goomba->GetState() == GOOMBA_STATE_DIE || goomba->GetState() == GOOMBA_STATE_BOUNCE_DEATH) return;

	if (state == KOOPA_STATE_BEING_HELD)
	{
		SetState(KOOPA_STATE_DIE);
	}

	goomba->SetState(GOOMBA_STATE_BOUNCE_DEATH);

	CPlayScene* playScene = dynamic_cast<CPlayScene*>(CGame::GetInstance()->GetCurrentScene());
	CMario* player = dynamic_cast<CMario*>(playScene->GetPlayer());
	player->AddComboPoints(e->obj);
}

void CKoopa::OnOverlapWithParaGoomba(LPCOLLISIONEVENT e)
{
	CParaGoomba* paragoomba = dynamic_cast<CParaGoomba*>(e->obj);
	if (paragoomba->GetState() == GOOMBA_STATE_DIE || paragoomba->GetState() == GOOMBA_STATE_BOUNCE_DEATH) return;

	if (state == KOOPA_STATE_BEING_HELD)
	{
		SetState(KOOPA_STATE_DIE);
	}

	if (paragoomba->GetIsGoomba() == false)
	{
		paragoomba->TurnIntoGoomba();
	}
	paragoomba->SetState(GOOMBA_STATE_BOUNCE_DEATH);

	CPlayScene* playScene = dynamic_cast<CPlayScene*>(CGame::GetInstance()->GetCurrentScene());
	CMario* player = dynamic_cast<CMario*>(playScene->GetPlayer());
	player->AddComboPoints(e->obj);
}

void CKoopa::OnOverlapWithVenus(LPCOLLISIONEVENT e)
{
	if (state == KOOPA_STATE_BEING_HELD)
	{
		SetState(KOOPA_STATE_DIE);
	}

	CVenus* venus = dynamic_cast<CVenus*>(e->obj);

	venus->SetState(VENUS_STATE_DIE);

	CPlayScene* playScene = dynamic_cast<CPlayScene*>(CGame::GetInstance()->GetCurrentScene());
	CMario* player = dynamic_cast<CMario*>(playScene->GetPlayer());
	player->AddComboPoints(e->obj);
}

void CKoopa::OnOverlapWithParaKoopa(LPCOLLISIONEVENT e)
{
	CParaKoopa* paraKoopa = dynamic_cast<CParaKoopa*>(e->obj);

	if (paraKoopa->GetIsKoopa())
	{
		OnOverlapWithKoopa(e);
		return;
	}

	if (state == KOOPA_STATE_BEING_HELD)
	{
		SetState(KOOPA_STATE_DIE);
	}

	paraKoopa->TurnIntoKoopa();
	paraKoopa->SetState(KOOPA_STATE_DIE);

	CPlayScene* playScene = dynamic_cast<CPlayScene*>(CGame::GetInstance()->GetCurrentScene());
	CMario* player = dynamic_cast<CMario*>(playScene->GetPlayer());
	player->AddComboPoints(e->obj);
}

void CKoopa::OnOverlapWithPiranha(LPCOLLISIONEVENT e)
{
	CPiranha* piranha = dynamic_cast<CPiranha*>(e->obj);
	if (piranha->GetState() == PIRANHA_STATE_DIE) return;

	if (state == KOOPA_STATE_BEING_HELD)
	{
		SetState(KOOPA_STATE_DIE);
	}

	piranha->SetState(PIRANHA_STATE_DIE);

	CPlayScene* playScene = dynamic_cast<CPlayScene*>(CGame::GetInstance()->GetCurrentScene());
	CMario* player = dynamic_cast<CMario*>(playScene->GetPlayer());
	player->AddComboPoints(e->obj);
}

void CKoopa::OnOverlapWithKoopa(LPCOLLISIONEVENT e)
{
	CKoopa* koopa = dynamic_cast<CKoopa*>(e->obj);

	if (koopa->GetState() == KOOPA_STATE_DIE) return;

	if (state == KOOPA_STATE_BEING_HELD)
	{
		SetState(KOOPA_STATE_DIE);
	}

	if (koopa->GetState() == KOOPA_STATE_SHELL_MOVING_LEFT || koopa->GetState() == KOOPA_STATE_SHELL_MOVING_RIGHT)
	{
		koopa->SetState(KOOPA_STATE_DIE);
		SetState(KOOPA_STATE_DIE);
	}
	else if (koopa->GetState() == KOOPA_STATE_WALKING_LEFT || koopa->GetState() == KOOPA_STATE_WALKING_RIGHT || koopa->GetState() == KOOPA_STATE_SHELL_IDLE)
	{
		koopa->SetState(KOOPA_STATE_DIE);
	}

	CPlayScene* playScene = dynamic_cast<CPlayScene*>(CGame::GetInstance()->GetCurrentScene());
	CMario* player = dynamic_cast<CMario*>(playScene->GetPlayer());
	player->AddComboPoints(e->obj);
}

void CKoopa::OnOverlapWithBrick(LPCOLLISIONEVENT e)
{
	if(state==KOOPA_STATE_SHELL_MOVING_LEFT || state==KOOPA_STATE_SHELL_MOVING_RIGHT)
		SetState(KOOPA_STATE_DIE);
}

void CKoopa::OnOverlapWithQuestionBlock(LPCOLLISIONEVENT e)
{
	if (state == KOOPA_STATE_SHELL_MOVING_LEFT || state == KOOPA_STATE_SHELL_MOVING_RIGHT)
		SetState(KOOPA_STATE_DIE);
}

void CKoopa::OnOverlapWithPipe(LPCOLLISIONEVENT e)
{
	if (state == KOOPA_STATE_SHELL_MOVING_LEFT || state == KOOPA_STATE_SHELL_MOVING_RIGHT)
		SetState(KOOPA_STATE_DIE);
}

void CKoopa::OnOverlapWithGround(LPCOLLISIONEVENT e)
{
	if (state == KOOPA_STATE_SHELL_MOVING_LEFT || state == KOOPA_STATE_SHELL_MOVING_RIGHT)
		SetState(KOOPA_STATE_DIE);
}

void CKoopa::OnOverlapWithWoodBlock(LPCOLLISIONEVENT e)
{
	if (state == KOOPA_STATE_SHELL_MOVING_LEFT || state == KOOPA_STATE_SHELL_MOVING_RIGHT)
		SetState(KOOPA_STATE_DIE);
}

CKoopa::CKoopa(float x, float y, boolean isGreen)
{
	this->x = x;
	this->y = y;
	this->isGreen = isGreen;
	ay = KOOPA_GRAVITY;
	isFlipped = false;

	if (isGreen == 0)
	{
		sensorBox = new CSensorBox(x, y, KOOPA_BBOX_WIDTH / 4, KOOPA_BBOX_HEIGHT / 4);

		CPlayScene* playScene = dynamic_cast<CPlayScene*>(CGame::GetInstance()->GetCurrentScene());
		playScene->AddObject(sensorBox);


		SetState(KOOPA_STATE_WALKING_LEFT);
	}
	else
	{
		sensorBox = NULL;

		//set state
		TurnToMario();
	}

}

void CKoopa::SetState(int nextState)
{
	switch (nextState)
	{
		case KOOPA_STATE_WALKING_LEFT:
			vx = -KOOPA_WALKING_SPEED;
			isFlipped = false; //koopa wakes up and returns to normal

			if(this->state != KOOPA_STATE_WALKING_LEFT && this->state != KOOPA_STATE_WALKING_RIGHT) AlignYOnTransform();
			break;

		case KOOPA_STATE_WALKING_RIGHT:
			vx = KOOPA_WALKING_SPEED;
			isFlipped = false; //koopa wakes up and returns to normal

			if (this->state != KOOPA_STATE_WALKING_LEFT && this->state != KOOPA_STATE_WALKING_RIGHT) AlignYOnTransform();
			break;

		case KOOPA_STATE_SHELL_IDLE:
			shellStartTime = GetTickCount64();
			vx = 0;
			break;
		case KOOPA_STATE_SHELL_MOVING_RIGHT:
			vx = KOOPA_SHELL_MOVING_SPEED;
			break;
		case KOOPA_STATE_SHELL_MOVING_LEFT:
			vx = -KOOPA_SHELL_MOVING_SPEED;
			break;
		case KOOPA_STATE_BEING_HELD: //state when mario holds koopa
			vx = 0;
			vy = 0;
			break;
		case KOOPA_STATE_DIE:
			//isDeleted = true;
			vy = -KOOPA_BOUNCE_SPEED;
			break;
		case KOOPA_STATE_SHELL_BOUNCE:
			DebugOut(L"koopa set state BOUNCE\n");
			isFlipped = true;
			vy = -KOOPA_BOUNCE_SPEED*1.4f;

			//set state shell idle 
			shellStartTime = GetTickCount64();
			vx = 0;
			nextState = KOOPA_STATE_SHELL_IDLE;

			break;
	}
	//only a SetState will update koopa state
	CGameObject::SetState(nextState); //need to update state later to check current state
}
