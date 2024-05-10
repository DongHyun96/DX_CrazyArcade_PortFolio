#pragma once
/* 
CONCRETE CLASS
���� ��ġ(��� StreamBlock�� ��ġ)�� ���ٱ� level�� �޾�,
�ð����� �ξ� ��� StreamBlock���� ������ �ð��������� 4���� StreamBlock ���� ó�� ���
*/
class Stream
{
public:
	Stream();
	~Stream();

	void Init();

	void Update();

public:

	/// <summary>
	/// <para> spawnCoord(��� streamBlock��ġ)���� �����ؼ� streamLv�� ����(�׸��� ���������� ����) </para>
	/// <para> StreamBlock�� �ð����� �ΰ� ���� </para>
	/// </summary>
	/// <param name="spawnCoord"> : ���ٱ� ���� ����� ��ġ </param>
	/// <param name="streamLv"> : ���ٱ� level </param>
	void Spawn(const Util::Coord& spawnCoord, const UINT& streamLv);

public:

	bool IsActive() const { return isActive; }

public: /* StreamDanagerZone ���� (Enemy�� PathFinding���� �ʿ�) */

	/// <summary>
	/// Balloon�� ���� ��, ���� balloon�� ��ǥ�� streamLv�� �޾� ���ٱ� ���� ���� �߰�
	/// </summary>
	/// <param name="balloonCoord"> : ���� balloon�� ��ǥ </param>
	/// <param name="streamLv"> : Stream level </param>
	static void AddStreamDanagerZone(const Util::Coord& balloonCoord, const UINT& streamLv);
	
	static void EraseStreamDangerZone(const Util::Coord& coord) { streamDangerZone.erase(coord); }

	static bool IsStreamDangerZone(const Util::Coord& coord) { return (streamDangerZone.find(coord) != streamDangerZone.end()); }

private:
	/// <summary>
	/// ù spawn�� ����������� �����ϴ��� reachedCoordMap �ʱ�ȭ
	/// </summary>
	/// <param name="spawnCoord"> : Spawn ��ġ(��� StreamBlock��ġ) </param>
	/// <param name="streamLv"> : Stream level </param>
	void InitReachedMap(const Util::Coord& spawnCoord, const UINT& streamLv);

	/* ���ٱ� ���� ���� ���� ���� balloon�� �ִ��� �����ؼ� �ִٸ� �ش� balloon�� ��� ���� ���� ��Ŵ */
	void HandleChainExplosion();

	/* �ð����� �ΰ� �� ������ StreamBlock���� spawn��Ŵ */
	void HandleSpawning();

	/* this�� ������Ų StreamBlock�� ��� �� ������ �ڽ��� active�� �� */
	void HandleSelfActive();

/***************************************************************************************************
*                                          Member variables                                        *
****************************************************************************************************/

private:

	bool isActive{};

private:
	/* �� Direction ���� ������ ��� ��ǥ�� */
	map<Direction, deque<Util::Coord>> reachedCoordMap{};

private:
	/* ���� �ֱ� spawn�� ���ٱ� block�� �� ���� spawn�� ���ٱ� block�� spawn �ð��� */
	const float BLOCK_SPAWN_DELTA{ 0.05f };

	float		blockSpawnTime = 0.f;
	bool		stopSpawning = true;

private:
	/* �� Stream(this) ��ü�� ������Ų activated streamBlocks */
	vector<StreamBlock*> activatedBlocks{};
	
	//���� stream ��ġ�� ���� -> AStar���� cell �Ǵ� �� ���
	static set<Util::Coord> streamDangerZone;

};
