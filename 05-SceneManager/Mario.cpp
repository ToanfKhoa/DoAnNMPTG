#include <algorithm>
#include "debug.h"

#include "Mario.h"
#include "Game.h"

#include "Goomba.h"
#include "Coin.h"
#include "Portal.h"

#include "Collision.h"
#include "ParaGoomba.h"
#include "CQuestionBlock.h"
#include "CVenus.h"
#include "CBulletVenus.h"
#include "CPowerUpItem.h"
#include "CKoopa.h"
#include "Brick.h"
#include "CPit.h"

void CMario::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	if (abs(vx) > abs(maxVx)) vx = maxVx;

	// reset untouchable timer if untouchable time has passed
	if ( GetTickCount64() - untouchable_start > MARIO_UNTOUCHABLE_TIME) 
	{
		untouchable_start = 0;
		untouchable = 0;
	}

	if (isKicking == true)
		kickTimer += dt;
	// reset kick timer if kick time has pass
	if (kickTimer >= MARIO_KICK_TIME)
	{
		isKicking = false;
		kickTimer = 0;
	}

	if (holdingObject != NULL)
	{
		//shell position attached to mario
		if (nx >= 0)
			holdingObject->SetPosition(x + MARIO_BIG_BBOX_WIDTH, y);
		else
			holdingObject->SetPosition(x - MARIO_BIG_BBOX_WIDTH, y);

		//release if not being held anymore
		if (holdingObject->GetState() != KOOPA_STATE_BEING_HELD)
			holdingObject = NULL;
	}

	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CMario::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
	isOnPlatform = false;
}

void CMario::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (e->ny != 0 && e->obj->IsBlocking())
	{
		vy = 0;
		if (e->ny < 0) isOnPlatform = true;
	}
	else 
	if (e->nx != 0 && e->obj->IsBlocking())
	{
		vx = 0;
	}

	//Be aware: The derived class needs to be detected before the base class
	if (dynamic_cast<CParaGoomba*>(e->obj))
		OnCollisionWithParaGoomba(e);
	else if (dynamic_cast<CGoomba*>(e->obj))
		OnCollisionWithGoomba(e);
	else if (dynamic_cast<CCoin*>(e->obj))
		OnCollisionWithCoin(e);
	else if (dynamic_cast<CQuestionBlock*>(e->obj))
		OnCollisionWithQuestionBlock(e);
	else if (dynamic_cast<CPortal*>(e->obj))
		OnCollisionWithPortal(e);
	else if (dynamic_cast<CVenus*>(e->obj))
		OnCollisionWithVenus(e);
	else if (dynamic_cast<CBulletVenus*>(e->obj))
		OnCollisionWithBulletVenus(e);
	else if (dynamic_cast<CPowerUpItem*>(e->obj))
		OnCollisionWithPowerUpItem(e);
	else if (dynamic_cast<CKoopa*>(e->obj))
		OnCollisionWithKoopa(e);
	else if (dynamic_cast<CBrick*>(e->obj))
		OnCollisionWithBrick(e);
	else if (dynamic_cast<CPit*>(e->obj))
		OnCollisionWithPit(e);
}

void CMario::OnCollisionWithGoomba(LPCOLLISIONEVENT e)
{
	CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);

	// jump on top >> kill Goomba and deflect a bit 
	if (e->ny < 0)
	{
		if (goomba->GetState() != GOOMBA_STATE_DIE)
		{
			goomba->SetState(GOOMBA_STATE_DIE);
			vy = -MARIO_JUMP_DEFLECT_SPEED;
		}
	}
	else // hit by Goomba
	{
		if (goomba->GetState() != GOOMBA_STATE_DIE)
		{
			GetDamaged();
		}
	}
}

void CMario::OnCollisionWithParaGoomba(LPCOLLISIONEVENT e)
{
	CParaGoomba* paragoomba = dynamic_cast<CParaGoomba*>(e->obj);
	DebugOut(L"Paragoomba collision \ns");
	// jump on top >> kill ParaGoomba and deflect a bit 
	if (e->ny < 0)
	{
		if (paragoomba->GetIsGoomba() == false)
		{
			paragoomba->TurnIntoGoomba();
			vy = -MARIO_JUMP_DEFLECT_SPEED;
		}
		else
		{
			if (paragoomba->GetState() != GOOMBA_STATE_DIE)
			{
				paragoomba->SetState(GOOMBA_STATE_DIE);
				vy = -MARIO_JUMP_DEFLECT_SPEED;
			}
		}
	}
	else // hit by ParaGoomba
	{
		if (paragoomba->GetState() != GOOMBA_STATE_DIE)
		{
			GetDamaged();
		}
	}
}

void CMario::OnCollisionWithCoin(LPCOLLISIONEVENT e)
{
	e->obj->Delete();
	coin++;
}

void CMario::OnCollisionWithQuestionBlock(LPCOLLISIONEVENT e)
{
	CQuestionBlock* question = dynamic_cast<CQuestionBlock*>(e->obj);
	if (e->ny > 0)
	{
		if (question->GetState() == QUESTIONBLOCK_STATE_IDLE)
		{
			question->SetState(QUESTIONBLOCK_STATE_BOUNCING_UP);
		}
	}
}

void CMario::OnCollisionWithPortal(LPCOLLISIONEVENT e)
{
	CPortal* p = (CPortal*)e->obj;
	CGame::GetInstance()->InitiateSwitchScene(p->GetSceneId());
}

void CMario::OnCollisionWithVenus(LPCOLLISIONEVENT e)
{
	CVenus* venus = dynamic_cast<CVenus*>(e->obj);
	
	// die if hit Venus
	if (venus->GetState() != VENUS_STATE_DIE)
	{
		{
			GetDamaged();
		}
	}
}

void CMario::OnCollisionWithBulletVenus(LPCOLLISIONEVENT e)
{
	GetDamaged();
}

void CMario::OnCollisionWithPowerUpItem(LPCOLLISIONEVENT e)
{
	CPowerUpItem* item = dynamic_cast<CPowerUpItem*>(e->obj);
	DebugOut(L"PowerUpItem collision \n");
	if (item->GetState() != POWERUPITEM_STATE_IDLE && item->GetState() != POWERUPITEM_STATE_EATEN)
	{
		if (level == MARIO_LEVEL_SMALL)
			SetLevel(MARIO_LEVEL_BIG);
		else if (level == MARIO_LEVEL_BIG)
			SetLevel(MARIO_LEVEL_RACOON);

		item->SetState(POWERUPITEM_STATE_EATEN);
	}
}

void CMario::OnCollisionWithKoopa(LPCOLLISIONEVENT e)
{
	CKoopa* koopa = dynamic_cast<CKoopa*>(e->obj);
	// jump on top >> kill ParaGoomba and deflect a bit 
	if (e->ny < 0)
	{
		if (koopa->GetState() == KOOPA_STATE_WALKING_LEFT || koopa->GetState() == KOOPA_STATE_WALKING_RIGHT)
		{
			koopa->SetState(KOOPA_STATE_SHELL_IDLE);

			vy = -MARIO_JUMP_DEFLECT_SPEED;
		}
		else if (koopa->GetState() == KOOPA_STATE_SHELL_IDLE)
		{
			float xKoopa, yKoopa;
			koopa->GetPosition(xKoopa, yKoopa);

			//Kick the shell
			SetState(MARIO_STATE_KICK);
			if (xKoopa >= x) 
				koopa->SetState(KOOPA_STATE_SHELL_MOVING_RIGHT);
			else
				koopa->SetState(KOOPA_STATE_SHELL_MOVING_LEFT);
		}
		else if (koopa->GetState() == KOOPA_STATE_SHELL_MOVING_RIGHT || koopa->GetState() == KOOPA_STATE_SHELL_MOVING_LEFT)
		{
			koopa->SetState(KOOPA_STATE_SHELL_IDLE);

			vy = -MARIO_JUMP_DEFLECT_SPEED;
		}

	}
	else //Hit not on top
	{
		//A is pressing = able to hold, hold the shell
		if (ableToHold && koopa->GetState() == KOOPA_STATE_SHELL_IDLE)
		{
			this->holdingObject = e->obj;
			CKoopa* koopaShell = dynamic_cast<CKoopa*>(holdingObject);
			DebugOut(L"setheld\n");
			koopaShell->SetState(KOOPA_STATE_BEING_HELD);
		}
		else if (untouchable == 0) 
		{
			if (koopa->GetState() == KOOPA_STATE_WALKING_LEFT || koopa->GetState() == KOOPA_STATE_WALKING_RIGHT
				|| koopa->GetState() == KOOPA_STATE_SHELL_MOVING_RIGHT || koopa->GetState() == KOOPA_STATE_SHELL_MOVING_LEFT)
			{
				GetDamaged();
			}
			else if(koopa->GetState() == KOOPA_STATE_SHELL_IDLE)
			{
				float xKoopa, yKoopa;
				koopa->GetPosition(xKoopa, yKoopa);

				//Kick the shell
				SetState(MARIO_STATE_KICK);
				if (xKoopa >= x) 
					koopa->SetState(KOOPA_STATE_SHELL_MOVING_RIGHT);
				else
					koopa->SetState(KOOPA_STATE_SHELL_MOVING_LEFT);
			}
		}
	}
}

void CMario::OnCollisionWithBrick(LPCOLLISIONEVENT e)
{
	CBrick* brick = dynamic_cast<CBrick*>(e->obj);
	if (e->ny > 0)
	{
		if (brick->GetState() == BRICK_STATE_IDLE )
		{
			if (level != MARIO_LEVEL_SMALL)
			{
				brick->SetIsBreakable(true);
			}
			brick->SetState(BRICK_STATE_BOUNCING_UP);
		}
	}
}

void CMario::OnCollisionWithPit(LPCOLLISIONEVENT e)
{
	SetState(MARIO_STATE_DIE);
}

//
// Get animation ID for small Mario
//
int CMario::GetAniIdSmall()
{
	int aniId = -1;
	if (!isOnPlatform)
	{
		if (abs(ax) == MARIO_ACCEL_RUN_X)
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_SMALL_JUMP_RUN_RIGHT;
			else
				aniId = ID_ANI_MARIO_SMALL_JUMP_RUN_LEFT;
		}
		else
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_SMALL_JUMP_WALK_RIGHT;
			else
				aniId = ID_ANI_MARIO_SMALL_JUMP_WALK_LEFT;
		}
	}
	else
		if (isKicking)
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_SMALL_KICK_RIGHT;
			else
				aniId = ID_ANI_MARIO_SMALL_KICK_LEFT;
		}
		else if (vx == 0)
			{
				if (nx > 0) aniId = ID_ANI_MARIO_SMALL_IDLE_RIGHT;
				else aniId = ID_ANI_MARIO_SMALL_IDLE_LEFT;
			}
			else if (vx > 0)
			{
				if (ax < 0)
					aniId = ID_ANI_MARIO_SMALL_BRACE_RIGHT;
				else if (ax == MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_SMALL_RUNNING_RIGHT;
				else if (ax == MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_MARIO_SMALL_WALKING_RIGHT;
			}
			else // vx < 0
			{
				if (ax > 0)
					aniId = ID_ANI_MARIO_SMALL_BRACE_LEFT;
				else if (ax == -MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_SMALL_RUNNING_LEFT;
				else if (ax == -MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_MARIO_SMALL_WALKING_LEFT;
			}

	if (aniId == -1) aniId = ID_ANI_MARIO_SMALL_IDLE_RIGHT;

	return aniId;
}


//
// Get animdation ID for big Mario
//
int CMario::GetAniIdBig()
{
	int aniId = -1;
	if (!isOnPlatform)
	{
		if (abs(ax) == MARIO_ACCEL_RUN_X)
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_BIG_JUMP_RUN_RIGHT;
			else
				aniId = ID_ANI_MARIO_BIG_JUMP_RUN_LEFT;
		}
		else
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_BIG_JUMP_WALK_RIGHT;
			else
				aniId = ID_ANI_MARIO_BIG_JUMP_WALK_LEFT;
		}
	}
	else
		if (isSitting)
		{
			DebugOut(L"sit");
			if (nx >= 0)
				aniId = ID_ANI_MARIO_BIG_SIT_RIGHT;
			else
				aniId = ID_ANI_MARIO_BIG_SIT_LEFT;
		}
		else
			if (isKicking)
			{
				if(nx >= 0)
					aniId = ID_ANI_MARIO_BIG_KICK_RIGHT;
				else
					aniId = ID_ANI_MARIO_BIG_KICK_LEFT;
			}
			else if (vx == 0)
			{
				if (nx > 0) aniId = ID_ANI_MARIO_BIG_IDLE_RIGHT;
				else aniId = ID_ANI_MARIO_BIG_IDLE_LEFT;
			}
			else if (vx > 0)
			{
				if (ax < 0)
					aniId = ID_ANI_MARIO_BIG_BRACE_RIGHT;
				else if (ax == MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_BIG_RUNNING_RIGHT;
				else if (ax == MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_MARIO_BIG_WALKING_RIGHT;
			}
			else // vx < 0
			{
				if (ax > 0)
					aniId = ID_ANI_MARIO_BIG_BRACE_LEFT;
				else if (ax == -MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_BIG_RUNNING_LEFT;
				else if (ax == -MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_MARIO_BIG_WALKING_LEFT;
			}

	if (aniId == -1) aniId = ID_ANI_MARIO_BIG_IDLE_RIGHT;

	return aniId;
}

//
// Get animdation ID for racoon Mario
//
int CMario::GetAniIdRacoon()
{
	int aniId = -1;
	if (!isOnPlatform)
	{
		if (abs(ax) == MARIO_ACCEL_RUN_X)
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_RACOON_JUMP_RUN_RIGHT;
			else
				aniId = ID_ANI_MARIO_RACOON_JUMP_RUN_LEFT;
		}
		else
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_RACOON_JUMP_WALK_RIGHT;
			else
				aniId = ID_ANI_MARIO_RACOON_JUMP_WALK_LEFT;
		}
	}
	else
		if (isSitting)
		{
			if (nx > 0)
				aniId = ID_ANI_MARIO_RACOON_SIT_RIGHT;
			else
				aniId = ID_ANI_MARIO_RACOON_SIT_LEFT;
		}
		else
			if (isKicking)
			{
				if (nx > 0)
					aniId = ID_ANI_MARIO_RACOON_KICK_RIGHT;
				else
					aniId = ID_ANI_MARIO_RACOON_KICK_LEFT;
			}
			else if (vx == 0)
			{
				if (nx > 0) aniId = ID_ANI_MARIO_RACOON_IDLE_RIGHT;
				else aniId = ID_ANI_MARIO_RACOON_IDLE_LEFT;
			}
			else if (vx > 0)
			{
				if (ax < 0)
					aniId = ID_ANI_MARIO_RACOON_BRACE_RIGHT;
				else if (ax == MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_RACOON_RUNNING_RIGHT;
				else if (ax == MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_MARIO_RACOON_WALKING_RIGHT;
			}
			else // vx < 0
			{
				if (ax > 0)
					aniId = ID_ANI_MARIO_RACOON_BRACE_LEFT;
				else if (ax == -MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_RACOON_RUNNING_LEFT;
				else if (ax == -MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_MARIO_RACOON_WALKING_LEFT;
			}

	if (aniId == -1) aniId = ID_ANI_MARIO_RACOON_IDLE_RIGHT;

	return aniId;
}

void CMario::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	int aniId = -1;

	if (state == MARIO_STATE_DIE)
		aniId = ID_ANI_MARIO_DIE;
	else if (level == MARIO_LEVEL_BIG)
		aniId = GetAniIdBig();
	else if (level == MARIO_LEVEL_RACOON)
		aniId = GetAniIdRacoon();
	else if (level == MARIO_LEVEL_SMALL)
		aniId = GetAniIdSmall();

	animations->Get(aniId)->Render(x, y);

	//RenderBoundingBox();
	
	DebugOutTitle(L"Coins: %d", coin);
}

void CMario::SetState(int state)
{
	// DIE is the end state, cannot be changed! 
	if (this->state == MARIO_STATE_DIE) return; 

	switch (state)
	{
	case MARIO_STATE_KICK:
		isKicking = true;
	case MARIO_STATE_RUNNING_RIGHT:
		if (isSitting) break;
		maxVx = MARIO_RUNNING_SPEED;
		ax = MARIO_ACCEL_RUN_X;
		break;
	case MARIO_STATE_RUNNING_LEFT:
		if (isSitting) break;
		maxVx = -MARIO_RUNNING_SPEED;
		ax = -MARIO_ACCEL_RUN_X;
		break;
	case MARIO_STATE_WALKING_RIGHT:
		if (isSitting) break;
		maxVx = MARIO_WALKING_SPEED;
		ax = MARIO_ACCEL_WALK_X;
		break;
	case MARIO_STATE_WALKING_LEFT:
		if (isSitting) break;
		maxVx = -MARIO_WALKING_SPEED;
		ax = -MARIO_ACCEL_WALK_X;
		break;
	case MARIO_STATE_JUMP:
		if (isSitting) break;
		if (isOnPlatform)
		{
			if (abs(this->vx) == MARIO_RUNNING_SPEED)
				vy = -MARIO_JUMP_RUN_SPEED_Y;
			else
				vy = -MARIO_JUMP_SPEED_Y;
		}
		break;

	case MARIO_STATE_RELEASE_JUMP:
		if (vy < 0) vy += MARIO_JUMP_SPEED_Y / 2;
		break;

	case MARIO_STATE_SIT:
		if (isOnPlatform && level != MARIO_LEVEL_SMALL)
		{
			state = MARIO_STATE_IDLE;
			isSitting = true;
			vx = 0; vy = 0.0f;
			y +=MARIO_SIT_HEIGHT_ADJUST;
		}
		break;

	case MARIO_STATE_SIT_RELEASE:
		if (isSitting)
		{
			isSitting = false;
			state = MARIO_STATE_IDLE;
			y -= MARIO_SIT_HEIGHT_ADJUST;
		}
		break;
	case MARIO_STATE_IDLE:
		ax = 0.0f;
		vx = 0.0f;
		break;

	case MARIO_STATE_DIE:
		vy = -MARIO_JUMP_DEFLECT_SPEED;
		vx = 0;
		ax = 0;
		break;
	}

	CGameObject::SetState(state);
}

void CMario::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	if (level == MARIO_LEVEL_BIG)
	{
		if (isSitting)
		{
			left = x - MARIO_BIG_SITTING_BBOX_WIDTH / 2;
			top = y - MARIO_BIG_SITTING_BBOX_HEIGHT / 2;
			right = left + MARIO_BIG_SITTING_BBOX_WIDTH;
			bottom = top + MARIO_BIG_SITTING_BBOX_HEIGHT;
		}
		else 
		{
			left = x - MARIO_BIG_BBOX_WIDTH/2;
			top = y - MARIO_BIG_BBOX_HEIGHT/2;
			right = left + MARIO_BIG_BBOX_WIDTH;
			bottom = top + MARIO_BIG_BBOX_HEIGHT;
		}
	}
	else if (level == MARIO_LEVEL_RACOON)
	{
		if (isSitting)
		{
			left = x - MARIO_RACOON_SITTING_BBOX_WIDTH / 2;
			top = y - MARIO_RACOON_SITTING_BBOX_HEIGHT / 2;
			right = left + MARIO_RACOON_SITTING_BBOX_WIDTH;
			bottom = top + MARIO_RACOON_SITTING_BBOX_HEIGHT;
		}
		else
		{
			left = x - MARIO_RACOON_BBOX_WIDTH / 2;
			top = y - MARIO_RACOON_BBOX_HEIGHT / 2;
			right = left + MARIO_RACOON_BBOX_WIDTH;
			bottom = top + MARIO_RACOON_BBOX_HEIGHT;
		}
	}
	else
	{
		left = x - MARIO_SMALL_BBOX_WIDTH/2;
		top = y - MARIO_SMALL_BBOX_HEIGHT/2;
		right = left + MARIO_SMALL_BBOX_WIDTH;
		bottom = top + MARIO_SMALL_BBOX_HEIGHT;
	}
}

void CMario::GetDamaged()
{
	if(untouchable) return;

	if (level == MARIO_LEVEL_SMALL)
	{
		DebugOut(L">>> Mario DIE >>> \n");
		SetState(MARIO_STATE_DIE);
		return;
	}
	else if (level == MARIO_LEVEL_RACOON)
		level = MARIO_LEVEL_BIG;
	else if (level == MARIO_LEVEL_BIG)
		level = MARIO_LEVEL_SMALL;
	
	StartUntouchable();
}

void CMario::Throw()
{
	if (holdingObject != NULL)
	{
		CKoopa* koopaShell = dynamic_cast<CKoopa*>(holdingObject);
		//Kick and trigger Shell moving
		DebugOut(L"throw\n");
		SetState(MARIO_STATE_KICK);
		
		if (nx > 0)
			koopaShell->SetState(KOOPA_STATE_SHELL_MOVING_RIGHT);
		else
			koopaShell->SetState(KOOPA_STATE_SHELL_MOVING_LEFT);
		//Release
		this->holdingObject = NULL;
	}
}

void CMario::SetLevel(int l)
{
	// Adjust position to avoid falling off platform
	if (this->level == MARIO_LEVEL_SMALL)
	{
		y -= (MARIO_BIG_BBOX_HEIGHT - MARIO_SMALL_BBOX_HEIGHT) / 2;
	}
	level = l;
}

