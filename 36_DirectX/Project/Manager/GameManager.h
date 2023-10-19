#pragma once

class Transform;

class Collider;
class ColliderRect;

class GameUIManager;
class PlayerManager;
class BlockManager;
class BalloonManager;
class StreamManager;
class ItemManager;
class DartManager;


class GameScene;

enum GameMode
{
	PVP,
	PVE
};

enum GameMap
{
	VILLAGE,
	FACTORY,
	FOREST,
	MAP_MAX
};

enum GameStatus
{
	START,
	PLAY,
	GAME_OVER
};


enum Direction;

enum CharacterType;
enum PlayerType;

namespace Util { struct Coord; }


class GameManager : public Singleton<GameManager>
{
	friend class Singleton;

private:

	GameManager();
	~GameManager();

//public:
//
//	static GameManager* GetInstance()
//	{
//		static GameManager singleton;
//		return &singleton;
//	}

public:

	void CreateGameObjects(); // MainGame �����ڿ��� call (GM �����ڿ��� �θ��� Singleton �����ñ� ������ ������)

	// GameScene ���� ���� (�Ǵ� ���� ��) �� �� ó��
	void InitGame();


public:
	
	void Update();

	void SetGameMode(const GameMode& gameMode) { this->gameMode = gameMode; }
	GameMode GetGameMode() const { return gameMode; }
	
	void SetGameScene(GameScene* gameScene) { this->gameScene = gameScene; }
	GameScene* GetGameScene() const { return gameScene; }

	PlayerManager* GetPlayerManager() const { return playerManager; }
	
	BalloonManager* GetBalloonManager() const { return balloonManager; }

	void SetBlockManager(BlockManager* blockManager) { this->blockManager = blockManager; }
	BlockManager* GetBlockManager() const { return blockManager; }

	StreamManager* GetStreamManager() const { return streamManager; }

	ItemManager* GetItemManager() const { return itemManager; }

	DartManager* GetDartManager() const { return dartManager; }

	GameUIManager* GetGameUIManager() const { return gameUIManager; }

	GameStatus GetGameStatus() const { return gameStatus; }
	void SetGameStatus(const GameStatus& gameStatus) { this->gameStatus = gameStatus; }

	Transform* GetGameFieldTransform() const { return gameFieldTransform; }

	map<PlayerType, CharacterType>& P_SelectedCharacterMap() { return pSelectedCharacterMap; }

public:

	bool IsEditMode() const { return editMode; }

	float GetMapL() const { return mapL; }
	float GetMapR() const { return mapR; }
	float GetMapT() const { return mapT; }
	float GetMapB() const { return mapB; }

	/// <param name="point"> --> Use Global Position</param>
	Vector2 GetCollidedMapCellPos(const Vector2& point);
	Util::Coord GetCollidedMapCellCoord(const Vector2& point);



public: // SelectedMap ���� (start ��ġ���� / �ε��� Ÿ��, ��� bin ����
	
	map<GameMap, wstring> tileBinFile{};
	map<GameMap, wstring> blockBinFile{};
	map<GameMap, string> mapBGM{};

	GameMap GetCurMapType() const { return curMap; }
	void SetCurMapType(const GameMap& type) { this->curMap = type; }

private:

	GameMode gameMode{PVP};
	GameMap curMap{ FACTORY };
	
	map<PlayerType, CharacterType> pSelectedCharacterMap{};



private: // Board �� GameField ����

	Transform* gameFieldTransform{};
	
	bool editMode = false;

	float mapL{};
	float mapR{};
	float mapT{};
	float mapB{};

	ColliderRect* mapCells[MAP_ROW][MAP_COL]{};

private: // ���� ������Ʈ ���� / �������� Update Render�� GameScene���� ���

	GameScene* gameScene{};

	GameUIManager* gameUIManager{};

	PlayerManager* playerManager{};

	// Ÿ�ϸŴ����� BlockManager�� �û� �ٲ� (GameScene���� ���� ���� ���), BlockManager�� GameManager�� set�ؼ� �������� �Ѹ� ����
	BlockManager* blockManager{}; 

	BalloonManager* balloonManager{};

	StreamManager* streamManager{};

	ItemManager* itemManager{};

	DartManager* dartManager{};

	GameStatus gameStatus{ START };

};
