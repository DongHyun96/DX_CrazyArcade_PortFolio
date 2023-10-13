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
	
	// 터졌을 때 owner의 물풍선 개수 회복해주기
	Character* owner{}; // spawn시에 자신의 owener를 받아올 것임

protected: // 볼륨 조절 용도 (1 tick에 풍선이 터졌는지 안터졌는지 체크)

	static bool explodeSoundPlayed;

private:

	float		explodeTime{};
	const float EXPLODE_TIME_LIMIT{ 3.f };

};
