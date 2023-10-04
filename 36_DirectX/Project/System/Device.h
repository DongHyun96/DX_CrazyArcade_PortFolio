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

private:
	void CreateDepthStencil();

private:

	// interface (���̺귯����) (������) - �������� �������� ���� ��κ� Ÿ�� �տ� ���̺귯������ ����
	ID3D11Device*			device;         // ���𰡸� ����� ����, CPU�� �ٷ�� ��ü
	ID3D11DeviceContext*	deviceContext;  // ���𰡸� �׸��� ����, GPU�� �ٷ�� ��ü

	IDXGISwapChain*			swapChain;
	ID3D11RenderTargetView* renderTargetView;

	
	//Depth Stencil ����
	ID3D11Texture2D*		g_pDepthStencil{};
	ID3D11DepthStencilView* stencilView{};
	ID3D11DepthStencilState* depthStencilState{};


};
