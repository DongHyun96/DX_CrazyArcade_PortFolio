#pragma once
/*
CONCRETE CLASS
���ٱ� �ֻ��� �Ѱ� �Ŵ��� ����
Stream Object pooling�� StreamBlockManager�� ���� ����
���ٱ� spawn �Ƿڸ� ���⼭ ù �������� ���� (SpawnStream�Լ��� ����)
*/
class StreamManager
{
public:
	StreamManager();
	~StreamManager();

	void Update();
	void Render();

	void Init();

public:

	/// <summary>
	/// ���ٱ� spawn�Ƿ��� ù ����
	/// </summary>
	/// <param name="spawnCoord"> : Spawn cell ��ǥ(���ٱ��� �� ���) </param>
	/// <param name="streamLv"> : Spawn�� stream�� stream level </param>
	void SpawnStream(const Util::Coord& spawnCoord, const UINT& streamLv);

	static StreamBlockManager* GetStreamBlockManager() { return streamBlockManager; }

private:
	
	const UINT		POOL_CNT = 60;
	vector<Stream*>	streams{};			// Stream Object pool

private:
	/* 
	StreamManager�� static���� �����ϰ� Stream ���� �� StreamBlock�� ���ʷ� ������ ��,
	�� streamBlockManager�� ���� StreamBlock ������Ŵ
	*/
	static StreamBlockManager*	streamBlockManager;

};
