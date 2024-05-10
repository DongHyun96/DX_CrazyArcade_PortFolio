#pragma once
/* CONCRETE CLASS */
class IntroScene : public Scene
{
public:
	IntroScene();
	~IntroScene();

	virtual void Update() override;
	virtual void Render() override;

private:

	Object*	background{};
	Object*	desc{};

private:

	vector<Object*> characters{};	// ȭ�鿡 ����� ĳ���� sprite objects
	vector<Vector2> destPos{};		// Ŭ�� ��, ĳ���� sprite objects�� ���� destination position

private:
	bool		clicked{};
	float		timer{};
	const float SPAWN_TICK = 0.4f;
};
