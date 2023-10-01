#pragma once

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
	VertexShader* vertexShader;
	PixelShader* pixelShader;

	MatrixBuffer* worldBuffer;

	map<int, Animation*> actions{};

	Animation* curAction{};

	int state{};

	float moveSpeed{};

	Vector2 moveDir{};

	Collider* bodyCollider{};
};
