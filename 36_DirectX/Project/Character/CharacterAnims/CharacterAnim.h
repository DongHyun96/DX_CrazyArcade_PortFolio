#pragma once

// TODO - ���� SpawnAction ��������Ʈ�� �������� ��

class CharacterAnim
{
protected:
	CharacterAnim();

public:
	virtual ~CharacterAnim();

	void Update();
	void Render();
	
	void UpdateAction(const CharacterState& cState, const Vector2& velocity);

protected:

	int GetDirRelativeFrameIdx(const Vector2& velocity);

protected:

	Animation*							spawnAction{};
	Animation*							winAction{};
	map<IdleAnimState, Animation*>		idleActions{};
	map<SpaceAnimState, Animation*>		spaceActions{};
	map<OwlAnimState, Animation*>		owlActions{};
	map<TurtleAnimState, Animation*>	turtleActions{};
	map<BubbleAnimState, Animation*>	bubbleActions{};

	Animation* curAction{};

	CharacterState						ownerPrevState{};
	Vector2								ownerPrevVelocity{};

};