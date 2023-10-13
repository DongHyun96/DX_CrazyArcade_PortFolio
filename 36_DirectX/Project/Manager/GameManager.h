#pragma once

class Transform;
class BalloonManager;
class BlockManager;
class StreamManager;
class Character;
class Collider;
class ColliderRect;
class DartManager;

enum GameMode
{
	PVP,
	PVE
};

enum GameMap
{
	VILLAGE,
	FACTORY,
	FOREST
};

enum Direction;
enum PlayerType;

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

	void SetGameMode(const GameMode& gameMode);
	GameMode GetGameMode() const { return gameMode; }
	
	//void SetPlayer(Character* player) { this->player = player; }
	//Character* GetPlayer() const { return player; }

	void SetPlayers(Character* p1, Character* p2);
	void SetPlayers(Character* p1, vector<Character*> enemies);
	
	vector<Character*>& GetWholePlayers() { return wholePlayers; }

	Character* GetP1() const { return p1; }
	Character* GetP2() const { return p2; }

	vector<Character*>& GetComEnemies() { return comEnemies; }

	void SetBalloonManager(BalloonManager* balloonManager) { this->balloonManager = balloonManager; }
	BalloonManager* GetBalloonManager() const { return balloonManager; }

	void SetBlockManager(BlockManager* blockManager) { this->blockManager = blockManager; }
	BlockManager* GetBlockManager() const { return blockManager; }

	void SetStreamManager(StreamManager* streamManager) { this->streamManager = streamManager; }
	StreamManager* GetStreamManager() const { return streamManager; }

	void SetDartManager(DartManager* dartManager) { this->dartManager = dartManager; }
	DartManager* GetDartManager() const { return dartManager; }


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











public: // Players' keyCode

	map<PlayerType, map<Direction, byte>> P_DIR_KEYCODE{};
	map<PlayerType, byte> P_BALLOON_KEYCODE{};
	map<PlayerType, byte> P_ITEM_KEYCODE{};

public: // SelectedMap ���� (start ��ġ���� / �ε��� Ÿ��, ��� bin ����
	
	map<GameMap, vector<Util::Coord>> spawnPosMap{};

	map<GameMap, wstring> tileBinFile{};
	map<GameMap, wstring> blockBinFile{};

	GameMap GetCurMapType() const { return curMap; }

private:

	GameMode gameMode{PVP};
	GameMap curMap{ VILLAGE };

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

	// ĳ���Ͱ� ���������� Character�� ����ִ� PlayerType���� ���а�����
	Character* player{};
	
	vector<Character*> wholePlayers{};

	Character* p1{};
	Character* p2{};
	
	vector<Character*> comEnemies{};

	BalloonManager* balloonManager{};
	BlockManager* blockManager{};
	StreamManager* streamManager{};

	DartManager* dartManager{};

};
