#pragma once


class TutorialScene : public Scene
{
public:
	TutorialScene();
	~TutorialScene();

	virtual void Update() override;
	virtual void Render() override;

private:
	Object* object{};

	XMFLOAT2 translation;

	XMFLOAT4X4 S, R, T;	// XMFLOAT4X4 => XMMatrix와는 다르게 원소에 접근 가능

	XMMATRIX		worldMatrix;
	MatrixBuffer*	worldBuffer;
	
	float theta{}; // angle
};
