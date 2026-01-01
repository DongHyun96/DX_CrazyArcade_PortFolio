#pragma once
class IndexBuffer
{
public:
	IndexBuffer(vector<UINT>& indices);
	~IndexBuffer();

	void SetBuffer();

private:
	ID3D11Buffer* indexBuffer;
};
