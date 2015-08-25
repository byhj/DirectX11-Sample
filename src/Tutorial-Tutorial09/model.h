#ifndef Cube_H
#define Cube_H

#include <d3d11.h>
#include <DirectXMath.h>
#include "SDKmesh.h"

#include "d3d/Shader.h"
#include "d3d/Utility.h"

using namespace DirectX;

namespace byhj
{

class Model
{

public:
	Model();
	~Model();

public:
	void Update();
	void Init(ID3D11Device *pD3D11Device, ID3D11DeviceContext *pD3D11DeviceContext);
	void Render(ID3D11DeviceContext *pD3D11DeviceContext, const d3d::MatrixBuffer &matrix);
	void Shutdown();

private:
	void init_buffer(ID3D11Device *pD3D11Device, ID3D11DeviceContext *pD3D11DeviceContext);
	void init_shader(ID3D11Device *pD3D11Device);
	void init_texture(ID3D11Device *pD3D11Device);

	struct LightBuffer
	{
		XMFLOAT4 lightPos;
	};

	ID3D11InputLayout         *m_pInputLayout       = nullptr;
	ID3D11VertexShader        *m_pVS                = nullptr;
	ID3D11PixelShader         *m_pPS                = nullptr;
	ID3D11Buffer              *m_pMVPBuffer         = nullptr;
	ID3D11Buffer              *m_pLightBuffer       = nullptr;
	ID3D11SamplerState        *m_pSamplerLinear     = nullptr;

	CDXUTSDKMesh   m_SdkMesh;
	d3d::MatrixBuffer cbMatrix;
	d3d::Shader CubeShader;
};


}

#endif