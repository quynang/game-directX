#include <algorithm>
#include <assert.h>
#include "Utils.h"
#include <iostream>
#include <fstream>
#include "Simon.h"
#include "Game.h"
#include "Textures.h"
#include "Sprites.h"
#include "ResourceManager.h"
#include "Portal.h"
#include "Item.h"
#include "TourchFlame.h"
#include "PlayScence.h"
#include"Brick.h"
#include "StairBottom.h"
#include "StairTop.h"

CSimon::CSimon(float x, float y) : CGameObject()
{
	untouchable = 0;
	SetState(SIMON_STATE_IDLE);

	start_x = x;
	start_y = y;
	this->x = x;
	this->y = y;
}

#define PLAYER_SECTION_UNKNOWN -1
#define PLAYER_SECTION_TEXTURES 2
#define PLAYER_SECTION_SPRITES 3
#define PLAYER_SECTION_ANIMATIONS 4
#define PLAYER_SECTION_ANIMATION_SETS	5
#define MAX_PLAYER_LINE 1024

void CSimon::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	whip->Update(dt, coObjects);
	CGameObject::Update(dt);
	if(!isClimbing)
		vy += SIMON_GRAVITY*dt;

	if ( GetTickCount() - start_jump > SIMON_JUMPING_TIME) 
	{
		start_jump = 0;
		canJump = true;
	}

	if (isFreeze && (GetTickCount() - freezeTimer > SIMON_FREEZE_TIME)) 
	{
		freezeTimer = 0;
		isFreeze = false;
		//SetState(SIMON_STATE_IDLE);
	}

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	vector<LPGAMEOBJECT> objectsColliding;
	this->CheckColliding(coObjects, objectsColliding);
	if (objectsColliding.size() == 0 && !isClimbing) {
		canClimbDown = false;
		canClimbUp = false;
	}	else {
		for (UINT i = 0; i < objectsColliding.size(); i++) {
			if (dynamic_cast<CStairBottom*>(objectsColliding.at(i))) {

				CStairBottom* stairBottom = dynamic_cast<CStairBottom*>(objectsColliding.at(i));
				canClimbUp = true;

				if (isClimbing && canClimbUp && !canClimbDown) { 
					x = stairBottom->getPosition().x + 4;
					canClimbDown = true;
					y -= 4;
				}

				nx_stair = stairBottom->GetDirection();

				bool isReachedBottomOfStair = stairBottom->getPosition().y - this->y < 28;
				if (isClimbing && isReachedBottomOfStair && canClimbUp && canClimbDown) { 
					y = stairBottom->getPosition().y - SIMON_BOX_HEIGHT;
					x = stairBottom->getPosition().x - 1;
					canClimbUp = false;
					canClimbDown = false;
					isClimbing = false;
				}
			}

			if (dynamic_cast<CStairTop*>(objectsColliding.at(i))) {

				CStairTop* stairTop = dynamic_cast<CStairTop*>(objectsColliding.at(i));
				bool isReachedTopOfStair = stairTop->getPosition().y - this->y > 20;

				if (isClimbing && isReachedTopOfStair) { 
					y = stairTop->getPosition().y - SIMON_BOX_HEIGHT + 10;
					x = stairTop->getPosition().x + 1;
					canClimbUp = false;
					isClimbing = false;
				}

				canClimbDown = true;

				if (isClimbing && canClimbDown && !canClimbUp) {
					x = stairTop->getPosition().x + 1;
					canClimbUp = true;
					y = stairTop->getPosition().y + STAIR_TOP_BOX_HEIGHT - SIMON_BOX_HEIGHT + 1.4f;
				}
			}
		}
	}

	//DebugOut(L"[INFO] Simon can climb down  : %d \n", canClimbDown);
	//DebugOut(L"[INFO] Simon can climb up  : %d \n", canClimbUp);
	
	coEvents.clear();

	CalcPotentialCollisions(coObjects, coEvents);

	if (coEvents.size()==0)
	{
		x += dx; 
		y += dy;

	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		float rdx = 0; 
		float rdy = 0;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		x += min_tx*dx + nx*0.4f;
		y += min_ty*dy + ny*0.4f;

		if (nx!=0) vx = 0;
		if (ny!=0) vy = 0;


		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			if (dynamic_cast<CWheapon*>(e->obj))
			{
				CWheapon* wheapon = dynamic_cast<CWheapon*>(e->obj);
				wheapon->SetVisible(false);
				whip->UpgradeLevel();
				SetState(SIMON_STATE_FREEZE);
				StartFreezeState();
			}

			if (dynamic_cast<CTourchFlame*>(e->obj)) {
				x += dx;
				if (e->ny < 0) {
					y += dy;
				}
			}

			if (dynamic_cast<CStairBottom*>(e->obj)) {
				CStairBottom* stairBottom = dynamic_cast<CStairBottom*>(e->obj);
				x += dx;
				if (e->ny < 0) {
					y += STAIR_BOTTOM_BOX_HEIGHT;
	
				}
			}

			if (dynamic_cast<CStairTop*>(e->obj)) {
				x += dx;
				if (e->ny < 0) {
					y += STAIR_TOP_BOX_HEIGHT;
				}
			}
	
			if (dynamic_cast<CHeart*>(e->obj)) {
				CHeart* heart = dynamic_cast<CHeart*>(e->obj);
				heart->SetVisible(false);
				//((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->TurnOffGameUpdationByTimer(3000);
			}

			if (dynamic_cast<CBrick*>(e->obj)) {
				CBrick* brick = dynamic_cast<CBrick*>(e->obj);
				if (e->ny > 0 || isClimbing) {
					y += dy;
					x += dx;
				}
				//((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->TurnOffGameUpdationByTimer(3000);
			}

			 if (dynamic_cast<CPortal *>(e->obj)) {
		
				CPortal *p = dynamic_cast<CPortal *>(e->obj);
				CGame::GetInstance()->SwitchScene(p->GetSceneId());
			}
		}
	}
	
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void CSimon::Render()
{
	int ani = -1;
	int alpha = 255;

	switch (state) {
		case SIMON_STATE_JUMP:
			if (nx > 0) ani = SIMON_ANI_JUMP_RIGHT;
			else ani = SIMON_ANI_JUMP_LEFT;
			isJumping = true;
			break;
		case SIMON_STATE_WALKING_RIGHT:
			if(isJumping) ani = SIMON_ANI_JUMP_RIGHT;
			else ani = SIMON_ANI_WALK_RIGHT;
			break;
		case SIMON_STATE_WALKING_LEFT:
			if(isJumping) ani = SIMON_ANI_JUMP_LEFT;
			else ani = SIMON_ANI_WALK_LEFT;
			break;
		case SIMON_STATE_STANDING_HITTING:
			if (nx > 0) ani = SIMON_ANI_STANDING_HITTING_RIGHT;
			else ani = SIMON_ANI_STANDING_HITTING_LEFT;
			isHitting = true;
			break;
		case SIMON_STATE_FREEZE:
			if (nx > 0) ani = SIMON_ANI_COLOR_RIGHT;
			else ani = SIMON_ANI_COLOR_LEFT;
			break;
		case SIMON_STATE_CLIMBING_UP:
			if (nx_stair > 0) ani = SIMON_ANI_CLIMBING_UP_RIGHT;
			else ani = SIMON_ANI_CLIMBING_UP_LEFT;
			break;
		case SIMON_STATE_CLIMBING_DOWN:
			if (nx_stair > 0) ani = SIMON_ANI_CLIMBING_DOWN_LEFT;
			else ani = SIMON_ANI_CLIMBING_DOWN_RIGHT;
		 	break;
		case SIMON_STATE_IDLE_ON_STAIR:
		 	if (nx_stair > 0 && nx > 0) ani = SIMON_ANI_IDLE_ON_STAIR_UP_RIGHT;
		 	else if(nx_stair > 0 && nx < 0) ani = SIMON_ANI_IDLE_ON_STAIR_DOWN_LEFT;
			else if(nx_stair < 0 && nx < 0)	ani = SIMON_ANI_IDLE_ON_STAIR_UP_LEFT;
			else if(nx_stair < 0 && nx > 0)	ani = SIMON_ANI_IDLE_ON_STAIR_DOWN_RIGHT;
		 	break;
		case SIMON_STATE_DUCKING:
			if (nx > 0) ani = SIMON_ANI_DUCKING_RIGHT;
			else ani = SIMON_ANI_DUCKING_LEFT;
			break;
		case SIMON_STATE_SITTING_AND_HITTING:
			if (nx > 0) ani = SIMON_ANI_SITTING_AND_HITTING_RIGHT;
			else ani = SIMON_ANI_SITTING_AND_HITTING_LEFT;
			isHitting = true;
			isDucking = false;
			break;
		case SIMON_STATE_HITTING_ON_STAIR:
			if (nx_stair > 0 && nx > 0)
				ani = SIMON_ANI_ASCENDING_STAIR_RIGHT_AND_HITTING;
			else if (nx_stair > 0 && nx < 0)
				ani = SIMON_ANI_DESCENDING_STAIR_LEFT_AND_HITTING;
			else if (nx_stair < 0 && nx > 0)
				ani = SIMON_ANI_DESCENDING_STAIR_RIGHT_AND_HITTING;
			else if (nx_stair > 0 && nx < 0)
				ani = SIMON_ANI_ASCENDING_STAIR_LEFT_AND_HITTING;
			isHitting = true;
			break;
		default:
			if (nx > 0) ani = SIMON_ANI_IDLE_RIGHT;
			else ani = SIMON_ANI_IDLE_LEFT;
	};

	animation_set->at(ani)->Render(x, y, alpha);
	if(isHitting) UseWhip(animation_set->at(ani)->GetCurrentFrame());

	if (isHitting == true && animation_set->at(ani)->isLastFrame()) isHitting = false; 
	
	
	if (vy > 0) isJumping = false;
	
	if (isHitting == false || isJumping == false) {
		if (isClimbing) SetState(SIMON_STATE_IDLE_ON_STAIR);
		else  SetState(SIMON_STATE_IDLE);
	}

	RenderBoundingBox();
}

void CSimon::StartFreezeState() {
	isFreeze = true;
	freezeTimer = GetTickCount();
}

void CSimon::UseWhip(int currentFrame) {
	whip->SetDirection(nx);
	/*	Xét trạng thái của cây roi
		Với trạng thái setup1 và setup2. Roi sẽ sau con Simon.
		Với trạng thái crack . Roi sẽ ở trước Simon.
		==> Do đó ta cần setPosition cho cây roi dựa vào 4 yếu tố. Box width của Simon, Box width của cây roi, trạng thái của cây roi, 
			phương hiện tại Simon.
		**Nhìn vào textures của Simon để thấy rõ hơn.
	*/

	int hand_offset_y = SIMON_HAND_OFFSET_Y;
	int hand_offset_x = SIMON_HAND_OFFSET_X;
	if (state == SIMON_STATE_SITTING_AND_HITTING) {
		hand_offset_y += 8;
	}

	//Điểu chỉnh sai lệch của cây roi khi simon đang leo lên cầu thang. Đây là trường hợp đặc biệt. 
	//Nếu chú ý thì sprite leo lên cầu thang sẽ có cái tay dài hơn và thấp hơn.
	if (state == SIMON_STATE_HITTING_ON_STAIR && nx_stair > 0 && nx > 0) {
		hand_offset_y += 2;
	}

	if (state == SIMON_STATE_HITTING_ON_STAIR && nx_stair < 0 && nx < 0) {
		hand_offset_y += 2;
	}
	switch(currentFrame) {
		case 0:
			if(nx > 0) whip->SetPosition(this->x - whip->GetBoxWidthSetup1ByCurrentLevel(), this->y + hand_offset_y);
			else whip->SetPosition(this->x + SIMON_BOX_WIDTH, this->y + hand_offset_y);
			whip->SetState(WHIP_STATE_SETUP_1);
			break;
		case 1:
			if (nx > 0) whip->SetPosition(this->x - whip->GetBoxWidthSetup2ByCurrentLevel(), this->y + hand_offset_y);
			else whip->SetPosition(this->x + SIMON_BOX_WIDTH, this->y + hand_offset_y);
			whip->SetState(WHIP_STATE_SETUP_2);
			break;
		case 2:
			if (nx > 0) whip->SetPosition(this->x + SIMON_BOX_WIDTH + hand_offset_x, this->y + hand_offset_y);
			else whip->SetPosition(this->x - whip->GetBoxWidthCrackByCurrentLevel() - hand_offset_x, this->y + hand_offset_y);
			whip->SetState(WHIP_STATE_CRACK);
			//whip->RenderBoundingBox();
			break;
	};

	whip->Render();
}


void CSimon::SetState(int state)
{
	//Vì trong trạng thái Ducking, ta chỉ có thể SetSate ngồi và đánh.
	if (isDucking) {
		if (state == SIMON_STATE_SITTING_AND_HITTING) {
			CGameObject::SetState(state);
			return;
		}
	}
	
	//Nếu simon trong thái hitting, ducking, jumping thì không thực hiện đổi state được. Vì nó cần thời gian để kết thúc trạng thái hiện tại.
	//Ví dụ: simon đang đánh thì phải đợi nó đánh hết 1 vòng (nghĩa là đợi nó render hết 1 vòng animations của hitting) rồi ta mới được SetState khác.
	if (!isHitting && !isJumping && !isFreeze && !isDucking) {
		

		switch (state)
		{
		case SIMON_STATE_WALKING_RIGHT:
			vx = SIMON_WALKING_SPEED;
			nx = 1;
			break;
		case SIMON_STATE_WALKING_LEFT:
			vx = -SIMON_WALKING_SPEED;
			nx = -1;
			break;
		case SIMON_STATE_IDLE:
			isDucking = false;
			vx = 0;
			break;
		case SIMON_STATE_JUMP:
			vy = -SIMON_JUMP_SPEED_Y;
			canJump = false;
			this->StartJump();
			break;
		case SIMON_STATE_STANDING_HITTING:
			vx = 0;
			break;
		case SIMON_STATE_CLIMBING_UP:
			vx = SIMON_WALKING_SPEED;
			vy = -0.07f;
			nx = nx_stair;
			break;
		case SIMON_STATE_CLIMBING_DOWN:
			vx = -SIMON_WALKING_SPEED;
			vy = 0.07f;
			nx = -nx_stair;
			break;
		case SIMON_STATE_IDLE_ON_STAIR:
			vx = 0;
			vy = 0;
			canClimbDown = true;
			canClimbUp = true;
			break;
		case SIMON_STATE_DUCKING:
			vx = 0;
			vy = 0;
			isDucking = true;
			break;
		case SIMON_STATE_HITTING_ON_STAIR:
			vx = 0;
			vy = 0;
			break;
		case SIMON_STATE_FREEZE:
			vx = 0;
			vy = 0;
			break;

		}

		CGameObject::SetState(state);
	}
}

void CSimon::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	
	top = y;
	left = x;
	int _width = SIMON_BOX_WIDTH;
	int _height = SIMON_BOX_HEIGHT;

	if (state == SIMON_STATE_SITTING_AND_HITTING) {
		top = y + 8;
		_height -= 8;
	}

	else if (isDucking) {
		top = y + 8;
		_height -= 8;
	}

	else if (isJumping) {
		_height -= 8;
	}


	right = left + _width;
	bottom = top + _height;
	
}


/*
	Reset Mario status to the beginning state of a scene
*/
void CSimon::Reset()
{
	SetState(SIMON_STATE_IDLE);
	SetPosition(start_x, start_y);
	SetSpeed(0, 0);
}


void CSimon::Load(LPCWSTR filePath) {
	DebugOut(L"[INFO] Start loading scene resources from : %s \n", filePath);

	ifstream f;
	f.open(filePath);

	// current resource section flag
	int section = PLAYER_SECTION_UNKNOWN;

	char str[MAX_PLAYER_LINE];
	while (f.getline(str, MAX_PLAYER_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	

		if (line == "[TEXTURES]") { section = PLAYER_SECTION_TEXTURES; continue; }
		if (line == "[SPRITES]") {
			section = PLAYER_SECTION_SPRITES; continue;
		}
		if (line == "[ANIMATIONS]") {
			section = PLAYER_SECTION_ANIMATIONS; continue;
		}
		if (line == "[ANIMATION_SETS]") {
			section = PLAYER_SECTION_ANIMATION_SETS; continue;
		}

		if (line[0] == '[') { section = PLAYER_SECTION_UNKNOWN; continue; }

		switch (section)
		{
			case PLAYER_SECTION_TEXTURES: CResourceManager::GetInstance()->_ParseSection_TEXTURES(line); break;
			case PLAYER_SECTION_SPRITES: CResourceManager::GetInstance()->_ParseSection_SPRITES(line); break;
			case PLAYER_SECTION_ANIMATIONS: CResourceManager::GetInstance()->_ParseSection_ANIMATIONS(line); break;
			case PLAYER_SECTION_ANIMATION_SETS: CResourceManager::GetInstance()->_ParseSection_ANIMATION_SETS(line); break;
		}
	}

	f.close();

	CAnimationSets * animation_sets = CAnimationSets::GetInstance();
	LPANIMATION_SET ani_set = animation_sets->Get(1);
	LPANIMATION_SET whip_ani_set = animation_sets->Get(21);
	this->SetAnimationSet(ani_set);
	whip = new CWhip(0, 0);
	whip->SetAnimationSet(whip_ani_set);
	//DebugOut(L"[INFO] whip animation sets %d\n", whip_ani_set->size());

	DebugOut(L"[INFO] Done loading scene resources %s\n", filePath);
}

void CSimon::useSimonBackupWithInfoNeeded(
	int whipLevel,
	bool isClimbing,
	bool canClimbUp,
	bool canClimbDown,
	int state
)
{
	this->whip->SetLevel(whipLevel);
	this->isClimbing = isClimbing;
	this->canClimbUp = canClimbUp;
	this->canClimbDown = canClimbDown;
	this->state = state;
}