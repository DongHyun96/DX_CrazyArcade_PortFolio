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
	/// Cell �� ĭ StreamBlock ���� ��Ű��
	/// </summary>
	/// <param name="dir"> : ���ٱ� 4���� �� ��� ���� ���ٱ����� </param>
	/// <param name="spawnCoord"> : ���� ��ġ </param>
	/// <param name="isEnd"> : ���ٱ��� �� �� block����(�� block�� animation�� �Ϲݰ� �ٸ�)</param>
	/// <returns> : Spawn�� StreamBlock ��ü </returns>
	StreamBlock* Spawn(const Direction& dir, const Util::Coord& spawnCoord, const bool& isEnd = false);
		
private:
	
	/* �� ���, ������, ĳ���Ϳ��� �浹�˻� �� ó�� */
	void HandleCollision();

	void HandleBlockCollision(StreamBlock* streamBlock); // StreamBlock vs Block
	void HandleItemCollision(StreamBlock* streamBlock);	 // StreamBlock vs Item

private:

	const UINT CENTER_POOL_CNT	= 60;						// ��� StreamBlock pool count
	const UINT DIR_POOL_CNT		= 48;						// �� direction�� ���� each streamBlock pool count

	vector<StreamBlock*>					centerBlocks{}; // ��� StreamBlock Object pool
	map<Direction, vector<StreamBlock*>>	dirStreamMap{};	// �� direction�� ���� StreamBlock Object pool

	
};
