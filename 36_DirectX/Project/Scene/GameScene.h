#pragma once


class GameScene : public Scene
{
public:
	GameScene();
	~GameScene();

	virtual void Update() override;
	virtual void Render() override;

private:

	TileManager* tileManager{};
	BlockManager* blockManager{};
	BalloonManager* balloonManager{}; // TODO 터졌을 때 콜백으로 플레이어의 balloonCnt에서 1을 돌려줘야 함

	Character* p1{};
	Character* p2{};

	StreamManager* streamManager{};

	ItemManager* itemManager{};

	DartManager* dartManager{};

};

