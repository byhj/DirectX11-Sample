#ifndef Cube_H
#define Cube_H

#include <d3d11.h>
#include <DirectXMath.h>
#include <d3dx11effect.h>
#include <d3dxGlobal.h>

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
	void Render(ID3D11DeviceContext *pD3D11DeviceContext, d3d::MatrixBuffer matrix, float time, float waveiness);
	void Shutdown();

private:
	void init_buffer(ID3D11Device *pD3D11Device, ID3D11DeviceContext *pD3D11DeviceContext);
	void init_shader(ID3D11Device *pD3D11Device);
	void init_texture(ID3D11Device *pD3D11Device);

	CDXUTSDKMesh   m_SdkMesh;

	ID3D11InputLayout                   *m_pInputLayout     = nullptr;
	ID3DX11Effect                       *m_pEffect          = nullptr;
	ID3DX11EffectTechnique              *m_pEffectTechnique = nullptr;
	ID3DX11EffectMatrixVariable         *m_pModel           = nullptr;
	ID3DX11EffectMatrixVariable         *m_pView            = nullptr;
	ID3DX11EffectMatrixVariable         *m_pProj            = nullptr;
	ID3DX11EffectScalarVariable         *m_pWaviness        = nullptr;
	ID3DX11EffectScalarVariable         *m_pTime            = nullptr;
	ID3DX11EffectShaderResourceVariable *m_pTexSRV          = nullptr;
};


}

#endif