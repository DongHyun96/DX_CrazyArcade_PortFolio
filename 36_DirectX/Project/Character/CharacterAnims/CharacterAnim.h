#pragma once

/*
CONCRETE CLASS
Owned by Character class
Character의 실질적인 Animation 출력물 담당
*/
class CharacterAnim : public Transform
{
protected:
	/// <param name="parentBody"> <para> : Transform의 parent로 취하여 부모의 위치를 따라갈 예정 </para>
	///                           <para> ColliderRect형(Transform의 자식 클래스)으로 받은 이유 - 추후 Parent body의 LocalSize 필요 </para>
	/// </param>
	CharacterAnim(ColliderRect* parentBody);

public:

	virtual ~CharacterAnim();

	void Init();

	void Update();
	void Render();

public:
	
	/// <summary>
	/// 주인 캐릭터의 mainState와 velocity를 받아, 실질적인 FSM transition 진행
	/// </summary>
	/// <param name="cState">   : OwnerCharacter current mainState </param>
	/// <param name="velocity"> : OwnerCharacter current velocity </param>
	void UpdateAction(const CharacterState& cState, const Vector2& velocity);

private:

	/// <summary>
	/// UpdateAction 구현부 내의 Direction을 키로 가지는 animation update 처리에 대한 boiler plate code 정리
	/// </summary>
	/// <param name="cState"> : OwnerCharacter current mainState </param>
	/// <param name="velocity"> : OwnerCharacter current velocity</param>
	/// <param name="dirActions"> : direction이 존재하고 cState에 해당하는 animation map </param>
	void UpdateDirectionActions(const CharacterState& cState, const Vector2& velocity, map<CharacterAnimDir, Animation*>& dirActions);
	
public: /* Anim Notify setters */

	void SetReturnIdleEndEvent(function<void()> E);															// Set Return-idle end event function pointer
	void SetCapturedEndEvent(function<void()> E)	{ bubbleActions[A_BUBBLE_CAPTURED]->SetEndEvent(E); }	// Set Captured animation end event function pointer
	void SetDeadEndEvent(function<void()> E)		{ bubbleActions[A_BUBBLE_DEAD]->SetEndEvent(E); }		// Set Bubble dead animation end event function pointer


public:

	Direction GetCurFaceDir() const { return curFaceDir; }			// Get Current facing direction

	Vector2 GetCurActionSize() const { return curAction->Size(); }	// 현재 재생중인 Animation rect의 크기

public:

	void Debug(const string& label);

private:

	/// <summary>
	/// OwnerCharacter의 velocioty에 따른 방향 getter
	/// </summary>
	/// <param name="velocity"> : OwnerCharacter velocity</param>
	/// <returns> -1: 향하고 있는 방향이 없을 때(속도크기가 0일 때) | 0~3 : CharacterAnimDir enum integer값 </returns>
	int GetCurFaceDirByVelocity(const Vector2& velocity);

	/* Owner Character의 velocity에 따라 curFaceDir set */
	void SetCurFaceDir(const Vector2& velocity);

/***************************************************************************************************
*                                          Member variables                                        *
****************************************************************************************************/

private:
	/* 직접 따라갈 부모의 몸체 */
	ColliderRect* parentBody{};

private:
	/* 부모의 4 way movement velocity에 따른 현재 바라보고 있는 방면 */
	Direction curFaceDir{};

protected: /* State에 따른 Animation maps */

	Animation*							winAction{};		// 승리 Animation

	map<CharacterAnimDir, Animation*>	idleActions{};		// 방향에 따른 기본 이동기 Animations map
	map<CharacterAnimDir, Animation*>	spaceActions{};		// 방향에 따른 우주선 이동기 Animations map
	map<CharacterAnimDir, Animation*>	owlActions{};		// 방향에 따른 부엉이 이동기 Animations map
	map<CharacterAnimDir, Animation*>	turtleActions{};	// 방향에 따른 거북이 이동기 Animations map
	map<BubbleAnimState, Animation*>	bubbleActions{};	// Bubble에 갇힌 상태에서, BubbleAnimState에 따른 Animations map 
	
		
	Animation*							curAction{};		// 현재 재생하고 있는 animation
	
private: /* Animation FSM에서(UpdateAction) transition 조건에 필요한 변수들 */
	
	CharacterState	ownerPrevState{};		// 주인 캐릭터의 이전 Update tick의 mainState
	Vector2			ownerPrevVelocity{};	// 주인 캐릭터의 이전 Update tick의 velocity

private:

	VertexShader*	vertexShader{};
	PixelShader*	pixelShader{};
	MatrixBuffer*	worldBuffer{};

private:
	/* 탈 것에서 내리고 있을 때, 다 내렸다면 호출시킬 함수 포인터 (부모의 mainState를 C_IDLE로 바꿀 예정) */
	function<void()> ReturnIdleEndEvent{};

private: /* Captured상태의 translation y Update 관련 */

	float		captured_yUpdateTime{};
	float		captured_ySpeed			= 10.f;

	const float CAPTURED_Y_UPDATE_TICK	= 1.f;

private: /* ReturnToIdle 상태에서 Ridable 관련 */

	bool		isRidableReturningToIdle{};
	
	float		jump_UpdateTime{};
	float		jump_ySpeed = 150.f;
	
	const float JUMP_TICK = 0.5f;

};
