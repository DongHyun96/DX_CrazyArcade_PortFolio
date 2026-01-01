#pragma once


/* 
CONCRETE CLASS
Owned by BalloonManager
*/
class Balloon : public ColliderHolder
{
public:
	/// <param name="animation"> : Balloon default sprite animation </param>
	Balloon(Animation* animation);
	virtual ~Balloon();

	void Init();

	void Update();
	void Render();

public:

	/// <param name="spawnCoord"> : 스폰시킬 cell coordinate </param>
	/// <param name="owner"> : 물풍선을 스폰시키려는 ownerCharacter </param>
	/// <returns> : 정상적으로 스폰 되었다면 return true </returns>
	virtual bool Spawn(const Util::Coord& spawnCoord, Character* owner);

public:
	/* Balloon 터뜨리기 */
	virtual void Explode();

public:
	/// <summary>
	/// Collision call back function
	/// </summary>
	/// <param name="targetCollider"> : Entered collider </param>
	/// <param name="owner"> : Owner of the entered collider </param>
	void OnColliderRectEnter(ColliderRect* targetCollider, ColliderHolder* owner);

public: /* Getters and setters */

	bool&						Active() { return isActive; }
	ColliderRect*				GetBody() const { return body; }
	
	void						SetVisible(const bool& visible) { this->visible = visible; }

	static vector<Vector2>&		GetActiveBalloonPositions() { return activeBalloonPositions; }
	static vector<Util::Coord>&	GetActiveBalloonCoords() { return activeBalloonCoords; }
	
	static bool					IsActiveBalloonOnCoord(const Util::Coord& coord);

	Util::Coord					GetSpawnCoord() const { return spawnCoord; }

	static void					SetExplodeSoundPlayed(const bool& played) { explodeSoundPlayed = played; }

public:

	/// <summary>
	/// 예비 DangerZone 삭제
	/// </summary>
	/// <param name="coord"> : 삭제할 cell coordinate </param>
	static void ErasePreDangerZone(const Util::Coord& coord) { preDangerZone.erase(coord); }

	/// <summary>
	/// 앞으로 생성될 물줄기 영역(PreDangerZone) 중 한 곳인지 체크
	/// </summary>
	/// <param name="coord"> : 검사할 cell coordinate </param>
	/// <returns> 생성될 물줄기 영역 중 한 곳이면 return true </returns>
	static bool IsPreDangerZone(const Util::Coord& coord) { return (preDangerZone.find(coord) != preDangerZone.end()); }

protected:

	/// <summary>
	/// 예비 DangerZone 추가
	/// </summary>
	/// <param name="spawnCoord"> : 새로 spawn될 물풍선의 좌표 </param>
	/// <param name="streamLv"> : 새로 spawn될 물풍선의 stream lv </param>
	static void AddPreDangerZone(const Util::Coord& spawnCoord, const UINT& streamLv);

protected:

	/// <summary>
	/// 물풍선 spawn시키기
	/// </summary>
	/// <param name="spawnPos"> Spawn할 position </param>
	void Spawn(const Vector2& spawnPos);

protected:
	/* 폭발 시간 체크하여 EXPLODE_TIME_LIMIT 이상 시간이 지나면 물풍선을 터침 (Called in Update tick) */
	virtual void HandleExplode();

/***************************************************************************************************
*                                          Member variables                                        *
****************************************************************************************************/

protected:
	bool isActive{};
	bool visible = true;

protected:
	/* Spawned cell Coordinate */
	Util::Coord spawnCoord{};

protected:

	static vector<Util::Coord>	activeBalloonCoords;		// 현재 Active한 모든 balloon들의 Cell 좌표들
	static vector<Vector2>		activeBalloonPositions;		// 현재 Active한 모든 balloon들의 positions

protected:

	ColliderRect*	body{};			// Body collider
	Animation*		balloonAnim{};	// Balloon animation

protected:

	UINT streamLv{}; // 이 balloon의 물줄기 lv

protected:

	ColorBuffer*	colorBuffer{};
	VertexShader*	vertexShader{};
	PixelShader*	pixelShader{};

	MatrixBuffer*	worldBuffer{};

protected:
	/* 
	터졌을 때 owner character의 놓을 수 있는 물풍선 개수 회복해줘야 함
	Spawn시에 자신의 owner를 받아올 것임
	*/
	Character* owner{};

protected: // 볼륨 조절 용도 (1 tick에 풍선이 터졌는지 안터졌는지 체크)

	/*
	Update 한 tick에 모든 balloon이 터질 때, 볼륨이 너무 큼
	물풍선 터지는 소리는 Update tick 내에서 한 번만 처리를 할 예정
	*/
	static bool explodeSoundPlayed;

private:

	float		explosionTimer{};			
	const float EXPLODE_TIME_LIMIT{ 3.f };	// 물풍선이 놓인 뒤 외부의 효과 없이 자체적으로 터질 시간

private:
	
	/*
	앞으로 생성될 물줄기들의 위치 cell coordinates
	예비 stream 위치를 저장->Enemy의 path target을 찾을 때 사용
	*/
	static set<Util::Coord> preDangerZone;
};
