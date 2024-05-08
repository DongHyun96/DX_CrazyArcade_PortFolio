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
	//TEST_FIELD,
	MAP_MAX
};

/* 현재 Scene이 GameScene일 때의 Game status */
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


/* CONCRETE CLASS | SINGLETON */
class GameManager : public Singleton<GameManager>
{
	friend class Singleton;

private:

	GameManager();
	~GameManager();

public:

	void Update();

public:

	/* MainGame 생성자에서 call (GM 생성자에서 부르면 Singleton 생성시기 때문에 오류남) */
	void CreateGameObjects();

	/* GameScene 끝난 시점(GameOver이후)이나 GameScene 시작 전 한 번 처리 */ 
	void InitGame();


public: /* Getters and setters */

	void								SetGameMode(const GameMode& gameMode) { this->gameMode = gameMode; }
	GameMode							GetGameMode() const { return gameMode; }
	
	void								SetGameScene(GameScene* gameScene) { this->gameScene = gameScene; }
	GameScene*							GetGameScene() const { return gameScene; }

	PlayerManager*						GetPlayerManager() const { return playerManager; }
	
	BalloonManager*						GetBalloonManager() const { return balloonManager; }

	void								SetBlockManager(BlockManager* blockManager) { this->blockManager = blockManager; }
	BlockManager*						GetBlockManager() const { return blockManager; }

	StreamManager*						GetStreamManager() const { return streamManager; }

	ItemManager*						GetItemManager() const { return itemManager; }

	DartManager*						GetDartManager() const { return dartManager; }

	GameUIManager*						GetGameUIManager() const { return gameUIManager; }

	GameStatus							GetGameStatus() const { return gameStatus; }
	void								SetGameStatus(const GameStatus& gameStatus) { this->gameStatus = gameStatus; }

	Transform*							GetGameFieldTransform() const { return gameFieldTransform; }

	map<PlayerType, CharacterType>&		P_SelectedCharacterMap() { return pSelectedCharacterMap; }

	bool								IsEditMode() const { return editMode; }

	float								GetMapL() const { return mapL; }
	float								GetMapR() const { return mapR; }
	float								GetMapT() const { return mapT; }
	float								GetMapB() const { return mapB; }

	GameMap								GetCurMapType() const { return curMap; }
	void								SetCurMapType(const GameMap& type) { this->curMap = type; }

public:

	/// <param name="point"> : Use Global Position</param>
	Vector2 GetCollidedMapCellPos(const Vector2& point);

	/// <param name="point"> : Use Global Position</param>
	Util::Coord GetCollidedMapCellCoord(const Vector2& point);
	

public: /* 각 GameMap에 따른 binary data들 & BGM들 정보 */

	map<GameMap, wstring>	tileBinFile{};
	map<GameMap, wstring>	blockBinFile{};
	map<GameMap, string>	mapBGM{};

private: /* 현재 고른 GameMode, Edit mode, Game Map, Character, GameStatus 관련 */

	GameMode						gameMode{};					// CurGameMode
	GameMap							curMap{};					// Cur selected gameMap
	map<PlayerType, CharacterType>	pSelectedCharacterMap{};	// P1, P2가 현재 고른 CharacterType
	bool							editMode{};					// If it is edit mode
	GameStatus						gameStatus{};				// CurScene이 GameScene일 경우 사용할 현재 게임 진행 상황

private: /* Board 및 GameField 관련 */

	/* 
	실질적인 Game Map Field는 전체 Window size로 잡히지 않고 Game UI Panel 안에 더 작은 크기로 잡힘
	Game에서 사용할 Game Object들 자체의 Transform은 Window size에 맞게끔 전체 크기로 배치한 뒤, 최상위 Parent Transform을
	해당 변수로 잡을 것임 -> Game field에 GameObject 배치하기가 더 용이
	*/
	Transform*		gameFieldTransform{};

	float			mapL{};	// Map Left boundary limit
	float			mapR{};	// Map Right boundary limit
	float			mapT{};	// Map Top boundary limit
	float			mapB{};	// Map Bottom boundary limit

	/*
	Game Map에 배치된 각 cell들의 colliders
	Game Object들의 cell coordinate를 파악하기 위한 용도로 사용
	*/
	ColliderRect*	mapCellColliders[MAP_ROW][MAP_COL]{};

private:
	/* 현재 플레이 중인 GameScene -> GameScene으로 scene 전환이 이루어질 때 할당할 예정 */
	GameScene* gameScene{};

private: /* InGame 오브젝트 관련, 실질적인 Update, Render는 GameScene에서 담당 */

	GameUIManager*		gameUIManager{};	// GameSceneUIManager

	PlayerManager*		playerManager{};

	/*
	TileManager와 BlockManager는 늘상 바뀜 (GameScene에서 생성 해제 담당)
	BlockManager만 GameManager로 set해서 전역적으로 뿌릴 것임
	*/
	BlockManager*		blockManager{}; 

	BalloonManager*		balloonManager{};

	StreamManager*		streamManager{};

	ItemManager*		itemManager{};

	DartManager*		dartManager{};

	

};
