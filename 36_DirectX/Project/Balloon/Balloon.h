#pragma once


class Balloon : public ColliderHolder
{
public:
	Balloon(Animation* animation);
	virtual ~Balloon();

	void Update();
	void Render();

	virtual bool Spawn(const Util::Coord& spawnCoord, Character* owner);

	virtual void Explode();

	void OnColliderRectEnter(ColliderRect*	targetCollider, ColliderHolder* owner);

public:

	bool& Active() { return isActive; }
	ColliderRect* GetBody() const { return body; }
	
	void SetVisible(const bool& visible) { this->visible = visible; }

	static vector<Vector2>& GetActiveBalloonPositions() { return activeBalloonPositions; }
	
	Util::Coord GetSpawnCoord() const { return spawnCoord; }

	static void SetExplodeSoundPlayed(const bool& played) { explodeSoundPlayed = played; }


protected:

	bool Spawn(const Vector2& spawnPos);

	virtual void HandleExplode();

protected:

	Util::Coord spawnCoord{};

	static vector<Vector2> activeBalloonPositions;

	bool isActive{};
	bool visible{ true };

	ColliderRect*	body{};
	Animation*		balloonAnim{};

	UINT		streamLv{};

	ColorBuffer*	colorBuffer{};
	VertexShader*	vertexShader{};
	PixelShader*	pixelShader{};

	MatrixBuffer*	worldBuffer{};

protected:
	
	// ������ �� owner�� ��ǳ�� ���� ȸ�����ֱ�
	Character* owner{}; // spawn�ÿ� �ڽ��� owener�� �޾ƿ� ����

protected: // ���� ���� �뵵 (1 tick�� ǳ���� �������� ���������� üũ)

	static bool explodeSoundPlayed;

private:

	float		explodeTime{};
	const float EXPLODE_TIME_LIMIT{ 3.f };

};
