#pragma once
/* 실시간으로 데이터를 변화시킬 buffer */
class ConstantBuffer
{
public:
	ConstantBuffer(void* data, UINT dataSize);
	virtual ~ConstantBuffer();

	// 데이터를 셰이더에 넘겨주는 함수
	void VSSetBuffer(UINT slot);
	void PSSetBuffer(UINT slot);

private:
	ID3D11Buffer* constantBuffer;

	void* data{};
	UINT dataSize{};
};

