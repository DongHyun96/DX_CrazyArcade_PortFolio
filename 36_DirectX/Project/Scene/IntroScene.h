#pragma once
class IntroScene : public Scene
{
public:
	IntroScene();
	~IntroScene();

	// Scene을(를) 통해 상속됨
	virtual void Update() override;
	virtual void Render() override;

private:

	bool pressed = false;

	Object* background{};
	Object* desc{};

	vector<Object*> characters{};
	vector<Vector2> destPos{};

private:
	bool clicked{};
	float timer = 0.f;
	const float SPAWN_TICK = 0.4f;
};
