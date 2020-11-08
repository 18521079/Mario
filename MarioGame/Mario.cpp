#include <algorithm>
#include <assert.h>
#include "Utils.h"

#include "Mario.h"
#include "Game.h"
#include "Animations.h"
#include "Goomba.h"
#include "Portal.h"
#include "Box.h"
#include "KooPas.h"
#include "BackGroundCollision.h"
#include"QuestionBlock.h"
#include"Ball.h"
#include"Coin.h"

CMario::CMario(float x, float y) : CGameObject()
{
	level = MARIO_LEVEL_SMALL;
	SetState(MARIO_STATE_IDLE);
	SetHolding(0);
	start_x = x;
	start_y = y;
	this->x = x;
	this->y = y;

}

void CMario::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	// Calculate dx, dy 
	CGameObject::Update(dt);
	// Simple fall down
	vy += MARIO_GRAVITY * dt;

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	// turn off collision when die 
	if (state != MARIO_STATE_DIE)
		CalcPotentialCollisions(coObjects, coEvents);

	// reset untouchable timer if untouchable time has passed
	if (GetTickCount() - untouchable_start > 500)
	{
		untouchable_start = 0;
		untouchable = 0;
	}
	/*if (GetTickCount() - preIDLE_start > 400)
	{
		preIDLE_start = 0;
		preidle = 0;
		if(nx>0)
		SetState(MARIO_STATE_WALKING_RIGHT);
		else if(nx < 0)
		SetState(MARIO_STATE_WALKING_LEFT);

	}*/
	// No collision occured, proceed normally
	if (GetTickCount() - kick_start > 200 )
	{
		AniKick = 0;
	}
	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		float rdx = 0;
		float rdy = 0;

		// TODO: This is a very ugly designed function!!!!
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		// how to push back Mario if collides with a moving objects, what if Mario is pushed this way into another object?
		//if (rdx != 0 && rdx!=dx)
		//	x += nx*abs(rdx); 

		// block every object first!
		x += min_tx * dx + nx * 0.4f;
		y += min_ty * dy + ny * 0.4f;

		if (nx != 0) vx = 0;
		if (ny != 0) vy = 0;

		if (ny != 0)
		{
			vy = 0;
			if (GetJumping() == 1)
			{
				Jump = 0;
			}
		}

		//
		// Collision logic with other objects
		//
		
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			float x, y;
			GetPosition(x, y);

			if (dynamic_cast<CGoomba*>(e->obj)) // if e->obj is Goomba 
			{
				CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);

				// jump on top >> kill Goomba and deflect a bit 
				if (e->ny < 0)
				{
					if (goomba->GetState() != GOOMBA_STATE_DIE)
					{
						goomba->SetState(GOOMBA_STATE_DIE);
						goomba->GoombaDie();
						goomba->SetTickCount();
						vy = -MARIO_JUMP_DEFLECT_SPEED;
					}
				}
				else if (e->nx != 0)
				{
					if (level == MARIO_LEVEL_BIG)
					{
						
						SetLevel(MARIO_LEVEL_SMALL);
						if(nx>0)
						SetPosition(x-20, y);
						else if(nx<0)
						SetPosition(x+20, y);
					}
					else if (level == MARIO_LEVEL_SMALL)
					{
						//StartUntouchable();
						SetState(MARIO_STATE_DIE);
					}
					else
					{
						StartUntouchable();
						SetLevel(MARIO_LEVEL_BIG);
						if (nx > 0)
							SetPosition(x - 20, y);
						else if (nx < 0)
							SetPosition(x + 20, y);
					}
				}
			}
			else if (dynamic_cast<CKoopas*>(e->obj)) // if e->obj is Goomba 
			{
				CKoopas* koopas = dynamic_cast<CKoopas*>(e->obj);
				/*if (Hold == 1)
				{
					koopas->SetHolding(1);
				}*/
				//// jump on top >> kill Goomba and deflect a bit 
		
				if (e->ny < 0)
				{
					if (koopas->GetState() != KOOPAS_STATE_SHELL)
					{
						koopas->SetState(KOOPAS_STATE_SHELL);
						vy = -MARIO_JUMP_DEFLECT_SPEED;
						
					}
	
				}
				
				//
				else if (nx != 0)
				{
					if (koopas->GetState() != KOOPAS_STATE_SHELL)
					{

						if (level == MARIO_LEVEL_BIG)
						{

							SetLevel(MARIO_LEVEL_SMALL);
							if (nx > 0)
								SetPosition(x - 30, y);
							else if (nx < 0)
								SetPosition(x + 30, y);

						}
						else if (level == MARIO_LEVEL_SMALL)
						{
							//StartUntouchable();
							SetState(MARIO_STATE_DIE);
						}
						else
						{
							SetLevel(MARIO_LEVEL_BIG);
							if (nx > 0)
								SetPosition(x - 20, y);
							else if (nx < 0)
								SetPosition(x + 20, y);
						}
					}
					else if(koopas->GetState() == KOOPAS_STATE_SHELL)
					{
						
						if(Hold == 1)
						{
							SetAniHolding(1);
							koopas->SetHolding(1);
						}
						else
						{
							//koopas->SetMarioKick(1);
							SetAniKick(1);
							StartKick();
							if (nx > 0)
								koopas->SetState(SHELL_STATE_WALKING_RIGHT);
							else
								koopas->SetState(SHELL_STATE_WALKING_LEFT);
						}
					}
				}
				
			}
			else if (dynamic_cast<CQuestionBlock*>(e->obj)) // if e->obj is Goomba 
			{
				CQuestionBlock* block = dynamic_cast<CQuestionBlock*>(e->obj);


				// jump on top >> kill Goomba and deflect a bit 
				if (e->ny > 0)
				{
					if (block->GetState() == BLOCK_STATE_ACTIVITY)
					{
						block->SetState(BLOCK_STATE_INACTIVITY);
					}

				}
			}
			else if (dynamic_cast<CCoin*>(e->obj)) // if e->obj is Goomba 
			{
				CCoin* coin = dynamic_cast<CCoin*>(e->obj);

			// jump on top >> kill Goomba and deflect a bit 
				if (e->ny > 0 || e->nx !=0)
				{
					coin->SetState(COIN_STATE_DISAPPEAR);
				}
			}
			if (dynamic_cast<CBall*>(e->obj)) // if e->obj is Goomba 
			{
				if (e->ny > 0)
				{
					CBall* ball = dynamic_cast<CBall*>(e->obj);
					ball->ActivityStart();
					ball->SetPosition(409, 70);
				}
			}
		}
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void CMario::Render()
{
	int ani = -1;
	if (state == MARIO_STATE_DIE)
		ani = MARIO_ANI_DIE;
	
	else
	{
		if (level == MARIO_LEVEL_BIG)
		{
			if (state == MARIO_STATE_IDLE)
			{
			
				if (vx == 0)
				{
					if (nx > 0)
					{
						ani = MARIO_ANI_BIG_IDLE_RIGHT;
					}
					else ani = MARIO_ANI_BIG_IDLE_LEFT;
				}
			}
			
			else if (state == MARIO_STATE_SIT)
			{
				if (nx > 0)
					ani = MARIO_ANI_BIG_SIT_RIGHT;
				else /*if(nx<0)*/
					ani = MARIO_ANI_BIG_SIT_LEFT;
			}
			else
			{
				if (ny > 0 && nx > 0 )
					ani = MARIO_ANI_BIG_JUMP_RIGHT;
				else if (ny > 0 && nx < 0)
					ani = MARIO_ANI_BIG_JUMP_LEFT;
				else if (AniHold == 1 && nx > 0)
				{
					ani = MARIO_ANI_BIG_HOLD_RIGHT;
				}
				else if (AniHold == 1 && nx < 0)
				{
					ani = MARIO_ANI_BIG_HOLD_LEFT;
				}
				else if (AniKick == 1 && nx > 0)
				{
					ani = MARIO_ANI_FIRE_IDLE_RIGHT;
				}
				else if (AniKick == 1 && nx < 0)
				{
					ani = MARIO_ANI_BIG_KICK_LEFT;
				}
				else if (Jump == 1 && nx>0)
				{
					ani = MARIO_ANI_BIG_JUMP_RIGHT;
				}
				else if (Jump == 1 && nx < 0)
				{
					ani = MARIO_ANI_BIG_JUMP_LEFT;
				}
				
				else if (nx > 0 )
					ani = MARIO_ANI_BIG_WALKING_RIGHT;
				else if(ny !=1 )
					ani = MARIO_ANI_BIG_WALKING_LEFT;
			}
		}
		
		if (level == MARIO_LEVEL_SMALL)
		{
			if (state == MARIO_STATE_IDLE)
			{
				if (vx == 0)
				{
					if (nx > 0) ani = MARIO_ANI_SMALL_IDLE_RIGHT;
					else ani = MARIO_ANI_SMALL_IDLE_LEFT;

				}
			}
			else
			{
				 if (ny > 0 && nx > 0)
					ani = MARIO_ANI_SMALL_JUMP_RIGHT;
				 else if (AniHold ==1 && nx > 0)
				 {
					 ani = MARIO_ANI_SMALL_HOLD_RIGHT;
				 }
				 else if (AniHold == 1 && nx < 0)
				 {
					 ani = MARIO_ANI_SMALL_HOLD_LEFT;
				 }
				  else if (ny > 0 && nx < 0)
					ani = MARIO_ANI_SMALL_JUMP_LEFT;
				  else if (Jump == 1 && nx > 0)
				 {
					 ani = MARIO_ANI_SMALL_JUMP_RIGHT;
				 }
				  else if (Jump == 1 && nx < 0)
				 {
					 ani = MARIO_ANI_SMALL_JUMP_LEFT;
				 }
				else if (nx > 0 )
					ani = MARIO_ANI_SMALL_WALKING_RIGHT;
				else if (nx < 0)
					ani = MARIO_ANI_SMALL_WALKING_LEFT;


			}
		}
		
		if (level == MARIO_LEVEL_TAIL)
		{
			if (state == MARIO_STATE_IDLE)
			{
				if (vx == 0)
				{
					if (nx > 0) ani = MARIO_ANI_TAIL_IDLE_RIGHT;
					else ani = MARIO_ANI_TAIL_IDLE_LEFT;
				}
			}
			else if (state == MARIO_STATE_SIT)
			{
				if (nx > 0)
					ani = MARIO_ANI_TAIL_SIT_RIGHT;
				else /*if(nx<0)*/
					ani = MARIO_ANI_TAIL_SIT_LEFT;
			}
			else
			{
				if (ny > 0 && nx > 0)
				{
					if (GetState() == MARIO_STATE_FLY)
						ani = MARIO_ANI_TAIL_FLY_RIGHT;
					else
					ani = MARIO_ANI_TAIL_JUMP_RIGHT;
					
				}
				else if (AniHold == 1 && nx > 0)
				{
					ani = MARIO_ANI_TAIL_HOLD_RIGHT;
				}
				else if (AniHold == 1 && nx < 0)
				{
					ani = MARIO_ANI_TAIL_HOLD_LEFT;
				}

				else if (Jump == 1 && nx > 0)
				{
					ani = MARIO_ANI_TAIL_JUMP_RIGHT;
				}
				else if (Jump == 1 && nx < 0)
				{
					ani = MARIO_ANI_TAIL_JUMP_LEFT;
				}
				else if (ny > 0 && nx < 0)
				{
					if (GetState() == MARIO_STATE_FLY)
						ani = MARIO_ANI_TAIL_FLY_LEFT;
					else
					ani = MARIO_ANI_TAIL_JUMP_LEFT;
				}
				else if (nx > 0)
					ani = MARIO_ANI_TAIL_WALKING_RIGHT;
				else
					ani = MARIO_ANI_TAIL_WALKING_LEFT;
			}
		}

		if (level == MARIO_LEVEL_FIRE)
		{
			if (state == MARIO_STATE_IDLE)
			{
				if (vx == 0)
				{
					if (nx > 0) ani = MARIO_ANI_FIRE_IDLE_RIGHT;
					else ani = MARIO_ANI_FIRE_IDLE_LEFT;
				}
			}

			//else if (state == MARIO_STATE_SIT)
			//{
			//	if (nx > 0)
			//		ani = MARIO_ANI_FIRE_SIT_RIGHT;
			//	else /*if(nx<0)*/
			//		ani = MARIO_ANI_FIRE_SIT_LEFT;
			//}
			else
			{
				if (ny > 0 && nx > 0)
					ani = MARIO_ANI_FIRE_JUMP_RIGHT;
				else if (ny > 0 && nx < 0)
					ani = MARIO_ANI_FIRE_JUMP_LEFT;
				else if (AniHold == 1 && nx > 0)
				{
					ani = MARIO_ANI_FIRE_HOLD_RIGHT;
				}
				else if (AniHold == 1 && nx < 0)
				{
					ani = MARIO_ANI_FIRE_HOLD_LEFT;
				}
				else if (Jump == 1 && nx > 0)
				{
					ani = MARIO_ANI_FIRE_JUMP_RIGHT;
				}
				else if (Jump == 1 && nx < 0)
				{
					ani = MARIO_ANI_FIRE_JUMP_LEFT;
				}
				else if (nx > 0)
					ani = MARIO_ANI_FIRE_WALKING_RIGHT;
				else
					ani = MARIO_ANI_FIRE_WALKING_LEFT;
			}
		}
	}

	int alpha = 255;
	if (untouchable) alpha = 128;

	animation_set->at(ani)->Render(x, y, alpha);

	RenderBoundingBox();
}

	void CMario::SetState(int state)
	{
		CGameObject::SetState(state);

		switch (state)
		{
		case MARIO_STATE_WALKING_RIGHT:
			vx = MARIO_WALKING_SPEED;
			nx = 1;
			ny = 0;
			break;
		case MARIO_STATE_WALKING_LEFT:
			vx = -MARIO_WALKING_SPEED;
			nx = -1;
			ny = 0;
			break;
		case MARIO_STATE_JUMP:
			// TODO: need to check if Mario is *current* on a platform before allowing to jump again
			vy = -MARIO_JUMP_SPEED_Y;
			ny = 1;
			break;
			
		case MARIO_STATE_IDLE:
			vx = 0;
			ny = 0;
			break;
		case MARIO_STATE_DIE:
			vy = -MARIO_DIE_DEFLECT_SPEED;
			break;
		case MARIO_STATE_SIT:
				vx = 0;
				ny = 0;
			break;
		case MARIO_STATE_FLY:
			vy = -MARIO_FLY_SPEED_Y;
			ny = 1;
			vx = 0;
		case MARIO_STATE_FAST_WALKING:
				if(nx>0)
				vx = MARIO_WALKING_FAST_SPEED;
				else
				vx = -MARIO_WALKING_FAST_SPEED;
			break;
		case MARIO_STATE_HOLDKOOPAS:
			SetHolding(1);
			break;
		 case MARIO_STATE_HIGHT_JUMP:
			vy = -MARIO_JUMP_HIGHT_SPEED_Y;
			ny = 1;

		}
	}

void CMario::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	
	left = x;
	top = y;
	
	 if (level != MARIO_LEVEL_SMALL /*&& state != MARIO_STATE_SIT*/)
	{
		right = x + MARIO_BIG_BBOX_WIDTH;
		bottom = y + MARIO_BIG_BBOX_HEIGHT;
		
	}
	
	else
	{
		right = x + MARIO_SMALL_BBOX_WIDTH;
		bottom = y + MARIO_SMALL_BBOX_HEIGHT;
	}

}

/*
	Reset Mario status to the beginning state of a scene
*/
void CMario::Reset()
{
	SetState(MARIO_STATE_IDLE);
	SetLevel(MARIO_LEVEL_BIG);
	SetPosition(start_x, start_y);
	SetSpeed(0, 0);
}

