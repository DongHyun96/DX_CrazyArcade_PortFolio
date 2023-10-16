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

    // Swap Chain의 설정값을 모아 둔 구조체
    DXGI_SWAP_CHAIN_DESC swapChainDesc = {}; // 매개변수를 모은 구조체 (Descriptor)

    swapChainDesc.BufferDesc.Width                      = WIN_WIDTH;
    swapChainDesc.BufferDesc.Height                     = WIN_HEIGHT;

    // 색상을 언리얼처럼 0부터 1까지의 값을 씀 (unsigned normalized) / signed normalized -> -1 ~ 1
    swapChainDesc.BufferDesc.Format                     = DXGI_FORMAT_R8G8B8A8_UNORM;
    swapChainDesc.BufferDesc.RefreshRate.Numerator      = 60; // RefreshRate 재생빈도 (주사율)
    swapChainDesc.BufferDesc.RefreshRate.Denominator    = 1;

    swapChainDesc.SampleDesc.Count                      = 1; // sampleDesc -> 샘플링과 관련한 descriptor
    swapChainDesc.SampleDesc.Quality                    = 0; // 1, 0 -> 해당 픽셀값을 그대로 쓸 것임 (sampling 사용 x )

    swapChainDesc.BufferUsage                           = DXGI_USAGE_RENDER_TARGET_OUTPUT; // 버퍼의 용도
    swapChainDesc.BufferCount                           = 1; //BackBuffer의 개수
    swapChainDesc.OutputWindow                          = hWnd;
    swapChainDesc.Windowed                              = false; // 창모드를 쓸 것인지

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
        &swapChain, // o 셋 다 할당됨
        &device,    // o
        nullptr,
        &deviceContext // o
    );

    // Texture2D -> 범용적으로 사용
    ID3D11Texture2D* backBuffer{};

    // 이중포인터 파라미터 -> backBuffer를 메서드 안에서 할당해주는것만 알면 됨
    // __uuidof (클래스는 고유의 uuid를 가지고 있고 uuidof는 해당 클래스의 고유 식별 id를 꺼내옴)
    swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backBuffer);

    // view가 들어간 친구들 -> GPU 쪽 리소스를 다룸 (RAM에 할당되는 것이 아닌 VRAM에 할당이 됨)
    device->CreateRenderTargetView(backBuffer, nullptr, &renderTargetView);

    // backBuffer는 renderTargetView를 만들면 끝남
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
    deviceContext->ClearRenderTargetView(renderTargetView, clearColor); // 화면을 백지로 초기화하는 것 (PltBlt과 같은 과정)

    deviceContext->ClearDepthStencilView(stencilView, D3D11_CLEAR_DEPTH, 1.f, 0);
}

void Device::Present()
{
    // WINAPI 에서는 BackDC에 있는 것을 BitBlt을 통해 보여지는 DC에 정보를 보냄
    // SwapChain에서는 present를 통해 방금 그린 버퍼를 "프리젠트"시킴
    swapChain->Present(0, 0); // 프리젠트 - 표시하다, 실제 swap을 여기서 함
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
