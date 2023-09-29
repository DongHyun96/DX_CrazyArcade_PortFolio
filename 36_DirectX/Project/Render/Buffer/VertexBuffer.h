#pragma once
class VertexBuffer
{
public:
	template<typename T>
	VertexBuffer(vector<T>& vertices);

	~VertexBuffer();

    void SetBuffer(D3D11_PRIMITIVE_TOPOLOGY type = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

private:
	ID3D11Buffer* vertexBuffer;

    UINT stride{};
    UINT offset{};

};

template<typename T>
inline VertexBuffer::VertexBuffer(vector<T>& vertices)
{
    stride = sizeof(T);

    D3D11_BUFFER_DESC bufferDesc = {};

    bufferDesc.ByteWidth            = sizeof(T) * vertices.size();
    bufferDesc.Usage                = D3D11_USAGE_DEFAULT;
    bufferDesc.BindFlags            = D3D11_BIND_VERTEX_BUFFER; //  buffer도 종류가 많음 / buffer의 용도를 설정
    bufferDesc.CPUAccessFlags       = 0;
    bufferDesc.MiscFlags            = 0;
    bufferDesc.StructureByteStride  = 0;

    D3D11_SUBRESOURCE_DATA initData{};
    initData.pSysMem = vertices.data(); // data() / vector의 주소값을 반환하는 함수

    DEVICE->CreateBuffer(&bufferDesc, &initData, &vertexBuffer);
}
