#include "Framework.h"
#include "CharacterAnim.h"


CharacterAnim::CharacterAnim(ColliderRect* parent)
	:parent(parent)
{
	vertexShader = new VertexShader(L"VertexTexture");
	pixelShader = new PixelShader(L"PixelTexture");

	worldBuffer = new MatrixBuffer();

	this->SetParent(parent);

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

	delete worldBuffer;
	delete vertexShader;
	delete pixelShader;
}

void CharacterAnim::Init()
{
	curFaceDir = DIR_DOWN;

	ownerPrevState = C_SPAWN;
	ownerPrevVelocity *= 0.f;

	captured_yUpdateTime = 0.f;
	captured_ySpeed = 10.f;

	ridableReturningToIdle = false;

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

	if (ridableReturningToIdle)
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

		if (translation.y < (curAction->Size().y - parent->LocalSize().y) / 2) // 점프 동작 끝 (착지함)
		{
			jump_UpdateTime = 0.f;
			jump_ySpeed = 150.f;

			ridableReturningToIdle = false;

			ReturnIdleEndEvent();
		}

		return;
	}
	

	// floor을 parent floor에 맞추는 작업
	translation.y = (curAction->Size().y - parent->LocalSize().y) / 2;
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
		curAction = idleActions[A_IDLE_DOWN];
		curAction->Stop(0);
		return;
	}

	if (ownerPrevState == cState && ownerPrevVelocity == velocity) return;

	switch (cState)
	{
	case C_IDLE:
	{
		int frameIdx = GetDirRelativeFrameIdx(velocity);

		SetCurFaceDir(velocity);
		
		if (frameIdx == -1)
		{
			if (ownerPrevState != C_IDLE) curAction = idleActions[A_IDLE_DOWN];
			curAction->Stop(0);
		}
		else
		{
			curAction = idleActions[(IdleAnimState)frameIdx];
			curAction->Play();
		}
	}
		break;
	case C_SPACECRAFT:  
	{

		int frameIdx = GetDirRelativeFrameIdx(velocity);

		SetCurFaceDir(velocity);

		if (frameIdx == -1)
		{
			if (ownerPrevState != C_SPACECRAFT) curAction = spaceActions[(A_SPACE_DOWN)];
		}
		else
		{
			curAction = spaceActions[(SpaceAnimState)frameIdx];
			curAction->Play();
		}
	}
		break;
	case C_OWL:
	{
		int frameIdx = GetDirRelativeFrameIdx(velocity);

		SetCurFaceDir(velocity);

		if (frameIdx == -1)
		{
			if (ownerPrevState != C_OWL) curAction = owlActions[(A_OWL_DOWN)];
			curAction->Stop(0);
		}
		else
		{
			curAction = owlActions[(OwlAnimState)frameIdx];
			curAction->Play();
		}
	}
		break;
	case C_TURTLE:
	{

		int frameIdx = GetDirRelativeFrameIdx(velocity);

		SetCurFaceDir(velocity);

		if (frameIdx == -1)
		{
			if (ownerPrevState != C_TURTLE) curAction = turtleActions[(A_TURTLE_DOWN)];
			curAction->Stop(0);

		}
		else
		{
			curAction = turtleActions[(TurtleAnimState)frameIdx];
			curAction->Play();
		}
	}
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
			ridableReturningToIdle = true;
			curAction = idleActions[A_IDLE_DOWN];
			curAction->Stop(0);
			return;
		}

		break;
	case C_DEAD:

		curAction = bubbleActions[A_BUBBLE_DEAD];
		curAction->Play();

		break;
	case C_WIN:
		curAction = winAction;
		curAction->Play();
		break;
	default:
		break;
	}

	ownerPrevState = cState;
	ownerPrevVelocity = velocity;
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
int CharacterAnim::GetDirRelativeFrameIdx(const Vector2& velocity)
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

