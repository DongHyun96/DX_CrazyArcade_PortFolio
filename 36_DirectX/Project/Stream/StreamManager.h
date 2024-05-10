#pragma once
/*
CONCRETE CLASS
물줄기 최상위 총괄 매니저 역할
Stream Object pooling과 StreamBlockManager를 갖고 있음
물줄기 spawn 의뢰를 여기서 첫 시작으로 받음 (SpawnStream함수를 통해)
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
	/// 물줄기 spawn의뢰의 첫 시작
	/// </summary>
	/// <param name="spawnCoord"> : Spawn cell 좌표(물줄기의 정 가운데) </param>
	/// <param name="streamLv"> : Spawn할 stream의 stream level </param>
	void SpawnStream(const Util::Coord& spawnCoord, const UINT& streamLv);

	static StreamBlockManager* GetStreamBlockManager() { return streamBlockManager; }

private:
	
	const UINT		POOL_CNT = 60;
	vector<Stream*>	streams{};			// Stream Object pool

private:
	/* 
	StreamManager를 static으로 소유하고 Stream 스폰 시 StreamBlock을 차례로 스폰할 때,
	이 streamBlockManager를 통해 StreamBlock 스폰시킴
	*/
	static StreamBlockManager*	streamBlockManager;

};
