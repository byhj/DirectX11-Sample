#include "RenderSystem.h"
#include <iostream>

namespace byhj
{

void RenderSystem::v_Init()
{
	init_device();
	init_camera();
	init_object();
}

void RenderSystem::v_Update()
{
	static float time = 0.0;
	time += 0.0001f;
	XMMATRIX rotMat = XMMatrixRotationY(time);
	XMStoreFloat4x4(&m_Matrix.model, XMMatrixTranspose(rotMat));

	m_Cube.Update();
}

void RenderSystem::v_Render()
{
	BeginScene();

	m_Cube.Render(m_pD3D11DeviceContext, m_Matrix);

	EndScene();
}

void RenderSystem::v_Shutdown()
{
	m_Cube.Shutdown();

	ReleaseCOM(m_pSwapChain);
	ReleaseCOM(m_pD3D11Device);
	ReleaseCOM(m_pD3D11DeviceContext);
	ReleaseCOM(m_pRenderTargetView);
}

void RenderSystem::init_device()
{
	DXGI_MODE_DESC bufferDesc;
	bufferDesc.Width                   = m_ScreenWidth;
	bufferDesc.Height                  = m_ScreenHeight;
	bufferDesc.RefreshRate.Numerator   = 60;
	bufferDesc.RefreshRate.Denominator = 1;
	bufferDesc.Format                  = DXGI_FORMAT_R8G8B8A8_UNORM;
	bufferDesc.ScanlineOrdering        = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	bufferDesc.Scaling                 = DXGI_MODE_SCALING_UNSPECIFIED;


	DXGI_SWAP_CHAIN_DESC swapChainDesc;
	ZeroMemory(&swapChainDesc, sizeof(DXGI_SWAP_CHAIN_DESC));
	swapChainDesc.BufferDesc         = bufferDesc;
	swapChainDesc.SampleDesc.Count   = 1;
	swapChainDesc.SampleDesc.Quality = 0;
	swapChainDesc.BufferUsage        = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.BufferCount        = 1;
	swapChainDesc.OutputWindow       = GetHwnd();
	swapChainDesc.Windowed           = TRUE;
	swapChainDesc.SwapEffect         = DXGI_SWAP_EFFECT_DISCARD;

	HRESULT hr;
	hr = D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE,
		NULL, NULL, NULL, NULL, D3D11_SDK_VERSION,
		&swapChainDesc, &m_pSwapChain, &m_pD3D11Device,
		NULL, &m_pD3D11DeviceContext);
	if (FAILED(hr))
		std::cout<<"Create Device and SwapChain fail"<<std::endl;

	//Create back buffer, buffer also is a texture
	ID3D11Texture2D *pBackBuffer;
	hr = m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&pBackBuffer);
	hr = m_pD3D11Device->CreateRenderTargetView(pBackBuffer, NULL, &m_pRenderTargetView);
	pBackBuffer->Release();

}

void RenderSystem::init_camera()
{
	D3D11_VIEWPORT vp;
	ZeroMemory(&vp, sizeof(D3D11_VIEWPORT));
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	vp.Width    = static_cast<float>(m_ScreenWidth);
	vp.Height   = static_cast<float>(m_ScreenHeight);
	m_pD3D11DeviceContext->RSSetViewports(1, &vp);

	//MVP Matrix
	XMVECTOR camPos    = XMVectorSet(0.0f, 0.0f, -5.0f, 0.0f);
	XMVECTOR camTarget = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
	XMVECTOR camUp     = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	XMMATRIX View      = XMMatrixLookAtLH(camPos, camTarget, camUp);
	XMMATRIX Proj      = XMMatrixPerspectiveFovLH(0.4f*3.14f, GetAspect(), 1.0f, 1000.0f);
	XMMATRIX Model     = XMMatrixIdentity();

	XMStoreFloat4x4(&m_Matrix.model, XMMatrixTranspose(Model));
	XMStoreFloat4x4(&m_Matrix.view, XMMatrixTranspose(View));
	XMStoreFloat4x4(&m_Matrix.proj, XMMatrixTranspose(Proj));
}

void RenderSystem::init_object()
{
	m_Cube.Init(m_pD3D11Device, m_pD3D11DeviceContext, GetHwnd() );
}

void RenderSystem::BeginScene()
{
	float bgColor[4] ={ 0.2f, 0.3f, 0.4f, 1.0f };
	m_pD3D11DeviceContext->OMSetRenderTargets(1, &m_pRenderTargetView, NULL);
	m_pD3D11DeviceContext->ClearRenderTargetView(m_pRenderTargetView, bgColor);
}

void RenderSystem::EndScene()
{
	m_pSwapChain->Present(0, 0);
}

}