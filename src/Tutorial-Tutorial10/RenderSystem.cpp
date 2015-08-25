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

void RenderSystem::Render(ID3D11DeviceContext *pD3D11DeviceContext, d3d::MatrixBuffer m_Matrix)
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

}

void RenderSystem::init_object(ID3D11Device *pD3D11Deivce, ID3D11DeviceContext *pD3D11DeviceContext)
{
	m_Model.Init(pD3D11Deivce, pD3D11DeviceContext);
}



}