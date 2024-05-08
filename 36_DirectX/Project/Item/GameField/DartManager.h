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
	/// Dart pool���� dart ���� �õ�
	/// </summary>
	/// <param name="spawnPos"> : ���� ���� ��ġ </param>
	/// <param name="fireDirection"> : �߻� ���� </param>
	void Spawn(const Vector2& spawnPos, const Direction& fireDirection);

	void HandleCollision();

	vector<Dart*>& GetDarts() { return darts; }

private:

	const UINT POOL_CNT{ 20 };

	vector<Dart*> darts{};

};
