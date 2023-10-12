#pragma once
class DartManager
{
public:
	DartManager();
	~DartManager();

	void Update();
	void Render();

	void Spawn(const Vector2& spawnPos, const Direction& fireDirection);

	void HandleCollision();

	vector<Dart*>& GetDarts() { return darts; }

private:

	const UINT POOL_CNT{ 20 };

	vector<Dart*> darts{};

};
