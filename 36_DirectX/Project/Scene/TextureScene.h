#pragma once
class TextureScene : public Scene
{
public:
	
	TextureScene();
	~TextureScene();

	void Update() override;
	void Render() override;

private:
	Knight* knight{};

	Object* background{};
};
