#pragma once
// Scene과 무관하게 세팅하는 환경값
class Environment : public Singleton<Environment>
{
public:
	Environment();
	~Environment();

	void Set();

	void CreateSamplerState();
	void CreateBlendState();
	void CreateRasterizerState();

private:
	XMMATRIX	  projectionMatrix;


	MatrixBuffer* projectionBuffer;

	ID3D11SamplerState* samplerState;

	ID3D11BlendState*	alphaBlend;

	ID3D11RasterizerState* rasterizerState;

};
