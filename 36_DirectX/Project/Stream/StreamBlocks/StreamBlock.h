#pragma once
class StreamBlock
{
public:
	StreamBlock();
	virtual ~StreamBlock();

	void Init();

	virtual void Update();
	virtual void Render();
	
	StreamBlock* Spawn(const Util::Coord& spawnCoord, const bool& isEnd = false);

	bool IsActive() const { return isActive; }

	ColliderRect* GetBody() const { return body; }

	Util::Coord GetSpawnCoord() const { return spawnCoord; }


protected:

	void SetActive(const bool& isActive);

	void OnAnimClipEvent();

protected:

	void OnColliderPointEnter(ColliderHolder* owner);
	void OnColliderRectEnter(ColliderRect* targetCollider, ColliderHolder* owner);

protected:

	bool isActive{};

	Util::Coord spawnCoord{};

	ColliderRect* body{};
	
	Animation* curAction{};

	// End point animation은 살짝 다름
	// 4방면의 End Point가 아닌 면의 animation
	Animation* mainAnim{};
	Animation* endAnim{};
	
	bool isEnd{}; // isEnd이면 endAnim을 사용

	VertexShader*	vertexShader{};
	PixelShader*	pixelShader{};

	MatrixBuffer*	worldBuffer{};
	ColorBuffer*	colorBuffer{};

	//const vector<UINT> ANIM_INDICES{ 3, 0, 1, 2, 0, 1, 2, 0, 1, 2, 0, 1, 2, 4, 5, 6, 7, 8, 9, 10 };
	const vector<UINT> ANIM_INDICES{ 3, 0, 1, 2, 1, 0, 1, 2, 1, 0, 1, 2, 1, 4, 5, 6, 7, 8, 9, 10 };
	const UINT ANIM_CLIP_IDX{ 14 };
	
	const float ANIM_SPEED{ 0.04f };
	//const float ANIM_SPEED{ 1.f };


	
};
