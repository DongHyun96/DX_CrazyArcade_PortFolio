#include "Framework.h"
#include "CharacterAnim.h"


CharacterAnim::CharacterAnim(ColliderRect* parentBody)
	:parentBody(parentBody)
{
	vertexShader = new VertexShader(L"VertexTexture");
	pixelShader = new PixelShader(L"PixelTexture");

	worldBuffer = new MatrixBuffer();

	this->SetParent(parentBody);

	curFaceDir = DIR_DOWN;

}

CharacterAnim::~CharacterAnim()
{
	if (winAction)
		delete winAction;

	for (auto& pair : idleActions)
		delete pair.second;

	for (auto& pair : spaceActions)
		delete pair.second;

	for (auto& pair : owlActions)
		delete pair.second;

	for (auto& pair : turtleActions)
		delete pair.second;

	for (auto& pair : bubbleActions)
		delete pair.second;

	idleActions.clear();
	spaceActions.clear();
	owlActions.clear();
	turtleActions.clear();
	bubbleActions.clear();

	delete vertexShader;
	delete pixelShader;
	delete worldBuffer;
}

void CharacterAnim::Init()
{
	curFaceDir = DIR_DOWN;

	ownerPrevState = C_SPAWN;
	ownerPrevVelocity *= 0.f;

	captured_yUpdateTime = 0.f;
	captured_ySpeed = 10.f;

	isRidableReturningToIdle = false;

	jump_UpdateTime = 0.f;
	jump_ySpeed = 150.f;
}

void CharacterAnim::Update()
{
	if (!curAction)
		return;

	Transform::Update();
	curAction->Update();

	// 직접적인 y 좌표 handling을 여기서 함

	if (curAction == bubbleActions[A_BUBBLE_CAPTURED])
	{
		Util::PlayFloatingEffect(translation.y, captured_yUpdateTime, captured_ySpeed, CAPTURED_Y_UPDATE_TICK);
		return;
	}
	else
	{
		captured_yUpdateTime = 0.f;
		captured_ySpeed = 10.f;
	}

	if (isRidableReturningToIdle)
	{
		// 처음에는 점프했다가 도로 제자리로 와야 함
		jump_UpdateTime += Time::Delta();
		
		if (jump_UpdateTime >= JUMP_TICK)
		{
			jump_ySpeed = -jump_ySpeed - 10.f;
			jump_UpdateTime = -100.f;
			return;
		}

		translation.y += jump_ySpeed * Time::Delta();

		if (translation.y < (curAction->Size().y - parentBody->LocalSize().y) / 2) // 점프 동작 끝 (착지함)
		{
			jump_UpdateTime = 0.f;
			jump_ySpeed = 150.f;

			isRidableReturningToIdle = false;

			ReturnIdleEndEvent();
		}

		return;
	}
	

	// floor을 parent floor에 맞추는 작업
	translation.y = (curAction->Size().y - parentBody->LocalSize().y) / 2;
}

void CharacterAnim::Render()
{
	if (!curAction)
		return;

	worldBuffer->SetData(world);
	worldBuffer->VSSetBuffer(0);

	vertexShader->SetShader();
	pixelShader->SetShader();

	curAction->Render();
}

void CharacterAnim::UpdateAction(const CharacterState& cState, const Vector2& velocity)
{
	if (cState == C_SPAWN)
	{
		curAction = idleActions[A_DOWN];
		curAction->Stop(0);
		return;
	}

	if (ownerPrevState == cState && ownerPrevVelocity == velocity) return;

	switch (cState)
	{
	case C_IDLE:		UpdateDirectionActions(cState, velocity, idleActions);
		break;
	case C_SPACECRAFT:	UpdateDirectionActions(cState, velocity, spaceActions);
		break;
	case C_OWL:			UpdateDirectionActions(cState, velocity, owlActions);
		break;
	case C_TURTLE:		UpdateDirectionActions(cState, velocity, turtleActions);
		break;
	case C_CAPTURED:

		if (ownerPrevState == C_CAPTURED) return;

		curAction = bubbleActions[A_BUBBLE_CAPTURED];
		curAction->Play(false);

		break;
	case C_RETURN_IDLE: // TODO -> EndEvent로 owner의 상태를 변화시켜야 함

		if (ownerPrevState == C_CAPTURED)
		{
			curAction->Stop(0); // Stopping Captured anim here once

			curAction = bubbleActions[A_BUBBLE_SAVED];
			curAction->Play();

		}
		else //ownerPrevState was C_RIDABLE_S
		{
			isRidableReturningToIdle = true;
			curAction = idleActions[A_DOWN];
			curAction->Stop(0);
			return;
		}

		break;
	case C_DEAD: case C_WIN:
		curAction = (cState == C_DEAD) ? bubbleActions[A_BUBBLE_DEAD] : winAction;
		curAction->Play();
	default:
		break;
	}

	ownerPrevState = cState;
	ownerPrevVelocity = velocity;
}

void CharacterAnim::UpdateDirectionActions(const CharacterState& cState, const Vector2& velocity, map<CharacterAnimDir, Animation*>& dirActions)
{
	switch (cState)
	{
	case C_SPAWN: case C_CAPTURED: case C_RETURN_IDLE: case C_DEAD: case C_WIN: return;
	}

	int animDirection = GetCurFaceDirByVelocity(velocity);
	
	SetCurFaceDir(velocity);

	if (animDirection == -1)
	{
		if (ownerPrevState != cState) curAction = dirActions[A_DOWN];
		curAction->Stop(0);
	}
	else
	{
		curAction = dirActions[(CharacterAnimDir)animDirection];
		curAction->Play();
	}
}

void CharacterAnim::Debug(const string& label)
{
	Transform::Debug(label);
}

void CharacterAnim::SetReturnIdleEndEvent(function<void()> E)
{
	this->ReturnIdleEndEvent = E;
	
	bubbleActions[A_BUBBLE_SAVED]->SetEndEvent(E);
}


/// <returns> 속도가 0이면 -1 return </returns>
int CharacterAnim::GetCurFaceDirByVelocity(const Vector2& velocity)
{
	if (velocity.Length() == 0.f)	return -1;
	else if (velocity.x < 0.f)		return 0; // LEFT
	else if (velocity.x > 0.f)		return 1; // RIGHT
	else if (velocity.y > 0.f)		return 2; // UP
	else                            return 3; // DOWN
}



void CharacterAnim::SetCurFaceDir(const Vector2& velocity)
{
	curFaceDir = (velocity.Length() == 0.f)	? curFaceDir	:
				 (velocity.x < 0.f)			? DIR_LEFT		:
				 (velocity.x > 0.f)			? DIR_RIGHT		:
				 (velocity.y > 0.f)			? DIR_UP		: DIR_DOWN;
}

