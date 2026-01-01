#pragma once

class MatrixBuffer : public ConstantBuffer
{
public:
	MatrixBuffer()
		:ConstantBuffer(&data, sizeof(Data))
	{
		data.matrix = XMMatrixIdentity();
	}

	void SetData(XMMATRIX value)
	{
		data.matrix = XMMatrixTranspose(value);
	}

private:
	struct Data
	{
		XMMATRIX matrix;
	};

	Data data;
};

class ColorBuffer : public ConstantBuffer
{
public:
	ColorBuffer()
		:ConstantBuffer(&data, sizeof(Data))
	{
	}

	void SetData(Vector4 color)
	{
		this->data.color = color;
	}

	void SetAlpha(const float& alpha)
	{
		this->data.color.z = alpha;
	}

private:
	struct Data
	{
		Vector4 color = { 1,1,1,1 };
	};

	Data data;
};