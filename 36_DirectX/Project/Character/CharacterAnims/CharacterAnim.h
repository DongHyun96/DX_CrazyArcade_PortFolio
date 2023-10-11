#pragma once

// TODO - 각자 SpawnAction 스프라이트를 만들어줘야 함

class CharacterAnim : public Transform
{
protected:
	CharacterAnim(ColliderRect* parent);

public:
	virtual ~CharacterAnim();

	void Update();
	void Render();
	
	void UpdateAction(const CharacterState& cState, const Vector2& velocity);

	void Debug(const string& label);

protected:

	int GetDirRelativeFrameIdx(const Vector2& velocity);

protected:

	bool isTransYSetToBodyFeet{ true };

protected:

	Animation*							spawnAction{};
	Animation*							winAction{};
	map<IdleAnimState, Animation*>		idleActions{};
	map<SpaceAnimState, Animation*>		spaceActions{};
	map<OwlAnimState, Animation*>		owlActions{};
	map<TurtleAnimState, Animation*>	turtleActions{};
	map<BubbleAnimState, Animation*>	bubbleActions{};

	Animation*							curAction{};

	CharacterState						ownerPrevState{};
	Vector2								ownerPrevVelocity{};

	ColliderRect*						parent{};

	VertexShader*						vertexShader{};
	PixelShader*						pixelShader{};

	MatrixBuffer*						worldBuffer{};

};
