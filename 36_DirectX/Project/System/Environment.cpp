#include "Framework.h"
#include "Environment.h"


Environment::Environment()
{

	projectionMatrix = XMMatrixOrthographicOffCenterLH
	(
		0.f, WIN_WIDTH,
		0.f, WIN_HEIGHT,
		NEAR_Z, FAR_Z
	);

	projectionBuffer = new MatrixBuffer();

	CreateSamplerState();
	CreateBlendState();
	CreateRasterizerState();
}

Environment::~Environment()
{
	delete projectionBuffer;

	samplerState->Release();
	alphaBlend->Release();
	rasterizerState->Release();
}

void Environment::Set()
{
	projectionBuffer->SetData(projectionMatrix);

	projectionBuffer->VSSetBuffer(2);
}

void Environment::CreateSamplerState()
{
	D3D11_SAMPLER_DESC desc{};

	desc.Filter			= D3D11_FILTER_MIN_MAG_MIP_POINT;
	desc.AddressU		= D3D11_TEXTURE_ADDRESS_WRAP;
	desc.AddressV		= D3D11_TEXTURE_ADDRESS_WRAP;
	desc.AddressW		= D3D11_TEXTURE_ADDRESS_WRAP;
	desc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	desc.MinLOD			= 0;								// LOD - level of detail
	desc.MaxLOD			= D3D11_FLOAT32_MAX;

	DEVICE->CreateSamplerState(&desc, &samplerState);
	DC->PSSetSamplers(0, 1, &samplerState);
}

void Environment::CreateBlendState()
{
	D3D11_BLEND_DESC desc = {};
	desc.AlphaToCoverageEnable				   = true;
	desc.IndependentBlendEnable				   = false;
	desc.RenderTarget[0].BlendEnable           = true;
	desc.RenderTarget[0].SrcBlend              = D3D11_BLEND_SRC_ALPHA;
	desc.RenderTarget[0].DestBlend             = D3D11_BLEND_INV_SRC_ALPHA;
	desc.RenderTarget[0].BlendOp               = D3D11_BLEND_OP_ADD;
	desc.RenderTarget[0].SrcBlendAlpha         = D3D11_BLEND_ONE;
	desc.RenderTarget[0].DestBlendAlpha        = D3D11_BLEND_ZERO;
	desc.RenderTarget[0].BlendOpAlpha          = D3D11_BLEND_OP_ADD;
	desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	DEVICE->CreateBlendState(&desc, &alphaBlend);
	DC->OMSetBlendState(alphaBlend, nullptr, D3D11_DEFAULT_SAMPLE_MASK);

}

void Environment::CreateRasterizerState()
{
	D3D11_RASTERIZER_DESC desc = {};

	desc.FillMode = D3D11_FILL_SOLID;
	desc.CullMode = D3D11_CULL_NONE;

	DEVICE->CreateRasterizerState(&desc, &rasterizerState);
	DC->RSSetState(rasterizerState);
}
