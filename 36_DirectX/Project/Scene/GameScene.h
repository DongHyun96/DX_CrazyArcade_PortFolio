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
	BalloonManager* balloonManager{}; // TODO ������ �� �ݹ����� �÷��̾��� balloonCnt���� 1�� ������� ��


	Block* block{};
	Util::Coord curBlockPos{};

	Block* block2{};

	Character* player{};

	StreamManager* streamManager{};

	ItemManager* itemManager{};

	DartManager* dartManager{};

};

