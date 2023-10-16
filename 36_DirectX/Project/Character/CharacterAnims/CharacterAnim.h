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

	void SetReturnIdleEndEvent(function<void()> E);
	void SetCapturedEndEvent(function<void()> E) { bubbleActions[A_BUBBLE_CAPTURED]->SetEndEvent(E); }
	void SetDeadEndEvent(function<void()> E) { bubbleActions[A_BUBBLE_DEAD]->SetEndEvent(E); }


	Direction GetCurFaceDir() const { return curFaceDir; }

	Vector2 GetCurActionSize() const { return curAction->Size(); }

protected:

	int GetDirRelativeFrameIdx(const Vector2& velocity);
	//int GetDirRelativeFrameIdx(const Direction& direction);
	void SetCurFaceDir(const Vector2& velocity);

protected:

	Direction curFaceDir{};

protected:

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

protected:

	// 부모의 상태를 RETURN_IDLE에서 Idle로 돌아가려면 이것을 사용
	function<void()> ReturnIdleEndEvent{};


protected: // Captured상태의 translation y Update 관련 field

	float		captured_yUpdateTime = 0.f;
	float		captured_ySpeed = 10.f;

	const float CAPTURED_Y_UPDATE_TICK = 1.f;

protected: // ReturnToIdle 상태에서 Ridable 관련 field

	bool ridableReturningToIdle{};
	
	float jump_UpdateTime = 0.f;
	float jump_ySpeed = 150.f;
	
	const float JUMP_TICK = 0.5f;

};
