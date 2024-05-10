#pragma once

/*
CONCRETE CLASS
Owned by Character class
Character�� �������� Animation ��¹� ���
*/
class CharacterAnim : public Transform
{
protected:
	/// <param name="parentBody"> <para> : Transform�� parent�� ���Ͽ� �θ��� ��ġ�� ���� ���� </para>
	///                           <para> ColliderRect��(Transform�� �ڽ� Ŭ����)���� ���� ���� - ���� Parent body�� LocalSize �ʿ� </para>
	/// </param>
	CharacterAnim(ColliderRect* parentBody);

public:

	virtual ~CharacterAnim();

	void Init();

	void Update();
	void Render();

public:
	
	/// <summary>
	/// ���� ĳ������ mainState�� velocity�� �޾�, �������� FSM transition ����
	/// </summary>
	/// <param name="cState">   : OwnerCharacter current mainState </param>
	/// <param name="velocity"> : OwnerCharacter current velocity </param>
	void UpdateAction(const CharacterState& cState, const Vector2& velocity);

private:

	/// <summary>
	/// UpdateAction ������ ���� Direction�� Ű�� ������ animation update ó���� ���� boiler plate code ����
	/// </summary>
	/// <param name="cState"> : OwnerCharacter current mainState </param>
	/// <param name="velocity"> : OwnerCharacter current velocity</param>
	/// <param name="dirActions"> : direction�� �����ϰ� cState�� �ش��ϴ� animation map </param>
	void UpdateDirectionActions(const CharacterState& cState, const Vector2& velocity, map<CharacterAnimDir, Animation*>& dirActions);
	
public: /* Anim Notify setters */

	void SetReturnIdleEndEvent(function<void()> E);															// Set Return-idle end event function pointer
	void SetCapturedEndEvent(function<void()> E)	{ bubbleActions[A_BUBBLE_CAPTURED]->SetEndEvent(E); }	// Set Captured animation end event function pointer
	void SetDeadEndEvent(function<void()> E)		{ bubbleActions[A_BUBBLE_DEAD]->SetEndEvent(E); }		// Set Bubble dead animation end event function pointer


public:

	Direction GetCurFaceDir() const { return curFaceDir; }			// Get Current facing direction

	Vector2 GetCurActionSize() const { return curAction->Size(); }	// ���� ������� Animation rect�� ũ��

public:

	void Debug(const string& label);

private:

	/// <summary>
	/// OwnerCharacter�� velocioty�� ���� ���� getter
	/// </summary>
	/// <param name="velocity"> : OwnerCharacter velocity</param>
	/// <returns> -1: ���ϰ� �ִ� ������ ���� ��(�ӵ�ũ�Ⱑ 0�� ��) | 0~3 : CharacterAnimDir enum integer�� </returns>
	int GetCurFaceDirByVelocity(const Vector2& velocity);

	/* Owner Character�� velocity�� ���� curFaceDir set */
	void SetCurFaceDir(const Vector2& velocity);

/***************************************************************************************************
*                                          Member variables                                        *
****************************************************************************************************/

private:
	/* ���� ���� �θ��� ��ü */
	ColliderRect* parentBody{};

private:
	/* �θ��� 4 way movement velocity�� ���� ���� �ٶ󺸰� �ִ� ��� */
	Direction curFaceDir{};

protected: /* State�� ���� Animation maps */

	Animation*							winAction{};		// �¸� Animation

	map<CharacterAnimDir, Animation*>	idleActions{};		// ���⿡ ���� �⺻ �̵��� Animations map
	map<CharacterAnimDir, Animation*>	spaceActions{};		// ���⿡ ���� ���ּ� �̵��� Animations map
	map<CharacterAnimDir, Animation*>	owlActions{};		// ���⿡ ���� �ξ��� �̵��� Animations map
	map<CharacterAnimDir, Animation*>	turtleActions{};	// ���⿡ ���� �ź��� �̵��� Animations map
	map<BubbleAnimState, Animation*>	bubbleActions{};	// Bubble�� ���� ���¿���, BubbleAnimState�� ���� Animations map 
	
		
	Animation*							curAction{};		// ���� ����ϰ� �ִ� animation
	
private: /* Animation FSM����(UpdateAction) transition ���ǿ� �ʿ��� ������ */
	
	CharacterState	ownerPrevState{};		// ���� ĳ������ ���� Update tick�� mainState
	Vector2			ownerPrevVelocity{};	// ���� ĳ������ ���� Update tick�� velocity

private:

	VertexShader*	vertexShader{};
	PixelShader*	pixelShader{};
	MatrixBuffer*	worldBuffer{};

private:
	/* Ż �Ϳ��� ������ ���� ��, �� ���ȴٸ� ȣ���ų �Լ� ������ (�θ��� mainState�� C_IDLE�� �ٲ� ����) */
	function<void()> ReturnIdleEndEvent{};

private: /* Captured������ translation y Update ���� */

	float		captured_yUpdateTime{};
	float		captured_ySpeed			= 10.f;

	const float CAPTURED_Y_UPDATE_TICK	= 1.f;

private: /* ReturnToIdle ���¿��� Ridable ���� */

	bool		isRidableReturningToIdle{};
	
	float		jump_UpdateTime{};
	float		jump_ySpeed = 150.f;
	
	const float JUMP_TICK = 0.5f;

};
