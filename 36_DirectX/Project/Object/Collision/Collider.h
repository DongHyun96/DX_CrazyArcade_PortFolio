#pragma once
class Collider : public Transform
{
public:
	Collider();
	virtual ~Collider();

	void Render();

	virtual void SetVertex() = 0;

	bool OBBCollision(Collider* other);

	virtual bool OBBCollision(const Vector2& point, ColliderHolder* owner = nullptr) = 0;
	virtual bool OBBCollision(class ColliderRect* other, ColliderHolder* owner = nullptr) = 0;
	virtual bool OBBCollision(class ColliderCircle* other) = 0;

	

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
