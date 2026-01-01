#include "Framework.h"
#include "ConstantBuffer.h"

ConstantBuffer::ConstantBuffer(void* data, UINT dataSize)
	:data(data), dataSize(dataSize)
{
    D3D11_BUFFER_DESC bufferDesc = {};

    bufferDesc.ByteWidth            = dataSize;
    bufferDesc.Usage                = D3D11_USAGE_DEFAULT;
    bufferDesc.BindFlags            = D3D11_BIND_CONSTANT_BUFFER; //  buffer도 종류가 많음 / buffer의 용도를 설정
    bufferDesc.CPUAccessFlags       = 0;
    bufferDesc.MiscFlags            = 0;
    bufferDesc.StructureByteStride  = 0;

    DEVICE->CreateBuffer(&bufferDesc, nullptr, &constantBuffer);
}

ConstantBuffer::~ConstantBuffer()
{
    constantBuffer->Release();
}

void ConstantBuffer::VSSetBuffer(UINT slot)
{
    // Subresource -> 버퍼를 의미
    DC->UpdateSubresource(constantBuffer, 0, nullptr, data, 0, 0);
    DC->VSSetConstantBuffers(slot, 1, &constantBuffer);
}

void ConstantBuffer::PSSetBuffer(UINT slot)
{
    DC->UpdateSubresource(constantBuffer, 0, nullptr, data, 0, 0);
    DC->PSSetConstantBuffers(slot, 1, &constantBuffer);
}

