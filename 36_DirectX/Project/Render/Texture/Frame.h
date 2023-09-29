#pragma once
class Frame
{
public:
	Frame(wstring file, Vector2 uvStart = Vector2(0, 0), Vector2 uvEnd = Vector2(1, 1));
	Frame(wstring file, UINT startX, UINT startY, UINT width, UINT height);

	~Frame();

	void Render();

	Vector2 Size() const { return size; }

private:
	vector<VertexTexture>	vertices{};
	vector<UINT>			indices{};

	VertexBuffer*			vertexBuffer;
	IndexBuffer*			indexBuffer;

	Texture*				texture;

	Vector2					size;
};
