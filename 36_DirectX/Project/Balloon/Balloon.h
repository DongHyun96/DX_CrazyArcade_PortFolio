#pragma once


class Balloon : public ColliderHolder
{
public:
	Balloon(Animation* animation);
	virtual ~Balloon();

	void Init();

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
	
	static vector<Util::Coord>& GetActiveBalloonCoords() { return activeBalloonCoords; }
	
	static bool IsActiveBalloonOnCoord(const Util::Coord& coord);

	Util::Coord GetSpawnCoord() const { return spawnCoord; }

	static void SetExplodeSoundPlayed(const bool& played) { explodeSoundPlayed = played; }

public:

	static void ErasePreDangerZone(const Util::Coord& coord) { preDangerZone.erase(coord); }
	static bool IsPreDangerZone(const Util::Coord& coord) { return (preDangerZone.find(coord) != preDangerZone.end()); }


protected:

	void Spawn(const Vector2& spawnPos);

	virtual void HandleExplode();

	static void AddPreDangerZone(const Util::Coord& spawnCoord, const UINT& streamLv);

protected:

	Util::Coord spawnCoord{};

	static vector<Util::Coord> activeBalloonCoords;
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

private:
	
	// 예비 stream 위치를 저장 -> Enemy의 path target을 찾을 때 사용
	static set<Util::Coord> preDangerZone;


};
