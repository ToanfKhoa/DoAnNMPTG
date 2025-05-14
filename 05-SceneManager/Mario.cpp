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
#include "CSpawnBox.h"
#include "PlayScene.h"
#include "CExtraLifeMushroom.h"

CMario::CMario(float x, float y) : CGameObject(x, y)
{
		isSitting = false;
		maxVx = 0.0f;
		ax = 0.0f;
		ay = MARIO_GRAVITY;
		nx = 1;

		level = MARIO_LEVEL_SMALL;
		untouchable = 0;
		untouchable_start = -1;
		isOnPlatform = false;
		coin = 0;

		kickTimer == 0;
		isKicking == false;

		jumpTimer = 0;
		isJumping = false;

		wagTimer = 0;
		isWagging = false;

		isTransforming = false;

		holdingObject = NULL;
		ableToHold = false;

		isWagging = false;

		flyTimer = 0;
		ableToFly = false;

		runPower = 0;

		hitBox = new CMarioHitBox(x, y, MARIO_HIT_BOX_WIDTH, MARIO_HIT_BOX_HEIGHT);
		CPlayScene* playScene = dynamic_cast<CPlayScene*>(CGame::GetInstance()->GetCurrentScene());
		if (playScene != NULL)
		{
			playScene->AddObject(hitBox);
		}
		else
		{
			DebugOut(L"[ERROR] Scene is NULL\n");
		}
}

void CMario::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	//DebugOut(L"timerattack %d\n", attackTimer);
	vx += ax * dt;
	vy += ay * dt;

	DebugOut(L"mario x,y : %f %f\n", x, y);
	//Mario slowly decrease vx when stop moving
	if (state == MARIO_STATE_IDLE)
	{
		if (abs(vx) > MARIO_MIN_SPEED)
			vx *= MARIO_FRICTION;
		else
			vx = 0; //Mario completely stop 
	}

	//Limit the max speed, check to prevent vx from reversing direction when maxVx changes suddenly
	if (abs(vx) > abs(maxVx) && (vx * maxVx >= 0)) vx = maxVx;

	// reset untouchable timer if untouchable time has passed
	if (GetTickCount64() - untouchable_start > MARIO_UNTOUCHABLE_TIME)
	{
		untouchable_start = 0;
		untouchable = 0;
	}

	// reset kick timer if kick time has pass
	if (isKicking == true)
	{
		kickTimer += dt;
		if (kickTimer >= MARIO_KICK_TIME)
		{
			isKicking = false;
			kickTimer = 0;
		}
	}

	//Limit jumping time of Mario
	if (isJumping == true)
	{
		jumpTimer += dt;
		if (jumpTimer >= MARIO_JUMP_TIME)
			SetState(MARIO_STATE_RELEASE_JUMP);
	}

	//Limit wagging time of Mario
	if (isWagging == true)
	{
		wagTimer += dt;
		if (wagTimer >= MARIO_WAG_TIME)
		{
			isWagging = false;
			wagTimer = 0;
		}
	}

	//Limit flying time
	if (ableToFly == true)
	{
		flyTimer += dt;
		if (flyTimer >= MARIO_FLY_TIME)
		{
			ableToFly = false;
			flyTimer = 0;
		}
	}

	//Run power
	if ((level == MARIO_LEVEL_RACOON && abs(vx) == MARIO_RUNNING_SPEED && isOnPlatform) || ableToFly == true) //Running or is in flying time
	{
		//Increase and keep runPower at max value
		if (runPower < MARIO_MAX_RUN_POWER)
			runPower += dt;
		else
			runPower = MARIO_MAX_RUN_POWER;
	}
	else
	{
		//Decrease and keep runPower at 0
		if(runPower > 0)
			runPower -= dt;
		else
			runPower = 0;
	}

	//Mario will transform while stop scenetime, transform stop when scene countinue to update
	if (isTransforming == true)
	{
		isTransforming = false;
	}

	CCollision::GetInstance()->Process(this, dt, coObjects);

	if (holdingObject != NULL)
	{
		//shell position attached to mario
		if (nx >= 0)
			holdingObject->SetPosition(x + MARIO_BIG_BBOX_WIDTH, y);
		else
			holdingObject->SetPosition(x - MARIO_BIG_BBOX_WIDTH, y);

		//release if not being held anymore
		if (holdingObject->GetState() != KOOPA_STATE_BEING_HELD)
		{
			if (nx >= 0)
				holdingObject->SetPosition(x + MARIO_BIG_BBOX_WIDTH, y - KOOPA_BBOX_HEIGHT / 2);
			else
				holdingObject->SetPosition(x - MARIO_BIG_BBOX_WIDTH, y - KOOPA_BBOX_HEIGHT / 2);

			if (holdingObject->GetState() == KOOPA_STATE_WALKING_LEFT || holdingObject->GetState() == KOOPA_STATE_WALKING_RIGHT) GetDamaged();


			holdingObject = NULL;
		}
	}


	//Limit attacking time and set position hitbox

	if (isAttacking == true)
	{
		attackTimer += dt;
		if(attackTimer >= MARIO_ATTACK_TIME / 3)
			hitBox->SetPosition(x + nx * MARIO_RACOON_BBOX_WIDTH / 2, y + MARIO_RACOON_BBOX_HEIGHT / 4);
		else
			hitBox->SetPosition(x - nx * MARIO_RACOON_BBOX_WIDTH / 2, y + MARIO_RACOON_BBOX_HEIGHT / 4);

		if (attackTimer >= MARIO_ATTACK_TIME)
		{
			isAttacking = false;
			hitBox->SetIsActive(false);
			attackTimer = 0;
		}
	}
	else
		hitBox->SetPosition(x, y + MARIO_RACOON_BBOX_HEIGHT / 4);

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
		if(e->ny > 0)
			SetState(MARIO_STATE_RELEASE_JUMP); //Deflect downward when hitting a block above
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
	//else if (dynamic_cast<CPowerUpItem*>(e->obj))
	//	OnCollisionWithPowerUpItem(e);
	else if (dynamic_cast<CKoopa*>(e->obj))
		OnCollisionWithKoopa(e);
	else if (dynamic_cast<CBrick*>(e->obj))
		OnCollisionWithBrick(e);
	else if (dynamic_cast<CPit*>(e->obj))
		OnCollisionWithPit(e);
	else if (dynamic_cast<CSpawnBox*>(e->obj))
		OnCollisionWithSpawnBox(e);
}

void CMario::OnOverlapWith(LPCOLLISIONEVENT e)
{
	if (dynamic_cast<CBulletVenus*>(e->obj))
		OnCollisionWithBulletVenus(e);
	else if (dynamic_cast<CPowerUpItem*>(e->obj))
		OnOverlapWithPowerUpItem(e);
	else if (dynamic_cast<CExtraLifeMushroom*>(e->obj))
		OnOverlapWithExtraLifeMushroom(e);
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
		if (goomba->GetState() != GOOMBA_STATE_DIE && goomba->GetState() != GOOMBA_STATE_BOUNCE_DEATH)
		{
			DebugOut(L"Mario collison with goomba state: %d\n", GetState());
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
		if (paragoomba->GetState() != GOOMBA_STATE_DIE && paragoomba->GetState() != GOOMBA_STATE_BOUNCE_DEATH)
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

void CMario::OnOverlapWithPowerUpItem(LPCOLLISIONEVENT e)
{
	CPowerUpItem* item = dynamic_cast<CPowerUpItem*>(e->obj);
	if (item->GetState() != POWERUPITEM_STATE_IDLE && item->GetState() != POWERUPITEM_STATE_EATEN)
	{
		if (level == MARIO_LEVEL_SMALL)
			SetLevel(MARIO_LEVEL_BIG);
		else if (level == MARIO_LEVEL_BIG)
			SetLevel(MARIO_LEVEL_RACOON);

		item->SetState(POWERUPITEM_STATE_EATEN);
	}
}

void CMario::OnOverlapWithExtraLifeMushroom(LPCOLLISIONEVENT e)
{
	CExtraLifeMushroom* item = dynamic_cast<CExtraLifeMushroom*>(e->obj);
	if (item->GetState() != EXTRALIFEMUSHROOM_STATE_IDLE && item->GetState() != EXTRALIFEMUSHROOM_STATE_EATEN)
	{
		//1-up 

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
			if (level == MARIO_LEVEL_SMALL)
			{
				brick->SetState(BRICK_STATE_BOUNCING_UP);
			}
			else
				brick->SetState(BRICK_STATE_BROKEN);
		}
	}
}

void CMario::OnCollisionWithPit(LPCOLLISIONEVENT e)
{
	SetState(MARIO_STATE_DIE);
}

void CMario::OnCollisionWithSpawnBox(LPCOLLISIONEVENT e)
{
	CSpawnBox* spawnBox = dynamic_cast<CSpawnBox*>(e->obj);

	spawnBox->Spawn();
	spawnBox->SetIsActivated(true);
}

//
// Get animation ID for small Mario
//
int CMario::GetAniIdSmall()
{
	int aniId = -1;
	if (!isOnPlatform)
	{
		if (holdingObject != NULL)
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_SMALL_HOLDING_JUMP_RIGHT;
			else
				aniId = ID_ANI_MARIO_SMALL_HOLDING_JUMP_LEFT;
		}
		else if (abs(ax) == MARIO_ACCEL_RUN_X)
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
		else if (holdingObject != NULL)
		{
			if (vx == 0)
			{
				if (nx > 0) aniId = ID_ANI_MARIO_SMALL_HOLDING_IDLE_RIGHT;
				else aniId = ID_ANI_MARIO_SMALL_HOLDING_IDLE_LEFT;
			}
			else if (nx > 0) //Turn immediately without braking
				aniId = ID_ANI_MARIO_SMALL_HOLDING_WALKING_RIGHT;
			else
				aniId = ID_ANI_MARIO_SMALL_HOLDING_WALKING_LEFT;
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
				else if (abs(vx) == MARIO_RUNNING_SPEED)
					aniId = ID_ANI_MARIO_SMALL_RUNNING_RIGHT;
				else 
					aniId = ID_ANI_MARIO_SMALL_WALKING_RIGHT;
			}
			else // vx < 0
			{
				if (ax > 0)
					aniId = ID_ANI_MARIO_SMALL_BRACE_LEFT;
				else if (abs(vx) == MARIO_RUNNING_SPEED)
					aniId = ID_ANI_MARIO_SMALL_RUNNING_LEFT;
				else
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
	if (isTransforming == true)
	{
		if (nx >= 0)
			aniId = ID_ANI_MARIO_BIG_TRANSFORM_RIGHT;
		else
			aniId = ID_ANI_MARIO_BIG_TRANSFORM_LEFT;
	}
	else if (!isOnPlatform)
	{
		if (holdingObject != NULL)
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_BIG_HOLDING_JUMP_RIGHT;
			else
				aniId = ID_ANI_MARIO_BIG_HOLDING_JUMP_LEFT;
		}
		else if (abs(ax) == MARIO_ACCEL_RUN_X)
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
			else if (holdingObject != NULL)
			{
				if (vx == 0)
				{
					if (nx > 0) aniId = ID_ANI_MARIO_BIG_HOLDING_IDLE_RIGHT;
					else aniId = ID_ANI_MARIO_BIG_HOLDING_IDLE_LEFT;
				}
				else if (nx > 0) //Turn immediately without braking
					aniId = ID_ANI_MARIO_BIG_HOLDING_WALKING_RIGHT;
				else 
					aniId = ID_ANI_MARIO_BIG_HOLDING_WALKING_LEFT;
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
				else if (abs(vx) == MARIO_RUNNING_SPEED)
					aniId = ID_ANI_MARIO_BIG_RUNNING_RIGHT;
				else
					aniId = ID_ANI_MARIO_BIG_WALKING_RIGHT;
			}
			else // vx < 0
			{
				if (ax > 0)
					aniId = ID_ANI_MARIO_BIG_BRACE_LEFT;
				else if (abs(vx) == MARIO_RUNNING_SPEED)
					aniId = ID_ANI_MARIO_BIG_RUNNING_LEFT;
				else
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
	if (isTransforming == true)
	{
		aniId = ID_ANI_MARIO_RACOON_TRANSFORM;
	}
	else if (isAttacking && !isSitting)
	{
		if (nx > 0)
			aniId = ID_ANI_MARIO_RACOON_ATTACK_RIGHT;
		else
			aniId = ID_ANI_MARIO_RACOON_ATTACK_LEFT;
	}
	else if (!isOnPlatform)
	{
		if (holdingObject != NULL)
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_RACOON_HOLDING_JUMP_RIGHT;
			else
				aniId = ID_ANI_MARIO_RACOON_HOLDING_JUMP_LEFT;
		}
		else if (isWagging)
		{
			if (ableToFly)
			{
				if (nx >= 0)
					aniId = ID_ANI_MARIO_RACOON_JUMP_WAG_RIGHT;
				else
					aniId = ID_ANI_MARIO_RACOON_JUMP_WAG_LEFT;
			}
			else
			{
				if (nx >= 0)
					aniId = ID_ANI_MARIO_RACOON_FALL_WAG_RIGHT;
				else
					aniId = ID_ANI_MARIO_RACOON_FALL_WAG_LEFT;
			}
		}
		else if (runPower == MARIO_MAX_RUN_POWER)
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_RACOON_JUMP_RUN_RIGHT;
			else
				aniId = ID_ANI_MARIO_RACOON_JUMP_RUN_LEFT;
		}
		else if (vy > 0) //falling
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_RACOON_FALL_RIGHT;
			else
				aniId = ID_ANI_MARIO_RACOON_FALL_LEFT;
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
			else if (holdingObject != NULL)
			{
				if (vx == 0)
				{
					if (nx > 0) aniId = ID_ANI_MARIO_RACOON_HOLDING_IDLE_RIGHT;
					else aniId = ID_ANI_MARIO_RACOON_HOLDING_IDLE_LEFT;
				}
				else if (nx > 0) //Turn immediately without braking
					aniId = ID_ANI_MARIO_RACOON_HOLDING_WALKING_RIGHT;
				else
					aniId = ID_ANI_MARIO_RACOON_HOLDING_WALKING_LEFT;
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
				else if (runPower == MARIO_MAX_RUN_POWER)
					aniId = ID_ANI_MARIO_RACOON_RUNNING_RIGHT;
				else
					aniId = ID_ANI_MARIO_RACOON_WALKING_RIGHT;
			}
			else // vx < 0
			{
				if (ax > 0)
					aniId = ID_ANI_MARIO_RACOON_BRACE_LEFT;
				else if (runPower == MARIO_MAX_RUN_POWER)
					aniId = ID_ANI_MARIO_RACOON_RUNNING_LEFT;
				else
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

	//blink effect
	if (untouchable==1)
	{
		if ((GetTickCount64()/ 100) % 2 == 0) return;
	}

	if (abs(ax) == MARIO_ACCEL_RUN_X)
		animations->Get(aniId)->RenderWithSpeed(x, y, MARIO_RUNNING_SPEED_RENDER); //Speed up render frame time while running
	else
		animations->Get(aniId)->Render(x, y);
	
	RenderBoundingBox();
	
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
			isJumping = true;
			ay = 0;

			//Start Fly time if has enough power
			if (runPower == MARIO_MAX_RUN_POWER && ableToFly == false)
				ableToFly = true;

			if (abs(this->vx) == MARIO_RUNNING_SPEED)
				vy = -MARIO_JUMP_RUN_SPEED_Y;
			else
				vy = -MARIO_JUMP_SPEED_Y;
		}
		else if (level == MARIO_LEVEL_RACOON && ableToFly == true) //Wag tail to keep flying
		{
			isWagging = true;
			ay = 0;
			vy = -MARIO_JUMP_SPEED_Y;
		}
		else if (level == MARIO_LEVEL_RACOON && vy > 0) //Wag tail in Raccoon form while falling
		{
			isWagging = true;
			vy = MARIO_JUMP_SPEED_Y / 1000;
			ay = MARIO_GRAVITY / 2;
		}

		break;

	case MARIO_STATE_RELEASE_JUMP:
		ay = MARIO_GRAVITY;
		jumpTimer = 0;
		isJumping = false;
		if (vy < 0) vy += MARIO_JUMP_SPEED_Y / 2;
		break;

	case MARIO_STATE_SIT:
		if (isOnPlatform && level != MARIO_LEVEL_SMALL)
		{
			state = MARIO_STATE_IDLE;
			isSitting = true;
			vy = 0.0f;
			ax = 0;
			
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
		ax = 0;
		break;

	case MARIO_STATE_DIE:
		vy = -MARIO_JUMP_DEFLECT_SPEED;
		vx = 0;
		ax = 0;
		ay = MARIO_GRAVITY;
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
	DebugOut(L"Mario damage\n");
	if (level == MARIO_LEVEL_SMALL)
	{
		DebugOut(L"Mario damage in small\n");
		DebugOut(L">>> Mario DIE >>> \n");
		SetState(MARIO_STATE_DIE);
		return;
	}
	else if (level == MARIO_LEVEL_RACOON)
		level = MARIO_LEVEL_BIG;
	else if (level == MARIO_LEVEL_BIG)
		level = MARIO_LEVEL_SMALL;
	
	StartUntouchable();

	//time stop effect
	CPlayScene* scene = dynamic_cast<CPlayScene*>(CGame::GetInstance()->GetCurrentScene());
	if (scene) scene->StartTimeStop();
}

void CMario::Throw()
{
	if (holdingObject != NULL)
	{
		CKoopa* koopaShell = dynamic_cast<CKoopa*>(holdingObject);
		//Kick and trigger Shell moving
		DebugOut(L"throw\n");
		SetState(MARIO_STATE_KICK);

		if (GetLevel() == MARIO_LEVEL_SMALL) koopaShell->AlignYOnTransform();
		
		if (nx > 0)
			koopaShell->SetState(KOOPA_STATE_SHELL_MOVING_RIGHT);
		else
			koopaShell->SetState(KOOPA_STATE_SHELL_MOVING_LEFT);
		//Release
		this->holdingObject = NULL;
	}
}

void CMario::Attack()
{
	if (isSitting)
		return;
	isAttacking = true; 
	hitBox->SetIsActive(true); 
}

void CMario::SetLevel(int l)
{
	// Adjust position to avoid falling off platform
	if (this->level == MARIO_LEVEL_SMALL)
	{
		y -= (MARIO_BIG_BBOX_HEIGHT - MARIO_SMALL_BBOX_HEIGHT) / 2;
	}
	
	//Transform effect
	if (l > level)
		isTransforming = true;

	level = l;

	//Time Stop
	CPlayScene* scene = dynamic_cast<CPlayScene*>(CGame::GetInstance()->GetCurrentScene());
	if (scene) scene->StartTimeStop();
}

