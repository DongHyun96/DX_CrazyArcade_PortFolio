#pragma once


class Balloon : public ColliderHolder
{
public:
	Balloon();
	~Balloon();

	void Update();
	void Render();

	bool Spawn(const Util::Coord& spawnCoord, Character* owner);

	void Explode();

	void OnColliderRectEnter(ColliderRect*	targetCollider, ColliderHolder* owner);

public:

	bool& Active() { return isActive; }
	ColliderRect* GetBody() const { return body; }
	
	void SetVisible(const bool& visible) { this->visible = visible; }

	static vector<Vector2> GetActiveBalloonPositions() { return activeBalloonPositions; }
	
	Util::Coord GetSpawnCoord() const { return spawnCoord; }

	static void SetExplodeSoundPlayed(const bool& played) { explodeSoundPlayed = played; }


private:

	bool Spawn(const Vector2& spawnPos);

	void HandleExplode();

private:

	Util::Coord spawnCoord{};

	static vector<Vector2> activeBalloonPositions;

	bool isActive{};
	bool visible{ true };

	ColliderRect*	body{};
	Animation*		balloonAnim{};


	float		explodeTime{};
	const float EXPLODE_TIME_LIMIT{ 3.f };


	ColorBuffer*	colorBuffer{};
	VertexShader*	vertexShader{};
	PixelShader*	pixelShader{};

	MatrixBuffer*	worldBuffer{};

private:
	
	// ������ �� owner�� ��ǳ�� ���� ȸ�����ֱ�
	Character* owner{}; // spawn�ÿ� �ڽ��� owener�� �޾ƿ� ����

private: // ���� ���� �뵵 (1 tick�� ǳ���� �������� ���������� üũ)
	static bool explodeSoundPlayed;

};
