#pragma once
/* CONCRETE CLASS */
class DartManager
{
public:
	DartManager();
	~DartManager();

	void Update();
	void Render();

	void Init();

public:

	/// <summary>
	/// Dart pool에서 dart 스폰 시도
	/// </summary>
	/// <param name="spawnPos"> : 스폰 시작 위치 </param>
	/// <param name="fireDirection"> : 발사 방향 </param>
	void Spawn(const Vector2& spawnPos, const Direction& fireDirection);

	void HandleCollision();

	vector<Dart*>& GetDarts() { return darts; }

private:

	const UINT POOL_CNT{ 20 };

	vector<Dart*> darts{};

};
