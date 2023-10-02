#pragma once

enum CharacterState
{
	SPAWN,
	IDLE,
	RIDING,
	CAPTURED,
	DEAD
};

class Character : public Transform
{
public:
	Character();
	virtual ~Character();

	virtual void Update();
	virtual void Render();

	void SetAction(int state);

	virtual void AddAction() = 0;

protected:

	VertexShader*			vertexShader{};
	PixelShader*			pixelShader{};

	MatrixBuffer*			worldBuffer{};

	Vector2					velocity{};

	CharacterState			mainState{IDLE};

	ColliderRect*			body{};


	//map<int, Animation*>	actions{};

	//Animation*			curAction{};

	//int					state{};
};
