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

	Object* tileExample{};

	Object* tileExamples[13][15];

	Transform* tileParentExample{};

	Collider* mapBoundary{};

	Knight* knight{};


};

