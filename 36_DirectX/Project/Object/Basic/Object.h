#pragma once
class Object : public Transform
{
public:
	Object(Vector2 size);

	// Texture 입힌 Object들
	Object(wstring file, Vector2 uvStart = Vector2(0, 0), Vector2 uvEnd = Vector2(1, 1)); // Texture size를 그대로 사용

	// Client가 정한 size 사용
	Object(Vector2 size, wstring file, Vector2 uvStart = Vector2(0, 0), Vector2 uvEnd = Vector2(1, 1)); 

	// 타일맵처럼 여러장 있을 때 분리하기 위한 용도
	Object(Vector2 size, wstring file, UINT frameX, UINT frameY, UINT targetX, UINT targetY); 


	~Object();

	void Render();

	void SetColor(const float& r, const float& g, const float& b, const float& a) { colorBuffer->SetData(Vector4(r, g, b, a)); }

	void SetData();

	Vector2 GetSize() const { return texture->GetSize(); }

private:
	vector<VertexTexture>	vertices{};
	vector<UINT>			indices{};

	VertexBuffer*			vertexBuffer;
	IndexBuffer*			indexBuffer;

	VertexShader*			vertexShader;

	PixelShader*			pixelShader;

	MatrixBuffer*			worldBuffer;
	ColorBuffer*			colorBuffer;

	Texture*				texture;
};
