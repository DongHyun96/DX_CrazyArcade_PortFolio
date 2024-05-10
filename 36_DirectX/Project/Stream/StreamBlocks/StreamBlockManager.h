#pragma once
/*
CONCRETE CLASS
StreamBlock Object pooling manager
*/
class StreamBlockManager
{
public:
	StreamBlockManager();
	~StreamBlockManager();

	void Init();

	void Update();
	void Render();

public:
	/// <summary>
	/// Cell 한 칸 StreamBlock 스폰 시키기
	/// </summary>
	/// <param name="dir"> : 물줄기 4방향 중 어느 방향 물줄기인지 </param>
	/// <param name="spawnCoord"> : 스폰 위치 </param>
	/// <param name="isEnd"> : 물줄기의 맨 끝 block인지(끝 block의 animation은 일반과 다름)</param>
	/// <returns> : Spawn된 StreamBlock 객체 </returns>
	StreamBlock* Spawn(const Direction& dir, const Util::Coord& spawnCoord, const bool& isEnd = false);
		
private:
	
	/* 맵 블록, 아이템, 캐릭터와의 충돌검사 및 처리 */
	void HandleCollision();

	void HandleBlockCollision(StreamBlock* streamBlock); // StreamBlock vs Block
	void HandleItemCollision(StreamBlock* streamBlock);	 // StreamBlock vs Item

private:

	const UINT CENTER_POOL_CNT	= 60;						// 가운데 StreamBlock pool count
	const UINT DIR_POOL_CNT		= 48;						// 각 direction에 대한 each streamBlock pool count

	vector<StreamBlock*>					centerBlocks{}; // 가운데 StreamBlock Object pool
	map<Direction, vector<StreamBlock*>>	dirStreamMap{};	// 각 direction에 대한 StreamBlock Object pool

	
};
