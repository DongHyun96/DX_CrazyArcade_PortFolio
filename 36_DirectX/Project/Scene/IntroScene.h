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


};
