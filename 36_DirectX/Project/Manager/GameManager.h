#pragma once

class Transform;
class BalloonManager;
class BlockManager;
class StreamManager;
class Character;
class Collider;
class ColliderRect;


namespace Util { struct Coord; }

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

	void SetBlockManager(BlockManager* blockManager) { this->blockManager = blockManager; }
	BlockManager* GetBlockManager() const { return blockManager; }

	void SetStreamManager(StreamManager* streamManager) { this->streamManager = streamManager; }
	StreamManager* GetStreamManager() const { return streamManager; }


public:

	Transform* GetGameFieldTransform() const { return gameFieldTransform; }
	bool IsEditMode() const { return editMode; }

	float GetMapL() const { return mapL; }
	float GetMapR() const { return mapR; }
	float GetMapT() const { return mapT; }
	float GetMapB() const { return mapB; }


	/// <param name="point"> --> Use Global Position</param>
	Vector2 GetCollidedMapCellPos(const Vector2& point);
	Util::Coord GetCollidedMapCellCoord(const Vector2& point);


private: // Board �� GameField ����

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

private: // ���� ������Ʈ ���� (���� ������ GameScene���� ���)

	Character* player{};
	BalloonManager* balloonManager{};
	BlockManager* blockManager{};
	StreamManager* streamManager{};

};
