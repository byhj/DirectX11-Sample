#include "RenderSystem.h"
#include <iostream>

namespace byhj
{

void RenderSystem::Init(ID3D11Device *pD3D11Deivce, ID3D11DeviceContext *pD3D11DeviceContext)
{
	init_object(pD3D11Deivce, pD3D11DeviceContext);
}

void RenderSystem::Update()
{
	static float time = 0.0;
	time += 0.0001f;
	XMMATRIX rotMat = XMMatrixRotationY(time);
	XMStoreFloat4x4(&m_Matrix.model, XMMatrixTranspose(rotMat));

	m_Model.Update();
}

void RenderSystem::Render(ID3D11DeviceContext *pD3D11DeviceContext)
{
	m_Model.Render(pD3D11DeviceContext, m_Matrix);

}

void RenderSystem::Shutdown()
{
	m_Model.Shutdown();
}



void RenderSystem::init_camera(float width, float height, ID3D11DeviceContext *pD3D11DeviceContext)
{
	D3D11_VIEWPORT vp;
	ZeroMemory(&vp, sizeof(D3D11_VIEWPORT));
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	vp.Width    = width;
	vp.Height   = height;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	pD3D11DeviceContext->RSSetViewports(1, &vp);
	float aspect = width / height;

	//MVP Matrix
	XMVECTOR camPos    = XMVectorSet(0.0f, 3.0f, -500.0f, 0.0f);
	XMVECTOR camTarget = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
	XMVECTOR camUp     = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	XMMATRIX View      = XMMatrixLookAtLH(camPos, camTarget, camUp);
	XMMATRIX Proj      = XMMatrixPerspectiveFovLH(0.4f*3.14f, aspect, 1.0f, 1000.0f);
	XMMATRIX Model     = XMMatrixIdentity();

	XMStoreFloat4x4(&m_Matrix.model, XMMatrixTranspose(Model));
	XMStoreFloat4x4(&m_Matrix.view, XMMatrixTranspose(View));
	XMStoreFloat4x4(&m_Matrix.proj, XMMatrixTranspose(Proj));
	pD3D11DeviceContext = 0;
}

void RenderSystem::init_object(ID3D11Device *pD3D11Deivce, ID3D11DeviceContext *pD3D11DeviceContext)
{
	m_Model.Init(pD3D11Deivce, pD3D11DeviceContext);
}



}