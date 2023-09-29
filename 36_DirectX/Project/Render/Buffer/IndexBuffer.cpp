#include "Framework.h"
#include "IndexBuffer.h"


IndexBuffer::IndexBuffer(vector<UINT>& indices)
{
    D3D11_BUFFER_DESC bufferDesc = {};

    bufferDesc.ByteWidth            = sizeof(UINT) * indices.size();
    bufferDesc.Usage                = D3D11_USAGE_DEFAULT;
    bufferDesc.BindFlags            = D3D11_BIND_INDEX_BUFFER; //  buffer도 종류가 많음 / buffer의 용도를 설정
    bufferDesc.CPUAccessFlags       = 0;
    bufferDesc.MiscFlags            = 0;
    bufferDesc.StructureByteStride  = 0;

    D3D11_SUBRESOURCE_DATA initData{};
    initData.pSysMem = indices.data(); // data() / vector의 주소값을 반환하는 함수

    DEVICE->CreateBuffer(&bufferDesc, &initData, &indexBuffer);
}

IndexBuffer::~IndexBuffer()
{
    indexBuffer->Release();
}

void IndexBuffer::SetBuffer()
{
    DC->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);
}
