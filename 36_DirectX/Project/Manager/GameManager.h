#pragma once

class Transform;
class BalloonManager;
class Character;
class Collider;
class ColliderRect;

class GameManager
{
private:

	GameManager();
	~GameManager();

public:
	
	static GameManager* GetInst()
	{
		static GameManager singleton;
		return &singleton;
	}

	void Update();
	
	void SetPlayer(Character* player) { this->player = player; }
	Character* GetPlayer() const { return player; }

	void SetBalloonManager(BalloonManager* balloonManager) { this->balloonManager = balloonManager; }
	BalloonManager* GetBalloonManager() const { return balloonManager; }

public:

	Transform* GetGameFieldTransform() const { return gameFieldTransform; }
	bool IsEditMode() const { return editMode; }

	float GetMapL() const { return mapL; }
	float GetMapR() const { return mapR; }
	float GetMapT() const { return mapT; }
	float GetMapB() const { return mapB; }


	/// <param name="point"> --> Use Global Position</param>
	Vector2 GetCollidedMapCellPos(const Vector2& point);


private: // Board 및 GameField 관련

	Transform* gameFieldTransform{};

	//VillageBlockSampleData
	//VillageTileData
	const wstring blockDataPath = L"VillageBlockData";
	const wstring tileDataPath  = L"VillageTileData";
	
	bool editMode = false;

	float mapL{};
	float mapR{};
	float mapT{};
	float mapB{};

	ColliderRect* mapCells[MAP_ROW][MAP_COL]{};

private: // 게임 오브젝트 관련 (생성 해제는 GameScene에서 담당)

	Character* player{};
	BalloonManager* balloonManager{};

};
