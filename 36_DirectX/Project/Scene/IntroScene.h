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

	vector<Object*> characters{};	// 화면에 출력할 캐릭터 sprite objects
	vector<Vector2> destPos{};		// 클릭 시, 캐릭터 sprite objects가 향할 destination position

private:
	bool		clicked{};
	float		timer{};
	const float SPAWN_TICK = 0.4f;
};
