#pragma once
class Polygons : public Transform
{
public:
	Polygons(float radius, UINT sectorCount = 36, Vector4 color = {1.f, 0.f, 0.f, 1.f});
	virtual ~Polygons();

	void Render();

private:
	vector<VertexColor> vertices{};
	vector<UINT>		indices{};

	VertexBuffer*		vertexBuffer;
	IndexBuffer*		indexBuffer;

	VertexShader*		vertexShader;

	PixelShader*		pixelShader;

	MatrixBuffer*		worldBuffer;

};
