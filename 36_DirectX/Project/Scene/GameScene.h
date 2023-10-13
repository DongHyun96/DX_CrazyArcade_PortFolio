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
	BalloonManager* balloonManager{}; // TODO ������ �� �ݹ����� �÷��̾��� balloonCnt���� 1�� ������� ��

	Character* p1{};
	Character* p2{};

	StreamManager* streamManager{};

	ItemManager* itemManager{};

	DartManager* dartManager{};

};

