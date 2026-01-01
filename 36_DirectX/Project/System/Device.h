#pragma once
class Device : public Singleton<Device>
{
	friend class Singleton; 

private:

	Device();
	~Device();

	void Initialize();

public:

	void ClearRTV(); // RanderTargetView
	void Present();

	ID3D11Device*			GetDevice() { return device; }
	ID3D11DeviceContext*	GetDC()		{ return deviceContext; }

	IDXGISwapChain* GetSwapChain() const { return swapChain; }

private:

	void CreateDepthStencil();

private:

	// interface (라이브러리명) (변수명) - 변수명을 구분짓기 위해 대부분 타입 앞에 라이브러리명을 붙임
	ID3D11Device*			device;         // 무언가를 만드는 역할, CPU를 다루는 객체
	ID3D11DeviceContext*	deviceContext;  // 무언가를 그리는 역할, GPU를 다루는 객체

	IDXGISwapChain*			swapChain;
	ID3D11RenderTargetView* renderTargetView;

	
	//Depth Stencil 관련
	ID3D11Texture2D*		g_pDepthStencil{};
	ID3D11DepthStencilView* stencilView{};
	ID3D11DepthStencilState* depthStencilState{};


};
