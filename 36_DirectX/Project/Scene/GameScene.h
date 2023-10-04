#pragma once


class GameScene : public Scene
{
public:
	GameScene();
	~GameScene();

	virtual void Update() override;
	virtual void Render() override;

private:

	Object* mainUI{};
	Collider* mapBoundary{};

	TileManager* tileManager{};
	BlockManager* blockManager{};

	Block* block{};
	Util::Coord curBlockPos{};

	Block* block2{};

	Character* player{};
};

