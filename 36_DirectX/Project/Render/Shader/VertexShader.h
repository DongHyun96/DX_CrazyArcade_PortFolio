#pragma once
class VertexShader
{
public:
	VertexShader(wstring file);
	~VertexShader();

	void SetShader();

private:
	void CreateInputLayout();

private:
	
	ID3D11InputLayout* inputLayout;
	ID3D11VertexShader* vertexShader;

	ID3D11ShaderReflection* reflection{};

	ID3DBlob* blob;
};
