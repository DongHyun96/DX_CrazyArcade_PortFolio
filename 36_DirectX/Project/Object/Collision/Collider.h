#pragma once
class Collider : public Transform
{
public:
	Collider();
	virtual ~Collider();

	void Render();

	virtual void SetVertex() = 0;

	bool Collision(Collider* other);

	virtual bool Collision(Vector2 point, Transform* owner = nullptr) = 0;

	virtual bool Collision(class ColliderRect* other, Transform* owner = nullptr) = 0;

	virtual bool Collision(class ColliderCircle* other) = 0;

	void SetColor(float r, float g, float b) { colorBuffer->SetData(Vector4(r, g, b, 1.f)); }

	bool& IsActive() { return isActive; }

protected:

	bool isActive{ true };

	vector<Vertex>	vertices;

	VertexBuffer*	vertexBuffer;

	VertexShader*	vertexShader;
	 PixelShader*	pixelShader;

	MatrixBuffer*	worldBuffer;
	ColorBuffer*	colorBuffer;
		

};
