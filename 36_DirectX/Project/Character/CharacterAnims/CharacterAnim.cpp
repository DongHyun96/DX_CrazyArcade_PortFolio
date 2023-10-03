#include "Framework.h"
#include "CharacterAnim.h"


CharacterAnim::CharacterAnim()
{
}

CharacterAnim::~CharacterAnim()
{
	if (spawnAction)
		delete spawnAction;
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
}

void CharacterAnim::Update()
{
	if (!curAction)
		return;

	curAction->Update();
}

void CharacterAnim::Render()
{
	if (!curAction)
		return;

	curAction->Render();
}

void CharacterAnim::UpdateAction(const CharacterState& cState, const Vector2& velocity)
{
	if (ownerPrevState == cState && ownerPrevVelocity == velocity) return;

	switch (cState)
	{
	case C_SPAWN: curAction = spawnAction;
		break;
	case C_IDLE:
	{
		int frameIdx = GetDirRelativeFrameIdx(velocity);
		
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

		if (frameIdx == -1)
		{
			if (ownerPrevState != C_OWL) curAction = owlActions[(A_OWL_DOWN)];
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

		if (frameIdx == -1)
		{
			if (ownerPrevState != C_TURTLE) curAction = turtleActions[(A_TURTLE_DOWN)];
		}
		else
		{
			curAction = turtleActions[(TurtleAnimState)frameIdx];
			curAction->Play();
		}
	}
		break;
	case C_CAPTURED: 
		curAction = bubbleActions[A_BUBBLE_CAPTURED];
		curAction->Play();
		break;
	case C_RETURN_IDLE: // TODO -> EndEvent로 owner의 상태를 변화시켜야 함
		if (ownerPrevState == C_CAPTURED)			curAction = bubbleActions[A_BUBBLE_SAVED];
		else if (ownerPrevState == C_SPACECRAFT)	curAction = spaceActions[A_SPACE_DESTROYED];
		else if (ownerPrevState == C_OWL)			curAction = owlActions[A_OWL_DESTROYED];
		else if (ownerPrevState == C_TURTLE)		curAction = turtleActions[A_TURTLE_DESTROYED];
		curAction->Play();

			
		break;
	case C_DEAD: curAction = bubbleActions[A_BUBBLE_DEAD];
		curAction->Play();

		break;
	default:
		break;
	}

	ownerPrevState = cState;
	ownerPrevVelocity = velocity;
}

int CharacterAnim::GetDirRelativeFrameIdx(const Vector2& velocity)
{
	if (velocity.Length() == 0.f)	return -1;
	else if (velocity.x < 0.f)		return 0;
	else if (velocity.x > 0.f)		return 1;
	else if (velocity.y > 0.f)		return 2;
	else                            return 3;
}

//void Character::SetAction(int state)
//{
//	if (this->state == state)
//		return;
//
//	this->state = state;
//
//	curAction = actions[state];
//	curAction->Play();
//}
