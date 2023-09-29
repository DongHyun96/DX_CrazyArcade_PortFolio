#pragma once
class SRTScene : public Scene
{
public:
	SRTScene();
	~SRTScene();

	virtual void Update() override;
	virtual void Render() override;

private:
	Object* object;

	XMFLOAT2 scale{1.f, 1.f};
	XMFLOAT2 translation{};

	float angle{};

	XMMATRIX world{};
	XMMATRIX world2{};
	
	XMMATRIX S, R, T;

	MatrixBuffer* worldBuffer;
	
};
