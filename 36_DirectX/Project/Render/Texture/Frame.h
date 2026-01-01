#pragma once
class Frame
{
public:
	
	Frame(wstring file, Vector2 uvStart = Vector2(0, 0), Vector2 uvEnd = Vector2(1, 1)); // Animation클래스에서 uv 좌표 계산하여 이용하는 생성자
	
	Frame(Vector2 texWorldSize, wstring file, Vector2 uvStart = Vector2(0, 0), Vector2 uvEnd = Vector2(1, 1)); // texWorldSize에 frame크기를 맞춤

	Frame(wstring file, UINT startX, UINT startY, UINT imgWidth, UINT imgHeight);

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
