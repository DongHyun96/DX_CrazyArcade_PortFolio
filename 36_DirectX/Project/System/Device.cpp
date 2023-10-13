#include "Framework.h"
#include "Device.h"


Device::Device()
{
	Initialize();
}

Device::~Device()
{
              device->Release();
       deviceContext->Release();
           swapChain->Release();
    renderTargetView->Release();

    g_pDepthStencil->Release();
    stencilView->Release();
    depthStencilState->Release();
}

void Device::Initialize()
{

    // Swap Chain�� �������� ��� �� ����ü
    DXGI_SWAP_CHAIN_DESC swapChainDesc = {}; // �Ű������� ���� ����ü (Descriptor)

    swapChainDesc.BufferDesc.Width                      = WIN_WIDTH;
    swapChainDesc.BufferDesc.Height                     = WIN_HEIGHT;

    // ������ �𸮾�ó�� 0���� 1������ ���� �� (unsigned normalized) / signed normalized -> -1 ~ 1
    swapChainDesc.BufferDesc.Format                     = DXGI_FORMAT_R8G8B8A8_UNORM;
    swapChainDesc.BufferDesc.RefreshRate.Numerator      = 60; // RefreshRate ����� (�ֻ���)
    swapChainDesc.BufferDesc.RefreshRate.Denominator    = 1;

    swapChainDesc.SampleDesc.Count                      = 1; // sampleDesc -> ���ø��� ������ descriptor
    swapChainDesc.SampleDesc.Quality                    = 0; // 1, 0 -> �ش� �ȼ����� �״�� �� ���� (sampling ��� x )

    swapChainDesc.BufferUsage                           = DXGI_USAGE_RENDER_TARGET_OUTPUT; // ������ �뵵
    swapChainDesc.BufferCount                           = 1; //BackBuffer�� ����
    swapChainDesc.OutputWindow                          = hWnd;
    swapChainDesc.Windowed                              = false; // â��带 �� ������

    D3D11CreateDeviceAndSwapChain
    (
        nullptr,
        D3D_DRIVER_TYPE_HARDWARE,
        0,
        D3D11_CREATE_DEVICE_BGRA_SUPPORT,
        nullptr,
        0,
        D3D11_SDK_VERSION,
        &swapChainDesc,
        &swapChain, // o �� �� �Ҵ��
        &device,    // o
        nullptr,
        &deviceContext // o
    );

    // Texture2D -> ���������� ���
    ID3D11Texture2D* backBuffer{};

    // ���������� �Ķ���� -> backBuffer�� �޼��� �ȿ��� �Ҵ����ִ°͸� �˸� ��
    // __uuidof (Ŭ������ ������ uuid�� ������ �ְ� uuidof�� �ش� Ŭ������ ���� �ĺ� id�� ������)
    swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backBuffer);

    // view�� �� ģ���� -> GPU �� ���ҽ��� �ٷ� (RAM�� �Ҵ�Ǵ� ���� �ƴ� VRAM�� �Ҵ��� ��)
    device->CreateRenderTargetView(backBuffer, nullptr, &renderTargetView);

    // backBuffer�� renderTargetView�� ����� ����
    backBuffer->Release();

    CreateDepthStencil();

    //deviceContext->OMSetRenderTargets(1, &renderTargetView, nullptr);
    deviceContext->OMSetRenderTargets(1, &renderTargetView, stencilView);


    /*  ViewPort */
    D3D11_VIEWPORT viewPort;

    viewPort.TopLeftX = 0.f;
    viewPort.TopLeftY = 0.f;
    viewPort.Width = WIN_WIDTH;
    viewPort.Height = WIN_HEIGHT;
    viewPort.MinDepth = 0.f;
    viewPort.MaxDepth = 1.f;

    deviceContext->RSSetViewports(1, &viewPort); // RS stands for Rasterizer state
}

void Device::ClearRTV()
{
    float clearColor[4] = { 0.33f, 0.33f, 0.33f, 1.0f };
    deviceContext->ClearRenderTargetView(renderTargetView, clearColor); // ȭ���� ������ �ʱ�ȭ�ϴ� �� (PltBlt�� ���� ����)

    deviceContext->ClearDepthStencilView(stencilView, D3D11_CLEAR_DEPTH, 1.f, 0);
}

void Device::Present()
{
    // WINAPI ������ BackDC�� �ִ� ���� BitBlt�� ���� �������� DC�� ������ ����
    // SwapChain������ present�� ���� ��� �׸� ���۸� "������Ʈ"��Ŵ
    swapChain->Present(0, 0); // ������Ʈ - ǥ���ϴ�, ���� swap�� ���⼭ ��
}

void Device::CreateDepthStencil()
{
    D3D11_TEXTURE2D_DESC descDepth;
    descDepth.Width                 = WIN_WIDTH;
    descDepth.Height                = WIN_HEIGHT;
    descDepth.MipLevels             = 1;
    descDepth.ArraySize             = 1;
    descDepth.Format                = DXGI_FORMAT_D24_UNORM_S8_UINT;
    descDepth.SampleDesc.Count      = 1;
    descDepth.SampleDesc.Quality    = 0;
    descDepth.Usage                 = D3D11_USAGE_DEFAULT;
    descDepth.BindFlags             = D3D11_BIND_DEPTH_STENCIL;
    descDepth.CPUAccessFlags        = 0;
    descDepth.MiscFlags             = 0;

    device->CreateTexture2D(&descDepth, nullptr, &g_pDepthStencil);

    D3D11_DEPTH_STENCIL_DESC depthStencilStateDesc;
    ZeroMemory(&depthStencilStateDesc, sizeof(D3D11_DEPTH_STENCIL_DESC));


    depthStencilStateDesc.DepthEnable       = TRUE;
    depthStencilStateDesc.DepthWriteMask    = D3D11_DEPTH_WRITE_MASK_ALL;
    depthStencilStateDesc.DepthFunc         = D3D11_COMPARISON_LESS;
    depthStencilStateDesc.StencilEnable     = FALSE;

    device->CreateDepthStencilState(&depthStencilStateDesc, &depthStencilState);
    deviceContext->OMSetDepthStencilState(depthStencilState, 1);

    D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;

    ZeroMemory(&descDSV, sizeof(descDSV));
    descDSV.Format = descDepth.Format;
    descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
    descDSV.Texture2D.MipSlice = 0;

    device->CreateDepthStencilView(g_pDepthStencil, &descDSV, &stencilView);
}
