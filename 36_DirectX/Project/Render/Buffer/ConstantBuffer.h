#pragma once
/* �ǽð����� �����͸� ��ȭ��ų buffer */
class ConstantBuffer
{
public:
	ConstantBuffer(void* data, UINT dataSize);
	virtual ~ConstantBuffer();

	// �����͸� ���̴��� �Ѱ��ִ� �Լ�
	void VSSetBuffer(UINT slot);
	void PSSetBuffer(UINT slot);

private:
	ID3D11Buffer* constantBuffer;

	void* data{};
	UINT dataSize{};
};

