#ifndef RENDERSYSTEM_H
#define RENDERSYSTEM_H

#include <windows.h>
#include <d3d11.h>
#include <DirectXColors.h>

#include "d3d/App.h"
#include "d3d/Utility.h"
#include "Cube.h"

using namespace DirectX;

namespace byhj
{

class RenderSystem 
{

public:
	void Init(ID3D11Device *pD3D11Deivce, ID3D11DeviceContext *pD3D11DeviceContext);
	void Update()   ;
	void Render(ID3D11DeviceContext *pD3D11DeviceContext);
	void Shutdown() ;
	void init_camera(float width, float height, ID3D11DeviceContext *pD3D11DeviceContext);

private:
	void init_object(ID3D11Device *pD3D11Deivce, ID3D11DeviceContext *pD3D11DeviceContext);

private:

	Cube m_Cube;
	d3d::MatrixBuffer m_Matrix;
};


}

#endif