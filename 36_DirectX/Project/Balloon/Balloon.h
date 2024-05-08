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

	/// <param name="spawnCoord"> : ������ų cell coordinate </param>
	/// <param name="owner"> : ��ǳ���� ������Ű���� ownerCharacter </param>
	/// <returns> : ���������� ���� �Ǿ��ٸ� return true </returns>
	virtual bool Spawn(const Util::Coord& spawnCoord, Character* owner);

public:
	/* Balloon �Ͷ߸��� */
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
	/// ���� DangerZone ����
	/// </summary>
	/// <param name="coord"> : ������ cell coordinate </param>
	static void ErasePreDangerZone(const Util::Coord& coord) { preDangerZone.erase(coord); }

	/// <summary>
	/// ������ ������ ���ٱ� ����(PreDangerZone) �� �� ������ üũ
	/// </summary>
	/// <param name="coord"> : �˻��� cell coordinate </param>
	/// <returns> ������ ���ٱ� ���� �� �� ���̸� return true </returns>
	static bool IsPreDangerZone(const Util::Coord& coord) { return (preDangerZone.find(coord) != preDangerZone.end()); }

protected:

	/// <summary>
	/// ���� DangerZone �߰�
	/// </summary>
	/// <param name="spawnCoord"> : ���� spawn�� ��ǳ���� ��ǥ </param>
	/// <param name="streamLv"> : ���� spawn�� ��ǳ���� stream lv </param>
	static void AddPreDangerZone(const Util::Coord& spawnCoord, const UINT& streamLv);

protected:

	/// <summary>
	/// ��ǳ�� spawn��Ű��
	/// </summary>
	/// <param name="spawnPos"> Spawn�� position </param>
	void Spawn(const Vector2& spawnPos);

protected:
	/* ���� �ð� üũ�Ͽ� EXPLODE_TIME_LIMIT �̻� �ð��� ������ ��ǳ���� ��ħ (Called in Update tick) */
	virtual void HandleExplode();



protected:
	bool isActive{};
	bool visible = true;

protected:
	/* Spawned cell Coordinate */
	Util::Coord spawnCoord{};

protected:

	static vector<Util::Coord>	activeBalloonCoords;		// ���� Active�� ��� balloon���� Cell ��ǥ��
	static vector<Vector2>		activeBalloonPositions;		// ���� Active�� ��� balloon���� positions

protected:

	ColliderRect*	body{};			// Body collider
	Animation*		balloonAnim{};	// Balloon animation

protected:

	UINT streamLv{}; // �� balloon�� ���ٱ� lv

protected:

	ColorBuffer*	colorBuffer{};
	VertexShader*	vertexShader{};
	PixelShader*	pixelShader{};

	MatrixBuffer*	worldBuffer{};

protected:
	/* 
	������ �� owner character�� ���� �� �ִ� ��ǳ�� ���� ȸ������� ��
	Spawn�ÿ� �ڽ��� owner�� �޾ƿ� ����
	*/
	Character* owner{};

protected: // ���� ���� �뵵 (1 tick�� ǳ���� �������� ���������� üũ)

	/*
	Update �� tick�� ��� balloon�� ���� ��, ������ �ʹ� ŭ
	��ǳ�� ������ �Ҹ��� Update tick ������ �� ���� ó���� �� ����
	*/
	static bool explodeSoundPlayed;

private:

	float		explosionTimer{};			
	const float EXPLODE_TIME_LIMIT{ 3.f };	// ��ǳ���� ���� �� �ܺ��� ȿ�� ���� ��ü������ ���� �ð�

private:
	
	/*
	������ ������ ���ٱ���� ��ġ cell coordinates
	���� stream ��ġ�� ����->Enemy�� path target�� ã�� �� ���
	*/
	static set<Util::Coord> preDangerZone;
};
