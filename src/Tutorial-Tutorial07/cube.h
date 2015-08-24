#ifndef Cube_H
#define Cube_H

#include <d3d11.h>
#include <DirectXMath.h>

#include "d3d/Shader.h"
#include "d3d/Utility.h"

using namespace DirectX;

namespace byhj
{

class Cube
{

public:
	Cube();
	~Cube();

public:
	void Update();
	void Init(ID3D11Device *pD3D11Device, ID3D11DeviceContext *pD3D11DeviceContext);
	void Render(ID3D11DeviceContext *pD3D11DeviceContext, const d3d::MatrixBuffer &matrix);
	void Shutdown();

private:
	void init_buffer(ID3D11Device *pD3D11Device, ID3D11DeviceContext *pD3D11DeviceContext);
	void init_shader(ID3D11Device *pD3D11Device);
	void init_texture(ID3D11Device *pD3D11Device);

	struct Vertex
	{
		XMFLOAT3 Position;
		XMFLOAT2 Tex;
	};

	ID3D11InputLayout         *m_pInputLayout       = nullptr;
	ID3D11VertexShader        *m_pVS                = nullptr;
	ID3D11PixelShader         *m_pPS                = nullptr;
	ID3D11Buffer              *m_pVertexBuffer      = nullptr;
	ID3D11Buffer              *m_pIndexBuffer       = nullptr;
	ID3D11Buffer              *m_pMVPBuffer         = nullptr;
	ID3D11ShaderResourceView  *m_pTextureSRV        = nullptr;
	ID3D11SamplerState        *m_pSamplerLinear     = nullptr;

	int m_IndexCount = 0;
	int m_VertexCount = 0;
	d3d::MatrixBuffer cbMatrix;
	d3d::Shader CubeShader;
};


}

#endif