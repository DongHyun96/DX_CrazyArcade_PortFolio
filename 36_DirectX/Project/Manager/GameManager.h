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

	void CreateGameObjects(); // MainGame 생성자에서 call (GM 생성자에서 부르면 Singleton 생성시기 때문에 오류남)

	// GameScene 끝난 이후 (또는 시작 전) 한 번 처리
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



public: // SelectedMap 관련 (start 위치정보 / 로드할 타일, 블록 bin 파일
	
	map<GameMap, wstring> tileBinFile{};
	map<GameMap, wstring> blockBinFile{};
	map<GameMap, string> mapBGM{};

	GameMap GetCurMapType() const { return curMap; }
	void SetCurMapType(const GameMap& type) { this->curMap = type; }

private:

	GameMode gameMode{PVP};
	GameMap curMap{ FACTORY };
	
	map<PlayerType, CharacterType> pSelectedCharacterMap{};



private: // Board 및 GameField 관련

	Transform* gameFieldTransform{};
	
	bool editMode = false;

	float mapL{};
	float mapR{};
	float mapT{};
	float mapB{};

	ColliderRect* mapCells[MAP_ROW][MAP_COL]{};

private: // 게임 오브젝트 관련 / 실질적인 Update Render는 GameScene에서 담당

	GameScene* gameScene{};

	GameUIManager* gameUIManager{};

	PlayerManager* playerManager{};

	// 타일매니저와 BlockManager는 늘상 바뀜 (GameScene에서 생성 해제 담당), BlockManager만 GameManager로 set해서 전역으로 뿌릴 것임
	BlockManager* blockManager{}; 

	BalloonManager* balloonManager{};

	StreamManager* streamManager{};

	ItemManager* itemManager{};

	DartManager* dartManager{};

	GameStatus gameStatus{ START };

};
