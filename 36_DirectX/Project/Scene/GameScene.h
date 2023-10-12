#pragma once


class GameScene : public Scene
{
public:
	GameScene();
	~GameScene();

	virtual void Update() override;
	virtual void Render() override;

private:

	//Collider* mapBoundary{};

	TileManager* tileManager{};
	BlockManager* blockManager{};
	BalloonManager* balloonManager{}; // TODO 터졌을 때 콜백으로 플레이어의 balloonCnt에서 1을 돌려줘야 함


	Block* block{};
	Util::Coord curBlockPos{};

	Block* block2{};

	Character* player{};

	StreamManager* streamManager{};

	ItemManager* itemManager{};

	DartManager* dartManager{};

};

