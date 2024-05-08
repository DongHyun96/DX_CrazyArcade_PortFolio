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

/* ���� Scene�� GameScene�� ���� Game status */
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

	/* MainGame �����ڿ��� call (GM �����ڿ��� �θ��� Singleton �����ñ� ������ ������) */
	void CreateGameObjects();

	/* GameScene ���� ����(GameOver����)�̳� GameScene ���� �� �� �� ó�� */ 
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
	

public: /* �� GameMap�� ���� binary data�� & BGM�� ���� */

	map<GameMap, wstring>	tileBinFile{};
	map<GameMap, wstring>	blockBinFile{};
	map<GameMap, string>	mapBGM{};

private: /* ���� �� GameMode, Edit mode, Game Map, Character, GameStatus ���� */

	GameMode						gameMode{};					// CurGameMode
	GameMap							curMap{};					// Cur selected gameMap
	map<PlayerType, CharacterType>	pSelectedCharacterMap{};	// P1, P2�� ���� �� CharacterType
	bool							editMode{};					// If it is edit mode
	GameStatus						gameStatus{};				// CurScene�� GameScene�� ��� ����� ���� ���� ���� ��Ȳ

private: /* Board �� GameField ���� */

	/* 
	�������� Game Map Field�� ��ü Window size�� ������ �ʰ� Game UI Panel �ȿ� �� ���� ũ��� ����
	Game���� ����� Game Object�� ��ü�� Transform�� Window size�� �°Բ� ��ü ũ��� ��ġ�� ��, �ֻ��� Parent Transform��
	�ش� ������ ���� ���� -> Game field�� GameObject ��ġ�ϱⰡ �� ����
	*/
	Transform*		gameFieldTransform{};

	float			mapL{};	// Map Left boundary limit
	float			mapR{};	// Map Right boundary limit
	float			mapT{};	// Map Top boundary limit
	float			mapB{};	// Map Bottom boundary limit

	/*
	Game Map�� ��ġ�� �� cell���� colliders
	Game Object���� cell coordinate�� �ľ��ϱ� ���� �뵵�� ���
	*/
	ColliderRect*	mapCellColliders[MAP_ROW][MAP_COL]{};

private:
	/* ���� �÷��� ���� GameScene -> GameScene���� scene ��ȯ�� �̷���� �� �Ҵ��� ���� */
	GameScene* gameScene{};

private: /* InGame ������Ʈ ����, �������� Update, Render�� GameScene���� ��� */

	GameUIManager*		gameUIManager{};	// GameSceneUIManager

	PlayerManager*		playerManager{};

	/*
	TileManager�� BlockManager�� �û� �ٲ� (GameScene���� ���� ���� ���)
	BlockManager�� GameManager�� set�ؼ� ���������� �Ѹ� ����
	*/
	BlockManager*		blockManager{}; 

	BalloonManager*		balloonManager{};

	StreamManager*		streamManager{};

	ItemManager*		itemManager{};

	DartManager*		dartManager{};

	

};
