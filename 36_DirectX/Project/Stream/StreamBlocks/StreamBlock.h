#pragma once
/* 
CONCRETE CLASS 
게임 맵에 실질적으로 map cell 한 칸에 spawn되는 물줄기 block
*/
class StreamBlock
{
public:
	StreamBlock();
	virtual ~StreamBlock();

	void Init();

	virtual void Update();
	virtual void Render();

public:
	
	/// <summary>
	/// 물줄기 block 스폰시키기
	/// </summary>
	/// <param name="spawnCoord"> : 스폰 위치 </param>
	/// <param name="isEnd"> : 맨 끝 물줄기인지 </param>
	/// <returns> : 스폰된 자기자신 return </returns>
	StreamBlock* Spawn(const Util::Coord& spawnCoord, const bool& isEnd = false);

public: /* Getters */

	bool			IsActive() const { return isActive; }

	ColliderRect*	GetBody() const { return body; }

	Util::Coord		GetSpawnCoord() const { return spawnCoord; }


protected:

	/*
	물줄기의 경우 자신의 물줄기 animation이 끝난 뒤 자신의 active를 끔
	물줄기 animation End event로 (param false) 걸어둘 함수
	*/
	void SetActive(const bool& isActive);

protected:

	/* 
	물줄기 block animation이 모두 끝나기 전에 body collider를 끌 예정 -> 물줄기 판정 조정
	Animation내에서 AnimNotify call back으로 특정 idx가 지났을 때 호출될 함수 
	*/
	void DisableBodyCollider();

protected: /* Collider call back functions */

	void OnColliderPointEnter(ColliderHolder* owner);
	void OnColliderRectEnter(ColliderRect* targetCollider, ColliderHolder* owner);

/***************************************************************************************************
*                                          Member variables                                        *
****************************************************************************************************/

protected:

	bool isActive{};

	Util::Coord spawnCoord{};

	ColliderRect* body{};
	
protected:

	// 물줄기 끝 block의 animation은 살짝 다름
	bool		isEnd{};		// isEnd이면 endAnim을 사용
	Animation*	curAction{};	// 현재 선택된 animation
	Animation*	mainAnim{};		// 자신의 위치가 물줄기의 끝부분이 아닐 때 사용할 animation
	Animation*	endAnim{};		// 자신이 물줄기의 끝부분일 때 사용할 animation
	
protected:

	VertexShader*	vertexShader{};
	PixelShader*	pixelShader{};

	MatrixBuffer*	worldBuffer{};
	ColorBuffer*	colorBuffer{};

protected:

	/* sprite 재생 index 순서 */
	const vector<UINT>	ANIM_INDICES{ 3, 0, 1, 2, 1, 0, 1, 2, 1, 0, 1, 2, 1, 4, 5, 6, 7, 8, 9, 10 };

	/* 
	물줄기 block animation이 모두 끝나기 전에 BODY_COLLISION_DISABLE_IDX 까지 재생하였다면 body collider를 끌 예정 ->
	물줄기 판정 조정
	*/
	const UINT			BODY_COLLISION_DISABLE_IDX{ 14 };
	
	const float			ANIM_SPEED = 0.04f;
};
