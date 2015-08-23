#ifndef RENDERSYSTEM_H
#define RENDERSYSTEM_H

#include <windows.h>
#include <d3d11.h>
#include <DirectXColors.h>

#include "d3d/App.h"
#include "d3d/Utility.h"
#include "triangle.h"

using namespace DirectX;

namespace byhj
{

class RenderSystem : public byhj::d3d::App
{

public:
	void v_Init()     override;
	void v_Update()   override;
	void v_Render()   override;
	void v_Shutdown() override;

private:
	void init_device();
	void init_camera();
	void init_object();
	void BeginScene();
	void EndScene();

private:

	Triangle m_Triangle;
	d3d::MatrixBuffer m_Matrix;

	IDXGISwapChain         *m_pSwapChain            = nullptr;
	ID3D11Device           *m_pD3D11Device          = nullptr;
	ID3D11DeviceContext    *m_pD3D11DeviceContext   = nullptr;
	ID3D11RenderTargetView *m_pRenderTargetView     = nullptr;
};


}

#endif