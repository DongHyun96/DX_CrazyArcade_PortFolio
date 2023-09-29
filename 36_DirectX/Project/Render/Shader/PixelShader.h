#pragma once
class PixelShader
{
public:
	PixelShader(wstring file);
	~PixelShader();

	void SetShader();

private:
	ID3DBlob* blob;

	ID3D11PixelShader* pixelShader;

};
